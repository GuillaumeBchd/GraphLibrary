/**
 * \file CParser.h
 * \brief Fichier header de la classe CParser.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.2
 * \date 16 mai 2019
 *
 * Fichier header de la classe CParser contenant des méthodes pour lire des fichiers txt sous un certain format.
 * Format de fichier compatible :
 * ##############################
 *
 * NBSommets=<Nombre_de_sommets_du_graphe>
 * NBArcs=<Nombre_d_arcs_du_graphe>
 * Sommets=[
 * Numero=<Numéro_sommet>
 * Numero=<Numéro_sommet>
 * ...
 * Numero=<Numéro_sommet>
 * ]
 * Arcs=[
 * Debut=<Sommet_départ_arc>,Fin=<Sommet_arrivé_arc>
 * Debut=<Sommet_départ_arc>,Fin=<Sommet_arrivé_arc>
 * ...
 * Debut=<Sommet_départ_arc>,Fin=<Sommet_arrivé_arc>
 * ]
 *
 */

#ifndef CParser_h
#define CParser_h

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "CException.h"

class CParser {

public:

    /**
     * \fn static int CParser::PARLectureMot(std::ifstream & fichier, char * pcMot)
     * \brief Fonction necessaire au bon fonctionnement du constructeur de CGraphe qui prend parametre un chemin de fichier : Lecture du mot suivant du ifstream & fichier passee en parametre
     *
     * \param fichier ifstream & : fichier ouvert (au moins en mode lecture),
     * \param pcMot char * : chaine de caracteres ou sera stocke
     * \return 0=mot-cle, 1=endOfFile (fichier.oef()) et 5=valeur.
     */
	static int PARLectureMot(std::ifstream& fichier, char * pcMot);

    /**
     * \fn static int CParser::PARStringCompare(char * pcString1, const char * pcString2)
     * \brief Fonction necessaire au bon fonctionnement du constructeur de CGraphe qui prend parametre un chemin de fichier : On compare si deux chaines de caracteres sont identiques.
     *
     * \param pcString1 char * : Premiere chaine a comparer.
     * \param pcString2 const char * Deuxieme chaine (constante) a comparer.
     * \return 0=Les chaines sont differentes et 1=Les chaines sont identiques.
     */
	static int PARStringCompare(char *pcString1, const char * pcString2);
	 
    /**
     * \fn static int CParser::PARGetCodeMotCle(char * pcString)
     * \brief Fonction necessaire au bon fonctionnement du constructeur de CGraphe qui prend parametre un chemin de fichier : On recupere le numero d'un mot-cle.
     *
     * \param pcString char * : Mot-cle dont on desire recuperer le code.
     * \return -1=Mot-cle inconnu, sinon code correspondant a la position dans pcMotsCles.
     */
	static int PARGetCodeMotCle(char *pcString);
};

#endif /* CParser_h */
