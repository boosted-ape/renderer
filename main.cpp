#include "tgaimage.h"
#include "model.h"

const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);
Model *model = NULL;
const int width = 800;
const int height = 800;


int main (int argc, char* argv){
        if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }

    TGAImage image(width, height, TGAImage::RGB);
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int x1 = (v1.x+1.)*width/2.;
            int y1 = (v1.y+1.)*height/2.;
            line(x0, y0, x1, y1, image, white);
        }
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}

int line( int x0, int x1, int y0, int y1, TGAImage &image, TGAColor color){
    //use linear interpolation to find steps, make sure that x increases faster than y
    //ensure that x0 < x
    bool steep = false;
    if(std::abs(x0-x1)< std::abs(y0-y1)){
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if(x0 > x1){
        std::swap(x0,x1);
        std::swap(y0,y1);
    }

    int dx = x1-x0;
    int dy = y1-y0;
    int dy_doubled = 2*dy; //remove floats
    int ystep = 0;
    int y = y0;
    for (float x=x0; x<=x1; x++){
        steep == false ? image.set(x,y,color): image.set(y,x,color);
        ystep += dy_doubled;
        if (ystep> dx*2){
            y += (y1>y0?1:-1);
            ystep -= 2*dx;
        }
    }
}

