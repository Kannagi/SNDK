
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retro.h"
#include <stdint.h>

int neogeofix_write_rom(unsigned char *outpixels,RETRO_Image *image,unsigned char *palette,int ncolor,int type)
{
	int blocx,blocy;
	int tiles[64];
	int x,y,i,size = 0;
	unsigned char *pixel = image->pixels;
	blocx = 0;
	blocy = 0;


	

	while(1)
	{
		bloc_palette(image,blocx,blocy,8,pixel,palette,tiles);

		for(x = 0;x < 4;x++)
		{
			if(x == 0) i = 4;
			if(x == 1) i = 6;
			if(x == 2) i = 0;
			if(x == 3) i = 2;

			for(y = 0;y < 8;y++)
			{
				outpixels[size] = (tiles[(i+0) + (y*8)]&0xF) | (tiles[(i+1) + (y*8)] << 4);
				size += 1;
			}
		}

		blocx += 8;
		if(blocx+8 >image->w)
		{
			blocx = 0;
			blocy += 8;
		}

		if(blocy+8 >image->h) break;
	}

	return size;
}

int neogeofix_write_pal(unsigned char *outpixels,RETRO_Image *image,unsigned char *palette,int ncolor,int mode)
{
	int i,n;
	int psize = 0;
	int color;
	int ngpal[4];

	int size = image->w*image->h*image->BytesPerPixel;
	unsigned char *pixel = image->pixels;

	if(mode == MODE_PAL_OUT)
	{
		n = 0;
		for(i = 0;i < size;i += image->BytesPerPixel)
		{
			palette[n+0] = pixel[i+0];
			palette[n+1] = pixel[i+1];
			palette[n+2] = pixel[i+2];
			n +=3;
			if(n >= 0x300) break;
		}
		ncolor = n/3;
	}

	for(i = 0;i < ncolor;i++)
	{
		n = i*3;

		ngpal[0] = palette[n+0]>>3;
		ngpal[1] = palette[n+1]>>3;
		ngpal[2] = palette[n+2]>>3;

		color = ( (ngpal[0]& 0x1E) >> 1) + ( (ngpal[1]& 0x1E) << 3) + ( (ngpal[2]& 0x1E) << 7);
		color += ( (ngpal[0] & 0x01) << 12) + ((ngpal[1] & 0x01) << 13) + ((ngpal[0] & 0x01) << 14);

		if( (i == 16) && (mode != MODE_PAL_OUT) )
		{
			return psize;
		}

		outpixels[psize+0] = color>>8;
		outpixels[psize+1] = color;

		psize += 2;
	}

	outpixels[0] = 0;
	outpixels[1] = 0;

	return psize;
}