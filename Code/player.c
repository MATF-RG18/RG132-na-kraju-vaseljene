#include "player.h"

/* Funkcija koja iscrtvama igraca */
void draw_spaceship(){

    /* obezbedjuje konstantnu rotaciju broda oko svoje ose*/
    rotation_angle += 2;

    GLfloat ambient_coeffs[] = { 0.1,0.1,0.1,1};
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };    

    /* dodaju se karakteristike materijala igraca */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,30);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glShadeModel(GL_SMOOTH);
    
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


    GLUquadricObj *quadric_object = gluNewQuadric();
    gluQuadricDrawStyle(quadric_object, GLU_FILL);
    gluQuadricTexture(quadric_object, GL_TRUE);

    /* disk */
    glPushMatrix();
        glRotatef(90,1,0,0);
        GLfloat diffuse_disc[] = {1,0.2,0.3,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse_disc);
        gluDisk(quadric_object,0,2.7,30,30);
    glPopMatrix();


    /* svetlost */
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glColor4f(1,1,1,0.5);
    glRotatef(90,1,0,0);
    gluCylinder(quadric_object,0.5,2.2,4,20,20);
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
}   


/* animacija kretanja spaceshipa na levu stranu */
void left_move(int value){
    if(value != TIMER_PLAYER_ID)
        return;

    if(player_x - 0.5 >= x_goal){
        player_x -= 0.5;
        animation_parametar += 0.07;
        animation_ongoing_l = 1;
        glutPostRedisplay();
        glutTimerFunc(TIMER_PLAYER_INTERVAL,left_move,TIMER_PLAYER_ID);
    }
    else animation_ongoing_l = 0;
}

/* animacija kretanja spaceshipa ka desnoj strani */
void right_move(int value){
    if(value != TIMER_PLAYER_ID)
        return;

    if(player_x + 0.5 <= x_goal){
        player_x += 0.5;
        animation_parametar -= 0.07;
        animation_ongoing_r = 1;
        glutPostRedisplay();
        glutTimerFunc(TIMER_PLAYER_INTERVAL,right_move,TIMER_PLAYER_ID);
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
