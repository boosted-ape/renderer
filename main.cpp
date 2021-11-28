#include "tgaimage.h"

const TGAColor white = TGAColor(255,255,255,255);


int main (int argc, char* argv){
    TGAImage image(100,100, TGAImage::RGB);
    line(13,20,80,40,image,white);
}

int line( int x0, int x1, int y0, int y1, TGAImage &image, TGAColor color){
    for (float t=0.; t<1.; t+=1){
        int x = x0 + (x1-x0)*t;
        int y = y0 + (y1-y0)*t;
        image.set(x,y,color);
    }
}