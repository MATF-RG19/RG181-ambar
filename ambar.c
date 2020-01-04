#include<stdio.h>
#include<GL/glut.h>
#include<time.h>
#include<stdlib.h>


#define TIMER_ID 0
#define TIMER_INTERVAL 20

static float animation_ongoing = 0;
static float rastojanje = 0.001;
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

  srand(time(NULL));
  k_x = -(1-k_size/2) + (2-k_size)*rand()/(float) RAND_MAX;
  k_y = -(1-k_size/2) + (2-k_size)*rand()/(float) RAND_MAX;

  k_vx = -k_size/2 + k_size*rand()/(float)RAND_MAX;
  k_vy = -k_size/2 + k_size*rand()/(float)RAND_MAX;
  
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

  glColor3f(0, 0, 1);
  glBegin(GL_POLYGON);
   glColor3f(0, 0, 1);
  glVertex3f(k_x+k_size/2, k_y+k_size/2, 0);
  glVertex3f(k_x+k_size/2, k_y-k_size/2, 0);
  glVertex3f(k_x-k_size/2, k_y-k_size/2, 0);
  glVertex3f(k_x-k_size/2, k_y+k_size/2, 0);
  glEnd();
  
  
  glutSwapBuffers();
}


static void on_keyboard(unsigned char key, int x, int y){
  switch(key){
  case 27:
    exit(0);
    break;
  case 'r':
    animation_ongoing = 0;
    srand(time(NULL));
    k_x = -(1-k_size/2) + (2-k_size)*rand()/(float) RAND_MAX;
    k_y = -(1-k_size/2) + (2-k_size)*rand()/(float) RAND_MAX;

    k_vx = -k_size/2 + k_size*rand()/(float)RAND_MAX;
    k_vy = -k_size/2 + k_size*rand()/(float)RAND_MAX;

    glutPostRedisplay();
    break;
  case 'g':
  case 'G':
    if(!animation_ongoing){
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
    break;
  case 's':
  case 'S':
    animation_ongoing = 0;
    break;
  case '4':
    if(lgornji_x > -1){
      lgornji_x-=l_size;
      ldonji_x-=l_size;
      glutPostRedisplay();
    }
    break;
  case '6':
    if(lgornji_x <1){
      lgornji_x+=l_size;
      ldonji_x+=l_size;
      glutPostRedisplay();
    }
    break;
  case '8':
    if(llevi_y<1){
      llevi_y+=l_size;
      ldesni_y+=l_size;
      glutPostRedisplay();
    }
    break;
  case '2':
    if(llevi_y>-1){
      llevi_y-=l_size;
      ldesni_y-=l_size;
      glutPostRedisplay();
    }
    break;
  }
  
}

static void on_timer(int id){
  if(id!=TIMER_ID)
    return;
  k_x += k_vx;
 
  k_y += k_vy;

  if((abs(k_x-llevi_x)<rastojanje && abs(k_y - llevi_y)<rastojanje)||(abs(k_x-ldesni_x)<rastojanje && abs(k_y - ldesni_y)<rastojanje))
    k_vx = k_vx * -1;

  if((abs(k_x-lgornji_x)<rastojanje && abs(k_y - lgornji_y)<rastojanje)||(abs(k_x-ldonji_x)<rastojanje && abs(k_y - ldonji_y)<rastojanje))
    k_vy = k_vy * -1;

  glutPostRedisplay();
  
  if(animation_ongoing){
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
  }
  
}
