#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmx.h"
extern TAG *tag;

void md_custom_map(TMX *tmx,char *out,int compress)
{
	FILE *file;
	int i,l,n = 0;
	unsigned int tile,flip,tmp;
	char str[512];
	int id,j;
	unsigned int data;
	int type;
	int size = 0;
	int itag = 0;

	//int relativet = 2;//,relative =0;

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
		//relativet = tmx->tileset[1].firstgid;
	}


	int enable_map[2];
	enable_map[0] = -1;
	enable_map[1] = -1;

	for(i = 0; i < tmx->nmap;i++)
	{
		if(strcmp(tmx->layer[i].name,"BG1EXT") == 0)
			enable_map[0] = i;

		if(strcmp(tmx->layer[i].name,"BG2EXT") == 0)
			enable_map[1] = i;

	}


	for(i = 0; i < tmx->nmap;i++)
	{
		size = 0;
		type = -1;
		sprintf(str,"%s_%d.ktm",out,i);

		int usebuffer = -1;
		if(strcmp(tmx->layer[i].name,"BG1") == 0)
		{
			usebuffer = enable_map[0];
			sprintf(str,"%s_A.ktm",out);
			type = 0;
		}


		if(strcmp(tmx->layer[i].name,"BG2") == 0)
		{
			usebuffer = enable_map[1];
			sprintf(str,"%s_B.ktm",out);
			type = 0;
		}


		if(strcmp(tmx->layer[i].name,"BGC") == 0)
		{
			sprintf(str,"%s_C.ktm",out);
			type = 1;
		}


		//BG1/2/3/4
		if(type == 0)
		{
			file = fopen(str,"wb");
			if(file == NULL)
			{
				printf("Error no write %s\n",out);
				return;
			}

			tmp = tmx->map.width;
			fputc(tmp,file);
			fputc(tmp>>8,file);

			tmp = tmx->map.height;
			fputc(tmp,file);
			fputc(tmp>>8,file);

			n = tmx->layer[i].width*tmx->layer[i].height;
			for(l = 0;l < n;l++)
			{

				id = tile = tmx->layer[i].data[l];
				flip = tile>>30;
				tile = tile&0xFFFF;

				int flag = 0;
				if(usebuffer != -1)
				{
					flag = tmx->layer[usebuffer].data[l];
				}

				tmp = 0;
				if(tile == 0) tmp += 4;

				if(tile > 0) tile -= ext+1;

				if(id > 0) tile++;

				id = (tile&0x07FF);

				if(flip & 2) tmp += 1;
				if(flip & 1) tmp += 2;


				data = id + (tmp<<11) + (flag<<13);

				tmx->layer[i].data[l] = data;

				if(compress == 0)
				{
					size += 2;
					fputc(data>>8,file);
					fputc(data,file);
				}

			}
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
			tmp = tmx->map.width;
			fputc(tmp,file);
			fputc(tmp>>8,file);

			tmp = tmx->map.height;
			fputc(tmp,file);
			fputc(tmp>>8,file);

			n = tmx->layer[i].width*tmx->layer[i].height;
			for(l = 0;l < n;l++)
			{
				data = tile = tmx->layer[i].data[l];

				//if(tile > 0) tile -= relativet;
				data = tile&0x7F;

				if((tile&0x80) == 0)
				{
					tmx->layer[i].data[l] = data;

					if(compress == 0)
					{
						size++;
						fputc(data,file);
					}
				}else
				{
					tmx->layer[i].data[l] = 0;

					tag[itag].type = data;
					tag[itag].x = ((l%tmx->layer[i].width)*16)<<2;
					tag[itag].y = ((l/tmx->layer[i].width)*16)<<2;
					itag++;
				}


			}


			fseek(file,0,SEEK_SET);
			fputc(size,file);
			fputc(size>>8,file);

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

