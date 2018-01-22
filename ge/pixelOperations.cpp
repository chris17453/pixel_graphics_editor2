#include <stdlib.h>     /* srand, rand */
#include <math.h>     /* srand, rand */
#include "graphicOperations.h"
#include "pixelOperations.h"
#include "palette.h"

extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern int TILE_BYTES;
extern unsigned char*graphicsLibrary;
extern unsigned char*master;
extern int curentTileIndex;
extern int foreColor;
extern int foreBar;
extern SDL_Texture   *graphicsTextures[];

bool WRAP=true;

void getPixeCoords(int &x,int &y){
    if(WRAP) {
        while(x<0 || y<0 || y>=TILE_HEIGHT || x>=TILE_WIDTH) {
            if(x<0) x+=TILE_WIDTH;
            if(y<0) y+=TILE_HEIGHT;
            if(x>=TILE_WIDTH) x-=TILE_WIDTH;
            if(y>=TILE_WIDTH) y-=TILE_HEIGHT;
        }
    } else {
        if(x<0) x=0;
        if(y<0) y=0;
        if(x>=TILE_WIDTH) x=TILE_WIDTH-1;
        if(y>=TILE_WIDTH) y=TILE_HEIGHT-1;
    }
}

unsigned char getPixelC(int x,int y){
    getPixeCoords(x,y);
    int colorIndex=x+y*TILE_WIDTH;
    return master[colorIndex];
}

unsigned char gePixelB(int x,int y){
    getPixeCoords(x,y);
    int barIndex=x+y*TILE_WIDTH+TILE_BYTES;
    return master[barIndex];
}

void setPixelC(int x,int y,unsigned color){
    getPixeCoords(x,y);
    int indent=curentTileIndex*TILE_BYTES*2;
    int colorIndex=indent+x+y*TILE_WIDTH;
    graphicsLibrary[colorIndex]=color;
}

void setPixelB(int x,int y,unsigned char bar){
    getPixeCoords(x,y);
    int indent=curentTileIndex*TILE_BYTES*2;
    int barIndex=indent+x+y*TILE_WIDTH+TILE_BYTES;
    graphicsLibrary[barIndex]=bar;
}

void fill(int pX,int pY,void (*function)(int,int)){
    lib2Temp(curentTileIndex);
    for(int y=0;y<TILE_HEIGHT;y++) {
    for(int x=0;x<TILE_WIDTH;x++) {
        function(x,y);
    }//end x
    }//end y
    temp2Lib(curentTileIndex);
    SDL_DestroyTexture(graphicsTextures[curentTileIndex]);
    graphicsTextures[curentTileIndex]=libtoTexture(curentTileIndex);
}

void pen(int x,int y){
    int colorIndex=x+y*TILE_WIDTH;
    int barIndex=colorIndex+TILE_BYTES;
    setPixelC(x,y,foreColor);
    setPixelB(x,y,foreBar);
}
    
void dither(int x,int y){
    unsigned char c=getPixelC(x,y);
    char e=c+rand()%3-1;
    if(e>=COLOR_BAR_DEPTH) e=COLOR_BAR_DEPTH-1;
    if(e<0)  e=0;
    setPixelC(x,y,e);
}

void processConvolutionMatrix(float cm[9],float divisorOverride,int x,int y){
    float average=0;
    float divisor=(cm[0]+cm[1]+cm[2]+cm[3]+cm[4]+cm[5]+cm[6]+cm[7]+cm[8]);
    if(divisorOverride!=0) divisor=divisorOverride;
    if(cm[0]!=0) average+=getPixelC(x-1,y-1)*cm[0];     
    if(cm[1]!=0) average+=getPixelC(x+0,y-1)*cm[1];     
    if(cm[2]!=0) average+=getPixelC(x+1,y-1)*cm[2];
    if(cm[3]!=0) average+=getPixelC(x-1,y-0)*cm[3];     
    if(cm[4]!=0) average+=getPixelC(x+0,y-0)*cm[4];     
    if(cm[5]!=0) average+=getPixelC(x+1,y-0)*cm[5];
    if(cm[6]!=0) average+=getPixelC(x-1,y+1)*cm[6];     
    if(cm[7]!=0) average+=getPixelC(x+0,y+1)*cm[7];     
    if(cm[8]!=0) average+=getPixelC(x+1,y+1)*cm[8];
    
    if(average!=0 && divisor!=0) 
        average/=divisor;
    if(average<0) average=0;
    if(average>=COLOR_BAR_DEPTH) average=COLOR_BAR_DEPTH-1;
    unsigned char c=round(average);
        
    setPixelC(x,y,c);
}

void sharpen(int x,int y){
    float cm[9]={ 0 ,-2, 0,
                -2, 11,-2,
                 0 ,-2, 0};
    processConvolutionMatrix(cm,0,x,y);
}

void blur(int x,int y){
     float cm[9]= { 1, 1, 1,
                    1, 1, 1,
                    1, 1, 1};
    
    processConvolutionMatrix(cm,0,x,y);
}

void gausianBlur(int x,int y){
     float cm[9]= { 1, 2, 1,
                    2, 4, 2,
                    1, 2, 1};
    
    processConvolutionMatrix(cm,0,x,y);
}

void edgeDetect(int x,int y){
     float cm[9]= { -1,-1,-1,
                     0, 0, 0,
                     1, 1, 1};
    
    processConvolutionMatrix(cm,0,x,y);
}

void brighten(int x,int y){
     float cm[9]= { 0, 0    , 0,
                    0, 1    , 0,
                    0, 0    , 0};
    
    processConvolutionMatrix(cm,.8,x,y);
}

void darken(int x,int y){
     float cm[9]= { 0, 0  , 0,
                    0, 1  , 0,
                    0, 0  , 0};
    
    processConvolutionMatrix(cm,1.2,x,y);
}
