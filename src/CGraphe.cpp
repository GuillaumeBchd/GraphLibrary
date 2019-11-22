/**
 * \file CGraphe.cpp
 * \brief Fichier de méthodes de la classe CGraphe.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.1
 * \date 16 mai 2019
 *
 */

#include "CGraphe.h"

/***     Constructeurs & Destructeur      ***/

/**
 * \fn CGraphe::CGraphe()
 * \brief Constructeur par défaut de CGraphe
 *
 */
CGraphe::CGraphe() : uiGRAMaxId(0), uiGRATailleSommet(0), uiGRANbSommet(0) {
	ppSOMGRASommet = NULL;
}

/**
 * \fn CGraphe::CGraphe(CGraphe & GRAGraphe)
 * \brief Constructeur de recopie de CGraphe
 *
 * \param GRAGraphe CGraphe (en lvalue) que l'on souhaite recopié
 *
 */
CGraphe::CGraphe(CGraphe & GRAGraphe) {
	unsigned int uiIterateur;

	uiGRATailleSommet = GRAGraphe.uiGRATailleSommet;
	uiGRANbSommet = GRAGraphe.uiGRANbSommet;
	uiGRAMaxId = GRAGraphe.uiGRAMaxId;

	//Verif graphe cohérent
	if (uiGRANbSommet > uiGRATailleSommet || uiGRANbSommet > uiGRAMaxId) {
		CException EXCError(EXC_NonCoherentGraph);
		throw EXCError;
	}

	if (uiGRATailleSommet != 0) {
		ppSOMGRASommet = (CSommet**)malloc(sizeof(CSommet*)*uiGRATailleSommet);
		if (ppSOMGRASommet == NULL) {
			CException EXCError(EXC_MallocError);
			throw EXCError;
		}

		for (uiIterateur = 0; uiIterateur < uiGRANbSommet; uiIterateur++) {
			ppSOMGRASommet[uiIterateur] = new CSommet(*GRAGraphe.ppSOMGRASommet[uiIterateur]);
		}
	}
}

/**
 * \fn CGraphe::CGraphe(CGraphe && GRAGraphe)
 * \brief Constructeur de recopie de CGraphe
 *
 * \param GRAGraphe CGraphe (en rvalue) que l'on souhaite recopié
 *
 */
CGraphe::CGraphe(CGraphe && GRAGraphe) {
    unsigned int uiIterateur;
    
    uiGRATailleSommet = GRAGraphe.uiGRATailleSommet;
    uiGRANbSommet = GRAGraphe.uiGRANbSommet;
    uiGRAMaxId = GRAGraphe.uiGRAMaxId;
    
    //Verif graphe cohérent
    if (uiGRANbSommet > uiGRATailleSommet || uiGRANbSommet > uiGRAMaxId) {
        CException EXCError(EXC_NonCoherentGraph);
        throw EXCError;
    }
    
    if (uiGRATailleSommet != 0) {
        ppSOMGRASommet = (CSommet**)malloc(sizeof(CSommet*)*uiGRATailleSommet);
        if (ppSOMGRASommet == NULL) {
            CException EXCError(EXC_MallocError);
            throw EXCError;
        }
        
        for (uiIterateur = 0; uiIterateur < uiGRANbSommet; uiIterateur++) {
            ppSOMGRASommet[uiIterateur] = new CSommet(*GRAGraphe.ppSOMGRASommet[uiIterateur]);
        }
    }
}

/**
 * \fn CGraphe::CGraphe(char * pcAdresseFichier)
 * \brief Constructeur de confort de CGraphe
 *
 * \param pcAdresseFichier char * qui est un chemin d'un fichier.
 *
 * Cette méthode appelle les fonctions du CParser pour crée un CGraphe à partir du fichier donnée en paramètre
 *
 */
CGraphe::CGraphe(char * pcAdresseFichier)
{
	//Définition de tous les indices de boucles :
	unsigned int uiCompteur;

	std::ifstream fichier(pcAdresseFichier, std::ios::in);  // ouvrir le fichier en mode lecture

	if (fichier) { // Si on a pu ouvrir
		char pcMotCle[256];
		int iCode = 0;

		// Variables necessaires a la creation du graphe :
		unsigned int uiNbSommets = 0;
		unsigned int uiNbArcs = 0;

		unsigned int uiNbSommetsTrouves = 0;
		unsigned int uiNbArcsTrouves = 0;

		unsigned int uiTabSommetsSize = 2;
		unsigned int uiTabArcsSize = 2;

		unsigned int *pTableauNumSommets = (unsigned int*)malloc((uiTabSommetsSize) * sizeof(unsigned int));
		unsigned int *pTableauNumDebutArc = (unsigned int*)malloc((uiTabArcsSize) * sizeof(unsigned int));
		unsigned int *pTableauNumFinArc = (unsigned int*)malloc((uiTabArcsSize) * sizeof(unsigned int));

		while (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1) && !fichier.eof() && !fichier.fail()) {

			if (iCode == 5) { //On doit forcement commencer par lire un mot-cle, sinon exception

				if ((iCode = CParser::PARGetCodeMotCle(pcMotCle)) != -1) { //On verifie ensuite que le mot-cle est connu
					switch (iCode) {
					case 0: //NBSommets
						//On s'attend ici a lire une valeur pour NBSommets, sinon exception
						if (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1)) {
							uiNbSommets = std::atoi(pcMotCle);
							if (uiNbSommets == 0) {
								for (uiCompteur = 0; uiCompteur < strlen(pcMotCle); uiCompteur++) {
									if (pcMotCle[uiCompteur] != '0') {
										CException EXCError(EXC_UnexpectedSymbol);
										throw EXCError;
									}
								}
							}
						}
						break;

					case 1: //NBArcs
						//On s'attend ici a lire une valeur pour NBArcs, sinon exception
						if (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1)) {
							uiNbArcs = std::atoi(pcMotCle);
							if (uiNbArcs == 0) {
								for (uiCompteur = 0; uiCompteur < strlen(pcMotCle); uiCompteur++) {
									if (pcMotCle[uiCompteur] != '0') {
										CException EXCError(EXC_UnexpectedSymbol);
										throw EXCError;
									}
								}
							}
						}
						else {
							CException EXCError(EXC_UnexpectedSymbol);
							throw EXCError;
						}
						break;

					case 2: //Sommets
						//On s'attend a lire le '[' d'ouverture ici
						if (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1) && *pcMotCle == '[') {
							uiNbSommetsTrouves = 0;

							//On lit le mot suivant tant que l'on atteint pas le ']' de fermeture
							while (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1) && *pcMotCle != ']') {

								//On s'attend a lire le mot "Numero" ici
								if (CParser::PARGetCodeMotCle(pcMotCle) == 4) {

									//On s'attend à une valeur pour NumeroSommet ici
									if (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1)) {
										//Si le tableau des sommets n'est pas assez grand on l'agrandit
										if (uiTabSommetsSize == uiNbSommetsTrouves) {
											uiTabSommetsSize = uiTabSommetsSize * 2;
											pTableauNumSommets = (unsigned int *)realloc(pTableauNumSommets, (uiTabSommetsSize * 2 + 1) * sizeof(unsigned int));
										}

										int numeroTrouve = std::atoi(pcMotCle);
										if (numeroTrouve < 0) {
											CException EXCError(EXC_NegativeNumber);
											throw EXCError;
										}

										//On verifie que si le numero trouve est 0, c'est bien un 0 et pas un char
										if (numeroTrouve == 0) {
											for (uiCompteur = 0; uiCompteur < strlen(pcMotCle); uiCompteur++) {
												if (pcMotCle[uiCompteur] != '.' && pcMotCle[uiCompteur] != '0') {
													CException EXCError(EXC_UnexpectedSymbol);
													throw EXCError;
												}
											}
										}

										//On verifie que le numero trouve n'a pas ete definit avant
										for (uiCompteur = 0; uiCompteur < uiNbSommetsTrouves; uiCompteur++) {
											if (pTableauNumSommets[uiCompteur] == numeroTrouve) {
												CException EXCError(EXC_DoubleDefinitionNumeroSommet);
												throw EXCError;
											}
										}

										pTableauNumSommets[uiNbSommetsTrouves] = numeroTrouve;

										uiNbSommetsTrouves++;
									}
									else {
										CException EXCError(EXC_UnexpectedSymbol);
										throw EXCError;
									}
								}
								else {
									CException EXCError(EXC_UnexpectedKeyWord);
									throw EXCError;
								}
							}
						}
						else {
							CException EXCError(EXC_UnexpectedSymbol);
							throw EXCError;
						}
						break;

					case 3: //Arcs
						//On s'attend a lire le '[' d'ouverture ici
						if (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1) && *pcMotCle == '[') {
							uiNbArcsTrouves = 0;

							//On lit le mot suivant tant que l'on atteint pas le ']' de fermeture
							while (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1) && *pcMotCle != ']') {

								//On s'attend a lire le mot "Debut" ici
								if (CParser::PARGetCodeMotCle(pcMotCle) == 5) {

									//On s'attend à une valeur pour NumeroDebut ici
									if (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1)) {
										//Si le tableau des sommets n'est pas assez grand on l'agrandit
										if (uiTabArcsSize == uiNbArcsTrouves) {
											uiTabArcsSize = uiTabArcsSize * 2;
											pTableauNumFinArc = (unsigned int *)realloc(pTableauNumFinArc, (uiTabArcsSize * 2 + 1) * sizeof(unsigned int));
											pTableauNumDebutArc = (unsigned int *)realloc(pTableauNumDebutArc, (uiTabArcsSize * 2 + 1) * sizeof(unsigned int));
										}

										int numeroTrouve = std::atoi(pcMotCle);
										if (numeroTrouve < 0) {
											CException EXCError(EXC_NegativeNumber);
											throw EXCError;
										}

										//On verifie que si le numero trouve est 0, c'est bien un 0 et pas un char
										if (numeroTrouve == 0) {
											for (uiCompteur = 0; uiCompteur < strlen(pcMotCle); uiCompteur++) {
												if (pcMotCle[uiCompteur] != '.' && pcMotCle[uiCompteur] != '0') {
													CException EXCError(EXC_UnexpectedSymbol);
													throw EXCError;
												}
											}
										}

										pTableauNumDebutArc[uiNbArcsTrouves] = numeroTrouve;

									}
									else {
										CException EXCError(EXC_UnexpectedSymbol);
										throw EXCError;
									}
								}
								else {
									CException EXCError(EXC_UnexpectedKeyWord);
									throw EXCError;
								}

								if ((iCode = CParser::PARLectureMot(fichier, pcMotCle)) == 1) {
									CException EXCError(EXC_UnexpectedKeyWord);
									throw EXCError;
								}

								//Une fois que l'on a lu "Debut", on s'attend à lire "Fin"
								if (CParser::PARGetCodeMotCle(pcMotCle) == 6) {

									//On s'attend à une valeur pour NumeroFin ici
									if (((iCode = CParser::PARLectureMot(fichier, pcMotCle)) != 1)) {

										//Inutile d'aggrandir le tableau de numeroFin ici, c'est déjà fait pour numeroDebut

										int numeroTrouve = std::atoi(pcMotCle);
										if (numeroTrouve < 0) {
											CException EXCError(EXC_NegativeNumber);
											throw EXCError;
										}

										//On verifie que si le numero trouve est 0, c'est bien un 0 et pas un char
										if (numeroTrouve == 0) {
											for (uiCompteur = 0; uiCompteur < strlen(pcMotCle); uiCompteur++) {
												if (pcMotCle[uiCompteur] != '.' && pcMotCle[uiCompteur] != '0') {
													CException EXCError(EXC_UnexpectedSymbol);
													throw EXCError;
												}
											}
										}

										pTableauNumFinArc[uiNbArcsTrouves] = numeroTrouve;

									}
									else {
										CException EXCError(EXC_UnexpectedSymbol);
										throw EXCError;
									}
								}
								else {
									CException EXCError(EXC_UnexpectedKeyWord);
									throw EXCError;
								}

								uiNbArcsTrouves++;
							}
						}
						else {
							CException EXCError(EXC_UnexpectedSymbol);
							throw EXCError;
						}
						break;

					default: //Cas possible pour [ et ] mal placés et si on rajoute des mots clés non gérés dans pcMotsCles
						CException EXCError(EXC_UnexpectedKeyWord);
						throw EXCError;
						break;
					}
				}
				else {
					CException EXCError(EXC_UnexpectedSymbol);
					throw EXCError;
				}
			}
			else {
				CException EXCError(EXC_UnexpectedSymbol);
				throw EXCError;
			}
		}
		fichier.close();

		//Si le nombre de valeurs trouvees est incoherentes, exception.
		if (uiNbSommets != uiNbSommetsTrouves || uiNbArcs != uiNbArcsTrouves) {
			CException EXCError(EXC_InvalidGraphParameters);
			throw EXCError;
		}

		uiGRATailleSommet = uiNbSommets;
		uiGRANbSommet = uiNbSommets;
		ppSOMGRASommet = (CSommet**)malloc(sizeof(CSommet*)*uiGRATailleSommet);
		uiGRAMaxId = 0;

		//Puis on parcourt notre tableau de numéros de sommets pour remplir notre nouveau graph en prenant soin de correctement définir le numéro maximum
		for (uiCompteur = 0; uiCompteur < uiNbSommets; uiCompteur++) {
			if (uiGRAMaxId < pTableauNumSommets[uiCompteur]) {
				uiGRAMaxId = pTableauNumSommets[uiCompteur];
			}
			ppSOMGRASommet[uiCompteur] = new CSommet(pTableauNumSommets[uiCompteur]);
		}

		//Et on ajoute tous les arcs
		for (uiCompteur = 0; uiCompteur < uiNbArcs; uiCompteur++) {
			GRAAjouterArc(pTableauNumDebutArc[uiCompteur], pTableauNumFinArc[uiCompteur]);
		}

	}
	else {
		CException EXCOuvertureFichier(EXC_OuvertureFichier);
		throw EXCOuvertureFichier;
	}
}

/**
 * \fn CGraphe::~CGraphe()
 * \brief Destructeur de CGraphe
 *
 */
CGraphe::~CGraphe() {
    unsigned int uiIterateurSommet;
    
	if (uiGRATailleSommet != 0) {
        //On delete les CSommets
        for(uiIterateurSommet = 0; uiIterateurSommet<uiGRANbSommet; uiIterateurSommet++){
            delete(ppSOMGRASommet[uiIterateurSommet]);
        }
		free(ppSOMGRASommet);
		ppSOMGRASommet = NULL;
	}
}

/***            Méthodes             ***/

/**
 * \fn CGraphe CGraphe::operator=(CGraphe &GRAGraphe)
 * \brief Surcharge de l'operateur= entre deux CGraphe
 *
 * \param GRAGraphe CGraphe (en lvalue) qui spécifie le CGraphe que l'on veut recopier
 *
 * \return CGraphe recopié
 *
 * Cette méthode désalloue et supprime les CSommets qui étaient présent dans les tableaux du CGraphe dans lequel on veut recopier le CGraphe passé en paramètre. De plus, les CSommets sont copié entièrement et non juste leurs adresses.
 *
 */
CGraphe CGraphe::operator=(CGraphe &GRAGraphe) {
	unsigned int uiIterateur;

	if (ppSOMGRASommet != NULL) {
        for(uiIterateur = 0; uiIterateur<uiGRANbSommet; uiIterateur++){
            delete(ppSOMGRASommet[uiIterateur]);
        }
		free(ppSOMGRASommet);
		ppSOMGRASommet = NULL;
	}

	uiGRATailleSommet = GRAGraphe.uiGRATailleSommet;
	uiGRANbSommet = GRAGraphe.uiGRANbSommet;
	uiGRAMaxId = GRAGraphe.uiGRAMaxId;

	//Verif graphe cohérent
	if (uiGRANbSommet > uiGRATailleSommet || uiGRANbSommet > uiGRAMaxId) {
		CException EXCError(EXC_NonCoherentGraph);
		throw EXCError;
	}

	if (uiGRATailleSommet != 0) {
		ppSOMGRASommet = (CSommet**)malloc(sizeof(CSommet*)*uiGRATailleSommet);
		if (ppSOMGRASommet == NULL) {
			CException EXCError(EXC_MallocError);
			throw EXCError;
		}

		for (uiIterateur = 0; uiIterateur < uiGRANbSommet; uiIterateur++) {
			ppSOMGRASommet[uiIterateur] = new CSommet(*GRAGraphe.ppSOMGRASommet[uiIterateur]);
		}
	}

	return *this;
}

/**
 * \fn CGraphe CGraphe::operator=(CGraphe &GRAGraphe)
 * \brief Surcharge de l'operateur= entre deux CGraphe
 *
 * \param GRAGraphe CGraphe (en rvalue) qui spécifie le CGraphe que l'on veut recopier
 *
 * \return CGraphe recopié
 *
 * Cette méthode désalloue et supprime les CSommets qui étaient présent dans les tableaux du CGraphe dans lequel on veut recopier le CGraphe passé en paramètre. De plus, les CSommets sont copié entièrement et non juste leurs adresses.
 *
 */
CGraphe CGraphe::operator=(CGraphe &&GRAGraphe) {
	unsigned int uiIterateur;

	if (ppSOMGRASommet != NULL) {
        for(uiIterateur = 0; uiIterateur<uiGRANbSommet; uiIterateur++){
            delete(ppSOMGRASommet[uiIterateur]);
        }
		free(ppSOMGRASommet);
		ppSOMGRASommet = NULL;
	}

	uiGRATailleSommet = GRAGraphe.uiGRATailleSommet;
	uiGRANbSommet = GRAGraphe.uiGRANbSommet;
	uiGRAMaxId = GRAGraphe.uiGRAMaxId;

	//Verif graphe cohérent
	if (uiGRANbSommet > uiGRATailleSommet || uiGRANbSommet > uiGRAMaxId) {
		CException EXCError(EXC_NonCoherentGraph);
		throw EXCError;
	}

	if (uiGRATailleSommet != 0) {
		ppSOMGRASommet = (CSommet**)malloc(sizeof(CSommet*)*uiGRATailleSommet);
		if (ppSOMGRASommet == NULL) {
			CException EXCError(EXC_MallocError);
			throw EXCError;
		}

		for (uiIterateur = 0; uiIterateur < uiGRANbSommet; uiIterateur++) {
			ppSOMGRASommet[uiIterateur] = new CSommet(*GRAGraphe.ppSOMGRASommet[uiIterateur]);
		}
	}

	return *this;
}

//Private

/**
 * \fn void CGraphe::GRAInitTab()
 * \brief Méthode privée qui permet d'initialiser le tableau de CSommet.
 *
 */
void CGraphe::GRAInitTab() {
	uiGRATailleSommet = 4;
	uiGRANbSommet = 0;
	ppSOMGRASommet = (CSommet**)malloc(sizeof(CSommet*)*uiGRATailleSommet);
	if (ppSOMGRASommet == NULL) {
		CException EXCError(EXC_MallocError);
		throw EXCError;
	}
}

/**
 * \fn void CGraphe::GRAReallocTab()
 * \brief Méthode privée qui permet de realloc le tableau de CSommet à la bonne taille.
 *
 */
void CGraphe::GRAReallocTab() {
	uiGRATailleSommet = uiGRATailleSommet * 2;
	ppSOMGRASommet = (CSommet**)realloc(ppSOMGRASommet, sizeof(CSommet*)*uiGRATailleSommet);
	if (ppSOMGRASommet == NULL) {
		CException EXCError(EXC_MallocError);
		throw EXCError;
	}
}

/**
 * \fn void CGraphe::GRACheckIdMax()
 * \brief Méthode privée qui permet de vérifier si l'idMax est toujours le même en parcourant tout le CSommets du tableau.
 *
 */
void CGraphe::GRACheckIdMax() {

	unsigned int uiIterateurSommet;
	unsigned int uiMaxId = 0;

	for (uiIterateurSommet = 0; uiIterateurSommet < uiGRANbSommet; uiIterateurSommet++) {
		if (uiMaxId < ppSOMGRASommet[uiIterateurSommet]->SOMGetNumeroSommet()) {
			uiMaxId = ppSOMGRASommet[uiIterateurSommet]->SOMGetNumeroSommet();
		}
	}

	uiGRAMaxId = uiMaxId;

}
//End private

/**
 * \fn void CGraphe::GRAAjouterSommet()
 * \brief Méthode qui permet d'ajouter un Sommet à notre graphe, l'id de celui-ci est généré automatiquement.
 *
 */
void CGraphe::GRAAjouterSommet() {
	//On gère les cas de base de malloc/realloc du tableau de sommet
	if (uiGRATailleSommet == 0) {
		GRAInitTab();
	}
	if (uiGRANbSommet == uiGRATailleSommet) {
		GRAReallocTab();
	}

	uiGRAMaxId++;
	ppSOMGRASommet[uiGRANbSommet] = new CSommet(uiGRAMaxId);
	uiGRANbSommet++;
}

/**
 * \fn void CGraphe::GRAAjouterSommet(unsigned int uiNumero)
 * \brief Méthode qui permet d'ajouter un Sommet à notre graphe, l'id de celui-ci est donnée en parametre.
 *
 * \param uiNumero unsigned int qui spécifie l'identifiant que l'on souhaite attribué à notre CSommet.
 *
 * \warning La méthode retourne une exception si l'identifiant passé en paramètre est déjà pris.
 *
 */
void CGraphe::GRAAjouterSommet(unsigned int uiNumero) {
	unsigned int uiIterateur;

	//On gère les cas de base de malloc/realloc du tableau de sommet
	if (uiGRATailleSommet == 0) {
		GRAInitTab();
	}
	if (uiGRANbSommet == uiGRATailleSommet) {
		GRAReallocTab();
	}

	//Si l'id est plus grand que notre maxId pas besoin de vérifier
	if (uiNumero > uiGRAMaxId) {
		uiGRAMaxId = uiNumero;
		ppSOMGRASommet[uiGRANbSommet] = new CSommet(uiGRAMaxId);
		uiGRANbSommet++;
	}
	else {
		//On vérifie que l'id est unique.
		for (uiIterateur = 0; uiIterateur < uiGRANbSommet; uiIterateur++) {
			if (ppSOMGRASommet[uiIterateur]->SOMGetNumeroSommet() == uiNumero) {
				CException EXCError(EXC_IdAlreadyTaken);
				throw EXCError;
			}
		}
		//On ajoute le sommet au tableau
		ppSOMGRASommet[uiGRANbSommet] = new CSommet(uiNumero);
		uiGRANbSommet++;
	}
}


/**
 * \fn void CGraphe::GRAModifierSommet(unsigned int uiIdSommet, unsigned int uiNumero)
 * \brief Méthode qui permet de modifier l'id d'un CSommet de notre graphe.
 *
 * \param uiIdSommet unsigned int qui spécifie l'id du CSommet que l'on souhaite modifié
 * \param uiNumero unsigned int qui spécifie l'identifiant que l'on souhaite attribué à notre CSommet.
 *
 * \warning Bonne fonction à utiliser pour modifier le numéro d'identification d'un sommet et non pas sommet.SOMSetNumeroSommet(...) pour conserver la cohérence du graphe.
 *
 */
void CGraphe::GRAModifierSommet(unsigned int uiIdSommet, unsigned int uiNumero) {
	int iSauvegardePosSommet = -1;
	unsigned int uiIterateurSommet;
	unsigned int uiIterateurArc;

	//On vérifie que le numéro n'est pas pris
	for (uiIterateurSommet = 0; uiIterateurSommet < uiGRANbSommet; uiIterateurSommet++) {
		if (ppSOMGRASommet[uiIterateurSommet]->SOMGetNumeroSommet() == uiNumero) {
			CException EXCError(EXC_IdAlreadyTaken);
			throw EXCError;
		}
		if (ppSOMGRASommet[uiIterateurSommet]->SOMGetNumeroSommet() == uiIdSommet) {
			iSauvegardePosSommet = uiIterateurSommet;
		}
	}
	//Normalement le numéro n'est pas pris
	if (uiNumero > uiGRAMaxId) {
		uiGRAMaxId = uiNumero;
	}

	if (iSauvegardePosSommet == -1) {
		CException EXCError(EXC_SommetManquant);
		throw EXCError;
	}

	GRAAjouterSommet(uiNumero);

	//On modifie les arcs partants de ce sommet
	for (uiIterateurArc = 0; uiIterateurArc < ppSOMGRASommet[iSauvegardePosSommet]->SOMGetNbArcsPartants(); uiIterateurArc++) {
		unsigned int uiArrivee = ppSOMGRASommet[iSauvegardePosSommet]->SOMGetNumSommetArcPartant(uiIterateurArc);
		GRAAjouterArc(uiNumero, uiArrivee);
	}

	//On modifie les arcs arrivants de ce sommet
	for (uiIterateurArc = 0; uiIterateurArc < ppSOMGRASommet[iSauvegardePosSommet]->SOMGetNbArcsArrivants(); uiIterateurArc++) {
		unsigned int uiDepart = ppSOMGRASommet[iSauvegardePosSommet]->SOMGetNumSommetArcArrivant(uiIterateurArc);
		GRAAjouterArc(uiDepart, uiNumero);
	}

	GRASupprimerSommet(uiIdSommet);

	//On check le nouveau uiGRAMaxId si c'était le sien
	if (uiIdSommet == uiGRAMaxId) {
		GRACheckIdMax();
	}

}

/**
 * \fn void CGraphe::GRASupprimerSommet(unsigned int uiIdSommet)
 * \brief Méthode qui permet de supprimer un CSommet de notre graphe.
 *
 * \param uiIdSommet unsigned int qui spécifie l'id du CSommet que l'on souhaite supprimer
 *
 */
void CGraphe::GRASupprimerSommet(unsigned int uiIdSommet) {
	if (ppSOMGRASommet == NULL) {
		CException EXCError(EXC_EmptyTab);
		throw EXCError;
	}

	unsigned int uiIterateurSommet = 0;
	unsigned int uiIterateurArc;

	while (uiIterateurSommet < uiGRANbSommet && ppSOMGRASommet[uiIterateurSommet]->SOMGetNumeroSommet() != uiIdSommet) {
		uiIterateurSommet++;
		//On cherche le sommet à supprimer.
	}

	if (uiIterateurSommet == uiGRANbSommet) {
		CException EXCError(EXC_SommetManquant);
		throw EXCError;
	}
	
	//On supprime les arcs partants de ce sommet
	for (uiIterateurArc = 0; uiIterateurArc < ppSOMGRASommet[uiIterateurSommet]->SOMGetNbArcsPartants(); uiIterateurArc++) {
		unsigned int uiDepart = ppSOMGRASommet[uiIterateurSommet]->SOMGetNumeroSommet();
		unsigned int uiArrivee = ppSOMGRASommet[uiIterateurSommet]->SOMGetNumSommetArcPartant(uiIterateurArc);
		GRASupprimerArc(uiDepart, uiArrivee);
	}

	//On supprime les arcs arrivants de ce sommet
	for (uiIterateurArc = 0; uiIterateurArc < ppSOMGRASommet[uiIterateurSommet]->SOMGetNbArcsArrivants(); uiIterateurArc++) {
		unsigned int uiDepart = ppSOMGRASommet[uiIterateurSommet]->SOMGetNumSommetArcArrivant(uiIterateurArc);
		unsigned int uiArrivee = ppSOMGRASommet[uiIterateurSommet]->SOMGetNumeroSommet();
		GRASupprimerArc(uiDepart, uiArrivee);
	}

	delete(ppSOMGRASommet[uiIterateurSommet]);

	while (uiIterateurSommet < uiGRANbSommet - 1) {
		ppSOMGRASommet[uiIterateurSommet] = ppSOMGRASommet[uiIterateurSommet + 1];
		uiIterateurSommet++;
	}
	ppSOMGRASommet[uiIterateurSommet] = NULL;
	uiGRANbSommet--;

	//On check le nouveau uiGRAMaxId si c'était le sien
	if (uiIdSommet == uiGRAMaxId) {
		GRACheckIdMax();
	}

}

/**
 * \fn void CGraphe::GRAAjouterArc(unsigned int uiNumDepart, unsigned int uiNumArrivee)
 * \brief Méthode qui permet d'ajouter un arc composé de deux CArc dans notre graphe.
 *
 * \param uiNumDepart unsigned int qui spécifie l'id du CSommet de départ de notre Arc
 * \param uiNumArrivee unsigned int qui spécifie l'id du CSommet d'arrivee de notre Arc
 *
 */
void CGraphe::GRAAjouterArc(unsigned int uiNumDepart, unsigned int uiNumArrivee) {
	if (uiGRATailleSommet == 0) {
		CException EXCError(EXC_EmptyTab);
		throw EXCError;
	}

	//On parcourt le tableau et on sauvegarde la position des sommets départ et arrivée
	unsigned int uiIterateur = 0;   //Iterateur pour parcourir le tableau
	int iPosDepart = -1;   //Sauvegarde de la position du sommet Depart
	int iPosArrive = -1;   //Sauvegarde de la position du sommet Arrivee
	while (uiIterateur < uiGRANbSommet && (iPosArrive == -1 || iPosDepart == -1)) {
		if (ppSOMGRASommet[uiIterateur]->SOMGetNumeroSommet() == uiNumDepart) {
			iPosDepart = uiIterateur;
		}
		if (ppSOMGRASommet[uiIterateur]->SOMGetNumeroSommet() == uiNumArrivee) {
			iPosArrive = uiIterateur;
		}
		uiIterateur++;
	}

	//Erreur si l'on a pas trouvé les sommets
	if (iPosArrive == -1 || iPosDepart == -1) {
		CException EXCError(EXC_SommetManquant);
		throw EXCError;
	}

	//On ajoute les CArc aux bons tableaux des sommets
	ppSOMGRASommet[iPosDepart]->SOMAjouterArcPartant(uiNumArrivee);
	ppSOMGRASommet[iPosArrive]->SOMAjouterArcArrivant(uiNumDepart);
}

/**
 * \fn void CGraphe::GRAModifierArc(unsigned int uiNumDepart, unsigned int uiNumArrivee, unsigned int uiNewNumDepart, unsigned int uiNewNumArrivee)
 * \brief Méthode qui permet de modifier un arc existant entre deux CSommets pour qu'il soit entre deux autres CSommets
 *
 * \param uiNumDepart unsigned int qui spécifie l'id du CSommet d'origine de départ de notre Arc
 * \param uiNumArrivee unsigned int qui spécifie l'id du CSommet d'origine d'arrivee de notre Arc
 * \param uiNewNumDepart unsigned int qui spécifie l'id du nouveau CSommet de départ de notre Arc
 * \param uiNewNumArrivee unsigned int qui spécifie l'id du nouveau CSommet d'arrivee de notre Arc
 *
 */
void CGraphe::GRAModifierArc(unsigned int uiNumDepart, unsigned int uiNumArrivee, unsigned int uiNewNumDepart, unsigned int uiNewNumArrivee) {

	GRASupprimerArc(uiNumDepart, uiNumArrivee);
	GRAAjouterArc(uiNewNumDepart, uiNewNumArrivee);

}

/**
 * \fn void CGraphe::GRASupprimerArc(unsigned int uiNumDepart, unsigned int uiNumArrivee)
 * \brief Méthode qui permet de supprimer un arc existant entre deux CSommets.
 *
 * \param uiNumDepart unsigned int qui spécifie l'id du CSommet de départ de notre Arc
 * \param uiNumArrivee unsigned int qui spécifie l'id du CSommet d'arrivee de notre Arc
 *
 */
void CGraphe::GRASupprimerArc(unsigned int uiNumDepart, unsigned int uiNumArrivee) {
	int iDepartPos = -1;
	int iArriveePos = -1;
	unsigned int uiIterateur;

	//On parcourt le tableau pour vérifier que les deux sommets sont bien présents
	for (uiIterateur = 0; uiIterateur < uiGRANbSommet; uiIterateur++) {
		if (ppSOMGRASommet[uiIterateur]->SOMGetNumeroSommet() == uiNumDepart) {
			iDepartPos = uiIterateur;
		}
		if (ppSOMGRASommet[uiIterateur]->SOMGetNumeroSommet() == uiNumArrivee) {
			iArriveePos = uiIterateur;
		}
	}

	//S'ils ne sont pas présent on lance une CException
	if (iDepartPos == -1 || iArriveePos == -1) {
		CException EXCError(EXC_SommetManquant);
		throw EXCError;
	}

	//On supprime les deux CArcs correspondants
	ppSOMGRASommet[iDepartPos]->SOMSupprimerArcPartant(uiNumArrivee);
	ppSOMGRASommet[iArriveePos]->SOMSupprimerArcArrivant(uiNumDepart);
}



/**
 * \fn void CGraphe::GRAAfficherGraphe()
 * \brief Méthode qui permet d'afficher un CGraphe dans la console.
 * 
 * Les CSommets sont affichés un à un et pour chacun est affiché leurs listes de CArcs partants et arrivants.
 *
 */
void CGraphe::GRAAfficherGraphe() {
	unsigned int uiIndiceSommet;
	unsigned int uiIndiceArc;
	if (uiGRANbSommet > 0) {
		std::cout << "Identificateur de sommet le plus haut = " << uiGRAMaxId << std::endl;
		for (uiIndiceSommet = 0; uiIndiceSommet < uiGRANbSommet; uiIndiceSommet++) {
			std::cout << "Liste des arcs du sommet " << ppSOMGRASommet[uiIndiceSommet]->SOMGetNumeroSommet() << " : " << std::endl;
			if (ppSOMGRASommet[uiIndiceSommet]->SOMGetNbArcsPartants() > 0) {
				std::cout << "Arcs partants : " << std::endl;
			}
			for (uiIndiceArc = 0; uiIndiceArc < ppSOMGRASommet[uiIndiceSommet]->SOMGetNbArcsPartants(); uiIndiceArc++) {
				std::cout
					<< "arc ("
					<< ppSOMGRASommet[uiIndiceSommet]->SOMGetNumeroSommet()
					<< ", "
					<< ppSOMGRASommet[uiIndiceSommet]->SOMGetNumSommetArcPartant(uiIndiceArc)
					<< ");"
					<< std::endl;
			}
			if (ppSOMGRASommet[uiIndiceSommet]->SOMGetNbArcsArrivants() > 0) {
				std::cout << "Arcs arrivants : " << std::endl;
			}
			for (uiIndiceArc = 0; uiIndiceArc < ppSOMGRASommet[uiIndiceSommet]->SOMGetNbArcsArrivants(); uiIndiceArc++) {
				std::cout
					<< "arc ("
					<< ppSOMGRASommet[uiIndiceSommet]->SOMGetNumSommetArcArrivant(uiIndiceArc)
					<< ", "
					<< ppSOMGRASommet[uiIndiceSommet]->SOMGetNumeroSommet()
					<< ");"
					<< std::endl;
			}
			std::cout << std::endl;
		}
	}
}

/**
 * \fn CSommet * CGraphe::GRAGetSommet(unsigned int uiIndice)
 * \brief Accesseur en lecture sur un CSommet* de notre graphe
 *
 * \param uiIndice unsigned int qui spécifie la position du CSommet* que l'on veut retourner.
 *
 * \return CSommet* en position uiIndice
 *
 */
CSommet * CGraphe::GRAGetSommet(unsigned int uiIndice)
{
    if(uiIndice >= uiGRANbSommet){
        CException EXCError(EXC_InvalidGraphParameters);
        throw EXCError;
    }
	return ppSOMGRASommet[uiIndice];
}
