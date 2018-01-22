#include <SDL2/SDL.h>
//#include "types.h"
#include "palette.h"


extern SDL_Renderer *renderer;
extern int     EDITOR_OFFSET_X ;
extern int     SCREEN_WIDTH;
extern int     SCREEN_HEIGHT;
extern int      xMouse;
extern int      yMouse;
extern palette  pal;
extern bool LEFT_MOUSE_BUTTON_DOWN;
extern bool RIGHT_MOUSE_BUTTON_DOWN;


int     foreColor=COLOR_BAR_DEPTH-1;
int     foreBar=0;
int     backColor=COLOR_BAR_DEPTH-1;
int     backBar=1;


int     PALETTE_COLOR_WIDTH             =13;
int     PALETTE_COLOR_HEIGHT            =13;
int     PALETTE_COLOR_PADDING_WIDTH     =0;
int     PALETTE_COLOR_PADDING_HEIGHT    =0;
int     PALETTE_PITCH_X=4+(PALETTE_COLOR_WIDTH +PALETTE_COLOR_PADDING_WIDTH )*COLOR_BAR_DEPTH;
int     PALETTE_PITCH_Y=4+(PALETTE_COLOR_HEIGHT+PALETTE_COLOR_PADDING_HEIGHT)*COLOR_BAR_COUNT;
int     PALETTE_VIEW_WIDTH              =40;
int     PALETTE_VIEW_HEIGHT             =44;



palette_control::palette_control(int left,int right,int top,int bottom):control(left,top,right,bottom,NULL){
    name="PALETTE";
    this->borderType=BORDER_3D;
    rect pos=rect(left,right,top,bottom);
    
    
    this->anchor.left=RIGHT;
    this->anchor.right=RIGHT;
    this->anchor.top=TOP;
    this->anchor.bottom=TOP;
    this->setPosition(pos);
    updateCoordinates();
    this->createCanvas();
    
    //BAR,s,depth,a1,r1,g1,b1   a2,r2,g2,b2 
    Make_Pal(0 ,0 ,32,   0xFF,0 ,0 ,0 , 0xFF,0  ,255,0  ); /* Green    */
    Make_Pal(1 ,0 ,32,   0xFF,0 ,0 ,0 , 0xFF,0  ,0  ,255); /* Blue     */
    Make_Pal(2 ,0 ,32,   0xFF,0 ,0 ,0 , 0xFF,255,0  ,0  ); /* Red      */
    Make_Pal(3 ,0 ,32,   0xFF,0 ,0 ,0 , 0xFF,255,255,255); /* Gray     */
    Make_Pal(4 ,0 ,32,   0xFF,0 ,0 ,0 , 0xFF,255,255,0  ); /* Gold     */
    Make_Pal(5 ,0 ,32,   0xFF,0 ,0 ,0 , 0xFF,255,0  ,255); /* Purple   */
    Make_Pal(6 ,0 , 7,   0xFF,0 ,0 ,0 , 0xFF,52 ,20 ,0  ); /* Brown » */
    Make_Pal(6 ,8 ,32,   0xFF,13,5 ,0 , 0xFF,255,224,196); /* Brown ¼ */
    Make_Pal(7 ,0 ,32,   0xFF,0 ,0 ,0 , 0xFF,127,127,255); /* Cyan     */
}

void palette_control::Make_Pal(int colorBar,int startIndex,int depth,int a1,int r1,int g1,int b1,int a2,int r2,int g2,int b2) {
    int e,f,g,h,p,i;
    for(i=startIndex;i<(startIndex+depth);i++) {
        p=((i-startIndex)*100)/(depth);
        e=((r2-r1)*p)/100;
        f=((g2-g1)*p)/100;
        g=((b2-b1)*p)/100;
        h=((a2-a1)*p)/100;
        pal.colorBars[colorBar].colors[i].a=(unsigned char)(a1+h);
        pal.colorBars[colorBar].colors[i].r=(unsigned char)(r1+e);
        pal.colorBars[colorBar].colors[i].g=(unsigned char)(g1+f);
        pal.colorBars[colorBar].colors[i].b=(unsigned char)(b1+g);
    }
}


void palette_control::updateMouse(){
    control::updateMouse();
    
    if(mouse.inWindow){
        int c=(mouse.x)/(PALETTE_COLOR_WIDTH +PALETTE_COLOR_PADDING_WIDTH );
        int b=(mouse.y)/(PALETTE_COLOR_HEIGHT+PALETTE_COLOR_PADDING_HEIGHT);
        if(c<0) c=0; if(c>=COLOR_BAR_DEPTH) c=COLOR_BAR_DEPTH-1;
        if(b<0) b=0; if(b>=COLOR_BAR_COUNT) b=COLOR_BAR_COUNT-1;
     
        if(mouse.LEFT) {
            foreColor=c;
            foreBar=b;
        }
        if (mouse.RIGHT){
            backColor=c;
            backBar=b;
        }
    }
}

void palette_control::draw(){
    control::draw();
    
    
   /* 
    control color1=control( left-PALETTE_VIEW_WIDTH-10,
                            top, 
                            left-10,
                            top+PALETTE_VIEW_HEIGHT);
    color1.face=pal.colorBars[backBar].colors[backColor];
    color1.draw();
    color2=control( left-PALETTE_VIEW_WIDTH-10,
                            bottom-PALETTE_VIEW_HEIGHT, 
                            left-10,
                            bottom);
    
    color2.face=pal.colorBars[foreBar].colors[foreColor];
    
    color2.draw();
    */
    
    
    SDL_Rect rect;            
    for(int colorBar=0;colorBar<COLOR_BAR_COUNT;colorBar++) {
        for(int color=0;color<COLOR_BAR_DEPTH;color++) {
            rect.x = color   *(PALETTE_COLOR_WIDTH +PALETTE_COLOR_PADDING_WIDTH);
            rect.y = colorBar*(PALETTE_COLOR_HEIGHT+PALETTE_COLOR_PADDING_HEIGHT);
            rect.w = PALETTE_COLOR_WIDTH;
            rect.h = PALETTE_COLOR_HEIGHT;
            this->drawRect(rect.x,rect.y,rect.w+rect.x,rect.y+rect.h,pal.colorBars[colorBar].colors[color]);
        }//end colors
    }//end color bar loop`
    
    rect.x =foreColor*(PALETTE_COLOR_WIDTH +PALETTE_COLOR_PADDING_WIDTH) ;
    rect.y =foreBar  *(PALETTE_COLOR_HEIGHT+PALETTE_COLOR_PADDING_HEIGHT);
    rect.w = PALETTE_COLOR_WIDTH;
    rect.h = PALETTE_COLOR_HEIGHT;
    this->drawRect(rect.x,rect.y,rect.w+rect.x,rect.y+rect.h,pal.colorBars[foreBar].colors[0]);
            
                    
    rect.y+=4;
    rect.h-=8;
    this->drawRect(rect.x,rect.y,rect.w+rect.x,rect.y+rect.h,pal.colorBars[foreBar].colors[COLOR_BAR_DEPTH-1]);
    
    rect.x = backColor*(PALETTE_COLOR_WIDTH +PALETTE_COLOR_PADDING_WIDTH);
    rect.y = backBar  *(PALETTE_COLOR_HEIGHT+PALETTE_COLOR_PADDING_HEIGHT);
    rect.w = PALETTE_COLOR_WIDTH;
    rect.h = PALETTE_COLOR_HEIGHT;
    this->drawRect(rect.x,rect.y,rect.w+rect.x,rect.y+rect.h,pal.colorBars[backBar].colors[0]);
                    
    rect.y+=4;
    rect.h-=8;
    this->drawRect(rect.x,rect.y,rect.w+rect.x,rect.y+rect.h,pal.colorBars[backBar].colors[COLOR_BAR_DEPTH-1]);
 
}
