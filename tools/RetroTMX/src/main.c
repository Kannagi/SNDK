#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmx.h"

TAG *tag;
void output_filename(char *address,char *str);
void neogeo_map(TMX *tmx,char *out,int compress);
void snes_map(TMX *tmx,char *out,int compress,int tmap);
void bin_map(TMX *tmx,char *out,int compress);
void pce_map(TMX *tmx,char *out,int tmap);
void md_custom_map(TMX *tmx,char *out,int compress);

int main(int argc, char** argv)
{
	int i;

    int option[10];
    char address[512];

    for(i = 0; i < 10;i++)
		option[i] = 0;

    address[0] = 0;

    for(i = 1; i < argc;i++)
    {
        if(argv[i][0] == '-')
        {
        	if(strcmp(argv[i],"-nes") == 0) option[3] = 1;
        	if(strcmp(argv[i],"-sms") == 0) option[3] = 2;
        	if(strcmp(argv[i],"-pce") == 0) option[3] = 3;
        	if(strcmp(argv[i],"-sfc") == 0) option[3] = 4;
        	if(strcmp(argv[i],"-md")  == 0) option[3] = 5;
        	if(strcmp(argv[i],"-ng")  == 0) option[3] = 6;

        	if(strcmp(argv[i],"-md")  == 0) option[3] = 7;

            if(strcmp(argv[i],"-z") == 0) option[1] = 1;
            if(strcmp(argv[i],"-pal") == 0) option[2] = 1;
            if(strcmp(argv[i],"-map1")  == 0) option[4] = 0;
            if(strcmp(argv[i],"-map2")  == 0) option[4] = 1;

        }else
        {
            strcpy(address,argv[i]);
        }
    }

    if(address[0] == 0)
    {
        printf("Enter a tmx format\n");
        printf("option target cible : -nes , -sms , -pce , -sfc , -md , -ng\n");
        printf("option compress : -z\n");
        printf("option pal : -pal\n");

        printf("\nExemple :\nRetroTMX -sfc -z map.tmx\n");
        return 0;
    }
	char str[512];
	static TMX tmx;
	Load_TMX(&tmx,address);
	output_filename(address,str);

	int console = option[3];




	if(console == 0)
		bin_map(&tmx,str,option[1]);

	if(console == 3)
		pce_map(&tmx,str,option[4]);


	if(console == 4)
		snes_map(&tmx,str,option[1],option[4]);

	if(console == 6)
		neogeo_map(&tmx,str,option[1]);

    return 0;
}



void output_filename(char *address,char *str)
{
    int l = 0;
    int i = 0;
    while(address[i] != 0 && address[i] != '.' )
    {
        str[l] = address[i];
        l++;

        if(address[i] == '/' || address[i] == '\\') l = 0;
        i++;
    }
    str[l] = 0;
}



