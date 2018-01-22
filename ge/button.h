                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   #include <iostream>
#include "types.h"
#include "event.h"

/* 
 * File:   button.h
 * Author: nd
 *
 * Created on November 16, 2015, 11:56 AM
 */
#include "container.h"
#ifndef BUTTON_H
#define	BUTTON_H

class button:public container{           
public:
    bool initialized;
    enum BUTTON_STATE{ BUTTON_UP,BUTTON_DOWN,BUTTON_PRESSED };
    int state;
    int lastState;
    string text;
    Caller buttonEventCallBack;
     

    
    button(){
        this->name="BUTTON_UNINIT";
        initialized=false;
        text="";
        this->state=BUTTON_UP;
        this->lastState=BUTTON_UP;
        this->borderType=BORDER_3D;
        this->borderStyle=BORDER_RAISED;
        
                
    }
    button(int left,int top,int width,int height,string text):container(left,top,left+width,top+height),text(text){   //,void (*callbackFunc)(),callbackFunc(callbackFunc){
        this->name="BUTTON";
        this->type=BUTTON;
        this->state=BUTTON_UP;
        this->lastState=BUTTON_UP;
        padding=rect(1,1,1,1);
        updateCoordinates();
        initialized=true;
        this->borderType=BORDER_3D;
        this->borderStyle=BORDER_RAISED;
        text="";
        this->state=BUTTON_UP;
        this->lastState=BUTTON_UP;
    }
    void updateMouse();
    void draw();

};

#endif	/* BUTTON_H */

