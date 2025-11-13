#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 0x8000
#define DEST_OFFSET1 0x18000
#define DEST_OFFSET2 0x20000

unsigned char block1[BLOCK_SIZE];
unsigned char block2[BLOCK_SIZE];

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <snes_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen("demo.smc", "rb+");
    if (!file) {
        printf("File open failed\n");
        return 1;
    }

    FILE *file2 = fopen("SAMPLE_PACK.brr", "rb");
    if (!file2) {
        printf("File open failed\n");
        return 1;
    }

    FILE *file1 = fopen(argv[1], "rb");
    if (!file1) {
        printf("File open failed\n");
        return 1;
    }

    fread(block1, 1, BLOCK_SIZE, file1);
    fread(block2, 1, BLOCK_SIZE, file2);

    fseek(file, DEST_OFFSET1, SEEK_SET);
    fwrite(block1, 1, BLOCK_SIZE, file);

    fseek(file, DEST_OFFSET2, SEEK_SET);
    fwrite(block2, 1, BLOCK_SIZE, file);

    fclose(file);
    fclose(file1);
    fclose(file2);

    return 0;
}
