/**
 * \file main.cpp
 * \brief Fichier main de la librairie Les Graphes
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.1
 * \date 16 mai 2019
 *
 * Ce fichier comporte la fonction main.
 *
 */

#include <iostream>
#include "CGraphe.h"
#include "CParser.h"

int testsUnitaires() {
    CGraphe graphe1 = CGraphe();
    
    graphe1.GRAAjouterSommet(1);
    graphe1.GRAAjouterSommet(2);
    graphe1.GRAAjouterSommet(3);
    graphe1.GRAAjouterSommet(4);
    graphe1.GRAAjouterSommet();
    
    graphe1.GRAAjouterArc(1, 2);
    graphe1.GRAAjouterArc(2, 1);
    graphe1.GRAAjouterArc(2, 4);
    graphe1.GRAAjouterArc(3, 4);
    
    graphe1.GRAAfficherGraphe();
    graphe1.GRASupprimerSommet(1);
    graphe1.GRAAfficherGraphe();
	graphe1.GRAModifierSommet(2, 7);
	graphe1.GRAAfficherGraphe();
	graphe1.GRAModifierArc(7, 4, 7, 3);
	graphe1.GRAAfficherGraphe();
	graphe1.GRASupprimerArc(7, 3);
	graphe1.GRAAfficherGraphe();
    
    return 0;
}

int main(int argc, char *argv[])
{
    unsigned int uiIndiceSommet;
    int iIndiceArc; // Non unsigned car on a besoin de faire uiIndiceArc-- lorsqu'il vaut 0.
    CGraphe graphe;
    CGraphe grapheInverse;
    
    testsUnitaires();
    
    if (argc > 1) {
        try {
            graphe = CGraphe(argv[1]);
			graphe.GRAAfficherGraphe();
        }
        catch (CException EXCLevee) {
            printf("Code d'erreur levee = %d\n", EXCLevee.EXCLireErreur());
            return 1;
        }
        
        printf("=========Inversion de tous les arcs du graphe =========\n\n");
        
        //On recopie d'abord tous les sommet du premier graphe :
        for (uiIndiceSommet = 0; uiIndiceSommet < graphe.GRAGetNbSommets(); uiIndiceSommet++) {
            grapheInverse.GRAAjouterSommet(graphe.GRAGetSommet(uiIndiceSommet)->SOMGetNumeroSommet());
        }
        
        //Puis on ajoute tous les arcs en les inversants au nouveau graphe :
        //On parcourt uniquement les arcs partants avec notre fonction GRAModifierArc qui inversera Žgalement les arcs arrivants
        for (uiIndiceSommet = 0; uiIndiceSommet < graphe.GRAGetNbSommets(); uiIndiceSommet++) {
            for (iIndiceArc = graphe.GRAGetSommet(uiIndiceSommet)->SOMGetNbArcsPartants() - 1; iIndiceArc >= 0 ; iIndiceArc--) {
                grapheInverse.GRAAjouterArc(graphe.GRAGetSommet(uiIndiceSommet)->SOMGetNumSommetArcPartant(iIndiceArc), graphe.GRAGetSommet(uiIndiceSommet)->SOMGetNumeroSommet());
            }
        }
        grapheInverse.GRAAfficherGraphe();
    }
    else {
        std::cout << "Aucun nom de fichier passe en parametre." << std::endl;
    }
}

