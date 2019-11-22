/**
 * \file CGraphe.h
 * \brief Fichier header de la classe CGraphe.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.1
 * \date 16 mai 2019
 *
 * Fichier header de la classe CGraphe contenant les attributs et méthodes pour initialiser des graphes composés de CSommets et de CArcs.
 *
 */

#ifndef CGraphe_h
#define CGraphe_h

#include <iostream> 
#include "CParser.h"
#include "CSommet.h"
#include "CException.h"

//Code d'erreur en 300 pour CGraphe
#define EXC_MallocError 1
#define EXC_NonCoherentGraph 300
#define EXC_IdAlreadyTaken 301
#define EXC_SommetManquant 302
#define EXC_OuvertureFichier 303
#define EXC_UnexpectedSymbol 304
#define EXC_UnexpectedKeyWord 305
#define EXC_InvalidGraphParameters 306
#define EXC_DoubleDefinitionNumeroSommet 307
#define EXC_NegativeNumber 308
#define EXC_NumeroSommetInconnu 309

class CGraphe {
    
    //Attributs
private:
    unsigned int uiGRATailleSommet;	 // Taille tableau malloc
    unsigned int uiGRANbSommet;		 // Nombre de sommet dans le tableau
    CSommet ** ppSOMGRASommet;		 // Tableau de sommet
    unsigned int uiGRAMaxId;		 // Permet de gérer les créations sans id de Sommet.
    
    // Constructeurs/Destructeurs
public:
    
    /**
     * \fn CGraphe::CGraphe()
     * \brief Constructeur par défaut de CGraphe
     *
     */
    CGraphe();
    
    /**
     * \fn CGraphe::CGraphe(CGraphe & GRAGraphe)
     * \brief Constructeur de recopie de CGraphe
     *
     * \param GRAGraphe CGraphe (en lvalue) que l'on souhaite recopié
     *
     */
    CGraphe(CGraphe & GRAGraphe);
    
    /**
     * \fn CGraphe::CGraphe(CGraphe && GRAGraphe)
     * \brief Constructeur de recopie de CGraphe
     *
     * \param GRAGraphe CGraphe (en rvalue) que l'on souhaite recopié
     *
     */
    CGraphe(CGraphe && GRAGraphe);
    
    /**
     * \fn CGraphe::CGraphe(char * pcAdresseFichier)
     * \brief Constructeur de confort de CGraphe
     *
     * \param pcAdresseFichier char * qui est un chemin d'un fichier.
     *
     * Cette méthode appelle les fonctions du CParser pour crée un CGraphe à partir du fichier donnée en paramètre.
     *
     */
	CGraphe(char * pcAdresseFichier);
    
    /**
     * \fn CGraphe::~CGraphe()
     * \brief Destructeur de CGraphe
     *
     */
    ~CGraphe();
    
    // Methodes
private :
    
    /**
     * \fn void CGraphe::GRAInitTab()
     * \brief Méthode privée qui permet d'initialiser le tableau de CSommet.
     *
     */
    void GRAInitTab();
    
    /**
     * \fn void CGraphe::GRAReallocTab()
     * \brief Méthode privée qui permet de realloc le tableau de CSommet à la bonne taille.
     *
     */
    void GRAReallocTab();
    
    /**
     * \fn void CGraphe::GRACheckIdMax()
     * \brief Méthode privée qui permet de vérifier si l'idMax est toujours le même en parcourant tout le CSommets du tableau.
     *
     */
	void GRACheckIdMax();
    
public:
    
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
    CGraphe operator=(CGraphe & GRAGraphe);
    
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
    CGraphe operator=(CGraphe && GRAGraphe);
    
    /**
     * \fn void CGraphe::GRAAjouterSommet()
     * \brief Méthode qui permet d'ajouter un Sommet à notre graphe, l'id de celui-ci est généré automatiquement.
     *
     */
    void GRAAjouterSommet();
    
    /**
     * \fn void CGraphe::GRAAjouterSommet(unsigned int uiNumero)
     * \brief Méthode qui permet d'ajouter un Sommet à notre graphe, l'id de celui-ci est donnée en parametre.
     *
     * \param uiNumero unsigned int qui spécifie l'identifiant que l'on souhaite attribué à notre CSommet.
     *
     * \warning La méthode retourne une exception si l'identifiant passé en paramètre est déjà pris.
     *
     */
    void GRAAjouterSommet(unsigned int uiNumero);
    
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
    void GRAModifierSommet(unsigned int uiIdSommet, unsigned int uiNumero);
    
    /**
     * \fn void CGraphe::GRASupprimerSommet(unsigned int uiIdSommet)
     * \brief Méthode qui permet de supprimer un CSommet de notre graphe.
     *
     * \param uiIdSommet unsigned int qui spécifie l'id du CSommet que l'on souhaite supprimer
     *
     */
    void GRASupprimerSommet(unsigned int uiIdSommet);
    
    /**
     * \fn void CGraphe::GRAAjouterArc(unsigned int uiNumDepart, unsigned int uiNumArrivee)
     * \brief Méthode qui permet d'ajouter un arc composé de deux CArc dans notre graphe.
     *
     * \param uiNumDepart unsigned int qui spécifie l'id du CSommet de départ de notre Arc
     * \param uiNumArrivee unsigned int qui spécifie l'id du CSommet d'arrivee de notre Arc
     *
     */
    void GRAAjouterArc(unsigned int uiNumDepart, unsigned int uiNumArrivee);
    
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
	void GRAModifierArc(unsigned int uiNumDepart, unsigned int uiNumArrivee, unsigned int uiNewNumDepart, unsigned int uiNewNumArrivee);
    
    /**
     * \fn void CGraphe::GRASupprimerArc(unsigned int uiNumDepart, unsigned int uiNumArrivee)
     * \brief Méthode qui permet de supprimer un arc existant entre deux CSommets.
     *
     * \param uiNumDepart unsigned int qui spécifie l'id du CSommet de départ de notre Arc
     * \param uiNumArrivee unsigned int qui spécifie l'id du CSommet d'arrivee de notre Arc
     *
     */
    void GRASupprimerArc(unsigned int uiNumDepart, unsigned int uiNumArrivee);

    /**
     * \fn void CGraphe::GRAAfficherGraphe()
     * \brief Méthode qui permet d'afficher un CGraphe dans la console.
     *
     * Les CSommets sont affichés un à un et pour chacun est affiché leurs listes de CArcs partants et arrivants.
     *
     */
    void GRAAfficherGraphe();
    
    /**
     * \fn CSommet * CGraphe::GRAGetSommet(unsigned int uiIndice)
     * \brief Accesseur en lecture sur un CSommet* de notre graphe
     *
     * \param uiIndice unsigned int qui spécifie la position du CSommet* que l'on veut retourner.
     *
     * \return CSommet* en position uiIndice
     *
     */
    CSommet * GRAGetSommet(unsigned int uiIndice);

    /**
     * \fn unsigned int CGraphe::GRAGetNbSommets()
     * \brief Accesseur en lecture sur un le nombre de CSommet de notre graphe
     *
     * \return unsigned int qui est le nombre de CSommet de notre graphe
     *
     */
	unsigned int GRAGetNbSommets() { return uiGRANbSommet; }
};

#endif /* CGraphe_h */
