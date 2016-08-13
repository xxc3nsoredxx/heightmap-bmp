#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main (int argc, char **argv) {
    if (argc < 3) {
        printf ("Usage:\n");
        printf ("\thm-bmp [input-name] [output-name]\n");
        return -1;
    }

    char *input_name = *(argv + 1);
    char *output_name = *(argv + 2);

    FILE *input = fopen (input_name, "r");
    if (!input) {
        printf ("File Not Found -- %s\n", input_name);
        return -1;
    }

    FILE *output = fopen (output_name, "w");
    if (!output) {
        printf ("Unable to Open File -- %s\n", output_name);
        return -1;
    }

    bmp_h bmp_header = create_bmp_header (input);
    printf ("ID: 0x%02X %02X\n", ((bmp_header.id >> 8) & 0xFF), (bmp_header.id & 0xFF));
    printf ("Size: 0x%02X %02X %02X %02X (%d bytes)\n", ((bmp_header.size >> 24) & 0xFF), ((bmp_header.size >> 16) & 0xFF), ((bmp_header.size >> 8) & 0xFF), (bmp_header.size & 0xFF), (bmp_header.size & 0xFFFFFFFF));
    printf ("Unused: 0x%02X %02X\n", ((bmp_header.unused1 >> 8) & 0xFF), (bmp_header.unused1 & 0xFF));
    printf ("Unused: 0x%02X %02X\n", ((bmp_header.unused2 >> 8) & 0xFF), (bmp_header.unused2 & 0xFF));
    printf ("Array Offset: 0x%02X %02X %02X %02X (%d bytes)\n", ((bmp_header.array_offset >> 24) & 0xFF), ((bmp_header.array_offset >> 16) & 0xFF), ((bmp_header.array_offset >> 8) & 0xFF), (bmp_header.array_offset & 0xFF), (bmp_header.array_offset & 0xFFFFFFFF));
    
    return 0;
}
