/* 
 * File:   palette.h
 * Author: nd
 *
 * Created on November 10, 2015, 5:35 PM
 */
#include <SDL2/SDL.h>
#include "control.h"

#ifndef PALETTE_H
#define	PALETTE_H

//palette pal;

class palette_control: public control{
    
    public:    

    palette_control(int,int,int,int);
    void Make_Pal(int colorBar,int startIndex,int depth,int a1,int r1,int g1,int b1,int a2,int r2,int g2,int b2) ;
    void updateMouse();
    void draw();
    
};


#endif	/* PALETTE_H */

