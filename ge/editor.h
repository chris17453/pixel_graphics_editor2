/* 
 * File:   editor.h
 * Author: nd
 *
 * Created on November 10, 2015, 8:38 PM
 */

//#include "container.h"
#include "control.h"
#ifndef EDITOR_H
#define	EDITOR_H




class editor_control:public control{
public :
    editor_control(int left,int right,int top,int bottom);
    void updateMouse();
    void preformAction(bool);
    void drawCursor();
    void draw();
};

#endif	/* EDITOR_H */

