#include <SDL2/SDL.h>
#include "editor.h"
#include "drawing.h"
#include "palette.h"


extern int TILE_WIDTH;
extern int TILE_HEIGHT;

bool    inEditor                        =false;
int     editorX=0;
int     editorY=0;
int     EDITOR_OFFSET_X                 =15;
int     EDITOR_OFFSET_Y                 =30;
char    EDITOR_PIXEL_WIDTH_PADDING      =1;
char    EDITOR_PIXEL_HEIGHT_PADDING     =1;
char    EDITOR_PIXEL_WIDTH              =15;
char    EDITOR_PIXEL_HEIGHT             =15;
int     EDITOR_PITCH_X                  =(EDITOR_PIXEL_WIDTH+EDITOR_PIXEL_WIDTH_PADDING)*TILE_WIDTH;
int     EDITOR_PITCH_Y                  =(EDITOR_PIXEL_HEIGHT+EDITOR_PIXEL_HEIGHT_PADDING)*TILE_HEIGHT;

color   EDITOR_BOX_COLOR  (0xFF,0xEE,0xEE,0xEE);

extern bool inBox(int,int,int,int);
extern SDL_Texture* libtoTexture(int);

extern SDL_Texture   *graphicsTextures[62];
extern unsigned char *graphicsLibrary;
extern int curentTileIndex;
extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern int TILE_BYTES;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
extern int PALETTE_OFFSET_X;
extern int PALETTE_VIEW_WIDTH;
//extern palette_control *paletteCTRLPTR;

extern int foreColor;           //The current 2 selected colors.
extern int foreBar;
extern int backColor;
extern int backBar;

extern int xMouse;
extern int yMouse;
extern SDL_Renderer *renderer;
extern palette pal;

editor_control::editor_control(int left,int right,int top,int bottom):control(left,top,right,bottom,NULL){
    name="EDITOR";
    this->borderType=BORDER_3D;
    rect pos=rect(left,right,top,bottom);
    
    this->anchor.left=LEFT;
    this->anchor.right=RIGHT;
    this->anchor.top=TOP;
    this->anchor.bottom=BOTTOM;
    this->setPosition(pos);
    updateCoordinates();
    this->createCanvas();
}
void editor_control::preformAction(bool LEFT){         //draw pen?
    int indent=curentTileIndex*TILE_BYTES*2;
    int colorIndex=indent+editorX+editorY*TILE_WIDTH;
    int barIndex=colorIndex+TILE_BYTES;
    if(LEFT){
        graphicsLibrary[colorIndex]=foreColor;
        graphicsLibrary[barIndex]=foreBar;
    } else {
        graphicsLibrary[colorIndex]=backColor;
        graphicsLibrary[barIndex]=backBar;
    }

   SDL_DestroyTexture(graphicsTextures[curentTileIndex]);
   graphicsTextures[curentTileIndex]=libtoTexture(curentTileIndex);
}

void editor_control::drawCursor(){
    SDL_Rect rect;
    int x=(this->mouse.x)/(EDITOR_PIXEL_WIDTH+EDITOR_PIXEL_WIDTH_PADDING);
    int y=(this->mouse.y)/(EDITOR_PIXEL_HEIGHT+EDITOR_PIXEL_HEIGHT_PADDING);
    if(x<0) x=0;
    if(y<0) y=0;
    if(x>=TILE_WIDTH ) x=TILE_WIDTH-1;
    if(y>=TILE_HEIGHT) y=TILE_HEIGHT-1;
    
    editorX=x;
    editorY=y;
    
    rect.x = x*(EDITOR_PIXEL_WIDTH +EDITOR_PIXEL_WIDTH_PADDING);
    rect.y = y*(EDITOR_PIXEL_HEIGHT+EDITOR_PIXEL_HEIGHT_PADDING);
    rect.w = EDITOR_PIXEL_WIDTH+1;
    rect.h = EDITOR_PIXEL_HEIGHT+1;
    color c=color(0xFF,0,0,0);
    this->drawRect(rect.x,rect.y,rect.x+rect.w,rect.y+rect.h,c);
}

void editor_control::updateMouse(){
    control::updateMouse();
    if(this->mouse.inWindow){
        
        if(this->mouse.LEFT)  { 
            preformAction(true);
        }
        if(this->mouse.RIGHT) {
            preformAction(false);
        }
    }
}

void editor_control::draw(){
    control::draw();
        
    unsigned int p;
    int indent=curentTileIndex*TILE_BYTES*2;
    for(int y=0;y<TILE_HEIGHT;y++) {
    for(int x=0;x<TILE_WIDTH;x++) {
        p=x+y*TILE_WIDTH;
        SDL_Rect rect;
        rect.x = x*(EDITOR_PIXEL_WIDTH+EDITOR_PIXEL_WIDTH_PADDING);
        rect.y = y*(EDITOR_PIXEL_HEIGHT+EDITOR_PIXEL_HEIGHT_PADDING);
        rect.w = EDITOR_PIXEL_WIDTH;
        rect.h = EDITOR_PIXEL_HEIGHT;
        char color=graphicsLibrary[indent+x+y*TILE_WIDTH];
        char colorBar=graphicsLibrary[indent+TILE_BYTES+x+y*TILE_WIDTH];
        this->drawRect(rect.x,rect.y,rect.x+rect.w,rect.y+rect.h,pal.colorBars[colorBar].colors[color]);
    }
    }
    if(this->mouse.inWindow) drawCursor();
}

