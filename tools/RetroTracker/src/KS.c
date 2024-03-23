#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "KS.h"

void KS_write(KS_FORMAT *ks,int *option)
{

	if(option[12] == 0)
		KS_write_SNES(ks,option);

	if(option[12] == 1)
		KS_write_PCE(ks,option);
}

void KS_write_PCE(KS_FORMAT *ks,int *option)
{
	if(option[5] == 0)
	{
		KS_write_track(ks,option,2);
		KS_write_header_PCE(ks,option,0);
	}else
	{
		KS_write_track(ks,option,3);
		KS_write_header_PCE(ks,option,1);
	}
}


void KS_write_SNES(KS_FORMAT *ks,int *option)
{
	if(option[5] == 0)
	{
		KS_write_track(ks,option,0);
		KS_write_header_SNES(ks,option,0);
	}else
	{
		KS_write_track(ks,option,1);
		KS_write_header_SNES(ks,option,1);
	}
}

void KS_instruments_init(KS_FORMAT *ks,int i)
{
	ks->instruments[i].volume = 0;
	ks->instruments[i].Relative = 0;
	ks->instruments[i].type = 0;
	ks->instruments[i].length = 0;
	ks->instruments[i].loop_start = 0;
	ks->instruments[i].enable = 0;
}

void KS_savedata_sample(KS_FORMAT *ks,char *str,int *option,unsigned char *data,int i,int loop_start,int length,
						int volume,int relative,int type,int bitssize,int frq)
{
	int compress = 0;
	float ratio = (float)loop_start/(float)length;
	int slength_out = length;

	if(option[4] != 0)
	{
		int copy_slength = length;
		int mask = 0xFE000;
		if(option[4] == 2) mask = 0xFF000;

		while(copy_slength&mask)
		{
			copy_slength = copy_slength>>1;
			if(compress == 0) compress = 2;
			else compress = compress<<1;
			relative -= 12;
		}

		if(compress > 0)
			slength_out =  KS_compress(data,length,bitssize ,compress);
	}

	static int temp_length = 0;

	int brrlength = 0;

	if(option[12] == 0)
	{
		if(option[5] != 0)
			brrlength = savebrr( str,data,slength_out,bitssize,0,0,temp_length+1);
		else
			brrlength = savebrr( str,data,slength_out,bitssize,0,0,0);
	}

	if(option[12] == 1)
	{
		if(option[5] != 0)
			brrlength = savepcm5b( str,data,slength_out,bitssize,0,0,temp_length+1);
		else
			brrlength = savepcm5b( str,data,slength_out,bitssize,0,loop_start,0);

		//printf("%d\n",brrlength);
	}


	temp_length += brrlength;
	ks->size_sample = temp_length;
	if(temp_length >= 0x8000)
	{
		printf("overflow sample (%d), use -compress or -compress2 ! \n",temp_length);
		return;
	}

	ks->instruments[i].volume = volume;
	ks->instruments[i].Relative = relative;
	ks->instruments[i].type = type;
	ks->instruments[i].length = brrlength;
	ks->instruments[i].loop_start = ratio*brrlength;
	ks->instruments[i].enable = 1;

	sprintf(str,"%d_%s.wav",i,ks->name);
	if(frq == 0)
		frq = KS_pitch(120-12+relative);

	if(option[1] == 1)
		savewav( str,data,slength_out,bitssize,frq);
}

void KS_set_header(KS_FORMAT *ks,char *name,unsigned char Nchannels,unsigned char Ninstruments,unsigned char tempo,unsigned char BPM)
{
	strcpy(ks->name,name);

	ks->Nchannels = Nchannels;
	ks->Ninstruments = Ninstruments;

	ks->tempo = tempo;
	ks->BPM = BPM;

	ks->instruments = malloc(Ninstruments*sizeof(KS_FORMAT_INSTRUMENTS));
}


void KS_set_pattern(KS_FORMAT *ks,int size)
{
	ks->size_pattern = size;

	ks->pattern = malloc(ks->Nchannels * sizeof(KS_FORMAT_PATTERN*));

	int i,l;
	for(i = 0;i < ks->Nchannels;i++)
	{
		ks->pattern[i] = malloc(size * sizeof(KS_FORMAT_PATTERN));
		for(l = 0;l < size;l++)
		{
			ks->pattern[i][l].flags = 0;
			ks->pattern[i][l].note = -1;
			ks->pattern[i][l].instrument = -1;
			ks->pattern[i][l].volume = -1;
			ks->pattern[i][l].effect1 = -1;
			ks->pattern[i][l].effect2 = -1;
		}
	}
}

void KS_delay_fputc(int delay,FILE *out)
{
	if( delay >= 0x40)
	{
		fputc( ((delay&0x3F00)>>8)+0xC0,out);
		fputc(delay&0x00FF,out);
	}else
	{
		fputc(delay+0x80,out);
	}
}
/*
void KS_delay_fputc(int delay,FILE *out)
{
	if( delay >= 0x80)
	{
		fputc( ((delay&0x7F00)>>8) + 0x80,out);
		fputc(delay&0x00FF,out);
	}else
	{
		fputc(delay,out);
	}
}
*/
int KS_pitch(int notes)
{
	double frq;
	frq = 16.3516*pow(2,notes/12); //it : 16,5625 , xm : 16,34375
	frq *= pow(1.0594630943,notes%12);

	return frq;
}
