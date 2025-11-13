
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retro.h"
#include <stdint.h>

void neogeo_extract(const char *filename1)
{
	uint8_t *data1,*data2;
	int size,size2;
	data1 = loadFile(filename1,&size);

	char filename2[256];
	strcpy(filename2,filename1);

	filename2[5]++;
	if(filename2[8] != 'i')
		filename2[8]++;

	data2 = loadFile(filename2,&size2);

	if( (data1 == NULL) || (data2 == NULL) || (size != size2) )
	{
		printf("Error open file !\n");
		return;
	}

	uint8_t color;
	int ibloc = 0;
	int x = 8,y = 0,l = 0;
	int px = 0;
	int py = 0;

	uint8_t pixels[16*16*4];
	RETRO_Image image;
	image.w = 512;
	image.h = size>>7;
	image.BytesPerPixel = 4;
	image.pixels = malloc(image.w*image.h*4);

	for(int j = 0; j < size;j+=2)
	{
		if(ibloc == 16)
		{
			x = 0;
			y = 0;
		}

		l = x*4 + y*4*16;

		//---------
		for(int i = 0;i < 8;i++)
		{
			color = ( (data1[j+0] >> i) & 0x01 )*1 + ( (data1[j+1] >> i) & 0x01 )*2 + ( (data2[j+0] >> i) & 0x01 )*4 + ( (data2[j+1] >> i) & 0x01 )*8;

			pixels[l+0] = 255-(color*16);
			pixels[l+1] = 255-(color*16);
			pixels[l+2] = 255-(color*16);
			pixels[l+3] = 0xFF;
			l+=4;
		}
		

		y++;
		ibloc++;
		if(ibloc >= 32)
		{
			blit_32b_buffer(&image,pixels,px,py,16,16);
			l = 0;
			x = 8;
			y = 0;

			px += 16;
			if(px >= 512)
			{
				px = 0;
				py += 16;
			}

			if(py >= image.h)
			{
				save_image("romC_spr.png",&image);
				return;
			}

			ibloc = 0;
		}
	}

	save_image("romC_spr.png",&image);
}



/*

void neogeo_extract(int argc, char** argv)
{
	SDL_Surface *image,*ecran;
	FILE *file1,*file2;
	int octet4[4],octet = 0,noctet = 0,i,l = 0,couleur,ocmp = 0,n = 0,x = 8 ,y = 0,ok;

	ecran = SDL_CreateRGBSurface(0,256,256,24,0,0,0,0);
	image = SDL_CreateRGBSurface(0,16,16,24,0,0,0,0);
	pixels = image->pixels;
	position.x = 0;
	position.y = 0;

	while(octet != -1)
	{
		octet = fgetc(file1);
		octet4[0] = octet;

		octet = fgetc(file1);
		octet4[1] = octet;

		octet = fgetc(file2);
		octet4[2] = octet;

		octet = fgetc(file2);
		octet4[3] = octet;

		//printf("%d %d %d\n",l,noctet,n);



		if(noctet == 0x20)
		{
			x = 0;
			y = 0;
		}



		l = x*3 + y*3*16;

		for(i = 0;i < 8;i++)
		{
			if(i == 0) ocmp = 0x01;
			if(i == 1) ocmp = 0x02;
			if(i == 2) ocmp = 0x04;
			if(i == 3) ocmp = 0x08;
			if(i == 4) ocmp = 0x10;
			if(i == 5) ocmp = 0x20;
			if(i == 6) ocmp = 0x40;
			if(i == 7) ocmp = 0x80;

			//printf("%d %d\n",noctet ,l);

			couleur = ( (octet4[0] >> i) & 0x01 )*1 + ( (octet4[1] >> i) & 0x01 )*2 + ( (octet4[2] >> i) & 0x01 )*4 + ( (octet4[3] >> i) & 0x01 )*8;
			//printf("%d : %d %x %x %x %x\n",l,couleur,octet4[0],octet4[1],octet4[2],octet4[3]);

			pixels[l+0] = 255-(couleur*16);
			pixels[l+1] = 255-(couleur*16);
			pixels[l+2] = 255-(couleur*16);
			l+=3;
		}


		y++;



		noctet +=2;
		if(noctet >= 0x40)
		{
			noctet = 0;
			l = 0;
			x = 8;
			y = 0;

			SDL_BlitSurface(image,NULL,ecran,&position);
			position.x += 16;
			if(position.x >= 256)
			{
				position.x = 0;
				position.y += 16;
			}

			if(position.y >= 256)
			{
				position.x = 0;
				position.y = 0;
				sprintf(chaine,"save%d.bmp",n);
				SDL_SaveBMP(ecran,chaine);
				n++;
			}
		}

		//if(n == 128) break;
	}


	fclose(file1);
	fclose(file2);
	SDL_FreeSurface(image);

}

*/