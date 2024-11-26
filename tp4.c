//
// Created by xiangyang on 2024/11/26.
//
#include<stdio.h>
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
    sup_j=date.borneInf-date.borneSup*100;
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


/*****************************************déclaration des fonctions à implémenter*****************************/
//1.Créer un noeud
T_Noeud *creer_noeud(int id_entr, char *objet, T_inter intervalle){
    //1.Créer un noeud
    T_Noeud *N = (T_Noeud *)malloc(sizeof(T_Noeud));
    N->date=intervalle;
    strcpy(N->descrip,objet);
    N->idInter = id_entr;
    N->fisDroite=NULL;
    N->fisGauche=NULL;
    return N;
}

//2.Ajouter une réservation
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

//6.Afficher toutes les réservations présentes dans l’arbre
void afficher_abr(T_Arbre abr){
    if(!abr)
        printf("Arbre est vide");
    else {
        printf("Nom de Entreprise")
        *abr->
    }
    return;
}

//7.Afficher les réservations d’une entreprise
void afficher_entr(T_Arbre abr, int id_entr){

}

//8.Afficher toutes les réservations sur une période
void afficher_periode(T_Arbre abr, T_inter periode){

}


