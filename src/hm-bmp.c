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

    FILE *output = fopen (output_name, "wb");
    if (!output) {
        printf ("Unable to Open File -- %s\n", output_name);
        fclose (input);
        return -1;
    }

    bmp_h bmp_header = create_bmp_header ();
    dib_h dib_header = create_dib_header (input);

    int size = dib_header.array_size;
    flip_endian (&size);
    size += 54;
    bmp_header.size = size;

    printf ("\nBMP Header:\n");
    printf ("ID: 0x%02X %02X\n", ((bmp_header.id >> 8) & 0xFF), (bmp_header.id & 0xFF));
    int sn = bmp_header.size;
    int s1 = (sn >> 24) & 0xFF;
    int s2 = (sn >> 16) & 0xFF;
    int s3 = (sn >> 8) & 0xFF;
    int s4 = sn & 0xFF;
    flip_endian (&sn);
    printf ("Size: 0x%02X %02X %02X %02X (%d bytes)\n", s1, s2, s3, s4, sn);
    printf ("Unused: 0x%02X %02X\n", ((bmp_header.unused1 >> 8) & 0xFF), (bmp_header.unused1 & 0xFF));
    printf ("Unused: 0x%02X %02X\n", ((bmp_header.unused2 >> 8) & 0xFF), (bmp_header.unused2 & 0xFF));
    int aon = bmp_header.array_offset;
    int ao1 = (aon >> 24) & 0xFF;
    int ao2 = (aon >> 16) & 0xFF;
    int ao3 = (aon >> 8) & 0xFF;
    int ao4 = aon & 0xFF;
    flip_endian (&aon);
    printf ("Array Offset: 0x%02X %02X %02X %02X (%d bytes)\n", ao1, ao2, ao3, ao4, aon);

    printf ("\nDIB Header:\n");
    int dsn = dib_header.size_dib_h;
    int ds1 = (dsn >> 24) & 0xFF;
    int ds2 = (dsn >> 16) & 0xFF;
    int ds3 = (dsn >> 8) & 0xFF;
    int ds4 = dsn & 0xFF;
    flip_endian (&dsn);
    printf ("DIB Size: 0x%02X %02X %02X %02X (%d bytes)\n", ds1, ds2, ds3, ds4, dsn);
    int wn = dib_header.width;
    int w1 = (wn >> 24) & 0xFF;
    int w2 = (wn >> 16) & 0xFF;
    int w3 = (wn >> 8) & 0xFF;
    int w4 = wn & 0xFF;
    flip_endian (&wn);
    printf ("BMP Width: 0x%02X %02X %02X %02X (%d pixels)\n", w1, w2, w3, w4, wn);
    int hn = dib_header.height;
    int h1 = (hn >> 24) & 0xFF;
    int h2 = (hn >> 16) & 0xFF;
    int h3 = (hn >> 8) & 0xFF;
    int h4 = hn & 0xFF;
    flip_endian (&hn);
    printf ("BMP Height: 0x%02X %02X %02X %02X (%d pixels)\n", h1, h2, h3, h4, hn);
    int p1 = (dib_header.planes >> 8) & 0xFF;
    int p2 = dib_header.planes & 0xFF;
    printf ("Color Planes: 0x%02X %02X (%d plane)\n", p1, p2, p1);
    int bpp1 = (dib_header.bits_per_pixel >> 8) & 0xFF;
    int bpp2 = dib_header.bits_per_pixel & 0xFF;
    printf ("Bits/Pixel: 0x%02X %02X (%d bits)\n", bpp1, bpp2, bpp1);
    int bi1 = (dib_header.bi_rgb >> 24) & 0xFF;
    int bi2 = (dib_header.bi_rgb >> 16) & 0xFF;
    int bi3 = (dib_header.bi_rgb >> 8) & 0xFF;
    int bi4 = dib_header.bi_rgb & 0xFF;
    printf ("Pixel Compression: 0x%02X %02X %02X %02X\n", bi1, bi2, bi3, bi4);
    int asn = dib_header.array_size;
    int as1 = (asn >> 24) & 0xFF;
    int as2 = (asn >> 16) & 0xFF;
    int as3 = (asn >> 8) & 0xFF;
    int as4 = asn & 0xFF;
    flip_endian (&asn);
    printf ("Pixel Data: 0x%02X %02X %02X %02X (%d bytes)\n", as1, as2, as3, as4, asn);
    int ppmhn = dib_header.ppm_h;
    int ppmh1 = (ppmhn >> 24) & 0xFF;
    int ppmh2 = (ppmhn >> 16) & 0xFF;
    int ppmh3 = (ppmhn >> 8) & 0xFF;
    int ppmh4 = ppmhn & 0xFF;
    flip_endian (&ppmhn);
    printf ("Pixels/Meter Horizontal: 0x%02X %02X %02X %02X (%d ppm)\n", ppmh1, ppmh2, ppmh3, ppmh4, ppmhn);
    int ppmvn = dib_header.ppm_v;
    int ppmv1 = (ppmvn >> 24) & 0xFF;
    int ppmv2 = (ppmvn >> 16) & 0xFF;
    int ppmv3 = (ppmvn >> 8) & 0xFF;
    int ppmv4 = ppmvn & 0xFF;
    flip_endian (&ppmvn);
    printf ("Pixels/Meter Vertical: 0x%02X %02X %02X %02X (%d ppm)\n", ppmv1, ppmv2, ppmv3, ppmv4, ppmvn);
    int cipn = dib_header.colors_in_palette;
    int cip1 = (cipn >> 24) & 0xFF;
    int cip2 = (cipn >> 16) & 0xFF;
    int cip3 = (cipn >> 8) & 0xFF;
    int cip4 = cipn & 0xFF;
    flip_endian (&cipn);
    printf ("Colors in Palette: 0x%02X %02X %02X %02X (%d colors)\n", cip1, cip2, cip3, cip4, cipn);
    int icn = dib_header.important_colors;
    int ic1 = (icn >> 24) & 0xFF;
    int ic2 = (icn >> 16) & 0xFF;
    int ic3 = (icn >> 8) & 0xFF;
    int ic4 = icn & 0xFF;
    printf ("Important Colors: 0x%02X %02X %02X %02X (%d colors)\n", ic1, ic2, ic3, ic4, icn);

    pixel **pixel_array = create_pixel_array (input, wn, hn);
    
    bmp_file output_data = {
        bmp_header,
        dib_header,
        pixel_array
    };

    write_data (output, output_data);

    fclose (input);
    fclose (output);

    for (int row = 0; row < hn; row++) {
        free (*(pixel_array + row));
    }
    free (pixel_array);

    return 0;
}
