#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "retro.h"

int snes_write_pal(unsigned char *outpixels,RETRO_Image *image,unsigned char *palette,int ncolor,int mode)
{
	int i,n;
	int psize = 0;
	unsigned char color;
	int snespal1,snespal2;

	int size = image->w*image->h*image->BytesPerPixel;
	unsigned char *pixel = image->pixels;
	int l = 0;

	palette[0] = 0;
	palette[1] = 0;
	palette[2] = 0;

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

		color = palette[n+0]/8;
		snespal1 = color;

		color = palette[n+1]/8;
		snespal1 += (0x07 & color) << 5;
		snespal2 =  (0x18 & color) >> 3;

		color = palette[n+2]/8;
		snespal2 += color << 2;

		outpixels[l] = snespal1;
		l++;

		outpixels[l] = snespal2;
		l++;

		psize += 2;
	}

	if(ncolor < 4)
	{
		for(i = ncolor;i < 4;i++)
		{
			outpixels[l] = 0;
			l++;

			outpixels[l] = 0;
			l++;
		}
	}else
	if( (ncolor < 16) && (ncolor != 4) )
	{
		for(i = ncolor;i < 16;i++)
		{
			outpixels[l] = 0;
			l++;

			outpixels[l] = 0;
			l++;
		}
	}

	return psize;
}

int snes_write_rom(unsigned char *outpixels,RETRO_Image *image,unsigned char *palette,int npal,int type)
{
	int blocx,blocy;
	int tiles[64];
	int snespixel[8];
	int i;
	int x,y,size = 0;
	short binpixel[32];
	char *cbinpixel = (char*)binpixel;
	unsigned char *pixel = image->pixels;
	blocx = 0;
	blocy = 0;
	

	while(1)
	{
		bloc_palette(image,blocx,blocy,8,pixel,palette,tiles);

		if(type == 0) //2,4,8 bpp
		{
			for(y = 0;y <8;y++)
			{
				for(i = 0;i < 8;i++)
					snespixel[i] = 0;

				for(x = 0;x < 8;x++)
				{
					i = tiles[x + (y*8)];

					if(i > npal-1) i = 1+i%(npal-1);
					snespixel[0] += ( (i>>0) & 0x01 ) << (7 - x);
					snespixel[1] += ( (i>>1) & 0x01 ) << (7 - x);
					snespixel[2] += ( (i>>2) & 0x01 ) << (7 - x);
					snespixel[3] += ( (i>>3) & 0x01 ) << (7 - x);

					snespixel[4] += ( (i>>4) & 0x01 ) << (7 - x);
					snespixel[5] += ( (i>>5) & 0x01 ) << (7 - x);
					snespixel[6] += ( (i>>6) & 0x01 ) << (7 - x);
					snespixel[7] += ( (i>>7) & 0x01 ) << (7 - x);
				}

				binpixel[y]	= snespixel[0] + (snespixel[1]<<8);
				binpixel[y+8]  = snespixel[2] + (snespixel[3]<<8);
				binpixel[y+16] = snespixel[4] + (snespixel[5]<<8);
				binpixel[y+24] = snespixel[6] + (snespixel[7]<<8);
			}


			memcpy(&outpixels[size],binpixel,16);
			if(npal > 4)  memcpy(&outpixels[size+16],&binpixel[8],16);
			if(npal > 16) memcpy(&outpixels[size+32],&binpixel[16],32);

			size += 16;
			if(npal > 4) size += 16;
			if(npal > 16) size += 32;

		}else //8pbb mode 7
		{
			for(y = 0;y <8;y++)
			{
				for(x = 0;x < 8;x++)
				{
					i = tiles[x + (y*8)];
					cbinpixel[x + (y*8)] =  i;

				}
			}

			memcpy(&outpixels[size],cbinpixel,64);

			size += 64;
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