#include "fonctions/fonctions.h"

int main(int argc, char const *argv[])
{
  char action[1];
  listeChainee *repertoire = initialiserRepertoire();
  do
  {
    menu();
    scanf("%s", action);
    switch (atoi(action))
    {
    case 1:
      enregistrerOuvrier(repertoire);
      sauvegardeFichier(repertoire);
      break;
    case 2:
      afficherRepertoire(repertoire);
      break;
    case 3:
      genre(repertoire);
      break;
    case 4:
      rechercheParNomEtPrenom(repertoire);
      break;
    case 5:
      repertoire = retirerOuvrier(repertoire);
      sauvegardeFichier(repertoire);
      break;
    case 6:
      exit(EXIT_SUCCESS);
      break;
    default:
      system("clear");
      printf("\nChoix inexistant !\n");
      break;
    }
    printf("\n\nAppuyer sur Entrée pour revenir au menu ");
    getchar();
  } while (getchar() == '\n');
  free(repertoire);
  return 0;
}
