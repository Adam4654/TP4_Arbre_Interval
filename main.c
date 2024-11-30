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
        printf("\n2. Afficher les reservations d’une entreprise ");
        printf("\n3. Afficher les reservations sur une periode ");
        printf("\n4. Ajouter une reservation ");
        printf("\n5. Modifier une reservation ");
        printf("\n6. Supprimer une reservation");
        printf("\n7. Quitter");
        printf("\n9. Add DEBUG values in Tree for testing");
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
                /*char dateOK = 0;
                int day, month, formated;

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
                }v0,45*/
                /*v0.5date.borneInf = readDate(1);
                date.borneSup = readDate(0);
                */
                readDate(&date.borneInf, &date.borneSup);
                /*while(!dateOK){ //Borne supperieur
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
                date.borneSup = formated;*/
                printTeteTab();
                afficher_periode(arbre, date);
                viderBuffer ();
                break;
            }

            case '4':{

                T_inter date;
                //char dateOK = 0;
                //int day, month, formated;
                int id = -1;
                char desc[100];
                readDate(&date.borneInf, &date.borneSup);
                //date.borneSup = readDate(0);
/*
                //Intervalle de date
                while(!dateOK){ //Borne inferieur
                    printf("Date de debut (jj/mm): ");
                    //Utilisateur peut diviser les jj/mm ou jj.mm ou jj mm ou jj\nmm ou jj-mm
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
*/

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
            case '5':
                printf("Comment voulez-vous selectioner le evenement pour modifier?\n");
                printf("0. Par donnees exactes primitive (faut etre precis sur intervalle ou entre les dates!)\n");
                printf("1. Par liste complete\n");
                printf("2. Par Intervalle\n");
                printf("3. Par Id de Entreprise\n");
                char choix2 = ' ';
                while (choix2 == ' '){
                    choix2 = getchar();
                    switch(choix2){
                        case '0':{
                            T_inter date;
                            T_inter dateNew;
                            int id = -1;
                            /* V0.5 - old
                            date.borneInf = readDate(1);
                            date.borneSup = readDate(0);
                            */
                            readDate(&date.borneInf, &date.borneSup);
                            while(id<0){
                                printf("\nId de Entreprise: ");
                                scanf(" %d", &id);
                            }
                            printTeteTab();
                            afficher_noeud(rechercher(arbre, date, id));
                            printf("\n - Nouvelle periode - \n");
                            readDate(&dateNew.borneInf, &dateNew.borneSup);
                            modifier(&arbre, id, date, dateNew);
                        }
                            break;
                        default:
                            choix2 = ' ';
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
            case '9':
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
                break;
        }
        printf("\n\n\n");
        viderBuffer();
    }
    return 0;
}

