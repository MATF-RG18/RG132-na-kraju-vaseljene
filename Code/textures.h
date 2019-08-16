#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "image.h"
#include <GL/glut.h>

#define LIGHT_FILENAME "svetlo.bmp"
#define STARS_FILENAME "stars.bmp"
#define COMET_FILENAME "comet.bmp"

#define LIGHT_TEXTURE 0
#define STARS_TEXTURE 1
#define COMET_TEXTURE 2

GLuint names[3];

void initialize_textures();

#endif
