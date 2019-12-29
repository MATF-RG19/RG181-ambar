#include<stdio.h>
#include<GL/glut.h>

static void on_display();

int main(int argc, char ** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(1200, 700);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Ambar");
  glutDisplayFunc(on_display);

  glutMainLoop();
  return 0;

}

static void on_display(){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
}
