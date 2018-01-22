/* 
 * File:   graphicOperations.h
 * Author: nd
 *
 * Created on November 10, 2015, 8:51 PM
 */
#include <SDL2/SDL.h>
#ifndef GRAPHICOPERATIONS_H
#define	GRAPHICOPERATIONS_H

SDL_Texture* libtoTexture(int tileIndex);
void lib2Temp(int tileIndex);
void temp2Lib(int tileIndex);

#endif	/* GRAPHICOPERATIONS_H */

