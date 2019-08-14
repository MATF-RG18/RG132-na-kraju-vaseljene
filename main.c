#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

void draw_path(float a, float b, float c); /* funkcija za iscrtavanje putanje */
void draw_rocket(); /* funkcija za iscrtavanje leteceg objekta */
void set_normal_and_vertex(float u, float v);
static void draw_debug_coosys(); /* pomocna funkcija za iscrtavanje koordinata  */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

/* on_timer callback funkcije */
static void right_move(int value);
static void left_move(int value);

static int animation_ongoing_r,animation_ongoing_l;
static float rocket_x, rocket_y, x_goal;

const static float pi = 3.141592653589793;

#define TIMER_ID 1
#define TIMER_INTERVAL 30

int main(int argc, char **argv){

    /* Inicijalizacija gluta */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       
    //glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Na kraju vaseljene");
    glutFullScreen();

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    /* Omogucavanje svetla i njegovo pozicioniranje */
    glEnable(GL_LIGHTING);
    GLfloat light_position[] = {0,0,0,1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    rocket_x = x_goal = 0;
    rocket_y = 1;
    animation_ongoing_l = animation_ongoing_r = 0;

    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27:
      exit(0);
      break; 
    case 97: /* pokrece se kretanje igraca u levo */
        if(!animation_ongoing_r && !animation_ongoing_l){
            x_goal = rocket_x - 6;
            if(x_goal >= -6){
                animation_ongoing_l = 1;
                glutTimerFunc(TIMER_INTERVAL,left_move,TIMER_ID);
            }
            else x_goal = rocket_x;
        }
        break;
    case 100: /* pokrece se kretanje igraca u desno */
        if(!animation_ongoing_r && !animation_ongoing_l){
            x_goal = rocket_x + 6;
            if(x_goal <= 6){ 
                animation_ongoing_r = 1;
                glutTimerFunc(TIMER_INTERVAL,right_move,TIMER_ID);
            }
            else x_goal = rocket_x;
        }
        break;
    }
}

static void left_move(int value){
    if(value != TIMER_ID)
        return;

    if(rocket_x - 0.5 > x_goal){
        rocket_x -= 0.5;
        animation_ongoing_l = 1;
        glutPostRedisplay();
        glutTimerFunc(TIMER_INTERVAL,left_move,TIMER_ID);
    }
    else animation_ongoing_l = 0;
}

static void right_move(int value){
    if(value != TIMER_ID)
        return;

    if(rocket_x + 0.5 < x_goal){
        rocket_x += 0.5;
        animation_ongoing_r = 1;
        glutPostRedisplay();
        glutTimerFunc(TIMER_INTERVAL,right_move,TIMER_ID);
    }
    else animation_ongoing_r = 0;
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
    /* podesavanje vidne tacke */
    gluLookAt(0,10,65,
            0,0,0,
            0,1,0);  

    /* Podesavanje komponenti svetla */
    glEnable(GL_LIGHT0);

    GLfloat light_ambient[] = { 0,0,0,1 };
    GLfloat light_diffuse[] =  { 0.7,0.7,0.7,1};
    GLfloat light_specular[] =  {.9,.9,.9,1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Iscrtavanje objekata: put i igrac */
    draw_debug_coosys();
    draw_path(width/2,height,depth);
    glPushMatrix();
        glTranslatef(rocket_x,rocket_y,depth-2); 
        draw_rocket();
    glPopMatrix();    

    glutSwapBuffers();
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


void draw_rocket(){
    /* igrac, opsti oblik */

    GLfloat ambient_coeffs[] = { 0.1,0.1,0.1,1};
    GLfloat diffuse_coeffs[] = { 0.1,0.5,0.6,1};
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };    

    /* dodaju se karakteristike materijala igraca */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,30);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glShadeModel(GL_SMOOTH);

    glRotatef(15,0,0,1);
    /* crtanje svemirskog broda */
    glPushMatrix();
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

    glPushMatrix();
        glScalef(2.5,2.5,2.5);
        //glRotatef(90,1,0,0);
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0,1,0);
            int i;
            for (i = 0; i < 20; i++) {
                glVertex3f(
                        sin(2 * i * pi / 20) ,
                        0,
                        cos(2 * i * pi / 20));
            }
        glEnd();
    glPopMatrix();

    /* TODO: dodati svetlost iz broda */

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
