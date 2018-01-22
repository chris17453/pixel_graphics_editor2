/*  
 * File:   themes.h
 * Author: nd
 *
 * Created on December 12, 2015, 11:09 AM
 */
#include "types.h"

#ifndef THEMES_H
#define	THEMES_H
class gui_theme{
public:;

    color activeCaption;
    color activeCaptionBorder;
    color activeCaptionText;
    color control;
    color controlDkShadow;
    color controlHighlight;
    color controlLtHighlight;
    color controlShadow;
    color controlText;
    color desktop;
    color inactiveCaption;
    color inactiveCaptionBorder;
    color inactiveCaptionText;
    color info;
    color infoText;
    color menu;
    color menuText;
    color scrollbar;
    color text;
    color textHighlight;
    color textHighlightText;
    color textInactiveText;
    color textText;
    color window;
    color windowBorder;
    color windowText;

    enum THEME_NAMES{   THEME_BLUE,THEME_OLIVE_GREEN,THEME_SILVER,THEME_CLASSIC_1,THEME_CLASSIC_2,THEME_BRICK,THEME_DESERT,THEME_EGGPLANT,THEME_LILAC,
                        THEME_MAPLE,THEME_MARE,THEME_PLUM,THEME_PUMPKIN,THEME_RAINY_DAY,THEME_RED_WHITE_BLUE,THEME_ROSE,THEME_SLATE,THEME_SPRUCE,
                        THEME_STORM,THEME_TEAL,THEME_WHEAT,THEME_HIGH_CONTRAST_1,THEME_HIGH_CONTRAST_2,THEME_HIGH_CONTRAST_3,THEME_HIGH_CONTRAST_4 };
     
    void setTheme(const char *name
                    ,unsigned long activeCaption        ,unsigned long activeCaptionBorder  ,unsigned long activeCaptionText  ,unsigned long control        
                    ,unsigned long controlDkShadow      ,unsigned long controlHighlight     ,unsigned long controlLtHighlight ,unsigned long controlShadow
                    ,unsigned long controlText          ,unsigned long desktop              ,unsigned long inactiveCaption    ,unsigned long inactiveCaptionBorder
                    ,unsigned long inactiveCaptionText  ,unsigned long info                 ,unsigned long infoText           ,unsigned long menu                 
                    ,unsigned long menuText             ,unsigned long scrollbar            ,unsigned long text               ,unsigned long textHighlight        
                    ,unsigned long textHighlightText    ,unsigned long textInactiveText     ,unsigned long textText           ,unsigned long window               
                    ,unsigned long windowBorder         ,unsigned long windowText);
    bool loadTheme(int theme);
        
};




#endif	/* THEMES_H */

