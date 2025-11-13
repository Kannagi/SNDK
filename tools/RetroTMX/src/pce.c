
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmx.h"
extern TAG *tag;

void pce_map(TMX *tmx,char *out,int type_map)
{
	FILE *file;
	int i,l,n = 0,x,y;
	unsigned int tile,tmp;
	char str[512];
	int id;
	unsigned int data;
	int type;
	int size = 0;

	for(i = 0; i < tmx->nmap;i++)
	{
		size = 0;
		type = -1;
		sprintf(str,"%s_%d.ktm",out,i);

		if(strcmp(tmx->layer[i].name,"BG1") == 0)
		{
			sprintf(str,"%s.ktm",out);
			type = 0;
		}

		if(strcmp(tmx->layer[i].name,"BGC") == 0)
		{
			sprintf(str,"%s_C.ktm",out);
			type = 1;
		}


		//BG1
		if(type == 0)
		{
			file = fopen(str,"wb");
			if(file == NULL)
			{
				printf("Error no write %s\n",out);
				return;
			}

			n = tmx->layer[i].width*tmx->layer[i].height;
			for(l = 0;l < n;l++)
			{

				id = tile = tmx->layer[i].data[l];
				tile = tile&0xFFFF;

				tmp = 0;


				if(tile > 0) tile -= 1;
				id = (tile&0x1FF)<<1;
				id += 0x100;

				if(tile&0x08)
				{
					tmp = 6;
					id += 0x180-0x10;
				}


				if(tile >= 0x20) tmp++;
				if(tile >= 0x40) tmp++;
				if(tile >= 0x60) tmp++;
				if(tile >= 0x80) tmp++;
				if(tile >= 0xA0) tmp++;

				if(type_map == 1)
					tmp = tmp>>1;

				tmp += 4;

				data = id + (tmp<<12);

				tmx->layer[i].data[l] = data;
			}

			int w = tmx->layer[i].width;
			int lenw = tmx->layer[i].width>>4;
			int lenh = tmx->layer[i].height>>4;
			int iw,ih = 0;

			while(lenh)
			{
				iw = 0;
				while(lenw)
				{
					for(y = 0;y < 16;y++)
					for(x = 0;x < 16;x++)
					{
						l = x+(y*w);
						l += iw + ih;

						data = tmx->layer[i].data[l];
						fputc(data,file);
						size ++;
					}

					for(y = 0;y < 16;y++)
					for(x = 0;x < 16;x++)
					{
						l = x+(y*w);
						l += iw + ih;

						data = tmx->layer[i].data[l];
						fputc(data>>8,file);
						size ++;
					}

					lenw--;
					iw += 16;
				}
				lenh--;
				lenw = tmx->layer[i].width>>4;
				ih += iw*16;
			}

			fclose(file);
		}

		//collision/tag
		if(type == 1)
		{

			file = fopen(str,"wb");
			if(file == NULL)
			{
				printf("Error no write %s\n",out);
				return;
			}

			n = tmx->layer[i].width*tmx->layer[i].height;
			for(l = 0;l < n;l++)
			{
				data = tile = tmx->layer[i].data[l];

				if(tile > 0) tile -= 0x181;
				data = tile&0x7F;

				tmx->layer[i].data[l] = data;
			}


			for(l = 0;l < n;l+=2)
			{
				data  = (tmx->layer[i].data[l+0]&0xF);
				data += (tmx->layer[i].data[l+0]&0xF)<<4;

				fputc(data,file);
				size++;
			}


			fclose(file);
		}

		printf("%s : %d bytes\n",str,size);
	}

}
