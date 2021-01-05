#include "Libr.h"

uint32_t numb_by_xy(const uint32_t width, const uint32_t x, const uint32_t y){
    return width*y+x;
}

void create_bmp_header( const uint32_t w, const uint32_t h, struct bmp_header* bmpH2){
    char* str = "BM";
    bmpH2->bfType=str[1]*256+str[0];
    uint32_t mx3 = (3*w+3) & (-4);
    bmpH2->bfileSize=54+mx3*h;
    bmpH2->bfReserved=0;
    bmpH2->bOffBits=54;
    bmpH2->biSize=40;
    bmpH2->biWidth=h;
    bmpH2->biHeight=w;
    bmpH2->biPlanes=1;
    bmpH2->biBitCount=24;
    bmpH2->biCompression=0;
    bmpH2->biSizeImage=bmpH2->bfileSize-bmpH2->bOffBits;
    bmpH2->biXPelsPerMeter=4724;
    bmpH2->biYPelsPerMeter=4724;
    bmpH2->biClrUsed=0;
    bmpH2->biClrImportant=0;
}
