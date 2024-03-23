#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "KS.h"


void KS_write_header_SNES(KS_FORMAT *ks,int *option,int out)
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
	int i,length = 0x4000;
	int loop_start;

	printf("Ninstruments : %d/32\n",ks->Ninstruments);

	for(i = 0;i < 32;i++)
	{
		if(i < ks->Ninstruments)
		{
			fputc( (length&0x00FF),file);
			fputc( (length&0xFF00)>>8,file);

			int padding = instruments[i].loop_start%9;

			loop_start = length + instruments[i].loop_start-padding;
			if(instruments[i].loop_start < 9) loop_start = length;

			if(instruments[i].type & 0x03)
			{
				fputc( (loop_start&0x00FF),file);
				fputc( (loop_start&0xFF00)>>8,file);
			}else
			{
				fputc(0x01,file);
				fputc(0x02,file);
			}


			length += instruments[i].length;
		}else
		{
			fputc(0x00,file);
			fputc(0x40,file);
			fputc(0x01,file);
			fputc(0x02,file);
		}

	}



	int Nchannels = 0;
	for(i = 0;i <ks->Nchannels;i++)
		Nchannels += 1<<i;

	printf("Nchannels : %d/8\n",ks->Nchannels);

	fputc(0x00,file); //flg
    fputc(Nchannels,file); //kon

    for(i = 0;i < 11;i++) //efb,evoll,evollr ,firc0-c7
		fputc(00,file);

	fputc(option[8],file); //ticks ms
	printf("ticks  : %d / 65535\n",ks->ticks);
	printf("second : %d / 262\n",(ks->ticks*option[8])/8000);
	printf("size sample : %d bytes (max 16KB-48KB)\n",ks->size_sample);
	printf("size track  : %d bytes (max 11452 bytes)\n",ks->size_track);

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


	for(i = 0;i < 32;i++)
	{
		if(i < ks->Ninstruments)
		{
			fputc(instruments[i].Relative,file);
			fputc(0x7F,file);
			fputc(0xE0,file);
			fputc(0x3F,file);
			fputc(instruments[i].volume,file);
		}else
		{
			fputc(0x00,file);
			fputc(0x7F,file);
			fputc(0xE0,file);
			fputc(0x3F,file);
			fputc(0x3F,file);
		}

	}

	fclose(file);



	KS_write_SNES_asm(ks,option);
}

void KS_write_SNES_asm(KS_FORMAT *ks,int *option)
{
	if(option[9] <= 0) return;
	int num = option[9]-1;
	char str[100];
	sprintf(str,"music_load%d.asm",num);
    FILE *file = fopen(str,"w");
    if(file == NULL) return;

    sprintf(str,"music_load%d: ;%s\n\n",num,ks->name);
	fputs(str,file);

	fputs("\t;sample\n",file);
	fputs("\tLKS_SPC_Set2 LKS_SPC_ADDR,LKS_SPC_SAMPLE\n",file);
	sprintf(str,"\tLKS_SPC_SetD BRR_Sample%d,BRR_Sample%dEOF-BRR_Sample%d\n\n",num,num,num);
	fputs(str,file);

	fputs("\t;track\n",file);
	fputs("\tLKS_SPC_Set2 LKS_SPC_ADDR,LKS_SPC_SMXDIR\n",file);
	sprintf(str,"\tLKS_SPC_SetD music%d,music%dEOF-music%d\n\n",num,num,num);
	fputs(str,file);

	fputs("\trts\n",file);

	fclose(file);

	//---------------------------------
	sprintf(str,"music_data%d.asm",num);
    file = fopen(str,"w");
    if(file == NULL) return;

    sprintf(str,"BRR_Sample%d: ;%s\n",num,ks->name);
	fputs(str,file);

	for(int i = 0;i < ks->Ninstruments;i++)
	{
		if(ks->instruments[i].enable == 1)
		{
			sprintf(str,".incbin \"music/data%d_sample%d.brr\" \n",num,i);
			fputs(str,file);
		}

	}

	sprintf(str,"BRR_Sample%dEOF:\n",num);
	fputs(str,file);
	fclose(file);


	sprintf(str,"music_track%d.asm",num);
    file = fopen(str,"w");
    if(file == NULL) return;
	sprintf(str,"music%d: ;%s\n",num,ks->name);
	fputs(str,file);

	sprintf(str,".incbin \"music/music%d_header.sks\" \n",num);
	fputs(str,file);
	sprintf(str,".incbin \"music/music%d_track.sks\" \n",num);
	fputs(str,file);

	sprintf(str,"music%dEOF:\n",num);
	fputs(str,file);


	fclose(file);
}


