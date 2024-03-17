#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeFile(const char* filename,int fileSize,unsigned char *buffer);
void* loadFile(const char* filename,int *sz);
void maxValues(unsigned char *array, unsigned char *max1, unsigned char *max2);

#define BLOCSIZE 16

int main(int argc, char *argv[])
{
	int sz;

	if(argc != 2)
		return -2;

	unsigned char *buf = loadFile(argv[1],&sz);
	if(buf == NULL)
		return -1;
	unsigned char bloc_array[256];

	unsigned char max1,max2;

	unsigned char *bufwrite = malloc(sz*2);

	printf("%d\n",sz);

	int filesize = 0;
	int iw = 0;


	int lignec = 0;
	int nzero = 0;

	for(int i = 0; i < sz;i+=BLOCSIZE)
	{
		for(int l = 0; l < 256;l++)
			bloc_array[l] = 0;

		for(int l = 0; l < BLOCSIZE;l++)
			bloc_array[buf[i+l]]++;
		
		maxValues(bloc_array,&max1,&max2);

		int lignec = filesize;

		unsigned int bindex = 0;

		for(int l = 0; l < BLOCSIZE;l++)
		{
			unsigned char tbloc = buf[i+l];

			if(tbloc == 0)
				bindex |= 0;
			else
			if(tbloc == max1)
				bindex |= 1<<(l<<1);
			else
			if(tbloc == max2)
				bindex |= 2<<(l<<1);
			else
			if(tbloc != 0)
				bindex |= 3<<(l<<1);
		}
		bufwrite[filesize+0] = bindex;
		bufwrite[filesize+1] = bindex>>8;
		bufwrite[filesize+2] = bindex>>16;
		bufwrite[filesize+3] = bindex>>24;
		filesize+=BLOCSIZE/4;

		if(bindex == 0)
			nzero++;

		if(max1 != 0)
		{
			bufwrite[filesize] = max1;
			filesize++;
		}
		if(max2 != 0)
		{
			bufwrite[filesize] = max2;
			filesize++;
		}

		for(int l = 0; l < BLOCSIZE;l++)
		{
			unsigned char tbloc = buf[i+l];
			if(
			(tbloc != 0) && (tbloc != max1) && (tbloc != max2)
			)
			{
				bufwrite[filesize] = tbloc;
				filesize++;
			}
			
		}
		//printf("%x %x\n,",i/16,bindex);
	}

	printf("%d %f / %d %d : %f\n",filesize ,(float)filesize/(float)sz,nzero,filesize-nzero*4,(float)(filesize-nzero*4)/(float)sz);

	char filename[256];
	sprintf(filename,"%s.bin",argv[1]);
	writeFile(filename,filesize,bufwrite);

	return 0;
}

#include <stdio.h>

void maxValues(unsigned char *array, unsigned char *max1, unsigned char *max2)
{
    unsigned char largest = 0,i1 = 0;
    unsigned char second_largest = 0,i2 = 0;

    for (int i = 1; i < 256; i++)
	{
        if (array[i] > largest)
		{
            largest = array[i];
			i1 = i;
        }
    }

	for (int i = 1; i < 256; i++)
	{
        if ( (array[i] > second_largest) && (i1 != i) )
		{
            second_largest = array[i];
			i2 = i;
        }
    }

	*max1 = i1;
	*max2 = i2;
}


void* loadFile(const char* filename,int *sz)
{
	int fileSize;
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Impossible to open the file : %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize <= 0)
    {
        fprintf(stderr, "Empty file: %s\n", filename);
        fclose(file);
        return NULL;
    }


    char* buffer = (char*)malloc(fileSize);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation error :%s /%d\n",filename,fileSize);
        fclose(file);
        return NULL;
    }

    int bytesRead = fread(buffer, 1, fileSize, file);
    if(bytesRead != fileSize)
    {
        fprintf(stderr, "Error reading file : %s\n", filename);
        fclose(file);
        free(buffer);
        return NULL;
    }

    fclose(file);

    *sz = fileSize;

    return buffer;
}

void writeFile(const char* filename,int fileSize,unsigned char *buffer)
{
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Impossible to open the file : %s\n", filename);
        return;
    }

    fwrite(buffer, 1, fileSize, file);

    fclose(file);
}