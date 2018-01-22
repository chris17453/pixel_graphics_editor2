#include "navigation.h"
#include "pixelOperations.h"

extern int curentTileIndex;
extern int GRAPHICS_LIB_SIZE;

navigation_control::navigation_control(int left,int right,int top,int bottom):control(left,top,right,bottom,NULL){
    name="LIBRARY";
    this->displayInfo=true;         //show frame etc...
    
    this->borderType=BORDER_3D;
    rect pos=rect(left,right,top,bottom);
    this->anchor.left=RIGHT;
    this->anchor.right=RIGHT;
    this->anchor.top=TOP;
    this->anchor.bottom=BOTTOM;
    //this->internalHeight=TILE_HEIGHT;
    this->setPosition(pos);
    updateCoordinates();
    this->createCanvas();
    
 
    int y=00;
    int w=100,h=30;
    int ym=h+10;
    button *bNext   =new button(0,y+0 *ym,w,h,(char *)"Next");                 bNext   ->buttonEventCallBack .connectCallback  (  [this] { return this->fNext(); }   );
    button *bLast   =new button(0,y+1 *ym,w,h,(char *)"Last");                 bLast   ->buttonEventCallBack .connectCallback  (  [this] { return this->fLast(); }   );
    button *bOpen   =new button(0,y+2 *ym,w,h,(char *)"Open");                 bOpen   ->buttonEventCallBack .connectCallback  (  [this] { return this->fOpen(); }   );
    button *bSave   =new button(0,y+3 *ym,w,h,(char *)"Save");                 bSave   ->buttonEventCallBack .connectCallback  (  [this] { return this->fSave(); }   );
    button *bDither =new button(0,y+4 *ym,w,h,(char *)"Dither");               bDither ->buttonEventCallBack .connectCallback  (  [this] { return this->fDither(); }   );
    button *bBlur   =new button(0,y+5 *ym,w,h,(char *)"Blur");                 bBlur   ->buttonEventCallBack .connectCallback  (  [this] { return this->fBlur(); }   );
    button *bDarken =new button(0,y+6 *ym,w,h,(char *)"Darken");               bDarken ->buttonEventCallBack .connectCallback  (  [this] { return this->fDarken(); }   );
    button *bBright =new button(0,y+7 *ym,w,h,(char *)"Brighten");             bBright ->buttonEventCallBack .connectCallback  (  [this] { return this->fBrighten(); }   );
    button *bSharpen=new button(0,y+8 *ym,w,h,(char *)"Sharpen");              bSharpen->buttonEventCallBack .connectCallback  (  [this] { return this->fSharpen(); }   );
    button *bEdgeD  =new button(0,y+9 *ym,w,h,(char *)"EdgeDetect");           bEdgeD  ->buttonEventCallBack .connectCallback  (  [this] { return this->fEdgeDetect(); }   );
    button *bGauss  =new button(0,y+10*ym,w,h,(char *)"GausianBlur");          bGauss  ->buttonEventCallBack .connectCallback  (  [this] { return this->fGausianBlur(); }   );
    this->addChild(bNext);
    this->addChild(bLast);
    this->addChild(bOpen);
    this->addChild(bSave);
    this->addChild(bDither);
    this->addChild(bBlur);
    this->addChild(bDarken);
    this->addChild(bBright);
    this->addChild(bSharpen);
    this->addChild(bEdgeD);
    this->addChild(bGauss);
    
    
}

void navigation_control::draw(){
   control::draw();
   this->resetClip();
}

void navigation_control::updateMouse(){
    control::updateMouse();
}


extern string BASE_DIR_PATH;
extern bool load(string );
extern bool save(string );
string fileName="base.lib";

void navigation_control::fOpen(){
    load(BASE_DIR_PATH+fileName);
}

void navigation_control::fSave(){
    save(BASE_DIR_PATH+fileName);
}

void navigation_control::fDither(){
    fill(0,0,&dither);
}

void navigation_control::fBlur(){
    fill(0,0,&blur);
}
void navigation_control::fBrighten(){
    fill(0,0,&brighten);
}

void navigation_control::fDarken(){
    fill(0,0,&darken);
}
void navigation_control::fSharpen(){
    fill(0,0,&sharpen);
}
void navigation_control::fEdgeDetect(){
    fill(0,0,&edgeDetect);
}
void navigation_control::fGausianBlur(){
    fill(0,0,&gausianBlur);
}

void navigation_control::fNext(){
    curentTileIndex++;
    if(curentTileIndex>=GRAPHICS_LIB_SIZE) curentTileIndex=GRAPHICS_LIB_SIZE-1;
}

void navigation_control::fLast(){
    curentTileIndex--;
    if(curentTileIndex<0) curentTileIndex=0;
    
}
 


