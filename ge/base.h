/* 
 * File:   base.h
 * Author: nd
 *
 * Created on November 10, 2015, 5:59 PM
 */

//#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>         //For loading png's n such
#include <SDL2/SDL_mouse.h>
#include <cstdlib>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "types.h"

using namespace std;



#ifndef BASE_H
#define	BASE_H
int     SCREEN_WIDTH                    = 1024;
int     SCREEN_HEIGHT                   = 768;
int     TILE_WIDTH                      =32;
int     TILE_HEIGHT                     =32;
int     TILE_PIXEL_COUNT                =TILE_WIDTH*TILE_HEIGHT;
int     TILE_BYTES                      =TILE_WIDTH*TILE_HEIGHT;
int     xMouse,yMouse;
int     textureX,textureY;
int     mouseOWNER;


const char      *BASE_LIB_PATH="base.gelib";
void            *base_lib=NULL;


unsigned char   *graphicsLibrary;
unsigned char   *master;

const int LIB_SIZE= 62;
int GRAPHICS_LIB_SIZE=LIB_SIZE;

int     GRAPHICS_LIBRARY_SIZE=TILE_BYTES*LIB_SIZE*2;
int     curentTileIndex=0;                                                      //The curent Tile
SDL_Window      *window;
SDL_Renderer    *renderer;
SDL_Texture     *background;
SDL_Texture     *cursor;
SDL_Texture     *graphicsTextures[LIB_SIZE];
palette pal;
#endif	/* BASE_H */

