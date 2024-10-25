#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "retro.h"

int select_option(int argc, char** argv,int *option,char *address,char *addresspal)
{
    int i,arg = 0;

	for(i = 0; i < 10;i++)
		option[i] = 0;

	strcpy(addresspal,"palette.png");
	address[0] = 0;

	for(i = 1; i < argc;i++)
	{
		if(argv[i][0] == '-')
		{
			//Target option
			if(strcmp(argv[i],"-pce") == 0) option[TARGET] = TARGET_PCE;
			if(strcmp(argv[i],"-sfc") == 0) option[TARGET] = TARGET_SNES;
			if(strcmp(argv[i],"-ng")  == 0) option[TARGET] = TARGET_NEOGEO;

			//Palette option
			if(strcmp(argv[i],"-noalpha") == 0) option[ALPHA] = 1;

			if(strcmp(argv[i],"-only-palette") == 0) option[MODE] = MODE_PAL_OUT;
			if(strcmp(argv[i],"-palettesp") == 0) option[MODE] = MODE_PAL_SP;

			//Map option :
			if(strcmp(argv[i],"-map1")   == 0) option[MAP] = 1;
			if(strcmp(argv[i],"-map2")   == 0) option[MAP] = 2;
			if(strcmp(argv[i],"-map3")   == 0) option[MAP] = 3;
			if(strcmp(argv[i],"-map4")   == 0) option[MAP] = 4;
			if(strcmp(argv[i],"-bundle") == 0) option[MAP] |= 0x10;

			//SNES option
			if(strcmp(argv[i],"-2bpp") == 0) option[BPP] = 4;
			if(strcmp(argv[i],"-4bpp") == 0) option[BPP] = 16;
			if(strcmp(argv[i],"-8bpp") == 0) option[BPP] = 256;
			if(strcmp(argv[i],"-mode7") == 0) option[TYPE] = 1;

			//PCE option
			if(strcmp(argv[i],"-bg")  == 0) option[TYPE] = 1;
			if(strcmp(argv[i],"-spr") == 0) option[TYPE] = 0;

			//TILE SPR
			if(strcmp(argv[i],"-tile8") == 0) option[TILE] = TILE8;
			if(strcmp(argv[i],"-tile16") == 0) option[TILE] = TILE16;
			if(strcmp(argv[i],"-tile32") == 0) option[TILE] = TILE32;
			if(strcmp(argv[i],"-tile64") == 0) option[TILE] = TILE64;

			arg = 0;

			//load pal
			if(strcmp(argv[i],"-loadpalette") == 0)
			{
				option[MODE] = MODE_PAL_LOAD;
				arg = 1;
			}

			//h option
			if(strcmp(argv[i],"-h") == 0)
				arg = 2;

			//v option
			if(strcmp(argv[i],"-w") == 0)
				arg = 3;

		}else
		{
			if(arg == 0) strcpy(address,argv[i]);
			if(arg == 1) strcpy(addresspal,argv[i]);
			if(arg == 2) option[HEIGHT] = atoi(argv[i]);
			if(arg == 3) option[WIDTH] = atoi(argv[i]);
			arg = 0;
		}
	}

	if(address[0] == 0)
	{
		printf("Enter a picture format JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC\n");
		printf("option target cible : -pce , -sfc , -ng\n");
		printf("option palette : -only-palette (output palette only) , -palettesp (special palette)\n");
		printf("-loadpalette + arg , (load palette extern)\n");
		printf("option tile spr : -tile8 -tile16 -tile32 -tile64\n");
		printf("option -w -h : size w/h , use for -tile\n");
		printf("\noption sfc : -2bpp,-4bpp ,-8bpp,-mode7\n");
		printf("option pce : -bg,-spr\n");
		
		printf("option -map1 : 256x256/7pal\n");
		printf("option -map2 : 256x256/6pal\n");
		printf("option -map3 : 256x192/12pal\n");
		printf("option -map4 : 256x192/6pal\n");

		printf("\nExemple :\nretroconvert -sfc -4bpp myimage.png\n");
		return 0;
	}

    return 1;

}