
# SiGP
Simulateur de thermodynamique statistique

SiGP est un programme écrit en C et utilisant la librairie graphique SDL 1.2.


INSTALLATION

Pour installer ce programme sur votre ordinateur, vous devez avoir
installé la librairie graphique SDL ainsi que les outils permettant
la compilation :
Par exemple, avec une distribution basée sur debian, dans un terminal avec les
droits de l'administrateur :

	# apt-get install gcc make libsdl1.2-dev

Placez-vous dans le répertoire des sources, effectuez la compilation,

	$ make

Lancer l'exécutable créé :

	$ ./SiGP

Lancer l'exécutable avec d'éventuelles options :

	$ ./SiGP cloison 0 thermostat 2


Il permet de simuler une détente de Joule ainsi que des transferts thermique et d'en donner une représentation graphique.

La touche F1 réinitialise le système, la touche F5 affiche les paramètres énergétiques.

Les touche F9, F10, F11 et F12 changent la vitesse de la simulation.

La touche entrée change le mode ( avec ou sans attente d'évènement ) de la simulation.

CLAVIER

Activation du thermostat :
	o : système isolé.
	i : système thermostaté symétrique
	k : système thermostaté gauche-droite

Réglage du thermostat :
		p, m : Température du thermostat uniforme
		u, j : Température de la paroi droite
		y, h : Température de la paroi gauche

Paroi :		w : supprime la cloison
		x : cloison fermée
		c : cloison percée
		v : démon de Maxwell

Taille du trou :
		a, q : augmente, diminue
		z, s : Taille max, min

OPTION DE LA LIGNE DE COMMANDE


pause :		Temps de pause en ms entre les affichages.

duree :		Nombre d'évolution du système entre les affichages.


temperature :	Température initiale.

gauche :	Température thermostat gauche.

droite :	Température thermostat droit.


thermostat :	Activation du thermostat, 0 : système isolé, 1 : uniforme, 2 : dissymétrie

cloison :	Activation cloison centrale.
0 : Pas de cloison, 
1 : Cloison fermée, 
2 : Cloison percée, 
-1 : Cloison percée et démon de maxwell, 
-2 : Cloison et démon de maxwell.


aide :		Affiche l'aide.

help :		Affiche l'aide.



LICENCE

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

