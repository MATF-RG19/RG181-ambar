#include<math.h>
#define TIMER_ID 0
#define TIMER_INTERVAL 20

static float dalekoOdKonja(float x, float y){
  return sqrt( (k_x-x)*(k_x-x) + (k_y-y)*(k_y-y) );
}

static void beziOdKonja(float * o_x, float* o_y){
  if(dalekoOdKonja(*o_x, *o_y)<2*rastojanje){
    if(*o_x > k_x)//ako je ovca desno od konja
      if(*o_x + 2*rastojanje<polje)
         *o_x +=rastojanje*2;
      else
	*o_x-=rastojanje*2;
    else
      if(*o_x-2*rastojanje > -polje)
        *o_x-=rastojanje*2;
      else
	*o_x+=rastojanje*2;
  }
}

   static void beziOdDrveta(float d_x, float d_y){
   if(dalekoOdKonja(d_x,d_y)<rastojanje/4){
     if(d_x<k_x)
       k_x+=rastojanje/2;
     else
       k_x-=rastojanje/2;
   }
   }
static void on_timer(int id){
  //proveravam da li je pravi tajmer
  if(id!=TIMER_ID)
    return;
  //pomeram psa u smeru u kom ide dok ne dodje do ivice, a onda mu menjamo smer
  p_x +=p_vx;
  
  if(p_x<=-(polje-p_size/2) || p_x>=polje-p_size/2){
    p_vx*=-1;

  }
  p_y +=p_vy;
  if(p_y<=-(polje-p_size/2) || p_y>=polje-p_size/2){
    p_vy*=-1;

  }
  //pomeram konja u smeru u kom ide
  k_x += k_vx;
  k_y += k_vy;

  
  //ako je rastojanje konja od ljudi sa strane ili psa u sredini manje od zadatog
  //menjam smer kretanja
  if((dalekoOdKonja(llevi_x, llevi_y) <rastojanje) && (k_x>llevi_x))
    {  k_vx = k_vx * -1;
      k_x = k_x + rastojanje/2;
           ugao=0;
          rotiraj = 0;
      
    }
  if( (dalekoOdKonja(ldesni_x, ldesni_y) <rastojanje) && (k_x<ldesni_x)) 
    {  k_vx = k_vx * -1;
           ugao=180;
          rotiraj = 1;
          k_x = k_x - rastojanje/2;
    }
 
  if((dalekoOdKonja(lgornji_x, lgornji_y) <rastojanje) && (k_y > lgornji_y))
    {   k_vy = k_vy * -1;
            ugao=-90;
            rotiraj= 1;
            k_y-=rastojanje/2;
    }
  
  if(( dalekoOdKonja(ldonji_x, ldonji_y) <rastojanje)&& (k_y < ldonji_y))
    {   k_vy = k_vy * -1;
            ugao=90;
            rotiraj= 1;
	    k_y +=rastojanje/2;
    }


  if(dalekoOdKonja(p_x, p_y) <rastojanje){
           k_vx *= -1;
           k_vy *= -1;
	   rotiraj = 1;
           if(abs(k_vx)>abs(k_vy))
	     {
	        
	        ugao=180;
	     }
	   else{
	     ugao = 90;
	        }
      }
    //ako je konj usao u ambar, smiruje se
  if(dalekoOdKonja(0, 0)<velicina_ambara/2){
           k_x = 0;
           k_y = 0;
      }    

  //ovce beze od konja
  beziOdKonja(&o1_x, &o1_y);
  beziOdKonja(&o2_x, &o2_y);
  beziOdKonja(&o3_x, &o3_y);
  beziOdKonja(&o4_x, &o4_y);
  beziOdKonja(&o5_x, &o5_y);
   //parametar za pomeranje nogu konja
   if(i)
     {
       ugao_nogu+=4;
       if(ugao_nogu>30)
	 i=0;
     }
   else{
     ugao_nogu-=4;
     if(ugao_nogu<-30)
       i=1;
   }



   beziOdDrveta(drvo1_x, drvo1_y);
   beziOdDrveta(drvo2_x, drvo2_y);
   beziOdDrveta(drvo3_x, drvo3_y);
   
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
