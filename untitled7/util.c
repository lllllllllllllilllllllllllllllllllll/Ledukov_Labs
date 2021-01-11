#include "Libr.h"

uint32_t numb_by_xy(const uint32_t width, const uint32_t x, const uint32_t y){
    return width*y+x;
}

struct bmp_header create_bmp_header( const uint32_t w, const uint32_t h){
    struct bmp_header bmpH;
    char* str = "BM";
    bmpH.bfType=str[1]*256+str[0];
    uint32_t mx3 = (3*w+3) & (-4);
    bmpH.bfileSize=54+mx3*h;
    bmpH.bfReserved=0;
    bmpH.bOffBits=54;
    bmpH.biSize=40;
    bmpH.biWidth=h;
    bmpH.biHeight=w;
    bmpH.biPlanes=1;
    bmpH.biBitCount=24;
    bmpH.biCompression=0;
    bmpH.biSizeImage=bmpH.bfileSize-bmpH.bOffBits;
    bmpH.biXPelsPerMeter=4724;
    bmpH.biYPelsPerMeter=4724;
    bmpH.biClrUsed=0;
    bmpH.biClrImportant=0;
    return bmpH;
}
