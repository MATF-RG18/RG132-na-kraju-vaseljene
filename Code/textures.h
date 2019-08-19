#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "image.h"
#include <GL/glut.h>

#define LIGHT_FILENAME "Teksture/svetlo.bmp"
#define STARS_FILENAME "Teksture/stars.bmp"
#define COMET_FILENAME "Teksture/comet.bmp"
#define GAMEOVER_FILENAME "Teksture/game_over.bmp"
#define START_FILENAME "Teksture/start.bmp"

#define LIGHT_TEXTURE 0
#define STARS_TEXTURE 1
#define COMET_TEXTURE 2
#define GAMEOVER_TEXTURE 3
#define START_TEXTURE 4

GLuint names[3];

void initialize_textures();

#endif
