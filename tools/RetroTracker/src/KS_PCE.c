#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "KS.h"


void KS_write_header_PCE(KS_FORMAT *ks,int *option,int out)
{
	char str[100];
	sprintf(str,"%s_header.sks",ks->name);

	if(option[9] > 0)
		sprintf(str,"music%d_header.sks",option[9]-1);

    FILE *file;

    if(out == 0)
		file = fopen(str,"wb");
	else
	{
		file = fopen("music.smc","rb+");
		fseek(file,0x8000*3,SEEK_SET);
	}
    if(file == NULL) return;

    KS_FORMAT_INSTRUMENTS *instruments = ks->instruments;
	int i;

	printf("%d\n",ks->Ninstruments);

	int Nchannels = 0;
	for(i = 0;i <ks->Nchannels;i++)	{
		if ((ks->chFlag & (1<<i)) != 0)
			Nchannels += 1;
	}

	printf("Nchannels : %d/%d\n",Nchannels,ks->Nchannels);

	fputc(0x00,file); //flg
    fputc(ks->chFlag,file); //kon

	printf("ticks  : %d / 65535\n",ks->ticks);
	printf("second : %d / 262\n",(ks->ticks*option[8])/8000);
	printf("size sample : %d bytes\n",ks->size_sample);
	printf("size track  : %d bytes\n",ks->size_track);


	printf("----------------\n");

	//size track
	fputc( (ks->ticks&0x00FF),file);
	fputc( (ks->ticks&0xFF00)>>8,file);

	for(i = 0;i < 32;i++)
	{
		if(i < ks->Ninstruments)
		{
			fputc(instruments[i].Relative,file);
			fputc(instruments[i].volume,file);
		}else
		{
			fputc(0x00,file);
			fputc(0x3F,file);
		}
	}

	fclose(file);



	//KS_write_PCE_asm(ks,option);
}
