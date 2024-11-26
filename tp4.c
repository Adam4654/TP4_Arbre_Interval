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
//    int i = 0;
//    printf("%d",i);
//    while (descrip[i] != '\0') {
//        p->descrip[i] = descrip[i];
//        i++;
//        printf("%d",i);
//    }
//    p->descrip[i] = '\0'; // 末尾添加 '\0'
    p->descrip=(char*)malloc(100*sizeof(char));
    strcpy(p->descrip , descrip);

    p->fisGauche = fisGauche;
    p->fisDroite = fisDroite;

    return;
}


//2.Ajouter une réservation
void ajouter(T_Arbre *abr, int id_entr, char *objet, T_inter intervalle){
    T_Noeud *N = (T_Noeud *)malloc(sizeof(T_Noeud));
    //printf("objet = %s",objet);
    Noeud_constructor(N,intervalle,id_entr,objet,NULL,NULL);
    if(abr==NULL)
        abr=&N;
    else{
        insert_Noeud(abr,N);
    }

    return;
}

void insert_Noeud(T_Arbre *abr, T_Noeud *New) {
    printf("here0");
    printf("here12");
    if ((*abr)==NULL) { // 树非空
        printf("here2");
        *abr = New;
    } else {
        printf("here1");
        if ((*abr)->date.borneInf > New->date.borneInf)
            insert_Noeud(&((*abr)->fisGauche), New);
        else
            insert_Noeud(&((*abr)->fisDroite), New);
    }
}


