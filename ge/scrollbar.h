/* 
 * File:   scrollbar.h
 * Author: nd
 *
 * Created on November 10, 2015, 9:03 PM
 */

#include "button.h"
//#include "container.h"
#ifndef SCROLLBAR_H
#define	SCROLLBAR_H

class scrollBar:public container{           //Scrollbar will be the opposite of the smallest difference in width or height;
public:
    float  lastPosition;
    float  position;
    float  visibleRange;
    int    startIndex;
    int    endIndex;
    float  percentage;
    bool   dragging;
    float  dragStartPosition;
    bool   mouseDownFinish;
    rect   tab;
    button *minButton;
    button *addButton;
    Caller scrollEventCallBack;

    
    void addPress();
    void minPress();

    
    scrollBar(int left,int top,int right,int bottom):container(left,top,right,bottom){
        position=0;
        visibleRange=2;
        startIndex=0;
        endIndex=0;
        percentage=0;
        dragging=false;
        dragStartPosition=0;
        mouseDownFinish=true;
        type=SCROLLBAR;   
        padding=rect(1,1,1,1);
        this->borderType=BORDER_SCROLLBAR;

        updateCoordinates();
        int w=face.bottom-face.top;
        int h=face.bottom-face.top;
        
        button *add=new button(this->width-w,0,w,h,">");
        button *min=new button(0            ,0,w,h,"<");
        min->name="minButton";
        add->name="addButton";
        add->borderType=BORDER_SINGLE;
        min->borderType=BORDER_SINGLE;
        min->buttonEventCallBack .connectCallback  (  [this] { return this->minPress(); }   );
        add->buttonEventCallBack .connectCallback  (  [this] { return this->addPress(); }   );
        addButton=add;
        minButton=min;
        this->addInternalChild(add);
        this->addInternalChild(min);
        
    }
    void updateMouse();
    void updateScrollRect();
    void draw();
    void present();
    void positionChanged();
    
};

#endif	/* SCROLLBAR_H */

