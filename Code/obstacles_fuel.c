#include "obstacles_fuel.h"

void comet_initialize(){
   int k;
   for(k=0;k<COMET_NUMBER;k++){
        make_comet(k);
        comet_array[k].z_pos = -50 - 30*k;
   }
}


void comet_fuel_mover_checker(int value){
    if(!game_ongoing)
        return;
    
    comet_fuel_rotation_angle += 2;

    if(value != TIMER_ID)
        return;

    int j;
    int i = -1;
    for(j=0;j<COMET_NUMBER;j++){
        comet_array[j].z_pos += speed_parametar; /* pomeramo sve komete unapred ga igracu */
        if(comet_array[j].z_pos >= 60){
            player_score += 10; /* kad kometa prodje pored igraca, njegov score se uvecava */
            i = j; /* pamtimo poziciju u nizu komete koja je prosla igraca */
        } 

        /* Ako nije preostalo goriva -> kraj igrice */
        if(fuel == 0){
            game_ongoing = 0;
            glutDisplayFunc(game_over_display);
            glutPostRedisplay();
        }

        /* ako igrac udario u neku od kometa -> kraj igrice */
        if((comet_array[j].x1 + 2 >= player_x && comet_array[j].x1 - 2 <= player_x) || (comet_array[j].x2 + 2 >= player_x && comet_array[j].x2 - 2 <= player_x))
            if(comet_array[j].z_pos >= 47 &&  comet_array[j].z_pos <= 53){
                game_ongoing = 0;
                glutDisplayFunc(game_over_display);
                glutPostRedisplay();
        }

        /* provera da li je igrac sakupio kuglu goriva */
        if((f.x_pos + 1 >= player_x && f.x_pos - 1 <= player_x) || (f.x_pos + 1 >= player_x && f.x_pos - 1 <= player_x))
            if(f.z_pos >= 47 && f.z_pos <= 53){
                fuel_taken = 1;
                fuel = 100;
            }
    }

    /* pomeranje kugle goriva */
    f.z_pos += speed_parametar;
    if(f.z_pos > 70)
        make_fuel(); /* generisanje nove kugle goriva*/
        
    /* ukoliko je neka kometa prosla igraca, ciklicno generisemo novu kometu 
        kada prodje 10 takvih kometa, ubrzavamo kretanje kometa do odredjene granice */
    if(i!=-1){
        brojac++;
        if(brojac % 10 == 0 && speed_parametar < 0.7){
            speed_parametar += 0.06;
        }
        
        comet_array[i].z_pos = -240;
    }


    glutPostRedisplay();
    glutTimerFunc(TIMER_INTERVAL, comet_fuel_mover_checker, TIMER_ID);
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

        /* crta dve komete u jednoj liniji */
        glBindTexture(GL_TEXTURE_2D, textures[c.first]);
        glPushMatrix();
            glTranslatef(c.x1,3,c.z_pos);  
            glRotatef(comet_fuel_rotation_angle,1,-2,2);
            gluSphere(quadric_object, 2.2, 7, 7);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, textures[c.second]);
        glPushMatrix();
            glTranslatef(c.x2,3,c.z_pos); 
            glRotatef(comet_fuel_rotation_angle,2,1.4,-2);
            gluSphere(quadric_object, 2.2, 7, 7);   
        glPopMatrix();
    }
    
    glDisable(GL_TEXTURE_2D);
}

void make_comet(int k){
    int empty_place,x1,x2;
    empty_place = rand() % 3;

    /* pozicija koja ostaje prazna */
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

    /* kometa se iscrtava na pozicijama x1 i x2 */
    comet_array[k].x1 = x1;
    comet_array[k].x2 = x2;

    /* izbor teksture */
    int first = rand() % 2 == 0 ? COMET_TEXTURE : COMET2_TEXTURE;
    int second = rand() % 2 == 0 ? COMET_TEXTURE : COMET2_TEXTURE;
    comet_array[k].first = first;
    comet_array[k].second = second;
}


void draw_fuel(){
    GLUquadricObj *quadric_object = gluNewQuadric();
    gluQuadricDrawStyle(quadric_object, GLU_FILL);
    gluQuadricTexture(quadric_object, GL_TRUE);
    
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textures[FUEL_TEXTURE]);
            glTranslatef(f.x_pos,3,f.z_pos);
            glRotatef(comet_fuel_rotation_angle,1,0,0);
            gluSphere(quadric_object,1,10,10);        
        glDisable(GL_TEXTURE_2D);    
    glPopMatrix();
}


void make_fuel(){
    /* place predstavlja jednu od tri pozicija na kojoj se kreira kugla goriva */
    int place = rand() %3; 
    switch(place){
        case 0: break;
        case 1: place = -6;
        case 2: place = 6;
    }
    f.x_pos = place;
    f.z_pos = -215;
    fuel_taken = 0;   
}

void draw_fuel_bar(){
    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-40,30,0.2);
        glVertex3f(-40,32,0);
        glVertex3f(40,32,0);
        glVertex3f(40,30,0.2);
    glEnd();

    
    float x_coord = fuel * 0.79;
    glBegin(GL_POLYGON);
        glColor3f(138.0/255,61.0/255,0);
        glVertex3f(-39.5,30.5,0.2);

        glColor3f(112.0/255,51.0/255,0);
        glVertex3f(-39.5,31.5,0);
        
        glColor3f(1,102.0/255,0);
        glVertex3f(-39.5 + x_coord ,31.5,0);
        
        glColor3f(163.0/255,102.0/255,0);
        glVertex3f(-39.5 + x_coord ,30.5,0.2);

    glEnd();
    glEnable(GL_LIGHTING);
}


void fuel_timer(int value){
    if(!game_ongoing)
        return;

    if(value != TIMER_FUEL_ID)
        return;
    
    fuel -= 0.1; /* smanjuje se kolicina goriva */

    glutTimerFunc(TIMER_FUEL_INTERVAL,fuel_timer,TIMER_FUEL_ID);
}
