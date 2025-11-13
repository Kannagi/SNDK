
#include <stdio.h>
#include <stdlib.h>
#include "retro.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


RETRO_Image  tile_spr(char *address,int tilew,int tileh,int type)
{
	int width, height;

	RETRO_Image image;

	int ret = load_image(address,&image,4);
	 if (ret != 0)
	{
		printf("Error: load \n");
		exit(0);
	}

	height =  image.h;
	width =  image.w;
	void* img_data = image.pixels;
   

	printf("image: %dx%d\n", width, height);
	printf("bloc: %d %d\n", tilew,tileh);

	unsigned char *pixel_out;

	pixel_out = tileset_spr(img_data,width,&height,tilew,tileh,type);
	width = 128;

	char filename[0x200];
	char name[0x180];

	output_filename(address,name);
	sprintf(filename,"%s.tile",name);
	writeFileTile(filename);

	image.w = width;
	image.h = height;
	image.pixels = pixel_out;
	image.BytesPerPixel = 4;

	return image;
}

int load_image(char *filename,RETRO_Image * image,int size)
{
	int channels;
	image->BytesPerPixel = size;
	image->pixels = stbi_load(filename, &image->w, &image->h, &channels, size); 
	if (image->pixels == NULL)
	{
		printf("Error: load %s\n", filename);
		return 1;
	}

	return 0;
}


int save_image(char *filename,RETRO_Image * image)
{
	return stbi_write_png(filename, image->w, image->h, image->BytesPerPixel, image->pixels, image->w * image->BytesPerPixel);
}

void free_image(RETRO_Image * image)
{
	if(image->pixels != NULL)
		 stbi_image_free(image->pixels);
}