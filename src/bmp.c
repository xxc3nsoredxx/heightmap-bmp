#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

bmp_h create_bmp_header () {
    bmp_h ret;
    
    ret.id = 0x424D & 0xFFFF;
    // Replaced after create_dib_header () is run
    ret.size = -1;
    ret.unused1 = 0 & 0xFFFF;
    ret.unused2 = 0 & 0xFFFF;
    ret.array_offset = 0x36000000 & 0xFFFFFFFF;

    return ret;
}

dib_h create_dib_header (FILE *input) {
    dib_h ret;

    int cols;
    fscanf (input, "%*s %d", &cols);
    int rows;
    fscanf (input, "%*s %d", &rows);
    int pads = ((cols * 3) % 4) * rows;
    int data_size = (rows * cols * 3) + pads;

    fscanf (input, "%*s %*s");
    fscanf (input, "%*s %*s");
    fscanf (input, "%*s %*s");
    fscanf (input, "%*s %*s");

    ret.size_dib_h = 0x28000000 & 0xFFFFFFFF;

    flip_endian (&cols);
    ret.width = cols & 0xFFFFFFFF;

    flip_endian (&rows);
    ret.height = rows & 0xFFFFFFFF;

    ret.planes = 0x0100 & 0xFFFF;

    ret.bits_per_pixel = 0x1800 & 0xFFFF;

    ret.bi_rgb = 0 & 0xFFFFFFFF;

    flip_endian (&data_size);
    ret.array_size = data_size & 0xFFFFFFFF;

    ret.ppm_h = 0x130B0000 & 0xFFFFFFFF;

    ret.ppm_v = 0x130B0000 & 0xFFFFFFFF;

    ret.colors_in_palette = 0 & 0xFFFFFFFF;

    ret.important_colors = 0 & 0xFFFFFFFF;

    return ret;
}

void val_to_rgb (double, int *, int *, int *);

pixel** create_pixel_array (FILE *input, int width, int height) {
    pixel **ret;

    ret = malloc (height * sizeof (pixel *));
    for (int row = 0; row < height; row++) {
        *(ret + row) = malloc (width * sizeof (pixel));
    }

    char *val_str = malloc (100);
    double val = 0;
    int r = 0, g = 0, b = 0;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            fscanf (input, "%s", val_str);
            sscanf (val_str, "%lf", &val);
            printf ("VAL_1: %f ", val);
            val_to_rgb (val, &r, &g, &b);
            printf ("RGB: %d %d %d\n", r, g, b);
            (*(ret + row) + col) -> red = r;
            (*(ret + row) + col) -> green = g;
            (*(ret + row) + col) -> blue = b;
        }
    }

    free (val_str);

    return ret;
}

void write_bmp_h (FILE *, bmp_h);
void write_dib_h (FILE *, dib_h);
void write_pixel (FILE *, pixel);
void pad (FILE *, int);
void add_to_array (char *, int *, int, int);

void write_data (FILE *output_file, bmp_file output_data) {
    write_bmp_h (output_file, output_data.bmp_header);
    write_dib_h (output_file, output_data.dib_header);

    int height = output_data.dib_header.height;
    int width = output_data.dib_header.width;
    flip_endian (&height);
    flip_endian (&width);
    int pad_amount = (width * 3) % 4;

    for (int r_pos = height - 1; r_pos >= 0; r_pos--) {
        pixel *row = *(output_data.pixel_array + r_pos);
        for (int c_pos = 0; c_pos < width; c_pos++) {
            write_pixel (output_file, *(row + c_pos));
        }
        pad (output_file, pad_amount);
    }
}

void flip_endian (int *val) {
    int p1 = (*val >> 24) & 0xFF;
    int p2 = (*val >> 16) & 0xFF;
    int p3 = (*val >> 8) & 0xFF;
    int p4 = *val & 0xFF;
    *val = p1 + (p2 << 8) + (p3 << 16) + (p4 << 24);
}

// -----PRIVATE FUNCTIONS-----

void val_to_rgb (double val, int *r, int *g, int *b) {
    val = 1 - val;
    printf ("VAL_2: %f ", val);

    if (val >= 0 && val <= 0.200) {
        *r = 255;
        *g = (val / 0.200) * 255;
        *b = 0;
    } else if (val > 0.200 && val <= 0.400) {
        val -= 0.200;
        *r = ((1 - val) / 0.200) * 255;
        *g = 255;
        *b = 0;
    } else if (val > 0.400 && val <= 0.600) {
        val -= 0.400;
        *r = 0;
        *g = 255;
        *b = (val / 0.200) * 255;
    } else if (val > 0.600 && val <= 0.800) {
        val -= 0.600;
        *r = 0;
        *g = (1 - val / 0.200) * 255;
        *b = 255;
    } else if (val > 0.800 && val <= 1.00) {
        val -= 0.800;
        *r = (val / 0.200) * 255;
        *g = 0;
        *b = 255;
    } else {
        *r = 128;
        *g = 128;
        *b = 128;
    }
}

void write_bmp_h (FILE *output_file, bmp_h bmp_header) {
    char *bmp_h_array = malloc (14);
    int pos = 0;

    add_to_array (bmp_h_array, &pos, bmp_header.id, 2);
    add_to_array (bmp_h_array, &pos, bmp_header.size, 4);
    add_to_array (bmp_h_array, &pos, bmp_header.unused1, 2);
    add_to_array (bmp_h_array, &pos, bmp_header.unused2, 2);
    add_to_array (bmp_h_array, &pos, bmp_header.array_offset, 4);

    fwrite (bmp_h_array, 1, 14, output_file);

    free (bmp_h_array);
}

void write_dib_h (FILE *output_file, dib_h dib_header) {
    int size = dib_header.size_dib_h;
    flip_endian (&size);
    char *dib_h_array = malloc (size);
    int pos = 0;

    add_to_array (dib_h_array, &pos, dib_header.size_dib_h, 4);
    add_to_array (dib_h_array, &pos, dib_header.width, 4);
    add_to_array (dib_h_array, &pos, dib_header.height, 4);
    add_to_array (dib_h_array, &pos, dib_header.planes, 2);
    add_to_array (dib_h_array, &pos, dib_header.bits_per_pixel, 2);
    add_to_array (dib_h_array, &pos, dib_header.bi_rgb, 4);
    add_to_array (dib_h_array, &pos, dib_header.array_size, 4);
    add_to_array (dib_h_array, &pos, dib_header.ppm_h, 4);
    add_to_array (dib_h_array, &pos, dib_header.ppm_v, 4);
    add_to_array (dib_h_array, &pos, dib_header.colors_in_palette, 4);
    add_to_array (dib_h_array, &pos, dib_header.important_colors, 4);
    
    fwrite (dib_h_array, 1, size, output_file);

    free (dib_h_array);
}

void write_pixel (FILE *output_file, pixel p) {
    char *pixel = malloc (3);

    *(pixel + 0) = p.blue & 0xFF;
    *(pixel + 1) = p.green & 0xFF;
    *(pixel + 2) = p.red & 0xFF;

    fwrite (pixel, 1, 3, output_file);

    free (pixel);
}

void pad (FILE *output_file, int bytes) {
    char *pad_array = malloc (bytes);

    for (int cx = 0; cx < bytes; cx++) {
        *(pad_array + cx) = 0;
    }

    fwrite (pad_array, 1, bytes, output_file);

    free (pad_array);
}

void add_to_array (char *array, int *pos, int src, int bytes) {
    for (int cx = ((bytes - 1) * 8); cx >= 0; cx -= 8) {
        *(array + *pos) = (src >> cx) & 0xFF;
        *pos += 1;
    }
}
