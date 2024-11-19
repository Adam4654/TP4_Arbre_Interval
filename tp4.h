#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

typedef struct Intervalle{
    int borneInf;
    int borneSup;
} T_Inter;

typedef struct Noeud{
    T_Inter date;
    int idInter;
    char* descrip;
    T_Noeud* fisGauche;
    T_Noeud* fisDroite;
} T_Noeud;

typedef T_Noeud* T_Arbre;


#endif // TP4_H_INCLUDED
