#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* loadFile(const char* filename,int *sz);
void maxValues(unsigned char *array, unsigned char *max1, unsigned char *max2);

int main()
{
	int sz;
	char *buf = loadFile("fontm.spr",&sz);
	unsigned char bloc_array[256];

	unsigned char max1,max2;

	printf("%d ok\n",sz);

	for(int i = 0; i < sz;i+=16)
	{

		for(int l = 0; l < 256;l++)
			bloc_array[l] = 0;

		for(int l = 0; l < 16;l++)
			bloc_array[buf[i+l]]++;

		maxValues(bloc_array,&max1,&max2);

	}

	return 0;
}

void maxValues(unsigned char *array, unsigned char *max1, unsigned char *max2)
{
    unsigned char largest = 0;
    unsigned char second_largest = 0;

    for (int i = 0; i < 256; i++)
	{
        if (array[i] > largest)
		{
            second_largest = largest;
            largest = array[i];
        } else if (array[i] > second_largest && array[i] != largest)
		{
            second_largest = array[i];
        }
		//printf("%d/%x\n",i,second_largest);
    }

	*max1 = largest;
	*max2 = second_largest;
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