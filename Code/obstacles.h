/* Generisanje i izgled prepreka */
#ifndef __OBSTACLES_H__
#define __OBSTACLES_H__

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "common.h"

void make_comet(int k); /* stvaranje jedne komete na poziji k u nizu comet_array */
void comet_initialize(); 
void draw_comets(); /* iscrtava komete po linijama */
void comet_generator(int value); /* generise i pokrece komete  */

#endif 