

#include <stdio.h>
#include <stdlib.h>
#include "retro.h"

unsigned char buffer_pixels[0x10000];

void init_image(RETRO_Image* image,int w,int h)
{
    image->w = w;
    image->h = h;
    image->pixels = buffer_pixels;
    image->BytesPerPixel = 4;
}

void blit_32b(RETRO_Image *in_image,RETRO_Image* out_image,int py,int px,int w,int h)
{
    int l = px + (py*in_image->w);
    int i = 0;
    int ix,lx;

    unsigned int *in_pixels  = in_image->pixels;
    unsigned int *out_pixels = out_image->pixels;

    for(int y = 0; y < h;y++)
    {
        lx = l;
        ix = i;
        for(int x = 0; x < w;x++)
        {
            out_pixels[ix] = in_pixels[lx];
            lx++;
            ix++;
        }
        i += out_image->w;
        l += in_image->w;
    }

}
