#ifndef __FUEL_H__
#define __FUEL_H__

#include <GL/glut.h>
#include "common.h"

void draw_fuel(); /* funkcija za iscrtavanje kugle koja predstavlja gorivo */
void make_fuel(); /* funkcija koja generise novu kuglu goriva */
void draw_fuel_bar(); /* funkcija za iscrtavanje statusa goriva */

void fuel_timer(int value); /* tajmer pomocu kojeg se smanjuje kolicina goriva */

#endif