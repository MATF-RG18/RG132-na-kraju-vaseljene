#include "functions.h"
#include "draw.h"
#include "textures.h"

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
    
    /* odredjivanje pozicije svetla */ 
    GLfloat light_position[] = {0,0,0,1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    
    /* podesavanje vidne tacke */
    gluLookAt(0,10,65,
            0,0,0,
            0,1,0); 

    draw_debug_coosys();

    draw_space();
    /* iscrtavanje elemenata scene: put, igrac i prepreke */
    int depth = 54;
    int width = 20;
    int height = 10;
    draw_path(width/2,height,depth);
    glPushMatrix();
        glTranslatef(rocket_x,rocket_y,depth-4); 
        glEnable(GL_LIGHT1);   
        draw_spaceship();
    glPopMatrix();    

    double clip_plane[] = {0,0,1,50};
    glClipPlane(GL_CLIP_PLANE0, clip_plane);
    glEnable(GL_CLIP_PLANE0);
    draw_comets();

    glutSwapBuffers();
}

void game_over_display(){
    

    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(0,1);
        glVertex2f(1,1);
        glVertex2f(1,0);
    glEnd();
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

    if(rocket_x - 0.5 >= x_goal){
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

    if(rocket_x + 0.5 <= x_goal){
        rocket_x += 0.5;
        animation_ongoing_r = 1;
        glutPostRedisplay();
        glutTimerFunc(TIMER_INTERVAL,right_move,TIMER_ID);
    }
    else animation_ongoing_r = 0;
}

/* funkcija za animaciju pomeranja prepreka  */
void comet_generator(int value){
    if(value != TIMER_ID1)
        return;
    
    if(generate_flag){
        int empty_place,x1,x2;
        i = i%7;
        empty_place = rand() % 3;

        comet_array[i].z_pos = -50;

        switch(empty_place){
            case 0:
                x1 = 0;
                x2 = 6;
                break;
            case 1:
                x1 = -6;
                x2 = 6;
                break;
            case 2:
                x1 = -6;
                x2 = 0;
                break;
        }

        comet_array[i].x1 = x1;
        comet_array[i].x2 = x2;
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

void collision(int value){
    if(value != TIMER_COLLISION)
        return;
     
    int j;
    for(j=0;j<8;j++){
        if(comet_array[j].x1 + 2 >= rocket_x && comet_array[j].x1 - 2 <= rocket_x){
            if(comet_array[j].z_pos == 50){
                printf("GameOver x1\n");
                exit(1);    
            }
        }
        if(comet_array[j].x2 + 2 >= rocket_x && comet_array[j].x2 - 2 <= rocket_x){
            if(comet_array[j].z_pos >= 47 &&  comet_array[j].z_pos <= 53){
                printf("GameOver x2\n!");
                exit(1);    
            }
        }
    }

    glutTimerFunc(COLLISION_INTERVAL,collision,TIMER_COLLISION);
}