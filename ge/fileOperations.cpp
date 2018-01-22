#include <SDL2/SDL.h>
#include <iostream>
#include <malloc.h>
#include "graphicOperations.h"

using namespace std;

extern unsigned char *graphicsLibrary;
extern int GRAPHICS_LIBRARY_SIZE;
extern SDL_Texture *graphicsTextures[];
extern int GRAPHICS_LIB_SIZE;
bool load(string path){
    const char * c = path.c_str();

    FILE *data;
    data=fopen(c,"rb");
    if(data){
        fseek(data, 0, SEEK_END);
        long fsize = ftell(data);
        fseek(data, 0, SEEK_SET);
        free(graphicsLibrary);
        graphicsLibrary=(unsigned char *)malloc(fsize );
        fread(graphicsLibrary,fsize,1,data);
        fclose(data);
    }
    
    for(int a=0;a<GRAPHICS_LIB_SIZE;a++) { 
        SDL_DestroyTexture(graphicsTextures[a]);
        graphicsTextures[a]=libtoTexture(a);
    }
    return true;
}

bool save(string path){
    const char * c = path.c_str();
    FILE *data;
    data=fopen(c,"wb");
    if(data){
        fwrite(graphicsLibrary,GRAPHICS_LIBRARY_SIZE,1,data);
        fclose(data);
    }
    return true;
}