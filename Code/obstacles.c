#include "obstacles.h"
#include "functions.h"


void comet_initialize(){
   int k;
   for(k=0;k<COMET_NUMBER;k++){
        make_comet(k);
        comet_array[k].z_pos = -50 - 30*k;
   }
}

/* funkcija za animaciju pomeranja prepreka  */
void comet_generator(int value){
    if(game_over)
        return;

    if(value != TIMER_COMET_ID)
        return;

    /* Ukoliko je igra u toku, i ukoliko treba generisati novu prepreku, onda se rand() funkcijom
        bira polje koje ce ostati prazno, dok se na ostala dva iscrtavaju komete(to je informacija 
        koju pamtimo u strukturi za komete). Pomeramo sve generisane komete za 0.5 ka igracu */

    int j;
    int i = -1;
    for(j=0;j<COMET_NUMBER;j++){
        comet_array[j].z_pos += speed_parametar; /* izmenom ove velicine, ubrzavamo ili usporavamo komete */
        if(comet_array[j].z_pos >= 60){
            player_score += 10;
            i = j;
        } 

        if(fuel == 0){
            game_over = 1;
            game_start = 0;
            glutDisplayFunc(game_over_display);
            glutPostRedisplay();
        }

        if((comet_array[j].x1 + 2 >= player_x && comet_array[j].x1 - 2 <= player_x) || (comet_array[j].x2 + 2 >= player_x && comet_array[j].x2 - 2 <= player_x))
            if(comet_array[j].z_pos >= 47 &&  comet_array[j].z_pos <= 53){
                game_over = 1;
                game_start = 0;
                glutDisplayFunc(game_over_display);
                glutPostRedisplay();
        }

        if((f.x_pos + 1 >= player_x && f.x_pos - 1 <= player_x) || (f.x_pos + 1 >= player_x && f.x_pos - 1 <= player_x))
            if(f.z_pos >= 47 && f.z_pos <= 53){
                fuel_taken = 1;
                fuel = 100;
            }
    }

    f.z_pos += speed_parametar;
    if(f.z_pos > 70)
        make_fuel();
        
    if(i!=-1){
        brojac++;
        if(brojac % 10 == 0 && speed_parametar < 0.7){
            speed_parametar += 0.06;
        }
        
        comet_array[i].z_pos = -240;
    }


    glutPostRedisplay();
    glutTimerFunc(TIMER_COMET_INTERVAL, comet_generator, TIMER_COMET_ID);
}


void draw_comets(){
    /* Iscrtava komete na pozicijama na kojima se trenutno nalaze u commet_array */
    comet_line c;
    int j;

    GLUquadricObj *quadric_object = gluNewQuadric();
    gluQuadricDrawStyle(quadric_object, GLU_FILL);
    gluQuadricTexture(quadric_object, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    for(j=0;j<COMET_NUMBER;j++){
        c = comet_array[j];

        /* iscrtava dve komete u jednoj liniji*/
        glBindTexture(GL_TEXTURE_2D, textures[c.first]);
        glPushMatrix();
            glTranslatef(c.x1,3,c.z_pos);  
            glRotatef(-110,1,0,0);
            gluSphere(quadric_object, 2.2, 5, 5);
        glPopMatrix();

        
        glBindTexture(GL_TEXTURE_2D, textures[c.second]);
        glPushMatrix();
            glTranslatef(c.x2,3,c.z_pos); 
            glRotatef(-110,1,0,0);
            gluSphere(quadric_object, 2.2, 5, 5);   
        glPopMatrix();
    }
    
    glDisable(GL_TEXTURE_2D);
}

void make_comet(int k){
    int empty_place,x1,x2;
    empty_place = rand() % 3;

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


    comet_array[k].x1 = x1;
    comet_array[k].x2 = x2;
    int first = rand() % 2 == 0 ? COMET_TEXTURE : COMET2_TEXTURE;
    int second = rand() % 2 == 0 ? COMET_TEXTURE : COMET2_TEXTURE;
    comet_array[k].first = first;
    comet_array[k].second = second;
}