/* 
 * File:   fileOperations.h
 * Author: nd
 *
 * Created on November 27, 2015, 4:10 PM
 */

#ifndef FILEOPERATIONS_H
#define	FILEOPERATIONS_H

bool load(string path);
bool open(string path);


#endif	/* FILEOPERATIONS_H */
/*
 
 extern string BASE_DIR_PATH;
extern bool load(string );
extern bool save(string );
string fileName="base.lib";
void openBase(){
    load(BASE_DIR_PATH+fileName);
}

void saveBase(){
    save(BASE_DIR_PATH+fileName);
}

void fDither(){
    int x=0,y=0;
    fill(0,0,&dither);
}

void fBlur(){
    fill(0,0,&blur);
}
void fBrighten(){
    fill(0,0,&brighten);
}

void fDarken(){
    fill(0,0,&darken);
}
void fSharpen(){
    fill(0,0,&sharpen);
}
void fEdgeDetect(){
    fill(0,0,&edgeDetect);
}
void fGausianBlur(){
    fill(0,0,&gausianBlur);
}

void  next(){
    curentTileIndex++;
    if(curentTileIndex>=GRAPHICS_LIB_SIZE) curentTileIndex=GRAPHICS_LIB_SIZE-1;
    motion=true;
}

void  last(){
    curentTileIndex--;
    if(curentTileIndex<0) curentTileIndex=0;
    motion=true;
    
}
 *   bool quit = false;
    
    int y=250;
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+0 *30,50,20,BUTTON_UP,(char *)"Next",&next) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+1 *30,50,20,BUTTON_UP,(char *)"Last",&last) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+2 *30,50,20,BUTTON_UP,(char *)"Open",&openBase) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+3 *30,50,20,BUTTON_UP,(char *)"Save",&saveBase) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+4 *30,50,20,BUTTON_UP,(char *)"Dither",&fDither) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+5 *30,50,20,BUTTON_UP,(char *)"Blur",&fBlur) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+6 *30,50,20,BUTTON_UP,(char *)"Darken",&fDarken) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+7 *30,50,20,BUTTON_UP,(char *)"Brighten",&fBrighten) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+8 *30,50,20,BUTTON_UP,(char *)"Sharpen",&fSharpen) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+9 *30,50,20,BUTTON_UP,(char *)"EdgeDetect",&fEdgeDetect) );
    BUTTON_LIST.add( new button(SCREEN_WIDTH-50-15,y+10*30,50,20,BUTTON_UP,(char *)"GausianBlur",&fGausianBlur) );
    

 */
