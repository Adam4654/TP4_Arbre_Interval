//
// Created by xiangyang on 2024/11/26.
//

#ifndef TP4_TP4_H
#define TP4_TP4_H

typedef struct Intervalle{
    int borneInf;
    int borneSup;
} T_Inter;

typedef struct Noeud{
    T_Inter date;
    int idInter;
    char* descrip;
    struct Noeud* fisGauche;
    struct Noeud* fisDroite;
} T_Noeud;

typedef T_Noeud* T_Arbre;

// fonction qui permet de vider le buffer d'entrée clavier
void viderBuffer ();

#endif //TP4_TP4_H
