#ifndef __DRAW_H__
#define __DRAW_H__

#include <GL/glut.h>
#include <math.h> 
#include <stdio.h>

const static float pi = 3.141592653589793;

typedef struct comet_struct{
    int x1;
    int x2;
    float z_pos;
} comet_line;

comet_line comet_array[8];

int i;

void set_normal_and_vertex(float u, float v);
void draw_debug_coosys(); /* pomocna funkcija za iscrtavanje koordinata  */

void draw_spaceship();
void draw_path(float a, float b, float c);
void draw_comets();

#endif