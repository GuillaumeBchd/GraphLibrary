/**
 * \file CSommet.cpp
 * \brief Fichier de méthodes de la classe CSommet.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.1
 * \date 16 mai 2019
 *
 */

#include "CSommet.h"

/**
 * \fn CSommet::CSommet()
 * \brief Constructeur par défaut de CSommet
 *
 */
CSommet::CSommet() : uiSOMNbArcPartant(0), uiSOMTaillePartant(0), uiSOMNbArcArrive(0), uiSOMTailleArrivee(0){
    uiSOMNumeroSommet = 0;
    ppARCSOMArrivee = NULL;
    ppARCSOMPartant = NULL;
}

/**
 * \fn CSommet::CSommet(CSommet & SOMSommet)
 * \brief Constructeur de recopie de CSommet
 *
 * \param SOMSommet CSommet qui spécifie le CSommet que l'on veut recopier
 *
 */
CSommet::CSommet(CSommet & SOMSommet)
{
    unsigned int uiIterateur;
    
    uiSOMNumeroSommet = SOMSommet.uiSOMNumeroSommet;
    uiSOMNbArcArrive = SOMSommet.uiSOMNbArcArrive;
    uiSOMTailleArrivee = SOMSommet.uiSOMTailleArrivee;
    uiSOMNbArcPartant = SOMSommet.uiSOMNbArcPartant;
    uiSOMTaillePartant = SOMSommet.uiSOMTaillePartant;
    
    //Verif graphe cohérent
    if (uiSOMNbArcArrive > uiSOMTailleArrivee || uiSOMNbArcPartant > uiSOMTaillePartant) {
        CException EXCError(EXC_SommetNonCoherent);
        throw EXCError;
    }
    
    //Recopie des arcs arrivants
    if (uiSOMTailleArrivee != 0) {
        ppARCSOMArrivee = (CArc**)malloc(sizeof(CArc*)*uiSOMTailleArrivee);
        if (ppARCSOMArrivee == NULL) {
            CException EXCError(EXC_MallocError);
            throw EXCError;
        }
        
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcArrive; uiIterateur++) {
            ppARCSOMArrivee[uiIterateur] = new CArc(*SOMSommet.ppARCSOMArrivee[uiIterateur]);
        }
    }
    //Recopie des arcs partants
    if (uiSOMTaillePartant != 0) {
        ppARCSOMPartant = (CArc**)malloc(sizeof(CArc*)*uiSOMTaillePartant);
        if (ppARCSOMPartant == NULL) {
            CException EXCError(EXC_MallocError);
            throw EXCError;
        }
        
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcPartant; uiIterateur++) {
            ppARCSOMPartant[uiIterateur] = new CArc(*SOMSommet.ppARCSOMPartant[uiIterateur]);
        }
    }
}

/**
 * \fn CSommet::CSommet(unsigned int uiNumSommet)
 * \brief Constructeur de confort de CSommet
 *
 * \param uiNumSommet unsigned int qui est l'id que l'on fixe au sommet
 *
 */
CSommet::CSommet(unsigned int uiNumSommet) : uiSOMNbArcPartant(0), uiSOMTaillePartant(0), uiSOMNbArcArrive(0), uiSOMTailleArrivee(0){
    uiSOMNumeroSommet = uiNumSommet;
    ppARCSOMArrivee = NULL;
    ppARCSOMPartant = NULL;
}

/**
 * \fn CSommet::~CSommet()
 * \brief Destructeur de CSommet
 *
 * Ce destructeur delete les CArcs présent dans les tableaux de CArcs arrivants et partants.
 *
 */
CSommet::~CSommet()
{
    unsigned int uiIterateurArc;
    
    //On delete le tableau des arcs arrivants :
   if (uiSOMTailleArrivee != 0) {
        //On delete les CArc
        for (uiIterateurArc = 0; uiIterateurArc < uiSOMNbArcArrive; uiIterateurArc++) {
            delete(ppARCSOMArrivee[uiIterateurArc]);
        }
        free(ppARCSOMArrivee);
        ppARCSOMArrivee = NULL;
    }
    
    //On delete le tableau des arcs partants :
    if (uiSOMTaillePartant != 0) {
        //On delete les CArc
        for (uiIterateurArc = 0; uiIterateurArc < uiSOMNbArcPartant; uiIterateurArc++) {
            delete(ppARCSOMPartant[uiIterateurArc]);
        }
        free(ppARCSOMPartant);
        ppARCSOMPartant = NULL;
    }
}

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
CSommet CSommet::operator=(CSommet & SOMSommet)
{
    unsigned int uiIterateur;
    
    if (ppARCSOMArrivee != NULL) {
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcArrive; uiIterateur++) {
            delete(ppARCSOMArrivee[uiIterateur]);
        }
        free(ppARCSOMArrivee);
        ppARCSOMArrivee = NULL;
    }
    if (ppARCSOMPartant != NULL) {
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcPartant; uiIterateur++) {
            delete(ppARCSOMPartant[uiIterateur]);
        }
        free(ppARCSOMPartant);
        ppARCSOMPartant = NULL;
    }
    
    uiSOMNumeroSommet = SOMSommet.uiSOMNumeroSommet;
    uiSOMNbArcArrive = SOMSommet.uiSOMNbArcArrive;
    uiSOMTailleArrivee = SOMSommet.uiSOMTailleArrivee;
    uiSOMNbArcPartant = SOMSommet.uiSOMNbArcPartant;
    uiSOMTaillePartant = SOMSommet.uiSOMTaillePartant;
    
    //Verif graphe cohérent
    if (uiSOMNbArcArrive > uiSOMTailleArrivee || uiSOMNbArcPartant > uiSOMTaillePartant) {
        CException EXCError(EXC_SommetNonCoherent);
        throw EXCError;
    }
    
    //Recopie des arcs arrivants
    if (uiSOMTailleArrivee != 0) {
        ppARCSOMArrivee = (CArc**)malloc(sizeof(CArc*)*uiSOMTailleArrivee);
        if (ppARCSOMArrivee == NULL) {
            CException EXCError(EXC_MallocError);
            throw EXCError;
        }
        
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcArrive; uiIterateur++) {
            ppARCSOMArrivee[uiIterateur] = new CArc(*SOMSommet.ppARCSOMArrivee[uiIterateur]);
        }
    }
    //Recopie des arcs partants
    if (uiSOMTaillePartant != 0) {
        ppARCSOMPartant = (CArc**)malloc(sizeof(CArc*)*uiSOMTaillePartant);
        if (ppARCSOMPartant == NULL) {
            CException EXCError(EXC_MallocError);
            throw EXCError;
        }
        
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcPartant; uiIterateur++) {
            ppARCSOMPartant[uiIterateur] = new CArc(*SOMSommet.ppARCSOMPartant[uiIterateur]);
        }
    }
    
    return *this;
}

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
CSommet CSommet::operator=(CSommet && SOMSommet)
{
    unsigned int uiIterateur;
    
    if (ppARCSOMArrivee != NULL) {
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcArrive; uiIterateur++) {
            delete(ppARCSOMArrivee[uiIterateur]);
        }
        free(ppARCSOMArrivee);
        ppARCSOMArrivee = NULL;
    }
    if (ppARCSOMPartant != NULL) {
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcPartant; uiIterateur++) {
            delete(ppARCSOMPartant[uiIterateur]);
        }
        free(ppARCSOMPartant);
        ppARCSOMPartant = NULL;
    }
    
    uiSOMNumeroSommet = SOMSommet.uiSOMNumeroSommet;
    uiSOMNbArcArrive = SOMSommet.uiSOMNbArcArrive;
    uiSOMTailleArrivee = SOMSommet.uiSOMTailleArrivee;
    uiSOMNbArcPartant = SOMSommet.uiSOMNbArcPartant;
    uiSOMTaillePartant = SOMSommet.uiSOMTaillePartant;
    
    //Verif graphe cohérent
    if (uiSOMNbArcArrive > uiSOMTailleArrivee || uiSOMNbArcPartant > uiSOMTaillePartant) {
        CException EXCError(EXC_SommetNonCoherent);
        throw EXCError;
    }
    
    //Recopie des arcs arrivants
    if (uiSOMTailleArrivee != 0) {
        ppARCSOMArrivee = (CArc**)malloc(sizeof(CArc*)*uiSOMTailleArrivee);
        if (ppARCSOMArrivee == NULL) {
            CException EXCError(EXC_MallocError);
            throw EXCError;
        }
        
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcArrive; uiIterateur++) {
            ppARCSOMArrivee[uiIterateur] = new CArc(*SOMSommet.ppARCSOMArrivee[uiIterateur]);
        }
    }
    //Recopie des arcs partants
    if (uiSOMTaillePartant != 0) {
        ppARCSOMPartant = (CArc**)malloc(sizeof(CArc*)*uiSOMTaillePartant);
        if (ppARCSOMPartant == NULL) {
            CException EXCError(EXC_MallocError);
            throw EXCError;
        }
        
        for (uiIterateur = 0; uiIterateur < uiSOMNbArcPartant; uiIterateur++) {
            ppARCSOMPartant[uiIterateur] = new CArc(*SOMSommet.ppARCSOMPartant[uiIterateur]);
        }
    }
    
    return *this;
}

/**
 * \fn void CSommet::SOMAjouterArcArrivant(unsigned int uiNumDestination)
 * \brief Méthode permettant d'ajouter un arc arrivant à notre CSommet
 *
 * \param uiNumDestination unsigned int qui spécifie le numéro de destination de notre CArc que l'on ajoute à notre tableau de CArcs arrivants.
 *
 * \warning Ne pas utiliser cette méthode pour un sommet présent dans un graphe.
 *
 */
void CSommet::SOMAjouterArcArrivant(unsigned int uiNumDestination){
    CArc * ARCArr = new CArc(uiNumDestination);
    
    //On s'occupe de la taille du tableau
    if(uiSOMTailleArrivee == 0){
        uiSOMTailleArrivee = 4;
        ppARCSOMArrivee = (CArc**) malloc(sizeof(CArc**)*uiSOMTailleArrivee);
        
    }
    else{
        if(uiSOMNbArcArrive == uiSOMTailleArrivee){
            uiSOMTailleArrivee = uiSOMTailleArrivee*2;
            ppARCSOMArrivee = (CArc**) realloc(ppARCSOMArrivee, sizeof(CArc**)*uiSOMTailleArrivee);
        }
    }
    
    //On ajoute l'arc au sommet
    ppARCSOMArrivee[uiSOMNbArcArrive] = ARCArr;
    uiSOMNbArcArrive++;
}

/**
 * \fn void CSommet::SOMSupprimerArcArrivant(unsigned int uiNumDestination)
 * \brief Méthode permettant de supprimer un arc arrivant de notre CSommet
 *
 * \param uiNumDestination unsigned int qui spécifie le numéro de destination de notre CArc que l'on supprime de notre tableau de CArcs arrivants.
 *
 * \warning Ne pas utiliser cette méthode pour un sommet présent dans un graphe.
 *
 */
void CSommet::SOMSupprimerArcArrivant(unsigned int uiNumDestination){
    
    if(uiSOMNbArcArrive == 0){
        CException EXCError(EXC_EmptyTab);
        throw(EXCError);
    }
    
    //On parcourt le tableau
    unsigned int uiIterateurArrivee = 0;
    while(uiIterateurArrivee < uiSOMNbArcArrive-1 && ppARCSOMArrivee[uiIterateurArrivee]->ARCGetDestination() != uiNumDestination){
        //On sort du tableau si on arrive au bout ou si on trouve l'arc.
        uiIterateurArrivee++;
    }
    
    //Si on est arrivé au bout du tableau
    if(uiIterateurArrivee == uiSOMNbArcArrive){
        CException EXCError(EXC_ElementMissing);
        throw(EXCError);
    }
    
    //On enlève l'arc du tableau.
    delete(ppARCSOMArrivee[uiIterateurArrivee]);
    
    while(uiIterateurArrivee < uiSOMNbArcArrive-1){
        ppARCSOMArrivee[uiIterateurArrivee] = ppARCSOMArrivee[uiIterateurArrivee+1];
        uiIterateurArrivee++;
    }
    ppARCSOMArrivee[uiIterateurArrivee] = NULL;
    
    uiSOMNbArcArrive--;
}

/**
 * \fn void CSommet::SOMAjouterArcPartant(unsigned int uiNumDestination)
 * \brief Méthode permettant d'ajouter un arc partant à notre CSommet
 *
 * \param uiNumDestination unsigned int qui spécifie le numéro de destination de notre CArc que l'on ajoute à notre tableau de CArcs partants.
 *
 * \warning Ne pas utiliser cette méthode pour un sommet présent dans un graphe.
 *
 */
void CSommet::SOMAjouterArcPartant(unsigned int uiNumDestination){
    CArc * ARCPar = new CArc(uiNumDestination);
    
    //On s'occupe de la taille du tableau
    if(uiSOMTaillePartant == 0){
        uiSOMTaillePartant = 4;
        ppARCSOMPartant = (CArc**) malloc(sizeof(CArc**)*uiSOMTaillePartant);
        
    }
    else{
        if(uiSOMNbArcPartant == uiSOMTaillePartant){
            uiSOMTaillePartant = uiSOMTaillePartant*2;
            ppARCSOMPartant = (CArc**) realloc(ppARCSOMPartant, sizeof(CArc**)*uiSOMTaillePartant);
        }
    }
    
    //On ajoute l'arc au sommet
    ppARCSOMPartant[uiSOMNbArcPartant] = ARCPar;
    uiSOMNbArcPartant++;
}

/**
 * \fn void CSommet::SOMSupprimerArcPartant(unsigned int uiNumDestination)
 * \brief Méthode permettant de supprimer un arc partant de notre CSommet
 *
 * \param uiNumDestination unsigned int qui spécifie le numéro de destination de notre CArc que l'on supprime de notre tableau de CArcs partant.
 *
 * \warning Ne pas utiliser cette méthode pour un sommet présent dans un graphe.
 *
 */
void CSommet::SOMSupprimerArcPartant(unsigned int uiNumDestination){
    if(uiSOMNbArcPartant == 0){
        CException EXCError(EXC_EmptyTab);
        throw(EXCError);
    }
    
    //On parcourt le tableau
    unsigned int uiIterateurPartant = 0;
    while(uiIterateurPartant < uiSOMNbArcPartant-1 && ppARCSOMPartant[uiIterateurPartant]->ARCGetDestination() != uiNumDestination){
        //On sort du tableau si on arrive au bout ou si on trouve l'arc.
        uiIterateurPartant++;
    }
    
    //Si on est arrivé au bout du tableau
    if(uiIterateurPartant == uiSOMNbArcPartant){
        CException EXCError(EXC_ElementMissing);
        throw(EXCError);
    }
    
    //On enlève l'arc du tableau.
    delete(ppARCSOMPartant[uiIterateurPartant]);
    
    while(uiIterateurPartant < uiSOMNbArcPartant-1){
        ppARCSOMPartant[uiIterateurPartant] = ppARCSOMPartant[uiIterateurPartant+1];
        uiIterateurPartant++;
    }
    ppARCSOMPartant[uiIterateurPartant] = NULL;
    
    uiSOMNbArcPartant--;
    
}
