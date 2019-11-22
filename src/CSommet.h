/**
 * \file CSommet.h
 * \brief Fichier header de la classe CGraphe.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.1
 * \date 16 mai 2019
 *
 * Fichier header de la classe CSommet contenant les attributs et méthodes pour initialiser
 * des sommets comprenant deux listes de CArcs.
 *
 * \warning les CSommets initialisés à l'extérieur d'un CGraphe ne peuvent être ajoutés à
 * un CGraphe par la suite. Il y a donc peu d'intérêt pour l'utilisateur à créer des CSommets.
 *
 * De plus, les méthodes de CSommet n'ont pas pour but d'être utilisées sur des CSommets présent dans un CGraphe, cela remettant en cause l'intégrité de ce dernier.
 * Veuillez utilisez les méthodes de CGraphe pour manipuler les CSommets présent dans un CGraphe.
 *
 */

#ifndef CSommet_hpp
#define CSommet_hpp

#include <stdio.h>
#include <stdlib.h>
#include "CArc.h"
#include "CException.h"

//Code d'erreur en 200 pour CSommet
#define EXC_MallocError 1
#define EXC_EmptyTab 200
#define EXC_ElementMissing 201
#define EXC_SommetNonCoherent 202


class CSommet{
    // Attributes
private:
    unsigned int uiSOMNumeroSommet;
    
    CArc** ppARCSOMArrivee;
    unsigned int uiSOMNbArcArrive;
    unsigned int uiSOMTailleArrivee;
    
    CArc** ppARCSOMPartant;
    unsigned int uiSOMNbArcPartant;
    unsigned int uiSOMTaillePartant;
    
    
    // Constructeurs/Destructeurs
public:
    
    /**
     * \fn CSommet::CSommet()
     * \brief Constructeur par défaut de CSommet
     *
     */
    CSommet();
    
    /**
     * \fn CSommet::CSommet(CSommet & SOMSommet)
     * \brief Constructeur de recopie de CSommet
     *
     * \param SOMSommet CSommet qui spécifie le CSommet que l'on veut recopier
     *
     */
    CSommet(CSommet & SOMSommet);
    
   /**
    * \fn CSommet::CSommet(unsigned int uiNumSommet)
    * \brief Constructeur de confort de CSommet
    *
    * \param uiNumSommet unsigned int qui est l'id que l'on fixe au sommet
    *
    */
    CSommet(unsigned int uiNumSommet);
    
    /**
     * \fn CSommet::~CSommet()
     * \brief Destructeur de CSommet
     *
     * Ce destructeur delete les CArcs présent dans les tableaux de CArcs arrivants et partants.
     *
     */
    ~CSommet();
    
    // Methodes
public:
    
    /**
     * \fn CSommet CSommet::operator=(CSommet & SOMSommet)
     * \brief Surcharge de l'operateur= entre deux CSommets
     *
     * \param SOMSommet CSommet (en lvalue) qui spécifie le CSommet que l'on veut recopier
     *
     * \return CSommet recopié
     *
     * Cette méthode désalloue et supprime les CArcs qui étaient présent dans les tableaux du CSommet dans lequel on veut recopier le CSommet passé en paramètre. De plus, les CArcs sont copié entièrement et non juste leurs adresses.
     */
    CSommet operator=(CSommet & SOMSommet);
    
    /**
     * \fn CSommet CSommet::operator=(CSommet && SOMSommet)
     * \brief Surcharge de l'operateur= entre deux CSommets
     *
     * \param SOMSommet CSommet (en rvalue) qui spécifie le CSommet que l'on veut recopier
     *
     * \return CSommet recopié
     *
     * Cette méthode désalloue et supprime les CArcs qui étaient présent dans les tableaux du CSommet dans lequel on veut recopier le CSommet passé en paramètre. De plus, les CArcs sont copié entièrement et non juste leurs adresses.
     *
     */
    CSommet operator=(CSommet && SOMSommet);
    
    /**
     * \fn unsigned int SOMGetNumeroSommet()
     * \brief Accesseur en lecture sur uiSOMNumeroSommet
     *
     * \return unsigned int qui spécifie l'identifiant du CSommet
     *
     */
    unsigned int SOMGetNumeroSommet() { return uiSOMNumeroSommet; }
    
    /**
     * \fn unsigned int SOMGetNbArcsPartants()
     * \brief Accesseur en lecture sur uiSOMNbArcArrive
     *
     * \return unsigned int qui spécifie le nombre de CArc partants de ce CSommet
     *
     */
    unsigned int SOMGetNbArcsPartants() { return uiSOMNbArcPartant; }
    
    /**
     * \fn unsigned int SOMGetNumSommetArcPartant(unsigned int uiIndice)
     * \brief Accesseur en lecture sur uiSOMNbArcPartant
     *
     * \return unsigned int qui spécifie l'indice du CArc dont on souhaite récupéré la destination
     *
     */
    unsigned int SOMGetNumSommetArcPartant(unsigned int uiIndice){ return ppARCSOMPartant[uiIndice]->ARCGetDestination(); }
    
    /**
     * \fn unsigned int SOMGetNbArcsArrivants()
     * \brief Accesseur en lecture sur uiSOMNbArcArrive
     *
     * \return unsigned int qui spécifie le nombre de CArc arrivants à ce CSommet
     *
     */
    unsigned int SOMGetNbArcsArrivants() { return uiSOMNbArcArrive; }
    
    /**
     * \fn unsigned int SOMGetNumSommetArcArrivant(unsigned int uiIndice)
     * \brief Accesseur en lecture sur un CArc présent dans le tableau des CArcs arrivants
     *
     * \param uiIndice unsigned int qui spécifie l'indice du CArc dont on souhaite récupéré la destination
     *
     * \return unsigned int qui est la destination de l'arc spécifié
     *
     */
    unsigned int SOMGetNumSommetArcArrivant(unsigned int uiIndice) { return ppARCSOMArrivee[uiIndice]->ARCGetDestination(); }
    
    /**
     * \fn void SOMSetNumeroSommet(unsigned int uiNumero)
     * \brief Accesseur en écriture sur uiSOMNumeroSommet
     *
     * \param uiNumero unsigned int qui spécifie l'identifiant que l'on souhaite mettre à notre CSommet
     *
     * \warning Ne pas utiliser cette méthode pour un sommet présent dans un graphe.
     *
     */
    void SOMSetNumeroSommet(unsigned int uiNumero) { uiSOMNumeroSommet = uiNumero;}
    
    /**
     * \fn void CSommet::SOMAjouterArcArrivant(unsigned int uiNumDestination)
     * \brief Méthode permettant d'ajouter un arc arrivant à notre CSommet
     *
     * \param uiNumDestination unsigned int qui spécifie le numéro de destination de notre CArc que l'on ajoute à notre tableau de CArcs arrivants.
     *
     * \warning Ne pas utiliser cette méthode pour un sommet présent dans un graphe.
     *
     */
    void SOMAjouterArcArrivant(unsigned int uiNumDestination); 
    
    /**
     * \fn void CSommet::SOMSupprimerArcArrivant(unsigned int uiNumDestination)
     * \brief Méthode permettant de supprimer un arc arrivant de notre CSommet
     *
     * \param uiNumDestination unsigned int qui spécifie le numéro de destination de notre CArc que l'on supprime de notre tableau de CArcs arrivants.
     *
     * \warning Ne pas utiliser cette méthode pour un sommet présent dans un graphe.
     *
     */
    void SOMSupprimerArcArrivant(unsigned int uiNumDestination);
    
    /**
     * \fn void CSommet::SOMAjouterArcPartant(unsigned int uiNumDestination)
     * \brief Méthode permettant d'ajouter un arc partant à notre CSommet
     *
     * \param uiNumDestination unsigned int qui spécifie le numéro de destination de notre CArc que l'on ajoute à notre tableau de CArcs partants.
     *
     * \warning Ne pas utiliser cette méthode pour un sommet présent dans un graphe.
     *
     */
    void SOMAjouterArcPartant(unsigned int uiNumDestination);
    
    /**
     * \fn void CSommet::SOMSupprimerArcPartant(unsigned int uiNumDestination)
     * \brief Méthode permettant de supprimer un arc partant de notre CSommet
     *
     * \param uiNumDestination unsigned int qui spécifie le numéro de destination de notre CArc que l'on supprime de notre tableau de CArcs partant.
     *
     * \warning Ne pas utiliser cette méthode pour un sommet présent dans un graphe.
     *
     */
    void SOMSupprimerArcPartant(unsigned int uiNumDestination);
    
};

#endif /* CSommet_hpp */



