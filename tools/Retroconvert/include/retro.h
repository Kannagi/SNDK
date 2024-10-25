#ifndef __RETRO__
#define __RETRO__

typedef struct 
{
    int w,h,BytesPerPixel;
    void *pixels;

}RETRO_Image;


void retro_convert(RETRO_Image *image,char *address,char *addresspal,int *option,int num);

int load_image(char *filename,RETRO_Image * image,int size);
int save_image(char *filename,RETRO_Image * image);
void free_image(RETRO_Image * image);

void* loadFile(const char* filename,int *sz);
void writeFile(const char* filename,void *data,int nsize);
void output_filename(char *address,char *str);
int select_option(int argc, char** argv,int *option,char *address,char *addresspal);
void writeFileTile(const char* filename);

void bloc_palette(RETRO_Image *image,int blocx,int blocy,int blocw,unsigned char *pixel,unsigned char *palette,int *tiles);
int load_palette_ext(unsigned char *palette,char *addresspal);
int load_palette(RETRO_Image *image,unsigned char *palette,int noalpha);
int load_palette_sp(RETRO_Image *image,unsigned char *palette,int noalpha);


int snes_write_pal(unsigned char *data,RETRO_Image *image,unsigned char *palette,int ncolor,int mode);
int snes_write_rom(unsigned char *data,RETRO_Image *image,unsigned char *palette,int ncolor,int type);

int pce_write_pal(unsigned char *data,RETRO_Image *image,unsigned char *palette,int ncolor,int mode);
int pce_write_rom(unsigned char *data,RETRO_Image *image,unsigned char *palette,int ncolor,int type);

int neogeo_write_pal(unsigned char *outpixels,RETRO_Image *image,unsigned char *palette,int ncolor,int mode);
int neogeo_write_rom(unsigned char *outpixels,RETRO_Image *image,unsigned char *palette,int ncolor,int type);

void *tileset_spr(unsigned int* pixels ,int width ,int *in_height,int tilew, int tileh,int tile_sz);
RETRO_Image  tile_spr(char *address,int tilew,int tileh,int type);

void blit_32b(RETRO_Image *in_image,RETRO_Image* out_image,int px,int py,int w,int h);
void init_image(RETRO_Image* image,int w,int h);


#define MAP 0
#define TILE 1
#define BPP 2
#define TARGET 3
#define ALPHA 4
#define TYPE 5
#define HEIGHT 6
#define WIDTH 7
#define MODE 8

#define TARGET_SNES 1
#define TARGET_PCE 2
#define TARGET_NEOGEO 3

#define MODE_PAL 0
#define MODE_PAL_OUT 1
#define MODE_PAL_SP 2
#define MODE_PAL_LOAD 3

#define TILE8 1
#define TILE16 2
#define TILE32 3
#define TILE64 4

#endif
