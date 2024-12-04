//
// Created by xiangyang on 2024/11/26.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tp4.h"

extern leap;

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
T_Noeud* creer_noeud(int id_entr, char* objet, T_inter intervalle){     //teste pas la date
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
        afficher_noeud(newNoeud);
        printf("\t\tSuccess! 0");
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
            afficher_noeud(newNoeud);
            printf("\t\tSuccess! G");
            return;
        }
    }else{  // Fis droite, reste a tester le borneSup < borneInf(succ)
            //Maximum si n'est pas fis droite d'aucune pere == pas de succ
        if( (succ==NULL) || (succ!=NULL && newNoeud->date.borneSup < succ->date.borneInf)){
            pereSelect->fisDroite = newNoeud;
            afficher_noeud(newNoeud);
            printf("\t\tSuccess! D");
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

// 3.Rechercher une réservation :

T_Noeud* rechercher(T_Arbre abr, T_inter intervalle, int id_entr){
    T_Noeud* select = abr;
    //Intervalle pas forcement exacte a reservation. Il SUFFIT DE ETRE CONTENU en DEDANS intervale de reservation
    while(select != NULL){
        //Si intervale furnit dans une reservation
        if( (intervalle.borneInf >= select->date.borneInf) && (intervalle.borneSup <= select->date.borneSup)){
            if(id_entr == select->idInter || id_entr == -1){ //Si id furnit correspend au intervale trouver
                return select;
            }else{                          //Si id furnit ne correspend pas
                printf("\nIntervalle trouver, mais pas de idInter = %5d. \nVouliez-vous dire idInterprise: %5d ?", id_entr, select->idInter);
                return NULL;
            }
        }
        //Si intervale a gauche
        if(intervalle.borneInf < select->date.borneInf){
            select = select->fisGauche;
        //Si intervale a droite
        }else if(select->date.borneSup < intervalle.borneInf){
            select = select->fisDroite;
        }else{  //Ni droite ni gauche c-a-d intervale entre 2 evenements differents:
            return NULL;
        }
    }
    return select;
}


//4.Supprimer une réservation
void supprimer(T_Arbre *abr, T_inter intervalle, int id_entr){
    if(abr == NULL)  return;  //Pas une adresse d'arbre
    if(*abr == NULL) return; //Arbre vide
    T_Noeud* select = *abr;
    T_Noeud* pereSelect = NULL;
    char trouver = 0;
    //Trouver l'element a supprimer:
    while( (select != NULL) && (!trouver)){
          //Si on a trouver le interval (exacte ou une partie dedans):
        if( (intervalle.borneInf >= select->date.borneInf) && (intervalle.borneSup <= select->date.borneSup)){
            if(id_entr == select->idInter){ //Si le entreprise corespend biensl=,
                trouver = 1;
                continue;
            }else{                          //Si entreprise ne corespend pas
                printf("\nIntervalle trouver, mais pas de idInter = %5d. \nVouliez-vous dire idInterprise: %5d ?", id_entr, select->idInter);
                return;
            }
        }
            //Si pas encore trouver
        pereSelect = select;
        //Si intervale a gauche
        if(intervalle.borneInf < select->date.borneInf){
            select = select->fisGauche;
        //Si intervale a droite
        }else if(select->date.borneSup < intervalle.borneInf) {
            select = select->fisDroite;
        }else{ //Intervale entre 2 intervalles borne inferiur dans le intervale de select mais borne superieur en dehors
            printf("\nIntervalle innvalide!");
            return;
        }
    }
    //Discuter sur element:
    if(!trouver){ //Parcourir et non trouver Equivalant a select != NULL
        printf("\nReservation n'existe pas. Aucun action effectuer.");
        return;
    }
    //Suprimer element, les 3 cas (1 fils gauche/droite, aucune fis, 2 fils) * 2 opsion(racine ou pas)
    if(select->fisDroite == NULL && select->fisGauche == NULL){ //aucun fils
        if(pereSelect){ //element pas racine
            if(pereSelect->fisDroite == select){ //si fils droit
                pereSelect->fisDroite = NULL;
            }else{                               //si fils gauche
                pereSelect->fisGauche = NULL;
            }
        }else{ // Elements racine et sans fils
            *abr = NULL;
        }

    //Explusive OR-bitwise, si 1 null et l'autre pas
    }else if( (select->fisDroite == NULL) ^ (select->fisGauche == NULL) ){
        if(pereSelect){ //element pas racine
            if(pereSelect->fisDroite == select){ //si fils droit
                if(select->fisDroite != NULL){      //si il ya fils droite
                    pereSelect->fisDroite = select->fisDroite;
                }else{                              //sinon il y a fils gauche
                    pereSelect->fisDroite = select->fisGauche;
                }
            }else{                               //si fils gauche
                if(select->fisDroite != NULL){      //si il ya fils droite
                    pereSelect->fisGauche = select->fisDroite;
                }else{                              //sinon il y a fils gauche
                    pereSelect->fisGauche = select->fisGauche;
                }
            }
        }else{ //Si element racine et avec 1 fis on change la racine avec son fis soit droite soit gauche
            *abr = (select->fisDroite)? select->fisDroite : select->fisGauche;
        }

    //Element possede deux fils, faut le replacer avec leur ici: predecesseur (ou successeur)
    }else{
        T_Noeud* succ = select->fisDroite; //le plus gauche de son fis droite
        while(succ->fisGauche!=NULL){
            succ = succ->fisGauche;
        }
            //copie de successeur et inheriter les nouveaux fils
        T_Noeud* remplacement = creer_noeud(succ->idInter, succ->descrip, succ->date);
        supprimer(&select, succ->date, succ->idInter); //supprimer le element copier, mettre a jour l'arbre
        //remplacement->fisDroite = (succ == select->fisDroite)? select->fisDroite->fisDroite : select->fisDroite; //ne pas copie soi meme
        remplacement->fisDroite = select->fisDroite;
        remplacement->fisGauche = select->fisGauche;
        afficher_noeud(remplacement); printf(" (\033[32m+\033[0m)\t\t\033[32mReAjouted!\033[0m\n");
        if(pereSelect){ //element pas racine
            if(pereSelect->fisDroite == select){ //si fils droit
                pereSelect->fisDroite = remplacement;
            }else{                               //si fils gauche
                pereSelect->fisGauche = remplacement;
            }
        }else{ // Elements racine et avec 2 fils
            *abr = remplacement;
        }
    }
    printTeteTab();
    //printf("\033[31m-\033[0m");
    afficher_noeud(select); printf(" (\033[31m-\033[0m)\t\t\033[31m Suprimer!\033[0m\n");
    //printf("\033[0m\n");
    free_noeud(select);

/*    if(toDelete = rechercher(racine, intervalle, id_entr)){
        //Recherer le pere en meme temps (pas possible de utiliser directement rechercher car on dois recommencer le recherche pour le parent.
        // comme ca on peut cree notre algo plus efficace
        free_noeud(toDelete);
    }else{
        printf("\nCette reservation n'existe pas! Aucune action effectuer.");
    }
    return;*/
}
// 5. Modifier les dates d’une réservation :
void modifier_old(T_Arbre* abr, int id_entr, T_inter actuel, T_inter nouveau){//PAS LE PLUS OPTIMALE
    // CAR 2 fois chercher //Essayer de ne pas ganger le prototype

    if(abr == NULL) return;
    if(*abr == NULL){
        printf("\nAucun element!");
        return;
    }

    T_Noeud* selected = rechercher(*abr, actuel, id_entr);
    //Noeud n'existe pas
    if(!selected){
      printf("\n Aucun element trouver pour modifier");
      return;
    }
    //Neoud existe
        //Si les borne nouvelle ne depasse pas leur valeurs originel, pas besoins de changer la structure, juste mettre a jour
    if(nouveau.borneInf>= selected->date.borneInf && nouveau.borneSup<= selected->date.borneSup){
        selected->date.borneInf = nouveau.borneInf;
        selected->date.borneSup = nouveau.borneSup;
        printf("\nMis a jour!");
        return;
    }
    //Si les borne en dehors d'originale, probeleme de chevauche (soi change structure soi non) \
        mais plus facile (lisible) et en meme complexite on va reajouter l'element
    char disc[100];
    strcpy(disc, selected->descrip);
    printf("\n");
    supprimer(abr, selected->date, selected->idInter);
    ajouter(abr, id_entr, disc, nouveau);
    return;
}

void modifier(T_Arbre abr, int id_entr, T_inter actuel, T_inter nouveau){
    // original prototype, abr est une pointeur meme si une pointeur de arbre en realiter et pas de noeud
    //On le stock dans le bonne type de double pointeur de noeud == pointeur de arbre,
    //juste quand'on passe le argument adresse d'arbre (T_Arbre*) vers le parametre (T_Arbre) puis en le covert
    T_Arbre* abr1 = (T_Arbre*) abr;
    if(abr1 == NULL) return;
    if(*abr1 == NULL){
        printf("\nAucun element!");
        return;
    }

    T_Noeud* selected = rechercher(*abr1, actuel, id_entr);
    //Noeud n'existe pas
    if(!selected){
      printf("\n Aucun element trouver pour modifier");
      return;
    }
    //Neoud existe
        //Si les borne nouvelle ne depasse pas leur valeurs originel, pas besoins de changer la structure, juste mettre a jour
    if(nouveau.borneInf>= selected->date.borneInf && nouveau.borneSup<= selected->date.borneSup){
        selected->date.borneInf = nouveau.borneInf;
        selected->date.borneSup = nouveau.borneSup;
        printf("\nMis a jour!");
        return;
    }
    //Si les borne en dehors d'originale, probeleme de chevauche (soi change structure soi non) \
        mais plus facile (lisible) et en meme complexite on va reajouter l'element
    char disc[100];
    strcpy(disc, selected->descrip);
    printf("\n");
    supprimer(abr1, selected->date, selected->idInter);
    ajouter(abr, id_entr, disc, nouveau);
    return;
}

//6.Afficher toutes les réservations présentes dans l’arbre
void afficher_abr(T_Arbre abr){
    if(abr==NULL) {

    }else{
        afficher_abr(abr->fisGauche);
        /*int inf_m=0,sup_m=0,inf_j=0,sup_j=0;
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
        */
        afficher_noeud(abr);
        afficher_abr(abr->fisDroite);
    }
    return;
}

//7.Afficher les réservations d’une entreprise
void afficher_entr(T_Arbre abr, int id_entr){
    if(abr==NULL) {

    }else{
        /*
        int inf_m=0,sup_m=0,inf_j=0,sup_j=0;
        inf_m=abr->date.borneInf/100;
        //printf("month1 %d",inf_m);
        inf_j=abr->date.borneInf-inf_m*100;
        //printf("day1 %d",inf_j);
        sup_m=abr->date.borneSup/100;
        //printf("month2 %d",sup_m);
        sup_j=abr->date.borneSup-sup_m*100;
        //printf("day2 %d",sup_j);
        */
        afficher_entr(abr->fisGauche, id_entr);
        if (abr->idInter==id_entr) {
            afficher_noeud(abr);
            /*
            printf("\nNumero de Entreprise:%d\t", abr->idInter);
            printf("Nom de Entreprise:%s\t", abr->descrip);
            printf("debut de %d/%d, fin de %d/%d", inf_m, inf_j, sup_m, sup_j);
            */
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
            /*
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
            */
            afficher_noeud(abr);
        }
        if (abr->date.borneInf<periode.borneSup)
            afficher_periode(abr->fisDroite,periode);
    }
    return;
}

//9. Détruire tous les nœuds d’un arbre binaire :
void detruire_arbre(T_Arbre *abr){
        //Passage Post Fix
    if(abr == NULL) return;
    if(*abr == NULL) return;
    detruire_arbre(&((*abr)->fisGauche));
    detruire_arbre(&((*abr)->fisDroite));
    afficher_noeud(*abr); printf(" (\033[31m-\033[0m)\t\t\033[32m Liberer!\033[0m");
    free_noeud(*abr);

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
    if(N == NULL){
        printf("\nNULL - NON-Trouver");
        return;
    }
    char day_string_debut[3], month_string_debut[3], date_string[5];
    char day_string_fin[3], month_string_fin[3];

    deFormater_DayMonth(day_string_debut, month_string_debut, N->date.borneInf);
    deFormater_DayMonth(day_string_fin, month_string_fin, N->date.borneSup);


    printf("\n%9d | %-30.30s | %s/%s - %s/%s", N->idInter, N->descrip,\
        day_string_debut, month_string_debut, day_string_fin, month_string_fin);
    return;
}

void free_noeud(T_Noeud* N){
    free(N->descrip);
    free(N);
}




void printTeteTab(){
    //printf("%d\n", leap);
    printf("\033[33m%9s | %26s %4s| %9s\033[0m", "id_Inter", "Description_Evenement", " ", "Date");
}

void readDate(int* debut, int* fin){
    char dateOK = 0;
    int day, month, formated;
    viderBuffer();
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
    *debut = formated;

    dateOK = 0;
    while(!dateOK){ //Borne supperieur
        printf("\nDate de fin (jj/mm): ");
        //Utilisateur peut diviser les jj/mm ou jj.mm ou jj mm ou jj\nmm
        scanf(" %d%*[./ -\n]%d", &day, &month);
        printf("\nFin - Jour: %d  Mois: %d\n", day, month);
        if(formated = formaterDate(day, month, leap)){
            dateOK = 1;
            if(*debut>formated){ //Si la date valide en existance verifier
                dateOK = 0;                 // si plus grand que la date debut
                printf("\n\033[31mDate de debut <= Date de fin!\033[0m\n");
            }
        }else{
            printf(" \t\t--Invalide!\n");
        }
    }
    *fin = formated;
    return;
}


