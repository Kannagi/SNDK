#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "KS.h"
#include "mod.h"

int MOD_Load(char *name,int *option)
{
	int size = 0,i,n = 0,cnt,note,eff,ins,chan = 4,r,c,line,ns;
	KS_FORMAT ks;
	char str[100],buffer[4096];
	unsigned char b1,b2,b3,b4;
	FILE *fichier;
    fichier = fopen(name,"rb");

    if(fichier == NULL) return 1;

    MOD_HEADER mod;
	MOD_SAMPLE mod_sample[32];

	fread ( (char*)&mod,1,20,fichier);

	fseek(fichier, 1080, SEEK_SET);
	fread ( (char*)&mod.id,1,4,fichier);


	chan = mod_id(mod.id);
	if(chan == -1)
    {
    	fclose(fichier);
    	return 1;
    }

    printf("MOD file : %s\n",mod.name);

    int info = option[2];

	if(info != 0) mod_print(mod);
	ns = 31;

	fseek(fichier, 20, SEEK_SET);
	for(i = 0;i < ns; i++)
	{
		fread ( (char*)&mod_sample[i],1,30,fichier);
		mod_sample_xor(&mod_sample[i]);
		if(info != 0) mod_print_sample(mod_sample[i],i);
	}

	fread ( (char*)&mod.ordnum,1,130,fichier);
	if(info != 0) mod_print2(mod);

	KS_set_header(&ks,mod.name,chan,32,6,125);
	init_brr(ks.name,option[3]);

	int patnum=0;
	for (i = 0;i < mod.ordnum;i++)
		if (mod.Pattern_Table[i] > patnum) patnum = mod.Pattern_Table[i];
	patnum++;

	size = 64*patnum;
	KS_set_pattern(&ks,size);

	int max = 0;

	//pattern
	for ( i = 0; i < patnum; i++)
	{
		n = mod.Pattern_Table[i];
		fseek(fichier, 1084+(1024*n), SEEK_SET);
		fread((char*)&buffer, 1, 1024,fichier);
		ks.rows[i] = 64;

		if(ftell(fichier) > max) max = ftell(fichier);

		for (r = 0; r < 64; r++)
		{
			for ( c = 0; c < chan; c++)
			{
				cnt = (c*4)+(r*4*chan);
				b1 = buffer[cnt+0];
				b2 = buffer[cnt+1];
				b3 = buffer[cnt+2];
				b4 = buffer[cnt+3];

				note = ((b1&0x0f)<<8)+b2;
				ins = (b1&0xf0)+(b3>>4);
				eff = b3&0xf;

				line = r+(i*64);
				ks.pattern[c][line].flags = 0;

				if(note != 0 )
				{
					ks.pattern[c][line].flags |= 0x01;
					ks.pattern[c][line].note = mod_convert_note(note);
				}
				if(ins != 0 )
				{
					ks.pattern[c][line].flags |= 0x02;
					ks.pattern[c][line].instrument = ins;
				}
				if( (eff != 0 ) || (b4 != 0) )
				{

					if(eff == 0x0C)
					{
						ks.pattern[c][line].volume = b4;
						ks.pattern[c][line].flags |= 0x04;
					}else
					{
						ks.pattern[c][line].effect1 = mod_convert_effect(eff);
						ks.pattern[c][line].effect2 = b4;
						ks.pattern[c][line].flags |= 0x18;
					}

				}
			}
		}
	}

	fseek(fichier, max, SEEK_SET);

	unsigned char *data;
	for(i = 0;i < ns; i++)
	{
		KS_instruments_init(&ks,i);
		sprintf(str,"sample_%d.brr",i);

		if(option[9] > 0)
			sprintf(str,"data%d_sample%d.brr",option[9]-1,i);

		n = mod_sample[i].length;
		if(n > 0)
		{
			data = malloc(n*sizeof(char));
			fread ( data,1,n,fichier);

			int length = n;
			int slength = mod_sample[i].loopstart+mod_sample[i].looplen;

			if(slength == 0)
				slength = length;

			mod_resample(data,slength,0);

			int volume = mod_sample[i].volume;

			KS_savedata_sample(&ks,str,option,data,i,mod_sample[i].loopstart,slength, //mod_sample[i].looplen
								volume,(12*2),1,0,0);
			free(data);
		}
	}

	fclose(fichier);

	KS_write(&ks,option);

	close_brr();
	return 0;
}

void mod_sample_xor(MOD_SAMPLE *mod)
{
	mod->length = ((mod->length&0x00FF)<<8) + ((mod->length&0xFF00)>>8);
	mod->loopstart = ((mod->loopstart&0x00FF)<<8) + ((mod->loopstart&0xFF00)>>8);
	mod->looplen = ((mod->looplen&0x00FF)<<8) + ((mod->looplen&0xFF00)>>8);

	mod->length = mod->length<<1;
	mod->loopstart = mod->loopstart<<1;
	mod->looplen = mod->looplen<<1;
}

int mod_id(char *id)
{
	char str[100];
	sprintf(str,"%.4s",id);


	if(strcmp(str,"M.K.") == 0) return 4;
	if(strcmp(str,"M!K!") == 0) return 4;

	if(strcmp(str,"OKTA") == 0) return 8;
	if(strcmp(str,"OCTA") == 0) return 8;
	if(strcmp(str,"FA08") == 0) return 8;
	if(strcmp(str,"CD81") == 0) return 8;

	sprintf(str,"%.3s",id);
	if(strcmp(str,"FLT") == 0)
	{
		if( (id[3] >= '0') && (id[3] <= '9') )
			return str[3] - '0';
	}

	if( (id[0] >= '0') && (id[1] == 'C') && (id[2] == 'H') && (id[3] == 'N') )
	{
		return id[0] - '0';
	}


	if( (id[0] >= '1') && (id[1] >= '0') && (id[1] <= '9') && (id[0] <= '9') && (id[2] == 'C') && (id[3] == 'H') )
	{
		sprintf(str,"%.2s",id);
		return atoi(str);
	}


	return -1;
}

int mod_convert_effect(int effect)
{
	switch(effect)
	{
		case 0x00: //Appregio
			return KS_Appregio;
		break;

		case 0x01: //Porta up
			return KS_porta_up;
		break;

		case 0x02: //Porta down
			return KS_porta_down;
		break;

		case 0x03: //Tone porta
			return KS_Toneporta;
		break;

		case 0x04: //Vibrato
			return KS_Vibrato;
		break;

		case 0x05: //Tone porta+Volume slide
			return KS_Toneporta_Volume_slide;
		break;

		case 0x06: //Vibrato+Volume slide
			return KS_Vibrato_Volume_slide;
		break;

		case 0x07: //Tremolo
			return KS_Tremolo;
		break;

		case 0x08: //Set panning
			return KS_Panning;
		break;

		case 0x09: //Sample offset
			//return 0x0F;
		break;

		case 0x0A: //Volume slide
			return KS_Volume_slide;
		break;

		case 0x0B: //Position jump
			return KS_Position_jump;
		break;

		case 0x0C: //Set volume
		break;

		case 0x0D: //Pattern break
			return KS_Pattern_break;
		break;

		case 0x0E:
		break;

		case 0x0F: //Set tempo/BPM
			return KS_Set_tempo;
		break;


		break;
	}
	return 0xFF;
}

int mod_convert_note(int note)
{
	int i,pitch,octave,l;

	for(l = 0;l < 12;l++)
	{
		octave = 2;
		if(l == 0) pitch = 1712;
		if(l == 1) pitch = 1616;
		if(l == 2) pitch = 1525;
		if(l == 3) pitch = 1440;
		if(l == 4) pitch = 1357;
		if(l == 5) pitch = 1281;
		if(l == 6) pitch = 1209;
		if(l == 7) pitch = 1141;
		if(l == 8) pitch = 1077;
		if(l == 9) pitch = 1017;
		if(l == 10) pitch = 961;
		if(l == 11) pitch = 907;

		for(i = 0;i < 5;i++)
		{
			if( (note+5 >= pitch) && (note-5 <= pitch) )
				return (octave*12)+l;

			pitch = pitch>>1;
			octave++;
		}
	}

	return 0;
}

void mod_resample(unsigned char *data,int len,int type)
{
	int i;

	unsigned short *sdata = (void*)data;

	if(type == 1)
	{
		len = len/2;
		for(i = 0;i < len;i++)
		{
			sdata[i] = 0x8000+sdata[i];
		}

	}else
	{
		for(i = 0;i < len;i++)
		{
			data[i] = 0x80+data[i];
		}
	}
}
