#include "scene.h"

void draw_space(){
    /* Funkcija iscrtava poligone koji predstavljaju prostor oko igraca i prepreka.
        Zatim na njih dodaje teksturu sa zvezdama. */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[STARS_TEXTURE]);
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
    glBindTexture(GL_TEXTURE_2D, textures[STARS_TEXTURE]);
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);

        glTexCoord2f(0,0);
        glVertex3f(-100,-100,-30);

        glTexCoord2f(5,0);        
        glVertex3f(100,-100,-30);

        glTexCoord2f(5,5);
        glVertex3f(100,100,-30);

        glTexCoord2f(0,5);
        glVertex3f(-100,100,-30);
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
            
            glVertex3f(-a,-0.1,c);
            glVertex3f(a,-0.1,c);
            glVertex3f(a,-0.1,-c);            
            glVertex3f(-a,-0.1,-c);  
        glEnd();    
    glPopMatrix();
}
