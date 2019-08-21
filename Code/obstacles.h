/* Generisanje i izgled prepreka */
#ifndef __OBSTACLES_H__
#define __OBSTACLES_H__

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "common.h"

void make_comet(int k);
void comet_initialize();
void draw_comets();
void comet_generator(int value);

#endif 