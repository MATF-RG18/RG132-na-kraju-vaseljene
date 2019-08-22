#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "common.h"
#include "player.h"
#include "obstacles_fuel.h"
#include "scene.h"

void on_reshape(int width, int height); 

/* callback display funkcije */
void on_display(void); /* ekran za tok igrice */
void game_over_display(void); /* ekran za kraj igrice */
void start_display(void); /* ekran za pocetak igrice */

void on_keyboard(unsigned char key, int x, int y);

void initialize_params(); /* funkcija inicijalizuje parametre igrice */

#endif
