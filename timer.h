#define TIMER_ID 0
#define TIMER_INTERVAL 20

static float dalekoOdKonja(float x, float y){
  return sqrt( (k_x-x)*(k_x-x) + (k_y-y)*(k_y-y) );
}

static void on_timer(int id){
  //proveravam da li je pravi tajmer
  if(id!=TIMER_ID)
    return;
  //pomeram psa u smeru u kom ide dok ne dodje do ivice, a onda mu menjamo smer
  p_x +=p_vx;
  if(p_x<=-(polje-p_size/2) || p_x>=polje-p_size/2)
    p_vx*=-1;
  p_y +=p_vy;
  if(p_y<=-(polje-p_size/2) || p_y>=polje-p_size/2)
    p_vy*=-1;
  //pomeram konja u smeru u kom ide
  k_x += k_vx;
  k_y += k_vy;
  //ako je rastojanje konja od pasa sa strane ili onog u sredini manje od zadatog
  //menjam smer kretanja
  if(dalekoOdKonja(llevi_x, llevi_y) <rastojanje
     || dalekoOdKonja(ldesni_x, ldesni_y) <rastojanje)
           k_vx = k_vx * -1;

  if(dalekoOdKonja(lgornji_x, lgornji_y) <rastojanje
     || dalekoOdKonja(ldonji_x, ldonji_y) <rastojanje)  
           k_vy = k_vy * -1;

  if(dalekoOdKonja(p_x, p_y) <rastojanje){
           k_vx *= -1;
           k_vy *= -1;
      }
    //ako je konj usao u ambar, smiruje se
  if(dalekoOdKonja(0, 0)<velicina_ambara/2){
           k_x = 0;
           k_y = 0;
      }    
    //reiscrtavam
  glutPostRedisplay();

     //prekidam igricu kad konj pobegne
   if(abs(k_x)>polje+3*rastojanje || abs(k_y)>polje+3*rastojanje)
       exit(EXIT_SUCCESS);
     
     //pozivam sledeci tajmer
   if(animation_ongoing){
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
  }
}
