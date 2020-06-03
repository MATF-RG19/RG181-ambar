#include<stdio.h>
#include<GL/glut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include"image.h" //pozajmljen kod zaglavlja sa vezbi
#include "initialize.h"
#include "display.h"
#include "keyboard.h"
#include "timer.h"
//static void on_keyboard(unsigned char key, int x, int y);

static void on_reshape(int width, int height);

int main(int argc, char ** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(1250, 550);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Ambar");
  
  glutDisplayFunc(on_display);
  glutKeyboardFunc(on_keyboard);
  glutReshapeFunc(on_reshape);
  
  /*pocetne vrednosti polozaja lenjira (ljudi) */
  lgornji_y=ldesni_x =polje;
  ldonji_y = llevi_x = -polje;
  lgornji_x = ldonji_x = -0;
  llevi_y = ldesni_y = -0;

  /* konj se postavlja na slucajnu poziciju na pocetku, ali u centralni deo ekrana*/
  srand(time(NULL));
  k_x = -(polje/2-k_size/2) + (polje-k_size)*rand()/(float) RAND_MAX;
  k_y = -(polje/2-k_size/2) + (polje-k_size)*rand()/(float) RAND_MAX;
  /*pocetna brzina konja*/
  k_vx =  k_size*0.16;
  k_vy =  k_size*0.16;

  /*pocetni polozaj psa na slucajnom mestu*/
  srand(time(NULL));
  p_x = -(polje-p_size/2) + (2*polje-p_size)*rand()/(float) RAND_MAX;
  p_y = -(polje-p_size/2) + (2*polje-p_size)*rand()/(float) RAND_MAX;

  /*brzina psa*/
  // p_vx = -p_size/2 + p_size*rand()/(float)RAND_MAX;
  // p_vy = -p_size/2 + p_size*rand()/(float)RAND_MAX;

  p_vx = 4*k_vx;
  p_vy = 4*k_vy;

  drvo1_x = polje*0.75;
  drvo1_y = polje *0.75;

  drvo3_x = -polje*0.40;
  drvo3_y = polje*0.2;

  drvo2_x = polje*0.3;
  drvo2_y = -polje*0.3;  

  o1_x = -polje/2;
  o1_y = polje/2;
  o2_x = -polje/2;
  o2_y = polje/4;
  o3_x = polje/2;
  o3_y = polje/4;
  o4_x = polje/2;
  o4_y = polje/2;
  o5_x = -polje/4;
  o5_y = polje/2;

  
  glClearColor(0, 0.4, 0, 0);
  glEnable(GL_DEPTH_TEST);
  /*uglavnom mi sluzi za teksture */

  initialize();
  
  glutMainLoop();
  return 0;
}

/* static void draw_axes(int duzina){ */

/*   glDisable(GL_LIGHTING); */
  
/*   glLineWidth(5); */
/*   glBegin(GL_LINES); */
/*   glColor3f(1, 0, 0); */
/*   glVertex3f(0, 0, 0.2); */
/*   glVertex3f(duzina, 0, 0); */

/*   glColor3f(0, 1, 0); */
/*   glVertex3f(0, 0, 0.2); */
/*   glVertex3f(0, duzina, 0); */

/*   glColor3f(0, 0, 1); */
/*   glVertex3f(0, 0, 0); */
/*   glVertex3f(0, 0, duzina); */
/*   glEnd(); */

/*   glEnable(GL_LIGHTING); */
/* } */

static void on_reshape(int width, int height){
  
   window_width = width;
   window_height= height;
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60, (float)width/(float)height, 1, 20);
}





