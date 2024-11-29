//
// Created by xiangyang on 2024/11/26.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tp4.h"

// fonction qui permet de vider le buffer d'entrée clavier
void viderBuffer (){
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

/*****************************************Fonctions des étudiant**********************************************/
/* old
void Intervalle_constructor(T_inter* p, int borneInf, int borneSup){
    p->borneInf = borneInf;
    p->borneSup = borneSup;
}

void Noeud_constructor( T_Noeud *p,
                        T_inter date,
                        int idInter,
                        char* descrip,
                        struct Noeud* fisGauche,
                        struct Noeud* fisDroite){

    p->date.borneSup = date.borneSup;
    p->date.borneInf = date.borneInf;
    p->idInter = idInter;
    p->descrip=(char*)malloc(100*sizeof(char));
    strcpy(p->descrip , descrip);

    p->fisGauche = fisGauche;
    p->fisDroite = fisDroite;

    return;
}

void insert_Noeud(T_Arbre *abr, T_Noeud *New) {
    if ((*abr)==NULL) { // 树非空
        printf("here2");
        *abr = New;
    } else {
        if ((*abr)->date.borneInf > New->date.borneInf)
            insert_Noeud(&((*abr)->fisGauche), New);
        else
            insert_Noeud(&((*abr)->fisDroite), New);
    }
}

int valide_interval(T_inter date){      //manque les cas de recherce les date de arbre
    //date ne respecte pas les regle
    int inf_m=0,sup_m=0,inf_j=0,sup_j=0;
    inf_m=date.borneInf/100;
    inf_j=date.borneInf-date.borneInf*100;
    sup_m=date.borneSup/100;
    sup_j=date.borneSup-date.borneSup*100;
    if(inf_m<1||inf_m>12){
        printf("date de début n'est pas valide");
        return 0;
    }
    if(sup_m<1||sup_m>12){
        printf("date de fin n'est pas valide");
        return 0;
    }
    switch (inf_m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:    return (1<=inf_j&&inf_j<=31);    break;
        case 4:
        case 6:
        case 9:
        case 11:    return (1<=inf_j&&inf_j<=30);    break;
        case 2:     return (1<=inf_j&&inf_j<=29);    break;
        default:    return 0;
    }
    switch (sup_m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:    return (1<=sup_j&&sup_j<=31);    break;
        case 4:
        case 6:
        case 9:
        case 11:    return (1<=sup_j&&sup_j<=30);    break;
        case 2:     return (1<=sup_j&&sup_j<=29);    break;
        default:    return 0;
    }
    if (date.borneSup<date.borneInf)
        return 0;
    return 1;
}

*/
/*****************************************déclaration des fonctions à implémenter*****************************/
//1.Créer un noeud - **Done**
T_Noeud* creer_noeud(int id_entr, char* objet, T_inter intervalle){
    //1.Créer un noeud
    T_Noeud* N = (T_Noeud*)malloc(sizeof(T_Noeud));

    //Initialisation:
    N->date = intervalle;
    N->descrip = (char*)malloc(sizeof(char) * (strlen(objet)+1));
    strcpy(N->descrip, objet);
    N->idInter = id_entr;
    N->fisDroite = NULL;
    N->fisGauche = NULL;
    return N;
}

//2.Ajouter une réservation
void ajouter(T_Arbre* abr, int id_entr, char* objet, T_inter intervalle){
    //Si l'arbre est vide on ajout notre element
    T_Noeud* newNoeud = creer_noeud(id_entr, objet, intervalle);
    if(*abr == NULL){
        *abr = newNoeud;
        printf("Success!\n");
        afficher_noeud(newNoeud);
        return;
    }


    //Trouver la place est tester si chauvache ou pas
    /**DONE: TESTE DE overlap of max
    trouver pred et succ et tester le sup < inf(succ) et inf > sup(predd)
    */
    T_Noeud* select = *abr;
    T_Noeud* pereSelect = NULL;
    T_Noeud* succ = NULL; //C'est le derniere pere qui a eu notre neoud fis gauche


    char lastOper = 0; //-1 si select fis gauche de pereSelect 1 si select fis droite

    while(select!=NULL){
        pereSelect = select;
        //Passer en gauche
        if( newNoeud->date.borneInf < select->date.borneInf){ //Reste a tester borne superieur
            succ = select;
            select = select->fisGauche;
            lastOper = -1;
        }
        //Passer en droite
        else if( select->date.borneSup < newNoeud->date.borneInf ){ //Reste a tester borne supperieur
            select = select->fisDroite;
            lastOper = 1;
        //Chevauche niv.1 Borne Inferieur
        }else{
            printf("\n \033[31mIntervalle Conflictuelle! Salle deja reserver dans cette creneau d'oraire\033[0m\nChevauche niveau 1 - Date de debut");
            char* temp = NULL;
            char intervalleDate[50];
            strcpy(intervalleDate, "\0");
            temp = deFormaterDate_String(select->date.borneInf);
            strcat(intervalleDate, temp);
            free(temp);
            temp = deFormaterDate_String(select->date.borneSup);
            strcat(intervalleDate, "\t-\t");
            strcat(intervalleDate, temp);
            free(temp);

            printf("\nEvenement: \t%20.20s. | id=%d | %s \n", select->descrip, select->idInter, intervalleDate);

            strcpy(intervalleDate, "\t\0");
            temp = deFormaterDate_String(newNoeud->date.borneInf);
            strcat(intervalleDate, temp);
            printf("\nConflicting: \t%20.20s. | id=%d | \033[31m %s\t\033[0m", newNoeud->descrip, newNoeud->idInter, intervalleDate);
            free(temp);
            temp = deFormaterDate_String(newNoeud->date.borneSup);
            printf("- %s", temp);
            free(temp);
            //Libere moemoire (donne le possibiliter pour update?)
            free_noeud(newNoeud);
            return;
        }
    }
    //Chevauche niv 2 Borne Supperieur
    //Ajouter novelle noeud. Le borne inferieur c'estait deja teste - pas besoin de predecesseur
    if(lastOper == -1){     //Fis gauche
        // Teste Successeur   - le successeur c'est exactement son pere
        if( newNoeud->date.borneSup < pereSelect->date.borneInf){
            pereSelect->fisGauche = newNoeud;
            printf("Success!\n");
            afficher_noeud(newNoeud);
            return;
        }
    }else{  // Fis droite, reste a tester le borneSup < borneInf(succ)
            //Maximum si n'est pas fis droite d'aucune pere == pas de succ
        if( (succ==NULL) || (succ!=NULL && newNoeud->date.borneSup < succ->date.borneInf)){
            pereSelect->fisDroite = newNoeud;
            printf("Success!\n");
            afficher_noeud(newNoeud);
            return;
        }
    }


    //Cas chauvache niveaux 2, borne supperieur dans une autre intervalle:
    printf("\n\033[31mIntervalle Conflictuelle! Salle deja reserver dans cette creneau d'oraire\033[0m\nChevauche niveau 1 - Date de fin");
    char* temp = NULL;
    char intervalleDate[50];
    strcpy(intervalleDate, "\t\0");
    temp = deFormaterDate_String(succ->date.borneInf);
    strcat(intervalleDate, temp);
    free(temp);
    temp = deFormaterDate_String(succ->date.borneSup);
    strcat(intervalleDate, "\t-\t");
    strcat(intervalleDate, temp);
    free(temp);

    printf("\nEvenement: \t%20.20s. | id=%d | %s \n", succ->descrip, succ->idInter, intervalleDate);

    strcpy(intervalleDate, "\0");
    temp = deFormaterDate_String(newNoeud->date.borneInf);
    strcat(intervalleDate, temp);
    printf("\nConflicting: \t%20.20s. | id=%d | %s\t- ", newNoeud->descrip, newNoeud->idInter, intervalleDate);
    free(temp);
    temp = deFormaterDate_String(newNoeud->date.borneSup);
    printf("\033[31m %s\033[0m\n", temp);
    free(temp);
    //Liberer le memoire
    free_noeud(newNoeud);
    return;

}

/* old
void ajouter(T_Arbre *abr, int id_entr, char *objet, T_inter intervalle){
    T_Noeud *N = (T_Noeud *)malloc(sizeof(T_Noeud));
    Noeud_constructor(N,intervalle,id_entr,objet,NULL,NULL);
    if(abr==NULL)
        abr=&N;
    else{
        insert_Noeud(abr,N);
    }
    return;
}
*/
//6.Afficher toutes les réservations présentes dans l’arbre
void afficher_abr(T_Arbre abr){
    if(abr==NULL) {

    }else{
        afficher_abr(abr->fisGauche);
        int inf_m=0,sup_m=0,inf_j=0,sup_j=0;
        inf_m=abr->date.borneInf/100;
        //printf("month1 %d",inf_m);
        inf_j=abr->date.borneInf-inf_m*100;
        //printf("day1 %d",inf_j);
        sup_m=abr->date.borneSup/100;
        //printf("month2 %d",sup_m);
        sup_j=abr->date.borneSup-sup_m*100;
        //printf("day2 %d",sup_j);
        printf("\nID de Entreprise:%d\t",abr->idInter);
        printf("Objet:%s\t",abr->descrip);
        printf("debut de %d/%d, fin de %d/%d",inf_m,inf_j,sup_m,sup_j);
        afficher_abr(abr->fisDroite);
    }
    return;
}

//7.Afficher les réservations d’une entreprise
void afficher_entr(T_Arbre abr, int id_entr){
    if(abr==NULL) {

    }else{
        int inf_m=0,sup_m=0,inf_j=0,sup_j=0;
        inf_m=abr->date.borneInf/100;
        //printf("month1 %d",inf_m);
        inf_j=abr->date.borneInf-inf_m*100;
        //printf("day1 %d",inf_j);
        sup_m=abr->date.borneSup/100;
        //printf("month2 %d",sup_m);
        sup_j=abr->date.borneSup-sup_m*100;
        //printf("day2 %d",sup_j);
        afficher_entr(abr->fisGauche,id_entr);
        if (abr->idInter==id_entr) {
            printf("\nNumero de Entreprise:%d\t", abr->idInter);
            printf("Nom de Entreprise:%s\t", abr->descrip);
            printf("debut de %d/%d, fin de %d/%d", inf_m, inf_j, sup_m, sup_j);
        }
        afficher_entr(abr->fisDroite,id_entr);
    }
    return;
}

//8.Afficher toutes les réservations sur une période
void afficher_periode(T_Arbre abr, T_inter periode){
    if(abr==NULL) {

    }else{
        if (abr->date.borneInf>periode.borneInf)
            afficher_periode(abr->fisGauche,periode);
        if (abr->date.borneSup<periode.borneInf||abr->date.borneInf>periode.borneSup){
        }
        else {
            int inf_m=0,sup_m=0,inf_j=0,sup_j=0;
            inf_m=abr->date.borneInf/100;
            //printf("month1 %d",inf_m);
            inf_j=abr->date.borneInf-inf_m*100;
            //printf("day1 %d",inf_j);
            sup_m=abr->date.borneSup/100;
            //printf("month2 %d",sup_m);
            sup_j=abr->date.borneSup-sup_m*100;
            //printf("day2 %d",sup_j);
            printf("\nNumero de Entreprise:%d\t", abr->idInter);
            printf("Nom de Entreprise:%s\t", abr->descrip);
            printf("debut de %d/%d, fin de %d/%d", inf_m, inf_j, sup_m, sup_j);
        }
        if (abr->date.borneInf<periode.borneSup)
            afficher_periode(abr->fisDroite,periode);
    }
    return;
}


/** Fonctions Supplementaire*/
int formaterDate(int day, int month, char isLeap){
    int maxDay = 0;
    //Tester la validite de mois
    if(month>12 || month<1) return 0;

    //Tester la validite de jour
    switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            maxDay = 31;
            break;
        case 2:
            if(isLeap)  maxDay = 29;
            else        maxDay = 28;
            break;
        default:
            maxDay = 30;
    }
    if(day<1 || day>maxDay) return 0;

    return month*100+day;
}

void deFormater_DayMonth(char day[3], char month[3], int date){
    char temp[5];
    sprintf(temp, "%d\0", date);
    if((int)strlen(temp) == 4){  // if MMDD\0
        strncpy(month, temp, 2); //skip MM
        strncpy(day, &temp[2], 3); //Je ne sais pas mais si je copie seul 2 il n'ajout pas \0
    }else{
        month[0] = '0';             // if -MDD\0
        month[1]= temp[0];         //skip M
        strncpy(day, &temp[1], 3);
    }
    month[2] = '\0';
    day[2] = '\0';
    return;
}

char* deFormaterDate_String(int date){
    char day[3];
    char mois[3];
    char* dataString = malloc(sizeof(char)*15);
    deFormater_DayMonth(day, mois, date);
    sprintf(dataString, "%s/%s", day, mois);
    return dataString;
}

void afficher_noeud(T_Noeud* N){
    char day_string_debut[3], month_string_debut[3], date_string[5];
    char day_string_fin[3], month_string_fin[3];

    deFormater_DayMonth(day_string_debut, month_string_debut, N->date.borneInf);
    deFormater_DayMonth(day_string_fin, month_string_fin, N->date.borneSup);


    printf("Ajoutee: %d. %s. %s/%s - %s/%s", N->idInter, N->descrip,\
        day_string_debut, month_string_debut, day_string_fin, month_string_fin);
    return;
}

void free_noeud(T_Noeud* N){
    free(N->descrip);
    free(N);
}
