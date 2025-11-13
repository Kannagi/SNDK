#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "retro.h"


int pce_write_rom(unsigned char *outpixels,RETRO_Image *image,unsigned char *palette,int ncolor,int type,int w,int h)
{
	int casex,casey;
	int tiles[64];
	int i,l , k = 0;
	int x,y,size = 0;
	int bin[128];
	int bx,by,bn;
	int ih,iw;
	ih = 0;
	iw = 0;

	int nl = 4,ns = 128,casez = 16;
	unsigned char *pixel = image->pixels;

	if(type == 1)
	{
		nl = 1;
		ns = 32;
		casez = 8;
	}

	casex = 0;
	casey = 0;

	if(h > 0) iw = -1;
	
	while(1)
	{
		if(iw >= w)
		{
			if(h > 0)
			{
				casex -= 16;
				casey += 16;
				if(w > 0) casex -= (w*16);
			}
			ih++;
			iw = 0;
		}
		else
		{
			iw++;
		}

		if(ih > h)
		{
			if(h > 0)
			{
				casex += 16;
				casey -= (h*16) + 16;
				if(w > 0) casex += (w*16);
			}
			ih = 0;
		}

		//printf("%d/%d: %d %d\n",iw,ih,casex,casey);

		for(i = 0;i < 128;i++)
			bin[i] = 0;


		for(l = 0;l < nl;l++)
		{

			if(l == 1)
			{
				casex+= 8;
			}

			if(l == 2)
			{
				casey += 8;
			}

			if(l == 3)
			{
				casex -= 8;
			}

			bloc_palette(image,casex,casey,8,pixel,palette,tiles);

			for(y = 0;y < 8;y++)
			{
				for(x = 0;x < 8;x++)
				{
					i = tiles[x + (y*8)];
					if(i > 15) i = 15;

					bx = x/8;
					by = y*2;
					bn = bx+by;

					if(type == 0)
					{

						if(l == 0) bn += 0x01;
						if(l == 2) bn += 0x10;
						if(l == 3) bn += 0x11;

						bin[bn+0x00] += ( (i&0x01)>>0 ) << (7 - x);
						bin[bn+0x20] += ( (i&0x02)>>1 ) << (7 - x);
						bin[bn+0x40] += ( (i&0x04)>>2 ) << (7 - x);
						bin[bn+0x60] += ( (i&0x08)>>3 ) << (7 - x);
					}else
					{
						bin[bn+0x00] += ( (i&0x01)>>0 ) << (7 - x);
						bin[bn+0x01] += ( (i&0x02)>>1 ) << (7 - x);
						bin[bn+0x10] += ( (i&0x04)>>2 ) << (7 - x);
						bin[bn+0x11] += ( (i&0x08)>>3 ) << (7 - x);
					}
				}

			}

			if(l == 3)
			{
				casey -= 8;
			}

		}

		for(i = 0;i < ns;i++)
		{
			outpixels[k] = bin[i];
			k++;
		}

		size += ns;

		//-----------
		casex += casez;
		if(casex+casez > image->w)
		{
			if(h == 0)
			{
				casex = 0;
				casey += casez;
			}else
			{
				if(ih == h)
				{
					casex = 0;
					casey += casez;
					casey += casez*h;
				}
			}
			
		}

		if(casey+casez > image->h) break;

	}

	return size;
}


int pce_write_pal(unsigned char *outpixels,RETRO_Image *image,unsigned char *palette,int ncolor,int mode)
{
	int i,n;
	int psize = 0;
	int color;
	int pal[4];

	int size = image->w*image->h*image->BytesPerPixel;
	unsigned char *pixel = image->pixels;

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
			if(n > 768) break;
		}
		ncolor = n/3;
	}

	for(i = 0;i < ncolor;i++)
	{
		n = i*3;

		pal[0] = palette[n+0]>>5;
		pal[1] = palette[n+1]>>5;
		pal[2] = palette[n+2]>>5;

		color = (pal[1]<<6) + (pal[0]<<3) +pal[2];

		outpixels[psize+0] = color;
		outpixels[psize+1] = (color>>8);

		psize += 2;
	}

	outpixels[0] = 0;
	outpixels[1] = 0;

	return psize;
}