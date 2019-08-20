/* Zajednicke promenljive */

#ifndef __COMMON_H__
#define __COMMON_H__

#include "textures.h"
#include "bitmaps.h"
#include <time.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 3

#define TIMER_ID1 1
#define TIMER_INTERVAL1 2

#define TIMER_ID2 2
#define COMET_NUMBER 20


int interval_comet_generate;
int i,brojac;
int animation_ongoing_r,animation_ongoing_l, generate_flag;
float player_x, player_y, x_goal;
int player_score; 
char ispis[64];
int game_over, game_start;
float rotation_angle;
float animation_parametar;

typedef struct comet_struct{
    int x1;
    int x2;
    float z_pos;
    int first;
    int second;
} comet_line;

comet_line comet_array[COMET_NUMBER];


const static float pi = 3.141592653589793;

#endif 
