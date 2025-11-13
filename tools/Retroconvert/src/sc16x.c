#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "retro.h"
#include <stdint.h>


void *sc16x(void *datas,int *sz)
{
	static uint8_t buffer[0x10000];
	uint16_t *header = datas;

	if( (header[0] != 0x6373) && (header[1] != 0x3631) )
	{
		printf("error no sc16 file %x %x \n",header[0],header[1]);
		return NULL;
	}

	//uint16_t bloc = header[2];

	uint16_t jsize =  header[3];

	//

	//printf("size: %d\n",size);
	uint8_t *data = datas;

	uint16_t pal1,pal2,pal3;
	uint16_t opal1,opal2,opal3;

	uint16_t i = 8;

	pal1 = data[i+1];
	pal2 = data[i+2];
	pal3 = data[i+3];
	i += 4;

	opal1 = i;
	i += pal1<<3;
	
	opal2 = i;
	i += pal2<<2;

	opal3 = i;
	i += pal3<<1;

	uint16_t sindex = 0;

	//printf("offset %x %x/%x/%x  /%x\n",(i),pal1,pal2,pal3,pal1+pal2);

	for(int j = 0;j < jsize;j++)
	{
		uint8_t index = data[i];

		//printf("%d: %x\n",i,index);

		if(index < 0xFB)
		{
			uint8_t type = 0;

			if(index >= pal1)
				type++;

			if(index >= (pal1+pal2) )
				type++;

			//printf("%d %d\n",index,type);

			if(type == 0)
			{
				uint16_t tmp = index<<3;
				memcpy(&buffer[sindex],&data[tmp+opal1],8);
				sindex+=8;
			}
			if(type == 1)
			{
				uint16_t tmp = (index-pal1)<<2;
				memcpy(&buffer[sindex],&data[tmp+opal2],4);
				sindex+=4;
			}
			if(type == 2)
			{
				uint16_t tmp = (index-pal1-pal2)<<1;
				memcpy(&buffer[sindex],&data[tmp+opal3],2);
				sindex+=2;
			}
		}else
		{
			
			if(index == 0xFC)
			{
				memcpy(&buffer[sindex],&data[i+1],2);
				sindex+=2;
				i+=2;
			}

			if(index == 0xFD)
			{
				memcpy(&buffer[sindex],&data[i+1],4);
				sindex+=4;
				i+=4;
			}

			if(index == 0xFE)
			{
				memcpy(&buffer[sindex],&data[i+1],8);
				sindex+=8;
				i+=8;
			}

			if(index == 0xFF)
			{
				uint16_t tmp = data[i+1]<<1;
				memcpy(&buffer[sindex],&data[i+2],tmp);
				sindex+=tmp;
				i+=(tmp)+1;
			}

			if(index == 0xFB)
			{
				uint16_t tmp = data[i+1]+1;
				for(int l = 0;l < tmp;l++)
				{
					memcpy(&buffer[sindex],&data[i+2],8);
					sindex+=8;
				}
				i+=9;
				//printf("%d , %d\n",tmp,tmp*8);
			}
		}

		i++;
	}

	*sz = sindex;
	return buffer;
}