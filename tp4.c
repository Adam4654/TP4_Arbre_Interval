//
// Created by xiangyang on 2024/11/26.
//
#include<stdio.h>
#include <string.h>
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
    p->date = date;
    p->idInter = idInter;
    strcpy(p->descrip , descrip);
    p->fisGauche = fisGauche;
    p->fisDroite = fisDroite;
}




