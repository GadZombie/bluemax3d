
#include <vcl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop

#include "fmod.h"
#include "fmod_errors.h"

#include "draw.h"

// moje inkludy:
#include "bmdef.h"
#include "dzwieki.h"

#include "bmtex.h"
#include "bmpomoc.h"
#include "bmobiekty3d.h"
#include "bminit.h"
#include "bmrys.h"
#include "bmruch.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TBMForm *BMForm;
//---------------------------------------------------------------------------
__fastcall TBMForm::TBMForm(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------------------------
void odswiez_dol()
{
    if (ekran.fuel!=gracz.fuel)
    {
       if (gracz.fuel<=50) BMForm->Lpaliwo->Font->Color=0x002020c0;
                      else BMForm->Lpaliwo->Font->Color=0x00ffffff;
       BMForm->Lpaliwo->Caption=l2t(gracz.fuel,3);
       ekran.fuel=gracz.fuel;
    }
    if (ekran.bomb!=gracz.bomb)
    {
       BMForm->Lbomb->Caption=l2t(gracz.bomb,3);
       ekran.bomb=gracz.bomb;
    }
    if (ekran.score!=gracz.score)
    {
       BMForm->LPunkty->Caption=l2t(gracz.score,5);
       ekran.score=gracz.score;
    }

    int ws;
    if (samolot[sterowanie].ileuszkodzen<=3)
       ws=floor(szybkosc*660.0);
       //ws=floor(szybkosc*1000.0 - samolot[sterowanie].dz*130.0);
    else ws=0;
    if (ekran.spd!=ws)
    {
       if (ws<=100) BMForm->Lspd->Font->Color=0x002020c0;
           else BMForm->Lspd->Font->Color=0x00ffffff;
       BMForm->Lspd->Caption=l2t(ws,3);
       ekran.spd=ws;
    }

    if (ekran.alt!=gracz.alt)
    {
       int p=floor(gracz.alt*10.0);
       if (p<0) p=0;
       BMForm->Lalt->Caption=l2t(p,3);
       ekran.alt=samolot[sterowanie].y;
    }

    if (ekran.odswiezuszkodzenia!=0)
    {
       BMForm->LUszkodzenia->Repaint();
       ekran.odswiezuszkodzenia=0;
    }
    if (ekran.odswiezwiatr!=0)
    {
       BMForm->Lwiatr->Repaint();
       ekran.odswiezwiatr=0;
    }

/*    float ax,az;
    ax=samolot[sterowanie].x;
    az=samolot[sterowanie].z;
    gdzie_xz(&ax,&az);
    BMForm->Label6->Caption="x="+FloatToStr(ax);
    BMForm->Label7->Caption="z="+FloatToStr(az);*/
//    BMForm->Label6->Caption=FloatToStr(zod);

//    BMForm->Label7->Caption=FloatToStr(dz0/dkrok);
//    BMForm->Label6->Caption=FloatToStr();

    if ((samolot[sterowanie].jest==1) &&        //czerwony
        (!gracz.na_poziomie_samolotu) &&
        (szybkosc>=maxszyb) &&
        (gracz.alt>=2.6) &&
        (gracz.alt<=7.0))
        BMForm->PanelDolny->Color=0x00000050;
    else
    if ((samolot[sterowanie].jest==1) &&        //migajacy
        (szybkosc>=maxszyb) &&
        (gracz.alt<2.6) &&
        (!gracz.moze_ladowac)) {
        if (oo % 10<=4)
           BMForm->PanelDolny->Color=0x00404070;
        else
           BMForm->PanelDolny->Color=0x008080F0;
    }
    else {
        if (gracz.na_poziomie_samolotu)         //niebieski
           BMForm->PanelDolny->Color=0x00e07030;
        else BMForm->PanelDolny->Color=clBlack; //czarny
    }

/*    if (gracz.nad_lotniskiem) BMForm->Label6->Caption="Nad lotniskiem";
                        else  BMForm->Label6->Caption="";*/

     BMForm->Label6->Caption="sum:"+IntToStr(gracz.ile_celow_glownych);
     BMForm->Label7->Caption="ter:"+IntToStr(gracz.ile_celow_glownych_teraz);

    if (!gracz.jest_lotnisko)
       BMForm->Llotnisko->Caption="";
    else
    if (gracz.moze_ladowac) {
       BMForm->Llotnisko->Caption="L";
       BMForm->Llotnisko->Font->Color=0x00FADCC0;
    } else {
       BMForm->Llotnisko->Caption="R";
       BMForm->Llotnisko->Font->Color=0x00109613;
    }

    if (ekran.ostrzezenieosamolocie>0 || ekran.odswiezostrzezenieosamolocie) {
       BMForm->Lsamolot->Repaint();
       ekran.odswiezostrzezenieosamolocie=0;
    }

}
//---------------------------------------------------------------------------
void __fastcall TBMForm::TimerRysTimer(TObject *Sender)
{
//	Timer1->Enabled = false;
    ((TTimer *)Sender)->Tag++;

    if (!gracz.winieta) DrawScene();
       else PanelWinieta->Show();
    odswiez_dol();

    if (ustawienia.pauza) {
       TimerRys->Enabled=false;
       PaintBox1->Repaint();
       for (int a=0; a<ilekanalow; a++)
           if (FSOUND_IsPlaying(kanaly[a]) && !FSOUND_GetPaused(kanaly[a]))
              FSOUND_SetPaused(kanaly[a], true);
    }

    //Yield();
//    Timer1->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TBMForm::TimerDzialajTimer(TObject *Sender)
{
//	Timer1->Enabled = false;
   if (!gracz.winieta) ruch();

    if (ustawienia.pauza) {
       TimerDzialaj->Enabled=false;
       LPauza->Visible=true;
    }
    //Yield();
//    Timer1->Enabled = true;
}

BOOL bSetupPixelFormat(HDC hdc)
{

    PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,
    };
//    PixelFormat = ChoosePixelFormat(hdc, &pfd);
//    SetPixelFormat(hdc, PixelFormat, &pfd);


    PIXELFORMATDESCRIPTOR *ppfd;
    int pixelformat;
    ppfd = &pfd;

/*    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                        PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_COLORINDEX;
    ppfd->cColorBits = 8;
    ppfd->cDepthBits = 16;

    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;
  */
    if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 )
    {
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE)
    {
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    return TRUE;

}

//---------------------------------------------------------------------------
void	TBMForm::DrawScene()
{
  rysuj_calosc();
  
  SwapBuffers(BMForm->ghDC);
}

//---------------------------------------------------------------------------
GLvoid TBMForm::resize( GLsizei width, GLsizei height )
{
	glViewport(0, PanelDolny->Height, (GLsizei) width, (GLsizei) height-PanelDolny->Height);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
   odswiezwidok();
	//gluPerspective(50.0, (GLfloat) width/ (GLfloat) height, 0.2/*nie dawac mniej,bo sie zbuffer jebie*/, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//---------------------------------------------------------------------------
GLvoid TBMForm::initializeGL(GLsizei width, GLsizei height)
{
init();
//   noweruchome(5,zdo+30,3);
//   noweruchome(3,zdo,4);
//   noweruchome(1,zdo,5);

}

//---------------------------------------------------------------------------
void __fastcall TBMForm::FormResize(TObject *Sender)
{
	resize(ClientRect.Right, ClientRect.Bottom);
   odswiez_dol();

   float rozm = (ClientRect.Right/640.0);


}
//---------------------------------------------------------------------------
void __fastcall TBMForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
   if (!PanelOpcje->Visible) { //gra
       if (gracz.koniecgry>50) gracz.koniecgry=1000;
       switch (Key)
       {
          case 'a':
          case 'A':
             kln['A']=1;
          break;

          case 'z':
          case 'Z':
             kln['Z']=1;
          break;

          case 'b':
          case 'B':
    //			kln['B']=1;
          break;

          case 107:
             kl['+']=1;
          break;
          case 109:
             kl['-']=1;
          break;

          case VK_LEFT:
          case VK_UP:
          case VK_RIGHT:
          case VK_DOWN:
             kl[Key]=1;
          break;

          default: kln[Key]=1; kl[Key]=1; break;
       }

       if (Shift.Contains(ssCtrl)) {
          kl['B']=1;
       }
       if (Shift.Contains(ssShift)) {
          kl[' ']=1;
       }
   } else { //opcje
       switch (Key)
       {
          case VK_UP:
             ustawienia.pozycja_kursora--;
             if (ustawienia.pozycja_kursora<0) ustawienia.pozycja_kursora=4;
             odswiezOpcje();
          break;
          case VK_DOWN:
             ustawienia.pozycja_kursora++;
             if (ustawienia.pozycja_kursora>4) ustawienia.pozycja_kursora=0;
             odswiezOpcje();
          break;

          case VK_LEFT:
             switch (ustawienia.pozycja_kursora)
             {
                case 0: //diff
                   ustawienia.poziomtrudnosci--;
                   if (ustawienia.poziomtrudnosci<0) ustawienia.poziomtrudnosci=2;
                break;
                case 1: //contr
                   ustawienia.typsterowania++;
                   if (ustawienia.typsterowania>1) ustawienia.typsterowania=0;
                break;
                case 2: //grav
                   ustawienia.grawitacja = !ustawienia.grawitacja;
                break;
                case 3: //det
                   ustawienia.detale--;
                   if (ustawienia.detale<0) ustawienia.detale=2;
                break;
                case 4: //volume
                   ustawienia.glosnosc--;
                   if (ustawienia.glosnosc<0) ustawienia.glosnosc=0;
                break;
             }
             odswiezOpcje();
          break;
          case VK_RIGHT:
          case VK_SPACE:
             switch (ustawienia.pozycja_kursora)
             {
                case 0: //diff
                   ustawienia.poziomtrudnosci++;
                   if (ustawienia.poziomtrudnosci>2) ustawienia.poziomtrudnosci=0;
                break;
                case 1: //contr
                   ustawienia.typsterowania++;
                   if (ustawienia.typsterowania>1) ustawienia.typsterowania=0;
                break;
                case 2: //grav
                   ustawienia.grawitacja = !ustawienia.grawitacja;
                break;
                case 3: //det
                   ustawienia.detale++;
                   if (ustawienia.detale>2) ustawienia.detale=0;
                break;
                case 4: //volume
                   ustawienia.glosnosc++;
                   if (ustawienia.glosnosc>10) ustawienia.glosnosc=10;
                break;
             }
             odswiezOpcje();
          break;


          default:
          break;
       }
   }
}
//---------------------------------------------------------------------------
void __fastcall TBMForm::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
   switch (Key)
   {
      case VK_F1: //nowa gra
         if (!PanelNewHigh->Visible) {
            if (PanelHighscores->Visible) schowajHighScores();
            if (PanelOpcje->Visible) schowajOpcje();
            gracz.winieta=false;
            nowagra();
            return;
         }
      break;

      case VK_F2: //opcje
         if (!PanelNewHigh->Visible) {
            if (PanelHighscores->Visible) schowajHighScores();
            if (PanelOpcje->Visible) schowajOpcje();
            ustawienia.pauza=true;
            ustawienia.pozycja_kursora=0;
            odswiezOpcje();
            PanelWinieta->Hide();
            PanelDolny->Hide();
            PanelOpcje->Show();
            gracz.jest_gra = false;
            return;
         }
      break;

      case VK_F3: //highscores
         if (!PanelNewHigh->Visible) {
            if (PanelHighscores->Visible) schowajHighScores();
            if (PanelOpcje->Visible) schowajOpcje();
             PanelWinieta->Hide();
             ustawienia.pauza=true;
             PanelDolny->Hide();
             PanelHighscores->Show();
            return;
         }
      break;

      case VK_F5: //niebo
         ustawienia.jestniebo = !ustawienia.jestniebo;

      break;
      case VK_F6: //wskazniki
         ustawienia.wskazniki = !ustawienia.wskazniki;
      break;

   }


   if (!PanelOpcje->Visible) { //gra
       switch (Key)
       {
          case 'a':
          case 'A':
             kln['A']=0;
          break;

          case 'z':
          case 'Z':
             kln['Z']=0;
          break;

          case 107:
             kl['+']=0;
          break;
          case 109:
             kl['-']=0;
          break;

          case VK_LEFT:
          case VK_UP:
          case VK_RIGHT:
          case VK_DOWN:
             kl[Key]=0;
          break;


          default: kln[Key]=0; kl[Key]=0; break;
              }
       if (!Shift.Contains(ssCtrl)) {
          kl['B']=0;
       }
       if (!Shift.Contains(ssShift)) {
          kl[' ']=0;
       }
   } else { //opcje

   }
}
//---------------------------------------------------------------------------
void __fastcall TBMForm::LUszkodzeniaPaint(TObject *Sender)
{
  for (int a=0; a<=3; a++)
  {
     if (samolot[sterowanie].uszkodzenia[a]==1)
        obruszkodzenia->Draw( LUszkodzenia->Canvas, a*20, 0, a );
  }
}
//---------------------------------------------------------------------------

void __fastcall TBMForm::LwiatrPaint(TObject *Sender)
{
   if (ustawienia.jestwiatr==1)
      obruszkodzenia->Draw( Lwiatr->Canvas, 0, 0, 4 );
}
//---------------------------------------------------------------------------

void __fastcall TBMForm::FPSTimerTimer(TObject *Sender)
{
  FPSLabel->Caption=IntToStr(TimerRys->Tag)+" FPS";
  TimerRys->Tag=0;
}
//---------------------------------------------------------------------------

void __fastcall TBMForm::FormDeactivate(TObject *Sender)
{
 ustawienia.pauza=true;
}
//---------------------------------------------------------------------------

void __fastcall TBMForm::FormKeyPress(TObject *Sender, char &Key)
{
	switch (Key)
	{
		case '1':
			kamera=0;
         odswiezwidok();
		break;
		case '2':
			kamera=1;
         odswiezwidok();
		break;
		case '3':
			kamera=2;
         odswiezwidok();
		break;
		case '4':
			kamera=3;
         odswiezwidok();
		break;
		case '5':
			kamera=4;
         odswiezwidok();
		break;
		case '6':
			kamera=6;
         odswiezwidok();
		break;
		case '7':
			kamera=7;
         odswiezwidok();
		break;
		case '8': //kamera ortho
			kamera=8;
         odswiezwidok();
		break;

		case 'q':
		case 'Q':
			ustawienia.rodzajwody++;
			if (ustawienia.rodzajwody>=2)
				ustawienia.rodzajwody=0;
		break;
		case 'p':
		case 'P':
         if (!PanelHighscores->Visible && !PanelOpcje->Visible) {
             ustawienia.pauza = !ustawienia.pauza;
             if (!ustawienia.pauza) {
                TimerDzialaj->Enabled=true;
                TimerRys->Enabled=true;
                LPauza->Visible=false;
             }
         }
		break;

      case 13:
          if (PanelNewHigh->Visible) schowajNewHigh();
          if (PanelHighscores->Visible) schowajHighScores();
          if (PanelOpcje->Visible) schowajOpcje();
      break;

		case 27:
         BMForm->Close();
		break;

		default:
      break;
   }


}
//---------------------------------------------------------------------------

void __fastcall TBMForm::PaintBox1Paint(TObject *Sender)
{
int r=1;
TRect tr;
for (int y=0; y<=maxdlug-1; y++)
  for (int x=0; x<=maxszer-1; x++) {
      if (teren[x][y].obiekt==ob_lotnisko ||
          (x>0 && teren[x-1][y].obiekt==ob_lotnisko) ||
          (x>1 && teren[x-2][y].obiekt==ob_lotnisko) ||
          (x<maxszer-1 && teren[x+1][y].obiekt==ob_lotnisko) ||
          (x<maxszer-2 && teren[x+2][y].obiekt==ob_lotnisko)
         )
         PaintBox1->Canvas->Brush->Color = clGray;
      else
      if (teren[x][y].y>0) {
         unsigned int kr,kg,kb;
         kr=(int)(teren[x][y].kr*256.0);
         kg=(int)(teren[x][y].kg*256.0);
         kb=(int)(teren[x][y].kb*256.0);
         PaintBox1->Canvas->Brush->Color =
                       kr | (kg << 8) | (kb << 16);
      } else
      if (teren[x][y].y<=0)
         PaintBox1->Canvas->Brush->Color = clBlue;

      tr.Left  =(int)(x*r)            ;
      tr.Right =(int)(x*r+r)          ;

      tr.Top   =(int)((maxdlug-y)*r)  ;
      tr.Bottom=(int)((maxdlug-y)*r+r);

      PaintBox1->Canvas->FillRect(tr);
  }

}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
void __fastcall TBMForm::ListaRekordowPaint(TObject *Sender)
{
  for (int a=0; a<ilemiejsc; a++)
  {
    AnsiString s;
    s.sprintf("%07d",rekordy[a].pkt);
    ((TPaintBox *)Sender)->Canvas->Font->Height=-10;
    ((TPaintBox *)Sender)->Canvas->TextOutA(5,a*30, IntToStr(a+1));

    ((TPaintBox *)Sender)->Canvas->TextOutA(30,a*30+14, ranki[rekordy[a].rank]);

    ((TPaintBox *)Sender)->Canvas->Font->Height=-13;
    ((TPaintBox *)Sender)->Canvas->TextOutA(((TPaintBox *)Sender)->Width - ((TPaintBox *)Sender)->Canvas->TextWidth(s)-5,a*30, s);
    ((TPaintBox *)Sender)->Canvas->TextOutA(30,a*30, rekordy[a].imie);

  }

}
//---------------------------------------------------------------------------

void __fastcall TBMForm::odswiezOpcje()
{
   String diff[]= { "NOVICE", "INTERMEDIATE", "ADVANCED" };
   String contr[]={ "NORMAL CONTROL", "REVERSE CONTROL" };
   String grav[]= { "GRAVITY", "NO GRAVITY" };
   String det[]=  { "LOW DETAILS", "MEDIUM DETAILS", "HIGH DETAILS" };

   LabPoz->Top=128+ustawienia.pozycja_kursora*32;

   LDifficulty->Caption=diff[ustawienia.poziomtrudnosci];
   LControl->Caption=contr[ustawienia.typsterowania];
   LGravity->Caption=grav[ustawienia.grawitacja];
   LDetails->Caption=det[ustawienia.detale];

   String s;
   for (int a=1; a<=ustawienia.glosnosc; a++)
       s = s+"#";
   for (int a=1+ustawienia.glosnosc; a<=10; a++)
       s = s+"..";
   LVolume->Caption="VOLUME "+s+" "+IntToStr(ustawienia.glosnosc*10)+"%";

}



//---------------------------------------------------------------------------
void __fastcall TBMForm::YourNameKeyPress(TObject *Sender, char &Key)
{
if (Key==13) schowajNewHigh();
}
//---------------------------------------------------------------------------

void __fastcall TBMForm::pokazWiniete()
{
   PanelDolny->Hide();
   PanelWinieta->Show();
   PanelWinieta->DoubleBuffered=true;
   gracz.winieta=true;
   if (FSOUND_GetPaused(muzyka_chan)) {
      FSOUND_SetPaused(muzyka_chan, FALSE);
      FSOUND_Stream_SetTime(muzyka, 0);
   }
}

//---------------------------------------------------------------------------
void __fastcall TBMForm::schowajOpcje()
{
   ustaw_klawisze_sterowania();

   PanelOpcje->Hide();
   if (gracz.jest_gra) {
      gracz.winieta=false;
      nowagra();
   } else
     pokazWiniete();
     //PanelWinieta->Show();
}

//---------------------------------------------------------------------------
void __fastcall TBMForm::schowajNewHigh()
{
   rekordy[ilemiejsc-1].imie=YourName->Text;
   rekordy[ilemiejsc-1].pkt=gracz.score;
   rekordy[ilemiejsc-1].rank=gracz.rank;

   sortujrekordy();

   PanelNewHigh->Hide();
   PanelHighscores->Show();
}

//---------------------------------------------------------------------------
void __fastcall TBMForm::schowajHighScores()
{
   PanelHighscores->Hide();
   if (!gracz.jest_gra) {
      //gracz.winieta=true;
      //nowagra();
      pokazWiniete();
     } else {
       TimerDzialaj->Enabled=true;
       TimerRys->Enabled=true;
       LPauza->Visible=false;
       ustawienia.pauza=false;
       PanelDolny->Show();
     }
}

//---------------------------------------------------------------------------
void __fastcall TBMForm::ActionOKNewHiscoreExecute(TObject *Sender)
{
   schowajNewHigh();
}
//---------------------------------------------------------------------------

void __fastcall TBMForm::ActionOKHighscoresExecute(TObject *Sender)
{
   schowajHighScores();
}
//---------------------------------------------------------------------------

void __fastcall TBMForm::ActionOKOpcjeExecute(TObject *Sender)
{
  schowajOpcje();
}
//---------------------------------------------------------------------------


void __fastcall TBMForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   if (MessageBoxA(BMForm->Handle, "Do you want to quit?", "Quit", MB_YESNO | MB_TASKMODAL | MB_ICONQUESTION) == IDYES)
      CanClose = true;
    else
      CanClose = false;
}
//---------------------------------------------------------------------------

void __fastcall TBMForm::LsamolotPaint(TObject *Sender)
{
   if (ekran.ostrzezenieosamolocie%10<=5)
      obruszkodzenia->Draw( Lsamolot->Canvas, 0, 0, 5 );
//   else

}
//---------------------------------------------------------------------------

void __fastcall ZapiszHighScore()
{
  FILE* file;

  file = fopen("hiscore.hsc", "wb");
  if (file == NULL)
  {
    Application->MessageBox("can't open the file mydata.dat", "Error", MB_OK);
    exit(1);
  }

  for (int a=0; a<ilemiejsc; a++)
      {
         char buf[255];
         StrPCopy(buf, rekordy[a].imie);
         int d = rekordy[a].imie.Length();

         fwrite(&d, sizeof(d) , 1, file);
         fwrite(&buf, rekordy[a].imie.Length() , 1, file);
         fwrite(&rekordy[a].pkt, sizeof(rekordy[a].pkt) , 1, file);
         fwrite(&rekordy[a].rank, sizeof(rekordy[a].rank) , 1, file);
      }

  fclose(file);

}
//---------------------------------------------------------------------------
void __fastcall WczytajHighScore()
{
  FILE* file;

  file = fopen("hiscore.hsc", "rb");
  if (file != NULL)
  {

    for (int a=0; a<ilemiejsc; a++)
        {
           char buf[255];
           int d;

           fread(&d, sizeof(d), 1, file);
           fread(&buf, d , 1, file);
           buf[d]=0;
           StrECopy(rekordy[a].imie.c_str(), buf);

           fread(&rekordy[a].pkt, sizeof(rekordy[a].pkt), 1, file);
           fread(&rekordy[a].rank, sizeof(rekordy[a].rank), 1, file);

        }
  }
  fclose(file);

}
//---------------------------------------------------------------------------
void __fastcall TBMForm::FormClose(TObject *Sender, TCloseAction &Action)
{
   TimerRys->Enabled = false;
   TimerDzialaj->Enabled = false;
        if (ghRC)
            wglDeleteContext(ghRC);
        if	(ghDC)
        	ReleaseDC(Handle, ghDC);

	if (fullscreen)         // Are we in fullscreen mode?
	{
		ChangeDisplaySettings(NULL,0);  // If so switch back to the desktop
		ShowCursor(true);               // Show mouse pointer
	}

   ZapiszHighScore();

}
//---------------------------------------------------------------------------
void __fastcall TBMForm::FormCreate(TObject *Sender)
{
   int width=640, height=480, bits=32, freq=75;


   if (dzwieki_start()!=0) exit(1);


   if (ParamCount()>=1 && ParamStr(1)=='f') fullscreen=true;

	if (fullscreen)         // Attempt fullscreen mode?
	{
		DEVMODE dmScreenSettings;                                       // Device mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	        // Makes sure memory's cleared
		dmScreenSettings.dmSize         = sizeof(dmScreenSettings);     // Size of the devmode structure
		dmScreenSettings.dmPelsWidth	= width;                        // Selected screen width
		dmScreenSettings.dmPelsHeight	= height;                       // Selected screen height
		dmScreenSettings.dmBitsPerPel	= bits;	                        // Selected bits per pixel
      dmScreenSettings.dmDisplayFrequency = freq;
		dmScreenSettings.dmFields       = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY;

		// Try to set selected mode and get results. NOTE: CDS_FULLSCREEN gets rid of start bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If the mode fails, offer two options. Quit or use windowed mode.
			if (MessageBox(NULL,"The requested fullscreen mode is not supported by\nyour video card. Use windowed mode instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = false;       // Windowed mode selected. Fullscreen = false
			}
			else
			{
				// Pop up a message box letting user know the program is closing.
				MessageBox(NULL,"Program will now close.","ERROR",MB_OK|MB_ICONSTOP);
				//return false;           // Return false
			}
		}

      BMForm->FormStyle = fsStayOnTop;
      BMForm->BorderStyle = bsNone;
      BMForm->WindowState = wsMaximized;

      ShowCursor(false);
	}

/*	if (fullscreen)                         // Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;    // Window extended style
		dwStyle = WS_POPUP;		// Windows style
		ShowCursor(false);		// Hide mouse pointer
	}
  */

        ghDC = GetDC(Handle);
        if (!bSetupPixelFormat(ghDC))
            Close();
        ghRC = wglCreateContext(ghDC);
        wglMakeCurrent(ghDC, ghRC);
        initializeGL(ClientRect.Right, ClientRect.Bottom);
        resize(width,height);

//        WczytajHighScore();

        ekran.ostrzezenieosamolocie=6;

        Application->OnDeactivate = FormDeactivate;
}
//---------------------------------------------------------------------------


