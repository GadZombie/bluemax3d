void wstaw_lotnisko(int a, int b, bool ustawsamolot, bool wrogie=false)
{
	//miejsce i wyprasowanie go dla lotniska
   int w,b1,a1;
	//a=15;
	//b=30;
	w=teren[b][a].y+1.5;
   if (w<1) w=1;
	for (b1=-6; b1<=3; b1++)
		for (a1=0; a1<=30; a1++)
			if ((a+a1>=0) && (a+a1<=maxdlug-1) && (b+b1>=0) && (b+b1<=maxszer-1))
         {
				teren[b+b1][a+a1].y=w;
				teren[b+b1][a+a1].obiekt=0;
				teren[b+b1][a+a1].kr=0.4+random(5)/100.0;
				teren[b+b1][a+a1].kg=0.4+random(5)/100.0;
				teren[b+b1][a+a1].kb=0.3+random(5)/100.0;
         }

   for (a1=0; a1<=28; a1+=2)
       if ((a+a1>=0) && (a+a1<=maxdlug-1) && (b>=0) && (b<=maxszer-1))
       {
          teren[b][a+a1].obiekt=ob_lotnisko + (int)wrogie;
          teren[b][a+a1].obiektobr=0;
          teren[b][a+a1].obiektrozm=1;
          teren[b][a+a1].obiekty=teren[b][a].y+0.05;
       }

   if (!wrogie) {
       for (a1=a-40; a1<=a+40; a1++)
         for (b1=0; b1<=maxszer; b1++)
           if ((a1>=0) && (a1<=maxdlug-1) &&
               (teren[b1][a1].obiekt==ob_barki ||
                teren[b1][a1].obiekt==ob_czolgi ||
                teren[b1][a1].obiekt==ob_dziala ||
                (teren[b1][a1].obiekt>=ob_budynki && teren[b1][a1].obiekt<=ob_budynki+4)
               )
              )
           {
    /*         if (teren[b1][a1].obiekt==ob_budynki) {
                for (int b2=-2; b2<=2; b2++)
                   for (int a2=-1; a2<=1; a2++)
                      if ((a1+a2>=0) && (a1+a2<=maxdlug-1) && (b1+b2>=0) && (b1+b2<=maxszer-1))
                         teren[b1+b2][a1+a2].jasnosc=0.7;
             }*/
             teren[b1][a1].obiekt=0;
           }
   }

   //hangar
   for (a1=4; a1<=10; a1+=2) {
       int n[][2] = { 2,0,
                      0,0,
                      1,1,
                      0,0,
                      1,1,
                      0,0,
                      0,2 };
       b1=-4;
       teren[b+b1][a+a1].obiekt=ob_hangar+n[a1-4][0];
       teren[b+b1][a+a1].obiektobr=-90;
       teren[b+b1][a+a1].obiektrozm=1.0;
       teren[b+b1][a+a1].obiekty=teren[b+b1][a+a1].y+0.05;
       b1=-5;
       teren[b+b1][a+a1].obiekt=ob_hangar+n[a1-4][1];
       teren[b+b1][a+a1].obiektobr=90;
       teren[b+b1][a+a1].obiektrozm=1.0;
       teren[b+b1][a+a1].obiekty=teren[b+b1][a+a1].y+0.05;
   }

   //lampy:
   a1=1;
   for (b1=-6; b1<=-4; b1+=1) {
       teren[b+b1][a+a1].obiekt=ob_lampy;
       teren[b+b1][a+a1].obiekty=teren[b+b1][a+a1].y;
       teren[b+b1][a+a1].obiektrozm=2.0;
       teren[b+b1][a+a1].obiektobr=b1*10;
   }

   a1-=3;
   //stad swiatlo:
   teren[b-2][a+a1].obiekt=ob_hangar+3;
   teren[b-2][a+a1].obiekty=teren[b-2][a+a1].y+0.05;

   for (a1=3; a1<=11; a1++) {
       for (b1=-6; b1<=-3; b1++) {
           teren[b+b1][a+a1].jasnosc=0.1;
       }
   }

   if (!wrogie) {
       if (ustawsamolot)
       {
         samolot[sterowanie].y=w;
         samolot[sterowanie].x=b*dkrok-dx0;
         samolot[sterowanie].z=5;
       }
   }
}

int rzekaod,rzekado,rzekaszer;

void zmienkolor(int x1, int y1, int x2, int y2)
{
  teren[x1][y1].kr= teren[x2][y2].kr - 0.025 + random(100)/2000.0;
  if (teren[x1][y1].kr<0.3) teren[x1][y1].kr=0.3;
//  if (teren[x1][y1].kr>teren[x1][y1].kg+0.2) teren[x1][y1].kr=teren[x1][y1].kg+0.2;
  if (teren[x1][y1].kr>1.0) teren[x1][y1].kr=1.0;
  teren[x1][y1].kg= teren[x2][y2].kg - 0.025 + random(100)/2000.0;
  if (teren[x1][y1].kg<0.5) teren[x1][y1].kg=0.5;
  if (teren[x1][y1].kg>1.0) teren[x1][y1].kg=1.0;
  teren[x1][y1].kb= teren[x2][y2].kb - 0.025 + random(100)/2000.0;
  if (teren[x1][y1].kb<0.2) teren[x1][y1].kb=0.2;
  if (teren[x1][y1].kb>0.5) teren[x1][y1].kb=0.5;
}

void zmienkolor2(int x1, int y1, int x2, int y2, int x3, int y3)
{
  teren[x1][y1].kr= (teren[x2][y2].kr+teren[x3][y3].kr)/2.0 - 0.025 + random(100)/2000.0;
  if (teren[x1][y1].kr<0.3) teren[x1][y1].kr=0.3;
//  if (teren[x1][y1].kr>teren[x1][y1].kg+0.2) teren[x1][y1].kr=teren[x1][y1].kg+0.2;
  if (teren[x1][y1].kr>1.0) teren[x1][y1].kr=1.0;
  teren[x1][y1].kg= (teren[x2][y2].kg+teren[x3][y3].kg)/2.0 - 0.025 + random(100)/2000.0;
  if (teren[x1][y1].kg<0.3) teren[x1][y1].kg=0.3;
  if (teren[x1][y1].kg>0.9) teren[x1][y1].kg=0.9;
  teren[x1][y1].kb= (teren[x2][y2].kb+teren[x3][y3].kb)/2.0 - 0.025 + random(100)/2000.0;
  if (teren[x1][y1].kb<0.2) teren[x1][y1].kb=0.2;
  if (teren[x1][y1].kb>0.5) teren[x1][y1].kb=0.5;
}

void stworz_teren(bool calynowy=true)
{
	int a,b, a1,b1, w;
   int wsiood;
	GLfloat vek1[3],vek2[3],vek3[3];
   int lotniskobedzie=maxdlug-150; //w ktorej "dlugosci" bedzie lotnisko; pierwsze lotnisko jest w 30
   int lotniskobedziex=maxszer/2 + 13*(random(2)*2-1); //w ktorej "szerokosci" bedzie lotnisko; pierwsze lotnisko jest w 30

   gracz.etap++;

   if (calynowy) {
       //brzegi rzeki:
       rzekaod=(4*maxszer)/16.0;
       rzekado=(6*maxszer)/16.0;
       rzekaszer=rzekado-rzekaod; //6.25

       wsiood=1;
   } else
   //jesli to kontynuacja terenu, przesun cala koncowke terenu na poczatek
   {
	   for (b=0; b<=maxszer-1; b++)
		    for (a=0; a<ilewidac_suma; a++) {
              teren[b][a]=teren[b][maxdlug-ilewidac_suma+a];
          }

      wsiood=ilewidac_suma;
   }


   //wyczyszczenie terenu z obiektow i wyrownanie jasnosci:
	for (b=0; b<=maxszer-1; b++)
		for (a=wsiood; a<=maxdlug-1; a++) {
         teren[b][a].jasnosc=0.7;
         teren[b][a].wstawruchome=0;
         teren[b][a].obiekt=0;
         teren[b][a].obiektcel=false;
         teren[b][a].obiektzniszcz=0;
         teren[b][a].kr=0;
         teren[b][a].kg=0;
         teren[b][a].kb=0;
      }

   //brzegi terenu: ustalenie wysokosci
   if (calynowy) {
	   teren[0][0].y=rand()%50/20.0;
	   teren[0][0].kr=0.6;
	   teren[0][0].kg=0.7;
	   teren[0][0].kb=0.3;
	   for (b=1; b<=maxszer-1; b++) {
		    teren[b][0].y= teren[b-1][0].y - 0.3 + rand()%20/30.0;
          zmienkolor(b,0, b-1,0);
      }
   }
	for (b=wsiood; b<=maxdlug-1; b++) {
		teren[0][b].y= teren[0][b-1].y - 0.3 + rand()%20/30.0;
      zmienkolor(0,b, 0,b-1);
   }

   //generowanie losowej wysokosci terenu:
	for (b=1; b<=maxszer-1; b++)
		for (a=wsiood; a<=maxdlug-1; a++) {
	      //teren[b][a].y= (teren[b-1][a].y+teren[b][a-1].y - 0.25 + rand()%20/40.0)/2.0 - 0.25 + rand()%20/40.0;
			teren[b][a].y= (teren[b-1][a].y+teren[b][a-1].y - 0.5 + rand()%40/40.0)/2.0 - 0.25 + rand()%20/40.0;
			if (teren[b][a].y<0.5) teren[b][a].y=0.5;
			if (teren[b][a].y>5.0) teren[b][a].y=5.0;
          teren[b][a].kr=0.5;
          teren[b][a].kg=0.7;
          teren[b][a].kb=0.2;
//         zmienkolor2(b,a, b-1,a, b,a-1);
		}

   //kolory terenu:
   {
    float kr,kg,kb;
    int roz;
    for (a=wsiood; a<=maxdlug-1; a+=random(10))
        for (b=1+random(10); b<=maxszer-1; b+=random(30))
        {
            kg=random(90)/100.0;
            kr=0.2+random(50)/100.0;
            if (kr>kg+0.2) kr=kg+0.2;
            kb=    random(25)/100.0;
            if (kr>0.5 && kg>0.5 && random(2)==0) kb=0.3+random(40)/100.0;
            if (kb>kr) kb=kr;

            roz=2+random(40);
            for (int ox=-roz; ox<=roz; ox++)
                for (int oy=-roz; oy<=roz; oy++)
                {
                    if (b+ox>=0 && b+ox<=maxszer-1 &&
                        a+oy>=wsiood && a+oy<=maxdlug-1)
                    {
                        float d=ox*ox+oy*oy;
                        float d2;

                        if (d!=0) d=sqrt(ox*ox+oy*oy);
                        else d=0;

                        if (d<roz) {
                           d2 = (roz-d)/roz;
                           if (d2==0) d2=0.0001;
                           teren[b+ox][a+oy].kr=(teren[b+ox][a+oy].kr*(1-d2)+kr*d2);
                           teren[b+ox][a+oy].kg=(teren[b+ox][a+oy].kg*(1-d2)+kg*d2);
                           teren[b+ox][a+oy].kb=(teren[b+ox][a+oy].kb*(1-d2)+kb*d2);
                        }
                    }
                }

        }

   }


   //po ktorej stronie bedzie miasto w stosunku do rzeki?
   int stronamiasta=random(2)*2-1;
   int miastood=80;
   int miastodo=lotniskobedzie-130;

   //ustalenie koryta rzeki:
   int szer2=maxszer/2;
	for (a=wsiood; a<=maxdlug-1; a++) {
      //kolory dna
		for (b=1; b<=maxszer-1; b++) {
			if ((b>=rzekaod) && (b<=rzekado))
			{
				teren[b][a].y-=2;
            if (teren[b][a].y>-1.5) teren[b][a].y=-1.5-random(150)/100.0;
				teren[b][a].jasnosc-=fabs(teren[b][a].y/7.0);
				if (teren[b][a].jasnosc<0) teren[b][a].jasnosc=0;
				teren[b][a].kr=random(30)/100.0;
				teren[b][a].kg=random(20)/100.0;
				teren[b][a].kb=random(20)/100.0;
			}
		}

      //kolory krawedzi
      for (b=0; b<=1; b++) {
          if (rzekaod>=1+b && rzekaod-b<maxszer-1 && teren[rzekaod-1][a].y>=2.0)
          {
             float j=0.4+random(30)/100.0;
             teren[rzekaod-b][a].kr=j;
             teren[rzekaod-b][a].kg=j;
             teren[rzekaod-b][a].kb=j;
          }
          if (rzekado<=maxszer-2-b && rzekado+b>=1 && teren[rzekado+1][a].y>=2.0)
          {
             float j=0.4+random(30)/100.0;
             teren[rzekado+b][a].kr=j;
             teren[rzekado+b][a].kg=j;
             teren[rzekado+b][a].kb=j;
          }
      }

      //losowe przesuniecie
		if (random(2)==0) rzekaod=rzekaod-1+random(3);

      if (calynowy && a>=0 && a<=65) { //przesuniecie rzeki w lewo przy pierwszym lotnisku
          if (rzekado>szer2) {
             rzekado--;
             rzekaod--;
          }
      } else //przesuniecie rzeki na bok przy kazdym kolejnym lotnisku
      if (a>=lotniskobedzie-40 && a<=lotniskobedzie+50) {
          if (lotniskobedziex>=szer2 && rzekaod+rzekaszer>szer2) {
             rzekado--;
             rzekaod--;
          } else
          if (lotniskobedziex<szer2 && rzekaod<szer2) {
             rzekado++;
             rzekaod++;
          }
      }

      //"zabierz" rzeke na bok, jesli to miasto
      if (gracz.czymiasto && a>miastood && a<=lotniskobedzie-80) {
         if (a<=miastodo) { //miasto
             if (stronamiasta<0 && rzekaod<maxszer+1) {
                rzekaod++;
                rzekado++;
             } else if (stronamiasta>0 && rzekado>-1) {
                  rzekaod--;
                  rzekado--;
             }
         } else { //przed lotniskiem, doprowadz rzeke do prawie srodka terenu
             if (rzekaod<5) {
                rzekaod++;
                rzekado++;
             } else if (rzekado>maxszer-5) {
                  rzekaod--;
                  rzekado--;
             }
         }
         rzekado=rzekaod+rzekaszer;
      } else { //jesli poza miastem...
          //losowanie szerokosci rzeki
          if (random(20)==0) {
             rzekaszer=rzekaszer-1+random(3);
             if (rzekaszer<5) rzekaszer = 5;
             if (rzekaszer>13) rzekaszer = 13;
          }

          //ograniczenie, zeby nie doszly brzegi rzegi do brzegu mapy jesli nie ma miasta
          if (rzekaod<2) rzekaod=2;
          rzekado=rzekaod+rzekaszer;
          if (rzekaod+rzekaszer>maxszer-4) rzekaod=maxszer-4-rzekaszer;
      }


	}

	//dodanie scenerii
	for (a=wsiood; a<=maxdlug-1; a++)
		for (b=1; b<=maxszer-1; b++) {
			teren[b][a].obiekt=0;
			if ((teren[b][a].y>0) && (rand()%10==0)) //sceneria
			{
				int c=rand()%2;
				teren[b][a].obiektobr=rand()%360;
				teren[b][a].obiekty=teren[b][a].y;
				switch (c)
				{
					case 0:
                  if (random(3-ustawienia.detale)==0) {
                     teren[b][a].obiekt=ob_drzewa+1;
                     teren[b][a].obiektrozm=0.5+rand()%100/90.0;
                     teren[b][a].jasnosc-=teren[b][a].obiektrozm*3.0;
                     if (teren[b][a].jasnosc<0) teren[b][a].jasnosc=0;
                  }
					break;
					case 1:
                  if (random(15-ustawienia.poziomtrudnosci*3)==0) {
                    if (random(2)==0) teren[b][a].obiekt=ob_czolgi;
                                 else teren[b][a].obiekt=ob_dziala;
                    teren[b][a].obiektrozm=1.0;
                    teren[b][a].obiektpatrzyobr=270;//random(360);
                    teren[b][a].obiektpatrzypion=20;//random(30);
                    teren[b][a].obiektcelujewgracza=false;

                    teren[b][a].jasnosc-=teren[b][a].obiektrozm*3.0;
                    if (teren[b][a].jasnosc<0) teren[b][a].jasnosc=0;
                  }
					break;
				}
			} else //budynki
			if ((b>=3 && b<=maxszer-4 && teren[b][a].y>1.0) &&
             (a<lotniskobedzie-40 || a>lotniskobedzie+40) &&
             (!calynowy || (calynowy && a>70)) &&
             (random(170)==0)) //budynki
			{
				int c=random(3); //rodzaj budynku...
                  //najpierw sprawdzmy, czy mozna:
                  bool mozna=true;
						for (b1=-4; b1<=4; b1++)
							for (a1=-5; a1<=3; a1++)
								if (!(a+a1>=0 && a+a1<=maxdlug-1 && b+b1>=0 && b+b1<=maxszer-1 &&
                              teren[b+b1][a+a1].y>=0.4 &&
                              (teren[b+b1][a+a1].obiekt==0 ||
                              teren[b+b1][a+a1].obiekt==ob_drzewa ||
                              teren[b+b1][a+a1].obiekt==ob_drzewa+1)
                              ) )
                              mozna=false;

                  if (gracz.czymiasto && b>=maxszer/2-5 && b<=maxszer/2+5) mozna=false;

                  if (mozna) {
                    teren[b][a].obiekt=ob_budynki+c;
                    if (gracz.czymiasto && a>=miastood && a<=miastodo) {
                       if (random(2)==0) {
                          if (b<=maxszer/2) teren[b][a].obiektobr=90;
                                       else teren[b][a].obiektobr=270;
                       } else teren[b][a].obiektobr=0;
                       teren[b][a].obiektrozm=1+random(100)/100.0;
                    } else {
                      teren[b][a].obiektobr=0;
                      teren[b][a].obiektrozm=1.3;
                    }
                    teren[b][a].obiekty=teren[b][a].y;
                    if (random(20)==0) teren[b][a].obiektcel=true;

                    for (b1=-3; b1<=3; b1++) //wyprasowanie terenu pod budynkiem
                       for (a1=-4; a1<=2; a1++)
                          if ((a+a1>=0) && (a+a1<=maxdlug-1) && (b+b1>=0) && (b+b1<=maxszer-1))
                          {
                             teren[b+b1][a+a1].y=teren[b][a].y;
                             if (b1>=-2 && b1<=2 && a1>=-1 && a1<=1) {
                                teren[b+b1][a+a1].jasnosc=0.1;
                             }
                             if (b1>=-2 && b1<=2 && a1>=-4 && a1<=2) {
                                 teren[b+b1][a+a1].kr=0.3+random(10)/100.0;
                                 teren[b+b1][a+a1].kg=0.3+random(10)/100.0;
                                 teren[b+b1][a+a1].kb=0.3+random(8 )/100.0;
                             }
                             if ((teren[b+b1][a+a1].obiekt<ob_budynki || teren[b+b1][a+a1].obiekt>ob_budynki+4) && teren[b][a].obiektobr==0)
                             {
                                if (b1>=-2 && b1<=2 && (a1<=-2) && (random(4-ustawienia.poziomtrudnosci)==0))
                                {
                                   teren[b+b1][a+a1].obiekty=teren[b+b1][a+a1].y;
                                   if (a1==-4 && b1==-2) teren[b+b1][a+a1].obiekt=ob_dziala;
                                      else teren[b+b1][a+a1].obiekt=ob_czolgi;
                                   teren[b+b1][a+a1].obiektcelujewgracza=false;
                                   teren[b+b1][a+a1].obiektrozm=1.0;
                                   teren[b+b1][a+a1].obiektobr=-60;
                                   teren[b+b1][a+a1].obiektpatrzyobr=random(360);
                                   teren[b+b1][a+a1].obiektpatrzypion=random(30);

                                   teren[b+b1][a+a1].jasnosc-=teren[b+b1][a+a1].obiektrozm*3.0;
                                   if (teren[b+b1][a+a1].jasnosc<0) teren[b+b1][a+a1].jasnosc=0;
                                } else
                                   teren[b+b1][a+a1].obiekt=0;
                             }
                          }
                  }
			} else //barki
			if ( teren[b][a].y<-0.4 && random(250-ustawienia.poziomtrudnosci*10)==0 &&
              b>=2 && b<=maxszer-3 &&
              a>=2 && a<=maxdlug-3 ) //barki
			{
            bool mozna=true;
            for (b1=-1; b1<=1; b1++)
               for (a1=-1; a1<=1; a1++) {
                   if (teren[b+b1][a+a1].y>=-0.4) mozna=false;
               }
            if (mozna)
              for (b1=-2; b1<=2; b1++)
                 for (a1=-2; a1<=2; a1++) {
                     if (teren[b+b1][a+a1].y>=-0.4 || teren[b+b1][a+a1].obiekt>0) mozna=false;
                 }

            if (mozna) {
              teren[b][a].obiekty=0;
              teren[b][a].obiekt=ob_barki;
              teren[b][a].obiektobr=180*random(2)-5+random(11);
              teren[b][a].obiektrozm=1.0;
              teren[b][a].obiektpatrzyobr=random(360);
              teren[b][a].obiektpatrzypion=random(30);
              teren[b][a].obiektcelujewgracza=false;
            }
         }


		}

   if (!gracz.czymiasto)
   { //mosty i ulice
     //miejsce
     int cobedzie;
     for (a=70; a<maxdlug-3; a+=30+rand()%60) {
       if (a<lotniskobedzie-20 || a>lotniskobedzie+50) {
         if (random(10)<=1) cobedzie=1;
            else cobedzie=0;

            //cobedzie=0;

         //a=40;
         //znalezienie najwyzszego punktu na drodze:
         float najw=teren[1][a].y;
         for (int a1=-1; a1<=1; a1++)
             for (b=1; b<=maxszer-1; b++)
                 if (teren[b][a+a1].y>najw) najw=teren[b][a+a1].y;

         najw-=rand()%200/100.0;
         if (najw<1) najw=1;
         //czyszczenie pod drogami
         for (int a1=-1; a1<=1; a1++)
             for (b=0; b<=maxszer-1; b++)
                 teren[b][a+a1].obiekt=0;

         //stawianie obiektow drogi i mostu
         for (b=0; b<=maxszer-1; b+=2) {
             if ( (b>=1 && teren[b-1][a].y<=0.3) ||
                  (b>=2 && teren[b-2][a].y<=0.3) ||
                  (b<maxszer-1 && teren[b+1][a].y<=0.3) ||
                  (b<maxszer-2 && teren[b+2][a].y<=0.3)
             ) teren[b][a].obiekt=ob_mosty+cobedzie;
                else teren[b][a].obiekt=ob_ulice+cobedzie;
             teren[b][a].obiektrozm=1;
             teren[b][a].obiektobr=90;
             teren[b][a].obiekty= najw+0.01;
         }

         //jesli most ma stac sie celem...
         if (random(6/*10*/)==0) {
            //sprawdz czy i gdzie jest most
            int mx1=-1,mx2=-1;
            for (int b=0; b<=maxszer-1; b++)
                if (teren[b][a].obiekt==ob_mosty ||
                    teren[b][a].obiekt==ob_mosty+1)
                {
                   mx1=b;
                   b=maxszer;
                }
            for (int b=maxszer-1; b>=0; b--)
                if (teren[b][a].obiekt==ob_mosty ||
                    teren[b][a].obiekt==ob_mosty+1)
                {
                   mx2=b;
                   b=-1;
                }
            //jest most, daj na srodek cel:
            if (mx1>=0 || mx2>=1) {
               teren[ (((mx2-mx1)/2 +mx1)/2)*2 ][a].obiektcel=true;
            }


         }

         //lampy
         if (cobedzie==0 && random(2)==0) {
             int n=-1;
             for (b=0; b<=maxszer-1; b+=4) {
                 if (!( (b>=1 && teren[b-1][a].y<=0.3) ||
                      (b>=2 && teren[b-2][a].y<=0.3) ||
                      (b<maxszer-1 && teren[b+1][a].y<=0.3) ||
                      (b<maxszer-2 && teren[b+2][a].y<=0.3) )
                 ) {
                     n=-n;
                     teren[b][a+n].obiekt=ob_lampy;
                     teren[b][a+n].obiektrozm=1;
                     teren[b][a+n].obiektobr=n*90+90;
                     teren[b][a+n].obiekty= najw;
                 }
             }
         }

         //podniesienie terenu pod droga
         for (int a1=-1; a1<=1; a1++)
             for (b=0; b<=maxszer-1; b++)
                 if (teren[b][a+a1].y>=0) teren[b][a+a1].y= najw;

         //drzewka przy drodze
         for (int a1=-2; a1<=2; a1+=4)
             for (b=1; b<=maxszer-2; b+=3-ustawienia.detale)
                 if (teren[b][a+a1].y>=0 && random(3)<=1) {
                    teren[b][a+a1].obiektobr=rand()%360;
                    teren[b][a+a1].obiekty= teren[b][a+a1].y;
                    teren[b][a+a1].obiekt=ob_drzewa+1;
                    teren[b][a+a1].obiektrozm=0.5+rand()%100/90.0;
                    teren[b][a+a1].jasnosc-=teren[b][a].obiektrozm*3.0;
                    if (teren[b][a+a1].jasnosc<0) teren[b][a].jasnosc=0;
                 }

         //pojazdy:
         if (random(4/* 4 */)==0) {
            int gdziewstaw=random(2);
            int cowstaw;

            if (cobedzie==0) { //droga
               cowstaw=random(2)+1;
            } else { //tory
               cowstaw=3;
            }
            if (gdziewstaw==0) teren[1][a].wstawruchome=cowstaw;
                          else teren[maxszer-2][a].wstawruchome=cowstaw;
         }

         //ruchome barki:
         if (random(4/* 4 */)==0) {
            int rod=-1,rdo=-1;
            int dod=(2+random(10)) * (random(2)*2-1);
            for (a1=1; a1<=maxszer-2; a1++) {
                if (teren[a1][a-dod].y<=-0.4 && rod==-1) rod=a1;
                else
                if (teren[a1][a-dod].y>-0.4 && rod>=0) {
                   rdo=a1;
                   a1=maxszer;
                }
            }
            if (rod>=1 && rdo>=4) {
                if (dod>=0) teren[rod+ (rdo-rod)/2][a-dod].wstawruchome=6;
                       else teren[rod+ (rdo-rod)/2][a-dod].wstawruchome=7;
            }
         }
       }

     }//for


   }

   //------------miasto:
   if (gracz.czymiasto) {
      //glowna ulica
         int ulicax=maxszer/2;
         int n=-1;

         //znalezienie najwyzszego punktu na drodze:
         float najw=teren[ulicax][miastood+10].y;
         for (int a1=miastood+30; a1<miastodo-20; a1++)
             for (b=ulicax-1; b<=ulicax+1; b++)
                 if (teren[b][a1].y>najw) najw=teren[b][a1].y;

         najw-=rand()%200/100.0;
         if (najw<1) najw=1;

         //czyszczenie pod drogami
         for (int a1=miastood+30; a1<miastodo-20; a1++)
             for (b=ulicax-2; b<=ulicax+2; b++)
                 teren[b][a+a1].obiekt=0;

         //rysujemy droge
         for (a=miastood+30; a<miastodo-20; a++) {
             if (a%2==0) {
                 //stawianie obiektow drogi
                 teren[ulicax][a].obiekt=ob_ulice;
                 teren[ulicax][a].obiektrozm=1;
                 teren[ulicax][a].obiektobr=0;
                 teren[ulicax][a].obiekty= najw+0.01;

                 //lampy
                 n=-n;
                 teren[ulicax+n][a].obiekt=ob_lampy;
                 teren[ulicax+n][a].obiektrozm=1;
                 teren[ulicax+n][a].obiektobr=n*90;
                 teren[ulicax+n][a].obiekty= najw;

                 if (a>=miastood+30+30 && a<=miastodo-20-30 && a%8==0 && random(5)==0)
                    teren[ulicax][a].wstawruchome= 2;

             }

             //podniesienie terenu pod droga
             for (b=ulicax-1; b<=ulicax+1; b++)
                 if (teren[b][a].y>=0) teren[b][a].y= najw;

/*             //drzewka przy drodze
             for (int a1=-2; a1<=2; a1+=4)
                 for (b=1; b<=maxszer-2; b+=3-ustawienia.detale)
                     if (teren[b][a+a1].y>=0 && random(3)<=1) {
                        teren[b][a+a1].obiektobr=rand()%360;
                        teren[b][a+a1].obiekty= teren[b][a+a1].y;
                        teren[b][a+a1].obiekt=ob_drzewa+1;
                        teren[b][a+a1].obiektrozm=0.5+rand()%100/90.0;
                        teren[b][a+a1].jasnosc-=teren[b][a].obiektrozm*3.0;
                        if (teren[b][a+a1].jasnosc<0) teren[b][a].jasnosc=0;
                     }
*/
/*             //pojazdy:
             if (random(4/* 4 *)==0) {
                int gdziewstaw=random(2);
                int cowstaw;

                if (cobedzie==0) { //droga
                   cowstaw=random(2)+1;
                } else { //tory
                   cowstaw=3;
                }
                if (gdziewstaw==0) teren[1][a].wstawruchome=cowstaw;
                              else teren[maxszer-2][a].wstawruchome=cowstaw;
             }
*/
/*             //ruchome barki:
             if (random(4/* 4 *)==0) {
                int rod=-1,rdo=-1;
                int dod=(2+random(10)) * (random(2)*2-1);
                for (a1=1; a1<=maxszer-2; a1++) {
                    if (teren[a1][a-dod].y<=-0.4 && rod==-1) rod=a1;
                    else
                    if (teren[a1][a-dod].y>-0.4 && rod>=0) {
                       rdo=a1;
                       a1=maxszer;
                    }
                }
                if (rod>=1 && rdo>=4) {
                    if (dod>=0) teren[rod+ (rdo-rod)/2][a-dod].wstawruchome=6;
                           else teren[rod+ (rdo-rod)/2][a-dod].wstawruchome=7;
                }
             }*/

         }//for


         a=miastood+100+random(200);
         wstaw_lotnisko(a, 13, false, true);
         a+=100+random(100);
         wstaw_lotnisko(a, 13, false, true);

   }
   //------------koniec miasta

   //lotniska
   if (calynowy)
      wstaw_lotnisko(15, 35, calynowy);
   wstaw_lotnisko(lotniskobedzie, lotniskobedziex, false);
   gracz.jest_lotnisko=false;
   gracz.ostrzezenie_o_lotnisku=lotniskobedzie-ile_wczesniej_informowac_o_lotnisku;

   //przyciemnianie zaglebien w terenie
   for (a=wsiood; a<=maxdlug-1; a++) {
	    for (b=0; b<=maxszer-1; b++)
           if ((teren[b][a].y<teren[b][a+1].y) || (teren[b][a].y<teren[b+1][a].y))
           {
              //teren[b][a].jasnosc = teren[b][a].jasnosc + (teren[b][a].y-teren[b+1][a].y)*2.0;
              teren[b][a].jasnosc = teren[b][a].jasnosc + (teren[b][a].y-teren[b][a+1].y)*0.5;
              teren[b][a+1].jasnosc = teren[b][a+1].jasnosc + (teren[b][a].y-teren[b][a+1].y)*0.5;
              //teren[b][a-1].jasnosc = teren[b][a-1].jasnosc + (teren[b][a].y-teren[b][a+1].y)*4.0;
              if (teren[b][a].jasnosc<0.15) teren[b][a].jasnosc=0.15;
              if (teren[b][a].jasnosc>1.0) teren[b][a].jasnosc=1.0;
           }
		}

   //
	for (b=0; b<=80; b++)
		for (a=0; a<=50; a++) {
          woda[a][b].rnd=random(5000);
      }

   //oznaczenie gdzie jest woda
	for (b=0; b<=maxdlug-1; b++)
		for (a=0; a<=maxszer-1; a++) {
          if (teren[a][b].y<=0) teren[a][b].jestwoda=1;
             else teren[a][b].jestwoda=0;
      }


   //rozszerzenie wody
   for (int n=0; n<=2; n++) {
       byte terenwoda[terensz][terendl];

       for (b=0; b<=maxdlug-1; b++)
          for (a=0; a<=maxszer-1; a++) {
              terenwoda[a][b]=teren[a][b].jestwoda;
          }

       for (b=0; b<=maxdlug-1; b++)
          for (a=0; a<=maxszer-1; a++) {
              if ((a>=1 && terenwoda[a-1][b]==1) ||
                  (b>=1 && terenwoda[a][b-1]==1) ||
                  (a<maxszer-1 && terenwoda[a+1][b]==1) ||
                  (b>maxdlug-1 && terenwoda[a][b+1]==1)
                 )
                 teren[a][b].jestwoda=1;
          }
   }

   //wyznaczenie kolejnosci rysowania (drzewa pozniej)
	for (b=0; b<=maxszer-1; b++)
		for (a=0; a<=maxdlug-1; a++) {
          switch (teren[b][a].obiekt) {
            case ob_drzewa:
            case ob_drzewa+1:
              teren[b][a].obiektktoreprzejscie=1;
            break;
            default:
              teren[b][a].obiektktoreprzejscie=0;
          }
		}

   //wyrownanie krawedzi terenu tak, by nie szly po rozciagnieciu w gore
   for (b=0; b<=maxszer-1; b++) {
       teren[b][0].y= teren[b][1].y;
       teren[b][maxdlug-1].y= teren[b][maxdlug-2].y;
       teren[b][0].jasnosc= 0.7;
       teren[b][maxdlug-1].jasnosc= 0.7;
   }
   for (b=0; b<=maxdlug-1; b++) {
       teren[0][b].y= teren[1][b].y;
       teren[maxszer-1][b].y= teren[maxszer-2][b].y;
       teren[0][b].jasnosc= 0.7;
       teren[maxszer-1][b].jasnosc= 0.7;
   }

	//obliczanie normalnych terenu - to musi byc na koncu
	for (b=1; b<=maxdlug-1; b++)
		for (a=1; a<=maxszer-1; a++) {
			vek1[0] = 1.0;
			vek1[1] = (teren[(int)a+1][(int)b  ].y-teren[(int)a  ][(int)b  ].y);
			vek1[2] = 0.0;

			vek2[0] = 0.0;
			vek2[1] = (teren[(int)a  ][(int)b+1].y-teren[(int)a  ][(int)b  ].y);
			vek2[2] = 1.0;

			cross_prod(vek2,vek1, vek3);

			teren[a][b].norm[0]=vek3[0];
			teren[a][b].norm[1]=vek3[1];
			teren[a][b].norm[2]=vek3[2];
		}


   if (!calynowy) {
      if (gracz.etap>=3-ustawienia.poziomtrudnosci && random(2)==0) //noc moze sie zdarzyc tylko po 3-cim etapie i raz na 2 razy
         ustawienia.dojasnoscswiatla=0.4+random(60)/100.0;
      else
         ustawienia.dojasnoscswiatla=0.7+random(30)/100.0;
   }

}

void nowagra()
{
   int a;

   if (!gracz.winieta) {
      FSOUND_SetPaused(muzyka_chan, TRUE);
      gracz.jest_gra = false;
   } else {
      if (FSOUND_GetPaused(muzyka_chan)) {
         FSOUND_SetPaused(muzyka_chan, FALSE);
         FSOUND_Stream_SetTime(muzyka, 0);
      }
      gracz.jest_gra = true;
   }

	for (a=0; a<maxpoc; a++) {
		poc[a].jest=0;
	}

	dx0=(float)dkrok*maxszer*0.5;
	dz0=0;

	wodakrok=2.0;

	wodax0=-dx0/wodakrok;
	wodaz0=-dx0/wodakrok;
	wodadx0=dx0/wodakrok;
	wodadz0=dx0/wodakrok;
	wodailex0=wodadx0-wodax0;
	//wodailez0=wodadz0-wodaz0;
   wodailez0=ilewidac_do-ilewidac_od;
	dz0=40;


	//samoloty
	for (a=0; a<ils; a++) {
		samolot[a].rodzaj=0;

		samolot[a].x=0;
		samolot[a].z=0;
		samolot[a].y=0;
		samolot[a].dx=0;
		samolot[a].dy=0;
		samolot[a].dz=0;

		samolot[a].rozm=1;
		samolot[a].smiglo=0;
		samolot[a].dzialotemp=0;
		samolot[a].jest=0;

		samolot[a].ileuszkodzen=0;
		samolot[a].zniszczony=0;
      for (int b=0; b<=3; b++) samolot[a].uszkodzenia[b]=0;
	}

	for (a=0; a<maxpoc; a++) poc[a].jest=0;
	for (a=0; a<maxwyb; a++) wyb[a].jest=0;
	for (a=0; a<maxruchome; a++) ruchome[a].jest=0;
	for (a=0; a<maxsmiec; a++) smiec[a].jest=0;
	for (a=swiatlaod; a<=swiatlado; a++) swiatla[a].jasnosc=0;

   gracz.czymiasto=false;
   stworz_teren();

	gracz.corobi=0;
   gracz.na_poziomie_samolotu=false;
/*	samolot[sterowanie].y=0;
	samolot[sterowanie].x=10.0;
	samolot[sterowanie].z=5.0;*/
	samolot[sterowanie].jest=1;

	szybkosc=0;//0;

	gracz.fuel=300;
	gracz.score=0;
	gracz.bomb=30;

   gracz.ile_celow_glownych=0;
   gracz.ile_celow_glownych_teraz=0;

   gracz.jaki_cel_pokazuje=-1;

   //ekran
   ekran.fuel=gracz.fuel-1;
   ekran.bomb=gracz.bomb-1;
   ekran.score=gracz.score-1;
   ekran.spd=-1;
   ekran.alt=-1;
   ekran.odswiezwiatr=1;
   ekran.odswiezuszkodzenia=1;
   ekran.ostrzezenieosamolocie=6;
   ekran.odswiezostrzezenieosamolocie=1;

   gracz.etap=0;
   gracz.rank=0;
   gracz.koniecgry=0;

   switch (ustawienia.poziomtrudnosci) {
       case 0:
          ustawienia.jasnoscswiatla=0.9; /* 0.9 */
       break;
       case 1:
          ustawienia.jasnoscswiatla=0.7+random(200)/1000.0; /* 0.9 */
       break;
       case 2:
          ustawienia.jasnoscswiatla=0.5+random(400)/1000.0; /* 0.9 */
       break;
   }
   ustawienia.dojasnoscswiatla=ustawienia.jasnoscswiatla+0.001;
   kameraczas=0;
   if (kamera==5) kamera=1;

   for (int a=0; a<=255; a++) {
       kl[a]=0;
       kln[a]=0;
   }

   for (int a=0; a<ils; a++)
   if (!FSOUND_IsPlaying(kanaly[a]))
   {
       kanaly[a] = FSOUND_PlaySound(FSOUND_FREE, dzwiek[4]);
       FSOUND_SetPaused(kanaly[a], true);
   }

   FSOUND_SetSFXMasterVolume(floor(ustawienia.glosnosc*25.5));

   ustawienia.pauza=false;
   BMForm->TimerDzialaj->Enabled=true;
   BMForm->TimerRys->Enabled=true;
   BMForm->LPauza->Visible=false;
   BMForm->PanelDolny->Show();
   BMForm->PanelWinieta->Hide();
}

void ustaw_klawisze_sterowania()
{
   switch (ustawienia.typsterowania) {
     case 0:
     kldol=VK_DOWN;
     klgora=VK_UP;
     break;
     case 1:
     kldol=VK_UP;
     klgora=VK_DOWN;
     break;
   }
}

void sortujrekordy()
{
   bool ok=false;
   while (!ok) {
       ok=true;
       for (int a=ilemiejsc-2; a>=0; a--) {
           if (rekordy[a].pkt<rekordy[a+1].pkt) {
              rekord r=rekordy[a];
              rekordy[a]=rekordy[a+1];
              rekordy[a+1]=r;
              ok=false;
           }
       }
   }
}

void standardoweustawienia()
{
   ustawienia.poziomtrudnosci=0;
	ustawienia.rodzajwody=1;
   ustawienia.typsterowania=1;
   ustaw_klawisze_sterowania();
   ustawienia.odleglosckamery=12;
   ustawienia.detale=2;
   ustawienia.jestniebo=true;
   ustawienia.wskazniki=true;

   for (int a=0; a<ilemiejsc; a++) {
       rekordy[a].pkt=50+random(200);
       rekordy[a].imie="BlueMax";
       rekordy[a].rank=random(3);
   }

   sortujrekordy();

}

//-----------------init-------------------------------------------------
void init()
{
	int a,b, a1,b1, w;

	glGenTextures(iletekstur, texName);

//        AnsiString g= GetCurrentDir();
	wczytaj_teksture(0, "dane\\niebo1.tga",1);
 	wczytaj_teksture(1, "dane\\dnobw.tga",0);
   wczytaj_teksture(2, "dane\\celownik.tga",0);
	wczytaj_teksture(3, "dane\\budsciana.tga",0);
	wczytaj_teksture(4, "dane\\dach.tga",0);
	wczytaj_teksture(5, "dane\\lotnisko.tga",0);
	wczytaj_teksture(6, "dane\\ulica.tga",0);
	wczytaj_teksture(7, "dane\\beton.tga",0);
	wczytaj_teksture(8, "dane\\wyb2.tga",0);
	wczytaj_teksture(9, "dane\\dym1.tga",0);
	wczytaj_teksture(10,"dane\\drzewo1.tga",0);
	wczytaj_teksture(11,"dane\\licznik.tga",0);
	wczytaj_teksture(12,"dane\\wskazowk.tga",0);
	wczytaj_teksture(13,"dane\\ziemia.tga",0);
//	wczytaj_teksture(14,"dane\\szalik.tga",0); !!!!!!!!!!
	wczytaj_teksture(15,"dane\\autotex.tga",0);
	wczytaj_teksture(16,"dane\\tory.tga",0);
	wczytaj_teksture(17,"dane\\swiatlo.tga",0);
	wczytaj_teksture(18,"dane\\ogien.tga",0);
	wczytaj_teksture(19,"dane\\woda.tga",0);
	wczytaj_teksture(20,"dane\\plusk.tga",0);
	wczytaj_teksture(21,"dane\\pockolo.tga",0);
	wczytaj_teksture(22,"dane\\dzialo.tga",0);
	wczytaj_teksture(23,"dane\\czolg.tga",0);
	wczytaj_teksture(24,"dane\\statek.tga",0);
	wczytaj_teksture(25,"dane\\budsciana2.tga",0);
	wczytaj_teksture(26,"dane\\samolot1.tga",0);
	wczytaj_teksture(27,"dane\\samolot2.tga",0);
	wczytaj_teksture(28,"dane\\samolot1a.tga",0);
	wczytaj_teksture(29,"dane\\samolot2a.tga",0);
	wczytaj_teksture(30,"dane\\szalik.tga",0);
	wczytaj_teksture(31,"dane\\szalik2.tga",0);
	wczytaj_teksture(32, "dane\\niebo2.tga",0);

	randomize();

   kula = gluNewQuadric();
   drzewo = gluNewQuadric();
        kolo = gluNewQuadric();

   ustawienia.mgla=true;
   ustawienia.pauza=false;
   ustawienia.glosnosc=10;

	glClearColor(0.6, 0.6, 0.7, 0.0);
//	glShadeModel(GL_FLAT);
//	glShadeModel(GL_FILL);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL); //fill
	glPolygonMode(GL_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glFrontFace (GL_CCW);
   glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_LIGHTING);

//   glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    if (ustawienia.mgla) glEnable(GL_FOG);
    {
        //GLfloat fogColor[4] = {0.1, 0.2, 0.6, 0.01};
        GLfloat fogColor[4] = {0.6, 0.6, 0.7, 0.1};

        glFogf (GL_FOG_START, 50.0);
        glFogf (GL_FOG_END, 80.0);

        glFogi (GL_FOG_MODE, GL_LINEAR);
        glFogfv(GL_FOG_COLOR, fogColor);
        //glFogf (GL_FOG_DENSITY, 0.11);
        glHint (GL_FOG_HINT, GL_FASTEST);
    }

/*   //slonce
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f); //obciecie stozka
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 00.0f); //wygaszanie na brzegach swiatla
//	glEnable(GL_LIGHT0); -chyba nie bedzie potrzebne
*/
   //globalne
/*	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);*/
	glEnable(GL_LIGHT1);

   //wybuch
/*	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight0);*/
//	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0f); //obciecie stozka
//	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 60.0f); //wygaszanie na brzegach swiatla
	//glEnable(GL_LIGHT2);

   //lampa przy lotnisku:
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f); //obciecie stozka
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f); //wygaszanie na brzegach swiatla


	glPointSize(0);
   glLineWidth(0);
   glEdgeFlag(GL_FALSE);
	//tworzenie obiektow
	stworz_listy();

   float m[4]= { 1.0, 1.0, 1.0, 1.0};
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, m);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   standardoweustawienia();
   gracz.winieta=true;
//   nowagra();

   gracz.jest_gra = false;

   BMForm->pokazWiniete();

}

void odswiezwidok()
{
   int width=BMForm->ClientRect.Right, height=BMForm->ClientRect.Bottom;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (kamera!=8) {
      gluPerspective(50.0, (GLfloat) width/ (GLfloat) height,
                     0.2/*nie dawac mniej,bo sie zbuffer jebie*/, 1700.0);
      ustawienia.mgla=true;   glEnable(GL_FOG);
//      ustawienia.mgla=false; glDisable(GL_FOG);
   } else {
      glOrtho(-width/(55-ustawienia.odleglosckamery),
              width/(55-ustawienia.odleglosckamery),
              -height/(55-ustawienia.odleglosckamery),
              height/(55-ustawienia.odleglosckamery),
              0.2, 100.0);
      ustawienia.mgla=false;
      glDisable(GL_FOG);

   }
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

