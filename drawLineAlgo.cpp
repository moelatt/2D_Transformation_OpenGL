#include "main.h"
using namespace std;

void DdaAlgorithm(double xStart, double yStart, double xEnd, double yEnd, int objectIndex){
    int dx = xEnd - xStart, dy = yEnd - yStart, steps, k = 0;
    double xinc, yinc, x = xStart, y = yStart;
    if (fabs(dx) > fabs(dy)){
        steps = fabs(dx);
    }
    else{
        steps = fabs(dy);
    }
    xinc = (double)dx/(double)steps;
    yinc = (double)dy/(double)steps;
    polygonPixel(roundOff(x), roundOff(y), objectIndex);
    
    while(k < steps){
        x = x + xinc;
        y = y + yinc;
        polygonPixel(roundOff(x), roundOff(y), objectIndex);
        k = k + 1;
    }
}
int absolute (int num){
    return ( (num>0) ? num : ( num * (-1)));
}
void BresenhamAlgorithm(double xStart, double yStart, double xEnd, double yEnd, int objectIndex){
      // Find Delta
    float dx = xEnd-xStart;
    float dy = yEnd-yStart;

    int Xs = (dx>=0) ? 1 : (-1);
    int Ys = (dy>=0) ? 1 : (-1);

    float x = xStart;
    float y = yStart;

    int isSwaped = 0;

    if(absolute(dy) > absolute(dx)){
        float tdx = dx;
        dx =dy;
        dy = tdx;
        isSwaped = 1;
    }

    float p = 2*(absolute(dy)) - absolute(dx);

    polygonPixel(x,y, objectIndex);

    for(int i = 0; i<= absolute(dx);i++){
        if(p < 0){
            if(isSwaped == 0){
                x = x + Xs;
                polygonPixel(x,y, objectIndex);
            }
            else{
                y = y+Ys;
                polygonPixel(x,y, objectIndex);
            }
            p = p + 2*absolute(dy);
        }
        else{
            x = x+Xs;
            y = y+Ys;
            polygonPixel(x,y, objectIndex);
            p = p + 2*absolute(dy) - 2*absolute(dx);
        }
    }
}