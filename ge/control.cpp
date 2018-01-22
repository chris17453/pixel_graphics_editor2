#include <SDL2/SDL.h>
#include "control.h"
#include "palette.h"

extern int xMouse;
extern int yMouse;
extern int cMouseX;
extern int cMouseY;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern bool LEFT_MOUSE_BUTTON_DOWN;
extern bool RIGHT_MOUSE_BUTTON_DOWN;


    
void control::setClipping(){
    setClip(face.left,face.top,face.right-face.left,face.bottom-face.top);
}

void control::removeClipping(){
    setClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}


void control::updateMouse(){
    container::updateMouse();
    
    container *node=children;
    while(node) {
        switch(node->type) {
            case BASIC    : node->updateMouse(); break;
            case BUTTON   : ((button   *)node)->updateMouse(); break;
            case SCROLLBAR: ((scrollBar*)node)->updateMouse(); break;
            case CONTROL  : ((control  *)node)->updateMouse(); break;
        }
        node=node->nextSibling;
    }
}

void control::resize(){
    container::resize();
    
    container *node=children;
    while(node) {
        switch(node->type) {
            case BASIC    : node->resize();
            case CONTROL  : ((control  *)node)->resize(); break;
            case BUTTON   : ((button   *)node)->resize(); break;
            case SCROLLBAR: ((scrollBar*)node)->resize(); break;
        }
        node=node->nextSibling;
    }
}

void control::draw(){
    container::draw();
  /*  if(this->hasHorizontalScrollbar ||this->hasVerticalScrollbar){
        if(this->hasHorizontalScrollbar)  { 
            //calcScrollH();
        }
    }*/

    container *node=children;
    container *last;
    while(node) {
        switch(node->type) {
            //case BASIC  :         node->draw();
            case CONTROL  : ((control  *)node)->draw(); break;
            case BUTTON   : ((button   *)node)->draw(); break;
            case SCROLLBAR: ((scrollBar*)node)->draw(); break;
        }
        last=node;
        node=node->nextSibling;
    }
}

void control::present(){
    container::present();
    container *node=children;
    container *last;
    while(node) {
        switch(type) {
            case BASIC    : node->present(); break;
            case CONTROL  : node->present(); break;
            case BUTTON   : node->present(); break;
            case SCROLLBAR: ((scrollBar*)node)->present(); break;
        }
        last=node;
        node=node->nextSibling;
    }
}

void control::setScrollH(int internalWidth){
    hasHorizontalScrollbar=true;
    
    scrollBar *scroll=new scrollBar(face.left,face.bottom-20,face.right,face.bottom);
    const char  *cname="H-SCROLL";
    scroll->name      =cname;
    scroll->endIndex=internalWidth;
    
    this->hScroll=scroll;
    this->hScroll->visibleRange  =this->hScroll->right-this->hScroll->left;
    //calcScrollH();
    this->hScroll->scrollEventCallBack.connectCallback  (  [this] { return this->hScrollEvent(); }   );
    this->addChild(this->hScroll);
    int i=0;
}

void control::hScrollEvent(){
    origin.left=hScroll->position;
}

