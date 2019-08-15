#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <GL/glut.h>
#include <math.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 30

int animation_ongoing_r,animation_ongoing_l;
float rocket_x, rocket_y, x_goal;

void on_reshape(int width, int height);
void on_display(void);
void on_keyboard(unsigned char key, int x, int y);
void left_move(int value);
void right_move(int value);

#endif