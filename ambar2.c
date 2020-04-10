#include<stdio.h>
#include<GL/glut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include"image.h" //pozajmljen kod zaglavlja sa vezbi
#include "initialize.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 20


static int window_width, window_height;

static float velicina_ambara = 0.3;
static float animation_ongoing = 0;
static float rastojanje = 0.4;
const static float k_size = 0.2;
static float k_x, k_y, k_vx, k_vy;
const static float l_size = 0.15;
static float lgornji_x, lgornji_y, ldonji_x, ldonji_y, ldesni_x, ldesni_y,llevi_x, llevi_y;
const static float p_size = 0.1;
static float p_x, p_y, p_vx, p_vy;
static float drvo1_x, drvo1_y;
static void on_display();
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
static void on_reshape(int width, int height);
static void draw_axes(int duzina);

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
  lgornji_y=ldesni_x =1;
  ldonji_y = llevi_x = -1;
  lgornji_x = ldonji_x = -0;
  llevi_y = ldesni_y = -0;

  /* konj se postavlja na slucajnu poziciju na pocetku, ali u centralni deo ekrana*/
  srand(time(NULL));
  k_x = -(0.5-k_size/2) + (1-k_size)*rand()/(float) RAND_MAX;
  k_y = -(0.5-k_size/2) + (1-k_size)*rand()/(float) RAND_MAX;
  /*pocetna brzina konja*/
  k_vx =  k_size*0.01;
  k_vy =  k_size*0.01;

  /*pocetni polozaj psa na slucajnom mestu*/
  srand(time(NULL));
  p_x = -(1-p_size/2) + (2-p_size)*rand()/(float) RAND_MAX;
  p_y = -(1-p_size/2) + (2-p_size)*rand()/(float) RAND_MAX;

  /*brzina psa*/
  p_vx = -p_size/2 + p_size*rand()/(float)RAND_MAX;
  p_vy = -p_size/2 + p_size*rand()/(float)RAND_MAX;

  drvo1_x = -(0.5-k_size/2) + (1-k_size)*rand()/(float) RAND_MAX;
  drvo1_y = -(0.5-k_size/2) + (1-k_size)*rand()/(float) RAND_MAX;
  
  glClearColor(0.75, 0.4, 0.2, 0);
  glEnable(GL_DEPTH_TEST);
  /*uglavnom mi sluzi za teksture */
  //   initialize();
  
  glutMainLoop();
  return 0;
}

static void draw_axes(int duzina){

  glDisable(GL_LIGHTING);
  
  glLineWidth(5);
  glBegin(GL_LINES);
  glColor3f(1, 0, 0);
  glVertex3f(0, 0, 0.2);
  glVertex3f(duzina, 0, 0);

  glColor3f(0, 1, 0);
  glVertex3f(0, 0, 0.2);
  glVertex3f(0, duzina, 0);

  glColor3f(0, 0, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, duzina);
  glEnd();

  glEnable(GL_LIGHTING);
}

static void on_reshape(int width, int height){
  
   window_width = width;
   window_height= height;
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60, (float)width/(float)height, 1, 5);
}

static void on_display(){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 1,  //0, -1, 1 vidim donju liniju i plavu liniiju
	     k_x, k_y, 0,
	     0, 1, 0 );
  
  
  glVertex3f(1, 0, 0);
  glPushMatrix();
  glTranslatef(lgornji_x, 1, 0);
  glutWireSphere(l_size/2, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(ldonji_x, -1, 0);
  glutWireSphere(l_size/2, 10, 10);
  glPopMatrix();

  glColor3f(0,1, 0);

  glPushMatrix();
  glTranslatef(-1, llevi_y, 0);
  glutWireSphere(l_size/2, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1, ldesni_y, 0);
  glutWireSphere(l_size/2, 10, 10);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(k_x, k_y, 0);
  glutWireSphere(k_size/2, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(p_x, p_y, 0);
  glutWireSphere(p_size/2, 10, 10);
  glPopMatrix();
  
  //Drvo
  /* glutWireCube(velicina_ambara); */
  /* glPushMatrix(); */
  /*  glColor3f( 0, 1, 0); */
  /*  glTranslatef(drvo1_x, drvo1_y, 0); */
  /*  glutSolidSphere(0.025, 20, 20); */
  /* glPopMatrix(); */
 
  /*tekstura za travu*/
 /* glBindTexture(GL_TEXTURE_2D, names[1]); */
 /*    glBegin(GL_QUADS); */
 /*        glNormal3f(0, 0, 1); */
 /* 	glTexCoord2f(1, 1); */
 /*        glVertex3f(1, 1, 0); */
 /*        glTexCoord2f(0, 1); */
 /*        glVertex3f(-1, 1, 0); */
 /* 	glTexCoord2f(0, 0); */
 /*        glVertex3f(-1, -1, 0); */
 /* 	glTexCoord2f(1, 0); */
 /*        glVertex3f(1, -1, 0); */
 /*    glEnd(); */

    draw_axes(25);
     //saljemo novu sliku na ekran  
  glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int x, int y){
  switch(key){
    //oslobanjamo memoriju i prekidamo program
  case 27:
    glDeleteTextures(10, names);
    exit(0);
    break;
  case 'r':
    //restartujemo igru i sve parametre postavljamo na pocetne
    animation_ongoing = 0;
    srand(time(NULL));
    k_x = -(0.5-k_size/2) + (1-k_size)*rand()/(float) RAND_MAX;
    k_y = -(0.5-k_size/2) + (1-k_size)*rand()/(float) RAND_MAX;

    k_vx = k_size*0.01;
    k_vy = k_size*0.01;

    srand(time(NULL));
    p_x = -(1-p_size/2) + (2-p_size)*rand()/(float) RAND_MAX;
    p_y = -(1-p_size/2) + (2-p_size)*rand()/(float) RAND_MAX;

    p_vx = -p_size/2 + p_size*rand()/(float)RAND_MAX;
    p_vy = -p_size/2 + p_size*rand()/(float)RAND_MAX;
    glutPostRedisplay();
    break;
  case 'g':
  case 'G':
    //pokrecemo animaciju
    if(!animation_ongoing){
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
    break;

    //zaustavljamo animaciju
  case 's':
  case 'S':
    animation_ongoing = 0;
    break;
    //uvecavamo brzinu dva puta
  case 'f':
  case 'F':
    k_vx*=2;
    k_vy*=2;
    break;
    //usporavamo duplo
  case 'd':
  case 'D':
    k_vx/=2;
    k_vy/=2;
    break;
    //pomeramo levo gornjeg i donjeg cuvara ako imamo gde
  case '4':
    if(lgornji_x > -1){
      lgornji_x-=l_size;
      ldonji_x-=l_size;
      glutPostRedisplay();
    }
    break;
    //pomeramo desno gornjeg i donjeg cuvara ako ima mesta desno
  case '6':
    if(lgornji_x <1){
      lgornji_x+=l_size;
      ldonji_x+=l_size;
      glutPostRedisplay();
    }
    break;
    //levi i desni cuvar idu gore ako vec nisu na vrhu
  case '8':
    if(llevi_y<1){
      llevi_y+=l_size;
      ldesni_y+=l_size;
      glutPostRedisplay();
    }
    break;
    //levi i desni cuvar idu dole ako nisu na dnu
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
  //proveravamo da li je pravi tajmer
  if(id!=TIMER_ID)
    return;
  //pomeramo psa u smeru u kom ide dok ne dodje do ivice, a onda mu menjamo smer
  p_x +=p_vx;
  if(p_x<=-(1-p_size/2) || p_x>=1-p_size/2)
    p_vx*=-1;
  p_y +=p_vy;
  if(p_y<=-(1-p_size/2) || p_y>=1-p_size/2)
    p_vy*=-1;
  //pomeramo konja u smeru u kom ide
  k_x += k_vx;
  k_y += k_vy;
  //ako je rastojanje konja od pasa sa strane ili onog u sredini manje od zadatog
  //menjamo smer kretanja
  if(sqrt((k_x - llevi_x)*(k_x-llevi_x)+(k_y-llevi_y)*(k_y-llevi_y)) <rastojanje
     || sqrt((k_x - ldesni_x)*(k_x-ldesni_x)+(k_y-ldesni_y)*(k_y-ldesni_y)) <rastojanje)
           k_vx = k_vx * -1;

    if(sqrt((k_x - lgornji_x)*(k_x-lgornji_x)+(k_y-lgornji_y)*(k_y-lgornji_y)) <rastojanje
      || sqrt((k_x - ldonji_x)*(k_x-ldonji_x)+(k_y-ldonji_y)*(k_y-ldonji_y)) <rastojanje)
           k_vy = k_vy * -1;

    if(sqrt((k_x - p_x)*(k_x-p_x)+(k_y-p_y)*(k_y-p_y)) <rastojanje){
           k_vx *= -1;
           k_vy *= -1;
      }
    //ako je konj usao u ambar, smiruje se
    if(sqrt((k_x)*(k_x)+(k_y)*(k_y)) <velicina_ambara/2){
           k_x = 0;
           k_y = 0;
      }    
    //reiscrtavamo  
     glutPostRedisplay();

     //pozivamo sledeci tajmer
     if(animation_ongoing){
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
  }
}
