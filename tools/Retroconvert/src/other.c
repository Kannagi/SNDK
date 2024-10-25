#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "retro.h"



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


void writeFile(const char* filename,void *data,int filesize)
{
    if ( filesize <= 0 )
        return;

    FILE* file = fopen(filename, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Impossible to write the file : %s\n", filename);
        return;
    }

    fwrite(data, 1, filesize, file);

    fclose(file);
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
