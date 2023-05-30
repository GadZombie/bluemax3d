
//---------------------------------------------------------------------------
void noweruchome(float zx,float zz, int rodz, int bedzieprzyczepionydo=-1,  float offset=0, float ndx=0, int ile=0)
{
	int a,b=-1;

	for (a=0; a<maxruchome; a++)
		if (ruchome[a].jest==0)
		{
			b=a;
			break;
		}

	if ((b>=0) && (b<=maxruchome))
	{
/*      if ((int)zx<0) ruchome[b].y=teren[0][(int)zz].y;
      else if ((int)zx>maxszer-1) ruchome[b].y=teren[maxszer-1][(int)zz].y;
      else ruchome[b].y=teren[(int)zx][(int)zz].y;
*/
      float nzx=zx*dkrok-dx0;
      float nzz=(float) -zz*dkrok+dz0 + fmod(dz0, dkrok)-dkrok/2.0;

      int spx = (int)nzx;
      if (spx<0) spx=0;
      else if (spx>maxszer-1) spx=maxszer-1;

      ruchome[b].y=gdzie_y_integer(spx,nzz);

		ruchome[b].x=nzx;
		ruchome[b].z=nzz;
		ruchome[b].dy=0;
		ruchome[b].rodzaj=rodz;
		ruchome[b].jest=1;
		ruchome[b].zniszcz=false;
      ruchome[b].przyczepionydo=bedzieprzyczepionydo;

      ruchome[b].obiektpatrzyobr=0;
      ruchome[b].obiektpatrzypion=0;
      ruchome[b].ktorykanal=-1;

      if (random(15)==0) ruchome[b].cel=true;
                    else ruchome[b].cel=false;

      if (ruchome[b].cel && gracz.jaki_cel_pokazuje==-1) {
         gracz.jaki_cel_pokazuje=1;
         gracz.ktory_cel_pokazuje=b;
      }

      switch (rodz) {
        case 1: //czolg na drodze
           if (nzx<0) {
             ruchome[b].dx= 0.12+random(10)/100.0;
             ruchome[b].obrot= 90;
           } else {
             ruchome[b].dx=-0.12-random(10)/100.0;
             ruchome[b].obrot= 270;
           }
		     ruchome[b].dz=0;
           ruchome[b].rozmiar=1.5;

           ruchome[b].ktorykanal = FSOUND_PlaySound(FSOUND_FREE, dzwiek[9]);
           FSOUND_SetVolume(ruchome[b].ktorykanal, 0);
           if (!FSOUND_GetPaused(ruchome[b].ktorykanal))
              FSOUND_SetPaused(ruchome[b].ktorykanal, false);
           FSOUND_SetFrequency(ruchome[b].ktorykanal, 44100);

        break;
        case 2: //auto na drodze
		     ruchome[b].dz=0;
           if (nzx<-10) {
             ruchome[b].dx= 0.15+random(10)/100.0;
             ruchome[b].obrot= 90;
           } else if (nzx>10) {
             ruchome[b].dx=-0.15-random(10)/100.0;
             ruchome[b].obrot= 270;
           } else {
             ruchome[b].dx=0;
             if (random(2)==0) {
                ruchome[b].dz=-0.11;//-random(10)/100.0;
                ruchome[b].obrot=180;
                ruchome[b].x+=1;
             } else {
                ruchome[b].dz=0.11;//-random(10)/100.0;
                ruchome[b].obrot=0;
                ruchome[b].x-=1;
             }
           }
           ruchome[b].rozmiar=1.2;
        break;
        case 3: //lokomotywa
           ruchome[b].z+=0.5;
           if (nzx<0) {
             if (ndx==0) ruchome[b].dx= 0.15+random(10)/100.0;
                else ruchome[b].dx=ndx;
             ruchome[b].obrot= 90;
           } else {
             if (ndx==0) ruchome[b].dx=-0.15-random(10)/100.0;
                else ruchome[b].dx=ndx;
             ruchome[b].obrot= 270;
           }
		     ruchome[b].dz=0;
       //  ruchome[b].rozmiar=1.8;

           ruchome[b].y=gdzie_y_integer(spx,ruchome[b].z);

           ruchome[b].ktorykanal = FSOUND_PlaySound(FSOUND_FREE, dzwiek[7]);
           FSOUND_SetVolume(ruchome[b].ktorykanal, 0);
           if (!FSOUND_GetPaused(ruchome[b].ktorykanal))
              FSOUND_SetPaused(ruchome[b].ktorykanal, false);
           FSOUND_SetFrequency(ruchome[b].ktorykanal, 44100);

           noweruchome(zx,zz,4, b, -2.7, ruchome[b].dx);
        break;
        case 4: //weglarka
           ruchome[b].z+=0.5;
           if (nzx<0) {
             if (ndx==0) ruchome[b].dx= 0.15+random(10)/100.0;
                else ruchome[b].dx=ndx;
             ruchome[b].obrot= 90;
           } else {
             if (ndx==0) ruchome[b].dx=-0.15-random(10)/100.0;
                else ruchome[b].dx=ndx;
             ruchome[b].obrot= 270;
           }
		     ruchome[b].dz=0;
           ruchome[b].rozmiar=1.0;

           ruchome[b].y=gdzie_y_integer(spx,ruchome[b].z);
           ruchome[b].cel=false;

           noweruchome(zx,zz,5, b, offset-2.3, ruchome[b].dx, 2+random(7));
        break;
        case 5: //wagon
           ruchome[b].z+=0.5;
           if (nzx<0) {
             if (ndx==0) ruchome[b].dx= 0.15+random(10)/100.0;
                else ruchome[b].dx=ndx;
             ruchome[b].obrot= 90;
           } else {
             if (ndx==0) ruchome[b].dx=-0.15-random(10)/100.0;
                else ruchome[b].dx=ndx;
             ruchome[b].obrot= 270;
           }
		     ruchome[b].dz=0;
           ruchome[b].rozmiar=1.0;

           ruchome[b].y=gdzie_y_integer(spx,ruchome[b].z);

           if (ile>0)
              noweruchome(zx,zz,5, b, offset-3.0, ruchome[b].dx, ile-1);
        break;

        case 6: //barka plynaca w strone gracza
        case 7: //barka plynaca w strone od gracza
           ruchome[b].dx= 0;
           if (rodz==6) {
              ruchome[b].dz=0.1+random(100)/1000.0;
              ruchome[b].obrot= 0;
           } else {
              ruchome[b].dz=-0.05-random(100)/1000.0;
              ruchome[b].obrot= 180;
           }
           ruchome[b].rozmiar=1.0;
           ruchome[b].y=0;
		     ruchome[b].rodzaj=6;
        break;

      }
      if (ruchome[b].dx<0) offset = -offset;
      ruchome[b].x = ruchome[b].x + offset;

   }

}

//---------------------------------------------------------------------------
void strzel(float zx,float zy,float zz, float dx,float dy,float dz, int czyj, int rodz)
{
	int a,b=-1;

	for (a=0; a<=maxpoc; a++)
		if (poc[a].jest==0)
		{
			b=a;
			break;
		}

	if ((b>=0) && (b<=maxpoc))
	{
		poc[b].x=zx;
		poc[b].y=zy;
		poc[b].z=zz;
		poc[b].dx=dx;
		poc[b].dy=dy;
		poc[b].dz=dz;
		poc[b].rodzaj=rodz;
		poc[b].obrotx=0;
		poc[b].obroty=0;
		poc[b].obrotz=0;

		if (rodz==0) {
//			GLfloat wek[3];
			poc[b].rozm=0.05;

/*			wek[0]=dx;
			wek[1]=dy;
			wek[2]=dz;

			normalize0(wek);

			if (dz<=0) poc[b].obrotx = jaki_to_kat(1,wek[1]);
					else poc[b].obrotx = -jaki_to_kat(1,wek[1]);
			poc[b].obroty = jaki_to_kat(1,wek[2]);
			poc[b].obrotz = 90+jaki_to_kat(1,wek[0]);*/

         int k = (-jaki_to_kat(dx, dz)+360)%360;
         poc[b].obroty = k;

         k = jaki_to_kat( sqrt( pow(dx,2) + pow(dz, 2)), dy);

         poc[b].obrotx = k;

		} else {
			poc[b].rozm=0.18;
			poc[b].dz-=szybkoscc;
		}
		poc[b].jest=1;
		poc[b].czyj=czyj;
		poc[b].czas=30;
	}

}

//---------------------------------------------------------------------------
void noweswiatlo(float zx,float zy,float zz)
{
	int a,b=-1;

	for (a=swiatlaod; a<=swiatlado; a++)
		if (swiatla[a].jasnosc<=0)
		{
			b=a;
			break;
		}

   if (b==-1) {
      b=swiatlaod+random(swiatlado-swiatlaod+1);
   }

	if ((b>=swiatlaod) && (b<=swiatlado))
	{
       swiatla[b].x=zx;
       swiatla[b].y=zy+25;
       swiatla[b].z=zz;
       swiatla[b].jasnosc=1.0;
       swiatla[b].czas=1.0;
   }
}

//---------------------------------------------------------------------------
void nowywyb( float zx,float zy,float zz, float dx,float dy,float dz,
              float szybrozm_, float szybprzezr_, float maxrozm_,
              float r_=0.7, float g_=0.4, float b_=0.05,
              short int rodz=0,
              float przezroczystosc=1.0, float waga=0, float rozmiarpoczatkowy=0)
{
	int a,b=-1;

	for (a=0; a<=maxwyb; a++)
		if (wyb[a].jest==0)
		{
			b=a;
			break;
		}

   if (b==-1 && random(2)==0)
   {
     b=random(maxwyb);
   }

	if ((b>=0) && (b<=maxwyb))
	{
		wyb[b].x=zx;
		wyb[b].y=zy;
		wyb[b].z=zz;
		wyb[b].dx=dx;
		wyb[b].dy=dy;
		wyb[b].dz=dz;
		wyb[b].obrot=0;

		wyb[b].rozm=rozmiarpoczatkowy;
		wyb[b].przezr=przezroczystosc;
		wyb[b].szybkoscrozm=szybrozm_;
		wyb[b].szybkoscprzezr=szybprzezr_;
		wyb[b].maxrozm=maxrozm_;
		wyb[b].waga=waga;

		wyb[b].r=r_;
		wyb[b].g=g_;
		wyb[b].b=b_;

		wyb[b].rodzaj=rodz;

		wyb[b].jest=1;
	}

}

//---------------------------------------------------------------------------
void caly_wybuch(float x,float y,float z, int ilosc=5, int duzywybuch=0)
{
  for (int wn=1; wn<=ilosc*3; wn++)
    nowywyb( x,y,z,

             rand()%100/1000.0-0.05,
             rand()%100/1000.0-0.02,
             rand()%100/1000.0-0.05,

             rand()%50/500.0+0.02,
             rand()%50/500.0+0.01,
             rand()%100/100.0+2,
             1,1,1,2
             );
/*if (duzywybuch==1)
    nowywyb( x,y,z,
             0,0,0,
             0.2,
             0.03,
             7,
             0.7,0.4,0.05,0,
             0.1
             );
  */
  noweswiatlo(x,y,z);

/*  if (duzywybuch==1)   //uszkodz pobliskie ruchome
    for (int b=0; b<maxruchome; b++)
       if (ruchome[b].jest && !ruchome[b].zniszcz) {
         float _x=fabs(x-ruchome[b].x);
         float _y=fabs(y-ruchome[b].y);
         float _z=fabs(z-ruchome[b].z);
         if ((_x==0) && (_y==0) && (_z==0)) {
            _x=0.01;
         }

         float c=sqrt(_x*_x + _y*_y + _z*_z);

         if (c<=ruchome[b].rozmiar+1.0) {
             gracz.score+=100;
             ruchome[b].zniszcz=true;
         }

   }
*/

}

//---------------------------------------------------------------------------
void nowysmiec( float zx,float zy,float zz, float dx,float dy,float dz,
                float rx_,float ry_,float rz_,
                float waga_=0.05,
                float r_=0.2, float g_=0.2, float b_=0.2,
                short int plonie_=1, short int dymi_=1)
{
	int a,b=-1;

	for (a=0; a<=maxsmiec; a++)
		if (smiec[a].jest==0)
		{
			b=a;
			break;
		}

	if ((b>=0) && (b<=maxsmiec))
	{
		smiec[b].x=zx;
		smiec[b].y=zy;
		smiec[b].z=zz;
		smiec[b].dx=dx;
		smiec[b].dy=dy;
		smiec[b].dz=dz;
		smiec[b].obrot=random(360);

		smiec[b].rx=rx_;
		smiec[b].ry=ry_;
		smiec[b].rz=rz_;
		smiec[b].waga=waga_;

		smiec[b].r=r_;
		smiec[b].g=g_;
		smiec[b].b=b_;

		smiec[b].dymi=dymi_;
		smiec[b].plonie=plonie_;

		smiec[b].jest=1;
	}

}

//---------------------------------------------------------------------------
void rozsypsmieci( float zx,float zy,float zz,
                   float sila, float ile,
                   float wielkosc_od=0.1, float wielkosc_do=0.3,
                   float waga_od=0.008, float waga_do=0.02,
                   float r_=0.2, float g_=0.2, float b_=0.2,
                   short int plonie_=1, short int dymi_=1, short int deski=1)
{
  for (int a=1; a<=ile; a++)
  {
    float rx,ry,rz, wielk;
    wielk=wielkosc_do-wielkosc_od;
    rx=random((int)100.0*wielk)/100.0+wielkosc_od;
    ry=random((int)100.0*wielk)/100.0+wielkosc_od;
    float dd=1;
    if (deski==1) dd=10.0;
    rz=(random((int)100.0*wielk)/100.0+wielkosc_od)/dd;
    nowysmiec( zx,zy,zz,
               random((int)100.0*sila)/140.0-0.5*sila,
               random((int)100.0*sila)/180.0+0.03,
               random((int)100.0*sila)/140.0-0.5*sila,
               rx,ry,rz,
               random((int)100.0*(waga_do-waga_od))+waga_od,
               r_,g_,b_,plonie_,dymi_
              );

  }

}

//---------------------------------------------------------------------------
void ruszaj_ruchome()
{
   int a;

   for (a=0; a<=maxszer; a++)
   {
      if (teren[a][(int)floor(zdo)].wstawruchome>=1) {
         noweruchome(a,zdo,teren[a][(int)zdo].wstawruchome);
         teren[a][(int)floor(zdo)].wstawruchome=0;
      }

   }

	for (a=0; a<maxruchome; a++)
		if (ruchome[a].jest==1)
		{
         float px,pz;
         ruchome[a].x=ruchome[a].x+ruchome[a].dx;
         ruchome[a].z=ruchome[a].z+ruchome[a].dz+szybkoscc;

         px=ruchome[a].x;
         pz=ruchome[a].z;
         gdzie_xz(&px, &pz);

         if (ruchome[a].ktorykanal>=0) {
             int o;
             float o2 = pow(samolot[0].x-ruchome[a].x,2)+pow(samolot[0].y-ruchome[a].y,2)+pow(samolot[0].z-ruchome[a].z,2);
             if (o2==0) o2=0.01;
             o = (int)225 - floor(sqrt( o2*4.0 ) );

             if (o<0) o = 0;
             if (o>225) o = 225;

             FSOUND_SetVolume(ruchome[a].ktorykanal, o);

         }

         //przyczenione wagony pociagu:
         if (ruchome[a].przyczepionydo>=0) {
            if (ruchome[ruchome[a].przyczepionydo].jest==0) {
               ruchome[a].dx*=0.9;
               if (fabs(ruchome[a].dx)<=0.05) {
                  ruchome[a].dx=0;
                  ruchome[a].przyczepionydo=-1;
               }
            } else {
              ruchome[a].dx=ruchome[ruchome[a].przyczepionydo].dx;
              ruchome[a].dz=ruchome[ruchome[a].przyczepionydo].dz;
            }
         }

         if (ruchome[a].rodzaj<=5) { //spadanie z mostu
             if (
                  ( (ruchome[a].dx!=0) &&
                    ((int)px>=1 &&
                     (int)px<=maxszer-2) &&
                     (teren[(int)px][(int)pz].obiekt==0 &&
                     (int)px+1<maxszer-1 &&
                     teren[(int)px+1][(int)pz].obiekt==0 &&
                     (int)px-1>=0 &&
                     teren[(int)px-1][(int)pz].obiekt==0
                    )
                  ) ||
                  ( (ruchome[a].dx==0) &&
                    ((int)pz>=1 &&
                     (int)pz<=maxdlug-2) &&
                     (teren[(int)px][(int)pz].obiekt==0 &&
                     (int)pz+1<maxdlug-1 &&
                     teren[(int)px][(int)pz+1].obiekt==0 &&
                     (int)pz-1>=0 &&
                     teren[(int)px][(int)pz-1].obiekt==0 &&

                     teren[(int)px-1][(int)pz].obiekt==0 &&
                     teren[(int)px+1][(int)pz].obiekt==0
                    )
                  ) ||
                  (ruchome[a].dy<=-0.1) )
             {
                //ruchome[a].zniszcz=true;
                ruchome[a].dx*=0.9;
                ruchome[a].dz*=0.9;
                if (ruchome[a].dy>-0.4) ruchome[a].dy-=0.04;
                ruchome[a].y=ruchome[a].y+ruchome[a].dy;
                if (ruchome[a].y<=gdzie_y_integer(ruchome[a].x,ruchome[a].z))
                   ruchome[a].zniszcz=true;
             }
         }

         //zniszczenie
         if (ruchome[a].zniszcz) {
            caly_wybuch(ruchome[a].x,ruchome[a].y,ruchome[a].z,10,1);
            strzel(ruchome[a].x,ruchome[a].y,ruchome[a].z, 0,-0.4,0, 1,1);

            switch (ruchome[a].rodzaj) {
               case 1: //czolg
                 rozsypsmieci( ruchome[a].x,ruchome[a].y+1,ruchome[a].z,
                               0.30, 18, 1.0, 4.0, 0.015, 0.04,
                               mat_czolg_kd[0], mat_czolg_kd[1], mat_czolg_kd[2], 1, 1);
               break;
               case 2: //auto
                 rozsypsmieci( ruchome[a].x,ruchome[a].y+1,ruchome[a].z,
                               0.25, 13, 0.6, 3.0, 0.006, 0.02,
                               mat_auto_kd[0], mat_auto_kd[1], mat_auto_kd[2], 1, 1);
               break;
               case 3: //lokomotywa
               case 4: //weglarka
               case 5: //wagon
                 rozsypsmieci( ruchome[a].x,ruchome[a].y+1,ruchome[a].z,
                               0.30, 28, 1.0, 4.0, 0.015, 0.04,
                               mat_poci_kd[0], mat_poci_kd[1], mat_poci_kd[2], 1, 1);
               break;
               case 6: //barka
                    rozsypsmieci( ruchome[a].x,ruchome[a].y+1,ruchome[a].z,
                                  0.36, 25, 1.5, 5.0, 0.015, 0.04,
                                  mat_barka_kd[0], mat_barka_kd[1], mat_barka_kd[2], 1, 1);
               break;

            }

            ruchome[a].jest=0;
            if (ruchome[a].ktorykanal>=0)
               FSOUND_StopSound( ruchome[a].ktorykanal );
         } else {

             switch (ruchome[a].rodzaj) {
               case 3: //lokomotywa dymi
                 //if (random(2)==0)
                  float dd, dp, dk;
                  if (ruchome[a].dx>0) dd= 1.43;
                                  else dd=-1.43;
                  nowywyb( ruchome[a].x+dd,
                           ruchome[a].y+1.4,
                           ruchome[a].z,

                           rand()%50/4000.0-0.00625+ustawienia.kierwiatrx,
                           rand()%100/7000.0+0.007,
                           rand()%50/4000.0-0.00625+ustawienia.kierwiatrz,

                           rand()%50/800.0+0.013,
                           rand()%50/1000.0+0.007,
                           rand()%100/400.0+0.35,

                           0.1,0.1,0.1,
                           1, 1.0, 0, 0.1


                           );

                  if (ruchome[a].dx>0) dd= 1.03;
                                  else dd=-1.03;

                  dp=(random(2)*2-1);
                  dk=0.65+random(100)/500.0;
                  nowywyb( ruchome[a].x+dd,
                           ruchome[a].y+0.2,
                           ruchome[a].z+dp*0.6,

                           0.0125-random(25)/1000.0+ruchome[a].dx*(0.5+random(100)/500.0),
                           0.0,
                           dp*random(30)/1000.0,

                           0.03, 0.016, 0.32,
                           dk,dk,dk, 1,0.9,
                           -0.00035, 0.1 );

                  if (random(60)==0) {
                      zagrajdzwiek(8,ruchome[a].x, ruchome[a].y, ruchome[a].z, 15000, false);

                      if (ruchome[a].dx>0) dd= 1.03;
                                      else dd=-1.03;
                      for (int k=0; k<=9; k++) {
                          nowywyb( ruchome[a].x+dd,
                                   ruchome[a].y+1.4,
                                   ruchome[a].z,

                                   rand()%50/4000.0-0.00625,
                                   rand()%100/4000.0+0.004+k*0.01,
                                   rand()%50/4000.0-0.00625,

                                   0.02, 0.032, 0.26,
                                   0.7,0.7,0.7, 1,0.3,
                                   -0.00035, 0.1

                                   );
                      }

                  }

               break;

               case 6://barka:
               {
                 int s;
                 float sila;

                 if (ruchome[a].dz>0) s=-3; else s=3;
                 if ( ((int)px>=0 && (int)px<=maxszer-1 &&
                       (int)pz>=s && (int)pz<=maxdlug-1-s &&
                       teren[(int)px][(int)pz+s].obiekt>0 ||
                       teren[(int)px][(int)pz+s].y>-0.3)
                 ) {
                    ruchome[a].dz*=0.93;
                 }

                 if (random(450-ustawienia.poziomtrudnosci*40)==0) {
                    sila=0.3+ustawienia.poziomtrudnosci/10.0;
                    strzel(ruchome[a].x + sin(ruchome[a].obiektpatrzyobr* PI180) * 1.7 ,
                           ruchome[a].y+1 + sin(ruchome[a].obiektpatrzypion * PI180)*0.7 ,
                           ruchome[a].z + cos(ruchome[a].obiektpatrzyobr* PI180) * 1.7 ,
                           sin(ruchome[a].obiektpatrzyobr * PI180) * sila,
                           sin(ruchome[a].obiektpatrzypion* PI180) * sila,
                           cos(ruchome[a].obiektpatrzyobr * PI180) * sila,
                           1, 0);
                 }

                    int k = (-jaki_to_kat(ruchome[a].x-samolot[sterowanie].x, ruchome[a].z-samolot[sterowanie].z)+360)%360;

                    if (k!=ruchome[a].obiektpatrzyobr) {
                       int k1 = (ruchome[a].obiektpatrzyobr - k + 360) %360;
                       if (k1<=180) {
                          ruchome[a].obiektpatrzyobr-=2;
                          int nk1 = (ruchome[a].obiektpatrzyobr - k + 360) %360;
                          if (nk1>180) ruchome[a].obiektpatrzyobr=k;
                       } else {
                       if (k1>180)
                          ruchome[a].obiektpatrzyobr+=2;
                          int nk1 = (ruchome[a].obiektpatrzyobr - k + 360) %360;
                          if (nk1<=180) ruchome[a].obiektpatrzyobr=k;
                       }
                    }

                    if (ruchome[a].obiektpatrzyobr>=360) ruchome[a].obiektpatrzyobr-=360;
                    else if (ruchome[a].obiektpatrzyobr<0) ruchome[a].obiektpatrzyobr+=360;

                    k = 90-jaki_to_kat( sqrt( pow(ruchome[a].x-samolot[sterowanie].x,2) + pow(ruchome[a].z-samolot[sterowanie].z, 2)),
                                     ruchome[a].y-samolot[sterowanie].y);
                    if (k<0) k=0;
                    if (k>60) k=60;

                    if (ruchome[a].obiektpatrzypion<k) {
                       ruchome[a].obiektpatrzypion+=2;
                       if (ruchome[a].obiektpatrzypion>k) ruchome[a].obiektpatrzypion=k;
                    } else
                    if (ruchome[a].obiektpatrzypion>k) {
                       ruchome[a].obiektpatrzypion-=2;
                       if (ruchome[a].obiektpatrzypion<k) ruchome[a].obiektpatrzypion=k;
                    }



               }
               break;
             }

           if ((ruchome[a].z>abs(ilewidac_od)*dkrok) ||
               (ruchome[a].dz<0 && ruchome[a].z<-ilewidac_do*dkrok-10) ||
               (ruchome[a].dx>0 && ruchome[a].x>maxszer/1.9*dkrok) ||
               (ruchome[a].dx<0 && ruchome[a].x<-maxszer/1.9*dkrok)) {
               ruchome[a].jest=0;
               if (ruchome[a].ktorykanal>=0)
                  FSOUND_StopSound( ruchome[a].ktorykanal );
           }
         }

		} else
        if (gracz.jaki_cel_pokazuje==1 && gracz.ktory_cel_pokazuje==a) {
           gracz.jaki_cel_pokazuje=-1;
        }
}

//---------------------------------------------------------------------------
void dzialanie_gracza()
{
	if (gracz.corobi==0 || samolot[0].ileuszkodzen>=4 || szybkosc<=0 || gracz.fuel<=0) {
      if (!FSOUND_GetPaused(kanaly[0])) FSOUND_SetPaused(kanaly[0], true);
   } else
      FSOUND_SetPaused(kanaly[0], false);

	switch (gracz.corobi)
	{
		case 0: //stoi na lotnisku
			if (kln['A']==1 && gracz.fuel>0) {
				gracz.corobi=1;
         }

         gracz.jest_lotnisko=false;
         if (gracz.fuel<300) {
            gracz.fuel++;
         } else
         if (gracz.bomb<30) {
            if (oo%2==0) gracz.bomb++;
         } else
         if (samolot[sterowanie].ileuszkodzen>0 && (oo%24==0)) {
            for (int u=0; u<=3; u++)
                if (samolot[sterowanie].uszkodzenia[u]==1) {
                   samolot[sterowanie].uszkodzenia[u]=0;
                   samolot[sterowanie].ileuszkodzen--;
                   u=4;
                   ekran.odswiezuszkodzenia=1;
                }
         }
		break;
		case 1: //startuje
		if ((szybkosc>0) && (kln['Z']==1))
		{
			szybkosc-=0.002;
			if (szybkosc<0) {
				szybkosc=0;
				gracz.corobi=0;
			}
		} else {
          if (szybkosc<maxszyb)
          {
             szybkosc+=0.0012; /*0.0017;*/
/*             if (szybkosc>maxszyb) {
                //szybkosc=maxszyb;
                //gracz.corobi=2;
             }*/
          } else if (!gracz.nad_lotniskiem) gracz.corobi=2;
      }

      szybkoscg=szybkosc;

		break;
		case 2: //leci
        szybkosc-=samolot[sterowanie].dy/250.0;
          if (kln['A']==1 && gracz.fuel>0)
          {
             //samolot[sterowanie].dz-=0.005;
             if (szybkoscg<0.30-samolot[sterowanie].ileuszkodzen*0.03)
             szybkoscg+=0.0010;
          } else
          if (kln['Z']==1)
          {
             //samolot[sterowanie].dz+=0.005;
             if (szybkoscg>0)
             szybkoscg-=0.0010;
          }

          if (szybkoscg>0.30-samolot[sterowanie].ileuszkodzen*0.03)
             szybkoscg-=0.0002;

          if (szybkosc>szybkoscg) szybkosc-=0.0008;
          else if (szybkosc<szybkoscg && gracz.fuel>0) szybkosc+=0.0004;

		break;
		case 3: //staje, zwalnia, ginie...
		if (szybkosc>0)
		{
			szybkosc-=0.002;
			if (szybkosc<0) {
				szybkosc=0;
				//gracz.corobi=2;
			}

         if (szybkosc>0.06)
         nowywyb(samolot[sterowanie].x+0.2*(random(2)*2-1),
                 samolot[sterowanie].y-0.4,
                 samolot[sterowanie].z,
                 0.0125-random(25)/1000.0, 0.0, random(20)/1000.0,
                 0.02, 0.01, 0.25,
                 0.50,0.50,0.50, 1,0.3,
                 -0.0005 );

		} else
			if (samolot[sterowanie].zniszczony==0 && samolot[sterowanie].jest==1 &&
             samolot[sterowanie].ileuszkodzen<=3) {
             gracz.corobi=0;
             //FSOUND_SetPaused(kanaly[0], false);
         }
		break;
	}

   if (gracz.fuel<=0 && szybkosc>0) szybkosc-=0.0006;

   if (!FSOUND_GetPaused(kanaly[0])) {
      FSOUND_SetFrequency(kanaly[0], (int) (7000+szybkoscc*120400));
      FSOUND_SetVolume(kanaly[0], (int) (100+szybkoscc*200));

      if (samolot[sterowanie].ileuszkodzen>=4) {
         //FSOUND_SetPaused(kanaly[0], true);
      }

   }
}

//---------------------------------------------------------------------------
void dzialaj_obiekty_scenerii()
{
	float x,z,px,pz, sila;
   bool lotniskowidoczne=false;

   if (gracz.jaki_cel_pokazuje==2 && gracz.gdziez_cel_pokazuje<zod) {
      gracz.jaki_cel_pokazuje=-1;
   }

   swiatlolotniska.juzniema=true;
	for (x=1; x<maxszer-1;x++)
		for (z=zod;z<zdo; z++) {

        if (z==zdo-1 && teren[(int)x][(int)z].obiektcel && gracz.jaki_cel_pokazuje==-1) {
           gracz.jaki_cel_pokazuje=2;
           gracz.gdziex_cel_pokazuje=x;
           gracz.gdziez_cel_pokazuje=z;
        }

        //zniszcz obiekty:
        if (teren[(int)x][(int)z].obiektzniszcz==1) {
 //          int ob=teren[(int)x][(int)z].obiekt;
                px=x*dkrok-dx0;
                pz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);

           teren[(int)x][(int)z].obiektzniszcz=0;
           if (gracz.jaki_cel_pokazuje==2 && (int)z==gracz.gdziez_cel_pokazuje && (int)x==gracz.gdziex_cel_pokazuje) {
              gracz.jaki_cel_pokazuje=-1;
           }

           switch (teren[(int)x][(int)z].obiekt) {
              case ob_czolgi:
                    teren[(int)x][(int)z].obiekt=ob_ogien;
                    teren[(int)x][(int)z].obiektktoreprzejscie=1;
                    caly_wybuch(px, teren[(int)x][(int)z].obiekty, pz, 5, 0 );
                    rozsypsmieci( px,teren[(int)x][(int)z].obiekty+0.2, pz,
                                  0.30, 18, 1.0, 4.0, 0.015, 0.04,
                                  mat_czolg_kd[0], mat_czolg_kd[1], mat_czolg_kd[2], 1, 1);
              break;
              case ob_dziala:
                    teren[(int)x][(int)z].obiekt=ob_ogien;
                    teren[(int)x][(int)z].obiektktoreprzejscie=1;
                    caly_wybuch(px, teren[(int)x][(int)z].obiekty, pz, 5, 0 );
                    rozsypsmieci( px,teren[(int)x][(int)z].obiekty+0.2, pz,
                                  0.30, 18, 1.0, 4.0, 0.015, 0.04,
                                  mat_dzialo_kd[0], mat_dzialo_kd[1], mat_dzialo_kd[2], 1, 1);
              break;
              case ob_barki:
                    teren[(int)x][(int)z].obiekt=ob_ogien;
                    teren[(int)x][(int)z].obiektktoreprzejscie=1;
                    teren[(int)x][(int)z].obiektrozm=2;
                    caly_wybuch(px, teren[(int)x][(int)z].obiekty, pz, 8, 1 );
                    rozsypsmieci( px,teren[(int)x][(int)z].obiekty+0.2, pz,
                                  0.36, 25, 1.5, 5.0, 0.015, 0.04,
                                  mat_barka_kd[0], mat_barka_kd[1], mat_barka_kd[2], 1, 1);
              break;
              case ob_drzewa:
              case ob_drzewa+1:
                    teren[(int)x][(int)z].obiekt=ob_ogien;
                    teren[(int)x][(int)z].obiektktoreprzejscie=1;
                    caly_wybuch(px, teren[(int)x][(int)z].obiekty, pz, 3, 0 );
                    rozsypsmieci( px,teren[(int)x][(int)z].obiekty+0.2, pz,
                                  0.26, 7, 1.0, 1.5, 0.010, 0.02,
                                  0.30, 0.13, 0.0, 1, 1);
              break;
              case ob_budynki:
              case ob_budynki+1:
              case ob_budynki+2:
              case ob_budynki+3:
              case ob_budynki+4:
              case ob_hangar:
              case ob_hangar+1:
              case ob_hangar+2:
                    teren[(int)x][(int)z].obiekt=ob_ogien;
                    teren[(int)x][(int)z].obiektktoreprzejscie=1;
                    teren[(int)x][(int)z].obiektrozm=2;
                    caly_wybuch(px, teren[(int)x][(int)z].obiekty, pz, 9, 1 );
                    rozsypsmieci( px,teren[(int)x][(int)z].obiekty+0.2, pz,
                                  0.34, 30, 1.5, 6.0 );
              break;
              case ob_mosty:
              case ob_mosty+1:
                    teren[(int)x][(int)z].obiekt=0;
                    caly_wybuch(px, teren[(int)x][(int)z].obiekty, pz, 19, 1 );
                    rozsypsmieci( px,teren[(int)x][(int)z].obiekty+0.2, pz,
                                  0.36, 40, 1.5, 7.0, 0.012, 0.03,
                                  0.16, 0.2, 0.16, 0, 1);
              break;
              case ob_lampy:
                    teren[(int)x][(int)z].obiekt=ob_ogien;
                    teren[(int)x][(int)z].obiektktoreprzejscie=1;
                    caly_wybuch(px, teren[(int)x][(int)z].obiekty, pz, 1, 0 );
                    rozsypsmieci( px,teren[(int)x][(int)z].obiekty+0.4, pz,
                                  0.17, 3, 0.6, 1.5, 0.012, 0.03,
                                  mat_poci_kd[0], mat_poci_kd[1], mat_poci_kd[2], 0.0, 0, 1);
              break;
              default:
                    teren[(int)x][(int)z].obiekt=0;
              break;
           }//switch
        } else if (teren[(int)x][(int)z].obiektzniszcz>0) { //odliczanie do wybuchu
          teren[(int)x][(int)z].obiektzniszcz--;
        } else  //nie zniszczony
         //strzelanie czolgow i barek
         switch (teren[(int)x][(int)z].obiekt) {
           case ob_czolgi:
           case ob_barki:
           case ob_dziala:
             if (random(600-ustawienia.poziomtrudnosci*40-teren[(int)x][(int)z].obiektcelujewgracza*150)==0) {
                sila=0.3+ustawienia.poziomtrudnosci/7.0;
                px=x*dkrok-dx0;
                pz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);
                strzel(px + sin(teren[(int)x][(int)z].obiektpatrzyobr* PI180) * 1.7 ,
                       teren[(int)x][(int)z].obiekty+1 + sin(teren[(int)x][(int)z].obiektpatrzypion * PI180)*0.7 ,
                       pz + cos(teren[(int)x][(int)z].obiektpatrzyobr* PI180) * 1.7 ,
                       sin(teren[(int)x][(int)z].obiektpatrzyobr * PI180) * sila,
                       sin(teren[(int)x][(int)z].obiektpatrzypion* PI180) * sila,
                       cos(teren[(int)x][(int)z].obiektpatrzyobr * PI180) * sila,
                       1, 0);
                //FSOUND_PlaySound(FSOUND_FREE, dzwiek[6]);
                zagrajdzwiek(6,px,teren[(int)x][(int)z].obiekty+1,pz, 5000, false);

             }
             px=x*dkrok-dx0;
             pz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);
             if (teren[(int)x][(int)z].obiektcelujewgracza) {
                int k = (-jaki_to_kat(px-samolot[sterowanie].x, pz-samolot[sterowanie].z)+360)%360;

                if (k!=teren[(int)x][(int)z].obiektpatrzyobr) {
                   int k1 = (teren[(int)x][(int)z].obiektpatrzyobr - k + 360) %360;
                   if (k1<=180) {
                      teren[(int)x][(int)z].obiektpatrzyobr-=2;
                      int nk1 = (teren[(int)x][(int)z].obiektpatrzyobr - k + 360) %360;
                      if (nk1>180) teren[(int)x][(int)z].obiektpatrzyobr=k;
                   } else {
                   if (k1>180)
                      teren[(int)x][(int)z].obiektpatrzyobr+=2;
                      int nk1 = (teren[(int)x][(int)z].obiektpatrzyobr - k + 360) %360;
                      if (nk1<=180) teren[(int)x][(int)z].obiektpatrzyobr=k;
                   }
                }

                if (teren[(int)x][(int)z].obiektpatrzyobr>=360) teren[(int)x][(int)z].obiektpatrzyobr-=360;
                else if (teren[(int)x][(int)z].obiektpatrzyobr<0) teren[(int)x][(int)z].obiektpatrzyobr+=360;

                k = 90-jaki_to_kat( sqrt( pow(px-samolot[sterowanie].x,2) + pow(pz-samolot[sterowanie].z, 2)),
                                 teren[(int)x][(int)z].obiekty-samolot[sterowanie].y);
                if (k<0) k=0;
                if (k>70) k=70;

                if (teren[(int)x][(int)z].obiektpatrzypion<k) {
                   teren[(int)x][(int)z].obiektpatrzypion+=2;
                   if (teren[(int)x][(int)z].obiektpatrzypion>k) teren[(int)x][(int)z].obiektpatrzypion=k;
                } else
                if (teren[(int)x][(int)z].obiektpatrzypion>k) {
                   teren[(int)x][(int)z].obiektpatrzypion-=2;
                   if (teren[(int)x][(int)z].obiektpatrzypion<k) teren[(int)x][(int)z].obiektpatrzypion=k;
                }

             } else
               if (random(700-ustawienia.poziomtrudnosci*160)==0) teren[(int)x][(int)z].obiektcelujewgracza=true;

             if (teren[(int)x][(int)z].obiekt==ob_barki) {
                teren[(int)x][(int)z].obiekty=sin((int)z+oo/20.0)*0.1;
                //BMForm->Label6->Caption="z="+IntToStr((int)(z))+" zod="+IntToStr((int)(zod));
             }

           break;
           case ob_ogien: //dymienie i ogien
              if ( ((teren[(int)x][(int)z].obiektrozm<=1.4) && (random(2)==0)) ||
                   (teren[(int)x][(int)z].obiektrozm>1.4)) {

                  float j=0.2+(rand()%30)/150.0-0.1;
                  float ox=x*dkrok-dx0;
                  float oz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);
                  int ile=1;
                  if (teren[(int)x][(int)z].obiektrozm>2) ile=teren[(int)x][(int)z].obiektrozm;

                  for (int n=0; n<=ile; n++)
                      nowywyb( ox+(-1.0+random(200)/100.0)*teren[(int)x][(int)z].obiektrozm,
                           teren[(int)x][(int)z].obiekty,
                           oz+(-1.0+random(200)/100.0)*teren[(int)x][(int)z].obiektrozm,
                           rand()%50/1000.0-0.025,
                           rand()%60/1000.0+0.04,
                           rand()%50/1000.0-0.025,

                           rand()%50/500.0+0.02,
                           rand()%50/500.0+0.02,
                           rand()%100/400.0+ile,
                           1,1,1,2, 1,0,0.15*teren[(int)x][(int)z].obiekty
                           );

                  for (int n=1; n<=ile; n++)
                    nowywyb( ox,
                           teren[(int)x][(int)z].obiekty+0.3,
                           oz,

                           rand()%100/2000.0-0.025+ustawienia.kierwiatrx,
                           rand()%100/900.0+0.05,
                           rand()%100/2000.0-0.025+ustawienia.kierwiatrz,

                           rand()%50/800.0+0.01,
                           rand()%50/500.0+0.01,
                           (rand()%100/150.0+0.5)*(float)teren[(int)x][(int)z].obiektrozm,

                           j,j,j, 1
                           );
              }

             teren[(int)x][(int)z].obiektrozm-=random(50)/10000.0;
             if (teren[(int)x][(int)z].obiektrozm<=0.02) teren[(int)x][(int)z].obiekt=0;

             teren[(int)x][(int)z].obiektobr+=30;//10+random(30);
//             if (rand()%300==0) teren[(int)x][(int)z].obiekt=0;
           break;
           case ob_hangar+3:
              if (ustawienia.jasnoscswiatla<0.75) {
                 if (teren[(int)x-2][(int)z+3].obiekt==ob_lampy ||
                     teren[(int)x-3][(int)z+3].obiekt==ob_lampy ||
                     teren[(int)x-4][(int)z+3].obiekt==ob_lampy) {
                      swiatlolotniska.juzniema=false;
                      swiatlolotniska.jest=true;
                      swiatlolotniska.x=x*dkrok-dx0;
                      swiatlolotniska.z=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);
                      swiatlolotniska.y = gdzie_y(swiatlolotniska.x,swiatlolotniska.z)+20;
                      lotniskowidoczne=true;
                  }
              }
           break;
         }//switch

      }

   if (swiatlolotniska.juzniema && swiatlolotniska.z<100) {
      swiatlolotniska.jest=true;
      swiatlolotniska.z=swiatlolotniska.z+szybkoscc;
      if (swiatlolotniska.z>=120)
         swiatlolotniska.jest=false;
   }

   if (gracz.jest_lotnisko &&
       (int)zdo>gracz.ostrzezenie_o_lotnisku+ile_wczesniej_informowac_o_lotnisku &&
       !lotniskowidoczne) gracz.jest_lotnisko=false;

//   BMForm->Label6->Caption = BoolToStr(gracz.jest_lotnisko, true);
//   BMForm->Label7->Caption = IntToStr((int)zdo)+", "+IntToStr(gracz.ostrzezenie_o_lotnisku+ile_wczesniej_informowac_o_lotnisku);
}

//---------------------------------------------------------------------------
void sterowanie_graczem()
{
		if ((kl[klgora]==1)
          && (samolot[sterowanie].ileuszkodzen<4))
		{
			samolot[sterowanie].dy+=0.04;
			if (samolot[sterowanie].lotkidy<1.0) samolot[sterowanie].lotkidy+=0.2;
		} else
		if (kl[kldol]==1)
		{
			samolot[sterowanie].dy-=0.04;
			if (samolot[sterowanie].lotkidy>-1.0) samolot[sterowanie].lotkidy-=0.2;
		} else
		{
         float ddy;
         if (ustawienia.grawitacja) ddy=-0.01; else ddy=0;

			if (samolot[sterowanie].dy>ddy) {
				samolot[sterowanie].dy-=0.005;
				if (samolot[sterowanie].dy<ddy) samolot[sterowanie].dy=ddy;
			} else
			if (samolot[sterowanie].dy<ddy) {
				samolot[sterowanie].dy+=0.005;
				if (samolot[sterowanie].dy>0) samolot[sterowanie].dy=ddy;
			}

			if (samolot[sterowanie].lotkidy<0.0) {
				samolot[sterowanie].lotkidy+=0.2;
				if (samolot[sterowanie].lotkidy>0.0) samolot[sterowanie].lotkidy=0;
			} else
			if (samolot[sterowanie].lotkidy>0.0) {
				samolot[sterowanie].lotkidy-=0.2;
				if (samolot[sterowanie].lotkidy<0.0) samolot[sterowanie].lotkidy=0;
			}

		}

		if ((szybkosc>=0.12) && (samolot[sterowanie].y>gdzie_y(samolot[sterowanie].x,samolot[sterowanie].z)+samolot_nad_ziemia+0.1))
		{
        if (kl[VK_LEFT]==1)
        {
           samolot[sterowanie].dx-=0.05;
           if (samolot[sterowanie].lotkidx<1.0) samolot[sterowanie].lotkidx+=0.2;
        } else
        if (kl[VK_RIGHT]==1)
        {
           samolot[sterowanie].dx+=0.05;
           if (samolot[sterowanie].lotkidx>-1.0) samolot[sterowanie].lotkidx-=0.2;
        } else
        {
           if (samolot[sterowanie].dx>0) {
              samolot[sterowanie].dx-=0.05;
              if (samolot[sterowanie].dx<0) samolot[sterowanie].dx=0;
           }
           if (samolot[sterowanie].dx<0) {
              samolot[sterowanie].dx+=0.05;
              if (samolot[sterowanie].dx>0) samolot[sterowanie].dx=0;
           }

           if (samolot[sterowanie].lotkidx<0.0) {
              samolot[sterowanie].lotkidx+=0.1;
              if (samolot[sterowanie].lotkidx>0.0) samolot[sterowanie].lotkidx=0;
           } else
           if (samolot[sterowanie].lotkidx>0.0) {
              samolot[sterowanie].lotkidx-=0.1;
              if (samolot[sterowanie].lotkidx<0.0) samolot[sterowanie].lotkidx=0;
           }
        }
      }

      if (szybkosc>=maxszyb) {
          if (kln['A']==1)
          {
             //samolot[sterowanie].dz-=0.005;
             //szybkosc+=0.002;
          } else
          if (kln['Z']==1)
          {
             //samolot[sterowanie].dz+=0.005;
             //szybkosc-=0.002;
          } else if ((kl[klgora]==0) && (kl[kldol]==0))
          {
             if (samolot[sterowanie].dz>0) {
                samolot[sterowanie].dz-=0.05;
                if (samolot[sterowanie].dz<0) samolot[sterowanie].dz=0;
             }
             if (samolot[sterowanie].dz<0) {
                samolot[sterowanie].dz+=0.05;
                if (samolot[sterowanie].dz>0) samolot[sterowanie].dz=0;
             }
          }
      }

		if (kl[' ']==1)
		{
			if (samolot[sterowanie].dzialotemp<=0)
			{
            if ((samolot[sterowanie].uszkodzenia[3]==0) || (rand()%20>18))
            {
                samolot[sterowanie].strzel=true;
            }
			}

		}
		if (kl['B']==1)
		{
			if ((samolot[sterowanie].bombytemp<=0) && (gracz.bomb>0))
			{
            if ((samolot[sterowanie].uszkodzenia[1]==0) || (rand()%40>38))
            {
               samolot[sterowanie].spuscbombe=true;
               gracz.bomb--;
            }
			}

		}

		if (szybkosc<0.19)
		{
			float sy;
			sy=gdzie_y(samolot[sterowanie].x,samolot[sterowanie].z)+samolot_nad_ziemia;
			if (samolot[sterowanie].y > sy+0.05)
			{
				//samolot[sterowanie].dy-=0.5*(0.30-szybkosc*2.0);
				samolot[sterowanie].dy-=0.3*(0.40-szybkosc*2.0);
			}

		}

      if (szybkosc>=0.002) {
        gracz.fuel -= szybkosc*0.20; //0.03;
      }
      if (samolot[sterowanie].uszkodzenia[0]==1) gracz.fuel -= 0.07*(rand()%100/100.0);
      if (gracz.fuel<0) gracz.fuel=0;

      if (samolot[sterowanie].zniszczony==1 && samolot[sterowanie].dz>0)
         samolot[sterowanie].dz = 0;

}

//---------------------------------------------------------------------------
//tworzy w losowym miejscu nowy samolot
void nowy_samolot()
{
	int a,b=-1;
	int skad;

	for (a=1; a<=ils; a++) // 0 = sterowanie
		if (samolot[a].jest==0)
		{
			b=a;
			break;
		}

	if ((b>=0) && (b<=ils))
	{

		skad=rand()%2;

		samolot[b].rodzaj=0;

		switch (skad)
		{
			case 0: //z przodu
			samolot[b].x=rand()%30-15;
			samolot[b].z=-ilewidac_do*dkrok;
			samolot[b].y=gdzie_y(samolot[b].x,samolot[b].z)+5+random(10);
			samolot[b].dx=0;
			samolot[b].dy=0;
			samolot[b].dz=0.4;
			break;
			case 1: //z tylu
			samolot[b].x=rand()%30-15;
			samolot[b].z=-ilewidac_od*dkrok;
			samolot[b].y=gdzie_y(samolot[b].x,samolot[b].z)+5+random(10);
			samolot[b].dx=0;
			samolot[b].dy=0;
			samolot[b].dz=-0.4;
			break;
		}

    	samolot[b].do_dx=0;
    	samolot[b].do_dy=0;

      samolot[b].uszkodzenia[0]=0;
      samolot[b].uszkodzenia[1]=0;
      samolot[b].uszkodzenia[2]=0;
      samolot[b].uszkodzenia[3]=0;
      samolot[b].ileuszkodzen=0;

		samolot[b].rozm=1;
		samolot[b].smiglo=0;
		samolot[b].dzialotemp=0;
		samolot[b].jest=1;
		samolot[b].zniszczony=0;

		samolot[b].strzalani=0;

    	samolot[b].szalikn=0;
		samolot[b].spuscbombe=false;
		samolot[b].strzel=false;

      samolot[b].x_=samolot[b].x;
      samolot[b].y_=samolot[b].y;
      samolot[b].z_=samolot[b].z;

      if (random(12)==0) samolot[b].cel=true;
		   else samolot[b].cel=false;

//         samolot[b].cel=true; //////////////////////////////rrrrrrrrrrrrrrrrrrrrrrr

      if (samolot[b].cel && gracz.jaki_cel_pokazuje==-1) {
         gracz.jaki_cel_pokazuje=0;
         gracz.ktory_cel_pokazuje=b;
      }
	}

}

//---------------------------------------------------------------------------
void uszkodz_samolot(int a, bool namaxa=false)
{
 if (a!=sterowanie || random(2)==0 || namaxa) {
    if (samolot[a].ileuszkodzen<=3) {
       int n;

       if (!namaxa) {
           do {
              n=rand()%4;
           } while (samolot[a].uszkodzenia[n]==1);

           samolot[a].uszkodzenia[n]=1;
           samolot[a].ileuszkodzen++;
       } else {
           for (n=0; n<=3; n++)
               samolot[a].uszkodzenia[n]=1;
           samolot[a].ileuszkodzen=4;
       }

       if ((a==sterowanie) && (gracz.corobi!=2)) { //zabij gracza calkiem jesli nie leci normalnie tylko np. stoi na lotnisku
          for (int c=0; c<=3; c++)
              samolot[a].uszkodzenia[c]=1;
          samolot[a].ileuszkodzen=4;
       }

       if (samolot[a].ileuszkodzen>=4) {
          caly_wybuch(samolot[a].x,samolot[a].y,samolot[a].z,5,1);
       }
       if (a==sterowanie) {
          ekran.odswiezuszkodzenia=1;
          if (samolot[a].ileuszkodzen>=4)
             kamera=5;
             kameraczas=1;
       }
    }
 }

// zagrajdzwiek(1+random(3),samolot[a].x,samolot[a].y,samolot[a].z, 0, false);
 zagrajdzwiek(12,samolot[a].x,samolot[a].y,samolot[a].z, 15000, false);

}

//---------------------------------------------------------------------------
void ruch_samolotow()
{
   float maxpredkier[2][3] = {0.6,0.4,0.5,
                              0.23,0.14,0.2};

	int a;

   gracz.na_poziomie_samolotu=false;
	//----------------ruch samolotow-------------------
	for (a=0; a<ils; a++)
		if (samolot[a].jest==1)
		{

      if (!FSOUND_IsPlaying(kanaly[a]) && samolot[a].ileuszkodzen<4)
      {
          kanaly[a] = FSOUND_PlaySound(FSOUND_FREE, dzwiek[4]);
          FSOUND_SetPaused(kanaly[a], false);
      }

      if (a>0 && FSOUND_GetPaused(kanaly[a])) FSOUND_SetPaused(kanaly[a], false);

      if (a>0)
      {
        FSOUND_SetFrequency(kanaly[a], (int) (50000+samolot[a].dz*10000 - fabs(samolot[0].z-samolot[a].z)*700 ));
        FSOUND_SetVolume(kanaly[a], (int) 230/*(230.0-fabs(samolot[a].z - samolot[0].z)*6.0)*/);

         int o;
         float o2 = pow(samolot[0].x-samolot[a].x,2)+pow(samolot[0].y-samolot[a].y,2)+pow(samolot[0].z-samolot[a].z,2);
         if (o2==0) o2=0.01;
         o = (int)(255.0 - floor(sqrt( o2*23.0 ) ));

         if (o<0) o = 0;
         if (o>255) o = 255;

         int o_;
         float o2_ = pow(samolot[0].x_-samolot[a].x_,2)+pow(samolot[0].y_-samolot[a].y_,2)+pow(samolot[0].z_-samolot[a].z_,2);
         if (o2_==0) o2_=0.01;
         o_ = (int)(255.0 - floor(sqrt( o2_*23.0 ) ));

         if (o_<0) o_ = 0;
         if (o_>255) o_ = 255;

         FSOUND_SetFrequency(kanaly[a], (int) (50000 + (o-o_)*3000 ) );
         FSOUND_SetVolume(kanaly[a], (int) o);

         o=128+(samolot[a].x-samolot[0].x)*10;
         if (o<0) o = 0;
         if (o>255) o = 255;
         FSOUND_SetPan(kanaly[a], (int) o);

      }

      samolot[a].x_=samolot[a].x;
      samolot[a].y_=samolot[a].y;
      samolot[a].z_=samolot[a].z;

      if (samolot[a].strzalani>0) samolot[a].strzalani--;

      if (samolot[a].zniszczony==0) {

          if (samolot[a].strzel) {
                float sy,dy=0;
                sy=(float)samolot[a].y - (float)gdzie_y(samolot[a].x,samolot[a].y);

                if ((sy<=7.0) && (sy>=2.6)) dy=-0.35;//-0.1*sy;

                float ddz;
                if (a==sterowanie) ddz=-2.5;
                else
                    if (samolot[a].dz<0) ddz=-1.0-ustawienia.poziomtrudnosci*0.5;
                                    else ddz=1.0+ustawienia.poziomtrudnosci*0.5;
                strzel(	samolot[a].x-0.10+samolot[a].dx*0.5,
                        samolot[a].y+0.21+samolot[a].dy*0.4,
                        samolot[a].z-1.5,
                        samolot[a].dx,
                        samolot[a].dy+dy,
                        samolot[a].dz+ddz,
                        a,0);
                strzel(	samolot[a].x+0.10+samolot[a].dx*0.5,
                        samolot[a].y+0.21+samolot[a].dy*0.4,
                        samolot[a].z-1.5,
                        samolot[a].dx,
                        samolot[a].dy+dy,
                        samolot[a].dz+ddz,
                        a,0);
                if (a!=sterowanie) samolot[a].dzialotemp=50-ustawienia.poziomtrudnosci*10;
                   else samolot[a].dzialotemp=3;

                //FSOUND_PlaySound(FSOUND_FREE, dzwiek[0]);
                zagrajdzwiek(0,samolot[a].x,samolot[a].y,samolot[a].z, 0, false);

                samolot[a].strzel=false;
                samolot[a].strzalani=4;
          }
          if (samolot[a].spuscbombe) {
                float dy;
                if (samolot[a].dy>=0) dy=samolot[a].dy/5.0;
                   else dy=samolot[a].dy;

                strzel(	samolot[a].x,
                      samolot[a].y-0.2,
                      samolot[a].z+0.4,
                      samolot[a].dx/5.0,
                      dy,
                      samolot[a].dz/5.0,
                      a,1);
                if (a!=sterowanie) samolot[a].bombytemp=60-ustawienia.poziomtrudnosci*5;
                   else samolot[a].bombytemp=30;
                samolot[a].spuscbombe=false;
                //FSOUND_PlaySound(FSOUND_FREE, dzwiek[5]);
                zagrajdzwiek(5,samolot[a].x,samolot[a].y,samolot[a].z, 0, false);
          }

          //strzelanie komputerow
          if (a!=sterowanie) {
             if (gracz.corobi!=2 && samolot[sterowanie].jest==1 &&
                 samolot[a].bombytemp<=0 &&
                 samolot[a].x>=samolot[sterowanie].x-15 && samolot[a].x<=samolot[sterowanie].x+10 &&
                 samolot[a].z>=samolot[sterowanie].z-40 && samolot[a].z<=samolot[sterowanie].z+40
                  ) {
                samolot[a].spuscbombe=true;
             }
             if (gracz.corobi==2 &&
                 samolot[a].y>=samolot[sterowanie].y-4 && samolot[a].y<=samolot[sterowanie].y+4 &&
                 samolot[a].dzialotemp<=0) {
                samolot[a].strzel=true;
             }
          }

          if (a!=sterowanie && samolot[a].y>=samolot[sterowanie].y-0.2 && samolot[a].y<=samolot[sterowanie].y+0.2)
             gracz.na_poziomie_samolotu=true;
          //obrot smigla
          if (a!=sterowanie)
             samolot[a].smiglo=samolot[a].smiglo+70.0+samolot[a].dz*30.0;
          else {
             if (gracz.fuel>0)
                samolot[a].smiglo=samolot[a].smiglo+szybkosc*547+samolot[a].dz*30.0;
             else
                samolot[a].smiglo=samolot[a].smiglo+szybkosc*247+samolot[a].dz*30.0;
          }

          if (samolot[a].dzialotemp>0) samolot[a].dzialotemp--;
          if (samolot[a].bombytemp>0) samolot[a].bombytemp--;

          short int ms=0;
          if (samolot[a].uszkodzenia[2]==1) ms=1;

          if (samolot[a].dx>maxpredkier[ms][0]) samolot[a].dx = maxpredkier[ms][0];
          if (samolot[a].dx<-maxpredkier[ms][0]) samolot[a].dx = -maxpredkier[ms][0];
          if (samolot[a].dy>maxpredkier[ms][1]) samolot[a].dy=maxpredkier[ms][1];
          if (samolot[a].ileuszkodzen<=3)
             if (samolot[a].dy<-maxpredkier[0][1]) samolot[a].dy=-maxpredkier[0][1];

          if (a==sterowanie) {
              if (samolot[a].dz>0.02) samolot[a].dz = 0.02;
              if (samolot[a].dz<-maxpredkier[ms][2]) samolot[a].dz = -maxpredkier[ms][2];
          } else {
              if (samolot[a].dz>maxpredkier[ms][2]) samolot[a].dz = maxpredkier[ms][2];
              if (samolot[a].dz<-maxpredkier[ms][2]) samolot[a].dz = -maxpredkier[ms][2];
          }

          samolot[a].x = samolot[a].x+samolot[a].dx;
          samolot[a].y = samolot[a].y+samolot[a].dy;
          if (a!=sterowanie)
             samolot[a].z = samolot[a].z+samolot[a].dz;

          if (samolot[a].x<-dx0+2) samolot[a].x=-dx0+2;
          if (samolot[a].x>dx0-2) samolot[a].x=dx0-2;
          if (a==sterowanie) {
              if (samolot[a].z<-17*dkrok) samolot[a].z=-17*dkrok;
              if (samolot[a].z>17*dkrok) samolot[a].z=17*dkrok;
              if (samolot[a].y>22) samolot[a].y=22;
          }

          float sy,sx,sz;
          sy=gdzie_y(samolot[a].x,samolot[a].z)+samolot_nad_ziemia;
          if (a==sterowanie) {
             float nsy=sy;
             if (nsy<0) nsy=0;
             gracz.alt = samolot[a].y - nsy;
          }
          sx=samolot[a].x;
          sz=samolot[a].z;
          gdzie_xz(&sx,&sz);

          //pluski wody
          if (samolot[a].y>=-0.6 && samolot[a].y<=0.6)
             nowywyb(samolot[a].x-1+random(200)/100.0, 0, samolot[a].z-1+random(200)/100.0,
                     0.05-random(100)/1000.0+samolot[a].dx,
                     0.03+random(100)/1500.0+fabs(samolot[a].dy),
                     0.05-random(100)/1000.0+samolot[a].dz,
                     0.08, 0.014, 1.00,
                     1,1,1, 4,0.7,
                     0.011, 0.2 );


          //samolot gracza: uderzenie w ziemie / ladowanie
          if (a==sterowanie) {
             short int jestlotnisko=0;

             for (int _x=-2; _x<=2; _x++)
               for (int _z=-1; _z<=1; _z++)
                   if (teren[(int)sx+_x][(int)sz+_z].obiekt==ob_lotnisko)
                   {
                      jestlotnisko=1;
                      _x=2;
                      _z=1;
                   }

             gracz.nad_lotniskiem = jestlotnisko;
             if (szybkosc<=0.22 && fabs(samolot[sterowanie].dx)<0.10 && fabs(samolot[sterowanie].dy)<0.35)
                gracz.moze_ladowac=true;
                else gracz.moze_ladowac=false;

             if (samolot[a].y <= sy+0.5 || samolot[a].y<=0.2) //uszkadzaj od uderzenia w ziemie
             {
                 if (jestlotnisko==0) uszkodz_samolot(a);
                 else
                 if (a==sterowanie && gracz.corobi>=2) { //laduj
                    if (gracz.moze_ladowac) gracz.corobi=3;
                       else uszkodz_samolot(a);
                 }
             } else
               if (gracz.corobi==1 && szybkosc>=maxszyb && samolot[a].y>sy+1.0)
                  gracz.corobi=2;
          } else { //samoloty wroga
             if (samolot[a].y <= sy+0.5) {//uszkadzaj od uderzenia w ziemie
                uszkodz_samolot(a);
                if (samolot[a].ileuszkodzen>=4) samolot[a].cel=false;
             }
          }

          if (samolot[a].y <= sy) //odbijaj w gore od ziemi, zeby nie wpadal pod
          {
              samolot[a].dy=-fabs(samolot[a].dy*0.8);
              samolot[a].y = sy;
              if (samolot[a].ileuszkodzen>=4) {
	              if (a==sterowanie) gracz.corobi=3;
                 if ((samolot[a].dy<-0.25) || (samolot[a].dy>=-0.25 && random(40)==0)) {
                     caly_wybuch(samolot[a].x,samolot[a].y,samolot[a].z, 10, 1);
                     strzel(samolot[a].x,samolot[a].y+0.1,samolot[a].z,0,-0.2,0,2,1);
                     {
                       float klr,klg,klb;
                       if (a==sterowanie) {
                          klr=mat_sam_kd[0];
                          klg=mat_sam_kd[1];
                          klb=mat_sam_kd[2];
                       } else {
                          klr=mat_sam2_kd[0];
                          klg=mat_sam2_kd[1];
                          klb=mat_sam2_kd[2];
                       }
                       rozsypsmieci( samolot[a].x,samolot[a].y+0.1,samolot[a].z,
                                     0.30, 22, 0.8, 3.5, 0.008, 0.02,
                                     klr, klg, klb, 1, 1, 1);
                     }
                     samolot[a].zniszczony=1;
                 } else { //sunie po ziemi zaraz przed rozwaleniem sie
                    samolot[a].dx=samolot[a].dx*0.95;
                    //samolot[a].dy=samolot[a].dy*0.95;
                    samolot[a].dz=samolot[a].dz*0.95;
                    if (fabs(samolot[a].dz)>0.05 || fabs(samolot[a].dx)>0.05 || szybkosc>0.05) {
                        float j=0.03+(rand()%30)/100.0;
                        nowywyb( samolot[a].x-0.25+random(100)/200.0,
                                 samolot[a].y,
                                 samolot[a].z-0.25+random(100)/200.0,

                                 rand()%100/2000.0-0.025+ustawienia.kierwiatrx*2.0,
                                 rand()%100/800.0,
                                 rand()%100/2000.0-0.010+ustawienia.kierwiatrz*2.0,

                                 rand()%50/400.0+0.02,
                                 rand()%50/800.0+0.01,
                                 rand()%100/50.0+0.5,

                                 j,j,j, 1, 1-random(40)/100.0-szybkoscc/3.0
                                 );
                    }
                 }
              }
          }

          if (samolot[a].ileuszkodzen>=4) //wrak spada
          {
                if (samolot[a].dy>-0.8)
                   samolot[a].dy = samolot[a].dy-0.013;
          }


          if ( (ustawienia.jestwiatr==1) && (samolot[a].y>sy+1) ) {
             samolot[a].x = samolot[a].x+ustawienia.kierwiatrx;
             if (a!=sterowanie)
                samolot[a].z = samolot[a].z+ustawienia.kierwiatrz;
               //dla gracza kierwiatrz jest w przesunieciu "szybkosc"
          }


          if ((a!=sterowanie) && (samolot[a].ileuszkodzen<4)) //losowy ruch komputerow
          {
             if (rand()%50==0)
                samolot[a].do_dx=rand()%100/100.0-0.5;

             if (samolot[a].dx>samolot[a].do_dx)
             {
                samolot[a].dx -= 0.03;
             } else
             if (samolot[a].dx<samolot[a].do_dx)
             {
                samolot[a].dx += 0.03;
             }

             if (rand()%50==0)
                samolot[a].do_dy=rand()%100/400.0-0.125;

             if (samolot[a].dy>samolot[a].do_dy)
             {
                samolot[a].dy -= 0.02;
             } else
             if (samolot[a].dy<samolot[a].do_dy)
             {
                samolot[a].dy += 0.02;
             }

             if (samolot[a].y>20) samolot[a].do_dy=0;
             if (samolot[a].y<gdzie_y(samolot[a].x, samolot[a].z)+4) {
                samolot[a].do_dy=0.4;
                if (samolot[a].dy<=0) samolot[a].dy=0.01;
             }

          }

          //kolizje samolotow z obiektami scenerii
             {
                int x,z, ob;
                float px,pz, _dx,_dy,_dz,c;
                for (x=1; x<maxszer-1;x++)
                   for (z=zod;z<zdo; z++) {
                      ob=teren[(int)x][(int)z].obiekt;
                      if (ob>=1)
                      {
                         px=x*dkrok-dx0;
                         pz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);

                         _dx=fabs(samolot[a].x-px);
                         _dy=fabs(samolot[a].y-teren[(int)x][(int)z].obiekty);
                         _dz=fabs(samolot[a].z-pz);
                         c=sqrt(_dx*_dx + _dy*_dy + _dz*_dz);
                         if (c<=obiektyrozm[ob]*teren[(int)x][(int)z].obiektrozm)
                         {
                            uszkodz_samolot(a,true);
                            strzel(px,teren[(int)x][(int)z].obiekty+0.2,pz,0,0,0,2,1);
                            //teren[(int)x][(int)z].obiekt=0;
                            //poc[a].jest=0;

                         }

                      }
                   }
             }


          //kolizje samolotow
          for (int b=0; b<ils; b++)
             if ((a!=b) && (samolot[b].jest==1))
             {
                 float _x,_y,_z, c;

                 _x=fabs(samolot[a].x-samolot[b].x);
                 _y=fabs(samolot[a].y-samolot[b].y);
                 _z=fabs(samolot[a].z-samolot[b].z);
                 if ((_x==0) && (_y==0) && (_z==0)) {
                    samolot[b].x=samolot[b].x+0.01;
                    _x=0.01;
                 }

                 c=sqrt(_x*_x + _y*_y + _z*_z);

                 if (c<=2.0)
                 {
                    //uszkodz_samolot(a);
                    uszkodz_samolot(b,true);
                 }
             }

      }//zniszczony
      else {
          if (gdzie_y(samolot[a].x,samolot[a].z)<samolot[a].y) {
             samolot[a].y = samolot[a].y+samolot[a].dy;
             if (samolot[a].dy>-0.7) samolot[a].dy=-0.7;
             if (fabs(samolot[a].dx)<0.5) samolot[a].dx=(float)((rand()%2)*2-1) * (0.5+rand()%50/100.0);
          } else if (random(100)==0) {//wysadz rozbity samolot po chwili
                 caly_wybuch(samolot[a].x,samolot[a].y,samolot[a].z, 20, 1);
                 //strzel(samolot[a].x,samolot[a].y+0.1,samolot[a].z,0,-0.2,0,2,1);
                 {
                   float klr,klg,klb;
                   if (a==sterowanie) {
                      klr=mat_sam_kd[0];
                      klg=mat_sam_kd[1];
                      klb=mat_sam_kd[2];
                   } else {
                      klr=mat_sam2_kd[0];
                      klg=mat_sam2_kd[1];
                      klb=mat_sam2_kd[2];
                   }
                   rozsypsmieci( samolot[a].x,samolot[a].y+0.1,samolot[a].z,
                                 0.30, 22, 0.8, 3.5, 0.008, 0.02,
                                 klr, klg, klb, 1, 1, 1);
                 }
                 samolot[a].jest=0;
                 samolot[a].cel=false;
          }
      }

      if (a!=sterowanie || samolot[a].zniszczony)
		   samolot[a].z = samolot[a].z+szybkoscc;

      //dymienie i ploniecie
      if (samolot[a].ileuszkodzen>=1)
      {
         float j=0.5+(rand()%30)/150.0-0.1 - samolot[a].ileuszkodzen/11.0;

         int ile;

         if (samolot[a].ileuszkodzen>=4) ile=4; else ile=1;

         //dym
         for (int n=1; n<=ile; n++) {
             if ((samolot[a].ileuszkodzen==3) ||
                (rand()%(5-samolot[a].ileuszkodzen)==0))
                nowywyb( samolot[a].x,
                         samolot[a].y,
                         samolot[a].z-0.2,

                         rand()%100/2000.0-0.025+ustawienia.kierwiatrx*2.0,
                         rand()%100/800.0+0.03,
                         rand()%100/2000.0-0.025+ustawienia.kierwiatrz*2.0,

                         rand()%50/800.0+0.01,
                         rand()%50/200.0+0.06-samolot[a].ileuszkodzen/100.0,
                         rand()%100/400.0+0.1,

                         j,j,j, 1
                         );
         }

         //ogien
         ile=samolot[a].ileuszkodzen;
         if (samolot[a].ileuszkodzen>=2)
            for (int n=0; n<=ile; n++)
             {
                  nowywyb( samolot[a].x,
                           samolot[a].y,
                           samolot[a].z-0.2,

                           ustawienia.kierwiatrx*1.5,
                           rand()%100/800.0+0.02,
                           ustawienia.kierwiatrz*1.5,

                           rand()%50/800.0+0.004,
                           rand()%50/150.0+0.07,
                           rand()%100/700.0+0.2,

                           0.5+(rand()%30)/150.0-0.1,
                           0.25+(rand()%30)/150.0-0.1,
                           0, 2

                           );
             }


      }

		if (a!=sterowanie || samolot[a].zniszczony==1)
		{
			if ((samolot[a].z<-20*dkrok) && (samolot[a].dz<0))
			{
				samolot[a].jest=0;
			}
			if ((samolot[a].z>20*dkrok) && (samolot[a].dz>0))
			{
				samolot[a].jest=0;
			}
		}

      //szalik
      samolot[a].szalikn+=szybkoscc*3.0;
      for (int s=0; s<szalikdlug; s++)
      {
         samolot[a].szalikx[s]=sin(samolot[a].szalikn-s)*(s/62.0) -samolot[a].dx*s/10.0;
         samolot[a].szaliky[s]=cos(samolot[a].szalikn-s)*(s/101.0) -samolot[a].dy*s/16.0 +s*0.01 - (0.25-szybkoscc)*0.12*s ;
         samolot[a].szalikz[s]=s*(0.02 + szybkoscc/10.0) ;

         if (a<szalikdlug-1) {
            samolot[a].szaliknormx[s]=(samolot[a].szalikx[s]+samolot[a].szalikx[s+1])/2.0;
            samolot[a].szaliknormy[s]=(samolot[a].szaliky[s]+samolot[a].szaliky[s+1])/2.0;
         }
      }


		} else //koniec samolotow
        if (gracz.jaki_cel_pokazuje==0 && gracz.ktory_cel_pokazuje==a) {
           gracz.jaki_cel_pokazuje=-1;
        }
/*   else
      if (a>0 && !FSOUND_GetPaused(kanaly[a]))
        FSOUND_SetPaused(kanaly[a], true);
  */
}

//---------------------------------------------------------------------------
void ruch_pociskow()
{
	int a,b,c,c1;
	float _x,_y,_z, _dx,_dy,_dz;

	//----------------ruch pociskow------------
	for (a=0; a<maxpoc; a++)
		if (poc[a].jest==1)
		{
			poc[a].x = poc[a].x+poc[a].dx;
			poc[a].y = poc[a].y+poc[a].dy;
			poc[a].z = poc[a].z+poc[a].dz;

			if (poc[a].rodzaj==0) { //pocisk
				poc[a].czas--;
				if (poc[a].czas <= 0) poc[a].jest = 0;

            if (((poc[a].z<-20*dkrok) && (poc[a].dz<0)) ||
               ((poc[a].z>20*dkrok) && (poc[a].dz>0)) )
                poc[a].jest=0;

			} else { //bomba
				if (poc[a].dy>-0.38) poc[a].dy=poc[a].dy-0.010;
				poc[a].dx*=0.98;
				poc[a].dz*=0.98;
				poc[a].z+=szybkoscc;
				poc[a].obrotx = 90+poc[a].dy*180;
				poc[a].obroty += poc[a].dy*60;
			}
         //uderzenie o ziemie
			if (poc[a].y < gdzie_y(poc[a].x,poc[a].z) || poc[a].y<0) {
            poc[a].jest = 0;
            if (poc[a].rodzaj==1 && poc[a].y<gdzie_y(poc[a].x,poc[a].z)) { //kratery
                float ax,az;
                ax=poc[a].x;
                az=poc[a].z;
                gdzie_xz(&ax,&az);

                for (int pz=-1; pz<=1; pz++)
                    for (int px=-1; px<=1; px++)
                        if ( ((int)ax+px>=0) && ((int)ax+px<=maxszer) &&
                             ((int)az+pz>=0) && ((int)az+pz<=maxdlug) )
                    {

                        teren[(int)ax+px][(int)az+pz].y-=0.9+rand()%100/100.0-fabs(px)*0.3-fabs(pz)*0.3;
                        teren[(int)ax+px][(int)az+pz].norm[0]=0;
                        teren[(int)ax+px][(int)az+pz].norm[1]=1;
                        teren[(int)ax+px][(int)az+pz].norm[2]=0;
                        teren[(int)ax+px][(int)az+pz].jasnosc-=1-(fabs(px)*0.5+fabs(pz)*0.5);
                        if (teren[(int)ax+px][(int)az+pz].jasnosc<0) teren[(int)ax+px][(int)az+pz].jasnosc=0;
                        if (teren[(int)ax+px][(int)az+pz].jasnosc>1) teren[(int)ax+px][(int)az+pz].jasnosc=1;

                        if ( !(abs(px)==1 && abs(pz)==1) && teren[(int)ax+px][(int)az+pz].obiekt>=1)
                           teren[(int)ax+px][(int)az+pz].obiektzniszcz=1;
                    }
                noweswiatlo(poc[a].x,poc[a].y,poc[a].z);
                rozsypsmieci( poc[a].x, gdzie_y(poc[a].x,poc[a].z)+0.1, poc[a].z,
                              0.35, 10, 1.0, 2.0, 0.004, 0.02,
                              0.05, 0.08, 0.05, 0, 0, 0);
                /*{
                 int dz= FSOUND_PlaySound(FSOUND_FREE, dzwiek[1+random(3)]);
                 FSOUND_SetFrequency(dz, (int) (30000+random(15000)));
                } */
                zagrajdzwiek(1+random(3),poc[a].x,poc[a].y,poc[a].z, 15000, false);

            }
         }

			//kolizje z obiektami
         if ((poc[a].czyj==sterowanie) || (poc[a].czyj==2))
			{
				int x,z, ob;
				float px,pz;
				for (x=1; x<maxszer-1;x++)
					for (z=zod;z<zdo; z++) {
						ob=teren[(int)x][(int)z].obiekt;
						if (ob>=1)
						{
							px=x*dkrok-dx0;
							pz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);

							_dx=fabs(poc[a].x-px);
							_dy=fabs(poc[a].y-teren[(int)x][(int)z].obiekty);
							_dz=fabs(poc[a].z-pz);
							c=sqrt(_dx*_dx + _dy*_dy + _dz*_dz);
							if (c<=obiektyrozm[ob]*teren[(int)x][(int)z].obiektrozm)
							{
								poc[a].jest=0;
                        if (poc[a].rodzaj==1)
                            /*{
                             int dz= FSOUND_PlaySound(FSOUND_FREE, dzwiek[1+random(3)]);
                             FSOUND_SetFrequency(dz, (int) (30000+random(15000)));
                            } */
                            zagrajdzwiek(1+random(3),poc[a].x,poc[a].y,poc[a].z, 15000, false);

								if (ob==ob_czolgi)
								{
									if (((poc[a].rodzaj==0) && (rand()%4==0)) ||
									    (poc[a].rodzaj==1) )
									{
										teren[(int)x][(int)z].obiektzniszcz=1;
                              if (poc[a].czyj==sterowanie) {
                                 gracz.score+=10 * (teren[(int)x][(int)z].obiektcel+1);
                                 if (teren[(int)x][(int)z].obiektcel) {
                                    gracz.ile_celow_glownych++;
                                    gracz.ile_celow_glownych_teraz++;
                                 }
                              }
									}
								}

								if (ob==ob_dziala)
								{
									if (((poc[a].rodzaj==0) && (rand()%4==0)) ||
									    (poc[a].rodzaj==1) )
									{
										teren[(int)x][(int)z].obiektzniszcz=1;
                              if (poc[a].czyj==sterowanie) {
                                 gracz.score+=10* (teren[(int)x][(int)z].obiektcel+1);
                                 if (teren[(int)x][(int)z].obiektcel) {
                                    gracz.ile_celow_glownych++;
                                    gracz.ile_celow_glownych_teraz++;
                                 }
                              }
									}
								}
								if (ob==ob_barki)
								{
									if (((poc[a].rodzaj==0) && (rand()%14==0)) ||
									    (poc[a].rodzaj==1) )
									{
										teren[(int)x][(int)z].obiektzniszcz=1;
                              if (poc[a].czyj==sterowanie) {
                                 gracz.score+=50 * (teren[(int)x][(int)z].obiektcel+1);
                                 if (teren[(int)x][(int)z].obiektcel) {
                                    gracz.ile_celow_glownych++;
                                    gracz.ile_celow_glownych_teraz++;
                                 }
                              }
									}
								}

								if ( (ob>=ob_drzewa && ob<=ob_drzewa+1) && (poc[a].rodzaj==1) ) {
										teren[(int)x][(int)z].obiektzniszcz=1;
                           }

								if ( ((ob>=ob_budynki && ob<=ob_budynki+4) || (ob>=ob_hangar && ob<=ob_hangar+2)) && (poc[a].rodzaj==1) ) {
										teren[(int)x][(int)z].obiektzniszcz=1+random(4);
                              if (poc[a].czyj==sterowanie) {
                                 gracz.score+=50 * (teren[(int)x][(int)z].obiektcel+1);
                                 if (teren[(int)x][(int)z].obiektcel) {
                                    gracz.ile_celow_glownych++;
                                    gracz.ile_celow_glownych_teraz++;
                                 }
                              }
                        }

								if ( (ob==ob_mosty || ob==ob_mosty+1) && (poc[a].rodzaj==1) ) {
										teren[(int)x][(int)z].obiektzniszcz=2+random(3);
                              if (poc[a].czyj==sterowanie) gracz.score+=50;// * (teren[(int)x][(int)z].obiektcel+1);
                              for (int xx=0; xx<=maxszer-1; xx++)
                                  if (teren[xx][(int)z].obiektcel) {
                                     gracz.score+=50;
                                     if (teren[xx][(int)z].obiektcel) {
                                        gracz.ile_celow_glownych++;
                                        gracz.ile_celow_glownych_teraz++;
                                     }
                                     teren[xx][(int)z].obiektcel=false;
                                  }
                        }

								if (ob==ob_lampy) {
										teren[(int)x][(int)z].obiektzniszcz=1;
                              if (poc[a].czyj==sterowanie) gracz.score+=2;
                           }


							}

						}
					}
			}


			//kolizje z samolotami
			for (b=0; b<ils; b++) {
				if (poc[a].czyj!=b)
				{
					_x=fabs(poc[a].x-samolot[b].x);
					_y=fabs(poc[a].y-samolot[b].y);
					_z=fabs(poc[a].z-samolot[b].z);
					if ((_x==0) && (_y==0) && (_z==0)) {
						poc[a].x=poc[a].x+0.01;
						_x=0.01;
					}

					c=sqrt(_x*_x + _y*_y + _z*_z);

					if (c<=2.0)
					{
						/*poc[a].x=poc[a].x+ (poc[a].x-samolot[b].x)/2.0;
						poc[a].z=poc[a].z+ (poc[a].z-samolot[b].z)/2.0;
						poc[a].dx=poc[a].dx+ (poc[a].dx-samolot[b].dx)*2.0;
						poc[a].dz=poc[a].dz+ (poc[a].dz-samolot[b].dz)*2.0;*/
                  int u=samolot[b].ileuszkodzen;
                  if (poc[a].rodzaj==1) //bomba
                     uszkodz_samolot(b,true);
                  else //pocisk
                      if (random(2-ustawienia.poziomtrudnosci)==0) uszkodz_samolot(b);

                  if ((poc[a].czyj==sterowanie) &&
                     (u<4) && (samolot[b].ileuszkodzen>=4) ) {
                     gracz.score+=100 * (samolot[b].cel+1);
                     if (samolot[b].cel) {
                        gracz.ile_celow_glownych++;
                        gracz.ile_celow_glownych_teraz++;
                     }
                  }

						poc[a].jest=0;
					}

				}
			}

			//kolizje z ruchomymi
			for (b=0; b<maxruchome; b++) {
				if (poc[a].czyj==0 && ruchome[b].jest && !ruchome[b].zniszcz)
				{
					_x=fabs(poc[a].x-ruchome[b].x);
					_y=fabs(poc[a].y-ruchome[b].y);
					_z=fabs(poc[a].z-ruchome[b].z);
					if ((_x==0) && (_y==0) && (_z==0)) {
						poc[a].x=poc[a].x+0.01;
						_x=0.01;
					}

					c=sqrt(_x*_x + _y*_y + _z*_z);

					if ((poc[a].rodzaj==0 && c<=ruchome[b].rozmiar) || //pocisk
                   (poc[a].rodzaj==1 && c<=ruchome[b].rozmiar+0.2)) //bomba
					{
                  if (poc[a].rodzaj==0 && random(4)==0) {
                      gracz.score+=100 * (ruchome[b].cel+1);
                      ruchome[b].zniszcz=true;
                      if (ruchome[b].cel) {
                         gracz.ile_celow_glownych++;
                         gracz.ile_celow_glownych_teraz++;
                      }
                  }

						poc[a].jest=0;
					}

				}
			}


         //jesli zniknal...
			if (poc[a].jest==0) {

           switch (poc[a].rodzaj)
           {
              case 0: //pocisk
              {
                 float px=poc[a].x;
					  float pz=poc[a].z;
                 int r;
                 float py;
                 gdzie_xz(&px,&pz);
                 if (px>=0 && px<=maxszer-1 && pz>=0 && pz<=maxdlug-1) {
                     if (teren[(int)px][(int)pz].jestwoda==0) {
                        r=3;
                        py = gdzie_y(poc[a].x,poc[a].z);
                        if (random(4)==0)
                           zagrajdzwiek(12,poc[a].x, poc[a].y, poc[a].z, 10000, false);
                     } else {
                        r=4;
                        py = 0;
                        //zagrajdzwiek(11,poc[a].x, 0, poc[a].z, 10000, false);
                     }
                     if (poc[a].y <= gdzie_y(poc[a].x,poc[a].z)+0.3 || poc[a].y<=0)
                         nowywyb(poc[a].x, py, poc[a].z,
                                 0.05-random(100)/1000.0, 0.05+random(100)/1500.0, 0.05-random(100)/1000.0,
                                 0.3, 0.02, 0.25,
                                 0.25,0.05,0.0, r,1.0,
                                 0.015 );
                 }
                 else
                     nowywyb(poc[a].x, poc[a].y, poc[a].z,
                             0, 0.1, 0,
                             0.1, 0.13, 0.25,
                             1.0,1.0,1.0, 2,0.5 );
              }
              break;
              case 1: //bomba
                 float px=poc[a].x;
					  float pz=poc[a].z;
                 int r;
                 gdzie_xz(&px,&pz);
                 if (px>=0 && px<=maxszer-1 && pz>=0 && pz<=maxdlug-1 &&
                     poc[a].y > gdzie_y(poc[a].x,poc[a].z) && poc[a].y<0 &&
                     teren[(int)px][(int)pz].jestwoda==1) { //plusk wody

                     nowywyb(poc[a].x, 0, poc[a].z,
                             0.05-random(100)/1000.0, 0.05+random(100)/1500.0, 0.05-random(100)/1000.0,
                             0.3, 0.015, 0.35,
                             1,1,1, 4, 0.9,
                             0.015 );

                     zagrajdzwiek(11,poc[a].x, 0, poc[a].z, 10000, false);

                 } else { //wybuch
                     nowywyb(poc[a].x, poc[a].y, poc[a].z,
                             0, 0.1, 0,
                             0.2, 0.02, 3, 0.7,0.4,0.05,0, 0.4);

                     for (int bb=0; bb<=5; bb++)
                         nowywyb(poc[a].x-0.05+rand()%10/10.0, poc[a].y, poc[a].z-0.05+rand()%10/10.0,
                                 0, 0.01+rand()%50/600.0, 0,
                                 0.04+rand()%10/500.0, 0.03, 1.6+rand()%100/100.0, 0.7,0.4,0.05,2, 0.8);

                    //uszkodz samoloty blisko wybuchu
                    for (int b=0; b<ils; b++)
                       if ((samolot[b].jest==1) && (samolot[b].ileuszkodzen<4))
                       {
                           float _x,_y,_z, c;

                           _x=fabs(poc[a].x-samolot[b].x);
                           _y=fabs(poc[a].y-samolot[b].y);
                           _z=fabs(poc[a].z-samolot[b].z);
                           if ((_x==0) && (_y==0) && (_z==0)) {
                              samolot[b].x=samolot[b].x+0.01;
                              _x=0.01;
                           }

                           c=sqrt(_x*_x + _y*_y + _z*_z);

                           if (c<=2.5+ustawienia.poziomtrudnosci)
                           {
                              uszkodz_samolot(b);
                              if (c<=1.5+ustawienia.poziomtrudnosci)
                                 uszkodz_samolot(b);
                              samolot[b].dx=samolot[b].dx+(samolot[b].x-poc[a].x)/5.0;
                              samolot[b].dy=samolot[b].dy+(samolot[b].y-poc[a].y)/5.0;
                              samolot[b].dz=samolot[b].dz+(samolot[b].z-poc[a].z)/5.0;
                           }
                       }
                    //zniszcz ruchome blisko wybuchu
                    for (int b=0; b<maxruchome; b++)
                       if (ruchome[b].jest==1 && ruchome[b].zniszcz==0) {
                         float _x=fabs(poc[a].x-ruchome[b].x);
                         float _y=fabs(poc[a].y-ruchome[b].y);
                         float _z=fabs(poc[a].z-ruchome[b].z);
                         if ((_x==0) && (_y==0) && (_z==0)) {
                            _x=0.01;
                         }

                         c=sqrt(_x*_x + _y*_y + _z*_z);

                         if (c<=ruchome[b].rozmiar+1.0) {
                             gracz.score+=100;
                             ruchome[b].zniszcz=true;
                         }

                   }
                 }//if

              break;
           }
        }

		}

}

//---------------------------------------------------------------------------
void ruch_wody()
{
	int a,b;
	GLfloat vek1[3],vek2[3],vek3[3];
	// ----------------------woda

	if (ustawienia.rodzajwody==1)
	{
		for (b=1; b<wodailez0; b++)
			for (a=1; a<=wodailex0; a++) {
				//--------woda[a][b].y=sin(dz0-(oo/29.0+b)/4.0)*cos(dz0-(oo/20.0+b*a)/3.3)/2.0;

				//woda[a][b].y=(sin((-dz0/1.4-oo/40.0-b-a))*cos(-oo/41.0+a+b*0.11))/7.0+sin(-(oo-dz0/1.4)/4.3+b*4.3-a*8.0)/19.0;

            woda[a][b].y=sin(oo/21.0 + woda[a][(int)fmod(b+dz0/2.0, 80)].rnd)/5.0;
			}

		//obliczanie normalnych
		for (b=1; b<wodailez0; b++)
			for (a=1; a<=wodailex0; a++) {
				vek1[0] = 1.0;                                                                      
				vek1[1] = (woda[(int)a+1][(int)b  ].y-woda[(int)a  ][(int)b  ].y);
				vek1[2] = 0.0;

				vek2[0] = 0.0;
				vek2[1] = (woda[(int)a  ][(int)b+1].y-woda[(int)a  ][(int)b  ].y);
				vek2[2] = 1.0;

				cross_prod(vek2,vek1, vek3);
                                normalize1(vek3);

				woda[a][b].norm[0]=vek3[0];
				woda[a][b].norm[1]=vek3[1];
				woda[a][b].norm[2]=vek3[2];
			}
	}
}


//---------------------------------------------------------------------------
void ruch_wybuchow()
{
	int a;

	for (a=0; a<maxwyb; a++)
		if (wyb[a].jest==1)
		{
         if (ustawienia.detale<2 && random(100+ustawienia.detale*60)==0) wyb[a].jest=0;

			wyb[a].x = wyb[a].x+wyb[a].dx;
			wyb[a].y = wyb[a].y+wyb[a].dy;
			wyb[a].z = wyb[a].z+wyb[a].dz+szybkoscc;

			wyb[a].dy = wyb[a].dy-wyb[a].waga;

			wyb[a].obrot += 22;

         wyb[a].przezr -= wyb[a].szybkoscprzezr;
         if (wyb[a].rozm<wyb[a].maxrozm)
            wyb[a].rozm += wyb[a].szybkoscrozm;

         if (wyb[a].y<0) {
            if (wyb[a].rodzaj==1 || wyb[a].rodzaj==4) wyb[a].jest=0;
            else
            if (wyb[a].rodzaj==2) wyb[a].przezr-=0.1;
         }
         if (wyb[a].przezr <= 0) wyb[a].jest = 0;

      }

}

//---------------------------------------------------------------------------
void ruch_swiatel()
{
   for (int a=swiatlaod; a<=swiatlado; a++)
     if (swiatla[a].czas>0) {
        swiatla[a].czas-=0.02;
        if (swiatla[a].czas<0) swiatla[a].czas=0;
        swiatla[a].z+=szybkoscc;
        swiatla[a].jasnosc=sin(swiatla[a].czas*M_PI/1.6);
     }
}

//---------------------------------------------------------------------------
void ruch_smieci()
{
	int a;

	for (a=0; a<maxsmiec; a++)
		if (smiec[a].jest==1)
		{
         if (ustawienia.detale<2 && random(100+ustawienia.detale*60)==0) smiec[a].jest=0;

			smiec[a].x = smiec[a].x+smiec[a].dx;
			smiec[a].y = smiec[a].y+smiec[a].dy;
			smiec[a].z = smiec[a].z+smiec[a].dz+szybkoscc;

			smiec[a].obrot += 22;

         if (smiec[a].dy>-1)
			   smiec[a].dy -= smiec[a].waga;

         if (smiec[a].y<0) {
            if (fabs(smiec[a].dy)>0.5) smiec[a].dy*=0.9;
            if (random(50)==0) smiec[a].jest=0;

            if (smiec[a].y-smiec[a].dy>=0)
               nowywyb(smiec[a].x, 0, smiec[a].z,
                       0.05-random(100)/1000.0, 0.03+random(100)/1500.0, 0.05-random(100)/1000.0,
                       0.06, 0.02, 0.45,
                       1,1,1, 4,0.8,
                       0.010, 0.1 );

         }

         if (smiec[a].dy<=0 && gdzie_y(smiec[a].x,smiec[a].z)>=smiec[a].y) {
            if (random(3)==0) smiec[a].jest = 0;
                         else smiec[a].dy=-smiec[a].dy*0.6;
         }

         if (smiec[a].plonie==1) {
            //if (rand()%1==0) {
                nowywyb( smiec[a].x,
                         smiec[a].y,
                         smiec[a].z-0.2,

                         ustawienia.kierwiatrx,
                         rand()%100/800.0+0.02,
                         ustawienia.kierwiatrz,

                         rand()%50/800.0+0.015,
                         rand()%50/150.0+0.04,
                         rand()%100/700.0+0.25,

                         0.5+(rand()%30)/150.0-0.1,
                         0.25+(rand()%30)/150.0-0.1,
                         0, 2
                         );
                if (rand()%90==0) smiec[a].plonie=0;
            //}
         }
         if (smiec[a].dymi==1) {
            if (random(2)==0) {
               float j=0.1+(rand()%30)/150.0 ;
                nowywyb( smiec[a].x,
                         smiec[a].y,
                         smiec[a].z-0.2,

                         rand()%100/2000.0-0.025+ustawienia.kierwiatrx,
                         rand()%100/800.0+0.01,
                         rand()%100/2000.0-0.025+ustawienia.kierwiatrz,

                         rand()%50/800.0+0.02,
                         rand()%50/200.0+0.02,
                         rand()%100/700.0+0.2,

                         j,j,j, 1
                         );

                if (rand()%90==0) smiec[a].dymi=0;
            }
         }
      }

}


//---------------------------------------------------------------------------
// ******************************* RUCH ***********************************
void ruch()
{
	int a,b,c,c1;
	float mn, _x,_y,_z, _dx,_dy,_dz;
	GLfloat vek1[3],vek2[3],vek3[3];
	GLfloat value1, value2, value3;

	oo++;

   //nowy "kawal" terenu:
   if (dz0/dkrok>=maxdlug-ilewidac_do) {
      //czy miasto?
      if ((gracz.ile_celow_glownych_teraz>=4) /*&&
          (gracz.ile_celow_glownych>=gracz.etap*3)*/) gracz.czymiasto=true;
          else gracz.czymiasto=false;
      stworz_teren(false);
      gracz.ile_celow_glownych_teraz=0; //wyczysc na lotnisku ilosc celow teraz
      dz0=40;//maxdlug-ilewidac_suma;
   }


   szybkoscc = szybkosc*1.6;

   ooszyb += szybkoscc/600.0;

/*   if (samolot[sterowanie].jest==1 && samolot[sterowanie].zniszczony==0 && samolot[sterowanie].ileuszkodzen<4)
      szybkoscc -= samolot[sterowanie].dz;*/

   if ((ustawienia.jestwiatr==1) && (gracz.corobi==2) &&
      (samolot[sterowanie].jest==1 && samolot[sterowanie].zniszczony==0 && samolot[sterowanie].ileuszkodzen<4))
      //dz0 = dz0-ustawienia.kierwiatrz;
      szybkoscc-=ustawienia.kierwiatrz;

	dz0=dz0+szybkoscc;

	zod=dz0/dkrok+ilewidac_od;
	if (zod<0) zod=0;
		else if (zod>maxdlug-1) zod=maxdlug-1;

	zdo=dz0/dkrok+ilewidac_do;
	if (zdo<0) zdo=0;
		else if (zdo>maxdlug-1) zdo=maxdlug-1;

   if ((int)zdo==gracz.ostrzezenie_o_lotnisku) gracz.jest_lotnisko=true;

   if (rand()%200==0) { //zmiana wiatru
      if (ustawienia.jestwiatr==0) {
         ustawienia.jestwiatr=1;
         ustawienia.kierwiatrx=rand()%100/800.0 - 0.05;
         ustawienia.kierwiatrz=rand()%100/800.0 - 0.05;
         if (ustawienia.poziomtrudnosci==0) {
            ustawienia.kierwiatrx/=2.0;
            ustawienia.kierwiatrz/=2.0;
         }
      } else {
        ustawienia.jestwiatr=0;
         ustawienia.kierwiatrx=0;
         ustawienia.kierwiatrz=0;
      }
      ekran.odswiezwiatr=1;
   }

   if (ekran.ostrzezenieosamolocie==0) {
      if (gracz.corobi==2) a=500-ustawienia.poziomtrudnosci*80;
         else a=40-ustawienia.poziomtrudnosci*5;
      if (random(a)==0) ekran.ostrzezenieosamolocie = 1;
   } else {
     ekran.ostrzezenieosamolocie++;
     if (ekran.ostrzezenieosamolocie%10==5)
        zagrajdzwiek(10,0,0,0,0,true);
     if (ekran.ostrzezenieosamolocie>=40) {
        nowy_samolot();
        ekran.ostrzezenieosamolocie=0;
     }
   }

	ruch_samolotow();


	ruch_pociskow();

	ruch_wody();

   ruch_smieci();
   ruch_wybuchow();
   ruch_swiatel();
   ruszaj_ruchome();

	dzialanie_gracza();
	dzialaj_obiekty_scenerii();

	if ((sterowanie>=0) &&
       (samolot[sterowanie].jest==1) && (samolot[sterowanie].zniszczony==0))
		sterowanie_graczem();
   else {
	    gracz.corobi=3;
       if (gracz.koniecgry==0)  gracz.koniecgry=1;
   }

   if (ustawienia.jasnoscswiatla<ustawienia.dojasnoscswiatla) {
      ustaw_swiatlo(ustawienia.jasnoscswiatla+0.001);
      if (ustawienia.jasnoscswiatla>ustawienia.dojasnoscswiatla)
         ustawienia.jasnoscswiatla=ustawienia.dojasnoscswiatla;
   } else {
   if (ustawienia.jasnoscswiatla>ustawienia.dojasnoscswiatla)
      ustaw_swiatlo(ustawienia.jasnoscswiatla-0.001);
      if (ustawienia.jasnoscswiatla<ustawienia.dojasnoscswiatla)
         ustawienia.jasnoscswiatla=ustawienia.dojasnoscswiatla;
   }

//   if (random(600)==0) ustawienia.dojasnoscswiatla=0.4+random(60)/100.0;

   if (kameraczas>=1) kameraczas+=0.1;
   if (kl['+']==1 && ustawienia.odleglosckamery>0.5) ustawienia.odleglosckamery-=0.2;
   if (kl['-']==1 && ustawienia.odleglosckamery<30) ustawienia.odleglosckamery+=0.2;

   if (gracz.koniecgry>0) {
      if (gracz.koniecgry>=300) {
         ustawienia.pauza=true;
         if (gracz.score>rekordy[ilemiejsc-1].pkt) {
             BMForm->PanelDolny->Hide();
             BMForm->PanelNewHigh->Show();
             BMForm->YourScore->Caption="Your score is "+IntToStr(gracz.score);
             gracz.rank=random(3);
             BMForm->YourRank->Caption="Your rank is "+ranki[gracz.rank];
             BMForm->YourName->SetFocus();
             //BMForm->ActionOKNewHiscore->Enabled=true;
         } else {
             BMForm->PanelDolny->Hide();
             BMForm->PanelHighscores->Show();
             //BMForm->ActionOKHighscores->Enabled=true;
         }
         FSOUND_Stream_SetTime(muzyka, 0);
         FSOUND_SetPaused(muzyka_chan, FALSE);
         gracz.jest_gra = false;
      } else
        gracz.koniecgry++;
   }
}


