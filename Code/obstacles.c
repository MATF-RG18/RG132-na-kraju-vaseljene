#include "obstacles.h"

void comet_initialize(){
    int k;
    for(k=0;k<COMET_NUMBER;k++)
        comet_array[k].z_pos = -1000;
}

/* funkcija za animaciju pomeranja prepreka  */
void comet_generator(int value){
    if(value != TIMER_ID1)
        return;

    if(game_over)
        return;

    /* Ukoliko je igra u toku, i ukoliko treba generisati novu prepreku, onda se rand() funkcijom
        bira polje koje ce ostati prazno, dok se na ostala dva iscrtavaju komete(to je informacija 
        koju pamtimo u strukturi za komete). Pomeramo sve generisane komete za 0.5 ka igracu */

    if(generate_flag){
        int empty_place,x1,x2;
        i = i%COMET_NUMBER;
        brojac++;
        /* ubrzava se generisanje novih kometa */
        if(brojac % 10 == 0){
            if(interval_comet_generate > 300){
                interval_comet_generate -= 50;
                points += 0.1;
            }
        }
        empty_place = rand() % 3;

        comet_array[i].z_pos = -70;

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
    for(j=0;j<COMET_NUMBER;j++)
        comet_array[j].z_pos += 0.5; /* izmenom ove velicine, ubrzavamo ili usporavamo komete */

    glutPostRedisplay();

    glutTimerFunc(TIMER_INTERVAL1, comet_generator, TIMER_ID1);
}

void generate_new(int value){
    if(value != TIMER_ID2)
        return;

    if(game_over)
        return;
    /* Odredjuje kada je potrebno generisati novu kometu */
    generate_flag = 1;
    player_score += points;
    glutTimerFunc(interval_comet_generate,generate_new,TIMER_ID2);
}


void draw_comets(){
    /* Iscrtava komete na pozicijama na kojima se trenutno nalaze u commet_array */
    comet_line c;
    int j;
    GLUquadricObj *quadric_object = gluNewQuadric();
    gluQuadricDrawStyle(quadric_object, GLU_FILL);
    gluQuadricTexture(quadric_object, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[COMET_TEXTURE]);
    for(j=0;j<COMET_NUMBER;j++){
        c = comet_array[j];

        /* iscrtava dve komete u jednoj liniji*/
        glPushMatrix();
            glTranslatef(c.x1,3,c.z_pos);  
            glRotatef(-110,1,0,0);
            gluSphere(quadric_object, 2.2, 5, 5);
            glRotatef(50,0,1,0);
            gluSphere(quadric_object, 2, 5, 5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(c.x2,3,c.z_pos); 
            glRotatef(-110,1,0,0);
            gluSphere(quadric_object, 2.2, 5, 5);     
            glRotatef(50,0,1,0);
            gluSphere(quadric_object, 2, 5, 5);
            glScalef(4,4,4);
        glPopMatrix();

    }
    glDisable(GL_TEXTURE_2D);
}

/*
void fog(){
    
    GLfloat fog_color[] = {0.5, 0.9, 0.5, 1.0};
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE,GL_LINEAR);
    glFogfv(GL_FOG_COLOR,fog_color);
    glFogf(GL_FOG_START, 4.0f);
    glFogf(GL_FOG_END, 10.0f);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glDisable(GL_FOG);
}
*/
