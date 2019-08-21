#include "fuel.h"

void draw_fuel(){
    GLUquadricObj *quadric_object = gluNewQuadric();
    gluQuadricDrawStyle(quadric_object, GLU_FILL);
    gluQuadricTexture(quadric_object, GL_TRUE);
    
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textures[FUEL_TEXTURE]);
            glTranslatef(f.x_pos,3,f.z_pos);
            gluSphere(quadric_object,1,10,10);        
        glDisable(GL_TEXTURE_2D);    
    glPopMatrix();
}

void make_fuel(){
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

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,textures[FUEL_TEXTURE]);
    
    float x_coord = fuel * 0.79;
    glBegin(GL_POLYGON);
        glNormal3f(0,0,-1);

      //  glTexCoord2d(0,0);
        glColor3f(210.0/255,102.0/255,0);
        glVertex3f(-39.5,30.5,0.2);

      // glTexCoord2d(1,0);  
        glColor3f(153.0/255,92.0/255,0);
        glVertex3f(-39.5,31.5,0);
        
      // glTexCoord2d(1,1);
        glColor3f(179.0/255,81.0/255,0);
        glVertex3f(-39.5 + x_coord ,31.5,0);
        
      //  glTexCoord2d(0,1);
        glColor3f(200.0/255,71.0/255,0);
        glVertex3f(-39.5 + x_coord ,30.5,0.2);

    //glDisable(GL_TEXTURE_2D);
    glEnd();

    glEnable(GL_LIGHTING);

}


void fuel_timer(int value){
    if(game_over)
        return;

    if(value != TIMER_FUEL_ID)
        return;
    
    fuel -= 0.5;

    glutTimerFunc(TIMER_FUEL_INTERVAL,fuel_timer,TIMER_FUEL_ID);
}