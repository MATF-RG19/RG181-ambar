#define TIMER_ID 0
#define TIMER_INTERVAL 20

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
