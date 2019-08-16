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

    int depth = 50;
    int width = 20;
    int height = 10;
    draw_path(width/2,height,depth);
    glPushMatrix();
        glTranslatef(rocket_x,rocket_y,depth-2); 
        draw_spaceship();
    glPopMatrix();    

    draw_comets();

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

void comet_generator(int value){
    if(value != TIMER_ID1)
        return;
    
    if(generate_flag){
        int empty_place;
        i = i%7;
        empty_place = rand() % 3;

        comet_array[i].z_pos = -50;
        comet_array[i].empty_place = empty_place;
        i = i+1;
        generate_flag = 0;
    }

    int j;
    for(j=0;j<8;j++){
        comet_array[j].z_pos += 0.5;
    }

    glutPostRedisplay();
    glutTimerFunc(TIMER_INTERVAL1, comet_generator, TIMER_ID1);
}

void generate_new(int value){
    if(value != TIMER_ID2)
        return;

    generate_flag = 1;
    glutTimerFunc(TIMER_INTERVAL2,generate_new,TIMER_ID2);
}

/*
void comet_init(){
    comet_array[0].z_pos = -50;
    comet_array[1].z_pos = -100;
    comet_array[2].z_pos = -150;
    comet_array[3].z_pos = -200;
    comet_array[4].z_pos = -250;
    comet_array[5].z_pos = -300;
    comet_array[6].z_pos = -350;
    comet_array[7].z_pos = -400;


    comet_array[0].empty_place = rand()%3;
    comet_array[1].empty_place = rand()%3;
    comet_array[2].empty_place = rand()%3;
    comet_array[3].empty_place = rand()%3;
    comet_array[4].empty_place = rand()%3;
    comet_array[5].empty_place = rand()%3;
    comet_array[6].empty_place = rand()%3;
    comet_array[7].empty_place = rand()%3;
}
*/