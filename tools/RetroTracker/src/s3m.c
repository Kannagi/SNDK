
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "KS.h"
#include "s3m.h"

int S3M_Load(char *name,int *option)
{
	int size = 0,i,n = 0,chan = 4,c,line,l;
	KS_FORMAT ks;
	char str[100];
	unsigned char what,b1,b2,b3,b4,b5;
	unsigned char *data;
	FILE *fichier;
    fichier = fopen(name,"rb");

    if(fichier == NULL) return 1;

	int info = option[2];
    S3M_HEADER s3m;
    S3M_INSTRUMENT s3m_instrument;

	fread ( (char*)&s3m,1,96,fichier);

	sprintf(str,"%.4s",s3m.sig2);
	if(strcmp(str,"SCRM") != 0)
	{
		fclose(fichier);
		return 1;
	}

	printf("S3M file : %s\n",s3m.name);

	if(info != 0) s3m_print(s3m);

	for (chan = 0; chan < 32; chan++)
		if (s3m.channelSettings[chan] == 255)
			break;

	//chan++;



	KS_set_header(&ks,s3m.name,chan,s3m.instrumentCount,s3m.initialSpeed,s3m.initialTempo);
	init_brr(ks.name,option[3]);
	size = s3m.patternPtrCount*64;
	KS_set_pattern(&ks,size);

	s3m.orderList = malloc(s3m.orderCount*sizeof(uint8_t));
	s3m.ptrInstruments = malloc(s3m.instrumentCount*sizeof(uint16_t));
	s3m.ptrPatterns = malloc(s3m.patternPtrCount*sizeof(uint16_t));


	fread ( (char*)s3m.orderList ,1,s3m.orderCount,fichier);
	fread ( (char*)s3m.ptrInstruments ,1,s3m.instrumentCount*2,fichier);
	fread ( (char*)s3m.ptrPatterns,1,s3m.patternPtrCount*2,fichier);

	S3M_XOR_HEADER(&s3m);

	int total = 0;
	for (i = 0; i < s3m.instrumentCount; i++)
	{
		fseek(fichier, s3m.ptrInstruments[i], SEEK_SET);
		fread ( (char*)&s3m_instrument,1,1,fichier);

		KS_instruments_init(&ks,i);
		if (s3m_instrument.type == 1)
		{
			fread ( (char*)&s3m_instrument.filename,1,13,fichier);
			fread ( (char*)&s3m_instrument.ptrDataL,1,66,fichier);

			if(info != 0) s3m_print_instrument(s3m_instrument,i);

			n = (s3m_instrument.ptrDataL<<4)+(s3m_instrument.ptrDataH<<20);
			fseek(fichier, n, SEEK_SET);
			n = s3m_instrument.length;
			data = malloc(n*sizeof(char));
			fread ( data,1,n,fichier);

			sprintf(str,"sample_%d.brr",i);

			if(option[9] > 0)
				sprintf(str,"data%d_sample%d.brr",option[9]-1,i);

			int bitssize = (s3m_instrument.flags&0x04)>>2;
			int slength = n;

			int relative = s3m_relative(s3m_instrument.c2spd);

			int length = s3m_instrument.loopStart+s3m_instrument.loopEnd;

			if(length == 0)
				length = length;

			s3m_resample(data,slength,bitssize);

			int volume = s3m_instrument.volume*4;
			if (volume > 255)
				volume = 255;
			KS_savedata_sample(&ks,str,option,data,i,s3m_instrument.loopStart,slength,//s3m_instrument.loopEnd,
								volume,relative+(12*2),s3m_instrument.flags&1,bitssize,s3m_instrument.c2spd);


			total += size;

			free(data);


		}
	}


	int len;
	line = 0;

	int offset;

	for (i = 0; i < s3m.patternPtrCount; i++)
	{
		n = s3m.orderList[i];
		offset = s3m.ptrPatterns[n];

		fseek(fichier, offset,SEEK_SET);
		ks.rows[i] = 0x40;

		fread ( (char*)&len,1,2,fichier);
		len -=2;

		for(l = 0; l < len;l++)
		{
			what = fgetc(fichier);

			if(what == 0x00)
			{
				line++;
				continue;
			}

			c = what&0x1F;
			if(what&0x20)
			{
				b1 = fgetc(fichier);
				b2 = fgetc(fichier);

				int octave = (b1&0xF0)>>4;
				int note = (octave * 12) + (b1&0x0F);

				if(b1 >= 0xC2) note = 0;

				ks.pattern[c][line].note = note;
				ks.pattern[c][line].instrument = b2;
				ks.pattern[c][line].flags |= 0x03;

				l++;
				l++;
			}

			if(what&0x40)
			{
				b3 = fgetc(fichier);

				ks.pattern[c][line].volume = b3;
				ks.pattern[c][line].flags |= 0x04;

				l++;
			}

			if(what&0x80)
			{
				b4 = fgetc(fichier);
				b5 = fgetc(fichier);
				l++;
				l++;

				ks.pattern[c][line].effect1 = s3m_convert_effect(b4);
				ks.pattern[c][line].effect2 = b5;
				ks.pattern[c][line].flags |= 0x18;
			}

		}


	}

	fclose(fichier);

	KS_write(&ks,option);
	close_brr();
	return 0;
}


void s3m_resample(unsigned char *data,int len,int type)
{
	int i;

	unsigned short *sdata = (void*)data;
	int tmp;

	if(type == 1)
	{
		len = len/2;
		for(i = 0;i < len;i++)
		{
			tmp = sdata[i];
			tmp = 0xFFFF-(tmp-0x8000);
			sdata[i] = tmp;
		}
	}else
	{
		for(i = 0;i < len;i++)
		{
			data[i] = 0xFF-data[i];
		}
	}
}


int s3m_convert_effect(int effect)
{


	switch(effect)
	{
		case 0x00:
			//return 0x00;
		break;

		case 0x01: // Set speed (ticks)
			return KS_Set_tempo;
		break;

		case 0x02: // Jump to order
			return KS_Position_jump;
		break;

		case 0x03: // Pattern break
			return KS_Pattern_break;
		break;

		case 0x04: // volume slide
			return KS_Volume_slide;
		break;

		case 0x05: //porta down
			return KS_porta_down;
		break;

		case 0x06: //porta up
			return KS_porta_up;
		break;

		case 0x07: // tone porta
			return KS_Toneporta;
		break;

		case 0x08: //vibrato
			return KS_Vibrato;
		break;

		case 0x09: //tremor
			//return 0x0F;
		break;

		case 0x0A: //arpeggio
			return KS_Appregio;
		break;

		case 0x0B: //vibrato & volslide
			return KS_Vibrato_Volume_slide;
		break;

		case 0x0C: // tone porta & volslide
			return KS_Toneporta_Volume_slide;
		break;


		case 0x0F: // set sample offset
		break;

		// retrig
		case 0x11:

		break;

		// tremolo
		case 0x12:
			return KS_Tremolo;
		break;

		break;
	}
	return 0xFF;
}

int s3m_relative(int spd)
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
			return i-97;

	}

	return 0;
}

void S3M_XOR_HEADER(S3M_HEADER *s3m)
{
	int i = 0;

	for (i = 0; i < s3m->instrumentCount; i++)
		s3m->ptrInstruments[i] = s3m->ptrInstruments[i]<<4;

	for (i = 0; i < s3m->patternPtrCount; i++)
		s3m->ptrPatterns[i] = s3m->ptrPatterns[i]<<4;
}
