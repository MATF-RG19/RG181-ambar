
static int window_width, window_height;
static float polje = 10;
static float velicina_ambara = 1.2;
static float animation_ongoing = 0;
static float rastojanje = 1.5;
static float velicina_drveta = 1;
static float visina_drveta=1.5;
const static float k_size = 0.5;
static float k_x, k_y, k_vx, k_vy;
const static float l_size = 0.5;
static float lgornji_x, lgornji_y, ldonji_x, ldonji_y, ldesni_x, ldesni_y,llevi_x, llevi_y;
const static float p_size = 0.3;
static float p_x, p_y, p_vx, p_vy;
static float drvo1_x, drvo1_y, drvo2_x, drvo2_y, drvo3_x, drvo3_y;
static float visina = 3;
static float sirina = -3;
static float parametar = 0;
static float parametar2 = 0;
static float ugao = 0;
static float velicina_ovce = 0.3;
GLfloat boja_stabla[] = {0.7, 0.7, 0.7};
//static void draw_axes(int n);

static void nacrtaj_valjak(float h, float r){
  GLUquadricObj * obj;
  obj = gluNewQuadric();
  gluCylinder(obj, r, r, h, 30, 30);
}

static void nacrtaj_konja(){
    glPushMatrix();
    glTranslatef(k_x, k_y, 0);
    glScalef(2.5, 1, 1);   
    //zadnja desna noga
    glTranslatef(-k_size/2, -k_size/2, 0);
    glutSolidCone(k_size/10, k_size/5, 30, 30);
    nacrtaj_valjak(k_size, k_size/15);
    glTranslatef(k_size/2, k_size/2, 0);
    //zadnja leva noga
    glTranslatef(-k_size/2, k_size/2, 0);
    glutSolidCone(k_size/10, k_size/5, 30, 30);
    nacrtaj_valjak(k_size, k_size/15);
    glTranslatef(k_size/2, -k_size/2, 0);
    //prednja leva noga
    glTranslatef(k_size/2, k_size/2, 0);
    glutSolidCone(k_size/10, k_size/5, 30, 30);
    nacrtaj_valjak(k_size, k_size/15);
    glTranslatef(-k_size/2,-k_size/2, 0);
    //prednja desna noga
    glTranslatef(k_size/2,-k_size/2, 0);
    glutSolidCone(k_size/10, k_size/5, 30, 30);
    nacrtaj_valjak(k_size, k_size/15);
    glTranslatef(-k_size/2, k_size/2, 0);    
    glTranslatef(0, 0, 1.5*k_size);
    //    glRotatef(ugao, k_x, k_y, 1);
    glutSolidSphere(k_size, 10, 10);
    //vrat
    glTranslatef(k_size*2/3, 0, k_size/2);
    glRotatef(30, 0, 1, 0);
    nacrtaj_valjak(k_size, k_size/5);
    glRotatef(-30, 0, 1, 0);
    glTranslatef(-k_size*2/3, 0, -k_size/2);
    //rep
     glTranslatef(-k_size*5/6, 0, 0);
    glRotatef(-160, 0, 1, 0);
    nacrtaj_valjak(k_size, k_size/10);
    glRotatef(160, 0, 1, 0);
    glTranslatef(k_size*5/6, 0, 0);
    
    //glava
    glTranslatef(k_size*6/5, 0, k_size);
    glScalef(1/2.5, 1, 2);
    glRotatef(45, 0, 1, 0);
    glutSolidSphere(k_size/2, 10, 10);
    glTranslatef(0, -k_size/2, k_size/3);
    glutSolidCone(k_size/5, k_size/5, 30, 30);
    glPopMatrix();

}


static void nacrtaj_drvo(float x, float y, float velicina, float visina){

  glPushMatrix();
  
  glBindTexture(GL_TEXTURE_2D, names[3]);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);
  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTranslatef(x, y, visina); 
  glutSolidSphere(velicina, 20, 20);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_TEXTURE_2D);
  glTranslatef(0, 0, -visina);
  //  glMaterialfv(GL_FRONT, GL_SPECULAR, boja_stabla);
  //  glColor3f(1, 1, 1);
  nacrtaj_valjak(visina/2, 0.2);
  glPopMatrix();  
}

static void nacrtaj_coveka(float x, float y){

  glPushMatrix();
  glTranslatef(x, y, l_size/2);
  //leva ruka
  glRotatef(60, 0, 1, 0);
  glTranslatef(-l_size/4, 0, l_size/3);
  nacrtaj_valjak(l_size/2, l_size/13);
  glTranslatef(l_size/4, 0, -l_size/3);
  glRotatef(-60, 0, 1, 0);
  //desna ruka
  glRotatef(-60, 0, 1, 0);
  glTranslatef(l_size/4, 0, l_size/3);
  nacrtaj_valjak(l_size/2, l_size/13);
  glTranslatef(-l_size/4, 0, -l_size/3);
  glRotatef(60, 0, 1, 0);
  
  //stomak
  glutSolidSphere(l_size/2, 10, 10);
  //glava
  glTranslatef(0, 0, l_size/2);
  nacrtaj_valjak(l_size/4, l_size/8);
  glTranslatef(0, 0, l_size/4);
  glutSolidSphere(l_size/4, 10, 10);
  //sesir
  glTranslatef(0, 0, l_size/6);
  glScalef(1, 1, 0.2);
  glutSolidSphere(l_size/2, 10, 10);
  glScalef(1, 1, 5);
  nacrtaj_valjak(l_size/4, l_size/5);
  glPopMatrix();

}

static void nacrtaj_ovcu(float k_x, float k_y, float k_size){

  glPushMatrix();
  
  glBindTexture(GL_TEXTURE_2D, names[4]);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);
  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      
    glTranslatef(k_x, k_y, 0);
    glScalef(2.5, 1, 1);   
    //zadnja desna noga
    glTranslatef(-k_size/2, -k_size/2, 0);
    glutSolidCone(k_size/10, k_size/5, 30, 30);
    nacrtaj_valjak(k_size, k_size/15);
    glTranslatef(k_size/2, k_size/2, 0);
    //zadnja leva noga
    glTranslatef(-k_size/2, k_size/2, 0);
    glutSolidCone(k_size/10, k_size/5, 30, 30);
    nacrtaj_valjak(k_size, k_size/15);
    glTranslatef(k_size/2, -k_size/2, 0);
    //prednja leva noga
    glTranslatef(k_size/2, k_size/2, 0);
    glutSolidCone(k_size/10, k_size/5, 30, 30);
    nacrtaj_valjak(k_size, k_size/15);
    glTranslatef(-k_size/2,-k_size/2, 0);
    //prednja desna noga
    glTranslatef(k_size/2,-k_size/2, 0);
    glutSolidCone(k_size/10, k_size/5, 30, 30);
    nacrtaj_valjak(k_size, k_size/15);
    glTranslatef(-k_size/2, k_size/2, 0);    
    glTranslatef(0, 0, 1.5*k_size);
    //    glRotatef(ugao, k_x, k_y, 1);
    glutSolidSphere(k_size, 10, 10);
    //vrat
    glTranslatef(k_size/2, 0, k_size/2);
    glRotatef(30, 0, 1, 0);
    nacrtaj_valjak(k_size, k_size/5);
    glRotatef(-30, 0, 1, 0);
    glTranslatef(-k_size/2, 0, -k_size/2);
    //rep
     glTranslatef(-k_size*5/6, 0, 0);
    glRotatef(-160, 0, 1, 0);
    nacrtaj_valjak(k_size, k_size/10);
    glRotatef(160, 0, 1, 0);
    glTranslatef(k_size*5/6, 0, 0);
    
    //glava
    glTranslatef(k_size, 0, k_size);
    glutSolidSphere(k_size/2, 10, 10);
  

  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_TEXTURE_2D);

  glPopMatrix();  

}

static void nacrtaj_psa(){

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, names[5]);
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

  
}


static void on_display(){
       
  GLfloat light_position[]={1, 1, 1, 0};
  GLfloat light_ambient[] = {0.0, 0.0, 0.0,1};
  GLfloat light_diffuse[]={0.7, 0, 0, 1};
  GLfloat light_specular[]={0.9, 0.9, 0.9, 1};

  GLfloat ambient_coeffs[] = {1.0, 0.1, 0.1, 1};
  GLfloat diffuse_coeffs[] = {0.8, 0.0, 0, 1};
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
  nacrtaj_coveka(lgornji_x, polje);


  //COVEK IZA
  nacrtaj_coveka(ldonji_x, -polje);

  //LEVI COVEK
  nacrtaj_coveka(-polje, llevi_y);

  //DESNI CUVAR
  nacrtaj_coveka(polje, ldesni_y);


  //crtam konja
  nacrtaj_konja();


  /* //crtam psa */
  nacrtaj_psa();
  


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
  glTranslatef(0, 0, velicina_ambara/2); 
  glutSolidCube(velicina_ambara); 
  glTranslatef(0, 0, velicina_ambara/2);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_TEXTURE_2D);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs); 
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs); 
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs); 
  glMaterialf(GL_FRONT, GL_SHININESS, shininess); 
  glutSolidCone(velicina_ambara, velicina_ambara/3, 10, 10);
  glEnable(GL_TEXTURE_2D); 
  glPopMatrix();


 
 
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
        glVertex3f(-velicina_ambara/2-0.1,- velicina_ambara/2-0.1,0);
	glTexCoord2f(8, 0);
        glVertex3f(-velicina_ambara/2-0.1,-velicina_ambara/2-0.1, velicina_ambara);
      	glTexCoord2f(8, 8);
        glVertex3f(velicina_ambara/2+0.1,- velicina_ambara/2-0.1, velicina_ambara);
        glTexCoord2f(0, 8);
        glVertex3f(velicina_ambara/2+0.1,-velicina_ambara/2-0.1,0);
   glEnd();
   glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
 	glTexCoord2f(0, 0);
        glVertex3f(velicina_ambara/2+0.1,- velicina_ambara/2-0.1,0);
	glTexCoord2f(8, 0);
        glVertex3f(velicina_ambara/2+0.1,-velicina_ambara/2-0.1, velicina_ambara);
      	glTexCoord2f(8, 8);
        glVertex3f(velicina_ambara/2+0.1, velicina_ambara/2+0.1, velicina_ambara);
        glTexCoord2f(0, 8);
        glVertex3f(velicina_ambara/2+0.1,velicina_ambara/2+0.1,0);
   glEnd();
      glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
 	glTexCoord2f(0, 0);
        glVertex3f(-velicina_ambara/2-0.1,- velicina_ambara/2-0.1,0);
	glTexCoord2f(8, 0);
        glVertex3f(-velicina_ambara/2-0.1,-velicina_ambara/2-0.1, velicina_ambara);
      	glTexCoord2f(8, 8);
        glVertex3f(-velicina_ambara/2-0.1, velicina_ambara/2+0.1, velicina_ambara);
        glTexCoord2f(0, 8);
        glVertex3f(-velicina_ambara/2-0.1,velicina_ambara/2+0.1,0);
   glEnd();

   nacrtaj_drvo(drvo1_x, drvo1_y, velicina_drveta, visina_drveta);
   nacrtaj_drvo(drvo2_x, drvo2_y, velicina_drveta, visina_drveta);
   nacrtaj_drvo(drvo3_x, drvo3_y, velicina_drveta, visina_drveta);

   nacrtaj_ovcu(-polje/2, polje/2, velicina_ovce);
   
   //  draw_axes(polje + 5);
     //saljemo novu sliku na ekran  
  glutSwapBuffers();
}
