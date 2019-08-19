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

#define TIMER_COLLISION 3
#define COLLISION_INTERVAL 3

void on_reshape(int width, int height);
void on_display(void);
void on_keyboard(unsigned char key, int x, int y);

void collision(int value);
void point_timer(int value);

void game_over_display(void);
void start_display(void);

void draw_coosys();
void initialize_params();

#endif