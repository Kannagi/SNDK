#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "KS.h"
#include "xm.h"

int XM_Load(char *name,int *option)
{
	int i,l,n;
	char str[100];
	unsigned char *data;
	FILE *fichier;
    fichier = fopen(name,"rb");

    if(fichier == NULL) return 1;


    KS_FORMAT ks;

    XM_HEADER xm;
	XM_SAMPLE *xm_sample;

    fread ( (char*)&xm,1,64,fichier);

	xm.ID_text[16] = 0;
    if(strcmp(xm.ID_text,"Extended Module:") != 0)
    {
    	fclose(fichier);
    	return 1;
    }
    printf("XM file : %.20s\n",xm.Module_name);


	fread ( ( (char*)&xm )+64,1,xm.Header_size-4,fichier);
	int info = option[2];
	if(info != 0) xm_print(xm);

	//patterns
	xm.patterns = malloc(xm.Npatterns * sizeof(XM_PATTERNS*));
	for(i = 0;i < xm.Npatterns;i++)
	{
		xm.patterns[i] = malloc(sizeof(XM_PATTERNS));
		fread ( (char*)xm.patterns[i] ,1,5,fichier);
		fread ( (char*)&xm.patterns[i]->Nrowspattern,1,4,fichier);

		if(xm.patterns[i]->size > 0)
		{
			xm.patterns[i]->data = malloc(xm.patterns[i]->size);
			fread ( (char*)xm.patterns[i]->data ,1,xm.patterns[i]->size,fichier);
		}else
		{
			xm.patterns[i]->data = NULL;
		}

		if(info != 0) xm_print_patterns(xm,i);
	}

	int size = 0;
	for(l = 0;l < xm.Song_length;l++)
	{
		i = xm.Pattern_table[l];
		size += xm.patterns[i]->Nrowspattern;
	}

	//instruments
	output_filename(name,str);

	KS_set_header(&ks,str,xm.Nchannels,xm.Ninstruments,xm.tempo,xm.BPM);
	init_brr(ks.name,option[3]);

	xm.instruments = malloc(xm.Ninstruments * sizeof(XM_INSTRUMENTS*));
	if(xm.instruments == NULL) return 1;

	int slength;

	for(i = 0;i < xm.Ninstruments;i++)
	{
		xm.instruments[i] = malloc(sizeof(XM_INSTRUMENTS));
		if(xm.instruments[i] == NULL) return 1;

		fread ( xm.instruments[i] ,1,27,fichier);
		fread ( &xm.instruments[i]->Nsamples ,1,2,fichier);
		if(info != 0) xm_print_instruments(xm,i);

		KS_instruments_init(&ks,i);

		if(xm.instruments[i]->Nsamples > 0)
		{
			fread ( (char*)&xm.instruments[i]->ext ,1,214,fichier);

			fseek (fichier , xm.instruments[i]->size-243 , SEEK_CUR);

			n = xm.instruments[i]->Nsamples;

			xm_sample = malloc(n * sizeof(XM_SAMPLE));
			if(xm_sample == NULL) return 1;

			for(l = 0;l < n;l++)
			{
				fread ( &xm_sample[l],1,40,fichier);
				if(info != 0) xm_print_samples(xm_sample[l],l+1);
			}

			for(l = 0;l < n;l++)
			{
				slength = xm_sample[l].length;
				ks.instruments[i].enable = 0;
				if(slength != 0)
				{
					int bitssize = (xm_sample[l].type&0x10)>>4;
					int length = xm_sample[l].loop_length+xm_sample[l].loop_start;

					if(length == 0)
						length = slength;

					data = malloc(slength*sizeof(char));
					if(data == NULL) return 1;
					fread ( data,1,slength,fichier);

					sprintf(str,"%s_sample%d.brr",ks.name,i);

					if(option[9] > 0)
						sprintf(str,"data%d_sample%d.brr",option[9]-1,i);

					if(l == 0)
					{
						xm_resample(data,slength,bitssize);

						int volume = xm_sample[l].Volume*4;
						if (volume > 255)
							volume = 255;
						KS_savedata_sample(&ks,str,option,data,i,xm_sample[l].loop_start,length,//xm_sample[l].loop_length,
								volume,xm_sample[l].Relative+(12*2),xm_sample[l].type,bitssize,0);
					}
					//fseek (fichier , xm_sample[l].length , SEEK_CUR);

					free(data);
				}

			}

			free(xm_sample);
		}else
		{
			fseek (fichier , xm.instruments[i]->size-29 , SEEK_CUR);
		}
	}

	fclose(fichier);

	KS_set_pattern(&ks,size);

	//write track
	int pitch = -1,volume = -1,index = -1,stdeffet1 = -1,stdeffet2 =-1,val,k;

	int j = 0,opitch;

	int total = 0;
	int ik = 0;

	ks.nrows = xm.Song_length;
	for(k = 0;k < xm.Song_length;k++)
	{
		i = xm.Pattern_table[k];
		total += xm.patterns[i]->size;
		j = 0;
		ks.rows[k] = xm.patterns[i]->Nrowspattern;

		for(l = 0;l < xm.patterns[i]->size;l++)
		{
			val = xm.patterns[i]->data[l]&0xFF;

			if(val < 0x80)
			{
				pitch = val-1;
				l++;
				index = xm.patterns[i]->data[l] ;
				l++;
				volume = xm.patterns[i]->data[l] ;
				l++;
				stdeffet1 = xm.patterns[i]->data[l];
				l++;
				stdeffet2 = xm.patterns[i]->data[l];
				ks.pattern[j][ik].flags = 0x1F;
				//if(j == 2) printf("%x (%x %x),",volume,ik/0x40,ik%0x40);

				if(val == 97)
				{
					pitch = 0x00;
					//ks.pattern[j][ik].flags = 0x01;
				}

				//if(j == 2) printf("%x,",volume);

				if( (volume >= 0x10) && (volume <= 0x50) )
				{
					volume -= 0x10;
				}else
				{
					ks.pattern[j][ik].flags -=4;
				}

			}else
			{
				ks.pattern[j][ik].flags = 0;
				volume = 0x3F;

				if( (val&0x01) == 0x01)
				{
					l++;
					opitch = xm.patterns[i]->data[l]&0xFF;
					pitch = opitch-1;

					if(opitch == 97)
						pitch = 0x00;

					ks.pattern[j][ik].flags |= 0x01;

				}
				if( (val&0x02) == 0x02)
				{
					l++;
					index = xm.patterns[i]->data[l] ;
					ks.pattern[j][ik].flags |= 0x02;

				}
				if( (val&0x04) == 0x04)
				{
					l++;
					volume = (xm.patterns[i]->data[l]);

					if( (volume >= 0x10) && (volume <= 0x50) )
					{
						volume -= 0x10;
						ks.pattern[j][ik].flags |= 0x04;
					}else
					{
						//printf("%x,",volume);
						val -=4;
					}
				}
				if( (val&0x08) == 0x08)
				{
					l++;
					stdeffet1 = (xm.patterns[i]->data[l]);
					ks.pattern[j][ik].flags |= 0x08;
				}
				if( (val&0x10) == 0x10)
				{
					l++;
					stdeffet2 = xm.patterns[i]->data[l];
					ks.pattern[j][ik].flags |= 0x10;
				}




			}

			if(stdeffet1 == 0x0C)
			{
				volume = stdeffet2;
				ks.pattern[j][ik].flags |= 0x04;
				ks.pattern[j][ik].flags = ks.pattern[j][ik].flags&0x7;
				stdeffet1 = 0xFF;
			}
			ks.pattern[j][ik].note = pitch;
			ks.pattern[j][ik].instrument = index;
			ks.pattern[j][ik].volume = volume;
			ks.pattern[j][ik].effect1 = xm_convert_effect(stdeffet1);
			ks.pattern[j][ik].effect2 = stdeffet2;

			j++;
			if(j >= xm.Nchannels)
			{
				j = 0;
				ik++;
			}
		}
	}

	if(info != 0)
		printf("pattern data total : %d $%x %d \n",total,total,ik);

	KS_write(&ks,option);

	close_brr();

    return 0;
}

int xm_convert_effect(int effect)
{


	switch(effect)
	{
		case 0x00: //Appregio
			return KS_Appregio;
		break;

		case 0x01: //Porta up
			return KS_porta_up;
		break;

		case 0x02: //Porta down
			return KS_porta_down;
		break;

		case 0x03: //Tone porta
			return KS_Toneporta;
		break;

		case 0x04: //Vibrato
			return KS_Vibrato;
		break;

		case 0x05: //Tone porta+Volume slide
			return KS_Toneporta_Volume_slide;
		break;

		case 0x06: //Vibrato+Volume slide
			return KS_Vibrato_Volume_slide;
		break;

		case 0x07: //Tremolo
			return KS_Tremolo;
		break;

		case 0x08: //Set panning
			return KS_Panning;
		break;

		case 0x09: //Sample offset
			//return 0x0F;
		break;

		case 0x0A: //Volume slide
			return KS_Volume_slide;
		break;

		case 0x0B: //Position jump
			return KS_Position_jump;
		break;

		case 0x0C: //Set volume
			//return 0x0F;
		break;

		case 0x0D: //Pattern break
			return KS_Pattern_break;
		break;

		case 0x0E:
			//return 0x0F;
		break;

		case 0x0F: //Set tempo/BPM
			return KS_Set_tempo;
		break;


		break;
	}
	return 0xFF;
}

void xm_resample(unsigned char *data,int len,int type)
{
	int i;

	unsigned short *sdata = (unsigned short *)data;

	if(type == 1)
	{
		len = len/2;
		sdata[0] = sdata[0];
		unsigned short spcm = sdata[0];
		for(i = 1;i < len;i++)
		{
			spcm += sdata[i];
			sdata[i] = spcm;
		}

	}else
	{
		data[0] = 0x80 + data[0];
		char cpcm = data[0];
		for(i = 1;i < len;i++)
		{
			cpcm += data[i];
			data[i] = cpcm;
		}
	}
}


