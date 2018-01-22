/*****************************
 *   Graphic Editor 2.0      *
 *       Created By:         *
 *     Charles Watkins       *
 *  November 7, 2015 1:33pm  *
 *                           *
 * For creating              *
 * Graphic Libraries         *
 *                           *
 * Inspired by the original  *
 * GE (GT) Circa 1995        *
 *                           *
 ****************************/
//#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>         //For loading png's n such
#include <SDL2/SDL_mouse.h>
#include <cstdlib>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


#include "base.h"
#include "button.h"
#include "scrollbar.h"
#include "fileOperations.h"
#include "setup.h"
#include "palette.h"
#include "drawing.h"
#include "editor.h"
#include "library.h"
#include "navigation.h"
#include "pixelOperations.h"


using namespace std;


color   APPLICATION_COLOR (0xFF,0xEE,0xEE,0xEE);
int     foreColorBar;
int     foreColorIndex;
int     backColorBar;
int     backColorIndex;
long frames=0;

int cMouseX=0;
int cMouseY=0;      //click position of mouse



extern int curentTileIndex;
extern int PALETTE_VIEW_WIDTH;

bool MOUSE_BUTTON_DOWN=false;
bool LEFT_MOUSE_BUTTON_DOWN=false;
bool RIGHT_MOUSE_BUTTON_DOWN=false;

extern SDL_Renderer *screenRenderer;

//{Functions}
void            drawFPS();
void            drawMouse();
void            drawLibrary();                                                              //scroll window of images.
bool            save(char*);
//palette pal=palette();

palette_control *paletteCTRLPTR;
int main(int argc, char** argv) {
    bool motion=false;

    if(!setup()) {
        return 0;
    }
    
    
    control windowCTRL=control(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,screenRenderer);
    windowCTRL.anchor.left  =LEFT;
    windowCTRL.anchor.right =RIGHT;
    windowCTRL.anchor.bottom=TOP;
    windowCTRL.anchor.bottom=BOTTOM;
    windowCTRL.name="MAIN WINDOW";
    windowCTRL.updateCoordinates();
    windowCTRL.displayInfo=true;
   
    /*
    control w2CTRL=control(0,0,100,100);
    windowCTRL.addChild(&w2CTRL);
    control w3CTRL=control(0,0,100,100);
    w2CTRL.addChild(&w3CTRL);
    button b=button(0,0,40,10,"hi");
    w3CTRL.addChild(&b);
    
    */
    
    
    
    int MARGIN=10;
    palette_control paletteCTRL =palette_control(windowCTRL.getWidth()-433,MARGIN,windowCTRL.getWidth()-MARGIN,MARGIN+110);
    paletteCTRL.name="Palette Control";
    paletteCTRLPTR=&paletteCTRL;
    windowCTRL.addChild(&paletteCTRL);
    
    
    editor_control      editorCTRL  =editor_control     (MARGIN,MARGIN,paletteCTRL.left-MARGIN,windowCTRL.getHeight()-MARGIN);
    library_control     libraryCTRL =library_control    (paletteCTRL.left,windowCTRL.getHeight()-MARGIN-TILE_HEIGHT-20-6,windowCTRL.getWidth()-MARGIN,windowCTRL.getHeight()-MARGIN);
    navigation_control  navCTRL     =navigation_control (paletteCTRL.left,paletteCTRL.bottom+MARGIN,windowCTRL.getWidth()-MARGIN,libraryCTRL.top-MARGIN);
   
    windowCTRL.addChild(&editorCTRL);
    windowCTRL.addChild(&libraryCTRL);
    windowCTRL.addChild(&navCTRL);
    
    SDL_Event e;
    bool quit=false;
    
    while (!quit){
            motion=false;
                
            while (SDL_PollEvent(&e)){
                if(e.type == SDL_MOUSEMOTION){
                    xMouse=e.motion.x;
                    yMouse=e.motion.y;
                    motion=true;
                }
                if (e.type == SDL_QUIT){
                        quit = true;
                }
                if (e.type == SDL_KEYDOWN){

                }
                if (e.type == SDL_MOUSEBUTTONDOWN){
                }
                if(e.type == SDL_WINDOWEVENT) {
                     switch (e.window.event) {
                        /*case SDL_WINDOWEVENT_SHOWN:SDL_Log("Window %d shown", event->window.windowID);                            break;
                        case SDL_WINDOWEVENT_HIDDEN:SDL_Log("Window %d hidden", event->window.windowID);break;
                        case SDL_WINDOWEVENT_EXPOSED:SDL_Log("Window %d exposed", event->window.windowID);break;
                        case SDL_WINDOWEVENT_MOVED:SDL_Log("Window %d moved to %d,%d",event->window.windowID, event->window.data1,event->window.data2);break;
                        */case SDL_WINDOWEVENT_RESIZED: SCREEN_WIDTH=e.window.data1;
                                                        SCREEN_HEIGHT=e.window.data2;
                                                        windowCTRL.resize();
                                                        break;
                        /*case SDL_WINDOWEVENT_SIZE_CHANGED:SDL_Log("Window %d size changed to %dx%d",event->window.windowID, event->window.data1,event->window.data2);break;
                        case SDL_WINDOWEVENT_MINIMIZED:SDL_Log("Window %d minimized", event->window.windowID);break;
                        case SDL_WINDOWEVENT_MAXIMIZED:SDL_Log("Window %d maximized", event->window.windowID);break;
                        case SDL_WINDOWEVENT_RESTORED:SDL_Log("Window %d restored", event->window.windowID);break;
                        case SDL_WINDOWEVENT_ENTER:SDL_Log("Mouse entered window %d",event->window.windowID);break;
                        case SDL_WINDOWEVENT_LEAVE:SDL_Log("Mouse left window %d", event->window.windowID);break;
                        case SDL_WINDOWEVENT_FOCUS_GAINED:SDL_Log("Window %d gained keyboard focus",event->window.windowID);break;
                        case SDL_WINDOWEVENT_FOCUS_LOST:SDL_Log("Window %d lost keyboard focus",event->window.windowID);break;
                        case SDL_WINDOWEVENT_CLOSE:SDL_Log("Window %d closed", event->window.windowID);                            break;
                        default: SDL_Log("Window %d got unknown event %d",event->window.windowID, event->window.event);break;
                        */}
                }
            
            }
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                if(!LEFT_MOUSE_BUTTON_DOWN) {
                    LEFT_MOUSE_BUTTON_DOWN=true;
                    cMouseX=xMouse;
                    cMouseY=yMouse;
                    motion=true;
                               
                }            
            } else {
                if(LEFT_MOUSE_BUTTON_DOWN) {
                    motion=true;
                    LEFT_MOUSE_BUTTON_DOWN=false;
                }
            }
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
                if(!RIGHT_MOUSE_BUTTON_DOWN) {
                    RIGHT_MOUSE_BUTTON_DOWN=true;
                    cMouseX=xMouse;
                    cMouseY=yMouse;
                    motion=true;
                }
            } else {
                if(RIGHT_MOUSE_BUTTON_DOWN) {
                    motion=true;
                    RIGHT_MOUSE_BUTTON_DOWN=false;
                }

            }
            
           if(motion){
               windowCTRL.updateMouse();
           }
            
            
        frames++;
        
        //SDL_SetTextureBlendMode(, SDL_BLENDMODE_BLEND); 
        //SDL_SetRenderTarget(screenRenderer,NULL);
        //SDL_SetRenderDrawColor(screenRenderer,0,0,0,0);
        //SDL_RenderClear(screenRenderer);
 
           windowCTRL.draw();
        
       // windowCTRL.focusRender();
        /*char FPS_text[80];
        sprintf(FPS_text,"Frame: %i",frames);
        windowCTRL.drawText(0,0,FPS_text,APPLICATION_COLOR);
     */
        
        windowCTRL.present();
     
        
        SDL_SetRenderTarget(screenRenderer,NULL);
        
        

        
        drawMouse();
        SDL_RenderPresent(screenRenderer);

    }    
    SDL_DestroyTexture(cursor);
    SDL_DestroyRenderer(screenRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void renderTexture(SDL_Texture *tex, int x, int y){
    //setClip();
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(screenRenderer, tex, NULL, &dst);
    //removeClip();
}



void drawMouse(){
    renderTexture(cursor, xMouse,yMouse);
}







