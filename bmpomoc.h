
//pomocnicze
void	normalize1(GLfloat vec[])
{
	double Length=sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
	if (Length==0.0) Length=1.0;
	vec[0] /=Length;
	vec[1] /=Length;
	vec[2] /=Length;
}

// ---------------------------------------------------------------------------
void	cross_prod(GLfloat in1[],GLfloat in2[],GLfloat out[])
{
	out[0]=(in1[1]*in2[2])-(in2[1]*in1[2]);
	out[1]=(in1[2]*in2[0])-(in2[2]*in1[0]);
	out[2]=(in1[0]*in2[1])-(in2[0]*in1[1]);
	normalize1(out);
}

// ---------------------------------------------------------------------------
int jaki_to_kat(float dx, float dy)
{
	float kk0;

	 if (dx>0) {
		if (dy>0) kk0 =atan(dy/dx)+M_PI/2.;
			else kk0 =atan(dy/dx)+M_PI/2.;
	 } else if (dx<0) {
		if (dy>0) kk0 =atan(dy/dx)+(3./2.)*M_PI;
			  else kk0 =atan(dy/dx)+(3./2.)*M_PI;
	 } else {
		if (dy>0) kk0 =M_PI;
			  else kk0 =0;
	 }
	 return floor( (kk0/(M_PI/180.0)) );
};

// ---------------------------------------------------------------------------
int jaki_to_katF(float dx, float dy)
{
	float kk0;

	 if (dx>0) {
		if (dy>0) kk0 =atan(dy/dx)+M_PI/2.;
			else kk0 =atan(dy/dx)+M_PI/2.;
	 } else if (dx<0) {
		if (dy>0) kk0 =atan(dy/dx)+(3./2.)*M_PI;
			  else kk0 =atan(dy/dx)+(3./2.)*M_PI;
	 } else {
		if (dy>0) kk0 =M_PI;
			  else kk0 =0;
	 }
	 return (kk0/(M_PI/180.0)) ;
};


// ---------------------------------------------------------------------------
void normalize0(GLfloat *vec)
{
  GLfloat len = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
  if (!len) return;
  vec[0] /= len;
  vec[1] /= len;
  vec[2] /= len;
}

// ---------------------------------------------------------------------------
void vertex_norm(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat norm[3];
	norm[0] = x;
	norm[1] = y;
	norm[2] = z;
	normalize0(norm);
	glNormal3fv(norm);
	glVertex3f(x,y,z);
}

// ---------------------------------------------------------------------------
//zwraca pozycje Y terenu w pozycji X i Z na ekranie (wzgledem poczatku ukladu wsp.)
float gdzie_y(float x, float z)
{
	float nx, nz;

	nx =  (x+dx0)/dkrok;
	nz =  (-z + dz0) /dkrok;

   x=x/dkrok;
   z=z/dkrok;

   float rx = fmod( fabs(x),(int) floor(fabs(x)) );
   float rz = fmod( fabs(z),(int) floor(fabs(z)) );

   if (x<0) rx=1-rx;
   if (z<0) rz=1-rz;

	if ((nx>=0) && (nz>=0) && (nx<maxszer) && (nz<maxdlug))
	{

      float ny1, ny2, nyx, nyz;

      ny1=teren[(int) floor(nx)  ][(int) nz].y;
      ny2=teren[(int) floor(nx)+1][(int) nz].y;

      nyx = (float)  rx*(ny2-ny1)+ny1;

      ny1=(float)teren[(int) nx][(int) floor(nz)  ].y;
      ny2=(float)teren[(int) nx][(int) floor(nz)-1].y;

      nyz = (float)  rz*(ny2-ny1)+ny1;

      float nyy = (nyx+nyz)/2.0;

		return nyy;

	} else
		return 0;
}

// ---------------------------------------------------------------------------
float gdzie_y_zwoda(float x, float z)
{
	float nx, nz;

	nx =  (x+dx0)/dkrok;
	nz =  (-z + dz0) /dkrok;

   x=x/dkrok;
   z=z/dkrok;

   float rx = fmod( fabs(x),(int) floor(fabs(x)) );
   float rz = fmod( fabs(z),(int) floor(fabs(z)) );

   if (x<0) rx=1-rx;
   if (z<0) rz=1-rz;

	if ((nx>=0) && (nz>=0) && (nx<maxszer) && (nz<maxdlug))
	{

      float ny1, ny2, nyx, nyz;

      ny1=teren[(int) floor(nx)  ][(int) nz].y;
      ny2=teren[(int) floor(nx)+1][(int) nz].y;

      nyx = (float)  rx*(ny2-ny1)+ny1;

      ny1=(float)teren[(int) nx][(int) floor(nz)  ].y;
      ny2=(float)teren[(int) nx][(int) floor(nz)-1].y;

      nyz = (float)  rz*(ny2-ny1)+ny1;

      float nyy = (nyx+nyz)/2.0;

		if (nyy>0) return nyy;
			else return 0;

	} else
		return 0;
}

// ---------------------------------------------------------------------------
//jak gdzie_y, ale bez zwracania uwagi na czesci kratki
float gdzie_y_integer(float x, float z)
{
	int nx, nz;

	nx = (int)  (x+dx0)/dkrok;
	nz = (int)  (-z + dz0) /dkrok;

	if ((nx>=0) && (nz>=0) && (nx<maxszer) && (nz<maxdlug))
	{
		return teren[nx][nz].y;
	} else
		return 0;

}


// ---------------------------------------------------------------------------
void gdzie_xz(float *x, float *z)
{
	int nx, nz;

	nx = (int) floor( (*x+dx0   ) / dkrok );
	nz = (int) floor( (-*z + dz0) / dkrok );
	*x = nx;
	*z = nz;
}

// --------------pomocnicze---------------------------------------------------
void klocek(GLfloat dl, GLfloat sz, GLfloat gr)
{
	glBegin(GL_QUADS);
		//spod
		glNormal3f (0.0, -1.0, 0.0);
		glVertex3f ( sz, 0.0, gr);
		glVertex3f (-sz, 0.0, gr);
		glVertex3f (-sz, 0.0,-gr);
		glVertex3f ( sz, 0.0,-gr);

		//gora
		glNormal3f (0.0, 1.0, 0.0);
		glVertex3f ( sz, dl,-gr);
		glVertex3f (-sz, dl,-gr);
		glVertex3f (-sz, dl, gr);
		glVertex3f ( sz, dl, gr);

		//bok lewy
		glNormal3f (-1.0, 0.0, 0.0);
		glVertex3f (-sz, 0.0,-gr);
		glVertex3f (-sz, 0.0, gr);
		glVertex3f (-sz,  dl, gr);
		glVertex3f (-sz,  dl,-gr);

		//bok prawy
		glNormal3f (1.0, 0.0, 0.0);
		glVertex3f ( sz,  dl,-gr);
		glVertex3f ( sz,  dl, gr);
		glVertex3f ( sz, 0.0, gr);
		glVertex3f ( sz, 0.0,-gr);

		//bok tylni
		glNormal3f (0.0, 0.0,-1.0);
		glVertex3f (-sz, 0.0,-gr);
		glVertex3f (-sz,  dl,-gr);
		glVertex3f ( sz,  dl,-gr);
		glVertex3f ( sz, 0.0,-gr);

		//bok przedni
		glNormal3f (0.0, 0.0, 1.0);
		glVertex3f ( sz, 0.0, gr);
		glVertex3f ( sz,  dl, gr);
		glVertex3f (-sz,  dl, gr);
		glVertex3f (-sz, 0.0, gr);

	glEnd();
}

// ---------------------------------------------------------------------------
void texklocek(GLfloat dl, GLfloat sz, GLfloat gr, float texy=1.0, float texx=1.0, float texz=1.0)
{
	glBegin(GL_QUADS);
		//spod
		glNormal3f (0.0, -1.0, 0.0);
		glTexCoord2f(texx, 0);		glVertex3f ( sz, 0.0, gr);
		glTexCoord2f(0, 0);		glVertex3f (-sz, 0.0, gr);
		glTexCoord2f(0, texz);		glVertex3f (-sz, 0.0,-gr);
		glTexCoord2f(texx, texz);		glVertex3f ( sz, 0.0,-gr);

		//gora
		glNormal3f (0.0, 1.0, 0.0);
		glTexCoord2f(texx, texz);		glVertex3f ( sz, dl,-gr);
		glTexCoord2f(0, texz);		glVertex3f (-sz, dl,-gr);
		glTexCoord2f(0, 0);		glVertex3f (-sz, dl, gr);
		glTexCoord2f(texx, 0);		glVertex3f ( sz, dl, gr);

		//bok lewy
		glNormal3f (-1.0, 0.0, 0.0);
		glTexCoord2f(0, texz);		glVertex3f (-sz,   0,-gr);
		glTexCoord2f(0, 0);		glVertex3f (-sz,   0, gr);
		glTexCoord2f(texy, 0);		glVertex3f (-sz,  dl, gr);
		glTexCoord2f(texy, texz);		glVertex3f (-sz,  dl,-gr);

		//bok prawy
		glNormal3f ( 1.0, 0.0, 0.0);
		glTexCoord2f(texy, texz);		glVertex3f ( sz,  dl,-gr);
		glTexCoord2f(0, texz);		glVertex3f ( sz,  dl, gr);
		glTexCoord2f(0, 0);		glVertex3f ( sz,   0, gr);
		glTexCoord2f(texy, 0);		glVertex3f ( sz,   0,-gr);

		//bok tylni
		glNormal3f (0.0, 0.0,-1.0);
		glTexCoord2f(0, 0);		glVertex3f (-sz, 0.0,-gr);
		glTexCoord2f(0, texy);		glVertex3f (-sz,  dl,-gr);
		glTexCoord2f(texx, texy);		glVertex3f ( sz,  dl,-gr);
		glTexCoord2f(texx, 0);		glVertex3f ( sz, 0.0,-gr);

		//bok przedni
		glNormal3f (0.0, 0.0, 1.0);
		glTexCoord2f(texx, 0);		glVertex3f ( sz, 0.0, gr);
		glTexCoord2f(texx, texy);		glVertex3f ( sz,  dl, gr);
		glTexCoord2f(0, texy);		glVertex3f (-sz,  dl, gr);
		glTexCoord2f(0, 0);		glVertex3f (-sz, 0.0, gr);

	glEnd();
}

// ---------------------------------------------------------------------------
// cos jak "texklocek()" ale robi sciete rogi, wykorzystywane do skrzydel
void texplat(GLfloat dl, GLfloat sz, GLfloat gr, GLfloat oilezmniejsz=0.0,
              float texxod=0.0, float texxdo=1.0,
              float texyod=0.0, float texydo=1.0,
              bool texscianagd=true,
              bool texscianalp=true,
              bool texscianapt=true)
{
   float texile = oilezmniejsz/(sz*2.0);
	glBegin(GL_QUADS);
		//spod
		glNormal3f (0.0, -1.0, 0.0);
		if (texscianagd) glTexCoord2f(texxdo, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz, 0.0, gr);
		if (texscianagd) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz, 0.0, gr);
		if (texscianagd) glTexCoord2f(texxod+texile, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz, 0.0,-gr);
		if (texscianagd) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz, 0.0,-gr);

		//gora
		glNormal3f (0.0, 1.0, 0.0);
		if (texscianagd) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz, dl,-gr);
		if (texscianagd) glTexCoord2f(texxod+texile, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz, dl,-gr);
		if (texscianagd) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz, dl, gr);
		if (texscianagd) glTexCoord2f(texxdo, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz, dl, gr);

		//bok lewy
		glNormal3f (-1.0, 0.0, 0.0);
		if (texscianalp) glTexCoord2f(texxod+texile, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz,   0,-gr);
		if (texscianalp) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz,   0, gr);
		if (texscianalp) glTexCoord2f(texxdo, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz,  dl, gr);
		if (texscianalp) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz,  dl,-gr);

		//bok prawy
		glNormal3f ( 1.0, 0.0, 0.0);
		if (texscianalp) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz,  dl,-gr);
		if (texscianalp) glTexCoord2f(texxod, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz,  dl, gr);
		if (texscianalp) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz,   0, gr);
		if (texscianalp) glTexCoord2f(texxdo-texile, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz,   0,-gr);

		//bok tylni
		glNormal3f (0.0, 0.0,-1.0);
		if (texscianapt) glTexCoord2f(texxod+texile, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz, 0.0,-gr);
		if (texscianapt) glTexCoord2f(texxod+texile, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz,  dl,-gr);
		if (texscianapt) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz,  dl,-gr);
		if (texscianapt) glTexCoord2f(texxdo-texile, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz, 0.0,-gr);

		//bok przedni
		glNormal3f (0.0, 0.0, 1.0);
		if (texscianapt) glTexCoord2f(texxdo, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz, 0.0, gr);
		if (texscianapt) glTexCoord2f(texxdo, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz,  dl, gr);
		if (texscianapt) glTexCoord2f(texxod, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz,  dl, gr);
		if (texscianapt) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz, 0.0, gr);

	glEnd();
}

// ---------------------------------------------------------------------------
// jak texplat, ale w inna strone scina (nie na szerokosc, tylko na dlugosc)
void texplatd(GLfloat dl, GLfloat sz, GLfloat gr, GLfloat oilezmniejsz=0.0,
              float texxod=0.0, float texxdo=1.0,
              float texyod=0.0, float texydo=1.0,
              bool texscianagd=true,
              bool texscianalp=true,
              bool texscianapt=true
              )
{
   GLfloat texile = 0;//oilezmniejsz/(sz/2.0);
	glBegin(GL_QUADS);
		//spod
		glNormal3f (0.0, -1.0, 0.0);
		if (texscianagd) glTexCoord2f(texxdo, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz, 0.0, gr);
		if (texscianagd) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz, 0.0, gr);
		if (texscianagd) glTexCoord2f(texxod, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz, 0.0,-gr);
		if (texscianagd) glTexCoord2f(texxdo, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz, 0.0,-gr);

		//gora
		glNormal3f (0.0, 1.0, 0.0);
		if (texscianagd) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz, dl,-gr);
		if (texscianagd) glTexCoord2f(texxod+texile, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz, dl,-gr);
		if (texscianagd) glTexCoord2f(texxod+texile, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz, dl, gr);
		if (texscianagd) glTexCoord2f(texxdo-texile, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz, dl, gr);

		//bok lewy
		glNormal3f (-1.0, 0.0, 0.0);
		if (texscianalp) glTexCoord2f(texxod, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz,   0,-gr);
		if (texscianalp) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz,   0, gr);
		if (texscianalp) glTexCoord2f(texxdo-texile, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz,  dl, gr);
		if (texscianalp) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz,  dl,-gr);

		//bok prawy
		glNormal3f ( 1.0, 0.0, 0.0);
		if (texscianalp) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz,  dl,-gr);
		if (texscianalp) glTexCoord2f(texxod+texile, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz,  dl, gr);
		if (texscianalp) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz,   0, gr);
		if (texscianalp) glTexCoord2f(texxdo, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz,   0,-gr);

		//bok tylni
		glNormal3f (0.0, 0.0,-1.0);
		if (texscianapt) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz, 0.0,-gr);
		if (texscianapt) glTexCoord2f(texxod+texile, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz,  dl,-gr);
		if (texscianapt) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz,  dl,-gr);
		if (texscianapt) glTexCoord2f(texxdo, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz, 0.0,-gr);

		//bok przedni
		glNormal3f (0.0, 0.0, 1.0);
		if (texscianapt) glTexCoord2f(texxdo, texyod); else glTexCoord2f(0,0);    glVertex3f ( sz, 0.0, gr);
		if (texscianapt) glTexCoord2f(texxdo-texile, texydo); else glTexCoord2f(0,0);    glVertex3f ( sz-oilezmniejsz,  dl, gr);
		if (texscianapt) glTexCoord2f(texxod+texile, texydo); else glTexCoord2f(0,0);    glVertex3f (-sz+oilezmniejsz,  dl, gr);
		if (texscianapt) glTexCoord2f(texxod, texyod); else glTexCoord2f(0,0);    glVertex3f (-sz, 0.0, gr);

	glEnd();
}

/*void texplatd(GLfloat dl, GLfloat sz, GLfloat gr, GLfloat oilezmniejsz=0.0, float texy=1.0, float texx=1.0, float texz=1.0)
{
	glBegin(GL_QUADS);
		//spod
		glNormal3f (0.0, -1.0, 0.0);
		glTexCoord2f(texx, 0);		glVertex3f ( sz, 0.0, gr);
		glTexCoord2f(0, 0);		glVertex3f (-sz, 0.0, gr);
		glTexCoord2f(0, texz);		glVertex3f (-sz, 0.0,-gr);
		glTexCoord2f(texx, texz);		glVertex3f ( sz, 0.0,-gr);

		//gora
		glNormal3f (0.0, 1.0, 0.0);
		glTexCoord2f(texx, texz);		glVertex3f ( sz, dl,-gr+oilezmniejsz);
		glTexCoord2f(0, texz);		glVertex3f (-sz, dl,-gr+oilezmniejsz);
		glTexCoord2f(0, 0);		glVertex3f (-sz, dl, gr-oilezmniejsz);
		glTexCoord2f(texx, 0);		glVertex3f ( sz, dl, gr-oilezmniejsz);

		//bok lewy
		glNormal3f (-1.0, 0.0, 0.0);
		glTexCoord2f(0, texz);		glVertex3f (-sz,   0,-gr);
		glTexCoord2f(0, 0);		glVertex3f (-sz,   0, gr);
		glTexCoord2f(texy, 0);		glVertex3f (-sz,  dl, gr-oilezmniejsz);
		glTexCoord2f(texy, texz);		glVertex3f (-sz,  dl,-gr+oilezmniejsz);

		//bok prawy
		glNormal3f ( 1.0, 0.0, 0.0);
		glTexCoord2f(texy, texz);		glVertex3f ( sz,  dl,-gr+oilezmniejsz);
		glTexCoord2f(0, texz);		glVertex3f ( sz,  dl, gr-oilezmniejsz);
		glTexCoord2f(0, 0);		glVertex3f ( sz,   0, gr);
		glTexCoord2f(texy, 0);		glVertex3f ( sz,   0,-gr);

		//bok tylni
		glNormal3f (0.0, 0.0,-1.0);
		glTexCoord2f(0, 0);		glVertex3f (-sz, 0.0,-gr);
		glTexCoord2f(0, texy);		glVertex3f (-sz,  dl,-gr+oilezmniejsz);
		glTexCoord2f(texx, texy);		glVertex3f ( sz,  dl,-gr+oilezmniejsz);
		glTexCoord2f(texx, 0);		glVertex3f ( sz, 0.0,-gr);

		//bok przedni
		glNormal3f (0.0, 0.0, 1.0);
		glTexCoord2f(texx, 0);		glVertex3f ( sz, 0.0, gr);
		glTexCoord2f(texx, texy);		glVertex3f ( sz,  dl, gr-oilezmniejsz);
		glTexCoord2f(0, texy);		glVertex3f (-sz,  dl, gr-oilezmniejsz);
		glTexCoord2f(0, 0);		glVertex3f (-sz, 0.0, gr);

	glEnd();
}
*/
// ---------------------------------------------------------------------------
AnsiString l2t(int liczba, int ilosc_lit)
{
   AnsiString ww;
   ww = IntToStr(liczba);
   if (ilosc_lit>0)
      while (ww.Length()<ilosc_lit)
            ww.Insert('0',1);
   return ww;
}


