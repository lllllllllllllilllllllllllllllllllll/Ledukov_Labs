#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef UNTITLED7_LIBR_H
#define UNTITLED7_LIBR_H
#pragma pack(push, 1)

struct bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

enum read_status  {
    READ_OK = 0,
    //READ_INVALID_SIGNATURE = 1,
    READ_INVALID_BITS = 2,
    READ_INVALID_HEADER = 3,
    //FILE_NOT_FOUND = 4
    /* коды других ошибок  */
};

enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR = 1
    /* коды других ошибок  */
};

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct image * create_img(const uint64_t w, const uint64_t h);
void destroy_img(struct image *img);

uint32_t numb_by_xy(const uint32_t width, const uint32_t x, const uint32_t y);
struct bmp_header create_bmp_header( const uint32_t w, const uint32_t h);

/* создаёт копию изображения, которая повёрнута на 90 градусов */
struct image rotate(const struct image source);

enum read_status read_header( FILE* in, struct bmp_header* bmpH1);
enum write_status write_header( FILE* file, struct bmp_header const bmpH2);
enum read_status from_bmp( FILE* in, struct image* img, struct bmp_header const bmpH1);
enum write_status to_bmp( FILE* file, struct image* img, struct bmp_header bmpH2 );
struct image * read_BMP(struct bmp_header* bmpH1);
uint8_t save_BMP(FILE *file, struct image* img2, const char *filename, struct bmp_header const bmpH2);
const char *read_filename(const char * filename);

struct pixel { uint8_t r, g, b; };
#endif //UNTITLED7_LIBR_H
