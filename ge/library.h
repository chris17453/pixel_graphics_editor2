/* 
 * File:   library.h
 * Author: nd
 *
 * Created on November 10, 2015, 8:58 PM
 */
#include "control.h"
#ifndef LIBRARY_H
#define	LIBRARY_H

class library_control:public control{

public:
    using control::draw;
    library_control(int left,int right,int top,int bottom);
    void draw();
    void updateMouse();
};

#endif	/* LIBRARY_H */

