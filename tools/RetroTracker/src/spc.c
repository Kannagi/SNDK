#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "KS.h"


void SPC_pitch()
{
	int i,o,n;
	double oct = 16.3516*4,frq;
	char str[100];

	int frqp;


	FILE *file = fopen("data.aspc","w");
	if(file == NULL) return;

	for(i = 0;i < 12*10;i++)
	{
		o = i/12;
		n = i%12;
		if(n == 0) oct *=2;
		frq = oct;
		frq *= pow(1.0594630943,n);

		sprintf(str,"Pitch%x:\n.dw ",o);
		if(n == 0) fputs(str,file);
		frqp = frq*0.128;
		frqp = frq;

		if(n != 11)  sprintf(str,"$%.4x,",frqp);
		else sprintf(str,"$%.4x\n",frqp);
		fputs(str,file);

		if(n == 0) printf("\n%d\n",o);
		printf("%d : %.6f %x, ",n,frq,frqp);

	}
	fclose(file);
}

void SPC_Sample(int *option)
{
	int i,len,div = option[10];
	char str[100];
	FILE *file = fopen("sfxdir.sks","wb");
	if(file == NULL) return;

	WAV wav;
	void*data;

	int length = 0x8000+(option[11]*0x800);
	int size = 0;
	int num = 0;
	int offset = length;

	for(i = 0;i < 32;i++)
	{
		sprintf(str,"Sample%d.wav",i);
		if(loadwav(str,&wav) == 1)
		{
			num++;
			data = wav.data;


			if(wav.BytePerBloc == 1)
				wav.DataSize /= 2;

			int frq = wav.frequence;

			if(div > 0)
			{
				len = wav.DataSize/div;
				frq = wav.frequence/(wav.DataSize/len);

				signed short *sdata = KS_resample16bits(data,wav.DataSize,wav.BytePerBloc);
				if(sdata != data)
				{
					data = sdata;
					wav.BytePerBloc = 1;
				}

				data = KS_resample(data,wav.DataSize,len,'b');
				wav.DataSize = len*2;
			}

			sprintf(str,"SFX%d.brr",i);
			len = savebrr(str,data,wav.DataSize,wav.BytePerBloc,0,0,0);

			sprintf(str,"SFX%d.wav",i);
			if(option[1] == 1)
				savewav( str,data,wav.DataSize,wav.BytePerBloc,frq);

			fputc( (length&0x00FF),file);
			fputc( (length&0xFF00)>>8,file);

			fputc(0x01,file);
			fputc(0x02,file);

			length += len;
			size += len;
			int tmp = frq/500;
			printf("%d : %d Hz -> %d Hz , pitch brr :%d\n",i,wav.frequence,frq ,tmp);
		}else
		{
			fputc(0x00,file);
			fputc(0x80,file);
			fputc(0x01,file);
			fputc(0x02,file);
		}


	}
	printf("size %d bytes\n",size);
	fclose(file);

	if(option[6] <= 0) return;
	KS_write_SPC_asm(num,offset);
}

void KS_write_SPC_asm(int num,int offset)
{
	char str[100];
    FILE *file = fopen("sfx_load.asm","w");
    if(file == NULL) return;

	fputs("sfx_load: ;SFX\n\n",file);

	fputs("\t;SFX\n",file);
	sprintf(str,"\tLKS_SPC_Set2 LKS_SPC_ADDR,$%x\n",offset);
	fputs(str,file);
	fputs("\tLKS_SPC_SetD BRR_SFX,BRR_SFXEOF-BRR_SFX\n\n",file);

	fputs("\t;SFXDIR\n",file);
	fputs("\tLKS_SPC_Set2 LKS_SPC_ADDR,LKS_SPC_SFXDIR\n",file);
	fputs("\tLKS_SPC_SetD BRR_SFXDIR,BRR_SFXDIREOF-BRR_SFXDIR\n\n",file);

	fputs("\trts\n",file);

	fclose(file);

	//SFXDATA-------------------------
    file = fopen("sfx_data.asm","w");
    if(file == NULL) return;

    fputs("BRR_SFX:\n",file);

	for(int i = 0;i < num;i++)
	{
		sprintf(str,".incbin \"digit/SFX%d.brr\" \n",i);
		fputs(str,file);
	}

	fputs("BRR_SFXEOF:\n",file);
	fclose(file);

	//SFXDIR--------------------------
	file = fopen("sfx_dir.asm","w");
    if(file == NULL) return;

    fputs("BRR_SFXDIR:\n",file);
	fputs(".incbin \"digit/sfxdir.sks\" \n",file);
	fputs("BRR_SFXDIREOF:\n",file);
	fclose(file);
}
