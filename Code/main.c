#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "draw.h"
#include "functions.h"
#include "textures.h"

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
    
    /* Omogucavanje svetla i*/
    glEnable(GL_LIGHTING);

    /* Podesavanje komponenti glavnog svetla */  
    GLfloat light_ambient[] = { 0,0,0,1 };
    GLfloat light_diffuse[] =  { 0.7,0.7,0.7,1};
    GLfloat light_specular[] =  {.9,.9,.9,1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


    /* inicijalizacije nekih parametara  */
    rocket_x = x_goal = 0;
    rocket_y = 3;
    animation_ongoing_l = animation_ongoing_r = 0;
    
    srand(time(NULL));
    initialize_textures();

    glutTimerFunc(TIMER_INTERVAL1,comet_generator,TIMER_ID1);
    glutTimerFunc(TIMER_INTERVAL2,generate_new,TIMER_ID2);
    glutTimerFunc(COLLISION_INTERVAL,collision,TIMER_COLLISION);
 
    glutMainLoop();

    return 0;
}
