/* Fichier des prototypes des fonctions et procédures */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "fonctions.c"

void insertion(listeChainee *liste, ouvrier *nouveau);
listeChainee *initialiserRepertoire();
void enregistrerOuvrier(listeChainee *liste);
void afficherRepertoire(listeChainee *liste);
void rechercheParNomEtPrenom(ouvrier *courant);
void rechercheParMatricule(ouvrier *courant);
listeChainee *retirerOuvrier(listeChainee *liste);
void menu();

#endif
