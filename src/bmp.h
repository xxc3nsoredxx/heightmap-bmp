#ifndef __XXC3NSOREDXX_BMP_H_20160812_2126
#define __XXC3NSOREDXX_BMP_H_20160812_2126

typedef struct bmp_h {
    int id; // ID field - 2 bytes
    int size; // Size of BMP file - 4 bytes
    int unused1; // Unused - 2 bytes
    int unused2; // Unused - 2 bytes
    int array_offset; // Offset for pixel array (54) - 4 bytes
} bmp_h; // 14 bytes

typedef struct dib_h {
    int size_dib_h; // Size of DIB header - 4 bytes
    int width; // Width of BMP in pixels - 4 bytes
    int height; // Height of BMP in pixels - 4 bytes
    int planes; // Color planes used (1) - 2 bytes
    int bits_per_pixel; // Bits per pixel (24: 255,255,255) - 2 bytes
    int bi_rgb; // Pixle compression (0: none) - 4 bytes
    int array_size; // Size of pixel data + pads - 4 bytes
    int ppm_h; // Pixels/meter horizontal (2835) - 4 bytes |
    int ppm_v; // Pixels/meter vertical (2835) - 4 bytes   | 72 dpi
    int colors_in_palette; // Number of colors in palette (0) - 4 bytes
    int important_colors; // Number of important colors (0) - 4 bytes
} dib_h; // 40 bytes

typedef struct pixel {
    int red; // 0-255 - 3 bytes
    int green; // -//-
    int blue; // -//-
} pixel;

typedef struct bmp_file {
    bmp_h bmp_header;
    dib_h dib_header;
    pixel **pixel_array;
} bmp_file;

bmp_h create_bmp_header (FILE *);
dib_h create_dib_header ();
pixel** create_pixel_array (int, int);

void normal (int *);

#endif
