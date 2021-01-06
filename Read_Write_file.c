#include "Libr.h"

enum read_status read_header( FILE* in,struct bmp_header* bmpH1) {
    size_t str=fread(bmpH1, sizeof(struct bmp_header), 1, in);
    if ((str!=1) || (bmpH1->bfType != 19778) || (bmpH1->biBitCount != 24)) {
        fprintf(stderr,"Corrupted file: ");
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}//read_header

enum write_status write_header( FILE* file, struct bmp_header const bmpH2){
    size_t st;
    st = fwrite(&bmpH2, sizeof(bmpH2), 1, file);
    if (st==1){
        return WRITE_OK;
    }
    return WRITE_ERROR;
}//write_header

enum read_status from_bmp( FILE* in, struct image* img, struct bmp_header const bmpH1) {
    uint32_t mx = bmpH1.biWidth;
    uint32_t my = bmpH1.biHeight;
    uint32_t mx3 = (3*mx+3) & (-4);
    size_t st;
    //áç¨âë¢ ­¨¥ ä ©« 
    for(uint32_t i = 0; i < my; ++i){
        uint32_t n=numb_by_xy(mx, 0, i);
        st=fread(&(img->data[n]), sizeof(struct pixel), mx, in);
        if (st!=mx){
            return READ_INVALID_BITS;
        }
        uint32_t ost=mx3-mx*3;
        uint64_t tmp=0;
        if (fread(&tmp, sizeof(uint8_t), ost, in)!=ost){
            return READ_INVALID_BITS;
        }
    }
    return READ_OK;
}//from_bmp

enum write_status to_bmp( FILE* file, struct image* img,struct bmp_header bmpH2 ){
    uint32_t mx = bmpH2.biWidth;
    uint32_t my = bmpH2.biHeight;
    uint32_t mx3 = (3*mx+3) & (-4);
    for (uint32_t j = 0; j < my; j++) {
        for (uint32_t i = 0; i < mx; i++) {
            uint32_t n=numb_by_xy(mx, i, j);
            fwrite(&img->data[n], sizeof(struct pixel), 1, file);
        }
        uint32_t ost=mx3-mx*3;
        uint64_t tmp=0;
        if (fread(&tmp, sizeof(uint8_t), ost, file)!=ost){
            return WRITE_ERROR;
        }
    }
    return WRITE_OK;
}//to_bmp

uint8_t read_BMP(struct bmp_header* bmpH1, struct image *img1) {
    //const char* filename= "C:\\Ci\\11.bmp";
    const char* filename= read_filename("Input filename-source: \n");
    FILE* file;
    file=fopen(filename, "rb");
    if(file == NULL) {
        printf("File <%s> not found", filename);
        return 1;
    }
    enum read_status rs=read_header(file,bmpH1);
    if (rs==READ_OK){
        uint32_t my = bmpH1->biWidth;
        uint32_t mx = bmpH1->biHeight;
        create_img(mx, my, img1);
        rs=from_bmp( file, img1, *bmpH1);
        fclose(file);
        if (rs==READ_OK) {
            return 0;
        }
        fprintf(stderr,"Error image in file <%s>", filename);
        destroy_img(img1);
    }
    fprintf(stderr,"Error Header in file <%s>", filename);
    fclose(file);
    return 1;
}//read_BMP

uint8_t save_BMP(FILE *file, struct image* img2, const char *filename, struct bmp_header const bmpH2) {
    enum write_status ws = write_header(file, bmpH2);
    if (ws==WRITE_OK){
        ws = to_bmp(file, img2, bmpH2);
        destroy_img(img2);
        fclose(file);
        if (ws==WRITE_OK){
            printf("The file <%s> was created successfully", filename);
            return 0;
        }
        fprintf(stderr,"Error writing to file <%s>", filename);
        return 5;
    }
    destroy_img(img2);
    fprintf(stderr,"Error writing to file <%s>", filename);
    fclose(file);

    return 4;
}//save_BMP
