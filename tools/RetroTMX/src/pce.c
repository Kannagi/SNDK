
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmx.h"
extern TAG *tag;

void pce_map(TMX *tmx,char *out,int compress)
{
	FILE *file;
	int i,l,n = 0,x,y;
	unsigned int tile,tmp;
	char str[512];
	int id;
	unsigned int data;
	int type;
	int size = 0;
	int itag = 0;


	int relativet = 2;//,relative =0;

	int ext = 0,pext = 0;;
	if( strcmp("ext",tmx->tileset[0].name) == 0 )
	{
		ext += tmx->tileset[0].tilecount;
		pext++;
		//relative = tmx->tileset[0].firstgid;
	}


	if( strcmp("tag",tmx->tileset[1].name) == 0 )
	{
		ext += tmx->tileset[1].tilecount;
		pext++;
		relativet = tmx->tileset[1].firstgid;
	}


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

				tmp = 1;



				if(tile > 0) tile -= ext+1;
				id = (tile&0x1FF)<<1;
				id += 0xA0;

				if(tile&0x08)
				{
					tmp = 8;
					id += 0x240-0x10;
				}


				if(tile >= 64) tmp++;
				if(tile >= 128) tmp++;
				if(tile >= 160) tmp++;
				if(tile >= 192) tmp++;
				if(tile >= 224) tmp++;
				if(tile >= 256) tmp++;
				if( (tmp == 14) && (tile >= 272) ) tmp++;

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
				ih += iw;
			}





			fclose(file);
		}

		//collision/tag
		if(type == 1)
		{
			itag = 0;

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

				if(tile > 0) tile -= relativet;
				data = tile&0x7F;

				if((tile&0x80) == 0)
				{
					tmx->layer[i].data[l] = data;

				}else
				{
					tmx->layer[i].data[l] = 0;

					tag[itag].type = data;
					tag[itag].x = ((l%tmx->layer[i].width)*16)<<2;
					tag[itag].y = ((l/tmx->layer[i].width)*16)<<2;
					itag++;
				}


			}

			if(compress != 0)
			{
				for(l = 0;l < n;l+=4)
				{
					data  = (tmx->layer[i].data[l+0]&3);
					data += (tmx->layer[i].data[l+1]&3)<<2;
					data += (tmx->layer[i].data[l+2]&3)<<4;
					data += (tmx->layer[i].data[l+3]&3)<<6;

					fputc(data,file);
					size++;
				}
			}else
			{
				for(l = 0;l < n;l+=2)
				{
					data  = (tmx->layer[i].data[l+0]&0xF);
					data += (tmx->layer[i].data[l+0]&0xF)<<4;

					fputc(data,file);
					size++;
				}
			}

			fclose(file);
		}

		printf("%s : %d bytes\n",str,size);
	}

	if(itag > 0)
	{
		sprintf(str,"%s_tag.ktm",out);
		file = fopen(str,"wb");
		if(file == NULL)
		{
			printf("Error no write %s\n",out);
			return;
		}
		fputc(itag,file);
		fputc(itag>>8,file);

		fwrite(&tag,sizeof(TAG), itag, file);
		fclose(file);
	}

}
