
static int window_width, window_height;
static float polje = 10;
static float velicina_ambara = 1.2;
static float animation_ongoing = 0;
static float rastojanje = 1.5;
const static float k_size = 1;
static float k_x, k_y, k_vx, k_vy;
const static float l_size = 0.5;
static float lgornji_x, lgornji_y, ldonji_x, ldonji_y, ldesni_x, ldesni_y,llevi_x, llevi_y;
const static float p_size = 0.3;
static float p_x, p_y, p_vx, p_vy;
static float drvo1_x, drvo1_y;
static float visina = 3;
static float sirina = -3;
static float parametar = 0;
static float parametar2 = 0;
static float ugao = 0;
static void draw_axes(int n);

static void on_display(){

   GLfloat light_position[]={1, 1, 1, 0};
  GLfloat light_ambient[] = {0.0, 0.0, 0.0,1};
  GLfloat light_diffuse[]={0.7, 0.7, 0.7, 1};
  GLfloat light_specular[]={0.9, 0.9, 0.9, 1};

  GLfloat ambient_coeffs[] = {1.0, 0.1, 0.1, 1};
  GLfloat diffuse_coeffs[] = {0.0, 0.0, 0.8, 1};
  GLfloat specular_coeffs[] = {1, 1, 1, 1};
  GLfloat shininess = 20;

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(k_x, k_y-2+sirina,visina-1, //oko
	    k_x+parametar, k_y+1, visina-1, //objekat 
	     0, 0, 1 );

  //crtam coveka ispred
  glPushMatrix();
  glTranslatef(lgornji_x, polje, l_size/2);
  //stomak
  glutSolidSphere(l_size/2, 10, 10);
  glTranslatef(0, 0, l_size/2);
  //glava
  glutSolidSphere(l_size/4, 10, 10);
  glTranslatef(0, 0, l_size/6);
  //sesir
  glutSolidCone(l_size/2,l_size/4, 10, 10);
  glPopMatrix();

  //COVEK IZA
  glPushMatrix();
  glTranslatef(ldonji_x, -polje,l_size/2);
  //stomak
  glutSolidSphere(l_size/2, 10, 10);
  glTranslatef(0, 0, l_size/2);
  //glava
  glutSolidSphere(l_size/4, 10, 10);
  glTranslatef(0, 0, l_size/6);
  // glScalef(0, 0, 0.5);
  //sesir
  glutSolidCone(l_size/2,l_size/4, 10, 10);
  glPopMatrix();

  // glColor3f(0,1, 0);

  //LEVI COVEK
  glPushMatrix();
  glTranslatef(-polje, llevi_y, l_size/2);
  //stomak
  glutSolidSphere(l_size/2, 10, 10);
  glTranslatef(0, 0, l_size/2);
  //glava
  glutSolidSphere(l_size/4, 10, 10);
  glTranslatef(0, 0, l_size/6);
  // glScalef(0, 0, 0.5);
  //sesir
  glutSolidCone(l_size/2,l_size/4, 10, 10);
  glPopMatrix();

  //DESNI CUVAR
  glPushMatrix();
  
  glTranslatef(polje, ldesni_y, l_size/2);
  //stomak
  glutSolidSphere(l_size/2, 10, 10);
  glTranslatef(0, 0, l_size/2);
  //glava
  glutSolidSphere(l_size/4, 10, 10);
  glTranslatef(0, 0, l_size/6);
  // glScalef(0, 0, 0.5);
  //sesir
  glutSolidCone(l_size/2,l_size/4, 10, 10);
  glPopMatrix();

  //crtam konja
  glPushMatrix();
  glTranslatef(k_x, k_y, k_size/2);
   glRotatef(ugao, k_x, k_y, 1);
   glutSolidSphere(k_size/2, 10, 10);
   glTranslatef(k_size/2, k_size/4, 0);
   glutSolidSphere(k_size/4, 10, 10);
  glPopMatrix();


  /* //crtam psa */
  /* glPushMatrix(); */
  /* glTranslatef(p_x, p_y, p_size/2); */
  /* glutSolidSphere(p_size/2, 10, 10); */
  /* glPopMatrix(); */

  glPushMatrix();
  glColor3f(1, 1, 1);
  //  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, names[2]);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);
  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTranslatef(p_x, p_y, p_size/2); 
  glutSolidSphere(p_size/2, 10, 10); 
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  // glDisable(GL_TEXTURE_2D); 
  glPopMatrix();

  //CRTAM AMBAR
  glPushMatrix();
  glDisable(GL_TEXTURE_2D);
  glTranslatef(0, 0, velicina_ambara/2);
  glutSolidCube(velicina_ambara);
  glTranslatef(0, 0, velicina_ambara/2);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  glutSolidCone(velicina_ambara, velicina_ambara/3, 10, 10);
  glEnable(GL_TEXTURE_2D);
  glPopMatrix();


  //Drvo
  /* glutWireCube(velicina_ambara); */
  /* glPushMatrix(); */
  /*  glColor3f( 0, 1, 0); */
  /*  glTranslatef(drvo1_x, drvo1_y, 0); */
  /*  glutSolidSphere(0.025, 20, 20); */
  /* glPopMatrix(); */
 
  /*tekstura za travu*/
 glBindTexture(GL_TEXTURE_2D, names[1]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
 	glTexCoord2f(10, 10);
        glVertex3f(polje, polje, 0);
        glTexCoord2f(0, 10);
        glVertex3f(-polje, polje, 0);
 	glTexCoord2f(0, 0);
        glVertex3f(-polje, -polje, 0);
 	glTexCoord2f(10, 0);
        glVertex3f(polje, -polje, 0);
    glEnd();

  /*tekstura za ambar*/
 glBindTexture(GL_TEXTURE_2D, names[2]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

 	glTexCoord2f(0, 0);
        glVertex3f(-velicina_ambara/2,- velicina_ambara/2-0.1,0);
	glTexCoord2f(8, 0);
        glVertex3f(-velicina_ambara/2,-velicina_ambara/2-0.1, velicina_ambara);
      	glTexCoord2f(8, 8);
        glVertex3f(velicina_ambara/2,- velicina_ambara/2-0.1, velicina_ambara);
        glTexCoord2f(0, 8);
        glVertex3f(velicina_ambara/2,-velicina_ambara/2-0.1,0);

    glEnd();


    draw_axes(polje + 5);
     //saljemo novu sliku na ekran  
  glutSwapBuffers();
}
