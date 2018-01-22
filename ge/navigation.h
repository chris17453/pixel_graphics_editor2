/* 
 * File:   navigation.h
 * Author: nd
 *
 * Created on February 14, 2016, 6:42 PM
 */

#ifndef NAVIGATION_H
#define	NAVIGATION_H

#include "control.h"

class navigation_control:public control{

public:
    using control::draw;
    navigation_control(int left,int right,int top,int bottom);
    void draw();
    void updateMouse();
    
    void openBase();
    void saveBase();
    void fOpen();
    void fSave();
    void fDither();
    void fBlur();
    void fBrighten();
    void fDarken();
    void fSharpen();
    void fEdgeDetect();
    void fGausianBlur();
    void fNext();
    void fLast();
    
};


#endif	/* NAVIGATION_H */

