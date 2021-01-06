#include "Libr.h"

void create_img(const uint64_t w, const uint64_t h, struct image *img){
    img->width = w;
    img->height = h;
    img->data = (struct pixel*)calloc(w*h, sizeof(struct pixel));
}
void destroy_img(struct image *img){
    if(img->data!=NULL){
        free(img->data);
    }
}
/* создаёт копию изображения, которая повёрнута на 90 градусов */
struct image rotate(struct image const source) {
    uint32_t my=source.width;
    uint32_t mx=source.height;
    struct pixel p;

    struct image* dest=(struct image*)calloc(1, sizeof(struct image));

    create_img(my, mx, dest);
    for (uint32_t x = 0; x < mx ; x++) {
        for (uint32_t y = 0; y < my; y++) {
            uint32_t n1=numb_by_xy(mx, x, y);//для источника
            uint32_t n2=numb_by_xy(my, my-y-1, x);//для адресата
            p=source.data[n1];
            dest->data[n2]=p;
        }
    }
    return *dest;
}
