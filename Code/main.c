#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "scene.h"
#include "functions.h"
#include "obstacles.h"
#include "player.h"
#include "textures.h"

int main(int argc, char **argv){

    /* Inicijalizacija gluta */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       
    /* Inicijaliacija prozora */
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Na kraju vaseljene");
    glutFullScreen();

    /* Postavljanje callback funkcija */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST); 
    
    /* Podesavanje svetla */
    glEnable(GL_LIGHTING); 
    GLfloat light_ambient[] = { 0,0,0,1 };
    GLfloat light_diffuse[] =  { 0.7,0.7,0.7,1};
    GLfloat light_specular[] =  {.9,.9,.9,1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    comet_initialize();
    initialize_params();
    initialize_textures();

    glutMainLoop();

    return 0;
}
