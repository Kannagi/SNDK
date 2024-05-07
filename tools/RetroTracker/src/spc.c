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
	int i,len,div = 1;
	char str[100];

	WAV wav;
	void*data;

	int size = 0;
	int num = 0;
	option[10]--;
	int offset = 0x8000 + (option[10]*0x800);

	printf("offset %x\n",offset);

	FILE *file = fopen("SFX.dir","wb");
	if(file == NULL) return;

	init_brr("SFX",0);

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

			fputc(offset,file);
			fputc(offset>>8,file);
			fputc(0x02,file);
			fputc(0x02,file);
			offset += len;
			size += len;

			int tmp = frq/500;
			printf("%d : %d Hz, pitch : %x ,size : %x\n",i,wav.frequence ,tmp*0x40, len);
		}


	}

	fclose(file);
	close_brr();

	printf("size %d bytes / max 20416 - 32704 bytes\n",size);
}


