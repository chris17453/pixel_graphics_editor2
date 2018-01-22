#include "setup.h"
#include "types.h"

#include <unistd.h>                 //for abs path of exe
#include <stdio.h>                  //BUFSIZ
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


extern SDL_Texture* libtoTexture(int);
extern SDL_Texture   *graphicsTextures[62];

extern int              SCREEN_WIDTH;
extern int              SCREEN_HEIGHT;
extern int              TILE_BYTES;
extern int              GRAPHICS_LIBRARY_SIZE;      //size of graphics memoty for colors and bars per tile for all tiles
extern int              GRAPHICS_LIB_SIZE;          //number of tiles

extern unsigned char   *master;
extern unsigned char   *graphicsLibrary;
extern SDL_Window      *window;
SDL_Renderer    *screenRenderer;
extern int xMouse;
extern int yMouse;
extern SDL_Texture *cursor;

string BASE_DIR_PATH="";



using namespace std;

bool setup() {
     char buffer[BUFSIZ];
     memset(buffer,0,BUFSIZ);
    readlink("/proc/self/exe", buffer, BUFSIZ);
    BASE_DIR_PATH=buffer;

    
    graphicsLibrary=(unsigned char*)malloc(GRAPHICS_LIBRARY_SIZE);
    master=(unsigned char*)malloc(TILE_BYTES);

    memset(graphicsLibrary,0,GRAPHICS_LIBRARY_SIZE);
    memset(master,0,TILE_BYTES);
    
    
    
    size_t pos = BASE_DIR_PATH.length();      
    string str3 = BASE_DIR_PATH.substr (0,pos-2);     // get from "live" to the end
    BASE_DIR_PATH=str3;

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
            error("SDL_Init");
            return false;
    }

    window = SDL_CreateWindow("GE - Graphics Editor 2.0", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if(window == NULL){
            error("CreateWindow");
            SDL_Quit();
            return false;
    }
    SDL_bool border=SDL_FALSE;
   // SDL_SetWindowBordered(window,border);
    screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC );//SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC SLOW ON CRAPY SYSTEM...
    if (screenRenderer== NULL){
            error("CreateRenderer");
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
    }
    
    
    SDL_ShowCursor(SDL_DISABLE);                        //turn off visibility of mouse
    cursor     =loadTexture(BASE_DIR_PATH + "blue-cursor.gif",screenRenderer);
    
    if (cursor == NULL){
            SDL_DestroyTexture(cursor);
            SDL_DestroyRenderer(screenRenderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
    }
    
    for(int a=0;a<GRAPHICS_LIB_SIZE;a++) { 
        graphicsTextures[a]=libtoTexture(a);
    }
    
    if( TTF_Init() == -1 ){
        printf("%s\n", TTF_GetError()); 
    }

    
    return true;

}


void error(string message){
    const char * c = message.c_str();
    //sprintf("%c",c);
    cout << c;
}




SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = NULL;
        SDL_Surface *loadedImage;
        
        loadedImage =IMG_Load(file.c_str()); 
            
            
        
	if (loadedImage != NULL){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == NULL){
                    error("CreateTextureFromSurface");
		}
	} else {
            error("LoadBMP ");
            error(file);
            error(IMG_GetError());
	}
	return texture;
}


