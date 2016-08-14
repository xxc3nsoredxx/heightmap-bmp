#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

bmp_h create_bmp_header (FILE *input) {
    bmp_h ret;
    
    // -----TEMP-----
    
    ret.id = 0x424D & 0xFFFF;
    ret.size = 0x46000000 & 0xFFFFFFFF;
    ret.unused1 = 0 & 0xFFFF;
    ret.unused2 = 0 & 0xFFFF;
    ret.array_offset = 0x36000000 & 0xFFFFFFFF;

    // -----TEMP-----

    (void) *input;
    return ret;
}

dib_h create_dib_header () {
    dib_h ret;

    // -----TEMP-----
    
    ret.size_dib_h = 0x28000000 & 0xFFFFFFFF;
    ret.width = 0x02000000 & 0xFFFFFFFF;
    ret.height = 0x02000000 & 0xFFFFFFFF;
    ret.planes = 0x0100 & 0xFFFF;
    ret.bits_per_pixel = 0x1800 & 0xFFFF;
    ret.bi_rgb = 0 & 0xFFFFFFFF;
    ret.array_size = 0x10000000 & 0xFFFFFFFF;
    ret.ppm_h = 0x130B0000 & 0xFFFFFFFF;
    ret.ppm_v = 0x130B0000 & 0xFFFFFFFF;
    ret.colors_in_palette = 0 & 0xFFFFFFFF;
    ret.important_colors = 0 & 0xFFFFFFFF;

    // -----TEMP-----

    return ret;
}

pixel** create_pixel_array (int width, int height) {
    pixel **ret;

    printf ("Width: %d\nHeight: %d\n", width, height);

    ret = malloc (height * sizeof (pixel *));
    for (int row = 0; row < height; row++) {
        *(ret + row) = malloc (width * sizeof (pixel));
    }

    // -----TEMP-----
    
    (*(*(ret + 1) + 0)).red = 255;
    (*(*(ret + 1) + 1)).red = 255;
    (*(*(ret + 1) + 1)).green = 255;
    (*(*(ret + 1) + 1)).blue = 255;
    (*(*(ret + 0) + 0)).blue = 255;
    (*(*(ret + 0) + 1)).green = 255;

    // -----TEMP-----

    return ret;
}

void normal (int *val) {
    int p1 = (*val >> 24) & 0xFF;
    int p2 = (*val >> 16) & 0xFF;
    int p3 = (*val >> 8) & 0xFF;
    int p4 = *val & 0xFF;
    *val = p1 + (p2 << 8) + (p3 << 16) + (p4 << 24);
}
