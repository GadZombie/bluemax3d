// ******************************* RYSOWANIE ***********************************


// --------------kamera
void ustaw_kamere()
{
	float x,z;

	switch (kamera)
	{
		case 0: //kamera ogolna krecaca sie
		gluLookAt(samolot[sterowanie].x+ustawienia.odleglosckamery*sin(oo/50.0),
                6+ustawienia.odleglosckamery/2.0,
                samolot[sterowanie].z+ustawienia.odleglosckamery*cos(oo/50.0),
				samolot[sterowanie].x, samolot[sterowanie].y, samolot[sterowanie].z,
				0.0, 1.0, 0.0);
      //glFogf (GL_FOG_END, ilewidac_do + samolot[sterowanie].z+25*cos(oo/50.0));
		break;
		case 1: //kamera z tylu i troche gory
		gluLookAt( samolot[sterowanie].x+samolot[sterowanie].dx*0.4,
			       samolot[sterowanie].y+samolot[sterowanie].dy*0.5+ustawienia.odleglosckamery/3.0,
				   samolot[sterowanie].z-samolot[sterowanie].dz*5.0+1+ustawienia.odleglosckamery,
				samolot[sterowanie].x, samolot[sterowanie].y, samolot[sterowanie].z-ustawienia.odleglosckamery,
				0.0, 1.0, 0.0);
      //glFogf (GL_FOG_END, ilewidac_do + samolot[sterowanie].z-samolot[sterowanie].dz*5.0+1+ustawienia.odleglosckamery);
		break;
		case 2: //kamera zza plecow
		gluLookAt( samolot[sterowanie].x+samolot[sterowanie].dx*0.4,
			       samolot[sterowanie].y+samolot[sterowanie].dy*0.5+2+ustawienia.odleglosckamery,
				   samolot[sterowanie].z-samolot[sterowanie].dz*5.0+1+ustawienia.odleglosckamery,
				samolot[sterowanie].x, samolot[sterowanie].y, samolot[sterowanie].z-ustawienia.odleglosckamery,
				0.0, 1.0, 0.0);
      //glFogf (GL_FOG_END, ilewidac_do + samolot[sterowanie].z-samolot[sterowanie].dz*5.0+1+ustawienia.odleglosckamery);
		break;
		case 3: //kamera w strone samolotu
		gluLookAt( 0, 20, 25+ustawienia.odleglosckamery,
				samolot[sterowanie].x/2.0, samolot[sterowanie].y/2.0, samolot[sterowanie].z/2.0,
				0.0, 1.0, 0.0);
/*		gluLookAt( 15, 24, 25,
				samolot[sterowanie].x/2.0, samolot[sterowanie].y/2.0, samolot[sterowanie].z/2.0,
				0.0, 1.0, 0.0);*/
      //glFogf (GL_FOG_END, 25+ustawienia.odleglosckamery+ilewidac_do);
		break;
		case 4: //kamera ze srodka
      {
        gluLookAt( samolot[sterowanie].x,
                   samolot[sterowanie].y,
                   samolot[sterowanie].z,

                   samolot[sterowanie].x,
                   samolot[sterowanie].y,
                   samolot[sterowanie].z-2,

                   0,1,0);
        glMatrixMode(GL_PROJECTION);
        glTranslatef(0, -0.28, -0.24);
		  glRotatef(samolot[sterowanie].dx*70, 0.0, 0.5, 1.0); //obrot wokol osi przy przesuwaniu w bok
		  glRotatef(-samolot[sterowanie].dy*60, 1.0, 0.0, 0.0);
        glMatrixMode(GL_MODELVIEW);
      }
		break;
		case 5: //kamera z ziemi w strone samolotu
      {
        float kx,kz, ky, ky2;
        float kk;
        kk=kameraczas;
        if (kk>30) kk=30;
        kx=samolot[sterowanie].x+kk*sin(kameraczas/7.0);
        kz=samolot[sterowanie].z+kk*cos(kameraczas/7.0);

        ky=gdzie_y(samolot[sterowanie].x, samolot[sterowanie].z)+4.0;
        ky2=gdzie_y(kx,kz);
        if (ky<ky2+1.0) ky=ky2+1.0;
        gluLookAt( kx, ky, kz,
              samolot[sterowanie].x, samolot[sterowanie].y, samolot[sterowanie].z,
              0.0, 1.0, 0.0);
      }
		break;
		case 6: //kamera krecaca sie wokol jadacego pojazdu
		gluLookAt(ruchome[0].x+6*sin(oo/50.0), ruchome[0].y+3, ruchome[0].z+6*cos(oo/50.0),
				ruchome[0].x, ruchome[0].y, ruchome[0].z,
				0.0, 1.0, 0.0);
		break;
		case 7: //kamera do tylu
		gluLookAt( samolot[sterowanie].x+samolot[sterowanie].dx*0.4,
			       samolot[sterowanie].y+samolot[sterowanie].dy*0.5+ustawienia.odleglosckamery/3.0,
				   samolot[sterowanie].z-samolot[sterowanie].dz*5.0-1-ustawienia.odleglosckamery,
				samolot[sterowanie].x, samolot[sterowanie].y, samolot[sterowanie].z+ustawienia.odleglosckamery,
				0.0, 1.0, 0.0);

		break;
		case 8: //kamera ortho w strone samolotu
		gluLookAt( samolot[sterowanie].x/1.0+15, samolot[sterowanie].y/2.0+16, samolot[sterowanie].z/1.0+15 -6,
				     samolot[sterowanie].x/1.0, samolot[sterowanie].y/2.0+5, samolot[sterowanie].z/1.0 -6,
				     0.0, 1.0, 0.0);
		break;
	}
}

//-----------------------------------------------------------------------------
// --------------obiekty
void rysuj_teren()
{
   #define ilebok 30
   float x,z,mn, px,pz, tx;
   GLfloat mat[3];

   //glPolygonMode(GL_BACK, GL_POINT);
   glPolygonMode(GL_FRONT, GL_FILL);
   glCullFace(GL_BACK);

   glPushMatrix();
   wlacz_teksture(1);
   glEnable(GL_COLOR_MATERIAL);

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_dno_ka);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dno_ka);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dno_ka);
   glMaterialf(GL_FRONT, GL_SHININESS, 20);

   for (x=0; x<maxszer-1;x++) {
       glBegin(GL_TRIANGLE_STRIP);
       for (z=zod;z<zdo; z++) {

           glColor3f( teren[(int)x][(int)z  ].jasnosc * teren[(int)x][(int)z  ].kr,
                      teren[(int)x][(int)z  ].jasnosc * teren[(int)x][(int)z  ].kg,
                      teren[(int)x][(int)z  ].jasnosc * teren[(int)x][(int)z  ].kb
                     );

                                    glNormal3fv(teren[(int)x][(int)z  ].norm);
                                    pz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);
           if (x==0) {
              px=-ilebok*dkrok-dx0;
              tx=-ilebok;
           } else {
              px=x*dkrok-dx0;
              tx=x;
           }
           glTexCoord2f((float) tx/teren_wielkosctex, (float) (z-zod+ ((int)dz0/(int)dkrok))/teren_wielkosctex);
                                    glVertex3f(px, teren[(int)x][(int)z  ].y, pz);

           glColor3f( teren[(int)x+1][(int)z  ].jasnosc * teren[(int)x+1][(int)z  ].kr,
                      teren[(int)x+1][(int)z  ].jasnosc * teren[(int)x+1][(int)z  ].kg,
                      teren[(int)x+1][(int)z  ].jasnosc * teren[(int)x+1][(int)z  ].kb
                     );

                                    glNormal3fv(teren[(int)x+1][(int)z  ].norm);
           if (x==maxszer-2) {
              px=(maxszer+ilebok)*dkrok-dx0;
                                       tx=x+ilebok;
                                    } else {
             px=(x+1)*dkrok-dx0;
             tx=x+1;
             }
           glTexCoord2f((float) tx/teren_wielkosctex, (float) (z-zod+ ((int)dz0/(int)dkrok))/teren_wielkosctex);
                                    glVertex3f(px, teren[(int)x+1][(int)z].y, pz);

       }
       glEnd();
   }

   glDisable(GL_COLOR_MATERIAL);
   wylacz_teksture();

   glPopMatrix();

   glPolygonMode(GL_FRONT, GL_FILL);
}

//-----------------------------------------------------------------------------
void rysuj_obiekty_scenerii(int przebieg, bool celowniki=false)
{
	float x,z,mn, px,pz;
	GLfloat mat[3];
//   glDepthMask(GL_TRUE);

   glPushAttrib(GL_ALL_ATTRIB_BITS);
   glDisable(GL_COLOR_MATERIAL);
   glPolygonMode(GL_FRONT, GL_FILL);
   if (przebieg==1) {
         glEnable(GL_BLEND);
         glDepthMask(GL_FALSE);
         glPolygonMode(GL_BACK, GL_FILL);
         glDisable(GL_CULL_FACE);
   } else {
     //glPolygonMode(GL_BACK, GL_POINT);
     glCullFace(GL_BACK);
   }

		for (x=0; x<=maxszer-1;x++)
			for (z=zod;z<zdo; z++)
				if ((teren[(int)x][(int)z].obiekt>=1) && (teren[(int)x][(int)z].obiektktoreprzejscie==przebieg))
				{
               if (!celowniki) { //rysuj obiekty
					    px=x*dkrok-dx0;
                   pz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);
                   glPushMatrix();
                      glTranslatef(px,teren[(int)x][(int)z].obiekty,pz);
                      if (teren[(int)x][(int)z].obiektrozm!=1.0)
                         glScalef(teren[(int)x][(int)z].obiektrozm,teren[(int)x][(int)z].obiektrozm,teren[(int)x][(int)z].obiektrozm);
                      if (teren[(int)x][(int)z].obiektobr!=0.0)
                         glRotatef(teren[(int)x][(int)z].obiektobr,0,1,0);
                      if (teren[(int)x][(int)z].obiekt==ob_barki)
                         glRotatef(teren[(int)x][(int)z].obiekty*22,1,0,0);
                      glCallList(listbase+teren[(int)x][(int)z].obiekt);
                      //dzialka obrotowe:
                      if (teren[(int)x][(int)z].obiekt==ob_czolgi ||
                          teren[(int)x][(int)z].obiekt==ob_barki ||
                          teren[(int)x][(int)z].obiekt==ob_dziala) {
                         glPopMatrix();
                         glPushMatrix();
                           glTranslatef(px,teren[(int)x][(int)z].obiekty,pz);
                           if (teren[(int)x][(int)z].obiektrozm!=1.0)
                              glScalef(teren[(int)x][(int)z].obiektrozm,teren[(int)x][(int)z].obiektrozm,teren[(int)x][(int)z].obiektrozm);
                           glRotatef(teren[(int)x][(int)z].obiektpatrzyobr, 0,1,0);
                           glCallList(listbase+teren[(int)x][(int)z].obiekt+1);
                           glRotatef(teren[(int)x][(int)z].obiektpatrzypion, -1, 0, 0 );
                           glCallList(listbase+teren[(int)x][(int)z].obiekt+2);
                         glPopMatrix();
                         glPushMatrix();
                      }

                   glPopMatrix();

                   //rozciagniete ulice na boki:
                    if ((x==0 || x==maxszer-2) &&
                        teren[(int)x][(int)z].obiekt==ob_ulice ||
                        teren[(int)x][(int)z].obiekt==ob_ulice+1 ||
                        teren[(int)x][(int)z].obiekt==ob_mosty ||
                        teren[(int)x][(int)z].obiekt==ob_mosty+1
                        )
                    {
                       int od_,do_, ob;
                       ob = teren[(int)x][(int)z].obiekt;
                       if (ob==ob_mosty) ob=ob_ulice;
                       if (ob==ob_mosty+1) ob=ob_ulice+1;
                       if (x==0) {
                          od_=-20;
                          do_=-1;
                       } else {
                          od_=maxszer;
                          do_=maxszer+20;
                       }
                        pz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);
                       for (int x1=od_; x1<=do_; x1+=2) {
                           px=x1*dkrok-dx0;
                           glPushMatrix();
                              glTranslatef(px,teren[(int)x][(int)z].obiekty,pz);
                              if (teren[(int)x][(int)z].obiektrozm!=1.0)
                                 glScalef(teren[(int)x][(int)z].obiektrozm,teren[(int)x][(int)z].obiektrozm,teren[(int)x][(int)z].obiektrozm);
                              if (teren[(int)x][(int)z].obiektobr!=0.0)
                                 glRotatef(teren[(int)x][(int)z].obiektobr,0,1,0);
                              glCallList(listbase+ob);
                           glPopMatrix();
                       }
                    }

               } else { //celowniki

                  //jesli glowny cel - rysuj celownik
                  if (teren[(int)x][(int)z].obiektcel) {
                     float celx = x*dkrok-dx0,
                           cely = teren[(int)x][(int)z].obiekty,
                           celz = (float) -z*dkrok+dz0 + fmod(dz0, dkrok),
                           celrozm=2;
                     glPushMatrix();
                     glPushAttrib(GL_ALL_ATTRIB_BITS);


                     float viewMatrix[16];
                     glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
                     GLfloat right[3]={viewMatrix[0], viewMatrix[4], viewMatrix[8]};
                     GLfloat up[3]={viewMatrix[1], viewMatrix[5], viewMatrix[9]};

                     glEnable(GL_BLEND);
                     glDisable(GL_LIGHTING);
                     glDepthMask(GL_FALSE);
                     glEnable(GL_COLOR_MATERIAL);
                     glPolygonMode(GL_FRONT, GL_FILL);
                     glCullFace(GL_BACK);

                     if (ustawienia.mgla) glDisable(GL_FOG);

                     glColor4f(1,0.5+sin(oo/4.0)*0.5,0.5+sin(oo/4.0)*0.5, 0.7);
                     wlacz_teksture(2);
                     glBegin(GL_QUADS);
                       glTexCoord2f(0.0, 0.0);
                       glVertex3f ((celx + (right[0] + up[0]) * -celrozm),(cely + (right[1] + up[1]) * -celrozm),(celz + (right[2] + up[2]) * -celrozm));
                       glTexCoord2f(1.0, 0.0);
                       glVertex3f ((celx + (right[0] - up[0]) * celrozm),(cely + (right[1] - up[1]) * celrozm),(celz + (right[2] - up[2]) * celrozm));
                       glTexCoord2f(1.0, 1.0);
                       glVertex3f ((celx + (right[0] + up[0]) * celrozm),(cely + (right[1] + up[1]) * celrozm),(celz + (right[2] + up[2]) * celrozm));
                       glTexCoord2f(0.0, 1.0);
                       glVertex3f ((celx + (up[0] - right[0]) * celrozm),(cely + (up[1] - right[1]) * celrozm),(celz + (up[2] - right[2]) * celrozm));
                     glEnd();
                     wylacz_teksture();

                     if (ustawienia.mgla) glEnable(GL_FOG);

                     glDisable(GL_COLOR_MATERIAL);
                     glDepthMask(GL_TRUE);
                     glDisable(GL_BLEND);



                     glPopAttrib();
                     glPopMatrix();

                  }

               }

				}

/*   if (przebieg==1) {
	      glPolygonMode(GL_FRONT, GL_POINT);
		   glDepthMask(GL_TRUE);
		   glDisable(GL_BLEND);
   } else
     glPolygonMode(GL_FRONT, GL_FILL);
*/

   if (przebieg==1)
         glEnable(GL_CULL_FACE);

   glPopAttrib();

}

//-----------------------------------------------------------------------------
void rysuj_sprajt(float sx, float sy, float sz, float sr, GLfloat *right, GLfloat *up)
{
 glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f ((sx + (right[0] + up[0]) * -sr),(sy + (right[1] + up[1]) * -sr),(sz + (right[2] + up[2]) * -sr));
   glTexCoord2f(1.0, 0.0);
   glVertex3f ((sx + (right[0] - up[0]) * sr),(sy + (right[1] - up[1]) * sr),(sz + (right[2] - up[2]) * sr));
   glTexCoord2f(1.0, 1.0);
   glVertex3f ((sx + (right[0] + up[0]) * sr),(sy + (right[1] + up[1]) * sr),(sz + (right[2] + up[2]) * sr));
   glTexCoord2f(0.0, 1.0);
   glVertex3f ((sx + (up[0] - right[0]) * sr),(sy + (up[1] - right[1]) * sr),(sz + (up[2] - right[2]) * sr));
 glEnd();
}

//-----------------------------------------------------------------------------
void rysuj_swiatelka_scenerii()
{
	float x,z,mn, px,pz;
	GLfloat mat[3];
//   glDepthMask(GL_TRUE);

   glPushAttrib(GL_ALL_ATTRIB_BITS);
   glEnable(GL_COLOR_MATERIAL);
   glDisable(GL_LIGHTING);
   glDisable(GL_FOG);
   glPolygonMode(GL_FRONT, GL_FILL);
   glEnable(GL_BLEND);
   glDepthMask(GL_FALSE);
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);

   float viewMatrix[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
   GLfloat right[3]={viewMatrix[0], viewMatrix[4], viewMatrix[8]};
   GLfloat up[3]={viewMatrix[1], viewMatrix[5], viewMatrix[9]};

   float sx,sy,sz,sr;

   //teren
   for (x=0; x<=maxszer-1;x++)
     for (z=zod;z<zdo; z++)
        if (teren[(int)x][(int)z].obiekt>=1)
        {
            px=x*dkrok-dx0;
            pz=(float) -z*dkrok+dz0 + fmod(dz0, dkrok);
            if (teren[(int)x][(int)z].obiekt==ob_lotnisko)
            {
               sy=teren[(int)x][(int)z].obiekty+0.05;
               sz=pz;
               sr=0.4;

               glColor4f(1.0, 0.1, 0.1, 1.0);
               wlacz_teksture(17);

               for (int n=-1; n<=1; n+=2) {
                 sx=px+n*5.0;
                 rysuj_sprajt(sx,sy,sz,sr,right,up);
               }
               wylacz_teksture();

            }

            if (teren[(int)x][(int)z].obiekt==ob_lampy && ustawienia.jasnoscswiatla<0.75 )
            {
               sy=teren[(int)x][(int)z].obiekty+1.6*teren[(int)x][(int)z].obiektrozm;
               sx=px;
               sz=pz;
               sr=0.8*teren[(int)x][(int)z].obiektrozm;

               glColor4f(1.0, 1.0, 0.6, 0.9);
               wlacz_teksture(17);
               rysuj_sprajt(sx,sy,sz,sr,right,up);
               wylacz_teksture();

            }

            glPopMatrix();

        }

   //ruchome
	for (int a=0; a<maxruchome; a++)
		if (ruchome[a].jest==1)
		{
		  glPushMatrix();
           switch (ruchome[a].rodzaj)
           {
             case 1: //czolg
              if (fabs(ruchome[a].dy)<0.1) {
               sx=ruchome[a].x;
               sy=ruchome[a].y;
               sr=0.35;

               wlacz_teksture(17);
               glColor4f(1.0, 0.1, 0.1, 0.8);
               for (int n=-1; n<=1; n+=2) {
                   sz=ruchome[a].z+n*0.38;
                   rysuj_sprajt(sx-sin(ruchome[a].obrot*PI180)*0.83,sy+0.34,sz,sr,right,up);
               }
               wylacz_teksture();
              }
             break;
             case 2: //auto
              if (fabs(ruchome[a].dy)<0.1) {
               sx=ruchome[a].x;
               sy=ruchome[a].y;
               sr=0.5; //0.5

               glColor4f(1.0, 1.0, 0.4, 0.8);
               wlacz_teksture(17);
               for (int n=-1; n<=1; n+=2) {
                   sx= ruchome[a].x
                       +sin(ruchome[a].obrot*PI180)*0.82
                       +(float)n*cos(ruchome[a].obrot*PI180)*0.24;
                   sz= ruchome[a].z
                       +cos(ruchome[a].obrot*PI180)*0.82
                       -(float)n*sin(ruchome[a].obrot*PI180)*0.24;

                   rysuj_sprajt(sx,sy+0.4,sz,sr,right,up);
/*                   sz=ruchome[a].z-(float)n*cos(ruchome[a].obrot*PI180)*0.24;
                   rysuj_sprajt(sx+sin(ruchome[a].obrot*PI180)*0.82,sy+0.4,sz,sr,right,up);*/
               }

               glColor4f(1.0, 0.1, 0.1, 0.8);
               for (int n=-1; n<=1; n+=2) {
                   sx= ruchome[a].x
                       -sin(ruchome[a].obrot*PI180)*0.83
                       +(float)n*cos(ruchome[a].obrot*PI180)*0.24;
                   sz= ruchome[a].z
                       -cos(ruchome[a].obrot*PI180)*0.83
                       -(float)n*sin(ruchome[a].obrot*PI180)*0.24;

                   rysuj_sprajt(sx,sy+0.4,sz,sr,right,up);
/*                   sz=ruchome[a].z-(float)n*cos(ruchome[a].obrot*PI180)*0.24;
                   rysuj_sprajt(sx-sin(ruchome[a].obrot*PI180)*0.83,sy+0.36,sz,sr,right,up);*/
               }
               wylacz_teksture();
              }
             break;
             case 3: //lokomotywa
              if (fabs(ruchome[a].dy)<0.1) {
               sx=ruchome[a].x;
               sy=ruchome[a].y;
               sr=0.6;

               glColor4f(1.0, 1.0, 0.4, 0.8);
               wlacz_teksture(17);
               for (int n=-1; n<=1; n+=2) {
                   sz=ruchome[a].z+n*0.3;
                   rysuj_sprajt(sx+sin(ruchome[a].obrot*PI180)*1.82,sy+0.3,sz,sr,right,up);
               }
               wylacz_teksture();
              }
             break;
/*             case 4: //weglarka
             break;
             case 5: //wagon
             break;*/
           }

        glPopMatrix();

        //rysuj_cien_ruchome(a);
		}



    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);

   glPopAttrib();

}

//-----------------------------------------------------------------------------
void rysuj_otoczenie()
{
  if (ustawienia.jestniebo && kamera!=8) {
     const int wysnieba=80;
     GLfloat norm[3];
     GLfloat mat[3];
     int ilekaw=50;
     int rozkaw=33;
     float texrazy=80.0;
     int x,z;
     float y;

//     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
     glCullFace(GL_BACK);
     glEnable(GL_CULL_FACE);

     glEnable(GL_FOG);
     glFogf (GL_FOG_START, 800.0);
     glFogf (GL_FOG_END, 1400.0);
     wlacz_teksture(32);
     glPushMatrix();

       glMatrixMode(GL_TEXTURE);
       glPushMatrix();
         glTranslatef(oo/3600.0, -oo/3500.0 - ooszyb, 0);
         glMatrixMode(GL_MODELVIEW);

         glNormal3f(0,-1,0);

         glEnable(GL_COLOR_MATERIAL);
         glColor3f(fogColor[0], fogColor[1], fogColor[2]);
         for (x=-ilekaw; x<ilekaw;x++) {
            glBegin(GL_TRIANGLE_STRIP);
               for (z=-ilekaw;z<ilekaw; z++) {
                  if (x==0 && z==0)
                  {
                     y=wysnieba;
                  } else
                     y = wysnieba- sqrt(x*x+z*z)*5.0;
                  glTexCoord2f(x/texrazy,z/texrazy);		glVertex3f( x*rozkaw, y, z*rozkaw);

                  if (x==0 && z==0)
                  {
                     y=wysnieba;
                  } else
                     y = wysnieba- sqrt((x+1)*(x+1)+z*z)*5.0;
                  glTexCoord2f((x+1)/texrazy,z/texrazy);  glVertex3f( (x+1)*rozkaw, y, z*rozkaw);

               }
            glEnd();
         }

         glMatrixMode(GL_TEXTURE);
       glPopMatrix();
       glMatrixMode(GL_MODELVIEW);

     glPopMatrix();
     wylacz_teksture();

     glFogf (GL_FOG_START, 50.0);
     glFogf (GL_FOG_END, 80.0);

     glCullFace(GL_BACK);

     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }

  rysuj_teren();
  rysuj_obiekty_scenerii(0);

/*
   float x = -sin(oo/60.0)*7.0;
   float z = cos(oo/60.0)*7.0+4;
   float yy = gdzie_y_zwoda(x,z);
   BMForm->Label6->Caption=FloatToStrF(x, ffGeneral,3,3)+" x "+FloatToStrF(z, ffGeneral,3,3);
   BMForm->Label7->Caption=FloatToStrF(yy, ffGeneral,3,3);
   glPushMatrix();
   glTranslatef(x, yy, z);
   gluSphere(kula, 1.0, 10, 10);
   glPopMatrix();*/
}


//-----------------------------------------------------------------------------
void rysuj_samolot(int a)
{
	//parametry materialu smigla
	GLfloat mat_smi_ka[] = {0.30, 0.30, 0.26, 1.0};
	GLfloat mat_smi_kd[] = {0.30, 0.30, 0.26, 1.0};
	GLfloat mat_smi_ks[] = {0.60, 0.60, 0.50, 1.0};

	//parametry materialu kola
	GLfloat mat_kol_ka[] = {0.10, 0.10, 0.10, 1.0};
	GLfloat mat_kol_kd[] = {0.10, 0.10, 0.10, 1.0};
	GLfloat mat_kol_ks[] = {0.40, 0.40, 0.40, 1.0};

	//parametry materialu srodka kol
	GLfloat mat_sko_ka[] = {0.70, 0.70, 0.70, 1.0};
	GLfloat mat_sko_kd[] = {0.70, 0.70, 0.70, 1.0};
	GLfloat mat_sko_ks[] = {0.70, 0.70, 0.70, 1.0};

	//parametry materialu podpor
	GLfloat mat_pod_ka[] = {0.40, 0.40, 0.50, 1.0};
	GLfloat mat_pod_kd[] = {0.40, 0.40, 0.50, 1.0};
	GLfloat mat_pod_ks[] = {0.80, 0.80, 0.80, 1.0};

	//parametry materialu szalika
	GLfloat mat_sza_ka[] = {0.60, 0.60, 0.60, 1.0};
	GLfloat mat_sza_kd[] = {0.80, 0.80, 0.80, 1.0};
	GLfloat mat_sza_ks[] = {1.00, 1.00, 1.00, 1.0};

   //pusty material, bialy
	GLfloat mat_pusty[] = {0.70, 0.70, 0.70, 1.0};

	GLfloat norm[3];
    GLdouble eqn[4] = {0.0,-1.0, 0.0, 0.0};

	int b,b1;

   int tn;
   if (a==0) tn=0; else tn=1;

/*	GLUquadricObj *kula;
   kula = gluNewQuadric();*/
   gluQuadricDrawStyle(kula, GLU_FILL);
   gluQuadricNormals(kula, GLU_SMOOTH);
   gluQuadricOrientation(kula, GLU_OUTSIDE);
   gluQuadricTexture(kula, GLU_TRUE);

   //glPolygonMode(GL_BACK, GL_POINT);
   glPolygonMode(GL_FRONT, GL_FILL);
   glCullFace(GL_BACK);

	glPushMatrix();
		glTranslatef(samolot[a].x, samolot[a].y, samolot[a].z);

		glRotatef(-samolot[a].dx*70, 0.0, 0.5, 1.0); //obrot wokol osi przy przesuwaniu w bok

      //obrot w pionie pod wplywem szybkosci pionowej
		if ((a!=sterowanie) && (samolot[a].dz>0)) glRotatef(-samolot[a].dy*60, 1.0, 0.0, 0.0);
                                           else glRotatef(samolot[a].dy*60, 1.0, 0.0, 0.0);

		if ((a!=sterowanie) && (samolot[a].dz>0))
			glRotatef(180, 0, 1,0);

		glScalef(samolot[a].rozm,samolot[a].rozm,samolot[a].rozm);

		//kadlub
		if (a==sterowanie) //gracz
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_sam_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_sam_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_sam_ks);
		} else { //inni
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_sam2_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_sam2_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_sam2_ks);
		}

		glMaterialf(GL_FRONT, GL_SHININESS, 80);
		//przod
		glPushMatrix();
			glScalef(0.3, 0.3, 0.2);
			eqn[1] = -1.0;
			glPushMatrix();
				glRotatef(90.0, 1.0, 0.0, 0.0);
				glRotatef(180.0, 0.0, 1.0, 0.0);
				glClipPlane (GL_CLIP_PLANE0, eqn); //obciecie gory
				glEnable (GL_CLIP_PLANE0);
				gluSphere(kula, 0.65, 8, 12);
				glDisable (GL_CLIP_PLANE0);
			glPopMatrix();
		glPopMatrix();
      wlacz_teksture(28+tn);
		//tyl
		glPushMatrix();
			glRotatef(-8.0, 1.0, 0.0, 0.0);
         glTranslatef(0,0,-0.02);
			glScalef(0.3, 0.3, 1.83);
			eqn[1] = -1.0;
			glPushMatrix();
				glRotatef(-89.0, 1.0, 0.0, 0.0);
				glClipPlane (GL_CLIP_PLANE0, eqn); //obciecie gory
				glEnable (GL_CLIP_PLANE0);
				gluSphere(kula, 0.65, 12, 12);
				glDisable (GL_CLIP_PLANE0);
			glPopMatrix();
		glPopMatrix();
      wylacz_teksture();

		//kola
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			//tylna podpora
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_kol_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_kol_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_kol_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 70);

			glPushMatrix();
				glTranslatef(0.0, 0.07, 1.05);
				glRotatef(120, 1, 0, 0);
				klocek(0.14, 0.015, 0.015);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, 0.11, 1.11);
				glRotatef(180, 1, 0, 0);
				klocek(0.08, 0.008, 0.008);
			glPopMatrix();

			//podpory zewnetrzne
			for (b=-1; b<=1; b+=2)
			{
				for (b1=0; b1<=1; b1++)
				{
					glPushMatrix();
						glTranslatef(0.15*b, -0.34, 0.15);
						glRotatef(-30.0*b1-80, 1.0, 0.0, 0.0);
						glRotatef(12.0*b, 0.0, 0.0, 1.0);
						//klocek(0.25, 0.01, 0.01);
				      gluCylinder(kula, 0.01, 0.01, 0.25, 6,1);
					glPopMatrix();
				}
			}


			//os
			glPushMatrix();
				//glTranslatef(0.0, -0.34, 0.15);
			   glTranslatef(0.18, -0.34, 0.15);
				glRotatef(-90.0, 0.0, 1.0, 0.0);
				//klocek(0.02, 0.18, 0.01);
		      gluCylinder(kula, 0.01, 0.01, 0.36, 6,1);
			glPopMatrix();

			//kola
         glPolygonMode(GL_FRONT, GL_FILL);
         glPolygonMode(GL_BACK, GL_FILL);
         glDisable(GL_CULL_FACE);
			for (b=-1; b<=1; b+=2)
			{
				glPushMatrix();
					glTranslatef(0.18*b, -0.34, 0.15);
					glRotatef(90.0*b, 0.0, 1.0, 0.0);

					glMaterialfv(GL_FRONT, GL_AMBIENT, mat_kol_ka);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_kol_kd);
					glMaterialfv(GL_FRONT, GL_SPECULAR, mat_kol_ks);
					glMaterialf(GL_FRONT, GL_SHININESS, 5);
					//glutSolidTorus(0.015, 0.08, 4, 15);
               gluDisk(kula, 0.08, 0.095, 12, 1);
//					glScalef(1.0, 1.0, 0.1);

					glMaterialfv(GL_FRONT, GL_AMBIENT, mat_sko_ka);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_sko_kd);
					glMaterialfv(GL_FRONT, GL_SPECULAR, mat_sko_ks);
					glMaterialf(GL_FRONT, GL_SHININESS, 50);
//               gluSphere(kula, 0.08, 10, 4);
               gluDisk(kula, 0.00, 0.08, 12, 1);

				glPopMatrix();
			}
         glEnable(GL_CULL_FACE);
		glPopAttrib();

		//skrzydla
		glPushMatrix(); //gorne
		   glPushAttrib(GL_ALL_ATTRIB_BITS);
         wlacz_teksture(26+tn);
         glDisable(GL_COLOR_MATERIAL);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_pusty);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_pusty);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_pusty);

			glTranslatef(0.0, 0.35, 0.11);
			texplat(0.03, 1.4, 0.13, 0.08,
                  0.0, 1.0, 0.75 , 1.0, true, false, false);
			glTranslatef(0.0, 0.0, 0.15);
         texplatd(0.03, 0.6, 0.03, 0.0,
                  0.25, 0.75, 0.75 , 1.0, true, false, true);

			//lotki
			for (b=-1; b<=1; b+=2)
			{
				glPushMatrix();
					glTranslatef(1.0*b, 0.015, -0.03);
					glRotatef(90.0-samolot[a].lotkidy*80, 1.0, 0.0, 0.0);
					texplatd(0.06, 0.4, 0.010, 0.02,
                        0.25, 0.65, 0.75 , 1.0, true, false, true);
				glPopMatrix();
			}
		glPopMatrix();
		glPushMatrix(); //dolne
			glTranslatef(0.0, -0.12, 0.21);
			texplat(0.03, 1.4, 0.13, 0.08,
                  0.0, 1.0, 0.75 , 1.0, true, false, false);
			glTranslatef(0.0, 0.0, 0.15);
         texplatd(0.03, 0.6, 0.03, 0.0,
                  0.25, 0.75, 0.75 , 1.0, true, false, true);
			//lotki
			for (b=-1; b<=1; b+=2)
			{
				glPushMatrix();
					glTranslatef(1.0*b, 0.015, -0.03);
					glRotatef(90.0-samolot[a].lotkidy*80, 1.0, 0.0, 0.0);
					texplatd(0.06, 0.4, 0.010, 0.02,
                        0.25, 0.65, 0.75 , 1.0, true, false, true);
				glPopMatrix();
			}
         wylacz_teksture();
		   glPopAttrib();
		glPopMatrix();

		//podpory zewnetrzne
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_pod_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_pod_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_pod_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 100);
			for (int b2=0; b2<=1; b2++)
			{
             for (b=-1; b<=1; b+=2)
             {
                for (b1=0; b1<=1; b1++)
                {
                   glPushMatrix();
                      glTranslatef((1.1-b2*0.6)*b, -0.11, 0.30-b1*0.16);
                      glRotatef(-12.0-90, 1.0, 0.0, 0.0);
                      gluCylinder(kula, 0.01, 0.01, 0.47, 6,1);
                   glPopMatrix();
                }
             }
         }

         //linki X miedzy podporami zewnetrznymi
         for (int b2=0; b2<=1; b2++)
         {
             for (b=-1; b<=1; b+=2)
             {
                for (b1=0; b1<=1; b1++)
                {
                   glPushMatrix();
                      glTranslatef((1.1-b2*0.6)*b, -0.11, 0.30-b1*0.16);
                      glRotatef(-12.0-90, 1.0, 0.0, 0.0);
                      if (b2==0) glRotatef(-51.5*b, 0.0, 1.0, 0.0);
                            else glRotatef(51.5*b, 0.0, 1.0, 0.0);
                      gluCylinder(kula, 0.004, 0.004, 0.75, 3,1);
                   glPopMatrix();
                }
             }
         }

         //linki X miedzy podporami wewnetrznymi
         for (int b2=0; b2<=1; b2++)
         {
             for (b=-1; b<=1; b+=2)
             {
                for (b1=0; b1<=1; b1++)
                {
                   glPushMatrix();
                      glTranslatef((0.5-b2*0.35)*b, -0.11, 0.30-b1*0.16);
                      glRotatef(-12.0-90, 1.0, 0.0, 0.0);
                      if (b2==0) glRotatef(-(25.5+b2*10.0)*b, 0.0, 1.0, 0.0);
                            else glRotatef((25.5+b2*10.0)*b, 0.0, 1.0, 0.0);
                      gluCylinder(kula, 0.004, 0.004, 0.53+b2*0.08, 3,1);
                   glPopMatrix();
                }
             }
         }

         //linki pojedyncze na koncach skrzydel
         for (b=-1; b<=1; b+=2)
         {
             glPushMatrix();
                glTranslatef(1.1*b, -0.11, 0.30-0.16);
                glRotatef(-81.0, 1.0, 0.0, 0.0);
                gluCylinder(kula, 0.004, 0.004, 0.45, 3,1);
             glPopMatrix();
         }

			//podpory wewnetrzne
			for (b=-1; b<=1; b+=2)
			{
				for (b1=0; b1<=1; b1++)
				{
					glPushMatrix();
						glTranslatef(0.15*b, 0.1, 0.22-b1*0.16);
						glRotatef(-25.0*b, 0.0, 0.0, 1.0);
						glRotatef(-90, 1.0, 0.0, 0.0);
						//klocek(0.25, 0.01, 0.01);
		            gluCylinder(kula, 0.01, 0.01, 0.28, 6,1);
					glPopMatrix();
				}
			}
		glPopAttrib();

		//ogon
		glPushMatrix();
			glTranslatef(0.0, 0.20, 1.05);
		   glPushAttrib(GL_ALL_ATTRIB_BITS);
         wlacz_teksture(26+tn);
         glDisable(GL_COLOR_MATERIAL);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_pusty);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_pusty);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_pusty);
			texplat(0.03, 0.5, 0.07, 0.09,
                 0.25,0.5,0.75,1.0, true,false,true);
			//lotki
			for (b=-1; b<=1; b+=2)
			{
				glPushMatrix();
					glTranslatef(0.3*b, 0.015, 0.07);
					glRotatef(90.0-samolot[a].lotkidy*80, 1.0, 0.0, 0.0);
					texplatd(0.09, 0.2, 0.01, 0.03,
                        0.25, 0.55, 0.75 , 1.0, true, false, true);
				glPopMatrix();
			}

			//pion
			glTranslatef(0.0,-0.05, 0.00);
			glPushMatrix();
			   glRotatef(90.0, -1.0, 0.0, 0.0);
			   glRotatef(90.0, 0.0, 1.0, 0.0);
            glTranslatef(-0.09,-0.065, 0.00);
            texplatd(0.10, 0.1, 0.01,0.07,
                 0.25,0.5,0.75,1.0, true,false,true);
			glPopMatrix();
			//klocek(0.2, 0.01, 0.065);
			//lotka
			glPushMatrix();
				glTranslatef(0.0, 0.08, 0.065);
				glRotatef(90.0, 1.0, 0.0, 0.0);
				glRotatef(samolot[a].lotkidx*65, 0.0, 0.0, 1.0);

				glRotatef(90.0, 0.0, 1.0, 0.0);
				texplatd(0.11, 0.110, 0.006, 0.04,
                     0.0 , 0.25 , 0.0 , 0.25, false, true, true);

				//texplatd(0.09, 0.008, 0.110, 0.03);
			glPopMatrix();
         wylacz_teksture();
		   glPopAttrib();

		glPopMatrix();

		//smiglo
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_smi_ka);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_smi_kd);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_smi_ks);
		glMaterialf(GL_FRONT, GL_SHININESS, 128);
      glDisable(GL_CULL_FACE);
			glPushMatrix();

				//1
				glTranslatef(0.0, 0.0, -0.01);
				glRotatef(180.0, 0.0, 1.0, 0.0);
				glRotatef(samolot[a].smiglo, 0.0, 0.0, 1.0);
				glRotatef(90.0, 0.0, 0.0, 1.0);
				gluCylinder(kula, 0.05, 0, 0.24, 6,6);

				//2
				glTranslatef(0.0, 0.0, 0.17);
				glRotatef(90.0, 1.0, 0.0, 0.0);

				glPushMatrix();
					for (b=0; b<=1; b++)
					{
						glRotatef(180.0, 0.0, 1.0, 0.0);
						glBegin(GL_POLYGON);
							vertex_norm( 0.02, 0.0 , 0.0 );
							vertex_norm( 0.04, 0.02,-0.10);
							vertex_norm( 0.0 , 0.0 ,-0.35);
							vertex_norm(-0.04,-0.02,-0.10);
							vertex_norm(-0.02, 0.0 , 0.0 );
						glEnd();
					}
				glPopMatrix();

				//przezroczyste kolko na smigle
            if ( (a!=sterowanie) ||
                 (a==sterowanie &&
                  ( (gracz.fuel>0 && szybkosc>=0.05) || (gracz.fuel<=0 && szybkosc>=0.20) )
                 )
               ) {
              glEnable(GL_BLEND);
              glDepthMask(GL_FALSE);
              glPushMatrix();
                glPolygonMode(GL_FRONT, GL_FILL);
                glPolygonMode(GL_BACK, GL_FILL);
                glDisable(GL_CULL_FACE);
                glEnable(GL_COLOR_MATERIAL);
                   glColor4f(mat_smi_kd[0],mat_smi_kd[1],mat_smi_kd[2],0.3);
                   glBegin(GL_POLYGON);
                   for (b=0; b<=11; b++)
                   {
                      vertex_norm(sin(b*(M_PI/180)*30)*0.35, 0.0 , cos(b*(M_PI/180)*30)*0.35 );
                   }
                   glEnd();
                glDisable(GL_COLOR_MATERIAL);
                glEnable(GL_CULL_FACE);
              glPopMatrix();
              glDepthMask(GL_TRUE);
              glDisable(GL_BLEND);
            }
			glPopMatrix();
      glEnable(GL_CULL_FACE);
		glPopAttrib();

		//dzialka
		glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_kol_ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_kol_kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_kol_ks);
        glMaterialf(GL_FRONT, GL_SHININESS, 128);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        glDisable(GL_CULL_FACE);
        for (int a1=-1; a1<=1; a1+=2) {
           glPushMatrix();
              glTranslatef(0.10*a1, 0.21, 0.25);
              glRotatef(180.0, 0.0, 1.0, 0.0);
              glRotatef(90.0, 0.0, 0.0, 1.0);
              gluCylinder(kula, 0.04, 0.04, 0.20, 8,2);
              gluDisk(kula, 0, 0.04, 8,2);

              float dlugoscdzialka=0.2-samolot[a].strzalani*0.01;

              glTranslatef(0.0, 0.0, 0.20);
              gluDisk(kula, 0, 0.04, 8,2);
              gluCylinder(kula, 0.02, 0.02, dlugoscdzialka, 8,2);

              if (samolot[a].strzalani>0) {
                 glPushAttrib(GL_ALL_ATTRIB_BITS);
                 glPolygonMode(GL_FRONT, GL_FILL);
                 glEnable(GL_BLEND);
                 glDepthMask(GL_FALSE);
                 glDisable(GL_CULL_FACE);
                 glPushMatrix();
                    glTranslatef(0.0, 0.0, dlugoscdzialka-0.02);
                    glRotatef(90, 1, 0, 0);
                    glRotatef(oo*13+samolot[a].strzalani*27, 0, 1, 0);
                    float sk= 0.05+samolot[a].strzalani/22.0;
                    glScalef(sk, sk, sk);
                    glEnable(GL_COLOR_MATERIAL);
                    glColor4f(1,1,1,0.05+samolot[a].strzalani/13.0);
                    glCallList(listbase+ob_ogien+1);
                 glPopMatrix();
                 glPopAttrib();
              }


           glPopMatrix();
        }
        glEnable(GL_CULL_FACE);
		glPopAttrib();

      //pilot
		glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_kol_ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_kol_kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_kol_ks);
        glMaterialf(GL_FRONT, GL_SHININESS, 128);
           glPushMatrix();

              glTranslatef(0.0, 0.28, 0.34);
              gluSphere(kula, 0.06, 8,6);

           glPopMatrix();
		glPopAttrib();

      //szalik pilota
		glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_CULL_FACE);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_sza_ka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_sza_kd);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_sza_ks);
        glMaterialf(GL_FRONT, GL_SHININESS, 1);

        glPushMatrix();
           glTranslatef(0.0, 0.24, 0.34);
           glRotatef(-90, 1.0, 0.0, 0.0);
           wlacz_teksture(30+tn);
           gluCylinder(kula, 0.05, 0.044, 0.04, 8,2);
        glPopMatrix();

        glPushMatrix();
           glTranslatef(0.0, 0.24, 0.34);
           glBegin(GL_TRIANGLE_STRIP);
           for (int s=0; s<szalikdlug; s++)
           {
              GLfloat wek[3];
              wek[0]=samolot[a].szaliknormx[s];
              wek[1]=samolot[a].szaliknormy[s];
              wek[2]=0;
              normalize0(wek);
              glNormal3fv(wek);
              glTexCoord2f((float)s/szalikdlug,0);
              glVertex3f(samolot[a].szalikx[s],samolot[a].szaliky[s],samolot[a].szalikz[s]);
              glTexCoord2f((float)s/szalikdlug,1);
              glVertex3f(samolot[a].szalikx[s],samolot[a].szaliky[s]+0.04,samolot[a].szalikz[s]);
           }
           glEnd();
        glPopMatrix();
        wylacz_teksture();
        glEnable(GL_CULL_FACE);
		glPopAttrib();

	glPopMatrix();
}

//-----------------------------------------------------------------------------
void vertexXZ(int a, float x, float z)
{
	x*=samolot[a].rozm;
	z*=samolot[a].rozm*(1-fabs(samolot[a].dy));
	glVertex3f(x , gdzie_y_zwoda(samolot[a].x+x,samolot[a].z+z)+0.2 ,z);
}

//-----------------------------------------------------------------------------
void rysuj_cien(int a)
{
	GLfloat cien_ka[] = {0.00, 0.00, 0.00, 0.5};
	float jas;

	jas = 0.8 - ( samolot[a].y - gdzie_y_zwoda(samolot[a].x,samolot[a].z) ) / 29.0;
	if (jas>0)
	{
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
	//		glEnable(GL_COLOR_MATERIAL);


		cien_ka[3] = jas;

		glMaterialfv(GL_FRONT, GL_AMBIENT, cien_ka);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cien_ka);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cien_ka);
		glMaterialf(GL_FRONT, GL_SHININESS, 0);

		glPushMatrix();
	//		glTranslatef(samolot[a].x, 0.0, samolot[a].z);

	/*		glRotatef(-samolot[a].dx*70, 0.0, 0.5, 1.0); //obrot wokol osi przy przesuwaniu w bok
			glRotatef(samolot[a].dy*60, 1.0, 0.0, 0.0); //obrot w pionie pod wplywem szybkosci pionowej
	*/
	//		glScalef(samolot[a].rozm,samolot[a].rozm,samolot[a].rozm);

			glTranslatef(samolot[a].x, 0, samolot[a].z);
			if ((a!=sterowanie) && (samolot[a].dz>0))
				glRotatef(180, 0, 1,0);

			glBegin(GL_POLYGON);
				glNormal3f(0.0, 1.0, 0.0);
				//dlug=1.2, szer=1.4/0.12
				vertexXZ(a, -0.2 ,-0.2 );
				vertexXZ(a, -0.2 , 0.0 );
				vertexXZ(a, -0.8 +fabs(samolot[a].dx/1.6), 0.0 );
				vertexXZ(a, -1.4 +fabs(samolot[a].dx/1.6), 0.0 );
				vertexXZ(a, -1.4 +fabs(samolot[a].dx/1.6), 0.3 );
				vertexXZ(a, -0.8 +fabs(samolot[a].dx/1.6), 0.3 );

				vertexXZ(a, -0.15, 0.3 );
				vertexXZ(a, -0.15, 1.2 );

				vertexXZ(a,  0.15, 1.2 );
				vertexXZ(a,  0.15, 0.3 );

				vertexXZ(a,  0.8 -fabs(samolot[a].dx/1.6), 0.3 );
				vertexXZ(a,  1.4 -fabs(samolot[a].dx/1.6), 0.3 );
				vertexXZ(a,  1.4 -fabs(samolot[a].dx/1.6), 0.0 );
				vertexXZ(a,  0.8 -fabs(samolot[a].dx/1.6), 0.0 );
				vertexXZ(a,  0.2 , 0.0 );
				vertexXZ(a,  0.2 ,-0.2 );
			glEnd();

			glBegin(GL_POLYGON);
				vertexXZ(a, -0.15, 1.2 );
				vertexXZ(a, -0.4 +fabs(samolot[a].dx/5.3), 1.25);
				vertexXZ(a, -0.4 +fabs(samolot[a].dx/5.3), 1.45);

				vertexXZ(a,  0.0 , 1.44 );

				vertexXZ(a,  0.4 -fabs(samolot[a].dx/5.3), 1.45);
				vertexXZ(a,  0.4 -fabs(samolot[a].dx/5.3), 1.25);
				vertexXZ(a,  0.15, 1.2 );
			glEnd();

/*
				vertexXZ(a, -0.2 ,-0.2 );
				vertexXZ(a, -0.2 , 0.0 );
				vertexXZ(a, -0.8 +fabs(samolot[a].dx/1.3), 0.0 );
				vertexXZ(a, -1.4 +fabs(samolot[a].dx/1.3), 0.0 );
				vertexXZ(a, -1.4 +fabs(samolot[a].dx/1.3), 0.3 );
				vertexXZ(a, -0.8 +fabs(samolot[a].dx/1.3), 0.3 );
				vertexXZ(a, -0.15, 0.3 );
				vertexXZ(a, -0.15, 1.2 );
				vertexXZ(a, -0.4 +fabs(samolot[a].dx/2.3), 1.3 );
				vertexXZ(a, -0.4 +fabs(samolot[a].dx/2.3), 1.45);

				vertexXZ(a,  0.0 , 1.4 );

				vertexXZ(a,  0.4 -fabs(samolot[a].dx/4.3), 1.45);
				vertexXZ(a,  0.4 -fabs(samolot[a].dx/4.3), 1.3 );
				vertexXZ(a,  0.15, 1.2 );
				vertexXZ(a,  0.15, 0.3 );
				vertexXZ(a,  0.8 -fabs(samolot[a].dx/4.3), 0.3 );
				vertexXZ(a,  1.4 -fabs(samolot[a].dx/4.3), 0.3 );
				vertexXZ(a,  1.4 -fabs(samolot[a].dx/4.3), 0.0 );
				vertexXZ(a,  0.8 -fabs(samolot[a].dx/4.3), 0.0 );
				vertexXZ(a,  0.2 , 0.0 );
				vertexXZ(a,  0.2 ,-0.2 );
*/
		glPopMatrix();

	//	glDisable(GL_COLOR_MATERIAL);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

}

//-----------------------------------------------------------------------------
void rysuj_samoloty(bool celowniki=false)
{
	int a;

	glPushMatrix();

	for (a=0; a<ils; a++)
		if (samolot[a].jest==1)
		{
			glPushMatrix();

         //wskaznik od gracza w strone celu
         if (ustawienia.wskazniki &&
             a==sterowanie && gracz.jaki_cel_pokazuje>=0) {
            float gdziex,gdziey,gdziez;
            float katx,katy;
            float j;

            if (gracz.jaki_cel_pokazuje==0) {
               gdziex=samolot[gracz.ktory_cel_pokazuje].x;
               gdziey=samolot[gracz.ktory_cel_pokazuje].y;
               gdziez=samolot[gracz.ktory_cel_pokazuje].z;
            } else
            if (gracz.jaki_cel_pokazuje==1) {
               gdziex=ruchome[gracz.ktory_cel_pokazuje].x;
               gdziey=ruchome[gracz.ktory_cel_pokazuje].y;
               gdziez=ruchome[gracz.ktory_cel_pokazuje].z;
            } else
            if (gracz.jaki_cel_pokazuje==2) {
               gdziex=gracz.gdziex_cel_pokazuje*dkrok-dx0;
               gdziey=teren[gracz.gdziex_cel_pokazuje][gracz.gdziez_cel_pokazuje].y;
               gdziez=(float) -gracz.gdziez_cel_pokazuje*dkrok+dz0 + fmod(dz0, dkrok);
            }

            katx = -jaki_to_katF(samolot[sterowanie].x-gdziex, samolot[sterowanie].z-gdziez);

            katy = 90-jaki_to_katF( sqrt( pow(samolot[sterowanie].x-gdziex,2) + pow(samolot[sterowanie].z-gdziez, 2)),
                                samolot[sterowanie].y-gdziey);

            j = sqrt( pow(samolot[sterowanie].x-gdziex,2) + pow(samolot[sterowanie].y-gdziey,2) + pow(samolot[sterowanie].z-gdziez, 2))/150.0;
            if (j>0.6) j=0.6;
            if (j<0.02) j=0.02;


            //BMForm->Label7->Caption = "X="+FloatToStr(katx);
            //BMForm->Label6->Caption = "Y="+FloatToStr(katy);

            glPushMatrix();
		         glTranslatef(samolot[sterowanie].x, samolot[sterowanie].y, samolot[sterowanie].z);

               glRotatef(katx, 0, 1, 0);
               glRotatef(katy, -1, 0, 0);

               glPushAttrib(GL_ALL_ATTRIB_BITS);
                 glEnable(GL_BLEND);
                 glDepthMask(GL_FALSE);

                 gluQuadricDrawStyle(kolo, GLU_FILL);
                 gluQuadricNormals(kolo, GLU_SMOOTH);
                 gluQuadricOrientation(kolo, GLU_OUTSIDE);
                 gluQuadricTexture(kolo, GLU_TRUE);

                 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_wskcel_ka);
                 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_wskcel_kd);
                 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_wskcel_ks);
                 glMaterialf(GL_FRONT, GL_SHININESS, 0);

                 glEnable(GL_COLOR_MATERIAL);
                 glColor4f(1,0.1,0.1, j);

                 glTranslatef(0,0,2);
                 gluCylinder(kula, 0.24, 0.01, j*5.0, 8,1);
                 glPushMatrix();
                   glRotatef(180,0,1,0);
                   gluDisk(kula, 0, 0.24, 8, 1);
                 glPopMatrix();

                 glDisable(GL_COLOR_MATERIAL);

                 //glEnable(GL_CULL_FACE);
                 glDepthMask(GL_TRUE);
                 glDisable(GL_BLEND);

               glPopAttrib();
            glPopMatrix();

         }


         if (!celowniki) {
             switch (samolot[a].rodzaj)
             {
                case 0: rysuj_samolot(a); break;
             }
         } else {

            //jesli glowny cel - rysuj celownik
            if (samolot[a].cel) {
               float celx = samolot[a].x,
                     cely = samolot[a].y,
                     celz = samolot[a].z,
                     celrozm=2;
               glPushMatrix();
               glPushAttrib(GL_ALL_ATTRIB_BITS);

               float viewMatrix[16];
               glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
               GLfloat right[3]={viewMatrix[0], viewMatrix[4], viewMatrix[8]};
               GLfloat up[3]={viewMatrix[1], viewMatrix[5], viewMatrix[9]};

               glEnable(GL_BLEND);
               glDisable(GL_LIGHTING);
               glDepthMask(GL_FALSE);
               glEnable(GL_COLOR_MATERIAL);
               glPolygonMode(GL_FRONT, GL_FILL);
               glCullFace(GL_BACK);

               if (ustawienia.mgla) glDisable(GL_FOG);

               glColor4f(1,0.5+sin(oo/4.0)*0.5,0.5+sin(oo/4.0)*0.5, 0.7);
               wlacz_teksture(2);
               glBegin(GL_QUADS);
                 glTexCoord2f(0.0, 0.0);
                 glVertex3f ((celx + (right[0] + up[0]) * -celrozm),(cely + (right[1] + up[1]) * -celrozm),(celz + (right[2] + up[2]) * -celrozm));
                 glTexCoord2f(1.0, 0.0);
                 glVertex3f ((celx + (right[0] - up[0]) * celrozm),(cely + (right[1] - up[1]) * celrozm),(celz + (right[2] - up[2]) * celrozm));
                 glTexCoord2f(1.0, 1.0);
                 glVertex3f ((celx + (right[0] + up[0]) * celrozm),(cely + (right[1] + up[1]) * celrozm),(celz + (right[2] + up[2]) * celrozm));
                 glTexCoord2f(0.0, 1.0);
                 glVertex3f ((celx + (up[0] - right[0]) * celrozm),(cely + (up[1] - right[1]) * celrozm),(celz + (up[2] - right[2]) * celrozm));
               glEnd();
               wylacz_teksture();

               if (ustawienia.mgla) glEnable(GL_FOG);

               glDisable(GL_COLOR_MATERIAL);
               glDepthMask(GL_TRUE);
               glDisable(GL_BLEND);



               glPopAttrib();
               glPopMatrix();

            }//if

         }//else
			glPopMatrix();
		}

	glPopMatrix ();
}

//-----------------------------------------------------------------------------
void rysuj_samoloty_cienie()
{
	int a;

	glPushMatrix();

	for (a=0; a<ils; a++)
		if (samolot[a].jest==1)
		{
			glPushMatrix();
			switch (samolot[a].rodzaj)
			{
				case 0: if (samolot[a].zniszczony==0 && samolot[a].y>=0) rysuj_cien(a); break;
			}
			glPopMatrix();
		}

	glPopMatrix ();
}

//-----------------------------------------------------------------------------
void vertexXZp(int a, float x, float z)
{
	x*=poc[a].rozm;
	z*=poc[a].rozm;
	glVertex3f(poc[a].x+x, gdzie_y_zwoda(poc[a].x+x, poc[a].z+z)+0.2 ,poc[a].z+z);
}

//-----------------------------------------------------------------------------
void rysuj_cien_poc(int a)
{
	GLfloat cien_ka[] = {0.00, 0.00, 0.00, 0.5};
	float jas;

	jas = 0.6 - ( poc[a].y - gdzie_y_zwoda(poc[a].x,poc[a].z) ) / 30.0;
	if (jas>0) 
	{
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
	//		glEnable(GL_COLOR_MATERIAL);


		cien_ka[3] = jas;

		glMaterialfv(GL_FRONT, GL_AMBIENT, cien_ka);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cien_ka);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cien_ka);
		glMaterialf(GL_FRONT, GL_SHININESS, 0);

		glPushMatrix();
	//		glTranslatef(poc[a].x, 0.0, poc[a].z);

	/*		glRotatef(-poc[a].dx*70, 0.0, 0.5, 1.0); //obrot wokol osi przy przesuwaniu w bok
			glRotatef(poc[a].dy*60, 1.0, 0.0, 0.0); //obrot w pionie pod wplywem szybkosci pionowej
	*/
	//		glScalef(poc[a].rozm,poc[a].rozm,poc[a].rozm);

			glBegin(GL_POLYGON);
				glNormal3f(0.0, 1.0, 0.0);
				vertexXZp(a, -1.5 , 0.0 );
				vertexXZp(a,  0.0 , 1.5 );
				vertexXZp(a,  1.5 , 0.0 );
				vertexXZp(a,  0.0 ,-1.5 );
			glEnd();

		glPopMatrix();

	//	glDisable(GL_COLOR_MATERIAL);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

}


//-----------------------------------------------------------------------------
void rysuj_pociski(int r)
{
	int a;

	glPushMatrix();
	for (a=0; a<maxpoc; a++)
		if (poc[a].jest==1 && poc[a].rodzaj==r)
		{
		  glPushMatrix();
			glTranslatef(poc[a].x, poc[a].y, poc[a].z);
         if (poc[a].rodzaj==0) {
           if (poc[a].obroty!=0.0)	glRotatef(poc[a].obroty, 0.0, 1.0, 0.0);
           if (poc[a].obrotx!=0.0)	glRotatef(poc[a].obrotx, 1.0, 0.0, 0.0);
           float p;
           if (poc[a].dx!=0 || poc[a].dy!=0 || poc[a].dz!=0)
              p=sqrt(poc[a].dx*poc[a].dx + poc[a].dy*poc[a].dy + poc[a].dz*poc[a].dz);
              else p=2;
           if (p<2) p=2;
			  glScalef(0.2, p/5.,0.2);
         } else {
           if (poc[a].obrotx!=0.0) {
               if (poc[a].dz<=0)
                  glRotatef(poc[a].obrotx, 1.0, 0.0, 0.0);
               else
                  glRotatef(poc[a].obrotx, -1.0, 0.0, 0.0);
           }
           if (poc[a].obroty!=0.0)	glRotatef(poc[a].obroty, 0.0, 1.0, 0.0);
           if (poc[a].obrotz!=0.0)	glRotatef(poc[a].obrotz, 0.0, 0.0, 1.0);
			  glScalef(poc[a].rozm, poc[a].rozm, poc[a].rozm);
         }
			glCallList(listbase+ob_pociski+poc[a].rodzaj);
		  glPopMatrix();

        if (poc[a].rodzaj==1) rysuj_cien_poc(a);
		}
	glPopMatrix();
}

//-----------------------------------------------------------------------------
void rysuj_wybuchy()
{
	int a;
   float viewMatrix[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
   GLfloat right[3]={viewMatrix[0], viewMatrix[4], viewMatrix[8]};
   GLfloat up[3]={viewMatrix[1], viewMatrix[5], viewMatrix[9]};

   glEnable(GL_BLEND);
   glDepthMask(GL_FALSE);
   glEnable(GL_COLOR_MATERIAL);
	glPolygonMode(GL_FRONT, GL_FILL);
//   glPolygonMode(GL_BACK, GL_POINT);
   glCullFace(GL_BACK);

   if (ustawienia.mgla) glDisable(GL_FOG);

	glPushMatrix();

	for (a=0; a<maxwyb; a++)
		if (wyb[a].jest==1)
		{
		  glPushMatrix();
         switch (wyb[a].rodzaj)
         {
           case 0: //kula wybuchu
             glPushAttrib(GL_ALL_ATTRIB_BITS);
	          glPolygonMode(GL_FRONT, GL_FILL);
             glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
             {
               //float kr=wyb[a].r-(0.20-wyb[a].przezr/5.0);
               //if (kr<0) kr=0;
               float kg=wyb[a].g-(0.31-wyb[a].przezr/3.0);
               if (kg<0) kg=0;
               glColor4f(wyb[a].r, kg, wyb[a].b, wyb[a].przezr);
             }
			    glTranslatef(wyb[a].x, wyb[a].y, wyb[a].z);
             if (wyb[a].obrot!=0.0)	glRotatef(wyb[a].obrot, 1.0, 0.0, 0.0);
             glScalef(wyb[a].rozm, wyb[a].rozm, wyb[a].rozm);
             glCallList(listbase+ob_wybuchy);
             glEnable(GL_CULL_FACE);
             glPopAttrib();
           break;
           case 1: //sprajt dymu
             glColor4f(wyb[a].r, wyb[a].g, wyb[a].b, wyb[a].przezr);
             wlacz_teksture(9);
             glBegin(GL_QUADS);
               glTexCoord2f(0.0, 0.0);
               glVertex3f ((wyb[a].x + (right[0] + up[0]) * -wyb[a].rozm),(wyb[a].y + (right[1] + up[1]) * -wyb[a].rozm),(wyb[a].z + (right[2] + up[2]) * -wyb[a].rozm));
               glTexCoord2f(1.0, 0.0);
               glVertex3f ((wyb[a].x + (right[0] - up[0]) * wyb[a].rozm),(wyb[a].y + (right[1] - up[1]) * wyb[a].rozm),(wyb[a].z + (right[2] - up[2]) * wyb[a].rozm));
               glTexCoord2f(1.0, 1.0);
               glVertex3f ((wyb[a].x + (right[0] + up[0]) * wyb[a].rozm),(wyb[a].y + (right[1] + up[1]) * wyb[a].rozm),(wyb[a].z + (right[2] + up[2]) * wyb[a].rozm));
               glTexCoord2f(0.0, 1.0);
               glVertex3f ((wyb[a].x + (up[0] - right[0]) * wyb[a].rozm),(wyb[a].y + (up[1] - right[1]) * wyb[a].rozm),(wyb[a].z + (up[2] - right[2]) * wyb[a].rozm));
	          glEnd();
             wylacz_teksture();
           break;
           case 2: //sprajt wybuchu
             glPushAttrib(GL_ALL_ATTRIB_BITS);
             glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
             //glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA);
     //        if (ustawienia.mgla) glDisable(GL_FOG);
             glColor4f(wyb[a].r, wyb[a].g, wyb[a].b, wyb[a].przezr);
             wlacz_teksture(8);
             glBegin(GL_QUADS);
               glTexCoord2f(0.0, 0.0);
               glVertex3f ((wyb[a].x + (right[0] + up[0]) * -wyb[a].rozm),(wyb[a].y + (right[1] + up[1]) * -wyb[a].rozm),(wyb[a].z + (right[2] + up[2]) * -wyb[a].rozm));
               glTexCoord2f(1.0, 0.0);
               glVertex3f ((wyb[a].x + (right[0] - up[0]) * wyb[a].rozm),(wyb[a].y + (right[1] - up[1]) * wyb[a].rozm),(wyb[a].z + (right[2] - up[2]) * wyb[a].rozm));
               glTexCoord2f(1.0, 1.0);
               glVertex3f ((wyb[a].x + (right[0] + up[0]) * wyb[a].rozm),(wyb[a].y + (right[1] + up[1]) * wyb[a].rozm),(wyb[a].z + (right[2] + up[2]) * wyb[a].rozm));
               glTexCoord2f(0.0, 1.0);
               glVertex3f ((wyb[a].x + (up[0] - right[0]) * wyb[a].rozm),(wyb[a].y + (up[1] - right[1]) * wyb[a].rozm),(wyb[a].z + (up[2] - right[2]) * wyb[a].rozm));
	          glEnd();
             wylacz_teksture();
      //       if (ustawienia.mgla) glEnable(GL_FOG);
             glPopAttrib();
           break;
           case 3: //sprajt ziemi
             glColor4f(wyb[a].r, wyb[a].g, wyb[a].b, wyb[a].przezr);
             wlacz_teksture(13);
             glBegin(GL_QUADS);
               glTexCoord2f(0.0, 0.0);
               glVertex3f ((wyb[a].x + (right[0] + up[0]) * -wyb[a].rozm),(wyb[a].y + (right[1] + up[1]) * -wyb[a].rozm),(wyb[a].z + (right[2] + up[2]) * -wyb[a].rozm));
               glTexCoord2f(1.0, 0.0);
               glVertex3f ((wyb[a].x + (right[0] - up[0]) * wyb[a].rozm),(wyb[a].y + (right[1] - up[1]) * wyb[a].rozm),(wyb[a].z + (right[2] - up[2]) * wyb[a].rozm));
               glTexCoord2f(1.0, 1.0);
               glVertex3f ((wyb[a].x + (right[0] + up[0]) * wyb[a].rozm),(wyb[a].y + (right[1] + up[1]) * wyb[a].rozm),(wyb[a].z + (right[2] + up[2]) * wyb[a].rozm));
               glTexCoord2f(0.0, 1.0);
               glVertex3f ((wyb[a].x + (up[0] - right[0]) * wyb[a].rozm),(wyb[a].y + (up[1] - right[1]) * wyb[a].rozm),(wyb[a].z + (up[2] - right[2]) * wyb[a].rozm));
	          glEnd();
             wylacz_teksture();
           break;
           case 4: //sprajt plusku
             glColor4f(1,1,1, wyb[a].przezr);
             wlacz_teksture(20);
             glBegin(GL_QUADS);
               glTexCoord2f(0.0, 0.0);
               glVertex3f ((wyb[a].x + (right[0] + up[0]) * -wyb[a].rozm),(wyb[a].y + (right[1] + up[1]) * -wyb[a].rozm),(wyb[a].z + (right[2] + up[2]) * -wyb[a].rozm));
               glTexCoord2f(1.0, 0.0);
               glVertex3f ((wyb[a].x + (right[0] - up[0]) * wyb[a].rozm),(wyb[a].y + (right[1] - up[1]) * wyb[a].rozm),(wyb[a].z + (right[2] - up[2]) * wyb[a].rozm));
               glTexCoord2f(1.0, 1.0);
               glVertex3f ((wyb[a].x + (right[0] + up[0]) * wyb[a].rozm),(wyb[a].y + (right[1] + up[1]) * wyb[a].rozm),(wyb[a].z + (right[2] + up[2]) * wyb[a].rozm));
               glTexCoord2f(0.0, 1.0);
               glVertex3f ((wyb[a].x + (up[0] - right[0]) * wyb[a].rozm),(wyb[a].y + (up[1] - right[1]) * wyb[a].rozm),(wyb[a].z + (up[2] - right[2]) * wyb[a].rozm));
	          glEnd();
             wylacz_teksture();
           break;
         }
		  glPopMatrix();
		}
	glPopMatrix();

   if (ustawienia.mgla) glEnable(GL_FOG);

   glDisable(GL_COLOR_MATERIAL);
   glDepthMask(GL_TRUE);
   glDisable(GL_BLEND);

}


//-----------------------------------------------------------------------------
void rysuj_wode()
{
	float x,z,mn, px,pz;

	glPushMatrix();
		wlacz_teksture_env(0);
/*		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glRotatef(oo, 0.0, 0.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
*/
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
//		glEnable(GL_COLOR_MATERIAL);
		glMaterialfv(GL_FRONT, GL_AMBIENT, material_ka);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material_kd);
		glMaterialfv(GL_FRONT, GL_SPECULAR, material_ks);
		glMaterialf(GL_FRONT, GL_SHININESS, 120);
//      glPolygonMode(GL_BACK, GL_POINT);
      glPolygonMode(GL_FRONT, GL_FILL);
      glCullFace(GL_BACK);

		switch (ustawienia.rodzajwody)
		{
		case 0: //brak
		break;
		case 1:	/*	woda falujaca	*/
         #define minwys 0.5
         for (x=0; x<maxszer-1;x++) {
			   for (z=0;z<wodailez0; z++) {
                if (
                    teren[(int)x][(int)(z+zod)].jestwoda==1
                  ) {

                  if ((z==0) ||
                      (teren[(int)x][(int)(z+zod-1)].jestwoda==1)
                     )
			            glBegin(GL_TRIANGLE_STRIP);

						glNormal3fv(woda[(int)x][(int)z  ].norm);

                  if (x==0) {
                     px=-ilebok*dkrok-dx0;
                  } else {
					     px=x*dkrok-dx0;
                  }
					   pz=(float) -(z+zod)*dkrok+dz0 + fmod(dz0, dkrok);

						glVertex3f(px, woda[(int)x][(int)z  ].y, pz);

						glNormal3fv(woda[(int)x+1][(int)z  ].norm);
						//px=(x+1)*wodakrok-dx0;
                  if (x==maxszer-2) {
                     px=(maxszer+ilebok)*dkrok-dx0;
                  } else {
					     px=(x+1)*dkrok-dx0;
                  }
						glVertex3f(px, woda[(int)x+1][(int)z].y, pz);

                  if ((z==wodailez0-1) || (teren[(int)x][(int)(z+zod+1)].jestwoda==0))
				         glEnd();

                }
				}
			}
		break;
		}

//		glDisable(GL_COLOR_MATERIAL);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		wylacz_teksture();

	glPopMatrix();
}

//-----------------------------------------------------------------------------
void vertexXZs(int a, float x, float z)
{
	x*=smiec[a].rx;
	z*=smiec[a].ry;
	glVertex3f(smiec[a].x+x, gdzie_y_zwoda(smiec[a].x+x, smiec[a].z+z)+0.2 ,smiec[a].z+z);
}

//-----------------------------------------------------------------------------
void rysuj_cien_smiec(int a)
{
	GLfloat cien_ka[] = {0.00, 0.00, 0.00, 0.5};
	float jas;

	jas = 0.5 - ( smiec[a].y - gdzie_y_zwoda(smiec[a].x,smiec[a].z) ) / 10.0;
	if (jas>0)
	{
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
	//		glEnable(GL_COLOR_MATERIAL);


		cien_ka[3] = jas;

		glMaterialfv(GL_FRONT, GL_AMBIENT, cien_ka);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cien_ka);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cien_ka);
		glMaterialf(GL_FRONT, GL_SHININESS, 0);

		glPushMatrix();
	//		glTranslatef(smiec[a].x, 0.0, smiec[a].z);

	/*		glRotatef(-smiec[a].dx*70, 0.0, 0.5, 1.0); //obrot wokol osi przy przesuwaniu w bok
			glRotatef(smiec[a].dy*60, 1.0, 0.0, 0.0); //obrot w pionie pod wplywem szybkosci pionowej
	*/
	//		glScalef(smiec[a].rozm,smiec[a].rozm,smiec[a].rozm);

			glBegin(GL_POLYGON);
				glNormal3f(0.0, 1.0, 0.0);
				vertexXZs(a, -0.1 , 0.0 );
				vertexXZs(a,  0.0 , 0.1 );
				vertexXZs(a,  0.1 , 0.0 );
				vertexXZs(a,  0.0 ,-0.1 );
			glEnd();

		glPopMatrix();

	//	glDisable(GL_COLOR_MATERIAL);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

}
//-----------------------------------------------------------------------------
void rysuj_smieci()
{
	int a;

	for (a=0; a<maxsmiec; a++)
		if (smiec[a].jest==1)
		{
	     glEnable(GL_COLOR_MATERIAL);
		  glPushMatrix();
           glColor4f(smiec[a].r, smiec[a].g, smiec[a].b, 1.0);
           glTranslatef(smiec[a].x, smiec[a].y, smiec[a].z);
           if (smiec[a].obrot!=0.0)	glRotatef(smiec[a].obrot, 1.0, 0.7, 0.0);
           glScalef(smiec[a].rx, smiec[a].ry, smiec[a].rz);
           glCallList(listbase+ob_smiec);
        glPopMatrix();
        glDisable(GL_COLOR_MATERIAL);
        rysuj_cien_smiec(a);
		}


}

//-----------------------------------------------------------------------------
void rysuj_ruchome(bool celowniki=false)
{
	int a;

	for (a=0; a<maxruchome; a++)
		if (ruchome[a].jest==1)
		{
		  glPushMatrix();

           if (!celowniki) { //rysuj obiekty
               glTranslatef(ruchome[a].x, ruchome[a].y, ruchome[a].z);
               if (ruchome[a].obrot!=0.0)	glRotatef(ruchome[a].obrot, 0.0, 1.0, 0.0);
               if (ruchome[a].dy<0.0) glRotatef(ruchome[a].dy*180, -1.0, 0.0, 0.0);
               //glScalef(ruchome[a].rx, ruchome[a].ry, ruchome[a].rz);

               switch (ruchome[a].rodzaj)
               {
                 case 1: //czolg
                   glCallList(listbase+ob_czolgi);
                   //glRotatef(teren[(int)x][(int)z].obiektpatrzyobr, 0,1,0);
                   glCallList(listbase+ob_czolgi+1);
                   glRotatef(15, -1, 0, 0 );
                   glCallList(listbase+ob_czolgi+2);
                 break;
                 case 2: //auto
                   glRotatef(180, 0,1,0);
                   glCallList(listbase+ob_auta);
                 break;
                 case 3: //lokomotywa
                   glRotatef(180, 0,1,0);
                   glCallList(listbase+ob_pociag);

                   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_pocicz_ka);
                   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_pocicz_kd);
                   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_poci_ks);
                   glMaterialf(GL_FRONT, GL_SHININESS, 120);

                   glPushAttrib(GL_ALL_ATTRIB_BITS);

                     glPolygonMode(GL_FRONT, GL_FILL);
                     glEnable(GL_CULL_FACE);
                     for (int l=-1; l<=1; l+=2) {
                       glPushMatrix();
                         glRotatef(90, 0,1,0);
                         glTranslatef(-0.5+sin(oo/1.4)*0.13,
                                      0.23+cos(oo/1.4)*0.13,
                                      0.50*l);
                         klocek(0.04, 0.85, 0.02);
                         //gluCylinder(kolo, (0.08+l*0.03)*skala, (0.08+l*0.03)*skala, 0.4*skala, 6,1);
                       glPopMatrix();
                     }

                   glPopAttrib();

                 break;
                 case 4: //weglarka
                   glRotatef(180, 0,1,0);
                   glCallList(listbase+ob_pociag+1);
                 break;
                 case 5: //wagon
                   glRotatef(180, 0,1,0);
                   glCallList(listbase+ob_pociag+2);
                 break;
                 case 6: //barka
                   glPushMatrix();
                     glRotatef(sin(oo/20.0)*3,1,0,0);
                     glTranslatef(0,sin(oo/20.0)*0.1,0);
                     glCallList(listbase+ob_barki);

                     glPushMatrix();
                       if (ruchome[a].obrot!=0.0)	glRotatef(-ruchome[a].obrot, 0.0, 1.0, 0.0);
                       glRotatef(ruchome[a].obiektpatrzyobr, 0,1,0);
                       glCallList(listbase+ob_barki+1);
                       glRotatef(ruchome[a].obiektpatrzypion, -1, 0, 0 );
                       glCallList(listbase+ob_barki+2);
                     glPopMatrix();
                   glPopMatrix();

                   //fale
                   if (fabs(ruchome[a].dz)>=0.01) {
                     glPushMatrix();
                       wlacz_teksture(19);
                         glEnable(GL_BLEND);
                         glColor4f(1,1,1,1);
                         glDisable(GL_CULL_FACE);
                         glDepthMask(GL_FALSE);
                         glPolygonMode(GL_FRONT, GL_FILL);
                         glPolygonMode(GL_BACK, GL_FILL);
                         glDisable(GL_COLOR_MATERIAL);
                         glMaterialfv(GL_FRONT, GL_AMBIENT, mat_plusk_kd);
                         glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_plusk_kd);
                         glMaterialfv(GL_FRONT, GL_SPECULAR, mat_plusk_kd);
                         glMaterialf(GL_FRONT, GL_SHININESS, 100);

                         glTranslatef(0,0.2,0);
                         for (int n=0; n<=1; n++) {
                           for (int s=-1; s<=1; s+=2) {
                             glBegin(GL_TRIANGLES);
                               glTexCoord2f(1,1+fmod(oo/50.0,2));  glVertex3f(  0, sin(oo/16.0+n*3)*0.33, 4.8-n/2.0);
                               glTexCoord2f(0,0+fmod(oo/50.0,2));  glVertex3f(3.3*s, cos(oo/20.0+n*4)*0.30+0.1, -2.8-n);
                               glTexCoord2f(1,0+fmod(oo/50.0,2));  glVertex3f(0.7*s, cos(oo/27.0+n*5)*0.22, -2.5-n);
                             glEnd();
                           }
                         }

                         glDepthMask(GL_TRUE);
                         glDisable(GL_BLEND);
                       wylacz_teksture();
                     glPopMatrix();
                   }

                 break;
               }
           } else { //celowniki
                  //jesli glowny cel - rysuj celownik
                  if (ruchome[a].cel) {
                     float celx = ruchome[a].x,
                           cely = ruchome[a].y,
                           celz = ruchome[a].z,
                           celrozm=2;
                     glPushMatrix();
                     glPushAttrib(GL_ALL_ATTRIB_BITS);


                     float viewMatrix[16];
                     glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
                     GLfloat right[3]={viewMatrix[0], viewMatrix[4], viewMatrix[8]};
                     GLfloat up[3]={viewMatrix[1], viewMatrix[5], viewMatrix[9]};

                     glEnable(GL_BLEND);
                     glDisable(GL_LIGHTING);
                     glDepthMask(GL_FALSE);
                     glEnable(GL_COLOR_MATERIAL);
                     glPolygonMode(GL_FRONT, GL_FILL);
                     glCullFace(GL_BACK);

                     if (ustawienia.mgla) glDisable(GL_FOG);

                     glColor4f(1,0.5+sin(oo/4.0)*0.5,0.5+sin(oo/4.0)*0.5, 0.7);
                     wlacz_teksture(2);
                     glBegin(GL_QUADS);
                       glTexCoord2f(0.0, 0.0);
                       glVertex3f ((celx + (right[0] + up[0]) * -celrozm),(cely + (right[1] + up[1]) * -celrozm),(celz + (right[2] + up[2]) * -celrozm));
                       glTexCoord2f(1.0, 0.0);
                       glVertex3f ((celx + (right[0] - up[0]) * celrozm),(cely + (right[1] - up[1]) * celrozm),(celz + (right[2] - up[2]) * celrozm));
                       glTexCoord2f(1.0, 1.0);
                       glVertex3f ((celx + (right[0] + up[0]) * celrozm),(cely + (right[1] + up[1]) * celrozm),(celz + (right[2] + up[2]) * celrozm));
                       glTexCoord2f(0.0, 1.0);
                       glVertex3f ((celx + (up[0] - right[0]) * celrozm),(cely + (up[1] - right[1]) * celrozm),(celz + (up[2] - right[2]) * celrozm));
                     glEnd();
                     wylacz_teksture();

                     if (ustawienia.mgla) glEnable(GL_FOG);

                     glDisable(GL_COLOR_MATERIAL);
                     glDepthMask(GL_TRUE);
                     glDisable(GL_BLEND);



                     glPopAttrib();
                     glPopMatrix();

                  }

           }

        glPopMatrix();

        //rysuj_cien_ruchome(a);
		}


}

//-----------------------------------------------------------------------------
void ustaw_swiatlo(float j)
{
   ustawienia.jasnoscswiatla=j;
   light_ka[0] = 1.00*j;
   light_ka[1] = 1.00*j;
   light_ka[2] = 0.85*j;

   light_kd[0] = 1.00*j;
   light_kd[1] = 1.00*j;
   light_kd[2] = 0.98*j;

   light_ks[0] = 1.00*j;
   light_ks[1] = 1.00*j;
   light_ks[2] = 0.92*j;

   fogColor[0] = 0.6 * cos(M_PI-j*M_PI);
   fogColor[1] = 0.6 * cos(M_PI-j*M_PI);
   fogColor[2] = 0.7 * cos(M_PI-j*M_PI);
   fogColor[3] = 0.1;

	glClearColor(fogColor[0], fogColor[1], fogColor[2], 0.0);

   glFogfv(GL_FOG_COLOR, fogColor);
}

//-----------------------------------------------------------------------------
void rysuj_licznik(float wartosc, float przezroczystosc=1.0, int px=0, int py=0, int rx=87, int ry=87)
{
  const int srx=rx/2.0;
  const int sry=ry/2.0;

  wlacz_teksture(11);                          

  glColor4f(1,1,1,przezroczystosc);
//  glLightModeli(GL_LIGHT_MODEL_AMBIENT, GL_FALSE);
  glBegin(GL_QUADS);
     glTexCoord2f(1,0); glVertex2f(  px+rx,  py);
     glTexCoord2f(1,1); glVertex2f(  px+rx,  py+ry);
     glTexCoord2f(0,1); glVertex2f(  px,  py+ry);
     glTexCoord2f(0,0); glVertex2f(  px,  py);
  glEnd();

  wylacz_teksture();

  wlacz_teksture(12);
  glColor4f(1,1,1,przezroczystosc);
//  glLightModeli(GL_LIGHT_MODEL_AMBIENT, GL_FALSE);

  glBegin(GL_QUADS);
     glTexCoord2f(0,0); glVertex2f( px+srx +sin( wartosc     *(M_PI/180.0))*srx, py+sry -cos( wartosc     *(M_PI/180.0))*sry);
     glTexCoord2f(0,1); glVertex2f( px+srx +sin((wartosc+90) *(M_PI/180.0))*srx, py+sry -cos((wartosc+90) *(M_PI/180.0))*sry);
     glTexCoord2f(1,1); glVertex2f( px+srx +sin((wartosc+180)*(M_PI/180.0))*srx, py+sry -cos((wartosc+180)*(M_PI/180.0))*sry);
     glTexCoord2f(1,0); glVertex2f( px+srx +sin((wartosc+270)*(M_PI/180.0))*srx, py+sry -cos((wartosc+270)*(M_PI/180.0))*sry);
  glEnd();

  wylacz_teksture();

}

//-----------------------------------------------------------------------------
void rysuj_liczniki()
{
  const float przezroczystoscpaskow = 0.4, przezroczystosclicznikow = 0.7;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  int width=BMForm->ClientRect.Right;
  int height=BMForm->ClientRect.Bottom-BMForm->PanelDolny->Height;
  gluOrtho2D(0,width,0,height);
//  gluOrtho2D(0,639,0,479-BMForm->PanelDolny->Height);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (ustawienia.mgla) glDisable(GL_FOG);
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);
  glPolygonMode(GL_FRONT, GL_FILL);

  //predkosc
    float wartosc = ekran.spd*1.1; //max ekran.spd = 200, max wartosc = 230
    wartosc = -wartosc*1.1+195;
    if (wartosc<-110) wartosc=-110;

    rysuj_licznik(wartosc, przezroczystosclicznikow);

  //wysokosc
    wartosc = gracz.alt; //max ekran.spd = 200, max wartosc = 230
    wartosc = -wartosc*13.0+195;
    if (wartosc<-110) wartosc=-110;

    rysuj_licznik(wartosc, przezroczystosclicznikow, width-87);

    glLightModeli(GL_LIGHT_MODEL_AMBIENT, GL_FALSE);
  //paliwo

    wartosc = gracz.fuel/300.0*(height-120);
    glBegin(GL_QUADS);
       glColor4f(0.8,0.1,0.1,przezroczystoscpaskow);
       glVertex2f( 6, 100);
       glVertex2f( 15, 100);
       glColor4f(0.1,0.8,0.1,przezroczystoscpaskow);
       glVertex2f( 15+(gracz.fuel/20.0), 100+wartosc);
       glVertex2f( 6, 100+wartosc);
    glEnd();

  //bomby
    wartosc = gracz.bomb/30.0*(height-120);
    glBegin(GL_QUADS);
       glColor4f(0.1,0.1,0.8,przezroczystoscpaskow);
       glVertex2f( width-15, 100);
       glVertex2f( width-6, 100);
       glColor4f(0.8,0.1,0.6,przezroczystoscpaskow);
       glVertex2f( width-6, 100+wartosc);
       glVertex2f( width-15-(gracz.bomb/2.0), 100+wartosc);
    glEnd();

  //glDisable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
  if (ustawienia.mgla) glEnable(GL_FOG);

}


void rysuj_calosc()
{
	//czyszczenie ekranu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

   odswiezwidok();

	ustaw_kamere();

	//wstawianie swiatla globalnego
	glPushMatrix();
		//glTranslatef(pos1[0], pos1[1], pos1[2]);
		glLightfv(GL_LIGHT1, GL_POSITION, pos1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ka);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_kd);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light_ks);
//		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, sin(oo/50.0)*180.0);
	glPopMatrix();


	//wstawianie swiatla reflektora
/*	glPushMatrix();
		glLightfv(GL_LIGHT0, GL_POSITION, pos0);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir1); //wektor kierunku swiecenia
//		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90); //obciecie stozka
//		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 70.0f); //wygaszanie na brzegach swiatla
	glPopMatrix();
*/
	//wstawianie swiatla wybuchu jesli jest
   for (int a=swiatlaod; a<=swiatlado; a++) {
       int swnr=GL_LIGHT0+a;
       if (swiatla[a].jasnosc>0)
       {
         float pozycja[4]={swiatla[a].x, swiatla[a].y, swiatla[a].z,1};
         float kierunek[3] = {0, -1, 0};
         float kolor[4] = { 1.0*swiatla[a].jasnosc,
                            0.5*swiatla[a].jasnosc,
                            0.2*swiatla[a].jasnosc,
                            1};

         glPushMatrix();
            glLightfv(swnr, GL_AMBIENT, kolor);
            glLightfv(swnr, GL_DIFFUSE, kolor);
            glLightfv(swnr, GL_SPECULAR, kolor);
            glLightf(swnr, GL_SPOT_CUTOFF, 30.0*swiatla[a].jasnosc);
            glLightf(swnr, GL_SPOT_EXPONENT, 80.0-swiatla[a].jasnosc*72.0);
            glLightfv(swnr, GL_POSITION, pozycja);
            glLightfv(swnr, GL_SPOT_DIRECTION, kierunek);
         glPopMatrix();
         glEnable(swnr);
       } else
         glDisable(swnr);
   }
   if (swiatlolotniska.jest) {
      float pozycja[4]={swiatlolotniska.x, swiatlolotniska.y, swiatlolotniska.z,1};
      float kierunek[3] = {0.1, -0.6, -0.5};//{sin(oo/20.0), -1.2, cos(oo/20.0)};
         float kolor[4] = { 1.0,
                            1.0,
                            0.9,
                            1};
      normalize0(kierunek);
         glPushMatrix();
            glLightfv(GL_LIGHT0, GL_POSITION, pozycja);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, kierunek);
            glLightfv(GL_LIGHT0, GL_AMBIENT, kolor);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, kolor);
            glLightfv(GL_LIGHT0, GL_SPECULAR, kolor);
         glPopMatrix();
      glEnable(GL_LIGHT0);

   } else glDisable(GL_LIGHT0);

   rysuj_otoczenie();
   rysuj_ruchome();
	rysuj_smieci();
	rysuj_pociski(1);

	rysuj_samoloty();

   //przezroczyste:
  	rysuj_wode();
   rysuj_samoloty_cienie();
   rysuj_swiatelka_scenerii();
	rysuj_obiekty_scenerii(1);
	rysuj_pociski(0);


	rysuj_wybuchy();

   //celowniki na glownych celach:
	glClear(GL_DEPTH_BUFFER_BIT);
	rysuj_obiekty_scenerii(0, true);
   rysuj_ruchome(true);
	rysuj_samoloty(true);

//   texplat(5, 20, 5, 15);

	glClear(GL_DEPTH_BUFFER_BIT);
   rysuj_liczniki();
	glFinish();

}
