#include "bitmaps.h"

void drawBitmapText(char *str,float x,float y,float z){  
	char *c;
	glColor3f(1,1,1);
	glRasterPos3f(x,y,z);

	for (c=str; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
	}
}