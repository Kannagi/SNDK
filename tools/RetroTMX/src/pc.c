
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmx.h"
extern TAG *tag;

void bin_map(TMX *tmx,char *out,int compress)
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
			sprintf(str,"%s_A.ktm",out);
			type = 0;
		}


		if(strcmp(tmx->layer[i].name,"BG2") == 0)
		{
			sprintf(str,"%s_B.ktm",out);
			type = 0;
		}

		if(strcmp(tmx->layer[i].name,"BG3") == 0)
		{
			sprintf(str,"%s_D.ktm",out);
			type = 0;
		}


		if(strcmp(tmx->layer[i].name,"BG4") == 0)
		{
			sprintf(str,"%s_E.ktm",out);
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

				tmp = 0;
				if(tile == 0) tmp += 4;

				if(tile > 0) tile -= ext+1;

				id = (tile&0x1FFF);

				if(flip & 2) tmp += 1;
				if(flip & 1) tmp += 2;


				data = id + (tmp<<13);

				tmx->layer[i].data[l] = data;

				if(compress == 0)
				{
					size += 2;
					fputc(data,file);
					fputc(data>>8,file);
				}

			}

			if(compress != 0)
			{
				size = 0;
				int rle = 0;
				unsigned int flag = 0;

				fputc(0,file);
				fputc(0,file);

				for(l = 0;l < n;l++)
				{
					data = tmx->layer[i].data[l];

					flag = 0;
					rle = 0;
					if(l+1 < n)
					{
						j = l;

						//-----------------------
						//RLE
						while(tmx->layer[i].data[j+0] == tmx->layer[i].data[j+1])
						{
							rle++;
							j++;

							if(rle >= 0x3F)
								break;
							if(j+1 >= n)
								break;
						}
						if(rle > 0)
							flag = 0x1;

						//-----------------------
						if(rle == 0)
						{
							j = l;
							while((data+2) == tmx->layer[i].data[j+1])
							{
								rle++;
								j+=2;

								if(rle >= 0x3F)
									break;
								if(j+1 >= n)
									break;
							}
							if(rle > 1)
							{
								flag = 0x3;
								j--;
							}
							else
								rle = 0;

						}
						//-----------------------
						//RLE inc
						if(rle == 0)
						{
							j = l;
							while(tmx->layer[i].data[j+0]+2 == tmx->layer[i].data[j+1])
							{
								rle++;
								j++;

								if(rle >= 0x3F)
									break;
								if(j+1 >= n)
									break;
							}
							if(rle > 0)
								flag = 0x2;
						}


						//-----------------------
/*
						if(rle == 0)
						{
							j = l;
							while( (tmx->layer[i].data[j+0]&0xFF00) == (tmx->layer[i].data[j+1]&0xFF00) )
							{
								rle++;
								j+=2;

								if(rle >= 0x3F)
									break;
								if(j+1 >= n)
									break;
							}
							if(rle > 0)
								flag = 0x4;
						}*/

						l = j;
					}

					if(flag != 0)
						data++;

					fputc(data,file);
					fputc(data>>8,file);
					size += 2;

					if(rle > 0)
					{
						rle |= (flag-1)<<6;
						fputc(rle,file);
						size += 1;

						//if(flag == 0x04) size += (rle&0x3F);
					}
				}

				fseek(file,0,SEEK_SET);
				fputc(size,file);
				fputc(size>>8,file);

				float percent = (float)size/(float)(n*2);
				printf("Compressed %d bytes into %d bytes ==> %.2f%% \n",n*2,size,percent*100);
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

				if(tile > 0) tile -= relativet;
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

			if(compress != 0)
			{
				fputc(0,file);
				fputc(0,file);
				int rle;

				for(l = 0;l < n;l++)
				{
					data = tmx->layer[i].data[l];

					rle = 0;
					if(l+1 < n)
					{
						j = l;

						//-----------------------
						//RLE
						while(tmx->layer[i].data[j+0] == tmx->layer[i].data[j+1])
						{
							rle++;
							j++;

							if(rle >= 0xFF)
								break;
							if(j+1 >= n)
								break;
						}

						l = j;
					}

					if(rle > 0)
						data |= 0x80;

					fputc(data,file);
					size++;

					if(rle > 0)
					{
						fputc(rle,file);
						size ++;
					}

				}


				fseek(file,0,SEEK_SET);
				fputc(size,file);
				fputc(size>>8,file);


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

