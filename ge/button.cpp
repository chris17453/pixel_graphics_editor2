#include "button.h"

void button::updateMouse() {
    container::updateMouse();
    lastState=state;
    if(mouse.inWindow && mouse.LEFT && mouse.clickInWindow) {
        this->state=BUTTON_DOWN;
    } else if(!mouse.LEFT) {
        this->state=BUTTON_UP;
    }
    
    if(state==BUTTON_UP && lastState==BUTTON_DOWN) {
        this->state=BUTTON_PRESSED;
        //if(NULL!=caller.)  {
         //   callbackFunc();                             
            this->buttonEventCallBack.call();
       // }
    }
}


void button::draw(){
    
    if(this->borderType==BORDER_3D) {
        switch(this->state){
            case BUTTON_UP      : this->borderStyle=BORDER_RAISED;       break;
            case BUTTON_DOWN    : this->borderStyle=BORDER_DEPRESSED;    break;
            case BUTTON_PRESSED : this->borderStyle=BORDER_DEPRESSED;    break;
        }
    }
    if(this->borderType==BORDER_SINGLE) {
        switch(this->state){
            case BUTTON_UP      : this->borderStyle=BORDER_RAISED;       break;
            case BUTTON_DOWN    : this->borderStyle=BORDER_DEPRESSED;    break;
            case BUTTON_PRESSED : this->borderStyle=BORDER_DEPRESSED;    break;
        }
    }
    
    
    container::draw();
    
    int x=0;
    int y=0;
    if(state==BUTTON_DOWN)    { x++; y++; }
    if(state==BUTTON_PRESSED) { x++; y++; }
    drawText(x,y,(char *)text.c_str(),theme.controlText);
}
