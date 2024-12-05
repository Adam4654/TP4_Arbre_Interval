#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tp4.h"
#define MAX_MEMORY 5

char leap = 0; //boolean

int main() {
    //========Initialisation=========//
    T_Arbre arbre = NULL;      //pointeur vers la racine

    // ============= MENU UTILISATEUR ============= */
    char choix = ' ';
    int year = 0;

    //Fixe l'anne
    printf("Bienvenue dans votre organisateur de reservations\n");
    while(year<=0){
        printf("Annee: ");
        scanf(" %d", &year);
    }
    viderBuffer();
    if( (year%400 == 0)  || (year%4 == 0 && year%100 != 0)) leap = 1;

    while (choix != '7') {
        printf("\n======================================");
        printf("\n1. Afficher toutes les reservations ");
        printf("\n2. Afficher les reservations d'une entreprise ");
        printf("\n3. Afficher les reservations sur une periode ");
        printf("\n4. Ajouter une reservation ");
        printf("\n5. Modifier une reservation ");
        printf("\n6. Supprimer une reservation");
        printf("\n7. Quitter");
        //printf("\n9. Add DEBUG values in Tree for testing");
        printf("\n======================================");
        printf("\n   Votre choix : ");
        choix = getchar();

        switch (choix) {
            case '1':
                printTeteTab();
                afficher_abr(arbre);
                viderBuffer ();
                break;
            case '2':{
                int ID;
                printf("ID de l'entreprise: ");
                scanf("%d",&ID);
                printTeteTab();
                afficher_entr(arbre,ID);
                viderBuffer ();
                break;
            }
            case '3':{
                T_inter date;

                readDate(&date.borneInf, &date.borneSup);

                printTeteTab();
                afficher_periode(arbre, date);
                viderBuffer ();
                break;
            }

            case '4':{

                T_inter date;

                int id = -1;
                char desc[100];
                readDate(&date.borneInf, &date.borneSup);


                //Id entreprise
                while(id<0){
                    printf("\nId de Entreprise: ");
                    scanf(" %d", &id);
                }

                //Description
                printf("\nDescription: ");
                scanf(" %99[^\n]", desc);   //Inclure les espaces et max 100 character (\0inclus)
                printTeteTab();
                ajouter(&arbre, id, desc, date);

            }

                viderBuffer ();
                break;
            case '5':{
                            T_inter date;
                            T_inter dateNew;
                            int id = -1;
                            T_Noeud* overlap, temp;
                            readDate(&date.borneInf, &date.borneSup);
                            while(id<0){
                                printf("\nId de Entreprise: ");
                                scanf(" %d", &id);
                            }

                            printf("\n - Nouvelle periode - \n");
                            readDate(&dateNew.borneInf, &dateNew.borneSup);

                            if(overlap = rechercher(arbre, dateNew, -1)){ // rechercher sans ID, si une reservation deja contiens l'intervale chevache ou pas
                                printf("Cette Intervale chevauche avec:\n");
                                printTeteTab();
                                afficher_noeud(overlap);
                                printf("\nAucune Operation Effectuer!!!");
                            }else{
                                modifier_old(&arbre, id, date, dateNew);
                            }

                }
                viderBuffer ();
                break;
            case '6':{
                T_inter date;
                int id = -1;
                readDate(&date.borneInf, &date.borneSup);
                while(id<0){
                    printf("\nId de Entreprise: ");
                    scanf(" %d", &id);
                }
                supprimer(&arbre, date, id);
                viderBuffer ();
                break;
            }
            /*case '9':
                printTeteTab();
                T_inter date;
                date.borneInf = formaterDate(2, 7, leap);
                date.borneSup = formaterDate(17, 7, leap);
                ajouter(&arbre, 1010, "Kristi-Joana", date);


                date.borneInf = formaterDate(28, 5, leap);
                date.borneSup = formaterDate(1, 6, leap);
                ajouter(&arbre, 1011, "Maj-Qershor", date);


                date.borneInf = formaterDate(5, 6, leap);
                date.borneSup = formaterDate(5, 6, leap);
                ajouter(&arbre, 1001, "Ditor 5 qershor", date);


                date.borneInf = formaterDate(3, 6, leap);
                date.borneSup = formaterDate(3, 6, leap);
                ajouter(&arbre, 1001, "Ditor 3 Qershor", date);

                date.borneInf = formaterDate(4, 6, leap);
                date.borneSup = formaterDate(4, 6, leap);
                ajouter(&arbre, 1001, "Ditor 4 Qershor", date);

                date.borneInf = formaterDate(2, 6, leap);
                date.borneSup = formaterDate(2, 6, leap);
                ajouter(&arbre, 1001, "Ditor 2 Qershor", date);

                date.borneInf = formaterDate(12, 6, leap);
                date.borneSup = formaterDate(15, 6, leap);
                ajouter(&arbre, 1010, "Mes Qershori", date);

                date.borneInf = formaterDate(20, 8, leap);
                date.borneSup = formaterDate(11, 9, leap);
                ajouter(&arbre, 1011, "Gusht-Shtator", date);

                date.borneInf = formaterDate(21, 9, leap);
                date.borneSup = formaterDate(24, 9, leap);
                ajouter(&arbre, 1010, "Fund Shtatori", date);

                date.borneInf = formaterDate(21, 7, leap);
                date.borneSup = formaterDate(31, 7, leap);
                ajouter(&arbre, 1010, "Fund Korriku", date);

                date.borneInf = formaterDate(15, 9, leap);
                date.borneSup = formaterDate(17, 9, leap);
                ajouter(&arbre, 1010, "Mes Shtatori", date);


                viderBuffer ();
                break;
            default:
                viderBuffer ();
                break;*/
        }
        printf("\n\n\n");
        viderBuffer();
    }
    if(arbre){
        printTeteTab();
        detruire_arbre(&arbre);
    }
    return 0;
}

