#define TIMER_ID 0
#define TIMER_INTERVAL 20

static void on_timer(int id);

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
    k_x = -(polje/2-k_size/2) + (polje-k_size)*rand()/(float) RAND_MAX;
    k_y = -(polje/2-k_size/2) + (polje-k_size)*rand()/(float) RAND_MAX;

    k_vx = k_size*0.01;
    k_vy = k_size*0.01;

    srand(time(NULL));
    p_x = -(polje-p_size/2) + (2*polje-p_size)*rand()/(float) RAND_MAX;
    p_y = -(polje-p_size/2) + (2*polje-p_size)*rand()/(float) RAND_MAX;

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
    if(lgornji_x > -polje){
      lgornji_x-=l_size;
      ldonji_x-=l_size;
      glutPostRedisplay();
    }
    break;
    //pomeramo desno gornjeg i donjeg cuvara ako ima mesta desno
  case '6':
    if(lgornji_x <polje){
      lgornji_x+=l_size;
      ldonji_x+=l_size;
      glutPostRedisplay();
    }
    break;
    //levi i desni cuvar idu gore ako vec nisu na vrhu
  case '8':
    if(llevi_y<polje){
      llevi_y+=l_size;
      ldesni_y+=l_size;
      glutPostRedisplay();
    }
    break;
    //levi i desni cuvar idu dole ako nisu na dnu
  case '2':
    if(llevi_y>-polje){
      llevi_y-=l_size;
      ldesni_y-=l_size;
      glutPostRedisplay();
    }
    break;
  case '7':
    visina+=0.1;
    glutPostRedisplay();
    break;
  case '1':
    visina-=0.1;
    glutPostRedisplay();
    break;
  case '0':
    sirina-=0.1;
    glutPostRedisplay();
    break;
  case '.':
    sirina+=0.1;
    glutPostRedisplay();
    break;
  case '/':
    parametar-=0.1;
    parametar2 = visina-1;
    glutPostRedisplay();
    break;
  case '*':
    parametar+=0.1;
    parametar2 = visina-1;
    glutPostRedisplay();
    break;
  }
}
