/* 
 * File:   pixelOperations.h
 * Author: nd
 *
 * Created on November 27, 2015, 6:25 PM
 */

#ifndef PIXELOPERATIONS_H
#define	PIXELOPERATIONS_H

void getPixeCoords(int &x,int &y);
unsigned char gePixelC(int x,int y);
unsigned char gePixelB(int x,int y);
void setPixelC(int x,int y,unsigned color);
void setPixelB(int x,int y,unsigned char bar);


void processConvolutionMatrix(float cm[9],float divisorOverride,int x,int y);
void fill(int pX,int pY,void (*func)(int,int));
void pen(int x,int y);
void dither(int x,int y);
void darken(int x,int y);
void brighten(int x,int y);
void sharpen(int x,int y);
void blur(int x,int y);
void gausianBlur(int x,int y);
void edgeDetect(int x,int y);

#endif	/* PIXELOPERATIONS_H */

