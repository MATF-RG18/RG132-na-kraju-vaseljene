#ifndef __DRAW_H__
#define __DRAW_H__

#include <GL/glut.h>
#include <math.h> 

const static float pi = 3.141592653589793;

void set_normal_and_vertex(float u, float v);
void draw_debug_coosys(); /* pomocna funkcija za iscrtavanje koordinata  */

void draw_spaceship();
void draw_path(float a, float b, float c);

#endif