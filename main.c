#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tp4.h"
#define MAX_MEMORY 5

int main() {
    //========Initialisation=========//
    T_Arbre arbre = NULL;      //pointeur vers la racine

    // ============= MENU UTILISATEUR ============= */
    char choix = ' ';
    int year = 0;
    char leap = 0; //boolean
    //Fixe l'anne
    printf("Bienvenue dans votre organisateur de reservations\n");
    while(year<=0){
        printf("Anne: ");
        scanf(" %d", &year);
    }
    viderBuffer();
    if( (year%400 == 0)  || (year%4 == 0 && year%100 != 0)) leap = 1;

    while (choix != '7') {
        printf("\n======================================");
        printf("\n1. Afficher toutes les reservations ");
        printf("\n2. Afficher les reservations d’une entreprise ");
        printf("\n3. Afficher les reservations sur une periode ");
        printf("\n4. Ajouter une reservation ");
        printf("\n5. Modifier une reservation ");
        printf("\n6. Supprimer une reservation");
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
            case '4':{

                T_inter date;
                char dateOK = 0;
                int day, month, formated;
                int id = -1;
                char desc[100];

                //Intervalle de date
                while(!dateOK){ //Borne inferieur
                    printf("Date de debut (jj/mm): ");
                    //Utilisateur peut diviser les jj/mm ou jj.mm ou jj mm ou jj\nmm
                    scanf(" %d%*[./ -\n]%d", &day, &month);
                    printf("\nDebut - Jour: %d  Mois: %d", day, month);
                    if(formated = formaterDate(day, month, leap)){ //valider & convert date
                        dateOK = 1;
                    }else{
                        printf(" \t\t--Invalide!\n");
                    }
                }
                date.borneInf = formated;

                dateOK = 0;
                while(!dateOK){ //Borne supperieur
                    printf("\nDate de fin (jj/mm): ");
                    //Utilisateur peut diviser les jj/mm ou jj.mm ou jj mm ou jj\nmm
                    scanf(" %d%*[./ -\n]%d", &day, &month);
                    printf("\nFin - Jour: %d  Mois: %d", day, month);
                    if(formated = formaterDate(day, month, leap)){
                        dateOK = 1;
                        if(date.borneInf>formated){ //Si la date valide en existance verifier
                            dateOK = 0;                 // si plus grand que la date debut
                            printf("\nDate de debut <= Date de fin!\n");
                        }
                    }else{
                        printf(" \t\t--Invalide!\n");
                    }
                }
                date.borneSup = formated;

                //Id entreprise
                while(id<0){
                    printf("\nId de Entreprise: ");
                    scanf(" %d", &id);
                }

                //Description
                printf("\nDescription: ");
                scanf(" %s", desc);

                ajouter(&arbre, id, desc, date);

            }
/*             printf("\t\t\tborne Supérieur:");
               scanf("%d",&date.borneSup);
                if(!valide_interval(date))
                    break;
                printf("\nentrer votre ID entreprise:");
                scanf("%d",&ID);
                printf("\nentrer votre objet:");
                scanf("%s",des);
                //T_Noeud* N=(T_Noeud*)malloc(sizeof(T_Noeud));
                ajouter(arbre,ID,des,date);
                */
                viderBuffer ();
                break;
            }
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

