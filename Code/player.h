/* Iscrtavanje i kretanje igraca */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <GL/glut.h>
#include <math.h> 
#include <stdio.h>
#include "textures.h"
#include "common.h"

void draw_spaceship(); /* funkcija za iscrtavanje svemirskog broda */
void set_normal_and_vertex(float u, float v); /* pomocna funkcija za iscrtavanje polulopte */
void left_move(int value); /* tajmer postavljen za pomeranje igraca u levo */
void right_move(int value); /* tajmer postavljen za pomeranje igraca u levo */

#endif 