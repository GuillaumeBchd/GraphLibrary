/**
 * \file CArc.h
 * \brief Fichier header de la classe CArc.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.1
 * \date 16 mai 2019
 *
 * Fichier header de la classe CArc contenant les attributs et méthodes pour initialiser
 * des arcs.
 *
 * \warning les CArcs initialisés à l'extérieur d'un CGraphe ne peuvent être ajoutés à un CGraphe par la suite. Il y a donc peu d'intérêt pour l'utilisateur à créer des CArcs.
 *
 * De plus, les méthodes de CArc n'ont pas pour but d'être utilisées sur des CArcs présent dans un CGraphe, cela remettant en cause l'intégrité de ce dernier.
 * Veuillez utilisez les méthodes de CGraphe pour manipuler les CArcs présent dans un CGraphe.
 *
 */

#ifndef CArc_h
#define CArc_h

#include <stdio.h>

class CArc{
    // Attributes
private:
    unsigned int uiARCDestination;
    
    // Constructeurs/Destructeurs
public:
    
    /**
     * \fn CArc::CArc()
     * \brief Constructeur par défaut de la classe CArc
     *
     */
    CArc();
    
    /**
     * \fn CArc::CArc(unsigned int uiDestination)
     * \brief Constructeur de confort de la classe CArc
     *
     */
    CArc(unsigned int uiDestination);
    
    // Methodes
public:
    
    /**
     * \fn unsigned int CArc::ARCGetDestination()
     * \brief Accesseur en lecture sur uiARCDestination
     *
     * \return unsigned int qui représente la valeur de la destination
     */
    unsigned int ARCGetDestination();
    
    /**
     * \fn void CArc::ARCModifierDestination(unsigned int uiDestination)
     * \brief Accesseur en ecriture sur uiARCDestination
     *
     * \param uiDestination unsigned int qui représente la valeur de la destination
     */
    void ARCModifierDestination(unsigned int uiDestination);
    
};

#endif /* CArc_hpp */
