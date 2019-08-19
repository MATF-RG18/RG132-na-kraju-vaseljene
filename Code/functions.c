#include "functions.h"


void on_reshape(int width, int height){
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 0.1, 200);
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

    //draw_debug_coosys();
    
    /* iscrtavanje delova scene */
    draw_space(); /* prostor */
    //draw_path(10,10,54); /* put po kom se igrac krece */
    glPushMatrix();
        glTranslatef(rocket_x,rocket_y,50);  
        draw_spaceship(); /* igrac */
    glPopMatrix();   
    draw_comets(); /* prepreke */

    glDisable(GL_LIGHTING);
    if(!game_start){
        drawBitmapText("PRESS S TO START NEW GAME",-13,15,50);
    }

    if(game_start){
        sprintf(ispis,"SCORE: %.3f",player_score);
        drawBitmapText(ispis,10,15,50);
    }

    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

void on_keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27:
      exit(0);
      break; 
    case 97: /* pokrece se kretanje igraca u levo */
        /* x_goal predstavlja poziciju do koje zelimo da igrac stigne. 
            Igracevo kretanje se odvija tako sto ga, koriscenjem tajmera,
            pomeramo za 0.5 sve dok ne stigne do x_goal   */
        if(!animation_ongoing_r && !animation_ongoing_l && game_start){
            x_goal = rocket_x - 6;
            if(x_goal >= -6){
                animation_ongoing_l = 1;
                glutTimerFunc(TIMER_INTERVAL,left_move,TIMER_ID);
            }
            else x_goal = rocket_x;
        }
        break;
    case 100: /* pokrece se kretanje igraca u desno */
        if(!animation_ongoing_r && !animation_ongoing_l && game_start){
            x_goal = rocket_x + 6;
            if(x_goal <= 6){ 
                animation_ongoing_r = 1;
                glutTimerFunc(TIMER_INTERVAL,right_move,TIMER_ID);
            }
            else x_goal = rocket_x;
        }
        break;
    case 's':
    case 'S':
        /* ukoliko je igra pokrenuta, pokrecemo tajmere */
        if(!game_start){
            initialize_params();
            comet_initialize();

            glClearColor(0,0,0,0);
            glutDisplayFunc(on_display);

            player_score = 0;
            game_start = 1;
            glutTimerFunc(TIMER_INTERVAL1,comet_generator,TIMER_ID1);
            interval_comet_generate = 1000;
            points = 0.1;

            glutTimerFunc(interval_comet_generate,generate_new,TIMER_ID2);
            glutTimerFunc(COLLISION_INTERVAL,collision,TIMER_COLLISION);

            glutPostRedisplay();
        }
        break; 
    }
}

void collision(int value){
    if(value != TIMER_COLLISION)
        return;

    if(game_over)
        return;
    /* Funckija koja regulise sudare. Prolazi kroz sve prepreke(nalaze se u nizu comet_array),
        detektuje da li se pozicija neke od njih poklapa sa pozicijom igraca, i ukoliko se poklapa,
        igra se prekida uz ispis odgovarajuce poruke   */     
    int j;
    for(j=0;j<COMET_NUMBER;j++){
        if((comet_array[j].x1 + 2 >= rocket_x && comet_array[j].x1 - 2 <= rocket_x) || (comet_array[j].x2 + 2 >= rocket_x && comet_array[j].x2 - 2 <= rocket_x))
            if(comet_array[j].z_pos >= 47 &&  comet_array[j].z_pos <= 53){
                game_over = 1;
                game_start = 0;
                glutDisplayFunc(game_over_display);
                glutPostRedisplay();
               //exit(1);    
            }
    }

    glutTimerFunc(COLLISION_INTERVAL,collision,TIMER_COLLISION);
}


void game_over_display(void){
    glClearColor(0,0,0,0);  
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,2,0,
              0,0,0,
              1,0,0);

    GLfloat light_position[] = {0,0,0,1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[GAMEOVER_TEXTURE]);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3f(-0.7,0,-1.2);

        glTexCoord2f(0, 1);
        glVertex3f(0.7,0,-1.2);

        glTexCoord2f(1, 1);
        glVertex3f(0.7,0,1.2);

        glTexCoord2f(1, 0);
        glVertex3f(-0.7,0,1.2);
        glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    
    glDisable(GL_LIGHTING);
    sprintf(ispis,"FINAL SCORE: %.3f",player_score);
    drawBitmapText(ispis,0.8,0.1,-0.16);
    drawBitmapText("PRESS S TO START NEW GAME", 0.7,0.1,-0.26);
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}


void draw_coosys(){
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(20,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,20,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,20);

    glEnd();
    glEnable(GL_LIGHTING);
}

void initialize_params(){
    /* inicijalizacije nekih parametara  */
    rocket_x = x_goal = 0;
    rocket_y = 3;
    animation_ongoing_l = animation_ongoing_r = player_score = game_start = 0;
    game_over = 0;

    srand(time(NULL));
}