/*
* Fichier de définition des fonctions et procédures
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define taille 100

/*
* Définition des structures de données
*/

typedef struct ouvrier
{
  int matricule;
  char nom[taille], prenom[taille], telephone[taille], mail[taille]; // Tableau de chaîne de caractères
  struct ouvrier *suivant;                                           // Pointeur sur l'ouvrier suivant
} ouvrier;

typedef struct liste
{
  ouvrier *premier; // Pointeur sur le premier ouvrier
} listeChainee;


/*
* Définition des fonctions et procédures
*/

void insertion(listeChainee *liste, ouvrier *nouveau)
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
  ouvrier *nouveau = (ouvrier *)malloc(sizeof(ouvrier)); // Déclaration d'une variable de type ouvrier pour stocker les données du fichier
  int count = 0;

  liste->premier = NULL; // La liste nouvellement initialisée ne contient aucun élément donc son premier élément pointe sur NULL

  FILE *fichier = fopen("Repertoire_ouvrier.txt", "r"); // Ouverture du fichier en mode lecture
  if (fichier != NULL)
  {
    while (fscanf(fichier, "%d\t%s\t%s\t%s\t%s\n",&nouveau->matricule, nouveau->nom, nouveau->prenom, nouveau->telephone, nouveau->mail) != EOF)
    {
      insertion(liste, nouveau);
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
  char rep[50];
  system("clear");
  printf("\n----------ENREGISTREMENT----------\n");
  printf("\n\nMatricule: ");
  scanf("%d", &nouveau->matricule);

  printf("\n\nNom: ");
  scanf("%s", nouveau->nom);

  printf("\nPrénom: ");
  scanf("%s", nouveau->prenom);

  printf("\nTéléphone: ");
  scanf("%s", nouveau->telephone);

  printf("\nMail: ");
  scanf("%s", nouveau->mail);

  insertion(liste, nouveau);
  system("clear");
  printf("\n----------ENREGISTREMENT----------\n");
  printf("\nAjout réussi !\n");
}

void afficherRepertoire(listeChainee *liste)
{
  ouvrier *courant = liste->premier;
  int count = 0;
  system("clear");
  printf("\n----------AFFICHAGE----------\n");
  if (courant == NULL)
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
      courant = courant->suivant;
      count++;
      printf("\n----------------------------");
    }
    printf("\n\nTotal: %d\n", count);
  }
}

void rechercheParNomEtPrenom(ouvrier *courant)
{
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
    if (courant->nom == nom && courant->prenom == prenom)
    {
      printf("\nMatricule: %d", courant->matricule);
      printf("\nNom: %s", courant->nom);
      printf("\nPrénom: %s", courant->prenom);
      printf("\nTéléphone: %s", courant->telephone);
      printf("\nMail: %s", courant->mail);
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
void rechercheParMatricule(ouvrier *courant)
{
  int matricule =0, trouver = 0;
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  printf("\nMatricule: ");
  scanf("%d", &matricule);
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  while (courant != NULL)
  {
    if (courant->matricule == matricule)
    {
      printf("\nMatricule: %d", courant->matricule);
      printf("\nNom: %s", courant->nom);
      printf("\nPrénom: %s", courant->prenom);
      printf("\nTéléphone: %s", courant->telephone);
      printf("\nMail: %s", courant->mail);
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

void menuDeRecherche(listeChainee *liste)
{
  char rep[50];
  ouvrier *courant = liste->premier;

  system("clear");
  printf("\n----------RECHERCHE----------\n");
  if (courant == NULL)
  {
    printf("\nRépertoire vide\n");
  }
  else
  {
    printf("\n(1)\tPar le nom et le prénom\n");
    printf("\n(2)\tPar le matricule\n");
    printf("\n\tChoix: ");
    scanf("%s", rep);
    while (rep[0] != '1' && rep[0] != '2')
    {
      printf("\n Votre réponse: ");
      scanf("%s", rep);
    }
    switch (atoi(rep))
    {
    case 1:
      rechercheParNomEtPrenom(courant);
      break;
    case 2:
      rechercheParMatricule(courant);
      break;
    }
  }
}

listeChainee *retirerOuvrier(listeChainee *liste)
{
  ouvrier *courant = liste->premier;
  ouvrier *next;
  char nom[50], prenom[50], rep[50];
  int trouver = 0;
  system("clear");
  printf("\n----------SUPPRESSION----------\n");
  if (courant == NULL)
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
    if (courant->nom == nom && courant->prenom == prenom)
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
        if (next->nom == nom && next->prenom == prenom && next != NULL)
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
  printf("\n----------MENU PRINCIPAL----------\n");
  printf("\n(1)\tAjouter un ouvrier\n");
  printf("\n(2)\tAfficher la liste des ouvriers\n");
  printf("\n(3)\tRechercher un ouvrier\n");
  printf("\n(4)\tRetirer un ouvrier\n");
  printf("\n(5)\tTerminer\n");
  printf("\nVotre choix: ");
}
