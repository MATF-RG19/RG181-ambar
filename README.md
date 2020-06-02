# RG181-ambar
Ambar
prevodjenje:

gcc main.c image.c  -lglut -lGLU -lGL -lm   ILI komandom make
folder se cisti od suvisnih fajlova sa make clean

pokretanje ./a.out

Konj krece pritiskom na 'g', moze da se ubrza ili uspori pritiskom na 'f' ili 'd', na 's' se pauzira, na 'r' restartuje.
Cilj je zaustaviti ga da ne ode van vidnog polja cuvarima sa 4 strane koji se krecu pritiscima na 2, 4, 6, 8 za levo, desno, gore, dole
sve dok ne udje u ambar. Po polju trci i pas koji ga plasi, dok ovce beze od njega. 

0 - udaljava kameru
. - priblizava kameru
7- podize kameru 
1- spusta kameru

image.c i image.h sam pozajmila kod sa vezbi. U initialize.h sam ga iskoristila, uglavnom mi sluzi za teksture taj fajl.
