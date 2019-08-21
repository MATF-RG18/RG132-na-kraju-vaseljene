/* Opste callback funkcije i funkcija kolizije */
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "common.h"
#include "player.h"
#include "obstacles.h"
#include "scene.h"

void on_reshape(int width, int height);
void on_display(void);
void game_over_display(void);
void on_keyboard(unsigned char key, int x, int y);

void initialize_params();

#endif