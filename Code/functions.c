#include "functions.h"
#include "draw.h"

#include <stdio.h>

void on_reshape(int width, int height){
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 200);
}

void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  
    int depth = 50;
    int width = 20;
    int height = 10;
    /* podesavanje vidne tacke */
    gluLookAt(0,10,65,
            0,0,0,
            0,1,0);  

    /* Podesavanje komponenti svetla */
    glEnable(GL_LIGHT0);

    GLfloat light_ambient[] = { 0,0,0,1 };
    GLfloat light_diffuse[] =  { 0.7,0.7,0.7,1};
    GLfloat light_specular[] =  {.9,.9,.9,1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Iscrtavanje objekata: put i igrac */
    draw_debug_coosys();
    draw_path(width/2,height,depth);
    glPushMatrix();
        glTranslatef(rocket_x,rocket_y,depth-2); 
        draw_spaceship();
    glPopMatrix();    

    glutSwapBuffers();
}

void on_keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27:
      exit(0);
      break; 
    case 97: /* pokrece se kretanje igraca u levo */
        if(!animation_ongoing_r && !animation_ongoing_l){
            x_goal = rocket_x - 6;
            if(x_goal >= -6){
                animation_ongoing_l = 1;
                glutTimerFunc(TIMER_INTERVAL,left_move,TIMER_ID);
            }
            else x_goal = rocket_x;
        }
        break;
    case 100: /* pokrece se kretanje igraca u desno */
        if(!animation_ongoing_r && !animation_ongoing_l){
            x_goal = rocket_x + 6;
            if(x_goal <= 6){ 
                animation_ongoing_r = 1;
                glutTimerFunc(TIMER_INTERVAL,right_move,TIMER_ID);
            }
            else x_goal = rocket_x;
        }
        break;
    }
}

void left_move(int value){
    if(value != TIMER_ID)
        return;

    if(rocket_x - 0.5 > x_goal){
        rocket_x -= 0.5;
        animation_ongoing_l = 1;
        glutPostRedisplay();
        glutTimerFunc(TIMER_INTERVAL,left_move,TIMER_ID);
    }
    else animation_ongoing_l = 0;
}

void right_move(int value){
    if(value != TIMER_ID)
        return;

    if(rocket_x + 0.5 < x_goal){
        rocket_x += 0.5;
        animation_ongoing_r = 1;
        glutPostRedisplay();
        glutTimerFunc(TIMER_INTERVAL,right_move,TIMER_ID);
    }
    else animation_ongoing_r = 0;
}


