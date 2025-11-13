
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retro.h"

unsigned int buffer[16*16];

int tile_empty(unsigned int* pixels ,int offset, int width)
{
	int count = 0;
	int l = 0;

	for(int y = 0; y < 16;y++)
	{
		for(int x = 0; x < 16;x++)
		{
			int i = (y*width) + x + offset;

			if(pixels[i] != 0xFFFF00FF)
				count++;

			buffer[l] = pixels[i];
			l++;
		}
	}

	if(count == 0)
		return 1;

	return 0;
}



void tile_copy(unsigned int* pixels ,int offset)
{
	int l = 0;
	int i = offset;
	int ix;

	for(int y = 0; y < 16;y++)
	{
		ix = i;
		for(int x = 0; x < 16;x++)
		{
			pixels[ix] = buffer[l];
			l++;
			ix++;
		}
		i += 128;
	}
}


unsigned char buffer_tile[0x4000];
static int nbuffer_tile = 0;

void *tileset_spr(unsigned int* pixels ,int width ,int *in_height,int tilew, int tileh,int tile_sz)
{
	if(tilew < 1)
		return NULL;

	if(tileh < 1)
		return NULL;

	int tsize = 16;
	if(tile_sz == TILE16)
		tsize = 32;

	if(tile_sz == TILE32)
		tsize = 64;

	if(tile_sz == TILE64)
		tsize = 128;

	int height = *in_height;
	int nw = (width/16)/tilew;
	int nh = (height/16)/tileh;
	int n =  nh*(tsize>>1)*(tileh+1);
	int lb = 0, lbi = 0;
	
	unsigned int *outpixels = malloc(128*n*4);
	*in_height = n;

	memset(buffer_tile, 0xFF, sizeof(buffer_tile));

	for(int y = 0; y < n;y++)
	{
		for(int x = 0; x < 128;x++)
		{
			int i = x + (y*128);
			outpixels[i] = 0xFFFF00FF;
		}
	}

	
	int offset = 0,offser_out = 0,tmp = 0;

	for(int yw = 0; yw < nh;yw++)
	{
		for(int xw = 0; xw < nw;xw++)
		{
			int itile = 0;

			offser_out = (xw*128*tsize) + (yw*128*tsize*nw);
			tmp = 0;
			lb = lbi;
			lbi += 16;

			for(int y = 0; y < tileh;y++)
			{
				for(int x = 0; x < tilew;x++)
				{
					int toff = (x*16) + (y*width*16) + offset;
					if (tile_empty(pixels,toff,width) == 0)
					{
						tile_copy(outpixels,offser_out);
						offser_out += 16;
						tmp += 16;
						if( tmp == 128)
						{
							offser_out += (15*128);
							tmp = 0;
						}
						itile++;

						buffer_tile[lb] = x | (y<<4);
						lb++;
					}
					if(itile > (tsize>>1))
					{
						printf("error tile (%d/%d) : max %d tiles !!!\n",xw+1,yw+1,tsize>>1);
						break;
					}
						
				}
			}

			offset += (tilew*16);
			
		}

		offset += (width*16*tileh)-width;
	}

	nbuffer_tile = lb;

	return outpixels;
}


void writeFileTile(const char* filename)
{
	if(nbuffer_tile == 0)
		return;
	FILE* file = fopen(filename, "wb");
	if (file == NULL)
	{
		fprintf(stderr, "Impossible to write the file : %s\n", filename);
		return;
	}

	fwrite(buffer_tile, 1, nbuffer_tile, file);

	fclose(file);
}
