/* 
 * File:   setup.h
 * Author: nd
 *
 * Created on November 10, 2015, 6:08 PM
 */
#include <iostream>
#include <SDL2/SDL.h>         //For loading png's n such
#include <SDL2/SDL_image.h>         //For loading png's n such

using namespace std;

#ifndef SETUP_H
#define	SETUP_H

bool            setup();
void            error(string);
bool            load(string);
SDL_Texture*    loadTexture(const std::string &file, SDL_Renderer *ren);

    
#endif	/* SETUP_H */

