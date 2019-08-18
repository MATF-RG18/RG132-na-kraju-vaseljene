#include "draw.h"

/* igrac */
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
        glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
       
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

    GLfloat diffuse_coeffs_light[] = {0.7,.7,.7,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs_light);
        
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

void draw_space(){

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[STARS_TEXTURE]);
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);

        glTexCoord2f(0,0);
        glVertex3f(-100,0,-100);

        glTexCoord2f(5,0);        
        glVertex3f(100,0,-100);

        glTexCoord2f(5,5);
        glVertex3f(100,0,100);
  
        glTexCoord2f(0,5);
        glVertex3f(-100,0,100);
    glEnd();    
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[STARS_TEXTURE]);
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);

        glTexCoord2f(0,0);
        glVertex3f(-100,-100,0);

        glTexCoord2f(5,0);        
        glVertex3f(100,-100,0);

        glTexCoord2f(5,5);
        glVertex3f(100,100,0);

        glTexCoord2f(0,5);
        glVertex3f(-100,100,0);
    glEnd();    
    glDisable(GL_TEXTURE_2D);
}

/* iscrtavanje puta po kom se igrac krece levo desno i na kom izbijaju prepreke */
void draw_path(float a, float b, float c){

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

void draw_comets(){
    comet_line c;
    int j;
    GLUquadricObj *quadricObj = gluNewQuadric();
    gluQuadricDrawStyle(quadricObj, GLU_FILL);
    gluQuadricTexture(quadricObj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[COMET_TEXTURE]);
    for(j=0;j<8;j++){
        c = comet_array[j];

        glPushMatrix();
            glTranslatef(c.x1,3,c.z_pos);  
            glRotatef(-110,1,0,0);
            gluSphere(quadricObj, 2, 20, 20);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(c.x2,3,c.z_pos); 
            glRotatef(-110,1,0,0);
            gluSphere(quadricObj, 2, 20, 20);       
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);

   /* GLUquadricObj *quadricObj = gluNewQuadric();
    gluQuadricDrawStyle(quadricObj, GLU_FILL);
    gluSphere(quadricObj, 1, 20, 20);
    gluQuadricTexture(quadricObj, GL_TRUE);*/
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
