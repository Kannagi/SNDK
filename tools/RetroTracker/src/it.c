#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "KS.h"
#include "it.h"

int IT_Load(char *name,int *option)
{
	int info = option[2];
	int size = 0,i;
	KS_FORMAT ks;
	unsigned char *data;
	char str[100];
	FILE *fichier;
    fichier = fopen(name,"rb");

    if(fichier == NULL) return 1;

    IT_HEADER it;
    IT_PATTERNS it_patterns;
	IT_SAMPLE it_sample;
	IT_INSTRUMENTS it_instruments;

    fread ( (char*)&it,1,4,fichier);
    sprintf(str,"%.4s",it.impm);

    if(strcmp(str,"IMPM") != 0)
    {
    	fclose(fichier);
    	return 1;
    }
    fread ( (char*)&it.title,1,188,fichier);

    if(info != 0) it_print(it);

    output_filename(name,str);

	KS_set_header(&ks,str,16,it.insnum,it.is,it.it);
	init_brr(ks.name,option[3]);

    fread ( (char*)&it.ord_table,1,it.ordnum,fichier);

    fread ( (int*)&it.insOff,4,it.insnum,fichier);
    fread ( (int*)&it.smpOff,4,it.smpnum,fichier);
    fread ( (int*)&it.patOff,4,it.patnum,fichier);

    // read instruments
	for (i = 0; i < it.insnum; i++)
	{
		fseek(fichier,it.insOff[i],SEEK_SET);
		KS_instruments_init(&ks,i);

		fread ( (char*)&it_instruments,1,17,fichier);
		if(info != 0) it_print_instruments(it_instruments,i);
		if(it.cwtv >= 0x200)
		{
			fread ( (char*)&it_instruments.n,1,3,fichier);
			fread ( (char*)&it_instruments.n.fadeout,1,45,fichier);
			if(info != 0) it_print_instruments_new(it_instruments.n);

			fread ( (char*)&it_instruments.n.notetrans,1,240,fichier);
			fread ( (char*)&it_instruments.n.vol_env,1,108*3,fichier);
		}else
		{

			fread ( (char*)&it_instruments.o,1,7,fichier);
			fread ( (char*)&it_instruments.o.fadeout,1,40,fichier);
			if(info != 0) it_print_instruments_old(it_instruments.o);

			fread ( (char*)&it_instruments.o.notetrans,1,240,fichier);
			fread ( (char*)&it_instruments.o.vol_env,1,250,fichier);
		}


	}

	// read samples
	for (i = 0; i < it.smpnum; i++)
	{
		fseek(fichier,it.smpOff[i],SEEK_SET);

		fread ( (char*)&it_sample,1,17,fichier);

		fread ( (char*)&it_sample.gvl,1,1,fichier);
		fread ( (char*)&it_sample.flag,1,1,fichier);
		fread ( (char*)&it_sample.vol,1,1,fichier);
		fread ( (char*)&it_sample.name,1,60,fichier);


		if(info != 0) it_print_sample(it_sample,i);

		//0x01 enable/disable ,0x02 :8/16 bits ,0x08 PCM/compressed , 0x10 loop , ping pong etc etc
		if(it_sample.flag&1)
		{
			fseek(fichier,it_sample.sample_pointer,SEEK_SET);

			int bitssize = (it_sample.flag&2)>>1;
			int length = it_sample.length<<bitssize;

			data = malloc(length*sizeof(char));

			fread ( data,1,length,fichier);


			int loop_end = it_sample.loop_end<<bitssize;
			int loop_start = it_sample.loop_start<<bitssize;

			sprintf(str,"%s_sample%d.brr",ks.name,i);


			if(option[9] > 0)
				sprintf(str,"data%d_sample%d.brr",option[9]-1,i);

			int relative = (12*2)+it_relative(it_sample.c5speed);
			int type = 0;
			if(it_sample.flag&0xF0) type = 1;

			KS_savedata_sample(&ks,str,option,data,i,loop_start,loop_end,
								it_sample.vol,relative,type,bitssize,it_sample.c5speed/2);
			free(data);
		}
	}

	// read pattern
	int l;
	for (i = 0; i < it.ordnum-1; i++)
	{
		l = it.ord_table[i];
		fseek(fichier,it.patOff[l],SEEK_SET);

		fread ( (char*)&it_patterns,1,8,fichier);

		//if(info != 0) it_print_patterns(it_patterns,i);

		size += it_patterns.rows;
	}

	KS_set_pattern(&ks,size);

	// convert pattern
	size = 0;
	i = 0;
	for (i = 0; i < it.ordnum-1; i++)
	{
		l = it.ord_table[i];
		fseek(fichier,it.patOff[l],SEEK_SET);
		fread ( (char*)&it_patterns,1,8,fichier);
		ks.rows[i] = it_patterns.rows;
		it_convert_pattern(&ks,fichier,it_patterns.length,size);
		size += it_patterns.rows;
	}
	fclose(fichier);

	KS_write(&ks,option);
	close_brr();

    return 0;

}

void it_convert_pattern(KS_FORMAT *ks,FILE *fichier,int n,int begin)
{
	int byte,chan = 0,i,tmp,line = begin;
	char last_mask[16];
	KS_FORMAT_PATTERN KS_tmp[0x1F];

	for (i = 0; i < n;)
	{
		do
		{
			byte = fgetc(fichier);
			i++;
			if(byte == 0) line++;

			if(i >= n) return;
		}while(byte == 0);

		chan = (byte&0x1F)-1;

		if(byte&0x80)
		{

			byte = fgetc(fichier);
			i++;
			last_mask[chan] = byte;
		}else
		{
			byte = last_mask[chan];
		}
		ks->pattern[chan][line].flags = 0;

		if(byte&0x01)
		{
			tmp = fgetc(fichier);
			i++;
			if (tmp == 255)	// key off
			{
				ks->pattern[chan][line].note = 0;
				KS_tmp[chan].note = 0;
				ks->pattern[chan][line].flags |= 0x01;
			}
			else if (tmp == 254) // note cut
			{
				ks->pattern[chan][line].note = 0;
				KS_tmp[chan].note = 0;
				ks->pattern[chan][line].flags |= 0x01;
			}
			else if (tmp >= 12*10); // fade out
			else if (tmp < 12*10)
			{
				ks->pattern[chan][line].note = tmp;
				KS_tmp[chan].note = tmp;
				ks->pattern[chan][line].flags |= 0x01;
			}
			//if(chan == 0) printf("(%d),",tmp);
		}


		if(byte&0x02)
		{
			tmp = fgetc(fichier);
			ks->pattern[chan][line].instrument = tmp;
			KS_tmp[chan].instrument = tmp;
			i++;

			ks->pattern[chan][line].flags |= 0x02;
		}

		if(byte&0x04)
		{
			i++;
			tmp = fgetc(fichier);
			if(tmp <=  64)
			{
				ks->pattern[chan][line].volume = tmp;
				KS_tmp[chan].volume = tmp;
				ks->pattern[chan][line].flags |= 0x04;

			}
		}


		if(byte&0x08)
		{
			i += 2;
			ks->pattern[chan][line].effect1 = fgetc(fichier);
			ks->pattern[chan][line].effect2 = fgetc(fichier);

			ks->pattern[chan][line].effect1 = it_convert_effect(ks->pattern[chan][line].effect1);

			KS_tmp[chan].effect1 = ks->pattern[chan][line].effect1;
			KS_tmp[chan].effect2 = ks->pattern[chan][line].effect2;
			ks->pattern[chan][line].flags |= 0x08;
		}

		if(byte&0x10)
		{
			ks->pattern[chan][line].note = KS_tmp[chan].note;
			ks->pattern[chan][line].flags |= 0x01;
		}

		if(byte&0x20)
		{
			ks->pattern[chan][line].instrument = KS_tmp[chan].instrument;
			ks->pattern[chan][line].flags |= 0x02;
		}

		if(byte&0x40)
		{
			ks->pattern[chan][line].volume = KS_tmp[chan].volume;
			ks->pattern[chan][line].flags |= 0x04;
		}

		if(byte&0x80)
		{

			ks->pattern[chan][line].effect1 = KS_tmp[chan].effect1;
			ks->pattern[chan][line].effect2 = KS_tmp[chan].effect2;

			ks->pattern[chan][line].flags |= 0x18;
		}

		if(ks->pattern[chan][line].effect1 == 0x0D)
		{
			ks->pattern[chan][line].volume = ks->pattern[chan][line].effect2;
			ks->pattern[chan][line].flags |= 0x04;
			ks->pattern[chan][line].flags = ks->pattern[chan][line].flags&0x7;
			ks->pattern[chan][line].effect1 = 0xFF;
		}

	}
}

int it_convert_effect(int effect)
{

	switch(effect)
	{
		// Axx     Set speed
		case 0x01:
			return KS_Set_tempo;
		break;

		// Bxx     Jump to Order
		case 0x02:
			return KS_Position_jump;
		break;

		// Cxx     Break to Row
		case 0x03:
			return KS_Pattern_break;
		break;

		// Dxx     Volume slide down
		case 0x04:
			return KS_Volume_slide;
		break;

		// Exx     porta down
		case 0x05:
			return KS_porta_down;
		break;

		// Fxx     porta up
		case 0x06:
			return KS_porta_up;
		break;

		// Gxx     tone porta
		case 0x07:
			return KS_Toneporta;
		break;

		// Hxy     Vibrato
		case 0x08:
			return KS_Vibrato;
		break;

		// Ixy     Tremor, ontime x, offtime y
		case 0x09:

		break;

		// Jxy     arpeggio
		case 0x0A:
			return KS_Appregio;
		break;

		// Kxy     vibrato & volslide
		case 0x0B:
			return KS_Vibrato_Volume_slide;
		break;

		// Lxx     tone porta & volslide
		case 0x0C:
			return KS_Toneporta_Volume_slide;
		break;

		// Mxx     set channel volume
		case 0x0D:

		break;

		// Nxx     channel volslide
		case 0x0E:
			return KS_Volume_slide;
		break;

		// Oxx     set sample offset
		case 0x0F:

		break;

		// Pxx     panning slide (TO-DO)
		case 0x10:
			return 0x09;
		break;

		// Qxx     retrig
		case 0x11:

		break;

		// Rxy     tremolo
		case 0x12:
			return KS_Tremolo;
		break;
/*
		// various subeffects
		case 0x13:
		eff = op>>4;
		switch (eff)
		{
			case 0x0:
			break;
			// past note actions/envelope trigger control etc.
			case 0x7:

			break;
			// set panning
			case 0x8:

			break;
			// set high sample offset
			case 0xA:

			break;
			// pattern loop
			case 0xB:

			break;
			// note cut
			case 0xC:

			break;
			// note delay
			case 0xD:

			break;
			// pattern delay
			case 0xE:

			break;
		}
		*/

		// Txx     set tempo
		case 0x14:

		break;

		// Uxx     fine vibrato
		case 0x15:
		break;

		// Vxx     set global volume
		case 0x16:

		break;

		// Wxx	   global volume slide (stupid IT/MPT)
		case 0x17:

		break;

		// Xxx	   set panning (0->FF)
		case 0x18:
			return 0x09;
		break;

		// Yxx	   panbrello
		case 0x19:

		break;
	}
	return 0xFF;
}

int it_relative(int spd)
{
	int i,n;
	double oct = 16,frq;
	int frqp;

	for(i = 0;i < 12*14;i++)
	{
		n = i%12;
		if(n == 0) oct *=2;
		frq = oct;
		frq *= pow(1.0594630943,n);
		frqp = frq;

		if(frqp > spd)
			return i-109;

	}

	return 0;
}
