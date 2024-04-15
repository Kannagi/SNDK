#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmx.h"

void quickSort2(int n,TAG *tag);
extern TAG *tag;

void snes_map(TMX *tmx,char *out,int compress)
{
	FILE *file;
	int i,l,n = 0;
	unsigned int tile,flip,anim,tmp;
	char str[512];
	int id,j,pal = 0;
	unsigned int data;
	int usebuffer = 0;
	int type;
	int size = 0;
	int itag = 0;
	int first = 1;

	int mode = compress&0xF0;

	compress = compress&0xF;

/*
	int ext = 0,pext = 0;;
	if( strcmp("ext",tmx->tileset[0].name) == 0 )
	{
		ext += tmx->tileset[0].tilecount;
		pext++;
		relative = tmx->tileset[0].firstgid;


	}

	if( strcmp("tag",tmx->tileset[1].name) == 0 )
	{
		ext += tmx->tileset[1].tilecount;
		pext++;
		relativet = tmx->tileset[1].firstgid;
	}

	for(i = 0; i < tmx->nmap;i++)
	{
		if(strcmp(tmx->tileset[i].name,"id") == 0)
			relativet2 = tmx->tileset[i].firstgid;
	}
*/

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
		//printf("ok2 %d %d\n",tmx->tileset[i].firstgid,tmx->tileset[i].tilecount);
		size = 0;
		type = -1;
		sprintf(str,"%s_%d.ktm",out,i);

		usebuffer = -1;
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
/*
		if(strcmp(tmx->layer[i].name,"BGC") == 0)
		{
			sprintf(str,"%s_C.ktm",out);
			type = 1;
		}
/*
		if(strcmp(tmx->layer[i].name,"BGC") == 0)
		{
			sprintf(str,"%s_T.ktm",out);
			type = 2;
		}

		if(strcmp(tmx->layer[i].name,"BG1EXT") == 0)
		{
			sprintf(str,"%s_BGEXT1.ktm",out);
		}

		if(strcmp(tmx->layer[i].name,"BG2EXT") == 0)
		{
			sprintf(str,"%s_BGEXT2.ktm",out);
		}
*/


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
				anim = 0;
				tile = tmx->layer[i].data[l];

				if(usebuffer != -1)
				{
					anim = tmx->layer[usebuffer].data[l];
					if(anim != 0)
						tile = anim;
				}


				if(tile > 0) tile -= 1;


				flip = (tile>>30)&3;
				tile = tile&0xFFFF;

				id = (tile&0xFF)<<1;
				pal = 1;
				int bloc2 = (tile&0xFF)/0x40;
				pal += bloc2;

				if(tile&0x08)
				{
					pal += 4;
					id += 0x200-0x10;
				}

				if(pal == 6) pal = 5;
				if(pal >= 7) pal = 6;
				if(tile >= 0xF8) pal = 7;

				pal = pal<<10;
				tmp = 0;
				if(flip & 2) tmp = 1;
				if(flip & 1) tmp += 2;
				flip = tmp<<14;

				tmp = 0;
				if(anim != 0) tmp = 0x2000;


				data = id + pal + tmp + flip;
				if(tile == 0) data = 0;

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
				pal = 0;
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
								//j-=2;
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

			compress = 1;
			n = tmx->layer[i].width*tmx->layer[i].height;
			for(l = 0;l < n;l++)
			{
				data = tile = tmx->layer[i].data[l];

				if(tile > 0) tile -= 257;
				data = tile&0x7F;

				if((tile&0x80) == 0)
				{
					tmx->layer[i].data[l] = data;

					if(compress == 0)
					{
						printf("nocommpress \n",compress);
						size++;
						fputc(data,file);
					}
				}else
				{
					tmx->layer[i].data[l] = 0;

					tag[itag].type = data;
					//tag[itag].x = ((l%tmx->layer[i].width)*16)<<2;
					//tag[itag].y = ((l/tmx->layer[i].width)*16)<<2;

					tag[itag].x = ((l%tmx->layer[i].width)*16);
					tag[itag].y = ((l/tmx->layer[i].width)*16);
					itag++;
					itag &= 0x7F;
				}

			}


			if(compress != 0)
			{
				printf("commpress \n",compress);

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

			compress = 0;

			fclose(file);
		}


		if(type == 2)
		{
			j = 0;
			n = tmx->layer[i].width*tmx->layer[i].height;
			for(l = 0;l < n;l++)
			{
				tile = tmx->layer[i].data[l];

				if(tile > 0) tile -= first;
				data = tile&0xFF;

				if(tile != 0)
				{
					tag[j].type |= data<<8;
					j++;
				}
			}
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

		//quickSort2(itag,tag);

		fputc(itag,file);
		fputc(itag>>8,file);

		fwrite(&tag,sizeof(TAG), itag, file);
		fclose(file);
	}

}

void quickSort2(int n,TAG *tag)
{

	int  piv,L, R,i =0 ;
	int *beg = malloc(n*sizeof(int));
	int *end = malloc(n*sizeof(int));
	int *arr = malloc(n*sizeof(int));

	for(i = 0;i < n;i++)
	{
		arr = tag[i].y;
	}

	beg[0]=0; end[0]=n-1;
	while (i>=0)
	{

		L=beg[i]; R=end[i]-1;
		if (L<R)
		{
			piv=arr[L];
			if (i >= (n-1) ) return;

			while (L<R)
			{
				while (arr[R]>=piv && L<R)
					R--;
				if (L<R)
				{
					tag[L].x = tag[R].x;
					tag[L].y = tag[R].y;
					tag[L].type = tag[R].type;
					arr[L++]=arr[R];
				}


				while (arr[L]<=piv && L<R)
					L++;
				if (L<R)
				{
					tag[L].x = tag[R].x;
					tag[L].y = tag[R].y;
					tag[L].type = tag[R].type;
					arr[R--]=arr[L];
				}
			}
			arr[L]=piv;
			beg[i+1]=L+1;
			end[i+1]=end[i];
			end[i++]=L;

		}
		else
		{
			i--;
		}
	}

	free(beg);
	free(end);
	free(arr);

}

