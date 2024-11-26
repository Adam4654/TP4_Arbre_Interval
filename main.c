#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tp4.h"
#define MAX_MEMORY 5

int main() {
    //========Initialisation=========//
    T_Arbre* arbre = NULL;      //pointeur vers la racine
    // ============= MENU UTILISATEUR ============= */
    char choix = ' ';
    while (choix != '7') {
        printf("\n======================================");
        printf("\n1. Afficher toutes les réservations ");
        printf("\n2. Afficher les réservations d’une entreprise ");
        printf("\n3. Afficher les réservations sur une période ");
        printf("\n4. Ajouter une réservation ");
        printf("\n5. Modifier une réservation ");
        printf("\n6. Supprimer une réservation");
        printf("\n7. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix : ");
        choix = getchar();

        switch (choix) {
            case '1':
                viderBuffer ();
                break;
            case '2':
                viderBuffer ();
                break;
            case '3':
                viderBuffer ();
                break;
            case '4':
                viderBuffer ();
                T_inter date;
                int ID=0;
                char des[100]="no description";
                printf("entrer votre interval,borne Inférieur:");
                scanf("%d",&date.borneInf);
                printf("\t\t\tborne Supérieur:");
                scanf("%d",&date.borneSup);
                if(!valide_interval(date))
                    break;
                printf("\nentrer votre ID entreprise:");
                scanf("%d",&ID);
                printf("\nentrer votre objet:");
                scanf("%s",des);
                //T_Noeud* N=(T_Noeud*)malloc(sizeof(T_Noeud));
                ajouter(arbre,ID,des,date);
                break;
            case '5':
                viderBuffer ();
                break;
            case '6':
                viderBuffer ();
                break;
            default:
                viderBuffer ();
                break;
        }
        printf("\n\n\n");
        viderBuffer();
    }
    return 0;
}

