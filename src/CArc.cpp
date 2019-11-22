/**
 * \file CArc.cpp
 * \brief Fichier de méthodes de la classe CArc.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.1
 * \date 16 mai 2019
 *
 */

#include "CArc.h"

/**
 * \fn CArc::CArc()
 * \brief Constructeur par défaut de la classe CArc
 *
 */
CArc::CArc(){
    uiARCDestination = 0;
}

/**
 * \fn CArc::CArc(unsigned int uiDestination)
 * \brief Constructeur de confort de la classe CArc
 *
 */
CArc::CArc(unsigned int uiDestination){
    uiARCDestination = uiDestination;
}

/**
 * \fn unsigned int CArc::ARCGetDestination()
 * \brief Accesseur en lecture sur uiARCDestination
 *
 * \return unsigned int qui représente la valeur de la destination
 */
unsigned int CArc::ARCGetDestination(){
    return uiARCDestination;
}

/**
 * \fn void CArc::ARCModifierDestination(unsigned int uiDestination)
 * \brief Accesseur en ecriture sur uiARCDestination
 *
 * \param uiDestination unsigned int qui représente la valeur de la destination
 */
void CArc::ARCModifierDestination(unsigned int uiDestination){
    uiARCDestination = uiDestination;
}
