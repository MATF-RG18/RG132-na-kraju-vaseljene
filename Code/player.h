/* Iscrtavanje i kretanje igraca */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <GL/glut.h>
#include <math.h> 
#include <stdio.h>
#include "textures.h"
#include "common.h"

void draw_spaceship();
void set_normal_and_vertex(float u, float v);
void left_move(int value);
void right_move(int value);

#endif 