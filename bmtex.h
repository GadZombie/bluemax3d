struct TGAFile
{
	unsigned char typeCode;
	short int width;
	short int height;
	unsigned char bpp;
	GLenum format;
	unsigned char *imageData;
};

bool loadUncompressedTGA(char *filename, TGAFile *tgaFile)
{
	FILE *file;

	unsigned char tmpRGB;

	unsigned char ucNull;
	unsigned short usNull;

	TCHAR path[256];
	char fullPath[256];
	GetModuleFileName(NULL, path, 256);

/*	TCHAR *pos = wcsrchr(path, '\\');
	*(pos + 1) = '\0';

	wcstombs(fullPath, path, 256);

	strcat(fullPath, filename);
*/
	file = fopen(filename,"rb");

	if (!file)
	{
		//MessageBox(NULL, L"Can't Find TGA", L"Error", MB_OK);
		return false;
	}

	fread(&ucNull,sizeof(unsigned char),1,file);
	fread(&ucNull,sizeof(unsigned char),1,file);

	fread(&tgaFile->typeCode,sizeof(unsigned char),1,file);

	if (tgaFile->typeCode != 2 && tgaFile->typeCode != 3)
	{
		//MessageBox(NULL, L"Incorrect texture type", L"Error", MB_OK);
		fclose(file);
		return false;
	}

	fread(&usNull,sizeof(unsigned short),1,file);
	fread(&usNull,sizeof(unsigned short),1,file);
	fread(&ucNull,sizeof(unsigned char),1,file);
	fread(&usNull,sizeof(unsigned short),1,file);
	fread(&usNull,sizeof(unsigned short),1,file);

	fread(&tgaFile->width, sizeof(unsigned short), 1, file);
	fread(&tgaFile->height, sizeof(unsigned short), 1, file);
	fread(&tgaFile->bpp, sizeof(unsigned char), 1, file);

	fread(&ucNull,sizeof(unsigned char),1,file);

	int colorMode = tgaFile->bpp / 8;

	if (colorMode == 3)
		tgaFile->format = GL_RGB;
	else
		tgaFile->format = GL_RGBA;

	long imageSize = tgaFile->width * tgaFile->height * colorMode;

	tgaFile->imageData = new unsigned char[imageSize];

	if (!tgaFile->imageData)
	{
		//MessageBox(NULL, L"Out of Memory", L"Error", MB_OK);
		delete[] tgaFile->imageData;
		fclose(file);
		return false;
	}

	fread(tgaFile->imageData,sizeof(unsigned char),imageSize,file);

	if (!tgaFile->imageData)
	{
		//MessageBox(NULL, L"Error reading TGA", L"Error", MB_OK);
		fclose(file);
		return false;
	}

	for (int i = 0; i < imageSize; i += colorMode)
	{
		tmpRGB = tgaFile->imageData[i];
		tgaFile->imageData[i] = tgaFile->imageData[i+2];
		tgaFile->imageData[i+2] = tmpRGB;
	}

	fclose(file);

	return true;
}


bool wczytaj_teksture(int numer, char * nazwa, int jaka)
{
	TGAFile tgaFile;

   if (!loadUncompressedTGA(nazwa, &tgaFile))
		return false;

	glBindTexture(GL_TEXTURE_2D, texName[numer]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (jaka==0) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		else
	if (jaka==1) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (jaka==1)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	}

   glTexImage2D(GL_TEXTURE_2D, 0, tgaFile.format, tgaFile.width,
                tgaFile.height, 0, tgaFile.format, GL_UNSIGNED_BYTE,
                tgaFile.imageData);
     
	if (gluBuild2DMipmaps(GL_TEXTURE_2D, tgaFile.bpp/8,
						tgaFile.width,
						tgaFile.height,
						tgaFile.format,
						GL_UNSIGNED_BYTE,
						tgaFile.imageData)
	 !=0)
		exit(1);

	delete[] tgaFile.imageData;
   delete nazwa;
   return true;
}

void wlacz_teksture_env(int numer)
{
	glBindTexture(GL_TEXTURE_2D, texName[numer]);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_2D);
}

void wlacz_teksture(int numer)
{
	glBindTexture(GL_TEXTURE_2D, texName[numer]);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//	glLightModeli(GL_LIGHT_MODEL_AMBIENT, GL_FALSE);
	glEnable(GL_TEXTURE_2D);
}


void wylacz_teksture()
{
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
};

