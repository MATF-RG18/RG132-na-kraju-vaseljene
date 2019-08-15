#include "draw.h"

void draw_spaceship(){
    /* igrac, opsti oblik */

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
        glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
        /* GLfloat diffuse_coeffs_disc[] = { 0.9,0.1,0.1,1};*/
        /* glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs_disc);*/
        
        glScalef(2.5,2.5,2.5);
        //glRotatef(90,1,0,0);

        // TODO: glDrawElements kako se koristi
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0,0,1);
            int i;
            for (i = 0; i < 20; i++) {
                /* GLfloat diffuse_coeffs_disc[] = { 0.7+(float)i/10,0.1,0.1,1};*/
                /* glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs_disc);*/
                glColor3f(0.7+(float)i/10, 0.1,0.1);
                glVertex3f(
                        sin(2 * i * pi / 20) ,
                        0,
                        cos(2 * i * pi / 20));
            }
        glEnd();
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();


    /* svetlo */
    glPushMatrix();
        GLfloat diffuse_coeffs_light[] = {0.7,.7,.7,1};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs_light);
    
        /* glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0.7,0.7,0.7,0.7);
        */

        glTranslatef(0,-2,0);
        glRotatef(-90,1,0,0);
        glutSolidCone(1.5,3,20,20);

    glPopMatrix();
   
    /* 
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(-0.8,0,0);
        glVertex3f(0.8,0,0);
        glVertex3f(1.5,-2,0);
        glVertex3f(-1.5,-2,0);
    glEnd();
    */
}   

void draw_path(float a, float b, float c){
    /* iscrtavanje puta po kom se igrac krece levo desno i na kom izbijaju prepreke */

    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0.2, 0.5, 0.2, 1 };
    GLfloat specular_coeffs[] = {0.2,0.2,0.2,1};    
    
    /* karakteristike materijala putanje se dodaju */
    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular_coeffs);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
        glShadeModel(GL_SMOOTH);
    
    //glColor3f((float)32/255,(float)29/255,(float)100/255);
        glBegin(GL_POLYGON);
            glNormal3f(0,1,0);
            glVertex3f(-a,0,c);   
            glVertex3f(a,0,c);   
            glVertex3f(a,0,-c);   
            glVertex3f(-a,0,-c);  
        glEnd();    
    glPopMatrix();
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


void draw_debug_coosys(){
    glBegin(GL_LINES);
    glColor3f (1, 0, 0);
    glVertex3f(20, 0, 0);
    glVertex3f(0, 0, 0);

    glColor3f (0, 1, 0);
    glVertex3f(0, 20, 0);
    glVertex3f(0, 0, 0);

    glColor3f (0, 0, 1);
    glVertex3f(0, 0, 20);
    glVertex3f(0, 0, 0);
    glEnd();
}
