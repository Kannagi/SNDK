#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "retro.h"

int load_palette(RETRO_Image *image,unsigned char *palette,int noalpha)
{
	int i,l;
	unsigned char *pixel = image->pixels;
	int size = image->w*image->h*image->BytesPerPixel;
	unsigned char r,g,b;
	int n = 3 -(noalpha*3),black = 0,pal;

	for(i = 0;i < 0x300;i++)
		palette[i] = 0;

	palette[0] = 0xFF;
	palette[1] = 0x00;
	palette[2] = 0xFF;

	for(i = 0;i < size;i += image->BytesPerPixel)
	{
		r = pixel[i+0];
		g = pixel[i+1];
		b = pixel[i+2];

		pal = 1;
		for(l = 0;l < 0x300;l+=3)
		{
			if(palette[l+0] == r && palette[l+1] == g && palette[l+2] == b)
			{
				pal = 0;
				break;
			}
		}

		if(pal == 1)
		{
			palette[n+0] = r;
			palette[n+1] = g;
			palette[n+2] = b;

			n +=3;
			if(n >= 0x300) return n;
		}else
		{
			if(black == 0 && r == 0 && g == 0 && b == 0)
			{
				palette[n+0] = r;
				palette[n+1] = g;
				palette[n+2] = b;

				n +=3;
				black = 1;
				if(n >= 0x300) return n;
			}
		}
	}

	return n/3;
}

int load_palette_sp(RETRO_Image *image,unsigned char *palette,int noalpha)
{
	int i,l;
	unsigned char *pixel = image->pixels;
	int size = image->w*image->h*image->BytesPerPixel;
	unsigned char r,g,b;
	int n = 3 -(noalpha*3),black = 0,pal;

	int nocolor = 0;

	for(i = 0;i < 0x300;i++)
		palette[i] = 0;


	for(i = 0;i < size;i += image->BytesPerPixel)
	{
		r = pixel[i+0];
		g = pixel[i+1];
		b = pixel[i+2];

		pal = 1;
		for(l = 0;l < 0x300;l+=3)
		{
			if(palette[l+0] == r && palette[l+1] == g && palette[l+2] == b)
			{
				pal = 0;
				break;
			}
		}

		if(pal == 1)
		{
			if(noalpha == 0 && r == 0xFF && g == 0x00 && b == 0xFF)
			{
				palette[0] = r;
				palette[1] = g;
				palette[2] = b;

			}else
			{
				nocolor = 0;

				if(r == 0x00 && g == 0xFF && b == 0x00)
					nocolor = 1;

				if(r == 0xFF && g == 0x00 && b == 0x00)
					nocolor = 1;

				if(r == 0x00 && g == 0x00 && b == 0xFF)
					nocolor = 1;

				if(r == 0xFF && g == 0xFF && b == 0x00)
					nocolor = 1;

				if(r == 0x00 && g == 0xFF && b == 0xFF)
					nocolor = 1;

				if(nocolor == 0)
				{
					palette[n+0] = r;
					palette[n+1] = g;
					palette[n+2] = b;

					n +=3;
				}
			}

			if(n >= 0x300) return n;
		}else
		{
			if(black == 0 && r == 0 && g == 0 && b == 0)
			{
				palette[n+0] = r;
				palette[n+1] = g;
				palette[n+2] = b;

				n +=3;
				black = 1;
				if(n >= 0x300) return n;
			}
		}
	}

	return n/3;
}

int load_palette_ext(unsigned char *palette,char *addresspal)
{
	int i;
	RETRO_Image image ;
    int ret = load_image(addresspal,&image,3);
	if(ret == 1)
	{
		printf("Image is not valide (palette)\n");
		return 0;
	}

	for(i = 0;i < 0x300;i++)
		palette[i] = 0;

	
	int ncolor = 0;
	unsigned char *pixel = image.pixels;

	int l = 0;

	for(i = 0;i < image.w*image.BytesPerPixel;i += image.BytesPerPixel)
	{
		palette[l+0] = pixel[i+0];
		palette[l+1] = pixel[i+1];
		palette[l+2] = pixel[i+2];
		ncolor++;
		l+=3;
	}

	free_image(&image);

	return ncolor;
}


void bloc_palette(RETRO_Image *image,int blocx,int blocy,int blocw,unsigned char *pixel,unsigned char *palette,int *tiles)
{
	int x,y,i,l;
	int n = 0;
	int r,g,b;


	for(y = blocy;y < blocy+blocw;y++)
	{
		for(x = blocx;x < blocx+blocw;x++)
		{
			i = (y*image->w*image->BytesPerPixel) + x*image->BytesPerPixel;
			r = pixel[i+0];
			g = pixel[i+1];
			b = pixel[i+2];

			for(l = 0;l < 0x300;l+=3)
			{
				if(palette[l+0] == r && palette[l+1] == g && palette[l+2] == b)
					break;
			}

			tiles[n] = l/3;
			n++;
		}
	}
}