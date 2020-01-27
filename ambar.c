#include<stdio.h>
#include<GL/glut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include"image.h" //pozajmljen kod zaglavlja sa vezbi

#define FILENAME3 "pas.bmp"
#define FILENAME2 "ambar.bmp"
#define FILENAME1 "grass.bmp"
#define FILENAME4 "horse.bmp"
#define FILENAME5 "pas2.bmp"
#define TIMER_ID 0
#define TIMER_INTERVAL 20

/*identifikatori tekstura*/
static GLuint names[10];

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
static void initialize(void);
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
  initialize();
  
  glutMainLoop();
  return 0;

}

static void on_reshape(int width, int height){

  window_width = width;
  window_height= height;

  //  glViewport(0, 0, width, height);
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  // gluPerspective(60, (float)width/height, 1, 15);
}
/*POCETAK POZAJMLJENOG KODA SA VEZBI*/
static void initialize(void)
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;


    /* Ukljucuje se testiranje z-koordinate piksela. */
    //    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

 

    /* Generisu se identifikatori tekstura. */
    glGenTextures(10, names);

    
    /* Kreira se trava */
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);


    /*kreira se ambar*/
    image_read(image, FILENAME2);
    
    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
               GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /*kreira se pas*/
    image_read(image, FILENAME3);
    glBindTexture(GL_TEXTURE_2D, names[3]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
               GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /*kreira se konj*/

        image_read(image, FILENAME4);
    glBindTexture(GL_TEXTURE_2D, names[4]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
		 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
      
      /*kreira se covek*/
          image_read(image, FILENAME5);
    glBindTexture(GL_TEXTURE_2D, names[5]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
		 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
      
      
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);

 
}

/*KRAJ POZAJMLJENOG KODA*/


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


  glBegin(GL_POLYGON);
  glColor3f(1, 0, 1);
  glVertex3f(p_x+p_size/2, p_y+p_size/2, 0);
  glVertex3f(p_x+p_size/2, p_y-p_size/2, 0);
  glVertex3f(p_x-p_size/2, p_y-p_size/2, 0);
  glVertex3f(p_x-p_size/2, p_y+p_size/2, 0);
  glEnd();
 

  glutWireCube(velicina_ambara);
  glPushMatrix();
   glColor3f( 0, 1, 0);
   glTranslatef(drvo1_x, drvo1_y, 0);
   glutSolidSphere(0.025, 20, 20);
  glPopMatrix();



   
  
  /*tekstura za travu*/
 glBindTexture(GL_TEXTURE_2D, names[1]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
        glVertex3f(1, 1, 0);
        glTexCoord2f(0, 1);
        glVertex3f(-1, 1, 0);
	glTexCoord2f(0, 0);	
        glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 0);
        glVertex3f(1, -1, 0);
    glEnd();
    /*tekstura za ambar */
 glBindTexture(GL_TEXTURE_2D, names[2]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

	glTexCoord2f(1, 1);
        glVertex3f(velicina_ambara/2, velicina_ambara/2,- 0.1);
	 glTexCoord2f(0, 1);
        glVertex3f(-velicina_ambara/2, velicina_ambara/2,- 0.1);
         glTexCoord2f(0, 0);	
	 glVertex3f(-velicina_ambara/2, -velicina_ambara/2,- 0.1);
	 glTexCoord2f(1, 0);
        glVertex3f(velicina_ambara/2, -velicina_ambara/2,- 0.1);
    glEnd();

    /*tekstura za psa */
 glBindTexture(GL_TEXTURE_2D, names[3]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
       glVertex3f(p_x+p_size/2, p_y+p_size/2, -0.09);
	 glTexCoord2f(0, 1);
       glVertex3f(p_x-p_size/2, p_y+p_size/2, -0.09); 
         glTexCoord2f(0, 0);	
	   glVertex3f(p_x-p_size/2, p_y-p_size/2, -0.09);
	 glTexCoord2f(1, 0);
        glVertex3f(p_x+p_size/2, p_y-p_size/2, -0.09);
    glEnd();

        /*tekstura za konja */
 glBindTexture(GL_TEXTURE_2D, names[4]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
       glVertex3f(k_x+k_size/2, k_y+k_size/2, -0.09);
	 glTexCoord2f(0, 1);
       glVertex3f(k_x-k_size/2, k_y+k_size/2, -0.09); 
         glTexCoord2f(0, 0);	
	   glVertex3f(k_x-k_size/2, k_y-k_size/2, -0.09);
	 glTexCoord2f(1, 0);
        glVertex3f(k_x+k_size/2, k_y-k_size/2, -0.09);
    glEnd();


    
        /*tekstura za gornjeg cuvara */
 glBindTexture(GL_TEXTURE_2D, names[5]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(lgornji_x+l_size/2, lgornji_y, -0.09);
	 glTexCoord2f(0, 1);
	 glVertex3f(lgornji_x-l_size/2, lgornji_y, -0.09); 
         glTexCoord2f(0, 0);	
	 glVertex3f(lgornji_x-l_size/2, lgornji_y-l_size, -0.09);
	 glTexCoord2f(1, 0);
        glVertex3f(lgornji_x+l_size/2, lgornji_y-l_size, -0.09);
    glEnd();

            /*tekstura za donjeg cuvara */
 glBindTexture(GL_TEXTURE_2D, names[5]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(ldonji_x+l_size/2, ldonji_y+l_size, -0.09);
	 glTexCoord2f(0, 1);
	 glVertex3f(ldonji_x-l_size/2, ldonji_y+l_size, -0.09); 
         glTexCoord2f(0, 0);	
	 glVertex3f(ldonji_x-l_size/2, ldonji_y, -0.09);
	 glTexCoord2f(1, 0);
        glVertex3f(ldonji_x+l_size/2, ldonji_y, -0.09);
    glEnd();

    /*tekstura za levog cuvara*/
    
     glBindTexture(GL_TEXTURE_2D, names[5]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(llevi_x+l_size, llevi_y+l_size/2, -0.09);
	 glTexCoord2f(0, 1);
	 glVertex3f(llevi_x, llevi_y+l_size/2, -0.09); 
         glTexCoord2f(0, 0);	
	 glVertex3f(llevi_x, llevi_y-l_size/2, -0.09);
	 glTexCoord2f(1, 0);
        glVertex3f(llevi_x+l_size, llevi_y-l_size/2, -0.09);
    glEnd();

       /*tekstura za desnog cuvara*/
    
     glBindTexture(GL_TEXTURE_2D, names[5]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(ldesni_x, ldesni_y+l_size/2, -0.09);
	 glTexCoord2f(0, 1);
	 glVertex3f(ldesni_x-l_size, ldesni_y+l_size/2, -0.09); 
         glTexCoord2f(0, 0);	
	 glVertex3f(ldesni_x-l_size, ldesni_y-l_size/2, -0.09);
	 glTexCoord2f(1, 0);
        glVertex3f(ldesni_x, ldesni_y-l_size/2, -0.09);
    glEnd();
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

  
  glutSwapBuffers();
}


static void on_keyboard(unsigned char key, int x, int y){
  switch(key){
  case 27:
    glDeleteTextures(10, names);
    exit(0);
    break;
  case 'r':
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
    if(!animation_ongoing){
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
    break;
  case 's':
  case 'S':
    animation_ongoing = 0;
    break;
  case 'f':
  case 'F':
    k_vx*=2;
    k_vy*=2;
    break;
  case 'd':
  case 'D':
    k_vx/=2;
    k_vy/=2;
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

  p_x +=p_vx;
  if(p_x<=-(1-p_size/2) || p_x>=1-p_size/2)
    p_vx*=-1;
  p_y +=p_vy;
  if(p_y<=-(1-p_size/2) || p_y>=1-p_size/2)
    p_vy*=-1;

  k_x += k_vx;
  k_y += k_vy;
  
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

    
    if(sqrt((k_x)*(k_x)+(k_y)*(k_y)) <velicina_ambara/2){
      k_x = 0;
      k_y = 0;
    }    
    
  glutPostRedisplay();
  
  if(animation_ongoing){
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
  }
  
}
