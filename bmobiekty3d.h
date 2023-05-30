//tworzenie obiektow

//obiekty (listy)
GLuint listbase;

const int ob_lotnisko=1;
const int ob_lotnisko_wroga=2;
const int ob_drzewa=10;
const int ob_czolgi=50;
const int ob_auta=55;
const int ob_barki=60;
const int ob_pociag=70;
const int ob_dziala=80;
const int ob_budynki=100;
         //ob_budynki+1 - drugi budynek
const int ob_hangar=115;
const int ob_ulice=120;
const int ob_mosty=130;
const int ob_lampy=140;
const int ob_pociski=150;
const int ob_wybuchy=180;
const int ob_ogien=190; //miejsce na ziemi, skad sie pali
        //ob_ogien+1 - ogien sam sprajt
const int ob_smiec=200; //lecacy w powietrzu smiec z wybuchow

//parametry materialu drzew-pnia
GLfloat mat_dpn_ka[] = {0.25, 0.13, 0.03, 1.0};
GLfloat mat_dpn_kd[] = {0.25, 0.13, 0.03, 1.0};
GLfloat mat_dpn_ks[] = {0.40, 0.40, 0.40, 1.0};

//parametry materialu drzew-korony
GLfloat mat_dko_ka[] = {0.03, 0.40, 0.00, 1.0};
GLfloat mat_dko_kd[] = {0.02, 0.40, 0.00, 1.0};
GLfloat mat_dko_ks[] = {0.15, 0.20, 0.15, 1.0};

void stworz_drzewo()
{
  //drzewo 1

//   drzewo = gluNewQuadric();

   gluQuadricDrawStyle(drzewo, GLU_FILL);
   gluQuadricNormals(drzewo, GLU_SMOOTH);
   gluQuadricOrientation(drzewo, GLU_OUTSIDE);
   gluQuadricTexture(drzewo, GLU_TRUE);

	glNewList(listbase+ob_drzewa, GL_COMPILE);
		glPushMatrix();
			//pien
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_dpn_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dpn_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dpn_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 0);
			glPushMatrix();
				glRotatef(-90.0, 1.0, 0.0, 0.0);
			      	gluCylinder(drzewo, 0.14, 0.1, 1.4, 10,10);
			glPopMatrix();

			//korona
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_dko_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dko_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dko_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 0);
			glPushMatrix();
				wlacz_teksture(2);
				glTranslatef(0.0, 2.0, 0.0);
				glScalef(1.0, 1.6, 1.0);
				gluSphere(drzewo, 0.8, 6, 5);
				//glutSolidSphere(0.8, 12, 10);
				wylacz_teksture();
			glPopMatrix();
		glPopMatrix();
	glEndList();

	obiektyrozm[ob_drzewa]=2.0;


  //drzewo 2
	glNewList(listbase+ob_drzewa+1, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_dko_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dko_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dko_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 20);
         GLfloat rozm=1.5;
         GLfloat rozm2=rozm*2;
				wlacz_teksture(10);
              for (int i=0; i<=1; i++)
              {
                glRotatef(90.0,0,1,0);
                glBegin(GL_QUADS);
                  glTexCoord2f(0.0, 1.0); glVertex3f(-rozm,rozm2,0);
                  glTexCoord2f(0.0, 0.0); glVertex3f(-rozm,0,0);
                  glTexCoord2f(1.0, 0.0); glVertex3f( rozm,0,0);
                  glTexCoord2f(1.0, 1.0); glVertex3f( rozm,rozm2,0);
                glEnd();
              }
				wylacz_teksture();
		glPopMatrix();
	glEndList();

	obiektyrozm[ob_drzewa+1]=1.8;//2.3;

}

//parametry materialu budynkow scian
GLfloat mat_budsc_ka[] = {0.42, 0.40, 0.40, 1.0};
GLfloat mat_budsc_kd[] = {0.42, 0.40, 0.40, 1.0};
GLfloat mat_budsc_ks[] = {0.15, 0.20, 0.15, 1.0};

void stworz_budynek()
{
	glNewList(listbase+ob_budynki, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_budsc_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_budsc_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_budsc_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 10);

         glEnable(GL_CULL_FACE);
         glCullFace(GL_BACK);

            float szerokosc=3;
            float wysprzod=3;
            float wystyl=2;
            float gleb=2;

            //gora
				wlacz_teksture(4);
            glBegin(GL_QUADS);
                glNormal3f (0.0, 1.0, 0.0);
                glTexCoord2f(1.6, 0);		glVertex3f ( szerokosc, wystyl  ,-gleb);
                glTexCoord2f(0, 0);		glVertex3f (-szerokosc, wystyl  ,-gleb);
                glTexCoord2f(0, 1);		glVertex3f (-szerokosc, wysprzod, gleb);
                glTexCoord2f(1.6,1);		glVertex3f ( szerokosc, wysprzod, gleb);
            glEnd();
		      wylacz_teksture();

		      wlacz_teksture(3);
            glBegin(GL_QUADS);
                //bok lewy
                glNormal3f (-1.0, 0.0, 0.0);
                glTexCoord2f(0, 0);		glVertex3f (-szerokosc, 0.0,-gleb);
                glTexCoord2f(1, 0);		glVertex3f (-szerokosc, 0.0, gleb);
                glTexCoord2f(1, 0.1);		glVertex3f (-szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 0.1);		glVertex3f (-szerokosc,  wystyl  ,-gleb);

                //bok prawy
                glNormal3f (1.0, 0.0, 0.0);
                glTexCoord2f(1, 0.1);		glVertex3f ( szerokosc,  wystyl  ,-gleb);
                glTexCoord2f(0, 0.1);		glVertex3f ( szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 0);		glVertex3f ( szerokosc, 0.0, gleb);
                glTexCoord2f(1, 0);		glVertex3f ( szerokosc, 0.0,-gleb);

                //bok tylni
                glNormal3f (0.0, 0.0, -1.0);
                glTexCoord2f(0, 0);		glVertex3f ( szerokosc, 0.0,-gleb);
                glTexCoord2f(1, 0);		glVertex3f (-szerokosc, 0.0,-gleb);
                glTexCoord2f(1, 0.1);		glVertex3f (-szerokosc,  wystyl  ,-gleb);
                glTexCoord2f(0, 0.1);		glVertex3f ( szerokosc,  wystyl  ,-gleb);
            glEnd();
		      wylacz_teksture();

            //bok przedni
		      wlacz_teksture(3);
            glBegin(GL_QUADS);
                glNormal3f (0.0, 0.0, 1.0);
                glTexCoord2f(1, 0);		      glVertex3f ( szerokosc, 0.0, gleb);
                glTexCoord2f(1, 0.679);		glVertex3f ( szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 0.679);		glVertex3f (-szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 0);		      glVertex3f (-szerokosc, 0.0, gleb);
            glEnd();
				wylacz_teksture();


		glPopMatrix();
	glEndList();
	obiektyrozm[ob_budynki]=4.0;
}

void stworz_budynek2()
{
	glNewList(listbase+ob_budynki+1, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_budsc_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_budsc_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_budsc_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 10);

         glEnable(GL_CULL_FACE);
         glCullFace(GL_BACK);

            float szerokosc=3;
            float wysprzod=3;
            float wystyl=2.5;
            float gleb=3;
            float szdach=0.1;

            //gora
				wlacz_teksture(4);
            glBegin(GL_QUADS);
                glNormal3f (0.0, 1.0, 0.0);
                glTexCoord2f(1.6, 0);		glVertex3f ( szerokosc+szdach, wystyl  ,-gleb-szdach);
                glTexCoord2f(0, 0);		glVertex3f (-szerokosc-szdach, wystyl  ,-gleb-szdach);
                glTexCoord2f(0, 1);		glVertex3f (-szerokosc-szdach, wysprzod, gleb+szdach);
                glTexCoord2f(1.6,1);		glVertex3f ( szerokosc+szdach, wysprzod, gleb+szdach);
            glEnd();
		      wylacz_teksture();

		      wlacz_teksture(25);
            glBegin(GL_QUADS);
                //bok lewy
                glNormal3f (-1.0, 0.0, 0.0);
                glTexCoord2f(0, 0);		glVertex3f (-szerokosc, 0.0,-gleb);
                glTexCoord2f(1, 0);		glVertex3f (-szerokosc, 0.0, gleb);
                glTexCoord2f(1, 0.3);		glVertex3f (-szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 0.3);		glVertex3f (-szerokosc,  wystyl  ,-gleb);

                //bok prawy
                glNormal3f (1.0, 0.0, 0.0);
                glTexCoord2f(1, 0.3);		glVertex3f ( szerokosc,  wystyl  ,-gleb);
                glTexCoord2f(0, 0.3);		glVertex3f ( szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 0);		glVertex3f ( szerokosc, 0.0, gleb);
                glTexCoord2f(1, 0);		glVertex3f ( szerokosc, 0.0,-gleb);

                //bok tylni
                glNormal3f (0.0, 0.0, -1.0);
                glTexCoord2f(0, 0);		glVertex3f ( szerokosc, 0.0,-gleb);
                glTexCoord2f(1, 0);		glVertex3f (-szerokosc, 0.0,-gleb);
                glTexCoord2f(1, 0.3);		glVertex3f (-szerokosc,  wystyl  ,-gleb);
                glTexCoord2f(0, 0.3);		glVertex3f ( szerokosc,  wystyl  ,-gleb);
            glEnd();
		      wylacz_teksture();

            //bok przedni
		      wlacz_teksture(25);
            glBegin(GL_QUADS);
                glNormal3f (0.0, 0.0, 1.0);
                glTexCoord2f(1, 0.371);		      glVertex3f ( szerokosc, 0.0, gleb);
                glTexCoord2f(1, 1);		glVertex3f ( szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 1);		glVertex3f (-szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 0.371);		      glVertex3f (-szerokosc, 0.0, gleb);
            glEnd();
				wylacz_teksture();


		glPopMatrix();
	glEndList();
	obiektyrozm[ob_budynki+1]=4.0;
}

void stworz_budynek3()
{
	glNewList(listbase+ob_budynki+2, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_budsc_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_budsc_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_budsc_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 10);

         glEnable(GL_CULL_FACE);
         glCullFace(GL_BACK);

            float szerokosc=3;
            float wysprzod=3;
            float wystyl=2.2;
            float gleb=2.3;

            //gora
				wlacz_teksture(4);
            glBegin(GL_QUADS);
                glNormal3f (0.0, 1.0, 0.0);
                glTexCoord2f(0.8, 0);		glVertex3f ( szerokosc, wysprzod, 0);
                glTexCoord2f(  0, 0);		glVertex3f (-szerokosc, wysprzod, 0);
                glTexCoord2f(  0, 1);		glVertex3f (-szerokosc, wystyl  , gleb);
                glTexCoord2f(0.8, 1);		glVertex3f ( szerokosc, wystyl  , gleb);

                glTexCoord2f(0.8, 0);		glVertex3f ( szerokosc, wystyl  ,-gleb);
                glTexCoord2f(  0, 0);		glVertex3f (-szerokosc, wystyl  ,-gleb);
                glTexCoord2f(  0, 1);		glVertex3f (-szerokosc, wysprzod, 0);
                glTexCoord2f(0.8, 1);		glVertex3f ( szerokosc, wysprzod, 0);

            glEnd();
		      wylacz_teksture();

		      wlacz_teksture(25);
            glBegin(GL_QUADS);
                //bok lewy
                glNormal3f (-1.0, 0.0, 0.0);
                glTexCoord2f(  0,   0);		glVertex3f (-szerokosc,       0.0, 0);
                glTexCoord2f(0.5,   0);		glVertex3f (-szerokosc,       0.0, gleb);
                glTexCoord2f(0.5, 0.2);		glVertex3f (-szerokosc,  wystyl  , gleb);
                glTexCoord2f(  0, 0.3);		glVertex3f (-szerokosc,  wysprzod, 0);

                glTexCoord2f(  0,   0);		glVertex3f (-szerokosc,       0.0,-gleb);
                glTexCoord2f(0.5,   0);		glVertex3f (-szerokosc,       0.0, 0);
                glTexCoord2f(0.5, 0.3);		glVertex3f (-szerokosc,  wysprzod, 0);
                glTexCoord2f(  0, 0.2);		glVertex3f (-szerokosc,  wystyl  ,-gleb);

                //bok prawy
                glNormal3f (1.0, 0.0, 0.0);
                glTexCoord2f(0.5, 0.3);		glVertex3f ( szerokosc,  wysprzod, 0);
                glTexCoord2f(  0, 0.2);		glVertex3f ( szerokosc,  wystyl  , gleb);
                glTexCoord2f(  0,   0);		glVertex3f ( szerokosc,       0.0, gleb);
                glTexCoord2f(0.5,   0);		glVertex3f ( szerokosc,       0.0, 0);

                glTexCoord2f(0.5, 0.2);		glVertex3f ( szerokosc,  wystyl  ,-gleb);
                glTexCoord2f(  0, 0.3);		glVertex3f ( szerokosc,  wysprzod, 0);
                glTexCoord2f(  0,   0);		glVertex3f ( szerokosc,       0.0, 0);
                glTexCoord2f(0.5,   0);		glVertex3f ( szerokosc,       0.0,-gleb);

                //bok tylni
                glNormal3f (0.0, 0.0, -1.0);
                glTexCoord2f(0,   0);		glVertex3f ( szerokosc, 0.0,-gleb);
                glTexCoord2f(1,   0);		glVertex3f (-szerokosc, 0.0,-gleb);
                glTexCoord2f(1, 0.3);		glVertex3f (-szerokosc,  wystyl  ,-gleb);
                glTexCoord2f(0, 0.3);		glVertex3f ( szerokosc,  wystyl  ,-gleb);
            glEnd();
		      wylacz_teksture();

            //bok przedni
		      wlacz_teksture(25);
            glBegin(GL_QUADS);
                glNormal3f (0.0, 0.0, 1.0);
                glTexCoord2f(1, 0.371);		      glVertex3f ( szerokosc, 0.0, gleb);
                glTexCoord2f(1, 1);		glVertex3f ( szerokosc,  wystyl, gleb);
                glTexCoord2f(0, 1);		glVertex3f (-szerokosc,  wystyl, gleb);
                glTexCoord2f(0, 0.371);		      glVertex3f (-szerokosc, 0.0, gleb);
            glEnd();
				wylacz_teksture();


		glPopMatrix();
	glEndList();
	obiektyrozm[ob_budynki+2]=4.0;
}

void stworz_hangar(int czesc)
{
	glNewList(listbase+ob_hangar+czesc, GL_COMPILE);
		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_budsc_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_budsc_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_budsc_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 10);

         glPolygonMode(GL_FRONT, GL_FILL);
         glPolygonMode(GL_BACK, GL_FILL);
         glDisable(GL_CULL_FACE);

            float szerokosc=dkrok;
            float wysprzod=2.5;
            float wystyl=1.8;
            float gleb=dkrok/2.0;
            float tgleb=-dkrok/1.2;

            //gora
				wlacz_teksture(4);
            glBegin(GL_QUADS);
                glNormal3f (0.0, 1.0, 0.0);
                glTexCoord2f(1, 0);		glVertex3f ( szerokosc, wystyl  ,tgleb);
                glTexCoord2f(0, 0);		glVertex3f (-szerokosc, wystyl  ,tgleb);
                glTexCoord2f(0, 1);		glVertex3f (-szerokosc, wysprzod, gleb);
                glTexCoord2f(1, 1);		glVertex3f ( szerokosc, wysprzod, gleb);
            glEnd();
		      wylacz_teksture();

		      wlacz_teksture(3);
            glBegin(GL_QUADS);
              if (czesc==0) {
                //bok lewy
                glNormal3f (-1.0, 0.0, 0.0);
                glTexCoord2f(0, 0);		   glVertex3f (-szerokosc, 0.0,tgleb);
                glTexCoord2f(1, 0);		   glVertex3f (-szerokosc, 0.0, gleb);
                glTexCoord2f(1, 0.1);		glVertex3f (-szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 0.1);		glVertex3f (-szerokosc,  wystyl  ,tgleb);
              } else {
                glNormal3f (-1.0, 0.0, 0.0);
                glTexCoord2f(0, 0);		   glVertex3f (-szerokosc, wystyl-0.05,tgleb);
                glTexCoord2f(1, 0);		   glVertex3f (-szerokosc, wystyl-0.05, gleb);
                glTexCoord2f(1, 0.05);		glVertex3f (-szerokosc,  wystyl, gleb);
                glTexCoord2f(0, 0.05);		glVertex3f (-szerokosc,  wystyl  ,tgleb);
              }

              if (czesc==2) {
                //bok prawy
                glNormal3f (1.0, 0.0, 0.0);
                glTexCoord2f(1, 0.1);		glVertex3f ( szerokosc,  wystyl  ,tgleb);
                glTexCoord2f(0, 0.1);		glVertex3f ( szerokosc,  wysprzod, gleb);
                glTexCoord2f(0, 0);		   glVertex3f ( szerokosc, 0.0, gleb);
                glTexCoord2f(1, 0);		   glVertex3f ( szerokosc, 0.0,tgleb);
              } else {
                glNormal3f (1.0, 0.0, 0.0);
                glTexCoord2f(1, 0.05);		glVertex3f ( szerokosc, wystyl  ,tgleb);
                glTexCoord2f(0, 0.05);		glVertex3f ( szerokosc, wystyl, gleb);
                glTexCoord2f(0, 0);		   glVertex3f ( szerokosc, wystyl-0.05, gleb);
                glTexCoord2f(1, 0);		   glVertex3f ( szerokosc, wystyl-0.05,tgleb);
              }

                //bok tylni
                glNormal3f (0.0, 0.0, -1.0);
                glTexCoord2f(0, 0);		glVertex3f ( szerokosc, 0.0,tgleb);
                glTexCoord2f(1, 0);		glVertex3f (-szerokosc, 0.0,tgleb);
                glTexCoord2f(1, 0.12);		glVertex3f (-szerokosc,  wystyl  ,tgleb);
                glTexCoord2f(0, 0.12);		glVertex3f ( szerokosc,  wystyl  ,tgleb);
            glEnd();
		      wylacz_teksture();

            glEnable(GL_CULL_FACE);

      glPopAttrib();
		glPopMatrix();
	glEndList();
	obiektyrozm[ob_hangar+czesc]=2.0;
}


//parametry materialu czolgow
GLfloat mat_czolg_ka[] = {0.22, 0.20, 0.02, 1.0};
GLfloat mat_czolg_kd[] = {0.22, 0.20, 0.02, 1.0};
GLfloat mat_czolg_ks[] = {0.25, 0.30, 0.25, 1.0};

void stworz_czolg()
{
   const float skala=2.0;
   const
   float pkt[][3]={    -0.25,       0,      0.3, //0
                         0.4,       0,      0.3, //1
                         0.6,    0.10,      0.3, //2
                         0.4,     0.2,      0.3, //3
                        -0.4,     0.2,      0.3, //4
                        -0.4,    0.10,      0.3, //5
                  //druga strona, w zasadzie to samo, tylko inny Z
                       -0.25,       0,     -0.3, //6
                         0.4,       0,     -0.3, //7
                         0.6,    0.10,     -0.3, //8
                         0.4,     0.2,     -0.3, //9
                        -0.4,     0.2,     -0.3, //10
                        -0.4,    0.10,     -0.3  //11
                   };

   float texlac[4]= {0.0, 0.2,  1.0, 0.6};
                    //punkty        wekt.normalne
   float lac[][6]= { 4, 5, 0,           0,0,1,
                     4, 0, 3,           0,0,1,
                     3, 0, 1,           0,0,1,
                     3, 1, 2,           0,0,1,

                     6,11,10,           0,0,-1,
                     9, 6,10,           0,0,-1,
                     7, 6, 9,           0,0,-1,
                     8, 7, 9,           0,0,-1

                   };
                    //punkty        wekt.normalne        wspolrzedne textury [x1,y1, x2,y2]
   float lacq[][11]={ 0, 5,11, 6,     -0.5,-0.5, 0,       0.0, 0.2, 1.0, 1.0,
                      5, 4,10,11,     -1.0,   0, 0,       0.0, 0.2, 1.0, 1.0,
                      4, 3, 9,10,        0, 1.0, 0,       0.0, 0.2, 1.0, 1.0,
                      3, 2, 8, 9,      0.4, 0.6, 0,       0.0, 0.2, 1.0, 1.0,
                      2, 1, 7, 6,      0.4,-0.6, 0,       0.0, 0.2, 1.0, 1.0
                   };


	glNewList(listbase+ob_czolgi, GL_COMPILE);
		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);
//         glTranslatef(-(5/12.0)*skala, 0.1, -1.0*skala);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_czolg_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_czolg_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_czolg_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 50);
         glFrontFace (GL_CW);

         wlacz_teksture(23);
         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=7; a++) {
                glNormal3f( lac[a][5], lac[a][4], lac[a][3]);
                for (int b=0; b<=2; b++) {
                    glTexCoord2f(pkt[(int)lac[a][b]][0]+0.4, pkt[(int)lac[a][b]][1]);
//                    glTexCoord2f(pkt[(int)lac[a][b]][0] /2, pkt[(int)lac[a][b]][1] /2+texlac[1]);
                    glVertex3f( pkt[(int)lac[a][b]][2]*skala, pkt[(int)lac[a][b]][1]*skala, pkt[(int)lac[a][b]][0]*skala);
                }
            }
         glEnd();
         glBegin(GL_QUADS);
            for (int a=0; a<=4; a++) {
                glNormal3f( lacq[a][6], lacq[a][5], lacq[a][4]);
                for (int b=0; b<=3; b++) {
                    switch (b) {
                       case 0: glTexCoord2f(lacq[a][7],lacq[a][8]); break;
                       case 1: glTexCoord2f(lacq[a][9],lacq[a][8]); break;
                       case 2: glTexCoord2f(lacq[a][9],lacq[a][10]); break;
                       case 3: glTexCoord2f(lacq[a][7],lacq[a][10]); break;
                    }
                    glVertex3f( pkt[(int)lacq[a][b]][2]*skala, pkt[(int)lacq[a][b]][1]*skala, pkt[(int)lacq[a][b]][0]*skala);
                }
            }
         glEnd();
         //wylacz_teksture();


        glFrontFace (GL_CCW);
//        GLUquadricObj *kolo;
//        kolo = gluNewQuadric();
        gluQuadricDrawStyle(kolo, GLU_FILL);
        gluQuadricNormals(kolo, GLU_SMOOTH);
        gluQuadricOrientation(kolo, GLU_OUTSIDE);
        gluQuadricTexture(kolo, GLU_TRUE);

        glPushMatrix();
          glRotatef(-90, 0, 1, 0);
          for (int b=-1; b<=1; b+=2) {
            glPushMatrix();
               glTranslatef( -0.3*skala, 0.26*skala, (-0.09+0.15*b)*skala );
               gluCylinder(kolo, 0.06*skala, 0.06*skala, 0.24*skala, 8, 1);
               glPushMatrix();
                 glRotatef(180,0,1,0);
                 gluDisk(kolo, 0, 0.06*skala, 8, 1);
               glPopMatrix();
               glTranslatef( 0, 0, 0.24*skala );
               gluDisk(kolo, 0, 0.06*skala, 8, 1);
            glPopMatrix();
          }
        glPopMatrix();

      glPopAttrib();
		glPopMatrix();
	glEndList();

   //wiezyczka
	glNewList(listbase+ob_czolgi+1, GL_COMPILE);
   const
   float wpkt[][3]={     -0.1,     0.2,      0.15, //0
                          0.1,     0.2,      0.15, //1
                         0.25,    0.27,      0.2,  //2
                         0.25,    0.34,      0.2,  //3
                          0.1,     0.4,      0.15, //4
                         -0.1,     0.4,      0.15, //5
                        -0.15,    0.34,      0.2,  //6
                        -0.15,    0.27,      0.2,  //7
                  //druga strona, w zasadzie to samo, tylko inny Z
                         -0.1,     0.2,     -0.15, //8
                          0.1,     0.2,     -0.15, //9
                         0.25,    0.27,     -0.2,  //10
                         0.25,    0.34,     -0.2,  //11
                          0.1,     0.4,     -0.15, //12
                         -0.1,     0.4,     -0.15, //13
                        -0.15,    0.34,     -0.2,  //14
                        -0.15,    0.27,     -0.2   //15

                   };

   float wtexlac[4]= {0.0, 0.2,  1.0, 0.6};
                    //punkty        wekt.normalne
   float wlac[][6]= { 0, 1, 2,           0,-0.3, 0.7,
                      0, 2, 7,           0,-0.3, 0.7,
                      7, 2, 3,           0,   0,   1,
                      6, 7, 3,           0,   0,   1,
                      5, 6, 4,           0, 0.3,-0.7,
                      4, 6, 3,           0, 0.3,-0.7,

                     10, 9, 8,           0,-0.3,-0.7,
                     15,10, 8,           0,-0.3,-0.7,
                     11,10,15,           0,   0,   1,
                     11,15,14,           0,   0,   1,
                     12,14,13,           0, 0.3, 0.7,
                     11,14,12,           0, 0.3, 0.7

                   };
                    //punkty        wekt.normalne        wspolrzedne textury [x1,y1, x2,y2]
   float wlacq[][11]={ 0, 7,15, 8,     -0.5,-0.5, 0,       0.0, 0.2, 1.0, 1.0,
                       7, 6,14,15,     -1.0,   0, 0,       0.0, 0.2, 1.0, 1.0,
                       6, 5,13,14,     -0.5, 0.5, 0,       0.0, 0.2, 1.0, 1.0,
                       5, 4,12,13,        0, 1.0, 0,       0.0, 0.2, 1.0, 1.0,
                       4, 3,11,12,      0.5, 0.5, 0,       0.0, 0.2, 1.0, 1.0,
                       3, 2,10,11,      1.0,   0, 0,       0.0, 0.2, 1.0, 1.0,
                       2, 1, 9,10,      0.5,-0.5, 0,       0.0, 0.2, 1.0, 1.0
                      };

		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_czolg_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_czolg_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_czolg_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 28);
         glFrontFace (GL_CW);
         wlacz_teksture(23);
         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=11; a++) {
                glNormal3f( wlac[a][5], wlac[a][4], wlac[a][3]);
                for (int b=0; b<=2; b++) {
//                    glTexCoord2f(wpkt[(int)wlac[a][b]][0], wpkt[(int)wlac[a][b]][1]-0.2);
                    glTexCoord2f(wpkt[(int)wlac[a][b]][0] /2, wpkt[(int)wlac[a][b]][1] /2+wtexlac[1]);
                    glVertex3f( wpkt[(int)wlac[a][b]][2]*skala, wpkt[(int)wlac[a][b]][1]*skala, wpkt[(int)wlac[a][b]][0]*skala);
                }
            }
         glEnd();
         glBegin(GL_QUADS);
            for (int a=0; a<=6; a++) {
                glNormal3f( wlacq[a][6], wlacq[a][5], wlacq[a][4]);
                for (int b=0; b<=3; b++) {
                    switch (b) {
                       case 0: glTexCoord2f(wlacq[a][7],wlacq[a][8]); break;
                       case 1: glTexCoord2f(wlacq[a][9],wlacq[a][8]); break;
                       case 2: glTexCoord2f(wlacq[a][9],wlacq[a][10]); break;
                       case 3: glTexCoord2f(wlacq[a][7],wlacq[a][10]); break;
                    }
                    glVertex3f( wpkt[(int)wlacq[a][b]][2]*skala, wpkt[(int)wlacq[a][b]][1]*skala, wpkt[(int)wlacq[a][b]][0]*skala);
                }
            }
         glEnd();
         wylacz_teksture();
      glPopAttrib();
		glPopMatrix();
      glTranslatef( 0, 0.33*skala, 0.24*skala );
	glEndList();

   //lufa
	glNewList(listbase+ob_czolgi+2, GL_COMPILE);
     gluQuadricDrawStyle(kolo, GLU_FILL);
     gluQuadricNormals(kolo, GLU_SMOOTH);
     gluQuadricOrientation(kolo, GLU_OUTSIDE);
     gluQuadricTexture(kolo, GLU_TRUE);
     glDisable(GL_CULL_FACE);
     wlacz_teksture(23);
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_czolg_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_czolg_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_czolg_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 28);
         gluCylinder(kolo, 0.025*skala, 0.025*skala, 0.7*skala, 6, 1);
		glPopMatrix();
      wylacz_teksture();
	glEndList();

	obiektyrozm[ob_czolgi]=1.3;
}

//parametry materialu dzialoow
GLfloat mat_dzialo_ka[] = {0.12, 0.20, 0.02, 1.0};
GLfloat mat_dzialo_kd[] = {0.12, 0.25, 0.02, 1.0};
GLfloat mat_dzialo_ks[] = {0.35, 0.43, 0.15, 1.0};

void stworz_dzialo()
{
   const float skala=1.5;
   const
   float pkt[][3]={     -0.3,       0,      0.3, //0
                         0.3,       0,      0.3, //1
                         0.2,     0.6,      0.2, //2
                        -0.2,     0.6,      0.2, //3
                  //druga strona, w zasadzie to samo, tylko inny Z
                        -0.3,       0,     -0.3, //4
                         0.3,       0,     -0.3, //5
                         0.2,     0.6,     -0.2, //6
                        -0.2,     0.6,     -0.2, //7
                   };

   float texlac[4]= {0.0, 0.2,  1.0, 0.6};
                    //punkty           wekt.normalne     wspolrzedne textury [x1,y1, x2,y2]
   float lac[][12]={ 0, 1, 2,           0, 0.1, 0.9,       0,   0,   1,   0,   1,   1,
                     0, 2, 3,           0, 0.1, 0.9,       0,   0,   1,   1,   0,   1,

                     5, 4, 7,           0, 0.1,-0.9,       0,   0,   1,   0,   1,   1,
                     5, 7, 6,           0, 0.1,-0.9,       0,   0,   1,   0,   1,   1,

                     4, 0, 3,        -0.9, 0.1,   0,       0,   0,   1,   0,   1,   1,
                     4, 3, 7,        -0.9, 0.1,   0,       0,   0,   1,   0,   1,   1,

                     1, 5, 6,         0.9, 0.1,   0,       0,   0,   1,   0,   1,   1,
                     1, 6, 2,         0.9, 0.1,   0,       0,   0,   1,   0,   1,   1,

                     7, 3, 2,           0,   1,   0,       0,   0,   1,   0,   1,   1,
                     7, 2, 6,           0,   1,   0,       0,   0,   1,   0,   1,   1

                   };


	glNewList(listbase+ob_dziala, GL_COMPILE);
		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);
//         glTranslatef(-(5/12.0)*skala, 0.1, -1.0*skala);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_dzialo_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dzialo_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dzialo_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 50);
         glFrontFace (GL_CCW);
         glPolygonMode(GL_FRONT, GL_FILL);
//         glPolygonMode(GL_BACK, GL_POINT);
         glCullFace(GL_BACK);

         wlacz_teksture(22);
         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=9; a++) {
                glNormal3f( lac[a][3], lac[a][4], lac[a][5]);
                for (int b=0; b<=2; b++) {
                    //glTexCoord2f(pkt[(int)lac[a][b]][0] /2, pkt[(int)lac[a][b]][1] /2+texlac[1]);
                    switch (b) {
                       case 0: glTexCoord2f(lac[a][6],lac[a][7]); break;
                       case 1: glTexCoord2f(lac[a][8],lac[a][9]); break;
                       case 2: glTexCoord2f(lac[a][10],lac[a][11]); break;
                    }

                    glVertex3f( pkt[(int)lac[a][b]][0]*skala, pkt[(int)lac[a][b]][1]*skala, pkt[(int)lac[a][b]][2]*skala);
                }
            }
         glEnd();
         wylacz_teksture();

      glPopAttrib();
		glPopMatrix();
	glEndList();

   //wiezyczka
	glNewList(listbase+ob_dziala+1, GL_COMPILE);
   const
   float wpkt[][3]={     -0.1,     0.0,      0.15, //0
                          0.1,     0.0,      0.15, //1
                         0.25,    0.17,      0.2,  //2
                         0.25,    0.24,      0.2,  //3
                          0.1,     0.3,      0.15, //4
                         -0.1,     0.3,      0.15, //5
                        -0.15,    0.24,      0.2,  //6
                        -0.15,    0.17,      0.2,  //7
                  //druga strona, w zasadzie to samo, tylko inny Z
                         -0.1,     0.0,     -0.15, //8
                          0.1,     0.0,     -0.15, //9
                         0.25,    0.17,     -0.2,  //10
                         0.25,    0.24,     -0.2,  //11
                          0.1,     0.3,     -0.15, //12
                         -0.1,     0.3,     -0.15, //13
                        -0.15,    0.24,     -0.2,  //14
                        -0.15,    0.17,     -0.2   //15

                   };

   float wtexlac[4]= {0.0, 0.2,  1.0, 0.6};
                    //punkty        wekt.normalne
   float wlac[][6]= { 0, 1, 2,           0,-0.3, 0.7,
                      0, 2, 7,           0,-0.3, 0.7,
                      7, 2, 3,           0,   0,   1,
                      6, 7, 3,           0,   0,   1,
                      5, 6, 4,           0, 0.3,-0.7,
                      4, 6, 3,           0, 0.3,-0.7,

                     10, 9, 8,           0,-0.3,-0.7,
                     15,10, 8,           0,-0.3,-0.7,
                     11,10,15,           0,   0,   1,
                     11,15,14,           0,   0,   1,
                     12,14,13,           0, 0.3, 0.7,
                     11,14,12,           0, 0.3, 0.7

                   };
                    //punkty        wekt.normalne        wspolrzedne textury [x1,y1, x2,y2]
   float wlacq[][11]={ 0, 7,15, 8,     -0.5,-0.5, 0,       0.0, 0.0, 1.0, 1.0,
                       7, 6,14,15,     -1.0,   0, 0,       0.0, 0.0, 1.0, 1.0,
                       6, 5,13,14,     -0.5, 0.5, 0,       0.0, 0.0, 1.0, 1.0,
                       5, 4,12,13,        0, 1.0, 0,       0.0, 0.0, 1.0, 1.0,
                       4, 3,11,12,      0.5, 0.5, 0,       0.0, 0.0, 1.0, 1.0,
                       3, 2,10,11,      1.0,   0, 0,       0.0, 0.0, 1.0, 1.0,
                       2, 1, 9,10,      0.5,-0.5, 0,       0.0, 0.0, 1.0, 1.0
                      };

		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_dzialo_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dzialo_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dzialo_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 28);
         glFrontFace (GL_CW);
         wlacz_teksture(22);
         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=11; a++) {
                glNormal3f( wlac[a][5], wlac[a][4], wlac[a][3]);
                for (int b=0; b<=2; b++) {
                    glTexCoord2f(wpkt[(int)wlac[a][b]][0] /2, wpkt[(int)wlac[a][b]][1] /2+wtexlac[1]);
                    glVertex3f( wpkt[(int)wlac[a][b]][2]*skala, (wpkt[(int)wlac[a][b]][1]+0.6)*skala, wpkt[(int)wlac[a][b]][0]*skala);
                }
            }
         glEnd();
         glBegin(GL_QUADS);
            for (int a=0; a<=6; a++) {
                glNormal3f( wlacq[a][6], wlacq[a][5], wlacq[a][4]);
                for (int b=0; b<=3; b++) {
                    switch (b) {
                       case 0: glTexCoord2f(wlacq[a][7],wlacq[a][8]); break;
                       case 1: glTexCoord2f(wlacq[a][9],wlacq[a][8]); break;
                       case 2: glTexCoord2f(wlacq[a][9],wlacq[a][10]); break;
                       case 3: glTexCoord2f(wlacq[a][7],wlacq[a][10]); break;
                    }
                    glVertex3f( wpkt[(int)wlacq[a][b]][2]*skala, (wpkt[(int)wlacq[a][b]][1]+0.6)*skala, wpkt[(int)wlacq[a][b]][0]*skala);
                }
            }
         glEnd();
         wylacz_teksture();
      glPopAttrib();
		glPopMatrix();
      glTranslatef( 0, (0.23+0.6)*skala, 0.24*skala );
	glEndList();

   //lufa
	glNewList(listbase+ob_dziala+2, GL_COMPILE);
     gluQuadricDrawStyle(kolo, GLU_FILL);
     gluQuadricNormals(kolo, GLU_SMOOTH);
     gluQuadricOrientation(kolo, GLU_OUTSIDE);
     gluQuadricTexture(kolo, GLU_TRUE);
     glDisable(GL_CULL_FACE);
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     wlacz_teksture(22);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_dzialo_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dzialo_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dzialo_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 28);
         gluCylinder(kolo, 0.025*skala, 0.025*skala, 0.7*skala, 6, 1);
		glPopMatrix();
     glEnable(GL_CULL_FACE);
     wylacz_teksture();
	glEndList();

	obiektyrozm[ob_dziala]=1.1;
}

//parametry materialu aut
GLfloat mat_auto_ka[] = {0.70, 0.70, 0.72, 1.0};
GLfloat mat_auto_kd[] = {0.70, 0.70, 0.72, 1.0};
GLfloat mat_auto_ks[] = {0.85, 0.70, 0.70, 1.0};

void stworz_auto()
{
   const float skala=0.9;
   const
   float pkt[][3]={      0.1,       0,        0, //0
                     1.0/6.0, 3.0/6.0,        0, //1
                      7/12.0, 3.0/6.0,        0, //2
                     5.0/6.0, 5.0/6.0,        0, //3
                     5.0/6.0, 3.0/6.0,        0, //4
                         1.9, 3.0/6.0,        0, //5
                         1.9,       0,        0, //6
                  //druga strona, w zasadzie to samo, tylko inny Z
                         0.1,       0,  5.0/6.0, //7
                     1.0/6.0, 3.0/6.0,  5.0/6.0, //8
                      7/12.0, 3.0/6.0,  5.0/6.0, //9
                     5.0/6.0, 5.0/6.0,  5.0/6.0, //10
                     5.0/6.0, 3.0/6.0,  5.0/6.0, //11
                         1.9, 3.0/6.0,  5.0/6.0, // 12
                         1.9,       0,  5.0/6.0  //13
                   };

   float texlac[4]= {0.0, 0.2,  1.0, 0.6};
                    //punkty        wekt.normalne
/*   float lac[][6]= {1,0,2,           0,0,1,
                    2,0,6,           0,0,1,
                    2,6,3,           0,0,1,
                    3,6,4,           0,0,1,
                    4,6,5,           0,0,1,

                     9, 7, 8,        0,0,-1,
                    13, 7, 9,        0,0,-1,
                    10,13, 9,        0,0,-1,
                    11,13,10,        0,0,-1,
                    12,13,11,        0,0,-1
                   };*/
   float lac[][6]= {1,0,2,           0,0,1,
                    2,0,6,           0,0,1,
                    2,4,3,           0,0,1,
                    2,6,5,           0,0,1,

                     9, 7, 8,        0,0,-1,
                    13, 7, 9,        0,0,-1,
                    10,11, 9,        0,0,-1,
                    12,13, 9,        0,0,-1
                   };
                    //punkty        wekt.normalne        wspolrzedne textury [x1,y1, x2,y2]
   float lacq[][11]={0, 1, 8, 7,     -0.9, 0.1, 0,       0.0, 0.6, 0.1, 1.0,
                     1, 2, 9, 8,        0,   1, 0,       0.1, 0.6, 0.3, 1.0,
                     2, 3,10, 9,     -0.9, 0.1, 0,       0.3, 0.6,0.46, 1.0,
                     3, 4,11,10,        0,   1, 0,       0.3, 0.6,0.46, 1.0,
                     4, 5,12,11,      0.5, 0.5, 0,     0.465, 0.6, 0.8, 1.0,
                     5, 6,13,12,      0.9, 0.1, 0,       0.8, 0.6, 1.0, 1.0
                   };


	glNewList(listbase+ob_auta, GL_COMPILE);
		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);

         glTranslatef(-(5/12.0)*skala, 0.1, -1.0*skala);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_auto_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_auto_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_auto_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 128);
         wlacz_teksture(15);
         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=7; a++) {
                glNormal3f( lac[a][5], lac[a][4], lac[a][3]);
                for (int b=0; b<=2; b++) {
                    glTexCoord2f(pkt[(int)lac[a][b]][0] /2, pkt[(int)lac[a][b]][1] /2+texlac[1]);
                    glVertex3f( pkt[(int)lac[a][b]][2]*skala, pkt[(int)lac[a][b]][1]*skala, pkt[(int)lac[a][b]][0]*skala);
                }
            }
         glEnd();
         glBegin(GL_QUADS);
            for (int a=0; a<=5; a++) {
                glNormal3f( lacq[a][6], lacq[a][5], lacq[a][4]);
                for (int b=0; b<=3; b++) {
                    switch (b) {
                       case 0: glTexCoord2f(lacq[a][7],lacq[a][8]); break;
                       case 1: glTexCoord2f(lacq[a][9],lacq[a][8]); break;
                       case 2: glTexCoord2f(lacq[a][9],lacq[a][10]); break;
                       case 3: glTexCoord2f(lacq[a][7],lacq[a][10]); break;
                    }
                    glVertex3f( pkt[(int)lacq[a][b]][2]*skala, pkt[(int)lacq[a][b]][1]*skala, pkt[(int)lacq[a][b]][0]*skala);
                }
            }
         glEnd();
         wylacz_teksture();

        //kola
//        GLUquadricObj *kolo;
//        kolo = gluNewQuadric();
        gluQuadricDrawStyle(kolo, GLU_FILL);
        gluQuadricNormals(kolo, GLU_SMOOTH);
        gluQuadricOrientation(kolo, GLU_OUTSIDE);
        gluQuadricTexture(kolo, GLU_FALSE);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        glDisable(GL_CULL_FACE);
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0,0,0);
        glRotatef(90,0,1,0);
        for (int l=0; l<=1; l++)
          for (int p=0; p<=1; p++)
          {
            glPushMatrix();
               glTranslatef(-(5/12.0+p*1.1)*skala, 0.06, -0.01+l*(5/6.0+0.02)*skala);
               gluDisk(kolo, 0, 0.15, 8, 1);
            glPopMatrix();
          }
        glDisable(GL_COLOR_MATERIAL);

        glEnable(GL_CULL_FACE);
      glPopAttrib();
		glPopMatrix();
	glEndList();
	obiektyrozm[ob_auta]=1.2;
}

//parametry materialu pociagu
/*GLfloat mat_poci_ka[] = {0.66, 0.65, 0.68, 1.0};
GLfloat mat_poci_kd[] = {0.65, 0.65, 0.66, 1.0};
GLfloat mat_poci_ks[] = {0.50, 0.50, 0.80, 1.0};*/
GLfloat mat_poci_ka[] = {0.06, 0.05, 0.08, 1.0};
GLfloat mat_poci_kd[] = {0.15, 0.15, 0.16, 1.0};
GLfloat mat_poci_ks[] = {0.50, 0.50, 0.80, 1.0};

GLfloat mat_pocicz_ka[] = {0.30, 0.08, 0.03, 1.0};
GLfloat mat_pocicz_kd[] = {0.45, 0.15, 0.14, 1.0};

void stworz_lokomotywe()
{
   const float skala=1.2;
   const
   float pkt[][3]={        0,       0,     -0.4, //0
                         3.0,       0,     -0.4, //1
                         3.0,     1.0,     -0.4, //2
                         2.5,     1.0,     -0.4, //3
                         2.5,     0.4,     -0.4, //4
                           0,     0.4,     -0.4, //5
                  //druga strona, w zasadzie to samo, tylko inny Z
                           0,       0,      0.4, //6
                         3.0,       0,      0.4, //7
                         3.0,     1.0,      0.4, //8
                         2.5,     1.0,      0.4, //9
                         2.5,     0.4,      0.4, //10
                           0,     0.4,      0.4  //11
                   };

//   float texlac[4]= {0.0, 0.2,  1.0, 0.6};
                    //punkty        wekt.normalne
   float lac[][6]= {5,0,4,           0,0,1,
                    4,0,1,           0,0,1,
                    4,1,2,           0,0,1,
                    3,4,2,           0,0,1,

                    10, 6,11,        0,0,-1,
                     7, 6,10,        0,0,-1,
                     8, 7,10,        0,0,-1,
                     8,10, 9,        0,0,-1
                   };
                    //punkty        wekt.normalne        wspolrzedne textury [x1,y1, x2,y2]
   float lacq[][11]={11, 6, 0, 5,     -1.0,   0, 0,       0.0, 0.6, 0.1, 1.0,
                     11, 5, 4,10,        0,   1, 0,       0.1, 0.6, 0.3, 1.0,
                      9,10, 4, 3,     -1.0,   0, 0,       0.3, 0.6,0.46, 1.0,
                      9, 3, 2, 8,        0,   1, 0,      0.46, 0.6,0.62, 1.0,
                      2, 1, 7, 8,      1.0,   0, 0,      0.62, 0.6, 0.8, 1.0
                   };

//   GLUquadricObj *kolo;
//   kolo = gluNewQuadric();
   gluQuadricDrawStyle(kolo, GLU_FILL);
   gluQuadricNormals(kolo, GLU_SMOOTH);
   gluQuadricOrientation(kolo, GLU_OUTSIDE);
   gluQuadricTexture(kolo, GLU_FALSE);

	glNewList(listbase+ob_pociag, GL_COMPILE);
		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);

//         glTranslatef(-0.5*skala, 0.1, -1.0*skala);
         glTranslatef(0, 0.1, -1.5*skala);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_poci_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_poci_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_poci_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 120);
         //wlacz_teksture(15);
         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=7; a++) {
                glNormal3f( lac[a][5], lac[a][4], lac[a][3]);
                for (int b=0; b<=2; b++) {
                    //glTexCoord2f(pkt[(int)lac[a][b]][0] /2, pkt[(int)lac[a][b]][1] /2+texlac[1]);
                    glVertex3f( pkt[(int)lac[a][b]][2]*skala, pkt[(int)lac[a][b]][1]*skala, pkt[(int)lac[a][b]][0]*skala);
                }
            }
         glEnd();
         glBegin(GL_QUADS);
            for (int a=0; a<=4; a++) {
                glNormal3f( lacq[a][6], lacq[a][5], lacq[a][4]);
                for (int b=0; b<=3; b++) {
                    switch (b) {
                       case 0: glTexCoord2f(lacq[a][7],lacq[a][8]); break;
                       case 1: glTexCoord2f(lacq[a][9],lacq[a][8]); break;
                       case 2: glTexCoord2f(lacq[a][9],lacq[a][10]); break;
                       case 3: glTexCoord2f(lacq[a][7],lacq[a][10]); break;
                    }
                    glVertex3f( pkt[(int)lacq[a][b]][2]*skala, pkt[(int)lacq[a][b]][1]*skala, pkt[(int)lacq[a][b]][0]*skala);
                }
            }
         glEnd();

         //przod
         glPushMatrix();

           glTranslatef(0,0.55*skala,0.05*skala);
           gluCylinder(kolo, 0.36*skala, 0.36*skala, 2.5*skala, 10,1);
           glRotatef(180, 0,1,0);
           gluDisk(kolo, 0, 0.36*skala, 10,1);

		   glPopMatrix();

         //komin
         glPolygonMode(GL_FRONT, GL_FILL);
         glPolygonMode(GL_BACK, GL_FILL);
         glDisable(GL_CULL_FACE);
         for (int l=0; l<=2; l++) {
           glPushMatrix();
             glTranslatef(0,0.65*skala,(0.3+l*0.6)*skala);
             glRotatef(90, -1,0,0);
             gluCylinder(kolo, (0.08+l*0.03)*skala, (0.08+l*0.03)*skala, 0.4*skala, 6,1);
           glPopMatrix();
         }

         //wylacz_teksture();

        //kola
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.8,0.8,0.8);
        glRotatef(90,0,1,0);
        wlacz_teksture(21);
        gluQuadricTexture(kolo, GLU_TRUE);
        for (int l=0; l<=1; l++) {
          for (int p=0; p<=1; p++)
          {
            glPushMatrix();
               glTranslatef(-(0.2+p*0.5)*skala, 0.06, (-0.41+l*0.82)*skala);
               gluDisk(kolo, 0, 0.15, 8, 1);
            glPopMatrix();
          }
          for (int p=0; p<=2; p++)
          {
            glPushMatrix();
               glTranslatef(-(1.3+p*0.62)*skala, 0.12, (-0.41+l*0.82)*skala);
               gluDisk(kolo, 0, 0.27, 8, 1);
            glPopMatrix();
          }
        }
        wylacz_teksture();
        glDisable(GL_COLOR_MATERIAL);

        glEnable(GL_CULL_FACE);

      glPopAttrib();
		glPopMatrix();
	glEndList();
	obiektyrozm[ob_pociag]=1.7;
}

void stworz_weglarke()
{
   const float skala=1.2;
   const
   float pkt[][3]={        0,       0,     -0.4, //0
                         1.3,       0,     -0.4, //1
                         1.3,     0.7,     -0.4, //2
                           0,     0.7,     -0.4, //3
                  //druga strona, w zasadzie to samo, tylko inny Z
                           0,       0,      0.4, //4
                         1.3,       0,      0.4, //5
                         1.3,     0.7,      0.4, //6
                           0,     0.7,      0.4, //7
                   };

//   float texlac[4]= {0.0, 0.2,  1.0, 0.6};
                    //punkty        wekt.normalne
   float lac[][6]= {0,1,2,           0,0,1,
                    0,2,3,           0,0,1,

                    6,5,4,           0,0,-1,
                    7,6,4,           0,0,-1
                   };
                    //punkty        wekt.normalne        wspolrzedne textury [x1,y1, x2,y2]
   float lacq[][11]={ 0, 3, 7, 4,     -1.0,   0, 0,       0.0, 0.6, 0.1, 1.0,
                      3, 2, 6, 7,        0,   1, 0,       0.1, 0.6, 0.3, 1.0,
                      2, 1, 5, 6,      1.0,   0, 0,       0.3, 0.6,0.46, 1.0
                   };

//   GLUquadricObj *kolo;
//   kolo = gluNewQuadric();
   gluQuadricDrawStyle(kolo, GLU_FILL);
   gluQuadricNormals(kolo, GLU_SMOOTH);
   gluQuadricOrientation(kolo, GLU_OUTSIDE);
   gluQuadricTexture(kolo, GLU_FALSE);

	glNewList(listbase+ob_pociag+1, GL_COMPILE);
		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);

         glTranslatef(0, 0.1, -0.65*skala);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_poci_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_poci_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_poci_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 12);
         //wlacz_teksture(15);
         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=3; a++) {
                glNormal3f( lac[a][5], lac[a][4], lac[a][3]);
                for (int b=0; b<=2; b++) {
                    //glTexCoord2f(pkt[(int)lac[a][b]][0] /2, pkt[(int)lac[a][b]][1] /2+texlac[1]);
                    glVertex3f( pkt[(int)lac[a][b]][2]*skala, pkt[(int)lac[a][b]][1]*skala, pkt[(int)lac[a][b]][0]*skala);
                }
            }
         glEnd();
         glBegin(GL_QUADS);
            for (int a=0; a<=2; a++) {
                glNormal3f( lacq[a][6], lacq[a][5], lacq[a][4]);
                for (int b=0; b<=3; b++) {
                    switch (b) {
                       case 0: glTexCoord2f(lacq[a][7],lacq[a][8]); break;
                       case 1: glTexCoord2f(lacq[a][9],lacq[a][8]); break;
                       case 2: glTexCoord2f(lacq[a][9],lacq[a][10]); break;
                       case 3: glTexCoord2f(lacq[a][7],lacq[a][10]); break;
                    }
                    glVertex3f( pkt[(int)lacq[a][b]][2]*skala, pkt[(int)lacq[a][b]][1]*skala, pkt[(int)lacq[a][b]][0]*skala);
                }
            }
         glEnd();

         //wylacz_teksture();

        //kola
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.8,0.8,0.8);
        wlacz_teksture(21);
        gluQuadricTexture(kolo, GLU_TRUE);
        glDisable(GL_CULL_FACE);
        glRotatef(90,0,1,0);
        for (int l=0; l<=1; l++) {
          for (int p=0; p<=3; p++)
          {
            glPushMatrix();
               glTranslatef(-(0.13+p*0.3)*skala, 0.06, (-0.41+l*0.82)*skala);
               gluDisk(kolo, 0, 0.15, 8, 1);
            glPopMatrix();
          }
        }
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_CULL_FACE);
        wylacz_teksture();

      glPopAttrib();
		glPopMatrix();
	glEndList();
	obiektyrozm[ob_pociag+1]=1.0;
}

void stworz_wagon()
{
   const float skala=1.2;
   const
   float pkt[][3]={        0,       0,     -0.4, //0
                         2.3,       0,     -0.4, //1
                         2.3,     1.0,     -0.4, //2
                           0,     1.0,     -0.4, //3
                  //druga strona, w zasadzie to samo, tylko inny Z
                           0,       0,      0.4, //4
                         2.3,       0,      0.4, //5
                         2.3,     1.0,      0.4, //6
                           0,     1.0,      0.4, //7
                   };

//   float texlac[4]= {0.0, 0.2,  1.0, 0.6};
                    //punkty        wekt.normalne
   float lac[][6]= {0,1,2,           0,0,1,
                    0,2,3,           0,0,1,

                    6,5,4,           0,0,-1,
                    7,6,4,           0,0,-1
                   };
                    //punkty        wekt.normalne        wspolrzedne textury [x1,y1, x2,y2]
   float lacq[][11]={ 0, 3, 7, 4,     -1.0,   0, 0,       0.0, 0.6, 0.1, 1.0,
                      3, 2, 6, 7,        0,   1, 0,       0.1, 0.6, 0.3, 1.0,
                      2, 1, 5, 6,      1.0,   0, 0,       0.3, 0.6,0.46, 1.0
                   };

//   GLUquadricObj *kolo;
//   kolo = gluNewQuadric();
   gluQuadricDrawStyle(kolo, GLU_FILL);
   gluQuadricNormals(kolo, GLU_SMOOTH);
   gluQuadricOrientation(kolo, GLU_OUTSIDE);
   gluQuadricTexture(kolo, GLU_FALSE);

	glNewList(listbase+ob_pociag+2, GL_COMPILE);
		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);

         glTranslatef(0, 0.1, -1.15*skala);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_poci_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_poci_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_poci_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 12);
         //wlacz_teksture(15);
         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=3; a++) {
                glNormal3f( lac[a][5], lac[a][4], lac[a][3]);
                for (int b=0; b<=2; b++) {
                    //glTexCoord2f(pkt[(int)lac[a][b]][0] /2, pkt[(int)lac[a][b]][1] /2+texlac[1]);
                    glVertex3f( pkt[(int)lac[a][b]][2]*skala, pkt[(int)lac[a][b]][1]*skala, pkt[(int)lac[a][b]][0]*skala);
                }
            }
         glEnd();
         glBegin(GL_QUADS);
            for (int a=0; a<=2; a++) {
                glNormal3f( lacq[a][6], lacq[a][5], lacq[a][4]);
                for (int b=0; b<=3; b++) {
                    switch (b) {
                       case 0: glTexCoord2f(lacq[a][7],lacq[a][8]); break;
                       case 1: glTexCoord2f(lacq[a][9],lacq[a][8]); break;
                       case 2: glTexCoord2f(lacq[a][9],lacq[a][10]); break;
                       case 3: glTexCoord2f(lacq[a][7],lacq[a][10]); break;
                    }
                    glVertex3f( pkt[(int)lacq[a][b]][2]*skala, pkt[(int)lacq[a][b]][1]*skala, pkt[(int)lacq[a][b]][0]*skala);
                }
            }
         glEnd();

         //wylacz_teksture();

        //kola
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        glEnable(GL_COLOR_MATERIAL);
        glDisable(GL_CULL_FACE);
        glColor3f(0.8,0.8,0.8);
        wlacz_teksture(21);
        gluQuadricTexture(kolo, GLU_TRUE);
        glRotatef(90,0,1,0);
        for (int l=0; l<=1; l++) {
          for (int p=0; p<=1; p++)
          {
            glPushMatrix();
               glTranslatef(-(0.20+p*0.3)*skala, 0.07, (-0.41+l*0.82)*skala);
               gluDisk(kolo, 0, 0.18, 8, 1);
            glPopMatrix();
          }
          for (int p=0; p<=1; p++)
          {
            glPushMatrix();
               glTranslatef(-(1.70+p*0.3)*skala, 0.07, (-0.41+l*0.82)*skala);
               gluDisk(kolo, 0, 0.18, 8, 1);
            glPopMatrix();
          }
        }
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_CULL_FACE);
        wylacz_teksture();

      glPopAttrib();
		glPopMatrix();
	glEndList();
	obiektyrozm[ob_pociag+2]=1.0;
}

void stworz_lampy()
{
   gluQuadricDrawStyle(drzewo, GLU_FILL);
   gluQuadricNormals(drzewo, GLU_SMOOTH);
   gluQuadricOrientation(drzewo, GLU_OUTSIDE);
   gluQuadricTexture(drzewo, GLU_TRUE);

	glNewList(listbase+ob_lampy, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_dpn_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dpn_ka);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dpn_ka);
			glMaterialf(GL_FRONT, GL_SHININESS, 90);
		   glTranslatef(0.0, 0.0, 0.1);
			glPushMatrix();
				glRotatef(-90.0, 1.0, 0.0, 0.0);
	      	gluCylinder(drzewo, 0.02, 0.015, 2.0, 3,1);
			glPopMatrix();

         glPolygonMode(GL_BACK, GL_FILL);
         glDisable(GL_CULL_FACE);
			glMaterialf(GL_FRONT, GL_SHININESS, 0);
			glPushMatrix();
				glTranslatef(0.0, 1.7, -0.03);
				glRotatef(130.0, 1.0, 0.0, 0.0);
	      	gluCylinder(drzewo, 0.015, 0.15, 0.15, 8,1);
			glPopMatrix();
         glEnable(GL_CULL_FACE);
		glPopMatrix();
	glEndList();

	obiektyrozm[ob_lampy]=0.6;
}

//parametry materialu barek
GLfloat mat_barka_ka[] = {0.12, 0.15, 0.16, 1.0};
GLfloat mat_barka_kd[] = {0.35, 0.40, 0.40, 1.0};
GLfloat mat_barka_ks[] = {0.20, 0.25, 0.30, 1.0};

void stworz_barki()
{
   const float skalab=3.0;
   const float zanurz=0.2;

   const
   float pkt[][3]={      0.25,      0,     -1.1, //0
                         0.25,      0,      0.7, //1
                         0.2,     0.2,      1.0, //2
                           0,     0.5,      1.2, //3 srodek przod
                         0.2,     0.45,      1.1, //4
                         0.3,     0.42,      0.7, //5
                         0.3,     0.41,     -1.1, //6

                        -0.25,      0,     -1.1, //7
                        -0.25,      0,      0.7, //8
                        -0.2,     0.2,      1.0, //9
                           0,     0.5,      1.2, //10 srodek przod
                        -0.2,     0.45,      1.1, //11
                        -0.3,     0.42,      0.7, //12
                        -0.3,     0.41,     -1.1  //13


                   };

                    //punkty           wekt.normalne
   float lac[][6]= { //prawy bok:
                     0, 5, 6,           0,   0, 1.0,
                     0, 1, 5,           0,   0, 1.0,
                     1, 2, 4,        0.15,  0, 0.85,
                     1, 4, 5,         0.3,   0, 0.7,
                     2, 3, 4,         0.6,   0, 0.4,

                     //lewy bok:
                    13,12, 7,           0,   0,-1.0,
                    12, 8, 7,           0,   0,-1.0,
                    11, 9, 8,        0.15,  0,-0.85,
                    12,11, 8,         0.3,   0,-0.7,
                    11, 3, 9,         0.6,   0,-0.4,

                     //tyl:
                     7, 0, 6,          -1,   0,   0,
                    13, 7, 6,          -1,   0,   0,

                     //przod:
                     1, 8, 2,         0.4,-0.6,   0,
                     2, 8, 9,         0.4,-0.6,   0,
                     2, 9, 3,         0.6,-0.4,   0,

                     //gora:
                     6,12,13,           0, 1.0,   0,
                     6, 5,12,           0, 1.0,   0,
                     5,11,12,        -0.15,0.85,   0,
                     5, 4,11,        -0.1, 0.9,   0,
                     4, 3,11,        -0.2, 0.8,   0

                   };


	glNewList(listbase+ob_barki, GL_COMPILE);
		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);
         glMaterialfv(GL_FRONT, GL_AMBIENT, mat_barka_ka);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_barka_kd);
         glMaterialfv(GL_FRONT, GL_SPECULAR, mat_barka_ks);
         glMaterialf(GL_FRONT, GL_SHININESS, 40);
         glFrontFace (GL_CCW);
         glPolygonMode(GL_FRONT, GL_FILL);
         glCullFace(GL_BACK);

         wlacz_teksture(24);

         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=19; a++) {
                float wek[3];

                wek[0]=lac[a][3];
                wek[1]=lac[a][4];
                wek[2]=lac[a][5];
                normalize0(wek);
                glNormal3fv(wek);

                for (int b=0; b<=2; b++) {
                    glTexCoord2f((pkt[(int)lac[a][b]][2]+1.1)/2+pkt[(int)lac[a][b]][0]+0.25, pkt[(int)lac[a][b]][1]);
                    //glTexCoord2f(pkt[(int)lac[a][b]][0] /2, pkt[(int)lac[a][b]][1] /2+texlac[1]);
                    glVertex3f( -pkt[(int)lac[a][b]][0]*skalab, (pkt[(int)lac[a][b]][1]-zanurz)*skalab, pkt[(int)lac[a][b]][2]*skalab);
                }
            }
         glEnd();

		   glPushMatrix();
             glTranslatef(0,(0.41-zanurz)*skalab,-0.8*skalab);
             texklocek(0.2*skalab, 0.2*skalab, 0.15*skalab);
		   glPopMatrix();

		   glPushMatrix();
             glPolygonMode(GL_FRONT, GL_FILL);
             glPolygonMode(GL_BACK, GL_FILL);
             glDisable(GL_CULL_FACE);
             glTranslatef(0,0.2*skalab,0.8*skalab);
             glPushMatrix();
                 glRotatef(90, -1,0,0);
                 gluCylinder(kolo, 0.03*skalab, 0.026*skalab, 0.5*skalab, 6,1);
             glPopMatrix();
             glTranslatef(0,0,0.2*skalab);
             glRotatef(110, -1,0,0);
             gluCylinder(kolo, 0.01*skalab, 0.01*skalab, 0.545*skalab, 6,1);
		   glPopMatrix();

         wylacz_teksture();

         //wylacz_teksture();

      glPopAttrib();
		glPopMatrix();
	glEndList();

	obiektyrozm[ob_barki]=1.5;


   //wiezyczka
   const float skala=2.0;
	glNewList(listbase+ob_barki+1, GL_COMPILE);
   const
   float wpkt[][3]={     -0.1,     0.2,      0.15, //0
                          0.1,     0.2,      0.15, //1
                         0.25,    0.27,      0.2,  //2
                         0.25,    0.34,      0.2,  //3
                          0.1,     0.4,      0.15, //4
                         -0.1,     0.4,      0.15, //5
                        -0.15,    0.34,      0.2,  //6
                        -0.15,    0.27,      0.2,  //7
                  //druga strona, w zasadzie to samo, tylko inny Z
                         -0.1,     0.2,     -0.15, //8
                          0.1,     0.2,     -0.15, //9
                         0.25,    0.27,     -0.2,  //10
                         0.25,    0.34,     -0.2,  //11
                          0.1,     0.4,     -0.15, //12
                         -0.1,     0.4,     -0.15, //13
                        -0.15,    0.34,     -0.2,  //14
                        -0.15,    0.27,     -0.2   //15

                   };

   float wtexlac[4]= {0.0, 0.2,  1.0, 0.6};
                    //punkty        wekt.normalne
   float wlac[][6]= { 0, 1, 2,           0,-0.3, 0.7,
                      0, 2, 7,           0,-0.3, 0.7,
                      7, 2, 3,           0,   0,   1,
                      6, 7, 3,           0,   0,   1,
                      5, 6, 4,           0, 0.3,-0.7,
                      4, 6, 3,           0, 0.3,-0.7,

                     10, 9, 8,           0,-0.3,-0.7,
                     15,10, 8,           0,-0.3,-0.7,
                     11,10,15,           0,   0,   1,
                     11,15,14,           0,   0,   1,
                     12,14,13,           0, 0.3, 0.7,
                     11,14,12,           0, 0.3, 0.7

                   };
                    //punkty        wekt.normalne        wspolrzedne textury [x1,y1, x2,y2]
   float wlacq[][11]={ 0, 7,15, 8,     -0.5,-0.5, 0,       0.0, 0.0, 1.0, 1.0,
                       7, 6,14,15,     -1.0,   0, 0,       0.0, 0.0, 1.0, 1.0,
                       6, 5,13,14,     -0.5, 0.5, 0,       0.0, 0.0, 1.0, 1.0,
                       5, 4,12,13,        0, 1.0, 0,       0.0, 0.0, 1.0, 1.0,
                       4, 3,11,12,      0.5, 0.5, 0,       0.0, 0.0, 1.0, 1.0,
                       3, 2,10,11,      1.0,   0, 0,       0.0, 0.0, 1.0, 1.0,
                       2, 1, 9,10,      0.5,-0.5, 0,       0.0, 0.0, 1.0, 1.0
                      };

		glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);
         glMaterialfv(GL_FRONT, GL_AMBIENT, mat_barka_ka);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_barka_kd);
         glMaterialfv(GL_FRONT, GL_SPECULAR, mat_barka_ks);
         glMaterialf(GL_FRONT, GL_SHININESS, 70);
         glFrontFace (GL_CW);
         wlacz_teksture(24);
         glBegin(GL_TRIANGLES);
            //przy Vertex3f kolejnosc jest od 2 do 0, zeby zamienic X i Z miejscami, w celu obrocenia od razu o 90 stopni
            for (int a=0; a<=11; a++) {
                glNormal3f( wlac[a][5], wlac[a][4], wlac[a][3]);
                for (int b=0; b<=2; b++) {
                    glTexCoord2f(wpkt[(int)wlac[a][b]][0] /2, wpkt[(int)wlac[a][b]][1] /2+wtexlac[1]);
                    glVertex3f( wpkt[(int)wlac[a][b]][2]*skala, (wpkt[(int)wlac[a][b]][1]-0.2)*skala+(zanurz)*skalab, wpkt[(int)wlac[a][b]][0]*skala);
                }
            }
         glEnd();
         glBegin(GL_QUADS);
            for (int a=0; a<=6; a++) {
                glNormal3f( wlacq[a][6], wlacq[a][5], wlacq[a][4]);
                for (int b=0; b<=3; b++) {
                    switch (b) {
                       case 0: glTexCoord2f(wlacq[a][7],wlacq[a][8]); break;
                       case 1: glTexCoord2f(wlacq[a][9],wlacq[a][8]); break;
                       case 2: glTexCoord2f(wlacq[a][9],wlacq[a][10]); break;
                       case 3: glTexCoord2f(wlacq[a][7],wlacq[a][10]); break;
                    }
                    glVertex3f( wpkt[(int)wlacq[a][b]][2]*skala, (wpkt[(int)wlacq[a][b]][1]-0.2)*skala+(zanurz)*skalab, wpkt[(int)wlacq[a][b]][0]*skala);
                }
            }
         glEnd();
         wylacz_teksture();
      glPopAttrib();
		glPopMatrix();
      glTranslatef( 0, (0.33-0.2)*skala+(zanurz)*skalab, 0.24*skala );
	glEndList();

   //lufa
	glNewList(listbase+ob_barki+2, GL_COMPILE);
      gluQuadricDrawStyle(kolo, GLU_FILL);
      gluQuadricNormals(kolo, GLU_SMOOTH);
      gluQuadricOrientation(kolo, GLU_OUTSIDE);
      gluQuadricTexture(kolo, GLU_TRUE);
      wlacz_teksture(24);
		glPushMatrix();
         glMaterialfv(GL_FRONT, GL_AMBIENT, mat_barka_ka);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_barka_kd);
         glMaterialfv(GL_FRONT, GL_SPECULAR, mat_barka_ks);
         glMaterialf(GL_FRONT, GL_SHININESS, 70);
         gluCylinder(kolo, 0.025*skala, 0.025*skala, 0.7*skala, 6, 1);
		glPopMatrix();
      wylacz_teksture();
	glEndList();


}

void stworz_pocisk()
{
   const
   float pkt[][3]={   0, 0.3,   0, //0
                    0.2,   0, 0.1, //1
                   -0.1,   0,-0.1, //2
                   -0.1,   0, 0.1, //3
                      0, 5.0, 0.0  //4
                   };
   int   lac[][3]={ 0,1,2,
                    0,2,3,
                    0,3,1,
                    1,4,2,
                    2,4,3,
                    3,4,1
                   };

	glNewList(listbase+ob_pociski, GL_COMPILE);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
      glEnable(GL_BLEND);
      glDepthMask(GL_FALSE);
      glPolygonMode(GL_FRONT, GL_FILL);
      glPolygonMode(GL_BACK, GL_FILL);
      glDisable(GL_CULL_FACE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_poc_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_poc_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_poc_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 10);
			glPushMatrix();
            glBegin(GL_TRIANGLES);

              for (int a=0; a<=5; a++) {
                  for (int b=0; b<=2; b++) {
                      glVertex3f( pkt[lac[a][b]][0], pkt[lac[a][b]][1], pkt[lac[a][b]][2]);
                  }
              }

            glEnd();
			glPopMatrix();
		glPopMatrix();
      glEnable(GL_CULL_FACE);
 	   glDepthMask(GL_TRUE);
 	   glDisable(GL_BLEND);
    glPopAttrib();
	glEndList();
	obiektyrozm[ob_pociski]=0.4;
}

void stworz_bombe()
{
//	GLUquadricObj *kula;
//   kula = gluNewQuadric();
   gluQuadricDrawStyle(kula, GLU_FILL);
   gluQuadricNormals(kula, GLU_SMOOTH);
   gluQuadricOrientation(kula, GLU_OUTSIDE);
   gluQuadricTexture(kula, GLU_TRUE);

	glNewList(listbase+ob_pociski+1, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_bom_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_bom_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_bom_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 90);
			glPushMatrix();
				glScalef(0.3, 1.0, 0.3);
				gluSphere(kula, 1.5, 8, 8);
			glPopMatrix();
			glTranslatef(0.0, 0.9, 0.0);
			klocek(0.5,0.05, 0.7);
			glRotatef(90, 0.0, 1.0, 0.0);
			klocek(0.5,0.05, 0.7);
		glPopMatrix();
	glEndList();
	obiektyrozm[ob_pociski+1]=0.4;
}

//parametry materialu wybuchow
GLfloat mat_wyb_ka[] = {0.70, 0.50, 0.03, 1.0};
GLfloat mat_wyb_kd[] = {0.70, 0.50, 0.03, 1.0};
GLfloat mat_wyb_ks[] = {0.0 , 0.00, 0.0 , 1.0};

void stworz_wybuch()
{
//	GLUquadricObj *kula;
//   kula = gluNewQuadric();
   gluQuadricDrawStyle(kula, GLU_FILL);
   gluQuadricNormals(kula, GLU_SMOOTH);
   gluQuadricOrientation(kula, GLU_OUTSIDE);
   gluQuadricTexture(kula, GLU_FALSE);

	glNewList(listbase+ob_wybuchy, GL_COMPILE);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_wyb_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_wyb_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_wyb_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 0);
     	   gluSphere(kula, 1.0, 15, 15);
		glPopMatrix();
      glEnable(GL_CULL_FACE);
    glPopAttrib();
	glEndList();
	obiektyrozm[ob_wybuchy]=0.4;
}

//parametry materialu wybuchow
GLfloat mat_ogi_ka[] = {0.70, 0.50, 0.03, 0.5};
GLfloat mat_ogi_kd[] = {0.70, 0.00, 0.03, 0.5};
GLfloat mat_ogi_ks[] = {0.0 , 1.00, 0.0 , 0.5};

void stworz_ogien() //ogien na ziemi, po rozwalonych obiektach
{
//	GLUquadricObj *kula;
//   kula = gluNewQuadric();
   gluQuadricDrawStyle(kula, GLU_FILL);
   gluQuadricNormals(kula, GLU_FLAT);
   gluQuadricOrientation(kula, GLU_OUTSIDE);
   gluQuadricTexture(kula, GLU_FALSE);

	glNewList(listbase+ob_ogien, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ogi_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_ogi_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ogi_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 90);
         glScalef(1,2,1);
	     	gluSphere(kula, 0.4, 4, 4);
		glPopMatrix();

		glPushMatrix();
			glMaterialf(GL_FRONT, GL_SHININESS, 10);
         GLfloat rozm=1.5;
         GLfloat rozm2=rozm*2;
				wlacz_teksture(18);
              glTranslatef(0,-0.5,0);
              for (int i=0; i<=1; i++)
              {
                glRotatef(90.0,0,1,0);
                glBegin(GL_QUADS);
                  glTexCoord2f(0.0, 1.0); glVertex3f(-rozm,rozm2,0);
                  glTexCoord2f(0.0, 0.0); glVertex3f(-rozm,0,0);
                  glTexCoord2f(1.0, 0.0); glVertex3f( rozm,0,0);
                  glTexCoord2f(1.0, 1.0); glVertex3f( rozm,rozm2,0);
                glEnd();
              }
				wylacz_teksture();

		glPopMatrix();
	glEndList();
	obiektyrozm[ob_ogien]=0.2;
}

void stworz_ogien_sam() //ogien sam, tylko sprajt
{
	glNewList(listbase+ob_ogien+1, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ogi_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_ogi_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ogi_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 10);
         GLfloat rozm=1.5;
         GLfloat rozm2=rozm*2;
				wlacz_teksture(18);
              glTranslatef(0,-0.5,0);
              for (int i=0; i<=1; i++)
              {
                glRotatef(90.0,0,1,0);
                glBegin(GL_QUADS);
                  glTexCoord2f(0.0, 1.0); glVertex3f(-rozm,rozm2,0);
                  glTexCoord2f(0.0, 0.0); glVertex3f(-rozm,0,0);
                  glTexCoord2f(1.0, 0.0); glVertex3f( rozm,0,0);
                  glTexCoord2f(1.0, 1.0); glVertex3f( rozm,rozm2,0);
                glEnd();
              }
				wylacz_teksture();

		glPopMatrix();
	glEndList();
	obiektyrozm[ob_ogien+1]=0.2;
}


//parametry materialu budynkow scian
GLfloat mat_lotn_ka[] = {0.32, 0.34, 0.30, 1.0};
GLfloat mat_lotn_kd[] = {0.32, 0.34, 0.30, 1.0};
GLfloat mat_lotn_ks[] = {0.15, 0.20, 0.15, 1.0};

void stworz_lotnisko(int czyje)
{
	glNewList(listbase+ob_lotnisko+czyje, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_lotn_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_lotn_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_lotn_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 120);
         float szerokosc=3*dkrok;
         float dlugosc=2*dkrok;

         wlacz_teksture(5);
         glBegin(GL_QUADS);
             glNormal3f (0.0, 1.0, 0.0);
             glTexCoord2f(1, 0);		glVertex3f ( szerokosc, 0,-dlugosc);
             glTexCoord2f(0, 0);		glVertex3f (-szerokosc, 0,-dlugosc);
             glTexCoord2f(0, 1);		glVertex3f (-szerokosc, 0, 0);
             glTexCoord2f(1, 1);		glVertex3f ( szerokosc, 0, 0);
         glEnd();
         wylacz_teksture();

		glPopMatrix();
	glEndList();
	obiektyrozm[ob_lotnisko+czyje]=0.0;
}

void stworz_ulice(int co, int tex)
{
	glNewList(listbase+co, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_lotn_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_lotn_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_lotn_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 70);
         float szerokosc=dkrok;
         float dlugosc=2*dkrok;

         wlacz_teksture(tex);
         glBegin(GL_QUADS);
             glNormal3f (0.0, 1.0, 0.0);
             glTexCoord2f(1, 0);		glVertex3f ( szerokosc, 0,-dlugosc);
             glTexCoord2f(0, 0);		glVertex3f (-szerokosc, 0,-dlugosc);
             glTexCoord2f(0, 1);		glVertex3f (-szerokosc, 0, 0);
             glTexCoord2f(1, 1);		glVertex3f ( szerokosc, 0, 0);
         glEnd();
         wylacz_teksture();

		glPopMatrix();
	glEndList();
	obiektyrozm[co]=0.0;
}

void stworz_most(int co, int tex)
{
	glNewList(listbase+co, GL_COMPILE);
		glPushMatrix();
       glPushAttrib(GL_ALL_ATTRIB_BITS);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_lotn_ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_lotn_kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_lotn_ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 20);

            float szerokosc=dkrok;
            float dlugosc=2*dkrok;

            glPolygonMode(GL_FRONT, GL_FILL);
//            glPolygonMode(GL_BACK, GL_POINT);
            glCullFace(GL_BACK);

		      wlacz_teksture(tex);
            glBegin(GL_QUADS);
                glNormal3f (0.0, 1.0, 0.0);
                glTexCoord2f(1, 0);		glVertex3f ( szerokosc, 0,-dlugosc);
                glTexCoord2f(0, 0);		glVertex3f (-szerokosc, 0,-dlugosc);
                glTexCoord2f(0, 1);		glVertex3f (-szerokosc, 0, 0);
                glTexCoord2f(1, 1);		glVertex3f ( szerokosc, 0, 0);
            glEnd();
				wylacz_teksture();

		      wlacz_teksture(7);
            //spod mostu
            glBegin(GL_QUADS);
                glNormal3f (0.0, 1.0, 0.0);
                glTexCoord2f(1, 1);		glVertex3f ( szerokosc, -0.10, 0);
                glTexCoord2f(0, 1);		glVertex3f (-szerokosc, -0.10, 0);
                glTexCoord2f(0, 0);		glVertex3f (-szerokosc, -0.10,-dlugosc);
                glTexCoord2f(1, 0);		glVertex3f ( szerokosc, -0.10,-dlugosc);
            glEnd();
            //bok
	         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDisable(GL_CULL_FACE);
            glBegin(GL_QUADS);
                glNormal3f (-1.0, 0.0, 0.0);
                glTexCoord2f(  0, 0.2);		glVertex3f (-szerokosc, 0.2,-dlugosc);
                glTexCoord2f(  0,   0);		glVertex3f (-szerokosc,-0.2,-dlugosc);
                glTexCoord2f(  1,   0);		glVertex3f (-szerokosc,-0.2, 0);
                glTexCoord2f(  1, 0.2);		glVertex3f (-szerokosc, 0.2, 0);
            glEnd();
            //wystajace
            glBegin(GL_QUADS);
                glNormal3f (-1.0, 0.0, 0.0);
                glTexCoord2f(  0, 0.4);		glVertex3f (-szerokosc, 0.5,-dlugosc/2.0);
                glTexCoord2f(  0,   0);		glVertex3f (-szerokosc, 0.0,-dlugosc/2.0);
                glTexCoord2f(0.6,   0);		glVertex3f (-szerokosc, 0.0,-dlugosc/5.0);
                glTexCoord2f(0.6, 0.4);		glVertex3f (-szerokosc, 0.5,-dlugosc/5.0);
            glEnd();
            //bok
            glBegin(GL_QUADS);
                glNormal3f ( 1.0, 0.0, 0.0);
                glTexCoord2f(  0, 0.2);		glVertex3f ( szerokosc, 0.2,-dlugosc);
                glTexCoord2f(  0, 0.2);		glVertex3f ( szerokosc,-0.2,-dlugosc);
                glTexCoord2f(  1, 0.2);		glVertex3f ( szerokosc,-0.2, 0);
                glTexCoord2f(  1, 0.2);		glVertex3f ( szerokosc, 0.2, 0);
            glEnd();
            //wystajace
            glBegin(GL_QUADS);
                glNormal3f ( 1.0, 0.0, 0.0);
                glTexCoord2f(0, 1);		glVertex3f ( szerokosc, 0.5,-dlugosc/2.0);
                glTexCoord2f(0, 0);		glVertex3f ( szerokosc, 0.0,-dlugosc/2.0);
                glTexCoord2f(1, 0);		glVertex3f ( szerokosc, 0.0,-dlugosc/5.0);
                glTexCoord2f(1, 1);		glVertex3f ( szerokosc, 0.5,-dlugosc/5.0);
            glEnd();
            glEnable(GL_CULL_FACE);

            glPolygonMode(GL_FRONT, GL_FILL);
//            glPolygonMode(GL_BACK, GL_POINT);
            glCullFace(GL_BACK);
            glTranslatef(0,-20.10,0/*-dlugosc/2.0*/);
            texklocek(20.0,szerokosc*0.9,dlugosc/8.0, 20, 1, 0.5);
				wylacz_teksture();

       glPopAttrib();
		glPopMatrix();
	glEndList();
	obiektyrozm[co]=dkrok*0.8;
}

void stworz_smieci()
{
	glNewList(listbase+ob_smiec, GL_COMPILE);
     glPushMatrix();
       glMaterialf(GL_FRONT, GL_SHININESS, 20);
       klocek(0.1, 0.1, 0.1);
     glPopMatrix();
	glEndList();

	obiektyrozm[ob_smiec]=0.1;
}



////////////
void stworz_listy()
{
   listbase = glGenLists(128);
   glListBase(listbase);

	stworz_lotnisko(0);
	stworz_lotnisko(1);
	stworz_ulice(ob_ulice, 6);
	stworz_ulice(ob_ulice+1, 16);
	stworz_most(ob_mosty, 6);
	stworz_most(ob_mosty+1, 16);

	stworz_lampy();

	stworz_budynek();
	stworz_budynek2();
	stworz_budynek3();

   for (int a=0; a<=2; a++) stworz_hangar(a);

	stworz_drzewo();

	stworz_czolg();
	stworz_dzialo();
	stworz_auto();

	stworz_barki();

	stworz_lokomotywe();
	stworz_weglarke();
	stworz_wagon();

	stworz_pocisk();
	stworz_bombe();
	stworz_wybuch();
   stworz_ogien();
   stworz_ogien_sam();

   stworz_smieci();
}
