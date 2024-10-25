#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmx.h"


void neogeo_map(TMX *tmx,char *out)
{
	FILE *file;
	int i,l,n = 0;
	unsigned int tile,flip,anim,tilemsb;
	char str[512];
	int id,j,pal = 0;
	unsigned int tileng;
	static char buffer[0x40000];
	int usebuffer = 0;
	int type;
	int size = 0;


	int ext = 0,pext = 0;;
	if( strcmp("ext",tmx->tileset[0].name) == 0 )
	{
		ext += tmx->tileset[0].tilecount;
		pext++;
	}


	if( strcmp("tag",tmx->tileset[1].name) == 0 )
	{
		ext += tmx->tileset[1].tilecount;
		pext++;
	}


	for(i = 0; i < tmx->nmap;i++)
	{
		size = 0;
		type = 0;
		sprintf(str,"%s_%d.ktm",out,i);

		if(strcmp(tmx->layer[i].name,"BG1") == 0)
			sprintf(str,"%s_A.ktm",out);

		if(strcmp(tmx->layer[i].name,"BG2") == 0)
			sprintf(str,"%s_B.ktm",out);

		if(strcmp(tmx->layer[i].name,"BGC") == 0)
		{
			sprintf(str,"%s_C.ktm",out);
			type = 1;
		}

		if(strcmp(tmx->layer[i].name,"BGEXT1") == 0)
			type = 2;

		if(strcmp(tmx->layer[i].name,"BGEXT2") == 0)
			type = 2;

		//BG1/2
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
				pal = 0;
				if(usebuffer != 0)
					anim = buffer[l];
				else
					anim = 0;

				id = tile = tmx->layer[i].data[l];
				flip = tile>>30;
				tile = tile&0xFFFF;
				tilemsb = tile&0xF0000;
				flip = anim<<2;
				if(tile > 0) tile -= 0x21;
				if(id > 0) id -= 0x21;

				pal = id/0x40;


				//tileng = tile | (flip<<16) | (pal<<24) | (tilemsb<<4);
				tileng = ((tile&0xFF00)>>8) | ((tile&0x00FF)<<8) | (flip<<24) | (pal<<16) | (tilemsb<<12);
				tmx->layer[i].data[l] = tileng;


				size += 4;
				fwrite(&tileng,sizeof(unsigned int),1,file);


			}
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
				id = tile = tmx->layer[i].data[l];
			}

			fclose(file);
		}




		//BG Ext
		if(type == 2)
		{
			n = tmx->layer[i].width*tmx->layer[i].height;
			int relative = 0;
			for(l = 0;l < n;l++)
			{
				id = tmx->layer[i].data[l];
				for(j = 0;j < tmx->ntileset;j++)
				{
					if(tmx->tileset[j].firstgid <= id)
						relative = tmx->tileset[j].firstgid;
				}
				buffer[l] = tmx->layer[i].data[l] - relative;
			}
			usebuffer = 1;

			printf("BGEXT\n");
		}

		printf("%s : %d bytes\n",str,size);
	}

}
