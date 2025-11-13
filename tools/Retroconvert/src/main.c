

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retro.h"

	
static unsigned char mega_bloc_buffer[0x2000000];
static int imb = 0;
	
static unsigned char mega_bloc_buffer_pal[0x20000];
static int imbp = 0;

void compare_files(const char *file1, const char *file2);

int main(int argc, char** argv)
{
	int option[10];
	char address[512],addresspal[512];

/*
	int sz;
	void *data = loadFile("otile.spr",&sz);
	void *cdata = sc16(data,&sz);
	writeFile("test.bin",cdata,sz);

	void *data2 = loadFile("test.bin",&sz);
	void *cdata2 = sc16x(data2,&sz);
	writeFile("test2.spr",cdata2,sz);

	compare_files("otile.spr","test2.spr");
	return 0;
*/
	if( select_option(argc,argv,option,address,addresspal) == 0 )
	{
		return 0;
	}

	if(option[TARGET] == 0)
	{
		if(option[LZ] == LZ_COMPRESSION)
		{
			int sz;
			void *data = loadFile(address,&sz);
			void *cdata = sc16(data,&sz);
			writeFile(addresspal,cdata,sz);
			return 0;
		}

	}

	if(option[LZ] == LZ_EXTRACT)
	{
		int sz;
		void *data = loadFile(address,&sz);
		void *cdata = sc16x(data,&sz);
		writeFile(addresspal,cdata,sz);
		return 0;
	}
	

	if(option[TARGET] == TARGET_NEOGEOX_FIX)
	{
		neogeo_extract_fix(address);
		return 0;
	}

	if(option[TARGET] == TARGET_NEOGEOX_SPR)
	{
		neogeo_extract(address);
		return 0;
	}

	RETRO_Image image,copy;
	int map = option[MAP]&0xF;
	int tile = option[TILE];

	if(tile != 0)
	{
		image = tile_spr(address,option[WIDTH],option[HEIGHT],tile);
		//return 0;
	}
	else
	{
		if(load_image(address,&image,4) == 1)
		{
			printf("Image is not valide\n");
			return 0;
		}
	}

	if(option[TARGET] == 0)
	{
		char filename[0x200];
		char name[0x180];

		output_filename(address,name);
		sprintf(filename,"%s_out.png",name);
		save_image(filename,&image);

		return 0;
	}

	//map
	int m = 0;
	if(map == 1)
	{
		init_image(&copy,128,64);

		for(int i = 0;i < 4;i++)
		{
			blit_32b(&image,&copy,(i*64),0x00,128,64);
			retro_convert(&copy,address,addresspal,option,m++);
		}

		init_image(&copy,128,128);
		blit_32b(&image,&copy,0x00,0x80,128,128);
		retro_convert(&copy,address,addresspal,option,m++);

		init_image(&copy,128,96);
		blit_32b(&image,&copy,0x80,0x80,128,96);
		retro_convert(&copy,address,addresspal,option,m++);

		init_image(&copy,128,32);
		blit_32b(&image,&copy,0xE0,0x80,128,32);
		retro_convert(&copy,address,addresspal,option,m++);
	}

	if(map == 2)
	{
		init_image(&copy,128,64);

		for(int i = 0;i < 4;i++)
		{
			blit_32b(&image,&copy,(i*64),0x00,128,64);
			retro_convert(&copy,address,addresspal,option,m++);
		}

		init_image(&copy,128,128);
		blit_32b(&image,&copy,0x00,0x80,128,128);
		retro_convert(&copy,address,addresspal,option,m++);

		blit_32b(&image,&copy,0x80,0x80,128,128);
		retro_convert(&copy,address,addresspal,option,m++);
	}

	if(map == 3)
	{
		init_image(&copy,128,32);

		for(int i = 0;i < 6;i++)
		{
			blit_32b(&image,&copy,(i*32),0x00,128,32);
			retro_convert(&copy,address,addresspal,option,m++);
		}

		for(int i = 0;i < 6;i++)
		{
			blit_32b(&image,&copy,(i*32),0x80,128,32);
			retro_convert(&copy,address,addresspal,option,m++);
		}
	}

	if(map == 4)
	{
		init_image(&copy,128,64);

		for(int i = 0;i < 3;i++)
		{
			blit_32b(&image,&copy,(i*64),0x00,128,64);
			retro_convert(&copy,address,addresspal,option,m++);

			blit_32b(&image,&copy,(i*64),0x80,128,64);
			retro_convert(&copy,address,addresspal,option,m++);
		}
	}

	if(map == 5)
	{
		init_image(&copy,256,256);
		blit_32b(&image,&copy,0x00,0x00,256,256);
		retro_convert(&copy,address,addresspal,option,m++);

		init_image(&copy,128,128);

		for(int i = 0;i < 6;i++)
		{
			blit_32b(&image,&copy,(i*128)+256,0,128,128);
			retro_convert(&copy,address,addresspal,option,m++);

			blit_32b(&image,&copy,(i*128)+256,128,128,128);
			retro_convert(&copy,address,addresspal,option,m++);
		}
	}

	if(map == 5)
	{
		init_image(&copy,256,256);
		blit_32b(&image,&copy,0x00,0x00,256,256);
		retro_convert(&copy,address,addresspal,option,m++);

		init_image(&copy,128,128);

		for(int i = 0;i < 6;i++)
		{
			blit_32b(&image,&copy,(i*128)+256,0,128,128);
			retro_convert(&copy,address,addresspal,option,m++);

			blit_32b(&image,&copy,(i*128)+256,128,128,128);
			retro_convert(&copy,address,addresspal,option,m++);
		}
	}

	if(map == 6)
	{
		init_image(&copy,256,16);

		for(int i = 0;i < 128;i++)
		{
			blit_32b(&image,&copy,0x00,16*i,256,16);
			retro_convert(&copy,address,addresspal,option,m++);
		}
	}


	if(map != 0)
	{
		if(option[MAP] & 0xF0)
		{
			char name[0x180];
			char filename[0x200];
			output_filename(address,name);

			if(option[MAP] & 0x10)
				sprintf(filename,"%s.spr",name);
			else
				sprintf(filename,"%s.bin",name);


			if(option[LZ] == LZ_COMPRESSION)
			{
				void *cdata = sc16(mega_bloc_buffer,&imb);
				writeFile(filename,cdata,imb);
			}else
			{
				writeFile(filename,mega_bloc_buffer,imb);
			}


			sprintf(filename,"%s.pal",name);
			writeFile(filename,mega_bloc_buffer_pal,imbp);
		}

		return 0;
	}
		

	retro_convert(&image,address,addresspal,option,-1);

	return 0;
}


//-----------------
static unsigned char buffer_data[0x1000000];

void retro_convert(RETRO_Image *image,char *address,char *addresspal,int *option,int num)
{
	int ncolor = 0;
	
	char name[0x180];
	char filename[0x200];

	unsigned char palette[0x300];

	int console = option[TARGET];
	int mode = option[MODE];
	int bpp  = option[BPP];
	int alpha = option[ALPHA];
	int type = option[TYPE];
	int bundle = option[MAP]&0xF0;
	int w = option[WIDTH];
	int h = option[HEIGHT];
	int lz = option[LZ];

	//------------
	if(mode == MODE_PAL)
		ncolor = load_palette(image,palette,alpha);
	
	if(mode == MODE_PAL_SP)
		ncolor = load_palette_sp(image,palette,alpha);

	if(mode == MODE_PAL_LOAD)
		ncolor = load_palette_ext(palette,addresspal);
	//-------------------------------
	
	if(bpp != 0)
		ncolor = bpp;

	printf("color : %d\n",ncolor);

	output_filename(address,name);
	//-------------------------------
	int size = 0,psize = 0;

	//Sprite
	if(num != -1)
		sprintf(filename,"%s_%d.spr",name,num);
	else
		sprintf(filename,"%s.spr",name);

	if(mode != MODE_PAL_OUT)
	{
		if(console == TARGET_PCE)
			size = pce_write_rom(buffer_data,image,palette,ncolor,type,w,h);

		if(console == TARGET_SNES)
			size = snes_write_rom(buffer_data,image,palette,ncolor,type);

		if(console == TARGET_NEOGEO)
			size = neogeo_write_rom(buffer_data,image,palette,ncolor,type);

		if(console == TARGET_NEOGEO_FIX)
			size = neogeofix_write_rom(buffer_data,image,palette,ncolor,type);

		if(bundle == 0)
		{
			if(lz == LZ_COMPRESSION)
			{
				void *cdata = sc16(buffer_data,&size);
				writeFile(filename,cdata,size);
			}
			else
				writeFile(filename,buffer_data,size);
		}else
		{
			memcpy(&mega_bloc_buffer[imb],buffer_data,size);
			imb += size;
		}
		
	}

	//----------------------------------------------

	//Palette
	if(num != -1)
		sprintf(filename,"%s_%d.pal",name,num);
	else
		sprintf(filename,"%s.pal",name);

	if(console == TARGET_PCE)
		psize = pce_write_pal(buffer_data,image,palette,ncolor,mode);

	if(console == TARGET_SNES)
		psize = snes_write_pal(buffer_data,image,palette,ncolor,mode);

	if(console == TARGET_NEOGEO)
		psize = neogeo_write_pal(buffer_data,image,palette,ncolor,mode);

	if(console == TARGET_NEOGEO_FIX)
		psize = neogeofix_write_pal(buffer_data,image,palette,ncolor,mode);

	if(bundle == 0)
	{
		writeFile(filename,buffer_data,psize);
	}else
	{
		memcpy(&mega_bloc_buffer_pal[imbp],buffer_data,psize);
		imbp += psize;
	}

	printf("size sprites : %d bytes\n",size);
	printf("size palette : %d bytes\n",psize);
	
}
