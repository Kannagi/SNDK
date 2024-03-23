#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "KS.h"

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
	sprintf(str,"%s_track.sks",ks->name);
	if(option[9] > 0)
		sprintf(str,"music%d_track.sks",option[9]-1);

    FILE *file;

    int begin = 0;

    out = out&1;
    if(out == 0)
		file = fopen(str,"wb");
	else
	{
		file = fopen("music.smc","rb+");
		fseek(file,(0x8000*3)+320,SEEK_SET);
		begin = (0x8000*3)+320;
	}

    if(file == NULL) return;

    if((out&2) == 0)
	{
		if(ks->Nchannels > 8) ks->Nchannels = 8;
	}
	else
	{
		if(ks->Nchannels > 6) ks->Nchannels = 6;
	}

	fticks_line = ( (TIME/(float)ks->BPM)*(float)ks->tempo);

	printf("ticks %f / %d %d\n",fticks_line,ks->BPM,ks->tempo);

	int row;
	int irow = 0;
	k = 0;
	int flags = 0,end = 0;
	int note[8];
	int index[8];
	int volume[8];
	//int effect[8];

	for(l = 0;l < 8;l++)
	{
		note[l] = -1;
		index[l] = -1;
		volume[l] = -1;
		//effect[l] = -1;
	}

	fticks = 0;
	int cmd = 0;

	float fdelay = 0;
	float oldfdelay = 0;

	for(l = 0;l < max;l++)
	{
		//------------
		row = ks->rows[k];

		if(irow >= row)
		{
			//printf("%x\n",k);
			irow = 0;
			k++;
			row = ks->rows[k];
		}
		irow++;
		//------------




		int jmpbreak = 0;
		cmd = 0;
		for(j = 0;j < ks->Nchannels;j++)
		{
			int tmp_effect = ks->pattern[j][l].effect1;
			int tmp_effect2 = ks->pattern[j][l].effect2;

			flags = ks->pattern[j][l].flags;

			//Effect A
			if(flags&0x18)
			{
				//F Set tempo/BPM
				if(tmp_effect == 0x0F)
				{
					fticks_line = ( (TIME/(float)ks->BPM)*(float)ks->pattern[j][l].effect2);
				}
				//D Pattern break
				if(tmp_effect == 0x0D)
				{
					jmpbreak = 1;
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
						printf("Not supported Jump row %x line $%x (Effect B%x)\n",k,irow-1,tmp_effect2);

						end = 1;
					}
				}
			}
			if(l >= max)
				break;

			if(end == 1)
			{
				l = max;
				break;
			}

			flags = ks->pattern[j][l].flags;
			pattern = 0;

			//note
			if(flags&0x01)
			{
				if(note[j] != ks->pattern[j][l].note)
					pattern |= 0x1;
				else
					pattern |= 0x2;

				note[j] = ks->pattern[j][l].note;
			}

			//instrument
			if(flags&0x02)
			{
				if(index[j] != ks->pattern[j][l].instrument-1)
					pattern |= 0x4;

				index[j] = ks->pattern[j][l].instrument-1;
			}

			//volume
			if(flags&0x04)
			{
				if(volume[j] != ks->pattern[j][l].volume)
					pattern |= 0x8;
				volume[j] = ks->pattern[j][l].volume;
			}

			//Effect B
			if(flags&0x18)
			{
				tmp_effect = ks->pattern[j][l].effect1;
				tmp_effect2 = ks->pattern[j][l].effect2;

				//pattern |= 0x3;
			}


			if( (cmd == 0) && (pattern != 0) )
			{
				int tmp = fdelay;
				if(tmp != 0)
				KS_delay_fputc(tmp,file);
				oldfdelay = fticks;
			}


			if(pattern != 0)
			{
				int tmp = j<<4;
				fputc(tmp+pattern,file);

				if(pattern&0x03)
				{
					if(pattern&0x01)
						fputc(note[j],file);

					//if(pattern&0x03) //Effect+note
				}
				if(pattern&0x04) fputc(index[j],file);
				if(pattern&0x08) fputc(volume[j],file);
				cmd++;

				if(j == 5)
				{
					//KS_debug_note(note[j]);
					//printf(" %x %x %x\n",note[j],index[j],volume[j]);
				}
			}

		}

		if(jmpbreak != 0)
		{
			//printf("%x %x / %x %x\n",l,row -(l%row),k,irow );
			l += row -(l%row)-1;
			irow = 0;
			k++;
		}

		fticks += fticks_line;
		fdelay = (fticks-oldfdelay);


	}

	fputc(0xFF,file);
	fputc(0xFF,file);

	ks->ticks = fticks;
	ks->size_track = ftell(file) - begin;

    fclose(file);
}

