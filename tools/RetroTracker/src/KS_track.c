#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "KS.h"

unsigned char buffer_track[0x10000];
void KS_delay_buf(int delay,unsigned char *buf,int *ibuf);

void KS_write_track(KS_FORMAT *ks,int *option,int out)
{
	int l,k,j;
	float tick_time = option[8]>>3;

	float TIME = 2500.0f/tick_time;
	//float TIME = 2000.0f/tick_time;
	//int ticks_line = (TIME/(float)ks->BPM)*(float)ks->tempo;
	float fticks_line = ( (TIME/(float)ks->BPM)*(float)ks->tempo);
	float fticks = 0;
	//printf("%f\n",fticks_line);

	int max = ks->size_pattern,pattern = 0;

	char str[100];
	sprintf(str,"%s.sks",ks->name);

    FILE *file;
    ks->chFlag = 0;


    int begin = 0x100;

	if(option[3] != 0)
	{
		file = fopen("demo.smc","rb+");
		fseek(file,0x8000*3,SEEK_SET);
		begin = (0x8000*3) + 0x100;
	}else
		file = fopen(str,"wb");

    if(file == NULL) return;
    for(int i = 0;i < 256;i++) //header
		fputc(00,file);

    if((out&2) == 0)
	{
		if(ks->Nchannels > 8) ks->Nchannels = 8;
	}
	else
	{
		if(ks->Nchannels > 6) ks->Nchannels = 6;
	}

	fticks_line = ( (TIME/(float)ks->BPM)*(float)ks->tempo);

	printf("ticks: %f / BPM: %d / Tempo: %d\n",fticks_line,ks->BPM,ks->tempo);

	int i;
	int testsize = 0;

	for(i = 0;i < ks->Nchannels;i++)
	{
		int note = -1;
		int prevnote = -1;
		int prevnoteNOKOFF = -1;
		int index = -1;
		int volume = -1;
		int delay = 0;
		int redelay = -1;
		int olddelay = 0;
		int ticks = 0;
		int flagsp = 0;
		int row;

		int irow = 0;
		int flags = 0;
		int end = 0;
		int cmd = 0;
		int empty = 0;
		int next_pattern = 0;
		int debug_delay;

		int ibuf = 0;
		int oldibuf = 0;

		int first_v = 0;

		k = 0;
		fticks = 0;

		ks->begin[i] = ftell(file) - begin;

		fticks_line = ( (TIME/(float)ks->BPM)*(float)ks->tempo);

		for(l = 0;l < max;l++)
		{
			row = ks->rows[k];

			if(irow >= row)
			{
				//printf("%x\n",k);
				irow = 0;
				k++;
				row = ks->rows[k];
			}
			irow++;

			for(j = 0;j < ks->Nchannels;j++)
			{
				int tmp_effect = ks->pattern[j][l].effect1;
				int tmp_effect2 = ks->pattern[j][l].effect2;


				flagsp = ks->pattern[j][l].flags;

				if(flagsp&0x18)
				{
					//F Set tempo/BPM
					if(tmp_effect == 0x0F)
					{
						if(tmp_effect2 < 0x20)
							ks->tempo = tmp_effect2;
						else
							ks->BPM = tmp_effect2;

						fticks_line = ( (TIME/(float)ks->BPM)*(float)ks->tempo);
					}
					//D Pattern break
					if(tmp_effect == 0x0D)
					{
						//if(i == 0) printf("%x %x\n",l,row -(l%row) );
						l += row -(l%row)-1;
						irow = 0;
					}
					//B Position Jump
					if(tmp_effect == 0x0B)
					{
						if(tmp_effect2 > k)
						{

							while(tmp_effect2 > k)
							{
								row = ks->rows[k];

								if(irow >= row)
								{
									irow = 0;
									k++;
									row = ks->rows[k];
								}
								irow++;
								l++;
							}

							j = 0;
							continue;


						}else
						{
							if(i == 0)
								printf("Not supported Jump row %x line $%x (Effect B%x)\n",k,irow-1,tmp_effect2);

							end = 1;
						}
					}
				}
			}
			if(l >= max)
				break;

			if(end == 1)
			{
				break;
			}

			flags = ks->pattern[i][l].flags;
			pattern = 0;

			//note
			if(flags&0x01)
			{
				if(prevnoteNOKOFF != ks->pattern[i][l].note)
					pattern |= 0x1;
				else
					pattern |= 0x2;

				note = ks->pattern[i][l].note;
				if (note != 0)
					prevnoteNOKOFF = note;
				else if (prevnote == 0)
					pattern &= 0xFC;
				prevnote = note;
			}

			//instrument
			if(flags&0x02)
			{
				if(index != ks->pattern[i][l].instrument-1)
					pattern |= 0x8;

				index = ks->pattern[i][l].instrument-1;
			}

			//volume
			if(flags&0x04)
			{
				if(volume != ks->pattern[i][l].volume)
					pattern |= 0x4;
				volume = ks->pattern[i][l].volume;
			}



			if(pattern != 0)
			{
				empty = 1;
				pattern &= 5;
				int tmp = delay;
				olddelay = ticks;
				int bnote = note;

				if(tmp == redelay)
				{
					debug_delay = redelay;
					buffer_track[oldibuf] |= 0x40;

				}else
				{
					KS_delay_buf(tmp,buffer_track,&ibuf);
				}
				redelay = tmp;
				oldibuf = ibuf;


				if (first_v == 0)
				{
					if(pattern&0x04)
					{

					}else
					{
						volume = ks->instruments[index].volume;
						pattern |= 0x04;
					}
				}
				first_v = 1;


				if(bnote != 0)
				{

					tmp = index+1;
					tmp = (tmp&0x1F) | (pattern<<5);


					buffer_track[ibuf] = tmp;
					ibuf++;

					if(pattern&0x01)
					{
						buffer_track[ibuf] = note;
						ibuf++;
					}

					if(pattern&0x04)
					{
						if (volume >= 64)
							buffer_track[ibuf] = 127;
						else
							buffer_track[ibuf] = volume<<1;
						ibuf++;
					}

				}else
				{
					buffer_track[ibuf] = 0;
					ibuf++;
				}

			}

			fticks += fticks_line;
			ticks = fticks;
			delay = (ticks-olddelay);
		}

		if(empty == 1)
		{
			ks->chFlag |= 1<<i;

			int tmp = delay;
			if(delay > 2) tmp -= 2;

			KS_delay_buf(tmp,buffer_track,&ibuf);

			buffer_track[ibuf] = 0;
			ibuf++;

			buffer_track[ibuf] = 0xFF;
			ibuf++;

			buffer_track[ibuf] = 0xFF;
			ibuf++;
			/*
			KS_delay_fputc(tmp,file);
			fputc(0,file);
			fputc(0xFF,file);
			fputc(0xFF,file);
			*/

			fwrite(buffer_track,1,ibuf,file);
		}


	}


	ks->ticks = fticks;
	ks->size_track = ftell(file) - begin;

    fclose(file);
}

