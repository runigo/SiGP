
/*
Copyright avril 2018, Stephan Runigo
runigo@free.fr
SiGP 1.4  simulateur de gaz parfait
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

#include "donnees.h"

	//		Valeurs initiales des données physiques du simulateur,
	//						et création du système

	//		Valeur initiale et création du graphe

	//		Initialisation de la SDL


int donneesSysteme(systemeT * systeme, optionsT * options);
int donneesGraphe(grapheT * graphe, optionsT * options);

int donneesOptions(optionsT * options)
	{
		// Préréglage des valeurs optionnelles

	(*options).fond=240;		// couleur du fond de l'affichage
	(*options).pause=25;		// temps de pause SDL en ms
	(*options).duree=1;		// nombre d'incrémentation du système par affichage

	(*options).temperature = 8.9;	// Température initiale
	(*options).gauche = 0.00333;	// Température thermostat gauche
	(*options).droite = 33.3;	// Température thermostat droit

	(*options).thermostat=0;	// 0 : système isolé, 1 : système thermostaté.
	(*options).cloison = 1;		// 0 : pas de paroi centrale. 1 : détente de joule, 2 : cloison fermé,
					//	 -1, -2 : démon de maxwell.
	(*options).trou = DEMItROU;

	return 0;
	}

int donneesControleur(controleurT * controleur)
	{

	(*controleur).duree = (*controleur).options.duree;	// nombre d'évolution du système par affichage

	(*controleur).mode = 1;	// -1 : Wait, 1 : Poll
	(*controleur).sortie = 0;	// Sortie de SiCP si > 0
	(*controleur).appui = 0;	// Appuie sur la souris

		fprintf(stderr, " Initialisation du système\n");
	donneesSysteme(&(*controleur).systeme, &(*controleur).options);

		fprintf(stderr, " Initialisation du graphe\n");
	donneesGraphe(&(*controleur).graphe, &(*controleur).options);

		fprintf(stderr, " Initialisation SDL\n");
	graphiqueInitialiseSDL((*controleur).options.fond);

		fprintf(stderr, " Initialisation horloge SDL\n");
	horlogeCreation(&(*controleur).horloge);

	return 0;
	}

int donneesSysteme(systemeT * systeme, optionsT * options)
	{
		// Initialisation géométrique de l'enceinte

	(*systeme).montage.largeur = (LARGEUR-MARGE); // Largeur
	(*systeme).montage.hauteur = (HAUTEUR-MARGE);// Hauteur
	(*systeme).montage.demiLargeur = (LARGEUR-MARGE)/2; // Demi largeur
	(*systeme).montage.demiHauteur = (HAUTEUR-MARGE)/2;// Demi hauteur

	//(*systeme).montage.epaisseur = TAILLE;// Épaisseur de la cloison

	(*systeme).montage.paroiCentrale = (*options).cloison;// 0 : pas de paroi centrale. 
	(*systeme).montage.trou = (*options).trou;// Taille du trou, sur 2

		// Initialisation du thermostat

	(*systeme).montage.thermostat.temperature = (*options).temperature;//	Température initiale
	(*systeme).montage.thermostat.gauche = (*options).gauche;	//	Température thermostat gauche
	(*systeme).montage.thermostat.droite = (*options).droite;	//	Température thermostat droite

	(*systeme).montage.thermostat.actif = (*options).thermostat;	//	0 : Système isolé, 1:température uniforme, 2:active gauche-droite

		// Initialisation du système
	systemeInitialise(systeme, TAILLE, sqrt((*options).temperature));

	return 0;
	}

int donneesGraphe(grapheT * graphe, optionsT * options)
	{
			// Points du montage
		//	
		//			ax	bx	cx
		//
		//		dy	-----------------
		//			|	|	|
		//		ey	|	-	|
		//		fy	|	-	|
		//			|	|	|
		//		gy	-----------------

		// Absisses
	(*graphe).ax = MARGE/2;
	(*graphe).bx = LARGEUR/2;
	(*graphe).cx = LARGEUR - MARGE/2;

		// Ordonnées
	(*graphe).dy = MARGE/2;
	(*graphe).ey = HAUTEUR/2 - DEMItROU;
	(*graphe).fy = HAUTEUR/2 + DEMItROU;
	(*graphe).gy = HAUTEUR - MARGE/2;

	(*graphe).cloison = (*options).cloison;	//
	(*graphe).thermostat = (*options).thermostat;	// 
	//(*graph).trou = (*options).trou;

		// Initialisation du graphe
	grapheInitialise(graphe, 20, 150, 200, (*options).fond);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////
