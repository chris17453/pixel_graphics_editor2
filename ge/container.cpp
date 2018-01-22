#include "container.h"

#include <iostream>

#include <cstddef>

extern int xMouse;
extern int yMouse;
extern int cMouseX;
extern int cMouseY;
extern bool LEFT_MOUSE_BUTTON_DOWN;
extern bool RIGHT_MOUSE_BUTTON_DOWN;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern string BASE_DIR_PATH;

void container::setFont(){
    string fontPath= BASE_DIR_PATH+"Hack-Regular.ttf";
    const char* fontName = fontPath.c_str();
    font = TTF_OpenFont(fontName, 12); 
    if(font == NULL) {
        printf("%s\n", TTF_GetError()); 
    }
}

void container::addChild(container *child){
    updateCoordinates();
    child->parent=this;
    child->nextSibling=children;
    children=child;
    child->updateCoordinates();
}

void container::addInternalChild(container *child){
    updateCoordinates();
    child->parent=this;
    child->nextSibling=internalChildren;
    internalChildren=child;
    child->updateCoordinates();
}

void container::updateMouse(){
    mouse.LEFT =LEFT_MOUSE_BUTTON_DOWN;
    mouse.RIGHT=RIGHT_MOUSE_BUTTON_DOWN;
    mouse.x=xMouse-worldCoordinates.left+face.left;
    mouse.y=yMouse-worldCoordinates.top +face.top;
    mouse.cX=cMouseX-worldCoordinates.left+face.left;
    mouse.cY=cMouseY-worldCoordinates.top  +face.top;
    if(mouse.x >=face.left  && mouse.y >=face.top && mouse.x <=face.right && mouse.y <=face.bottom) mouse.inWindow     =true; else mouse.inWindow     =false;
    if(mouse.cX>=face.left  && mouse.cY>=face.top && mouse.cX<=face.right && mouse.cY<=face.bottom) mouse.clickInWindow=true; else mouse.clickInWindow=false;
}

void container::updateCoordinates(){
    updateOffset();
    updateFace();
    updatePosition();
    getWorldCooridinates();
}

void container::getWorldCooridinates(){
    container *node=this->parent;
    worldCoordinates.left  =left    ;
    worldCoordinates.top   =top     ;                //Set cooridinates to the curent rect...
    worldCoordinates.right =face.right   ;
    worldCoordinates.bottom=face.bottom  ;
        
    while(node!=NULL) {
        //worldCoordinates.left  +=node->left;
        //worldCoordinates.top   +=node->top;              
        //worldCoordinates.right +=node->left;
        //worldCoordinates.bottom+=node->top;

        
        worldCoordinates.left  +=node->left;
        worldCoordinates.top   +=node->top;              
        if(node->parent) {
            
            worldCoordinates.left  +=node->padding.left;
            worldCoordinates.top   +=node->padding.top;             

            
        }
        /*worldCoordinates.right +=node->left+padding.left;
        worldCoordinates.bottom+=node->top+padding.top;
         */
        node=node->parent;
    }
    //worldCoordinates.left  +=padding.left;
    //worldCoordinates.top   +=padding.top;              
    
}

void container::updateOffset(){
   int wMax=0,hMax=0;                                  //max width/height of window
   int wMin=0,hMin=0;                                  //max width/height of window
    if(parent!=NULL) {
        wMin=parent->left;
        hMin=parent->top;
        wMax=parent->right;
        hMax=parent->bottom;
    } else {
        wMin=0;
        hMin=0;
        wMax=SCREEN_WIDTH;
        hMax=SCREEN_HEIGHT;
    }
    offsetMin.left  =left ;// -wMin;
    offsetMin.right =right;// -wMin;
    offsetMin.top   =top   ;//-hMin;
    offsetMin.bottom=bottom;//-hMin;

    offsetMax.left  =left  -wMax;
    offsetMax.right =right -wMax;
    offsetMax.top   =top   -hMax;
    offsetMax.bottom=bottom-hMax;
  //  getWorldCooridinates();
}

void container::updatePosition(){
    int wMax=0,hMax=0;                                  //max width/height of window
    int wMin=0,hMin=0;                                  //max width/height of window
    if(parent!=NULL) {
        wMin=parent->left;
        hMin=parent->top;
        wMax=parent->right;
        hMax=parent->bottom;
    } else {
        wMin=0;
        hMin=0;
        wMax=SCREEN_WIDTH;
        hMax=SCREEN_HEIGHT;
    }

    //if(anchor.left  ==LEFT)  left  =wMin+offsetMin.left;
    //if(anchor.right ==LEFT)  right =wMin+offsetMin.right;
    //if(anchor.top   ==TOP)   top   =hMin+offsetMin.top;
    //if(anchor.bottom==TOP)   bottom=hMin+offsetMin.bottom;
    
    if(anchor.left  ==RIGHT)  left  =wMax+offsetMax.left;
    if(anchor.right ==RIGHT)  right =wMax+offsetMax.right;
    if(anchor.top   ==BOTTOM) top   =hMax+offsetMax.top;
    if(anchor.bottom==BOTTOM) bottom=hMax+offsetMax.bottom;
}

void container::updateFace(){
    face.left   =            this->padding.left;
    face.right  =getWidth()- this->padding.right;
    face.top    =            this->padding.top;
    face.bottom =getHeight()-this->padding.bottom;
   /* if(this->hasHorizontalScrollbar) { 
        face.bottom -=this->hScroll.h;
    }
    if(this->hasVerticalScrollbar) { 
        face.right -=this->vScroll.w;
    }*/
}

void container::setPosition(rect position){
    left    =position.left;
    right   =position.right;
    bottom  =position.bottom;
    top     =position.top;
    this->updateOffset();
    this->updatePosition();
    this->updateFace();
}
 
void container::resize(){
    
    this->updatePosition();
    this->updateFace();
    this->getWorldCooridinates();
    if(NULL!=this->canvas) {
        SDL_DestroyTexture(this->canvas);
    }
    this->canvas = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,this->getWidth(),this->getHeight());
}

void container::drawText(int x,int y,char *text,color c){
    if(font==NULL ) return;
    SDL_Color sdlC = {c.r, c.g, c.b };  
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, sdlC); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    int w,h;
    
    if(!this->absolutePosition){
        x = x+face.left-origin.left;
        y = y+face.top -origin.top;
    } 

    SDL_QueryTexture(Message, NULL, NULL, &w, &h);
    renderTexture(Message, x,y);
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);    
}

rect container::getTextRect(char *text){
    SDL_Color White = {255, 255, 255};  
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, White); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    int w,h;
    SDL_QueryTexture(Message, NULL, NULL, &w, &h);
    rect r=rect();
    r.width=w;
    r.height=h;
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);    

    return r;
}

void container::draw(){
    SDL_Rect dst;
    dst.x=left;
    dst.y=top;
    dst.w=right-left;
    dst.h=bottom-top;
    this->frame++;
    
    if(this->canvas!=NULL) {
        drawBorder();
        if(this->displayInfo) {
            char FPS_text[80];
            sprintf(FPS_text,"Frame: %i",this->frame);
            drawText(0,0,FPS_text,this->theme.activeCaptionText);
        }
    
    }
}

void container::present(){
    const char *name=this->name;
    if(this->canvas!=NULL) {
        this->getWorldCooridinates();
        SDL_Rect dst;
	dst.x = worldCoordinates.left;
	dst.y = worldCoordinates.top;
        SDL_QueryTexture(this->canvas, NULL, NULL, &dst.w, &dst.h);
        SDL_SetRenderTarget(this->renderer, NULL);
        SDL_RenderCopy(this->renderer, canvas, NULL, &dst);
    }
}

void container::focusRender(){
    SDL_SetRenderTarget(this->renderer, this->canvas);
}

void container::createCanvas(){
    if(NULL==this->canvas) {
        this->canvas = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,this->getWidth(),this->getHeight());
    }
}

void container::drawRect(int x1,int y1,int x2,int y2,color color){
    this->focusRender();
    resetClip();
    SDL_Rect rect;
    
    rect.w = x2-x1;
    rect.h = y2-y1;
   
    if(!this->absolutePosition){
        x1 = x1+face.left-origin.left;
        y1 = y1+face.top -origin.top;
    }
    rect.x = x1;
    rect.y = y1;
     SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
    SDL_RenderFillRect(this->renderer, &rect);
}

void container::setClip(int x1,int y1,int x2,int y2) {
    this->focusRender();
    SDL_Rect rect;
    rect.x = x1;
    rect.y = y1;
    rect.w = x2-x1;
    rect.h = y2-y1;
    SDL_RenderSetClipRect(this->renderer, &rect);    
}

void container::removeClip() {
    this->focusRender();
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = this->getWidth();
    rect.h = this->getHeight();
    SDL_RenderSetClipRect(this->renderer, &rect);    
}

void container::resetClip(){
    setClip(face.left,face.top,face.right,face.bottom);

}

void container::renderTexture(SDL_Texture *tex, int x, int y){
    this->focusRender();
    //setClip();
     if(!this->absolutePosition){
        x = x+face.left-origin.left;
        y = y+face.top -origin.top;
    } 
    
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(this->renderer, tex, NULL, &dst);
    //removeClip();
}

void container::drawBorder(){
    face.left=0;
    face.top=0;
    face.right=getWidth();
    face.bottom=getHeight();
    int l=0,t=0,r=this->getWidth(),b=this->getHeight();
    
    this->absolutePosition=true;            //turn off virtual positioning and face

    
    
    
    
    if(borderType==BORDER_3D) {
        if(borderStyle==BORDER_RAISED){
            drawRect(l  ,t  ,r  ,b  ,theme.controlHighlight);       //highlight      
            drawRect(l+1,t+1,r  ,b  ,theme.controlDkShadow);        //darkShadow
            drawRect(l+1,t+1,r-1,b-1,theme.controlLtHighlight);     //highlightLight
            drawRect(l+2,t+2,r-1,b-1,theme.controlShadow);          //lightShadow
            drawRect(l+2,t+2,r-2,b-2,theme.control);                //face
        }
        if(borderStyle==BORDER_DEPRESSED){
            drawRect(l  ,t  ,r  ,b  ,theme.controlDkShadow);        //highlight      
            drawRect(l+1,t+1,r  ,b  ,theme.controlHighlight);       //darkShadow
            drawRect(l+1,t+1,r-1,b-1,theme.controlShadow);          //highlightLight
            drawRect(l+2,t+2,r-1,b-1,theme.controlLtHighlight);     //lightShadow
            drawRect(l+2,t+2,r-2,b-2,theme.control);                //face
        }
    } else 
    
    if(borderType==BORDER_SINGLE) {        
        if(borderStyle==BORDER_DEPRESSED){
            drawRect(l  ,t  ,r  ,b  ,theme.controlHighlight);
            drawRect(l  ,t  ,r-1,b-1,theme.controlDkShadow);
            drawRect(l+1,t+1,r-1,b-1,theme.control);
        }
        if(borderStyle==BORDER_RAISED){
            drawRect(l  ,t  ,r  ,b  ,theme.controlDkShadow);
            drawRect(l  ,t  ,r-1,b-1,theme.controlHighlight);
            drawRect(l+1,t+1,r-1,b-1,theme.control);
        }
        if(borderStyle==BORDER_FLAT) {
            drawRect(l  ,t  ,r  ,b  ,theme.controlHighlight);
            drawRect(l  ,t  ,r-1,b-1,theme.controlDkShadow);
            drawRect(l+1,t+1,r-1,b-1,theme.control);
        } 
    } else
    
    
    if(borderType==BORDER_SCROLLBAR) {
                        drawRect(l  ,t  ,r  ,b  ,theme.controlHighlight);
                        drawRect(l  ,t  ,r-1,b-1,theme.controlDkShadow);
                        drawRect(l+1,t+1,r-1,b-1,theme.scrollbar);
    } 
    
        
   
    this->absolutePosition=false;    
    this->updateFace();
    //setClip(this->face.left,this->face.top,this->face.width,this->face.height);
}

    