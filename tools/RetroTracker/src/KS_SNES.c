#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "KS.h"


void KS_write_header_SNES(KS_FORMAT *ks,int *option,int out)
{
	char str[100];
	sprintf(str,"%s.sks",ks->name);

    FILE *file;

	if(option[3] != 0)
	{
		file = fopen("demo.smc","rb+");
		fseek(file,0x8000*3,SEEK_SET);
	}else
		file = fopen(str,"rb+");

    if(file == NULL) return;

    KS_FORMAT_INSTRUMENTS *instruments = ks->instruments;
	int i,length = 0x3000;
	int loop_start;

	printf("Ninstruments : %d/23\n",ks->Ninstruments);

	fputc(0x00,file);
	fputc(0x02,file);
	fputc(0x00,file);
	fputc(0x02,file);
	for(i = 0;i < 23;i++)
	{
		if(i < ks->Ninstruments)
		{
			fputc( (length&0x00FF),file);
			fputc( (length&0xFF00)>>8,file);

			int padding = instruments[i].loop_start%9;

			loop_start = length + instruments[i].loop_start-padding;
			if(instruments[i].loop_start < 9) loop_start = length;


			//printf("%.4x %.4x\n",length,loop_start);

			if(instruments[i].type & 0x03)
			{
				fputc( (loop_start&0x00FF),file);
				fputc( (loop_start&0xFF00)>>8,file);
			}else
			{
				fputc(0x00,file);
				fputc(0x02,file);
			}


			length += instruments[i].length;
		}else
		{
			fputc(0x00,file);
			fputc(0x30,file);
			fputc(0x00,file);
			fputc(0x02,file);
		}

	}



	int Nchannels = 0;
	for(i = 0;i <ks->Nchannels;i++)
		Nchannels += 1<<i;

	printf("Nchannels : %d/8\n",ks->Nchannels);

	fputc(0x00,file); //flg
    fputc(ks->chFlag,file); //kon

    for(i = 0;i < 11;i++) //efb,evoll,evollr ,firc0-c7
		fputc(00,file);

	fputc(option[8],file); //ticks ms
	printf("ticks  : %d / 65535\n",ks->ticks);
	printf("second : %d / 524\n",(ks->ticks*option[8])/8000);
	printf("size sample : %d bytes (max 20480 - 32768 bytes)\n",ks->size_sample);
	printf("size track  : %d bytes (max 9216 bytes)\n",ks->size_track);

	printf("----------------\n");

	//size track
	fputc( (ks->ticks&0x00FF),file);
	fputc( (ks->ticks&0xFF00)>>8,file);

	//begin track
	for(i = 0;i <8;i++)
	{
		fputc( (ks->begin[i]&0x00FF),file);
		fputc( (ks->begin[i]&0xFF00)>>8,file);
	}

	fputc(0x00,file);
	fputc(0x7F,file);
	fputc(0xE0,file);
	fputc(0x00,file);
	fputc(0x00,file);
	for(i = 0;i < 23;i++)
	{
		if(i < ks->Ninstruments)
		{
			fputc(instruments[i].Relative,file);
			fputc(0x7F,file);
			fputc(0xE0,file);
			fputc(option[5],file);
			//fputc(0x00,file);
			fputc(instruments[i].volume,file);
		}else
		{
			fputc(0x00,file);
			fputc(0x7F,file);
			fputc(0xE0,file);
			fputc(option[5],file);
			fputc(0x3F,file);
		}

	}

	fclose(file);

}


