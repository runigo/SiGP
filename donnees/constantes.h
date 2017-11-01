
/*
Copyright novembre 2017, Stephan Runigo
runigo@free.fr
SiGP 1.3.4  simulateur de gaz parfait
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

#ifndef _CONSTANTES_
#define _CONSTANTES_

//#include "unistd.h"

#include <assert.h>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define ALEA 77 // Taille du tableau de nombre aléatoire

#define NOMBRE 349 // Nombre de particules
#define TAILLE 5 // Taille des particules
//#define IMPACT 1 // Influence des chocs avec les parois

#define PI 3.14159265359
#define DEUXPI 6.28318530718

#define LARGEUR 1090 // Largeur de la fenêtre
#define HAUTEUR 395 // Hauteur de la fenêtre
#define MARGE 49 // Marge fenêtre-montage

#define DEMItROU 7 // Trou dans la cloison, sur 2

#define DUREE_MAX 99 // Nombre d'itération du système par affichage
#define TEMPERATURE_MAX 19666.1 // Température maximale
#define TEMPERATURE_MIN 0.0000003 // Température minimale

#define ENERGIE_SECURITE 777666555444333222111 // Énergie à ne pas dépasser

#endif
