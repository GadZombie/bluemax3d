//---------------------------------------------------------------------------
#ifndef drawH
#define drawH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ActnList.hpp>
#include <Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class TBMForm : public TForm
{
__published:	// IDE-managed Components
   TTimer *TimerRys;
   TPanel *PanelDolny;
   TLabel *LPunkty;
   TImageList *obruszkodzenia;
   TPaintBox *LUszkodzenia;
   TLabel *Lpaliwo;
   TLabel *Lbomb;
   TLabel *Lspd;
   TLabel *Lalt;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TPaintBox *Lwiatr;
   TLabel *Label6;
   TLabel *Label7;
        TTimer *FPSTimer;
        TLabel *FPSLabel;
   TTimer *TimerDzialaj;
   TLabel *Llotnisko;
   TLabel *LPauza;
   TPaintBox *PaintBox1;
   TPanel *PanelOpcje;
   TPanel *Panel1;
   TPanel *PanelHighscores;
   TPanel *Panel3;
   TPaintBox *ListaRekordow;
   TPanel *PanelNewHigh;
   TPanel *Panel4;
   TLabel *YourScore;
   TLabel *Label9;
   TEdit *YourName;
   TLabel *YourRank;
   TLabel *LDifficulty;
   TLabel *LControl;
   TLabel *LGravity;
   TLabel *LDetails;
   TLabel *LabPoz;
   TPanel *PanelWinieta;
   TImage *Image1;
   TLabel *LVolume;
   TPaintBox *Lsamolot;
	void __fastcall TimerRysTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall LUszkodzeniaPaint(TObject *Sender);
   void __fastcall LwiatrPaint(TObject *Sender);
        void __fastcall FPSTimerTimer(TObject *Sender);
   void __fastcall TimerDzialajTimer(TObject *Sender);
   void __fastcall FormDeactivate(TObject *Sender);
   void __fastcall FormKeyPress(TObject *Sender, char &Key);
   void __fastcall PaintBox1Paint(TObject *Sender);
   void __fastcall ListaRekordowPaint(TObject *Sender);
   void __fastcall YourNameKeyPress(TObject *Sender, char &Key);
   void __fastcall ActionOKNewHiscoreExecute(TObject *Sender);
   void __fastcall ActionOKHighscoresExecute(TObject *Sender);
   void __fastcall ActionOKOpcjeExecute(TObject *Sender);

   void __fastcall odswiezOpcje();

   void __fastcall pokazWiniete();
   void __fastcall schowajOpcje();
   void __fastcall schowajNewHigh();
   void __fastcall schowajHighScores();
   void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
   void __fastcall LsamolotPaint(TObject *Sender);

private:	// User declarations
	void DrawScene();
    GLvoid initializeGL(GLsizei width, GLsizei height);
    GLvoid resize( GLsizei width, GLsizei height );
    GLfloat latitude, longitude, latinc, longinc;
    GLdouble radius;
    HGLRC ghRC;
    HDC   ghDC;

public:		// User declarations
	__fastcall TBMForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TBMForm *BMForm;
//---------------------------------------------------------------------------
#endif
