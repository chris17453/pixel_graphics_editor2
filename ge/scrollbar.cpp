#include "scrollbar.h"
#include "drawing.h"


void scrollBar::addPress(){
    lastPosition=position;
    this->position++;
    if(this->position>this->endIndex) this->position=endIndex;    
    if(this->position!=this->lastPosition) positionChanged();
}

void scrollBar::minPress(){
    this->lastPosition=this->position;
    this->position--;
    if(this->position<0) this->position=0;
    if(this->position!=this->lastPosition) positionChanged();
}

void  scrollBar::updateMouse(){
    //return;
    container::updateMouse();
    addButton->updateMouse();
    minButton->updateMouse();
    lastPosition=position;
    if(!mouse.LEFT) {                                                                   //is the mouse not pressed.. if so clear these flags.
        mouseDownFinish=false;
        dragging=false;
    } else {                                                                                        //is the LEFT Mouse Button pressed and are we dragging?
        if(dragging){
            if(right-left<bottom-top) {                               // its skinnier than long... so UP DOWN...
        
            } else {
                float w=right-left;
                float xPixelPosition  =mouse.x-mouse.cX;//data->container.x+1;
                float xPixelPercentage=xPixelPosition/w;
                
                float diff=xPixelPercentage*(endIndex-startIndex)+startIndex+dragStartPosition;
                if(diff<startIndex)             diff=startIndex;
                if(diff>endIndex-visibleRange)  diff=endIndex-visibleRange;
                
                position=diff;//data->draggingPosition+diff;
            }
        }
    }

    if(mouse.LEFT && mouse.clickInWindow 
            && mouse.x>minButton->getWidth() 
            && mouse.x<face.right-addButton->getWidth()) {                                         //The click originated inside this object first.
        if(right-left<bottom-top) {                                                 // its skinnier than long... so UP DOWN...
            
        } else {
            if(!dragging && !mouseDownFinish) {                                     //we are not dragging...
                if(mouse.cX>tab.left && mouse.cX<(tab.right)  && 
                   mouse.cY>tab.top  && mouse.cY<(tab.bottom)) {                    //the click originated INSIDE the tab
                    dragging=true;
                    dragStartPosition=position;
                } else
                if(mouse.cX<tab.left &&
                   mouse.cY>tab.top && mouse.cY<(tab.bottom)) {                     //the click originated To the LEFT of the tab subtract 1 page of visible
                    position-=visibleRange;
                    if(position<startIndex) position=startIndex;
                    mouseDownFinish=true;                                           //accept no other input from the mouse because you need to click AGAIN
                }else
                if(mouse.cX>(tab.right) &&
                   mouse.cY>tab.top && mouse.cY<(tab.bottom)) {                     //the click originated To the RIGHT of the tab  add 1 page of visible
                    position+=visibleRange;
                    if((position+visibleRange)>endIndex) position=endIndex-visibleRange;
                    mouseDownFinish=true;                                           //accept no other input from the mouse because you need to click AGAIN
                }
            }//end not dragging not mousefinish
        }// end if scrollbar up down left right                                                                                       
    }//end left mouse click inside of container
    if(this->position!=this->lastPosition) positionChanged();
}///end handle mouse

void scrollBar::updateScrollRect(){
    //return;
    if(right-left<bottom-top) {                               // its skinnier than long... so UP DOWN...
    /*    tab.x=x+1+parentX;
        tab.w=w-2;
        tab.y=y+position+1+parentY;
        tab.h=(int)((h-2)/(endIndex-startIndex))*(h-2);
    */} else {                                            // else SIDE SIDE
        int buttonWidth=face.bottom-face.top;
        float w=(face.right-face.left)-buttonWidth*2;
        float mW=(endIndex-startIndex);
        float tabWidth=(visibleRange/mW)*w-1;
        float c1=(position/mW)*w;
        
        int calcX=(int)c1;
        tab.left=face.left+calcX+buttonWidth;
        tab.right=tab.left+tabWidth;
        tab.top=0;
        tab.bottom=face.bottom-face.top;
        
    }
}

void scrollBar::draw(){
    container::draw();
    //control::draw();
    addButton->draw();              //no recurson on continer on container action...
    minButton->draw();
    this->updateScrollRect();
    
    int l=tab.left,t=tab.top,r=tab.right,b=tab.bottom;

    drawRect(l  ,t  ,r  ,b  ,theme.controlDkShadow);
    drawRect(l  ,t  ,r-1,b-1,theme.controlHighlight);
    drawRect(l+1,t+1,r-1,b-1,theme.control);
}

void scrollBar::present(){
    container::present();
    minButton->getWorldCooridinates();
    addButton->getWorldCooridinates();
    minButton->present();
    addButton->present();
}

void scrollBar::positionChanged(){
    this->scrollEventCallBack.call();

}