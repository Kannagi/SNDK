#include <stdio.h>
#include <stdlib.h>

#include "vgm.h"


int VGM_data_pcm(int i,unsigned char *buffer,FILE *file,int wr)
{
	int size;

	i+=2;
	size = buffer[i] + (buffer[i+1]<<8)  + (buffer[i+2]<<16)  + (buffer[i+3]<<24);

	//printf("PCM data ,type : %x , size : %d\n",buffer[i-1],size);

	if(wr >= 1)
	{
		printf("PCM data ,type : %x , size : %d\n",buffer[i-1],size);
		fwrite(&buffer[6], sizeof(char), size, file);
	}


	return size+6;
}


unsigned char buffer_pcm[0x8000];

int VGM_data_pcm_ricoh(int i,unsigned char *buffer,VGM *vgm,int wr,FILE *file)
{
	int size,size_pcm,begin = 0;

	i+=2;
	size = buffer[i] + (buffer[i+1]<<8)  + (buffer[i+2]<<16)  + (buffer[i+3]<<24);

	int offset = 0x4000,tsize = 0,len,isample = 1,n = 0;
	vgm->inst[0] = 0;

	size_pcm = 0;
	printf("PCM data ,type : %x , size : %d\n",buffer[i-1],size);
	for(int l = 0; l < size;l++)
	{
		unsigned char tmp = buffer[6+l];

		if( (tmp != 0xFF) && (tmp != 0x00) && (begin == 1) )
		{
			begin = 0;
		}

		if( (tmp != 0xFF) && (begin == 0) )
		{
			if(tmp&0x80)
				buffer_pcm[tsize] = tmp;
			else
				buffer_pcm[tsize] = 0x80-tmp;



			size_pcm++;
			tsize++;
		}
		else
		{
			if(tsize > 0)
			{
				//    savebrr( str    ,data      ,sleng,s,0,0,2);
				len = savebrr("SP.brr",buffer_pcm,tsize,0,0,0,2);
				fputc(offset,file);
				fputc(offset>>8,file);
				fputc(offset,file);
				fputc(offset>>8,file);
				offset += len;
				tsize = 0;

				vgm->inst[l>>8] = isample;
				isample++;
				n++;

				//printf("offset: %d § %x\n",l>>8,l);
			}
			begin = 1;
		}
	}

	if(tsize > 0)
	{
		len = savebrr("SP.brr",buffer_pcm,tsize,0,0,0,2);
		fputc(offset,file);
		fputc(offset>>8,file);
		fputc(offset,file);
		fputc(offset>>8,file);
		offset += len;
		tsize = 0;
		n++;
	}

	n = 32 - n;
	for(i = 0;i < n;i++) //padding
	{
		fputc(2,file);
		fputc(2,file);
		fputc(2,file);
		fputc(2,file);
	}


	//Header :
	for(i = 0;i < 16;i++) //flg,non,efb,eon,evoll,evollr ,firc0-c7
		fputc(vgm->spc700[i],file);

	fputc(0x01,file); //size
	fputc(0x00,file);

	for(i = 0;i < 14;i++) //padding
		fputc(0,file);

	for(i = 0;i < 32;i++) //ADSR
	{
		fputc(vgm->adsr1[i],file);
		fputc(vgm->adsr2[i],file);
		fputc(vgm->gain[i] ,file);
	}



	return size+6;
}
