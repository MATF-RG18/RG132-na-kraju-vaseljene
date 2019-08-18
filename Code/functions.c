#include "functions.h"

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


    //draw_debug_coosys();
    
    /* iscrtavanje delova scene */
    draw_space(); /* prostor */
    draw_path(10,10,54); /* put po kom se igrac krece */
    glPushMatrix();
        glTranslatef(rocket_x,rocket_y,50);  
        glEnable(GL_LIGHT1);   
        draw_spaceship(); /* igrac */
    glPopMatrix();   
    draw_comets(); /* prepreke */


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
        if(!animation_ongoing_r && !animation_ongoing_l && game_ongoing){
            x_goal = rocket_x - 6;
            if(x_goal >= -6){
                animation_ongoing_l = 1;
                glutTimerFunc(TIMER_INTERVAL,left_move,TIMER_ID);
            }
            else x_goal = rocket_x;
        }
        break;
    case 100: /* pokrece se kretanje igraca u desno */
        if(!animation_ongoing_r && !animation_ongoing_l && game_ongoing){
            x_goal = rocket_x + 6;
            if(x_goal <= 6){ 
                animation_ongoing_r = 1;
                glutTimerFunc(TIMER_INTERVAL,right_move,TIMER_ID);
            }
            else x_goal = rocket_x;
        }
        break;
    case 'p':
    case 'P':
        /* pauza zaustavlja igru */
        if(game_ongoing)
            game_ongoing = 0;
        else {
            game_ongoing = 1;
        }
        break;
    case 'r':
    case 'R':
        /* reset, pokrece igricu ponovo */

        break; 
    }
}

void collision(int value){
    if(value != TIMER_COLLISION)
        return;

    /* Funckija koja regulise sudare. Prolazi kroz sve prepreke(nalaze se u nizu comet_array),
        detektuje da li se pozicija neke od njih poklapa sa pozicijom igraca, i ukoliko se poklapa,
        igra se prekida uz ispis odgovarajuce poruke   */     
    int j;
    for(j=0;j<COMET_NUMBER;j++){
        if((comet_array[j].x1 + 2 >= rocket_x && comet_array[j].x1 - 2 <= rocket_x) || (comet_array[j].x2 + 2 >= rocket_x && comet_array[j].x2 - 2 <= rocket_x))
            if(comet_array[j].z_pos >= 47 &&  comet_array[j].z_pos <= 53){
                printf("GameOver x1\n");
                game_ongoing = 0;
                //game_over_display();
                exit(1);    
            }
    }
    glutTimerFunc(COLLISION_INTERVAL,collision,TIMER_COLLISION);
}


void game_over_display(){
}
