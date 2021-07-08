/* Fichier des prototypes des fonctions et procédures */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "fonctions.c"

listeChainee *initialiserRepertoire();

void sauvegardeFichier(listeChainee *liste);

int matriculeExiste(listeChainee *liste, int matricule);

void tronquerMot(char *mot);

void tronquerGenre(char *mot);

int estVide(listeChainee *liste);

void inserer(listeChainee *liste, ouvrier *nouveau);

void enregistrerOuvrier(listeChainee *liste);

int longueur(listeChainee *liste);

void rechercheParNomEtPrenom(listeChainee *liste);

void genre(listeChainee *liste);

void afficherRepertoire(listeChainee *liste);

listeChainee *retirerOuvrier(listeChainee *liste);

void menu();

#endif
