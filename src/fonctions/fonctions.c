/*
* Fichier de définition des fonctions et procédures
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define taille 50
#define true 1
#define false 0

/*
* Définition des structures de données
*/

typedef struct ouvrier
{
  int matricule;
  char nom[taille], prenom[taille], telephone[taille], mail[taille], genre[taille]; // Tableau de chaîne de caractères
  struct ouvrier *suivant;                                           // Pointeur sur l'ouvrier suivant
} ouvrier;

typedef struct liste
{
  ouvrier *premier; // Pointeur sur le premier ouvrier
} listeChainee;

/*
* Définition des fonctions et procédures
*/

void sauvegardeFichier(listeChainee *liste)
{
  FILE *fichier;
  ouvrier *courant = liste->premier;
  fichier = fopen("documents/repertoire_ouvrier.txt", "w"); // Ouverture du fichier en mode d'écriture
  while (courant != NULL)                 // Parcours de la liste jusqu'à la fin matérialisée par NULL
  {
    fprintf(fichier, "%d\t%s\t%s\t%s\t%s\t%s\n", courant->matricule, courant->nom, courant->prenom, courant->telephone, courant->mail, courant->genre);
    courant = courant->suivant;
  }
  fclose(fichier);
}

int estVide(listeChainee *liste)
{
  return (liste->premier == NULL) ? true : false;
}

int matriculeExistant(listeChainee *liste, int matricule)
{
  ouvrier *courant = liste->premier;
  int trouver = false;
  while (courant != NULL)
  {
    if (courant->matricule == matricule)
    {
      trouver = true;
    }
    courant = courant->suivant;
  }
  return trouver;
}

void inserer(listeChainee *liste, ouvrier *nouveau)
{
  ouvrier *courant = liste->premier;
  if (courant != NULL) // Si le premier ouvrier existe
  {
    while (courant->suivant != NULL) // Si le suivant de l'ouvrier courant n'est pas NULL
    {
      courant = courant->suivant; // On avance jusqu'à la fin qui est NULL
    }
    // On quitte la boucle while si le suivant de la ouvrier courante est NULL: c'est la fin
    courant->suivant = nouveau; // On insère donc le nouveau ouvrier à la fin
    nouveau->suivant = NULL;    // Et le suivant du nouveau ouvrier pointe sur NULL
  }
  else // Il n'y a pas de ouvrier dans la liste
  {
    nouveau->suivant = liste->premier; // Le nouveau ouvrier est la premier sur la liste
    liste->premier = nouveau;          // Et pour ne pas perdre la liste de vue, le pointeur de premier pointe sur 'nouveau'
  }
}

listeChainee *initialiserRepertoire()
{
  listeChainee *liste = (listeChainee *)malloc(sizeof(listeChainee)); // Déclaration d'une liste avec une allocation dynamique de l'espace mémoire
  ouvrier *nouveau = (ouvrier *)malloc(sizeof(ouvrier));              // Déclaration d'une variable de type ouvrier pour stocker les données du fichier
  int compteur = 0;

  liste->premier = NULL; // La liste nouvellement initialisée ne contient aucun élément donc son premier élément pointe sur NULL

  FILE *fichier = fopen("documents/repertoire_ouvrier.txt", "r"); // Ouverture du fichier en mode lecture
  if (fichier != NULL)
  {
    while (fscanf(fichier, "%d\t%s\t%s\t%s\t%s\t%s\n", &nouveau->matricule, nouveau->nom, nouveau->prenom, nouveau->telephone, nouveau->mail, nouveau->genre) != EOF)
    {
      inserer(liste, nouveau);
      nouveau = (ouvrier *)malloc(sizeof(ouvrier)); // On alloue un nouvel espace pour l'élément suivant
    }
    fclose(fichier);
  }
  return liste; // On retourne la liste initialisée avec les données du fichier
}

void enregistrerOuvrier(listeChainee *liste)
{
  ouvrier *nouveau = (ouvrier *)malloc(sizeof(ouvrier));
  ouvrier *courant = liste->premier;
  char rep[taille];
  system("clear");
  printf("\n----------ENREGISTREMENT----------\n");
  do
  {
    printf("\nMatricule: ");
    scanf("%d", &nouveau->matricule);
    if (matriculeExistant(liste, nouveau->matricule) == true)
    {
      printf("\nMatricule existant. Veuillez le changer !\n");
    }
  } while (matriculeExistant(liste, nouveau->matricule) == true);

  printf("\nNom: ");
  scanf("%s", nouveau->nom);

  printf("\nPrénom: ");
  scanf("%s", nouveau->prenom);

  printf("\nTéléphone: ");
  scanf("%s", nouveau->telephone);

  printf("\nMail: ");
  scanf("%s", nouveau->mail);

  do
  {
    printf("\nGenre: [ F(éminin) / M(asculin) ]: ");
    scanf("%s", nouveau->genre);
    if (strcasecmp(nouveau->genre, "F") != 0 && strcasecmp(nouveau->genre, "M") != 0)
    {
      printf("\nVeuillez choisir la bonne lettre !\n");
    }
  } while (strncasecmp(nouveau->genre, "F", 1) && strncasecmp(nouveau->genre, "M", 1));

  // nouveau->genre = (strncasecmp(nouveau->genre, "F", 1) == 0) ? "F" : "M";

  inserer(liste, nouveau);
  system("clear");
  printf("\n----------ENREGISTREMENT----------\n");
  printf("\nAjout réussi !\n");
}

int longueur(listeChainee *liste)
{
  ouvrier *courant = liste->premier;
  int compteur = 0;
  if (estVide(liste) == true)
  {
    printf("\nRépertoire vide\n");
  }
  else
  {
    while (courant != NULL)
    {
      courant = courant->suivant;
      compteur++;
    }
  }
  return compteur;
}

void rechercheParNomEtPrenom(listeChainee *liste)
{
  ouvrier *courant = liste->premier;
  char nom[taille], prenom[taille];
  int trouver = 0;
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  printf("\nNom: ");
  scanf("%s", nom);
  printf("\nPrénom: ");
  scanf("%s", prenom);
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  while (courant != NULL)
  {
    if (strcasecmp(courant->nom, nom) == 0 && strcasecmp(courant->prenom, prenom) == 0)
    {
      printf("\nMatricule: %d", courant->matricule);
      printf("\nNom: %s", courant->nom);
      printf("\nPrénom: %s", courant->prenom);
      printf("\nTéléphone: %s", courant->telephone);
      printf("\nMail: %s", courant->mail);
      printf("\nGenre: %s", courant->genre);
      printf("\n----------------------------");
      trouver++;
    }
    courant = courant->suivant;
  }
  if (trouver == 0)
  {
    printf("\nOuvrier non trouvé !\n");
  }
  else
  {
    printf("\n\n%d ouvrier(s) trouvé(s)\n", trouver);
  }
}

void genre(listeChainee *liste)
{
  ouvrier *courant = liste->premier;
  int compteur = 0;
  system("clear");
  printf("\n---------- AFFICHAGE DE LA FICHE DES OUVRIÈRES ----------\n");
  if (estVide(liste) == true)
  {
    printf("\nRépertoire vide\n");
  }
  else
  {
    while (courant != NULL)
    {
      if (strncasecmp(courant->genre, "F", 1))
      {
        printf("\nMatricule: %d", courant->matricule);
        printf("\nNom: %s", courant->nom);
        printf("\nPrénom: %s", courant->prenom);
        printf("\nTéléphone: %s", courant->telephone);
        printf("\nMail: %s", courant->mail);
        compteur++;
        printf("\n----------------------------");
      }
      courant = courant->suivant;
    }
    if (compteur == 0)
    {
      printf("\n\n Zéro ouvrière trouvée");
    }
    else
    {
      printf("\n\nTotal: %d\n", compteur);
    }
  }
}

void afficherRepertoire(listeChainee *liste)
{
  ouvrier *courant = liste->premier;
  system("clear");
  printf("\n---------- AFFICHAGE DE LA FICHE DE TOUS LES OUVRIERS----------\n");
  if (estVide(liste) == true)
  {
    printf("\nRépertoire vide\n");
  }
  else
  {
    while (courant != NULL)
    {
      printf("\nMatricule: %d", courant->matricule);
      printf("\nNom: %s", courant->nom);
      printf("\nPrénom: %s", courant->prenom);
      printf("\nTéléphone: %s", courant->telephone);
      printf("\nMail: %s", courant->mail);
      printf("\nGenre: %s", courant->genre);
      courant = courant->suivant;
      printf("\n----------------------------");
    }
    printf("\n\nTotal: %d\n", longueur(liste));
  }
}

listeChainee *retirerOuvrier(listeChainee *liste)
{
  ouvrier *courant = liste->premier;
  ouvrier *next;
  char nom[taille], prenom[taille], rep[taille];
  int trouver = 0;
  system("clear");
  printf("\n----------SUPPRESSION----------\n");
  if (estVide(liste) == true)
  {
    printf("\nRepertoire vide\n");
    return liste;
  }
  else
  {
    printf("\nNom: ");
    scanf("%s", nom);
    printf("\nPrénom: ");
    scanf("%s", prenom);
    if (strcasecmp(courant->nom, nom) == 0 && strcasecmp(courant->prenom, prenom) == 0)
    {
      trouver++;
      printf("\nVoulez-vous vraiment supprimer l'ouvrier ? [o/n] ");
      scanf("%s", rep);
      while (rep[0] != 'n' && rep[0] != 'N' && rep[0] != 'o' && rep[0] != 'O')
      {
        printf("\n Votre réponse [o/n]: ");
        scanf("%s", rep);
      }
      if (rep[0] == 'n' || rep[0] == 'N')
      {
        printf("\nSuppression annulée !\n");
        return liste;
      }
      if (rep[0] == 'o' || rep[0] == 'O')
      {
        liste->premier = courant->suivant;
        free(courant);
        system("clear");
        printf("\n----------SUPPRESSION----------\n");
        printf("\nSuppression réussie !\n");
        return liste;
      }
    }
    else
    {
      next = courant->suivant;
      while (next != NULL)
      {
        if (strcasecmp(next->nom, nom) == 0 && strcasecmp(next->prenom, prenom) == 0 && next != NULL)
        {
          trouver++;
          printf("\nVoulez-vous vraiment supprimer l'ouvrier ? [o/n] ");
          scanf("%s", rep);
          while (rep[0] != 'n' && rep[0] != 'N' && rep[0] != 'o' && rep[0] != 'O')
          {
            printf("\n Votre réponse [o/n]: ");
            scanf("%s", rep);
          }
          if (rep[0] == 'n' || rep[0] == 'N')
          {
            return liste;
          }
          if (rep[0] == 'o' || rep[0] == 'O')
          {
            courant->suivant = next->suivant;
            free(next);
            system("clear");
            printf("\n----------SUPPRESSION----------\n");
            printf("\nSuppression réussie !\n");
            return liste;
          }
        }
        if (next == NULL)
        {
          trouver = 0;
        }
        courant = next;
        next = next->suivant;
      }
    }
    if (trouver == 0)
    {
      system("clear");
      printf("\n----------SUPPRESSION----------\n");
      printf("\nOuvrier non trouvé !\n");
      return liste;
    }
  }
  return liste;
}

void menu()
{
  system("clear");
  printf("\nQue voulez-vous faire : \n");
  printf("\n* Ajouter une ouvrier                       (1)\n");
  printf("\n* Afficher tout le repertoire               (2)\n");
  printf("\n* Afficher le repertoire des ouvrières      (3)\n");
  printf("\n* Faire une recherche par nom               (4)\n");
  printf("\n* Retirer une ouvrier par nom               (5)\n");
  printf("\n* Terminer                                  (6)\n");
  printf("\nVotre choix: ");
}
