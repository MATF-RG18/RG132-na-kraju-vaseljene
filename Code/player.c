#include "player.h"

/* Funkcija koja iscrtvama igraca */
void draw_spaceship(){

    GLfloat ambient_coeffs[] = { 0.1,0.1,0.1,1};
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };    

    /* dodaju se karakteristike materijala igraca */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,30);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glShadeModel(GL_SMOOTH);

    glRotatef(15,0,0,1);
    
    /* crtanje svemirskog broda */
    /* glava */
    glPushMatrix();
    GLfloat diffuse_coeffs_head[] = { 0.1,0.5,0.6,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs_head);
    glRotatef(90,0,0,1);
    float u,v;
    for(u=0;u<pi;u+=pi/50){
        glBegin(GL_TRIANGLE_STRIP);
        for(v=0;v<=pi+0.01; v+= pi/50){
            set_normal_and_vertex(u,v);
            set_normal_and_vertex(u+pi/50,v);
        }
        glEnd();
    }
    glPopMatrix();

    /* disk */
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glScalef(2.5,2.5,2.5);
        // TODO: glDrawElements kako se koristi
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0,0,1);
            int j;
            for (j = 0; j < 20; j++) {
                glColor3f(0.7+(float)j/10, 0.1,0.1);
                glVertex3f(sin(2 * j * pi / 20), 0, cos(2 * j * pi / 20));
            }
        glEnd();       
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    /* svetlost */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,names[LIGHT_TEXTURE]);
    glTranslatef(0,1,0);
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);

        glTexCoord2f(.5,1);
        glVertex3f(0,0,0);

        glTexCoord2f(0,0);
        glVertex3f(-2,-5,0);
        
        glTexCoord2f(1,0);
        glVertex3f(2,-5,0);    
    glEnd();
    glDisable(GL_TEXTURE_2D);
}   


/* animacija kretanja spaceshipa na levu stranu */
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

/* animacija kretanja spaceshipa ka desnoj strani */
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

//funkcija za iscrtavanje polulopte
void set_normal_and_vertex(float u, float v){
    glNormal3f(sin(u)*sin(v),
                cos(u),
                sin(u)*cos(v));
    glVertex3f(sin(u)*sin(v),
                cos(u),
                sin(u)*cos(v));
}
