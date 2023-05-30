FSOUND_SAMPLE  *dzwiek[20];
FSOUND_STREAM  *muzyka;
int             muzyka_chan;
char            key, listenerflag = 1;
int             driver, i = 0, channel1 = -1, channel2 = -1;
float           listenerpos[3] =  { 0,0,0 };

int dzwiekoutput=1;
int dzwiekoutputtyp=0;

#define ilekanalow 10
int kanaly[ilekanalow]; //0: silnik samolotu gracza

//---------------------------------------------------------------------------
void dzwiekiClose()
{
    // you dont need to free samples if you let fsound's sample manager look after samples, as
    // it will free them all for you.
    FSOUND_Close();
}

//---------------------------------------------------------------------------
int ladujdzwiek(int nr, char * nazwa, int czyloop)
{
    dzwiek[nr] = FSOUND_Sample_Load(FSOUND_FREE, nazwa, FSOUND_HW2D, 0, 0);
    if (!dzwiek[nr])
    {
        printf( "blad: %s\n", FMOD_ErrorString(FSOUND_GetError()));
        dzwiekiClose();
        return 1;
    }

    // increasing mindistnace makes it louder in 3d space
    FSOUND_Sample_SetMinMaxDistance(dzwiek[nr], 4.0f, 10000.0f);

    if (czyloop) FSOUND_Sample_SetMode(dzwiek[nr], FSOUND_LOOP_NORMAL);
            else FSOUND_Sample_SetMode(dzwiek[nr], FSOUND_LOOP_OFF);

    return 0;
}

//---------------------------------------------------------------------------
int dzwieki_start()
{
    if (FSOUND_GetVersion() < FMOD_VERSION)
    {
        printf("Error : You are using the wrong DLL version!  You should be using FMOD %.02f\n", FMOD_VERSION);
        return 1;
    }

  switch (dzwiekoutput) {
        case '0' :  FSOUND_SetOutput(FSOUND_OUTPUT_NOSOUND); break;
        case '1' :  FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND); break;
        case '2' :  FSOUND_SetOutput(FSOUND_OUTPUT_WINMM); break;
  }


    for (i=0; i < FSOUND_GetNumDrivers(); i++)
    {
        //printf("%d - %s\n", i+1, FSOUND_GetDriverName(i));    // print driver names
        {
            unsigned int caps = 0;

            FSOUND_GetDriverCaps(i, &caps);

            if (caps & FSOUND_CAPS_HARDWARE)
                printf("  * Driver supports hardware 3D sound!\n");
            if (caps & FSOUND_CAPS_EAX2)
                printf("  * Driver supports EAX 2 reverb!\n");
            if (caps & FSOUND_CAPS_EAX3)
                printf("  * Driver supports EAX 3 reverb!\n");
        }
    }

    FSOUND_SetDriver(dzwiekoutputtyp); // Select sound card (0 = default)



/*    {
        unsigned int caps = 0;

        FSOUND_GetDriverCaps(FSOUND_GetDriver(), &caps);

        printf("---------------------------------------------------------\n");
        printf("Driver capabilities\n");
        printf("---------------------------------------------------------\n");
        if (!caps)
            printf("- This driver will support software mode only.\n  It does not properly support 3D sound hardware.\n");
        if (caps & FSOUND_CAPS_HARDWARE)
            printf("- Driver supports hardware 3D sound!\n");
        if (caps & FSOUND_CAPS_EAX2)
            printf("- Driver supports EAX 2 reverb!\n");
        if (caps & FSOUND_CAPS_EAX3)
            printf("- Driver supports EAX 3 reverb!\n");
        printf("---------------------------------------------------------\n");
    }*/

    FSOUND_SetMixer(FSOUND_MIXER_AUTODETECT);

    if (!FSOUND_Init(44100, 32, 0))
    {
        printf("Init: %s\n", FMOD_ErrorString(FSOUND_GetError()));
        return 1;
    }


    ladujdzwiek(0,"dane\\gun.wav", false);
    ladujdzwiek(1,"dane\\explode1.wav", false);
    ladujdzwiek(2,"dane\\explode2.wav", false);
    ladujdzwiek(3,"dane\\explode3.wav", false);
//    ladujdzwiek(4,"dane\\ZIP 2.wav", true);
    ladujdzwiek(4,"dane\\samolotmono.wav", true);
    ladujdzwiek(5,"dane\\bomba.wav", false);
    ladujdzwiek(6,"dane\\tankgun.wav", false);
    ladujdzwiek(7,"dane\\train.wav", true);
    ladujdzwiek(8,"dane\\train2.wav", false);
    ladujdzwiek(9,"dane\\czolg.wav", true);
    ladujdzwiek(10,"dane\\sygsaml.wav", false);
    ladujdzwiek(11,"dane\\plum.wav", false);
    ladujdzwiek(12,"dane\\rikoszet.wav", false);


    FSOUND_Stream_SetBufferSize(1000);

    FILE      *fp;
    int        length;
    char      *data;

    fp = fopen("dane\\muzyka.mp3", "rb");
    if (!fp)
    {
        printf("Error!\n");
        printf("File Not Found\n");
        FSOUND_Close();
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    data = (char *)malloc(length);
    fread(data, length, 1, fp);
    fclose(fp);

    muzyka = FSOUND_Stream_Open(data, FSOUND_NORMAL | FSOUND_MPEGACCURATE | FSOUND_LOADMEMORY, 0, length);

    muzyka_chan = FSOUND_Stream_PlayEx(20, muzyka, NULL, TRUE);
//    FSOUND_SetPaused(muzyka_chan, FALSE);

    return 0;
}

//---------------------------------------------------------------------------
void zagrajdzwiek(int n, float px, float py, float pz, int rnd, bool blisko)
{
  int dz = FSOUND_PlaySound(FSOUND_FREE, dzwiek[n]);
  FSOUND_SetFrequency(dz, (int) (44100-rnd/2+random(rnd)));
  if (!blisko) {
     int o;
     float o2 = pow(samolot[0].x-px,2)+pow(samolot[0].y-py,2)+pow(samolot[0].z-pz,2);
     if (o2==0) o2=0.01;
     o = (int)(255.0 - floor(sqrt( o2*5.0 ) ));

     if (o<0) o = 0;
     if (o>255) o = 255;

     FSOUND_SetVolume(dz, o);


     o=128+(px-samolot[0].x)*10;
     if (o<0) o = 0;
     if (o>255) o = 255;

     FSOUND_SetPan(dz, o);

  } else
     FSOUND_SetPan(dz, FSOUND_STEREOPAN);

}

