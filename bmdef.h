#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define PI180 (M_PI/180.0)

#define ilemiejsc 10

#define iletekstur 34
#define szalikdlug 7

#define terensz 51
#define terendl 801

#define ile_wczesniej_informowac_o_lotnisku 40

const int ilewidac_od=-20, ilewidac_do=40;
const int ilewidac_suma=ilewidac_do-ilewidac_od;

bool fullscreen = false;

const sterowanie = 0;
const ils = 5;
const float samolot_nad_ziemia=0.6f;
const float maxszyb = 0.25;

//maxy
const maxdlug=780;//780; //dlugosc terenu
const maxszer=50; //szerokosc terenu

const maxpoc=198; //ilosc pociskow
const maxwyb=398; //ilosc wybuchow

const maxruchome=29; //ilosc obiektow ruchomych na raz

const maxsmiec=398; //ilosc smieci z wybuchow [deski, itp]

float dkrok=2.0f;
float dx0,dz0, zod,zdo;
float teren_wielkosctex=12.0;

float wodakrok=2.0f;
float wodax0,wodaz0;
float wodadx0,wodadz0;
float wodailex0,wodailez0;

int oo=0;
float ooszyb=0;

int kamera=3;
float kameraczas=0;
byte kl[256];
byte kln[256];

/*float pos0[4] = {20.0, 20.0, -130.0, 1.0}; //swiatlo slonca
float spotDir1[3] = {-0.15, -0.1, 1.0};
float ambientLight0[4] = {0.5f, 0.5f, 0.3f, 1.0f};
float diffuseLight0[4] = {0.5f, 0.5f, 0.3f, 1.0f};
float specularLight0[4] = {0.8f, 0.7f, 0.7f, 1.0f};
*/
/*float ambientLight1[4] = {0.1f, 0.1f, 0.1f, 1.0f};
float diffuseLight1[4] = {0.1f, 0.1f, 0.1f, 1.0f};
float specularLight1[4] = {0.1f, 0.1f, 0.1f, 1.0f};      */


//parametry materialu pociskow
float mat_poc_ka[] = {0.80, 0.80, 0.90, 0.3};
float mat_poc_kd[] = {0.80, 0.80, 0.90, 0.3};
float mat_poc_ks[] = {0.80, 0.80, 0.90, 0.3};

//parametry materialu bomb
float mat_bom_ka[] = {0.10, 0.10, 0.10, 1.0};
float mat_bom_kd[] = {0.10, 0.10, 0.10, 1.0};
float mat_bom_ks[] = {0.80, 0.80, 0.80, 1.0};

//parametry materialu dna
float mat_dno_ka[] = {0.30, 0.35, 0.30, 1.0};
float mat_dno_kd[] = {0.30, 0.35, 0.30, 1.0};
float mat_dno_ks[] = {0.30, 0.35, 0.30, 1.0};

//parametry materialu wody
float material_ka[] = {0.38, 0.33, 0.30, 0.8};
float material_kd[] = {0.30, 0.25, 0.30, 0.8};
float material_ks[] = {0.30, 0.30, 0.30, 1.0};

float mat_plusk_kd[] = {0.50, 0.50, 0.50, 1.0};

//parametry materialu samolotu gracza
GLfloat mat_sam_ka[] = {0.87890625, 0.87890625, 0.953125, 1.0};
GLfloat mat_sam_kd[] = {0.87890625, 0.87890625, 0.953125, 1.0};
GLfloat mat_sam_ks[] = {0.90, 0.90, 0.90, 1.0};

//parametry materialu samolotu przeciwnika
GLfloat mat_sam2_ka[] = {0.6640625, 0.46484375, 0.04296875, 1.0};
GLfloat mat_sam2_kd[] = {0.6640625, 0.46484375, 0.04296875, 1.0};
GLfloat mat_sam2_ks[] = {0.90, 0.90, 0.90, 1.0};

//parametry swiatla globalnego
float pos1[4] = {0.0,8.0,-20.0, 0.0};
float light_ka[] = {0.80, 0.80, 0.65, 1.0};
float light_kd[] = {0.95, 0.95, 0.90, 1.0};
float light_ks[] = {0.90, 0.94, 0.72, 1.0};

//parametry materialu wskaznika celu
float mat_wskcel_ka[] = {0.80, 0.30, 0.10, 1.0};
float mat_wskcel_kd[] = {0.80, 0.30, 0.10, 1.0};
float mat_wskcel_ks[] = {1.00, 0.80, 0.60, 1.0};

GLfloat fogColor[4];

//tekstury
//BITMAPINFO	*BitmapInfo[iletekstur-1] = { NULL };	/* Current bitmap information */
//void		*BitmapBits[iletekstur-1] = { NULL };	/* Current bitmap pixel bits */
static unsigned int texName[iletekstur-1];

float szybkosc  ; //szybkosc, z jaka przesuwa sie teren pod spodem
float szybkoscc ; //szybkosc, z jaka przesuwa sie teren pod spodem + szybkosc DZ samolotu gracza
float szybkoscg ; //szybkosc, jaka gracz sobie ustawil i szybkosc stara sie jej dorownac

float obiektyrozm[256];

struct
{
	float y;
	float norm[3]; //wektor normalny
   float jasnosc; //jasnosc wektorow terenu (przy dziurach)
   float kr,kg,kb; //kolor
   byte jestwoda;

	int   obiekt; //0=nic, 10=drzewo1, 100=budynek
	float obiektrozm; //wielkosc obiektu; 1=normalny
	int   obiektobr; //obrocenie wokol wlasnej osi obiektu
	float obiekty; //pozycja w pionie (zwykle rowno z terenem, ale barki sa na wodzie)
   byte  obiektktoreprzejscie;
   int   obiektpatrzyobr, obiektpatrzypion; //do czolgow: obrot wiezyczki wokol osi i w pionie
   bool  obiektcelujewgracza; //do czolgow: czy namierzaja gracza?
   int   obiektzniszcz;   //za ile klatek obiekt zostanie zniszczony

   bool  obiektcel; //czy to jeden z glownych celow? jesli tak, rysowany bedzie celownik

   byte wstawruchome; //jesli >=1 to w tym miejscu pojawi sie ruchomy obiekt o tym numerze, kiedy wejdzie na ekran
} teren[terensz][terendl];

struct
{
	float y,dy;
	float norm[3]; //wektor normalny
   int rnd;
} woda[51][81];

struct
{
	float x,y,z,
		  dx,dy,dz,
		  rozm,
		  obrotx, obroty, obrotz;
	short int jest;
	int czyj;
	int czas;

	int rodzaj; //0-pocisk, 1-bomba
} poc[200];

struct
{
	int rodzaj;

	float x, y, z,   x_,y_,z_,
		  dx, dy, dz;
	float smiglo;

   //dla samolotow wroga:
     float do_dx, do_dy;

	float lotkidx,lotkidy;

	float rozm;
	int dzialotemp, bombytemp;
   int strzalani; //klatka animacji strzalu; 0=bez animacji

   short int uszkodzenia[4];// B G M F
   short int ileuszkodzen;

	short int jest;
	short int zniszczony;

   float szalikn;
   float szalikx[szalikdlug];
   float szaliky[szalikdlug];
   float szalikz[szalikdlug];
   float szaliknormx[szalikdlug];
   float szaliknormy[szalikdlug];

   bool cel;

   bool spuscbombe, strzel;
} samolot[10]; //0 = gracz

struct
{
	short int jest;

	int rodzaj; //0=nic, 1=auto na drodze w bok
	float x, y, z,
		  dx, dy, dz,
        obrot; //obrot wokol wlasnej osi na terenie, w kierunku, w ktorym sie przesuwa
   bool zniszcz; //po trafieniu itd, zeby go zabilo

   float rozmiar; //zasieg od srodka, do niszczenia
   int przyczepionydo;

   int   obiektpatrzyobr, obiektpatrzypion; //do barek: obrot wiezyczki wokol osi i w pionie

   int ktorykanal; //dla lokomotywy itd, na ktorym kanale gra dzwiek

   bool cel;
} ruchome[30]; //obiekty ruchome: auta na drodze, barki itp

struct
{
	short int jest;

	float x,y,z,
		  dx,dy,dz,
		  rozm, przezr,
                  szybkoscrozm, szybkoscprzezr,
                  maxrozm,
                  obrot;
   float waga;

   float r,g,b;
   short int rodzaj; //0=kula wybuchu, 1=sprajt dymu, 2=sprajt wybuchu, 3=sprajt ziemi, 4=sprajt wody/plusku

} wyb[400];

struct
{
   float jasnosc, czas;
   float x,y,z;

} swiatla[8];
const int swiatlaod=2;
const int swiatlado=7;

struct
{
   float x,y,z;
   bool jest;
   bool juzniema; //nie ma na ekranie, wiec obliczamy jego pozycje z szybkosci
} swiatlolotniska;

struct
{
	int rodzajwody;
   short int jestwiatr;
   float kierwiatrx,kierwiatrz;
   int typsterowania; //0=gora/dol 1=dol/gora

   float odleglosckamery;

   bool mgla;

   float jasnoscswiatla;   //obecna jasnosc
   float dojasnoscswiatla; //docelowa jasnosc, do ktorej powoli sie zmienia

   int poziomtrudnosci; //0=novice,1=intermediate,2=advanced
   int detale;
   bool grawitacja;
   bool pauza;

   bool jestniebo;
   bool wskazniki;

   int glosnosc; //glosnosc dzwiekow w skali 0-10

   int pozycja_kursora; //w menu ustawiania opcji

} ustawienia;

struct
{
	int corobi; //0=stoi na lotnisku, 1=startuje, 2=leci

   float fuel, alt;
   int score, bomb;

   bool na_poziomie_samolotu;

   bool nad_lotniskiem; //w ogole jest nad lotniskiem?
   bool moze_ladowac;   //nad lotniskiem i ma odpowiednia predkosc?
   bool jest_lotnisko;   //czy jest juz lotnisko w poblizu?
   int ostrzezenie_o_lotnisku; //w ktorym miejscu terenu (zod) pokazac info o lotnisku?

   int rank;

   int etap; //czyli ktore lotnisko jest za graczem
   bool czymiasto; //jesli mamy leciec do miasta...

   int koniecgry; //licznik do zakonczenia gry i pokazania listy rekordow
   bool winieta;
   bool jest_gra; //czy w chwili obecnej toczy sie gra?

   int ile_celow_glownych; //ile zostalo zniszczonych juz celow glownych w sumie?
   int ile_celow_glownych_teraz; //ile zniszczonych od ostatniego lotniska?

   //wskaznik kierunku celu
   int jaki_cel_pokazuje;  //-1 = zaden, 0=samolot, 1=ruchome, 2=na ziemi
   int ktory_cel_pokazuje; //dla samolotow i ruchomych
   int gdziex_cel_pokazuje,gdziez_cel_pokazuje; //dla celow naziemnych: wspolrzedne x,y na terenie

} gracz;

struct
{
   float fuel, alt;
   int spd, score, bomb;
   int odswiezwiatr;
   int odswiezuszkodzenia;
   int odswiezostrzezenieosamolocie;

   int ostrzezenieosamolocie;
} ekran;

int kldol,klgora;

struct
{
	short int jest;

	float x,y,z, //pozycja
		  dx,dy,dz, //kierunek lotu
		  rx,ry,rz, //rozmiar w kazda strone
        obrot, //kat obrocenia w strone, w ktora leci
        waga; //szybkosc spadania

   float r,g,b; //kolor
   short int plonie, dymi; //czy plonie/dymi [0/1]

} smiec[400];

GLUquadricObj *kula;
GLUquadricObj *drzewo;
GLUquadricObj *kolo;

typedef struct
{
   String imie;
   long unsigned int pkt;
   int rank;
} rekord;

rekord rekordy[ilemiejsc];

const String ranki[]=
      {"Kamikaze trainee", //class 1
       "Runway sweeper", //class 2 (wszystkie zniszczenia)   //class 1 (rozwalilem sie o samolot wroga), (c1, 210p)
       "Air Cadet", //class 4, (2260pkt, zniszczony) (1010pkt, rozwalony na lotnisku), (c2, 4220p rozwalony na lotnisku)
       "Blue Max"};
