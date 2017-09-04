
/*
Copyright septembre 2017, Stephan Runigo
runigo@free.fr
SiGP 1.3.3  simulateur de gaz parfait
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

#include "controleur.h"

int controleurProjection(controleurT * control);
int controleurEvolutionSysteme(controleurT * control);
int controleurConstructionGraphique(controleurT * control);
int controleurActionClavier(controleurT * control);

int controleurTraiteEvenement(controleurT * control);

int controleurClavier(controleurT * control);
int controleurSouris(controleurT * control);
void controleurBoutonSouris(controleurT * control, int appui);

void controleurChangeMode(controleurT * control);
void controleurChangeVitesse(controleurT * control, float facteur);


int controleurSimulationGraphique(controleurT * control)
	{

	fprintf(stderr, "Entrée dans la boucle SDL\n");
	do
		{
			//fprintf(stderr, "Projection du systeme sur la représentation graphique\n");
		controleurProjection(control);

			//fprintf(stderr, "Evolution du systeme\n");
		controleurEvolutionSysteme(control);

			//fprintf(stderr, "Mise à jour de la fenêtre graphique et pause\n");
		controleurConstructionGraphique(control);

			//fprintf(stderr, "Prise en compte des actions clavier\n");
		controleurActionClavier(control);

		}
	while((*control).evenement.type != SDL_QUIT);

	return 0;
	}

int controleurProjection(controleurT * control)
	{
		// Projection du système sur le graphique
	projectionSystemeGraphe(&(*control).systeme,&(*control).graphe);

	return (*control).sortie;
	}

int controleurEvolutionSysteme(controleurT * control)
	{
		// Évolution du système
	systemeEvolue(&(*control).systeme, (*control).duree);

	return 0;
	}

int controleurConstructionGraphique(controleurT * control)
	{
		//fprintf(stderr, "Dessin des graphes\n");
	graphiqueDessineGraphe(&(*control).graphe);

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	//graphiqueMiseAJour();

		//fprintf(stderr, "Pause %d \n", (*control).options.pause);
	SDL_Delay((*control).options.pause);

	return 0;
	}

int controleurActionClavier(controleurT * control)
	{
	int sortie = 0;
		//fprintf(stderr, "Traitement des évenements, mode %d\n", (*control).mode);
	if((*control).mode<0)
		{
				// Attente d'un évenement SDL
		if(SDL_WaitEvent(&(*control).evenement))
			{
			sortie += controleurTraiteEvenement(control);
			}
		}
	else
		{
			// Sans attente
		if( SDL_PollEvent(&(*control).evenement) )
			{
			sortie += controleurTraiteEvenement(control);
			}
		}


	if((*control).evenement.type == SDL_QUIT) sortie += 1;

	(*control).sortie += sortie;

	return (*control).sortie;
	}

int controleurTraiteEvenement(controleurT * control)
	{
	int sortie = 0;
	switch((*control).evenement.type)
		{
		case SDL_QUIT:
			sortie = 1;break;
	  case SDL_KEYDOWN:
	    sortie = controleurClavier(control);break;
		/*case SDL_KEYDOWN:
			if (((*control).evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
				{sortie = controleurClavierMaj(control);break;}
			else
				{
				if (((*control).evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT)
					{sortie = controleurClavierMaj(control);break;}
				else {sortie = controleurClavier(control);break;}
				}*/
		default:
			;
		}

	if(sortie != 0)
		{
		fprintf(stderr, "sortie <> 0\n");
		(*control).sortie = 1;
		}
	return sortie;
	}

void controleurChangeMode(controleurT * control)
	{
	(*control).mode=-(*control).mode;

	return;
	}

void controleurChangeVitesse(controleurT * control, float facteur)
	{
	if( (*control).duree > DUREE_MAX && facteur > 1 )
		{
		fprintf(stderr, "duree maximale atteinte");
		}
	else
		{
		if( (*control).duree > 11 )
			{
			(*control).duree = (*control).duree * facteur;
			}
		else
			{
			if( facteur > 1)
				{
				(*control).duree ++;
				}
			else
				{
				if( (*control).duree > 1 )
					{
					(*control).duree --;
					}
				else
					{
					fprintf(stderr, "duree minimale atteinte");
					}
				}
			}
		}
	fprintf(stderr, "duree = %d\n", (*control).duree);
	return;
	}

int controleurClavier(controleurT * control)
	{
	switch ((*control).evenement.key.keysym.sym)
		{

	// Sortie

		case SDLK_ESCAPE:
			(*control).sortie = 1;break;

    // Mode : attente d'un evenement / pas d'attente

		case SDLK_RETURN:
			controleurChangeMode(control);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(control);break;

	// Vitesse de la simulation

		case SDLK_KP_PLUS:
			controleurChangeVitesse(control, 1.7);break;
		case SDLK_KP_MINUS:
			controleurChangeVitesse(control, 0.6);break;

		case SDLK_UP:
			controleurChangeVitesse(control, 1.1);break;
		case SDLK_DOWN:
			controleurChangeVitesse(control, 0.9);break;
		case SDLK_LEFT:
			controleurChangeVitesse(control, 0.6);break;
		case SDLK_RIGHT:
			controleurChangeVitesse(control, 1.7);break;

	// Taille du trou

		case SDLK_a:
			montageChangeTrou(&(*control).systeme.montage, 1.1);break;
		case SDLK_q:
			montageChangeTrou(&(*control).systeme.montage, 0.9);break;
		case SDLK_z:
			montageChangeTrou(&(*control).systeme.montage, -2);break;
		case SDLK_s:
			montageChangeTrou(&(*control).systeme.montage, -1);break;

		case SDLK_w:	//	Pas de cloison central
			systemeChangeCloison(&(*control).systeme, 0);break;
		case SDLK_x:	//	Cloison fermée
			systemeChangeCloison(&(*control).systeme, 1);break;
		case SDLK_c:	//	Cloison percée
			systemeChangeCloison(&(*control).systeme, 2);break;
		case SDLK_v:	//	Démon de Maxwell
			systemeChangeCloison(&(*control).systeme, -1);break;

	// Thermostat

		case SDLK_o:	//	Système isolé
			thermostatChangeEtat(&(*control).systeme.montage.thermostat, 0);break;
		case SDLK_i:	//	Système thermostaté symétrique
			thermostatChangeEtat(&(*control).systeme.montage.thermostat, 1);break;
		case SDLK_k:	//	Système  thermostaté gauche-droite
			thermostatChangeEtat(&(*control).systeme.montage.thermostat, 2);break;
		case SDLK_l:	//	Erreur
			thermostatChangeEtat(&(*control).systeme.montage.thermostat, 3);break;

		case SDLK_p:	//	Valeur de la température
			thermostatChangeTemperature(&(*control).systeme.montage.thermostat, 1.7);break;
		case SDLK_m:	//	
			thermostatChangeTemperature(&(*control).systeme.montage.thermostat, 0.6);break;

		case SDLK_u:	//	Température à droite
			thermostatChangeTemperatureDroite(&(*control).systeme.montage.thermostat,1.9);break;
		case SDLK_j:	//	Température à droite
			thermostatChangeTemperatureDroite(&(*control).systeme.montage.thermostat,0.51);break;
		case SDLK_y:	//	Température à gauche
			thermostatChangeTemperatureGauche(&(*control).systeme.montage.thermostat,1.9);break;
		case SDLK_h:	//	Température à gauche
			thermostatChangeTemperatureGauche(&(*control).systeme.montage.thermostat,0.51);break;


  // Initialiser le système

		case SDLK_F1:
			systemeInitialisePosition(&(*control).systeme);
			break;

  // Afficher les observables

		case SDLK_F5:	//	
			observablesAfficheEnergie(&(*control).systeme);
			break;

  // Changer le montage

		case SDLK_F9:	//	Trou
			observablesAfficheEnergie(&(*control).systeme);
			break;

  // Afficher les observables

		case SDLK_F10:	//	Maxwel
			observablesAfficheEnergie(&(*control).systeme);
			break;

		default:
			;
		}
	return (*control).sortie;
	}

//////////////////////////////////////////////////////////////////////////////////////
	//FILE *energie;
	//energie = fopen("cinetique","w");
	//if (energie==NULL){printf("Erreur de création du fichier \n");}

	//fclose(energie);
	//fprintf(energie, "%d %6.3f %6.3f\n", ti, cinetique(system), ecartCinetique(system));

