#include<stdio.h>
#include<GL/glut.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 20

const static float k_size = 0.05;
static float k_x, k_y, k_vx, k_vy;
const static float l_size = 0.1;
static float lgornji_x, lgornji_y, ldonji_x, ldonji_y, ldesni_x, ldesni_y,llevi_x, llevi_y;


static void on_display();
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
int main(int argc, char ** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(1250, 550);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Ambar");

  glutDisplayFunc(on_display);
  glutKeyboardFunc(on_keyboard);

  lgornji_y=ldesni_x =1;
  ldonji_y = llevi_x = -1;
  lgornji_x = ldonji_x = -0;
  llevi_y = ldesni_y = -0;
  glClearColor(0.75, 0.4, 0.2, 0);
  glEnable(GL_DEPTH_TEST);
  
  glutMainLoop();
  return 0;

}

static void on_display(){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  glVertex3f(1, 0, 0);
  glBegin(GL_POLYGON);
  glVertex3f(lgornji_x + l_size/2, lgornji_y + l_size/2, 0);
  glVertex3f(lgornji_x + l_size/2, lgornji_y - l_size/2, 0);
  glVertex3f(lgornji_x - l_size/2, lgornji_y - l_size/2, 0);
  glVertex3f(lgornji_x - l_size/2, lgornji_y + l_size/2, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(ldonji_x + l_size/2, ldonji_y + l_size/2, 0);
  glVertex3f(ldonji_x + l_size/2, ldonji_y - l_size/2, 0);
  glVertex3f(ldonji_x - l_size/2, ldonji_y - l_size/2, 0);
  glVertex3f(ldonji_x - l_size/2, ldonji_y + l_size/2, 0);
  glEnd();

  glColor3f(0,1, 0);
  
  glBegin(GL_POLYGON);
  glVertex3f(llevi_x + l_size/2, llevi_y + l_size/2, 0);
  glVertex3f(llevi_x + l_size/2, llevi_y - l_size/2, 0);
  glVertex3f(llevi_x - l_size/2, llevi_y - l_size/2, 0);
  glVertex3f(llevi_x - l_size/2, llevi_y + l_size/2, 0);
  glEnd();


  glBegin(GL_POLYGON);
  glVertex3f(ldesni_x + l_size/2, ldesni_y + l_size/2, 0);
  glVertex3f(ldesni_x + l_size/2, ldesni_y - l_size/2, 0);
  glVertex3f(ldesni_x - l_size/2, ldesni_y - l_size/2, 0);
  glVertex3f(ldesni_x - l_size/2, ldesni_y + l_size/2, 0);
  glEnd();
  
  glutSwapBuffers();
}


static void on_keyboard(unsigned char key, int x, int y){
  switch(key){
  case 27:
    exit(0);
    break;
  case '4':
    lgornji_x-=l_size;
    ldonji_x-=l_size;
    glutPostRedisplay();
    break;
  case '6':
    lgornji_x+=l_size;
    ldonji_x+=l_size;
    glutPostRedisplay();
    break;
  case '8':
    llevi_y+=l_size;
    ldesni_y+=l_size;
    glutPostRedisplay();
    break;
  case '2':
    llevi_y-=l_size;
    ldesni_y-=l_size;
    glutPostRedisplay();
    break;
  }
  
}

static void on_timer(int id){

}
