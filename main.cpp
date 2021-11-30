#include "tgaimage.h"

const TGAColor white = TGAColor(255,255,255,255);


int main (int argc, char* argv){
    TGAImage image(100,100, TGAImage::RGB);
    line(13,20,80,40,image,white);
}

int line( int x0, int x1, int y0, int y1, TGAImage &image, TGAColor color){
    //use linear interpolation to find steps, make sure that x increases faster than y
    //ensure that x0 < x
    bool steep = false;
    if(std::abs(x0-x1)< std::abs(y0-y1)){
        std::swap(x0, y0);
        std::swap(x1,y1);
        steep = true;
    }

    if(x0 > x1){
        std::swap(x0,x1);
        std::swap(y0,y1);
    }

    int dx = x1-x0;
    int dy = y1-y0;
    float gradient = std::abs(dy/dx);
    float ystep = 0;
    int y = y0;
    for (float x=x0; x<=x1; x++){
        steep == false ? image.set(x,y,color): image.set(y,x,color);
        ystep += gradient;
        if (ystep>.5){
            y += (y1>y0?1:-1);
            ystep -= 1.;
        }
    }
}

