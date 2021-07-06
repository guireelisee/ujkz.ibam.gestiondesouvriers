/* Fichier des prototypes des fonctions et procédures */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "fonctions.c"

listeChainee *initialisation();
void insertion(listeChainee *liste, ouvrier *nouveau);
void initialiserRepertoire(listeChainee *liste);
void enregistrerOuvrier(listeChainee *liste);
void afficherRepertoire(listeChainee *liste);
void rechercheParNomEtPrenom(ouvrier *courant);
void rechercheParMatricule(ouvrier *courant);
listeChainee *retirerOuvrier(listeChainee *liste);
void menu();

#endif
