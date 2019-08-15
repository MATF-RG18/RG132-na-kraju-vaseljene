#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "draw.h"
#include "functions.h"

int main(int argc, char **argv){

    /* Inicijalizacija gluta */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       
    //glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Na kraju vaseljene");
    glutFullScreen();

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    /* Omogucavanje svetla i njegovo pozicioniranje */
    glEnable(GL_LIGHTING);
    GLfloat light_position[] = {0,0,0,1}; /* direkciono svetlo */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    rocket_x = x_goal = 0;
    rocket_y = 3;
    animation_ongoing_l = animation_ongoing_r = 0;

    glutMainLoop();

    return 0;
}