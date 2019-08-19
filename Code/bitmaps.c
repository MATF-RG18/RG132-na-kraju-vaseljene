#include "bitmaps.h"

void drawBitmapText(char *str,float x,float y,float z){  
    
    glColor3f(1,1,1);
    glRasterPos3f(x,y,z);

    int i;
    int len = strlen(str);
    for (i=0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,str[i]);
    }
}
