
/*
Copyright février 2018, Stephan Runigo
runigo@free.fr
SiGP 1.3.7  simulateur de gaz parfait
Ce logiciel est un programme informatique servant à simuler un gaz parfait
et à en donner une représentation graphique. Il permet d'observer une détente
de Joule ainsi que des transferts thermiques avec des thermostats.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "graphique.h"

//////// Variables globales //////

SDL_Surface* affichage;

Uint32 couleurNouveau;
Uint32 couleurActuel;
Uint32 couleurAncien;

Uint32 couleurTrace1;
Uint32 couleurTrace2;

Uint32 couleurFond;

/////////////////////////////////

void graphiqueAffichePixel (int x, int y, Uint32 couleur);
void graphiqueAffichePixelVerif(int x, int y, Uint32 couleur);
void graphiqueLigneDroite(int X, int Y, int x, int y, Uint32 couleur);
void graphiqueCercle(int X, int Y, int rayon, Uint32 couleur);
void graphiqueDisque(int X, int Y, int rayon, Uint32 couleur);
void graphiqueParticule(int abs, int ord, Uint32 couleur);

int graphiqueInitialiseSDL(int fond)
	{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
		fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
		}

	atexit(SDL_Quit);

	affichage = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_SWSURFACE);

	if (affichage == NULL)
		{
		fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
		}
	SDL_WM_SetCaption("Simulateur de gaz parfait", NULL);

	couleurNouveau = SDL_MapRGB(affichage->format, 255-fond, 255-fond/2, 255);
	couleurTrace1 = SDL_MapRGB(affichage->format, 222-fond/3, 222, 222-fond/3);
	couleurActuel = SDL_MapRGB(affichage->format,151,90,50);
	couleurTrace2 = SDL_MapRGB(affichage->format, 111+fond/3, 111, 111+fond/3);
	couleurAncien = SDL_MapRGB(affichage->format, 111, 11, 11);
	couleurFond = SDL_MapRGB(affichage->format, fond, fond, fond);

	//Uint32 couleurS=SDL_MapRGB(affichage->format, (*graphe).rouge, (*graphe).vert, (*graphe).bleu);
	//Uint32 couleurP=SDL_MapRGB(affichage->format, (*graphe).vert, (*graphe).rouge, (*graphe).bleu);

	SDL_FillRect(affichage, NULL, couleurFond);

	return 0;
	}

int graphiqueNettoyage(void)
	{
	SDL_FillRect(affichage, NULL, couleurFond);
	return 0;
	}

int graphiqueMiseAJour(void)
	{
	SDL_UpdateRect(affichage, 0, 0, 0, 0);
	return 0;
	}

void graphiqueAffichePixel(int x, int y, Uint32 couleur)
	{
	*((Uint32*)(affichage->pixels) + x + y * affichage->w) = couleur;
	return;
	}

void graphiqueAffichePixelVerif(int x, int y, Uint32 couleur)
	{
	if (x>=0 && x < affichage->w && y>=0 && y < affichage->h)
		graphiqueAffichePixel(x, y, couleur);
	return;
	}

void graphiqueLigneDroite(int X, int Y, int x, int y, Uint32 couleur)
	{
	int i, abs, ord;
	int min, max;
	float a;

	max=X-x; min=Y-y;
	if(max<0){max=-max;} if(min<0){min=-min;}
	if(max<min){max=min;}
	max=1.1*max;

	for(i=0;i<max;i++)
		{
		a=i/(float)max;
		abs=(X+(int)(a*(x-X)));
		ord=(Y+(int)(a*(y-Y)));
		graphiqueAffichePixelVerif(abs, ord, couleur);
		}
	return;
	}

void graphiqueCercle(int X, int Y, int rayon, Uint32 couleur)
	{
	int i, abs, ord;

	int p = 2*PI*rayon + 1;

	for(i=0;i<p;i++)
		{
		abs=(X+rayon*sin(i/(float)rayon));
		ord=(Y+rayon*cos(i/(float)rayon));
		graphiqueAffichePixelVerif(abs, ord, couleur);
		}
	return;
	}

void graphiqueDisque(int X, int Y, int rayon, Uint32 couleur)
	{
	int i;

	if(rayon > 1)
		{
		for(i=1;i<rayon;i++)
			{
			graphiqueCercle(X, Y, i, couleur);
			}
		}
	else
		{
		graphiqueAffichePixelVerif(X, Y, couleur);
		}

	return;
	}

void graphiqueDessineGraphe(grapheT * graphe)
	{
	int i, x, y, X, Y;
	int rayon = (*graphe).rayon;

	  //fprintf(stderr, "Suppression de l'ancien graphe\n");
	SDL_FillRect(affichage, NULL, 0);

	  //fprintf(stderr, "Particules\n");
		// Particules
	for(i=0;i<NOMBRE;i++)
		{
		x=(*graphe).ancienAbscisse[i];
		y=(*graphe).ancienOrdonnee[i];
		//fprintf(stderr, "graphiqueDisque, x, y %d %d \n",x, y);
		graphiqueDisque(x, y, rayon, couleurAncien);
		//graphiqueParticule(x, y, couleurAncien);
		X=(*graphe).actuelAbscisse[i];
		Y=(*graphe).actuelOrdonnee[i];
		//fprintf(stderr, "graphiqueDisque, X, Y %d %d \n", X, Y);
		graphiqueDisque(X, Y, rayon, couleurActuel);
		//graphiqueParticule(x, y, couleurActuel);
		graphiqueLigneDroite(X, Y, x, y, couleurTrace2);
		x=(*graphe).nouveauAbscisse[i];
		y=(*graphe).nouveauOrdonnee[i];
		//fprintf(stderr, "graphiqueDisque, x, y %d %d \n",x, y);
		graphiqueDisque(x, y, rayon, couleurNouveau);
		//graphiqueParticule(x, y, couleurNouveau);
		graphiqueLigneDroite(X, Y, x, y, couleurTrace1);
		}

		// Parois horizontales
		graphiqueLigneDroite((*graphe).ax, (*graphe).dy, (*graphe).cx, (*graphe).dy, couleurTrace1);
		graphiqueLigneDroite((*graphe).ax, (*graphe).gy, (*graphe).cx, (*graphe).gy, couleurTrace1);
		// Parois verticales
		graphiqueLigneDroite((*graphe).ax, (*graphe).dy, (*graphe).ax, (*graphe).gy, couleurTrace1);
		graphiqueLigneDroite((*graphe).cx, (*graphe).dy, (*graphe).cx, (*graphe).gy, couleurTrace1);

		// Paroi centrale
	if((*graphe).cloison != 0)
		{
		graphiqueLigneDroite((*graphe).bx, (*graphe).dy, (*graphe).bx, (*graphe).ey, couleurTrace1);
		graphiqueLigneDroite((*graphe).bx, (*graphe).fy, (*graphe).bx, (*graphe).gy, couleurTrace1);
		}

	//fprintf(stderr, "Mise à jour de l'affichage\n");
	SDL_UpdateRect(affichage, 0, 0, 0, 0);
	return;
	}
/*
void graphiqueParticule(int abs, int ord, Uint32 couleur)
	{
	int i;
	int j;

	for(i=-1;i<2;i++)
		{
	for(j=-1;j<2;j++)
			{
			graphiqueAffichePixelVerif(abs+i, ord+j, couleur);
			}
		}
	graphiqueAffichePixelVerif(abs+2, ord, couleur);
	graphiqueAffichePixelVerif(abs-2, ord, couleur);
	graphiqueAffichePixelVerif(abs, ord+2, couleur);
	graphiqueAffichePixelVerif(abs, ord-2, couleur);

	return;
	}

void graphiqueDessineGraphe(grapheT * graphe)
	{
	int i, x, y, X, Y;

	  //fprintf(stderr, "Suppression de l'ancien graphe\n");
	SDL_FillRect(affichage, NULL, 0);

	  //fprintf(stderr, "Particules\n");
		// Particules
	for(i=0;i<NOMBRE;i++)
		{
		x=(*graphe).ancienAbscisse[i];
		y=(*graphe).ancienOrdonnee[i];
		//fprintf(stderr, "graphiqueDisque, x, y %d %d \n",x, y);
		graphiqueDisque(x, y, 3, couleurAncien);
		//graphiqueParticule(x, y, couleurAncien);
		X=(*graphe).actuelAbscisse[i];
		Y=(*graphe).actuelOrdonnee[i];
		//fprintf(stderr, "graphiqueDisque, X, Y %d %d \n", X, Y);
		graphiqueDisque(X, Y, 3, couleurActuel);
		//graphiqueParticule(x, y, couleurActuel);
		graphiqueLigneDroite(X, Y, x, y, couleurTrace2);
		x=(*graphe).nouveauAbscisse[i];
		y=(*graphe).nouveauOrdonnee[i];
		//fprintf(stderr, "graphiqueDisque, x, y %d %d \n",x, y);
		graphiqueDisque(x, y, 3, couleurNouveau);
		//graphiqueParticule(x, y, couleurNouveau);
		graphiqueLigneDroite(X, Y, x, y, couleurTrace1);
		}

		// Parois horizontales
	for(i=0; i<TAILLE; i++)
		{
		graphiqueLigneDroite((*graphe).ax-TAILLE, (*graphe).dy-i, (*graphe).cx+TAILLE, (*graphe).dy-i, couleurTrace1);
		graphiqueLigneDroite((*graphe).ax-TAILLE, (*graphe).gy+i, (*graphe).cx+TAILLE, (*graphe).gy+i, couleurTrace1);
		}
		// Parois verticales
	for(i=0; i<TAILLE; i++)
		{
		graphiqueLigneDroite((*graphe).ax-i-1, (*graphe).dy, (*graphe).ax-i-1, (*graphe).gy, couleurTrace1);
		graphiqueLigneDroite((*graphe).cx+i, (*graphe).dy, (*graphe).cx+i, (*graphe).gy, couleurTrace1);
		}

		// Paroi centrale
	if((*graphe).cloison != 0)
		{
		for(i=-TAILLE/2; i<TAILLE/2; i++)
			{
			graphiqueLigneDroite((*graphe).bx+i, (*graphe).dy, (*graphe).bx+i, (*graphe).ey, couleurTrace1);
			graphiqueLigneDroite((*graphe).bx+i, (*graphe).fy, (*graphe).bx+i, (*graphe).gy, couleurTrace1);
			}
		}

	//fprintf(stderr, "Mise à jour de l'affichage\n");
	  //	Mise à jour de l'affichage
	SDL_UpdateRect(affichage, 0, 0, 0, 0);
	return;
	}
*/
