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
