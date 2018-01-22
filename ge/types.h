/* 
 * File:   types.h
 * Author: nd
 *
 * Created on November 28, 2015, 2:49 PM
 */

#ifndef TYPES_H
#define	TYPES_H


#define COLOR_BAR_DEPTH         32          //Number of colors in a color segment
#define COLOR_BAR_COUNT         8           //Number of color bars in palette

struct color{
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    color() : a(), r(), g(),b() {}
    color(int a,int r,int g,int b) :a(a),r(r),g(g),b(b){}
    color(unsigned long hexColor){                  //0xRRGGBB
        a=0xFF;                                     //no alpha in a hex color.
        int red   = ((hexColor >> 16) & 0xFF);        // Extract the RR byte
        int green = ((hexColor >> 8 ) & 0xFF);        // Extract the GG byte
        int blue  = ((hexColor      ) & 0xFF);        // Extract the BB byte
        r=red;
        g=green;
        b=blue;
    }

};

struct colorBar{
    color  colors[COLOR_BAR_DEPTH];
};

struct palette{
    colorBar colorBars[COLOR_BAR_COUNT];
    palette(){
        
    }
} ;

struct mouse_state{
    int x;                      //mouse position
    int y;
    int cX;                     //position of mouse when clicked
    int cY;         
    bool inWindow;              //is the mouse in this window
    bool clickInWindow;         //did the click originate in thie window?
    bool LEFT;                  //left  mouse button status
    bool RIGHT;                 //right mouse button status
};

enum BORDER_TYPE{ BORDER_SINGLE,BORDER_3D,BORDER_NONE,BORDER_SCROLLBAR};
enum BORDER_STYLE{ BORDER_RAISED,BORDER_DEPRESSED,BORDER_FLAT};
enum CONTAINER_TYPE{BASIC,CONTROL,SCROLLBAR,BUTTON,INPUT};
enum anchor_point{LEFT,RIGHT,TOP,BOTTOM,NONE};
class anchor_container{
public:
    anchor_point left  ;
    anchor_point top   ;
    anchor_point right ;
    anchor_point bottom;
    anchor_container():left(),top(),right(),bottom() {
        left    =LEFT;
        top     =TOP;
        right   =LEFT;
        bottom  =TOP;
    }
    anchor_container(anchor_point left,anchor_point top,anchor_point right,anchor_point bottom):left(left),top(top),right(right),bottom(bottom) {}
    
};

class rect{
public:
    int left;
    int right;
    int top;
    int bottom;
    int width;
    int height;
    rect():left(0),top(0),right(0),bottom(0),width(0),height(0){}
    rect(int left,int top,int right,int bottom):left(left),top(top),right(right),bottom(bottom){
        this->width=getWidth();
        this->height=getHeight();
    }
    int getWidth()  { return right-left; }
    int getHeight() { return bottom-top; }
};

#endif	/* TYPES_H */

