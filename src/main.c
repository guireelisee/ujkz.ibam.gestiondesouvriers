#include "fonctions/fonctions.h"

int main(int argc, char const *argv[])
{
  int Action, choice;
  listeChainee *repertoire = initialisation();
  char rep[50];
  initialiserRepertoire(repertoire);
  do
  {
    menu();
    scanf("%s", rep);

    Action = atoi(rep);
    switch (Action)
    {
    case 1:
      enregistrerOuvrier(repertoire);
      break;
    case 2:
      afficherRepertoire(repertoire);
      break;
    case 3:
      menuDeRecherche(repertoire);
      break;
    case 4:
      repertoire = retirerOuvrier(repertoire);
      break;
    case 5:
      // choice = Quitter(repertoire);
      break;
    default:
      system("clear");
      printf("\nChoix inexistant !\n");
      break;
    }
    printf("\n\nAppuyer sur Entrée pour revenir au menu ");
    getchar();
  } while (getchar() == '\n' || choice == 1);
  free(repertoire);
  return 0;
}
