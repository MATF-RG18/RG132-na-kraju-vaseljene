#ifndef __OBSTACLES_FUEL_H__
#define __OBSTACLES_FUEL_H__

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "common.h"
#include "functions.h"

void make_comet(int k); /* stvaranje jedne komete na poziji k u nizu comet_array */
void comet_initialize(); 
void draw_comets(); /* iscrtava komete po linijama */

void comet_fuel_mover_checker(int value); /* generise i pokrece komete i kugle goriva */

void draw_fuel(); /* funkcija za iscrtavanje kugle koja predstavlja gorivo */
void make_fuel(); /* funkcija koja generise novu kuglu goriva */
void draw_fuel_bar(); /* funkcija za iscrtavanje statusa goriva */
void fuel_timer(int value); /* tajmer pomocu kojeg se smanjuje kolicina goriva */

#endif 
