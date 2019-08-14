#include <GL/glut.h>
#include <stdio.h>

static void draw_path(float a, float b, float c); /* funkcija za iscrtavanje putanje */
static void draw_rocket(); /* funkcija za iscrtavanje leteceg objekta */
static void draw_debug_coosys();
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Na kraju vaseljene");
    glutFullScreen();

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
//  GLfloat light_position[] = {0,20,80,1};
    GLfloat light_position[] = {0,0,0,1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
      exit(0);
      break;
  }   
}


static void on_reshape(int width, int height){
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 200);
}


static void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  
    int depth = 50;
    int width = 20;
    int height = 10;
    gluLookAt(0,10,65,
            0,0,0,
            0,1,0);  

    glEnable(GL_LIGHT0);

    GLfloat light_ambient[] = { 0,0,0,1 };
    GLfloat light_diffuse[] =  { 0.7,0.7,0.7,1};
    GLfloat light_specular[] =  {.9,.9,.9,1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    draw_debug_coosys();

    draw_path(width/2,height,depth);
    
    glPushMatrix();
        glTranslatef(0,1,depth-1); 
        draw_rocket();
    glPopMatrix();

    glutSwapBuffers();
}

static void draw_path(float a, float b, float c){
    
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0.2, 0.5, 0.2, 1 };
    GLfloat specular_coeffs[] = {0.2,0.2,0.2,1};    
    
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

static void draw_rocket(){

    GLfloat ambient_coeffs[] = { 0.1,0.1,0.1,1};
    GLfloat diffuse_coeffs[] = { 0.1,0.5,0.6,1};
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };    

    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular_coeffs);
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,30);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
        glShadeModel(GL_SMOOTH);

        glutSolidSphere(1,20,20);
    glPopMatrix();
}

static void draw_debug_coosys(){
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
