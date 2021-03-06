#include "Libr.h"

int main(){
    struct bmp_header bmpH1,bmpH2;
    struct image* img1, *img2;
    img1=read_BMP(&bmpH1);
    if (img1!=NULL) {
        FILE* file;
        //const char* filename = "C:\\Ci\\2.bmp";
        const char* filename = read_filename("Input filename-destination: \n");
        file=fopen(filename, "wb");
        if (file == NULL) {
            fprintf(stderr,"Error writing to file <%s>", filename);
            fclose(file);
            destroy_img(img1);
            return WRITE_ERROR;
        }
        img2=create_img(img1->height, img1->width);
        *img2 = rotate(*img1);
        destroy_img(img1);
        bmpH2=create_bmp_header(img2->height, img2->width);
        return save_BMP(file, img2, filename, bmpH2);
    }
    return 1;
}//main




