/* Promenljive i strukture */
#ifndef __COMMON_H__
#define __COMMON_H__

#include "textures.h"
#include "bitmaps.h"
#include <time.h>

const static float pi = 3.141592653589793;

#define TIMER_PLAYER_ID 0
#define TIMER_PLAYER_INTERVAL 2

#define TIMER_ID 1
#define TIMER_INTERVAL 2
#define COMET_NUMBER 10

#define TIMER_FUEL_ID 2
#define TIMER_FUEL_INTERVAL 20

unsigned brojac; /* brojac za podesavanje brzine kretanja kometa i kugla goriva */ 
int animation_ongoing_r,animation_ongoing_l, game_ongoing; /* flegovi */
float player_x, player_y, x_goal; /* pozicija igraca */
float animation_parametar, speed_parametar; /* parametri kretanja igraca */ 
unsigned comet_fuel_rotation_angle, ship_rotation_angle; 
int player_score; 
char ispis[64]; 
float fuel; /* preostala kolicina goriva igraca */
int fuel_taken; 

typedef struct comet_struct{
    int x1; /* prva pozicija komete */
    int x2; /* druga pozicija komete */
    float z_pos; 
    int first; /* tekstura za prvu kometu */
    int second; /* tekstura za drugu kometu */
} comet_line;

typedef struct fuel_struct {
    int x_pos;
    float z_pos;
} fuel_object;
fuel_object f;

comet_line comet_array[COMET_NUMBER];

#endif 
