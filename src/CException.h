/**
 * \file CException.h
 * \brief Fichier header de la classe CException.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.1
 * \date 16 mai 2019
 *
 * Fichier header contenant la classe CException contenant les attributs et méthodes pour initialiser des exceptions.
 * Toutes les exceptions de cette librairie seront des objets de cette classe.
 *
 */

#ifndef CException_h
#define CException_h

#include <stdio.h>

class CException {
    
	//Attributs
private:
	unsigned int uiEXCErreur;

	//Méthodes
public:
	CException(unsigned int uiErreur) {
		uiEXCErreur = uiErreur;
	}
	unsigned int EXCLireErreur() {
		return uiEXCErreur;
	}
	void EXCModifierErreur(unsigned int uiErreur) {
		uiEXCErreur = uiErreur;
	}
};

#endif /* CException_h */
