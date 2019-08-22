#include "functions.h"

void on_reshape(int width, int height){
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 0.1, 100);
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

    
    /* iscrtavanje delova scene */
    draw_space(); /* prostor */
    glPushMatrix();
        glTranslatef(player_x,player_y,50);
        glRotatef(20*animation_parametar,0,0,1);
        glRotatef(ship_rotation_angle,0,1,0);
        draw_spaceship(); /* igrac */
    glPopMatrix();   
    draw_comets(); /* prepreke */

    /* ako nismo pokupili gorivo, ono se iscrtava */
    if(!fuel_taken)
        draw_fuel();

    /* ako je igra pocela, na ekranu se ispisuje trenutni broj poena i kolicina goriva */
    glDisable(GL_LIGHTING);
    if(game_start){
        sprintf(ispis,"SCORE: %d",player_score);
        drawBitmapText(ispis,50,31,0);
        
        draw_fuel_bar();
    }
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

void on_keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27:
      exit(0);
      break; 
    case 'a':
    case 'A':
        /* pokrece se kretanje igraca u levo */
        /* x_goal predstavlja poziciju do koje zelimo da igrac stigne. 
            Igrac se krece pomerajima od 0.5 dok ne stigne do x_goal. */
        if(!animation_ongoing_r && !animation_ongoing_l && game_start){
            x_goal = player_x - 6;
            if(x_goal >= -6){
                animation_ongoing_l = 1;
                glutTimerFunc(TIMER_PLAYER_INTERVAL,left_move,TIMER_PLAYER_ID);
            }
            else x_goal = player_x;
        }
        break;
    case 'd':
    case 'D':
         /* pokrece se kretanje igraca u desno  analogno sa kretanjem u levo */
        if(!animation_ongoing_r && !animation_ongoing_l && game_start){
            x_goal = player_x + 6;
            if(x_goal <= 6){ 
                animation_ongoing_r = 1;
                glutTimerFunc(TIMER_PLAYER_INTERVAL,right_move,TIMER_PLAYER_ID);
            }
            else x_goal = player_x;
        }
        break;
    case 32:
        /* ako je igra (ponovo) pokrenuta, inicijalizujemo parametre scene i pokrecemo tajmere */
        if(!game_start){
            initialize_params();
            comet_initialize();

            glClearColor(0,0,0,0);
            glutDisplayFunc(on_display);

            game_start = 1;
            glutTimerFunc(TIMER_INTERVAL, comet_fuel_mover_checker, TIMER_ID);
            glutTimerFunc(TIMER_FUEL_INTERVAL,fuel_timer,TIMER_FUEL_ID);

            glutPostRedisplay();
        }
        break; 
    }
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
    glBindTexture(GL_TEXTURE_2D, textures[GAMEOVER_TEXTURE]);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3f(-0.5,0,-1);

        glTexCoord2f(0, 1);
        glVertex3f(0.5,0,-1);

        glTexCoord2f(1, 1);
        glVertex3f(0.5,0,1);

        glTexCoord2f(1, 0);
        glVertex3f(-0.5,0,1);
        glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    
    glDisable(GL_LIGHTING);
    sprintf(ispis,"FINAL SCORE: %d",player_score);
    drawBitmapText(ispis,0.8,0.1,-0.12);
    drawBitmapText("PRESS SPACE TO START NEW GAME", 0.7,0.1,-0.28);
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}


void start_display(void){
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
    glBindTexture(GL_TEXTURE_2D, textures[START_TEXTURE]);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3f(-0.25,0,-0.5);

        glTexCoord2f(0, 1);
        glVertex3f(0.25,0,-0.5);

        glTexCoord2f(1, 1);
        glVertex3f(0.25,0,0.5);

        glTexCoord2f(1, 0);
        glVertex3f(-0.25,0,0.5);
        glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}


void initialize_params(){
    /* inicijalizacije parametara  */
    
    /* inicjalizacija pozicije igraca */
    player_x = x_goal = 0;
    player_y = 3;

    /* inicjalizacija flegova */
    animation_ongoing_l = animation_ongoing_r = game_start = game_over = 0;

    /* inicijalizacija parametar */ 
    comet_fuel_rotation_angle = ship_rotation_angle = 0; /* ugao rotacije kometa i broda oko njihovih osa */
    speed_parametar = 0.5; /* pocetna vrednost za pomeraj kometa i fuel kugle */
    animation_parametar = 0; /* parametar za kretanje igraca */

    player_score = 0; /* poeni igraca */
    brojac = 0; /* brojac za podesavanje brzine kretanja kometa i kugla goriva */

    fuel_taken = 0; /* flag koji registruje da li je igrac pokupio gorivo */
    fuel = 100;  /* kolicina goriva broda */
    make_fuel(); 

    srand(time(NULL));
}
