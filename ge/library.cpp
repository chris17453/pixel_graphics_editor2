#include <SDL2/SDL.h>
#include "library.h"
#include "scrollbar.h"
#include "drawing.h"
#include "palette.h"
#include "button.h"


extern SDL_Texture   *graphicsTextures[];
extern SDL_Renderer  *renderer;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int TILE_WIDTH;
extern int TILE_HEIGHT;

extern int GRAPHICS_LIB_SIZE;

int         LIBRARY_TILE_PADDING            =2;
extern int PALETTE_VIEW_WIDTH;

extern palette pal;

library_control::library_control(int left,int right,int top,int bottom):control(left,top,right,bottom,NULL){
    name="LIBRARY";
    this->borderType=BORDER_3D;
    rect pos=rect(left,right,top,bottom);
    this->anchor.left=RIGHT;
    this->anchor.right=RIGHT;
    this->anchor.top=BOTTOM;
    this->anchor.bottom=BOTTOM;
    this->internalHeight=TILE_HEIGHT;
    this->setPosition(pos);
    
    this->setScrollH((TILE_WIDTH+LIBRARY_TILE_PADDING)*GRAPHICS_LIB_SIZE);
    
    

    updateCoordinates();
    this->createCanvas();
}

void library_control::draw(){
   control::draw();
      
   
    //this->drawRect(0,0,20,20,pal.colorBars[0].colors[COLOR_BAR_DEPTH-1]);
   this->resetClip();
   
    int x=0;
    for(int a=0;a<GRAPHICS_LIB_SIZE;a++) {
        x=(TILE_WIDTH+LIBRARY_TILE_PADDING)*a;
        if(NULL!=graphicsTextures[a]) {
            this->renderTexture(graphicsTextures[a],x,0);
        }
       
    }
    this->present();
}

void library_control::updateMouse(){
    control::updateMouse();
}

