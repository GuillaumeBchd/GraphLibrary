/**
 * \file CParser.cpp
 * \brief Fichier de mŽthodes de la classe CParser.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.2
 * \date 16 mai 2019
 *
 */

#include "CParser.h"

const char *pcMotsCles[] = { "NBSommets", "NBArcs", "Sommets", "Arcs", "Numero", "Debut", "Fin", "[", "]" };

/**
 * \fn static int CParser::PARLectureMot(std::ifstream & fichier, char * pcMot)
 * \brief Fonction necessaire au bon fonctionnement du constructeur de CGraphe qui prend parametre un chemin de fichier : Lecture du mot suivant du ifstream & fichier passee en parametre
 *
 * \param fichier ifstream & : fichier ouvert (au moins en mode lecture),
 * \param pcMot char * : chaine de caracteres ou sera stocke
 * \return 0=mot-cle, 1=endOfFile (fichier.oef()) et 5=valeur.
 */
int CParser::PARLectureMot(std::ifstream & fichier, char * pcMot)
{
	char cMyChar;
	unsigned int uiIndice = 0;

	//Tant que l'on a pas atteint la fin du fichier, on continue le programme :
	while (!fichier.eof()) {
		fichier.get(cMyChar);
		//Si on lit un caractere qui démarque la séparation d'un mot, arrete de remplir pcMot et on avance jusqu'au prochain mot
		if (cMyChar == ' ' || cMyChar == '\n' || cMyChar == '=') {
			while ((cMyChar == ' ' || cMyChar == '\n' || cMyChar == '=') && !fichier.eof()) {
				if (cMyChar == '=') {
					pcMot[uiIndice] = '\0';
					return 5;
				}
				fichier.get(cMyChar);
			}
			pcMot[uiIndice] = '\0';
			if (uiIndice > 0) {
				fichier.unget();
				return 0;
			}
			uiIndice = 0;
		}
		//Dernière ligne du fichier
		if (fichier.eof() || fichier.fail()) {
			pcMot[uiIndice] = '\0';
			return 0;
		}
		pcMot[uiIndice] = cMyChar;
		uiIndice++;
	}
	pcMot[uiIndice] = '\0';
	if (uiIndice > 0) {
		fichier.unget();
		return 0;
	}

	return 0;
}

/**
 * \fn static int CParser::PARStringCompare(char * pcString1, const char * pcString2)
 * \brief Fonction necessaire au bon fonctionnement du constructeur de CGraphe qui prend parametre un chemin de fichier : On compare si deux chaines de caracteres sont identiques.
 *
 * \param pcString1 char * : Premiere chaine a comparer.
 * \param pcString2 const char * Deuxieme chaine (constante) a comparer.
 * \return 0=Les chaines sont differentes et 1=Les chaines sont identiques.
 */
int CParser::PARStringCompare(char * pcString1, const char * pcString2)
{
	char *pcPointeur1 = pcString1;
	const char *pcPointeur2 = pcString2;
	while (*pcPointeur1 == *pcPointeur2) {
		if (*pcPointeur1 == '\0' && *pcPointeur2 == '\0') {
			return 1;
		}
		pcPointeur1++;
		pcPointeur2++;
	}
	return 0;
}

/**
 * \fn static int CParser::PARGetCodeMotCle(char * pcString)
 * \brief Fonction necessaire au bon fonctionnement du constructeur de CGraphe qui prend parametre un chemin de fichier : On recupere le numero d'un mot-cle.
 *
 * \param pcString char * : Mot-cle dont on desire recuperer le code.
 * \return -1=Mot-cle inconnu, sinon code correspondant a la position dans pcMotsCles.
 */
int CParser::PARGetCodeMotCle(char * pcString)
{
	int iIndice;

	//On parcours tout le tableau pcMotsCles
	for (iIndice = 0; iIndice < sizeof(pcMotsCles) / sizeof(char*); iIndice++) {
		if (PARStringCompare(pcString, pcMotsCles[iIndice])) {
			return iIndice;
		}
	}

	return -1;
}
