
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retro.h"
#include <stdint.h>


void neogeo_extract_fix(const char *filename)
{
	uint8_t *data;
	int size;
	data = loadFile(filename,&size);
	if(data == NULL)
	{
		printf("Error open file !\n");
		return;
	}

	uint8_t color,bpp4;
	int ibloc = 0;
	int x = 4,y = 0,l = 0;
	int px = 0;
	int py = 0;

	uint8_t pixels[8*8*4];
	RETRO_Image image;
	image.w = 256;
	image.h = 1024;
	image.BytesPerPixel = 4;
	image.pixels = malloc(256*1024*4);

	for(int i = 0; i < size;i++)
	{
		bpp4 = data[i];

		if(ibloc < 8) x = 4;
		else if(ibloc < 16) x = 6;
		else if(ibloc < 24) x = 0;
		else if(ibloc < 32) x = 2;

		l = x*4 + y*4*8;

		color = bpp4 & 0x0F;

		pixels[l+0] = 255-(color*16);
		pixels[l+1] = 255-(color*16);
		pixels[l+2] = 255-(color*16);
		pixels[l+3] = 0xFF;

		if(color == 0)
		{
			pixels[l+0] = 255;
			pixels[l+1] = 0;
			pixels[l+2] = 255;
		}

		color = bpp4 >> 4;

		pixels[l+4] = 255-(color*16);
		pixels[l+5] = 255-(color*16);
		pixels[l+6] = 255-(color*16);
		pixels[l+7] = 0xFF;

		if(color == 0)
		{
			pixels[l+4] = 255;
			pixels[l+5] = 0;
			pixels[l+6] = 255;
		}

		l += 8;

		y++;
		if(y >= 8) y = 0;

		ibloc++;
		if(ibloc >= 32)
		{
			blit_32b_buffer(&image,pixels,px,py,8,8);

			px += 8;
			if(px >= 256)
			{
				px = 0;
				py += 8;
			}

			if(py >= 1024)
			{
				save_image("fix.png",&image);
				return;
			}

			ibloc = 0;
		}
	}

	save_image("fix.png",&image);
}