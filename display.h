
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
static void draw_axes(int n);

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
