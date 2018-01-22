/* 
 * File:   control.h
 * Author: nd
 *
 * Created on November 29, 2015, 9:39 AM
 */
#include "types.h"
#include "drawing.h"
#include "scrollbar.h"
#include "container.h"

#ifndef CONTROL_H
#define	CONTROL_H

class control:public container{                             //if anchored then frame becomes the distance from that border.
    void setClipping();
    void removeClipping();
    

public:
  //  using container::updateMouse;
    bool hasVerticalScrollbar;
    bool hasHorizontalScrollbar;
    
    scrollBar *hScroll;
    scrollBar *vScroll;
    int internalWidth;
    int internalHeight;
    
    control(){
       // borderType=BORDER_SINGLE_RAISED;
        hasVerticalScrollbar=false;
        hasHorizontalScrollbar=false;
        type=CONTROL;
        vScroll=NULL;
        hScroll=NULL;
        renderer=NULL;
    };
    control(int left,int top,int right,int bottom):container(left,top,right,bottom){
       // borderType=BORDER_3D_RAISED;
        hasVerticalScrollbar=false;
        hasHorizontalScrollbar=false;
        type=CONTROL;
        vScroll=NULL;
        hScroll=NULL;
    }
    
    control(int left,int top,int right,int bottom,SDL_Renderer *renderer):container(left,top,right,bottom){
       // borderType=BORDER_3D_RAISED;
        hasVerticalScrollbar=false;
        hasHorizontalScrollbar=false;
        type=CONTROL;
        vScroll=NULL;
        hScroll=NULL;
        renderer=renderer;
        
    }
    container  getPosition();
    
    void verticalScrollbar();
    void calcScrollH();
    void resize();
    virtual void  present();
    virtual void  draw();
    virtual void updateMouse();
    //virtual void drawText(int x,int y,char *text,color c);

    void setScrollH(int internalWidth);
    void hScrollEvent();
};


#endif	/* CONTROL_H */

