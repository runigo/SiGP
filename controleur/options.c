
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

#include "options.h"

//void optionsFond(optionsT * options, char *opt);
void optionsPause(optionsT * options, char *opt);
void optionsDuree(optionsT * options, char *opt);

void optionsTemperature(optionsT * options, char *opt);
void optionsGauche(optionsT * options, char *opt);
void optionsDroite(optionsT * options, char *opt);

void optionsThermostat(optionsT * options, char *opt);
void optionsCloison(optionsT * options, char *opt);
void optionsTrou(optionsT * options, char *opt);

void optionsAide(void);

int optionsTraitement(optionsT * options, int nb, char *opt[])
	{
	int i=0;	//fprintf(stderr, "\nNombre d'options : %d\n", nb);
	do
		{

		//if(strcmp(opt[i], "fond")==0 && opt[i+1]!=NULL)
			//optionsFond(options, opt[i+1]);		// Couleur du fond de l'affichage
		if(strcmp(opt[i], "pause")==0 && opt[i+1]!=NULL)
			optionsPause(options, opt[i+1]);	// temps de pause en ms entre les affichages.
		if(strcmp(opt[i], "duree")==0 && opt[i+1]!=NULL)
			optionsDuree(options, opt[i+1]);	// Nombre d'évolution du système entre les affichages.

		if(strcmp(opt[i], "thermostat")==0 && opt[i+1]!=NULL)
			optionsThermostat(options, opt[i+1]);	// Activation du thermostat, 0 : système isolé.
		if(strcmp(opt[i], "temperature")==0 && opt[i+1]!=NULL)
			optionsTemperature(options, opt[i+1]);	// Température initiale.
		if(strcmp(opt[i], "gauche")==0 && opt[i+1]!=NULL)
			optionsGauche(options, opt[i+1]);	// Température thermostat gauche.
		if(strcmp(opt[i], "droite")==0 && opt[i+1]!=NULL)
			optionsDroite(options, opt[i+1]);	// Température thermostat droit.

		if(strcmp(opt[i], "cloison")==0 && opt[i+1]!=NULL)
			optionsCloison(options, opt[i+1]);	// Activation cloison centrale.
		if(strcmp(opt[i], "trou")==0 && opt[i+1]!=NULL)
			optionsTrou(options, opt[i+1]);	// Trou dans la cloison centrale.

		if(strcmp(opt[i], "aide")==0)
			optionsAide();	// Affiche l'aide.
		if(strcmp(opt[i], "help")==0)
			optionsAide();	// Affiche l'aide.

  		i++;
  		}
		while(i<nb);
	return 0;
	}
/*
void optionsFond(optionsT * options, char *opt)
	{    	// Couleur du fond 
	int fond = atoi(opt);
	if(fond>0 && fond<255)
		{
		(*options).fond = fond;
		printf("Option fond valide, fond = %d\n", (*options).fond);
		}
	else
		{
		printf("Option fond non valide, fond = %d\n", (*options).fond);
		printf("Option fond : 0 < fond < 255\n");
		}
	return;
	}
*/
void optionsPause(optionsT * options, char *opt)
	{    	// Temps de pause en ms après affichage graphique
	int pause = atoi(opt);
	if(pause>5 && pause<99)
		{
		(*options).pause = pause;
		printf("Option pause valide, pause = %d\n", (*options).pause);
		}
	else
		{
		printf("Option pause non valide, pause = %d\n", (*options).pause);
		printf("Option pause : 5 < pause < 555\n");
		}
	return;
	}

void optionsDuree(optionsT * options, char *opt)
	{    	// Nombre d'évolution du système entre les affichages
	int duree = atoi(opt);
	if ( duree > 0 && duree < DUREE_MAX)
		{
		(*options).duree = duree;
		printf("Option duree valide, duree = %d\n", (*options).duree);
		}
	else
		{
		printf("Option duree non valide, duree = %d\n", (*options).duree);
		printf("Option duree : 0.0 < duree < %d\n", DUREE_MAX);
		}
	return;
	}

void optionsTemperature(optionsT * options, char *opt)
	{    	// Température initiale
	float temperature = atof(opt);
	if(temperature>TEMPERATURE_MIN && temperature<TEMPERATURE_MAX)
		{
		(*options).temperature = temperature;
		printf("Option temperature valide, température initiale = %f\n", (*options).temperature);
		}
	else
		{
		printf("Option temperature non valide, température = %f\n", (*options).temperature);
		printf("Option temperature : %f < temperature < %f\n", TEMPERATURE_MIN, TEMPERATURE_MAX);
		}
	return;
	}

void optionsGauche(optionsT * options, char *opt)
	{    	// Température initiale à gauche
	float gauche = atof(opt);
	if(gauche>TEMPERATURE_MIN && gauche<TEMPERATURE_MAX)
		{
		(*options).gauche = gauche;
		printf("Option gauche valide, température thermostat gauche = %f\n", (*options).gauche);
		}
	else
		{
		printf("Option gauche non valide, gauche = %f\n", (*options).gauche);
		printf("Option gauche : %f < gauche < %f\n", TEMPERATURE_MIN, TEMPERATURE_MAX);
		}
	return;
	}

void optionsDroite(optionsT * options, char *opt)
	{    	// Température initiale à droite
	float droite = atof(opt);
	if(droite>TEMPERATURE_MIN && droite<TEMPERATURE_MAX)
		{
		(*options).droite = droite;
		printf("Option droite valide, température thermostat droite = %f\n", (*options).droite);
		}
	else
		{
		printf("Option droite non valide, droite = %f\n", (*options).droite);
		printf("Option droite : %f < droite < %f\n", TEMPERATURE_MIN, TEMPERATURE_MAX);
		}
	return;
	}

void optionsThermostat(optionsT * options, char *opt)
	{		// choix du thermostat
	int thermostat = atoi(opt);
	if(thermostat > -3 && thermostat < 3)
		{
		(*options).thermostat = thermostat;
		printf("Option thermostat valide, thermostat = %d\n", (*options).thermostat);
		}
	else
		{
		printf("Option thermostat non valide, thermostat = %d\n", (*options).thermostat);
		printf("Option thermostat : -3 < thermostat < 3\n");
		}
	return;
	}

void optionsCloison(optionsT * options, char *opt)
	{
	int cloison = atoi(opt);
	if(cloison > -3 && cloison <3)
		{
		(*options).cloison = cloison;
		printf("Option cloison valide, cloison = %d\n", (*options).cloison);
		}
	else
		{
		printf("Option cloison non valide, cloison = %d\n", (*options).cloison);
		printf("Option cloison : -3 < cloison < 3\n");
		}
	return;
	}

void optionsTrou(optionsT * options, char *opt)
	{
	int trou = atoi(opt);
	if(trou > -1 && trou < (HAUTEUR-MARGE)/2+1)
		{
		(*options).trou = trou;
		printf("Option trou valide, trou = %d\n", (*options).trou);
		}
	else
		{
		printf("Option trou non valide, trou = %d\n", (*options).trou);
		printf("Option trou : 0 <= trou < %d\n", DEMItROU);
		}
	return;
	}

void optionsAide(void)
	{
	printf("\n\nAide de SiGP\n\n");

	printf("Options et commande du simulateur de thermodynamique\n\n");

	//printf("Option fond	0 < fond < 255	:	couleur du fond de l'affichage\n");
	//printf("	Fond noir : 0, fond blanc : 255\n\n");

	printf("pause	5 < pause < 555	:	pause entre les affichages en ms\n");

	printf("duree	1 < duree < %d	:	nombre d'évolution du système entre les affichages\n", DUREE_MAX);
	printf("	flèches haut, bas, gauche, droite\n\n");

	printf("temperature	%f < temperature < %f	Température du thermostat\n", TEMPERATURE_MIN, TEMPERATURE_MAX);
	printf("	p, m : augmenter, diminuer la température\n\n");

	printf("gauche	%f < gauche < %f	Température à gauche \n", TEMPERATURE_MIN, TEMPERATURE_MAX);
	printf("	y, h : augmenter, diminuer la température\n\n");

	printf("droite	%f < droite < %f	Température à droite \n", TEMPERATURE_MIN, TEMPERATURE_MAX);
	printf("	u, j : augmenter, diminuer la température\n\n");

	printf("thermostat	-1 < thermostat < 3	Système isolé, système thermostaté, \n");
	printf("		0 : système isolé, 1 : thermostat symétrique \n");
	printf("		2 : thermostats droite-gauche. \n");
	printf("	o : Désactive le thermostat \n");
	printf("	i : Active le thermostat \n");
	printf("	k : Active les thermostats. \n\n");

	printf("trou	-1 < trou < %d, taille du trou	\n", (HAUTEUR-MARGE)/2+1);
	printf("	a, q : augmenter, diminuer la taille du trou\n\n");
	printf("	z, s : Trou max, trou implicite\n\n");

	printf("cloison	-3 < cloison < 3	Cloison si <> 0\n");
	printf("		0 : pas de cloison, 1 : cloison percée,\n");
	printf("		2 : cloison fermé, -1 : démon de maxwell.\n");
	printf("	w, x, c, v.\n");
	printf("\n");
	fprintf(stderr, "\nSortie de SiGP\n");
	exit(EXIT_FAILURE);
	return;
	}

////////////////////////////////////////////////////////////////////////////
