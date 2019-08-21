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