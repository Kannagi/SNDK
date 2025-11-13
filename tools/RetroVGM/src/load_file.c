


#include <stdio.h>
#include <stdlib.h>
#include "vgm.h"

void load_option(VGM *vgm)
{
    FILE *file;
    char line[64];
    int number,number1,number2,number3;

    file = fopen("option.txt", "r");
    if (file == NULL)
    {
        printf("Error : file open ! (option.txt)\n");
        return;
    }
    int i = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *ptr = strchr(line, ':');

        if (ptr != NULL)
        {
            ptr++; //":"
            if (sscanf(ptr, "%x", &number) == 1)
            {
				vgm->spc700[i] = number;
            }
        }
        i++;

        if(i == 17) break;
    }

    fgets(line, sizeof(line), file);

    i = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *ptr = strchr(line, ':');

        if (ptr != NULL)
        {
            ptr++; //":"
            if (sscanf(ptr, "0x%x,0x%x,0x%x",&number1,&number2,&number3) == 3)
            {
                vgm->adsr1[i] = number1;
                vgm->adsr2[i] = number2;
                vgm->gain[i]  = number3;
            }
        }
        i++;

        if(i == 32) break;
    }

    fclose(file);
}
