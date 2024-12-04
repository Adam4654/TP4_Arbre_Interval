//
// Created by xiangyang on 2024/11/26.
//

#ifndef TP4_TP4_H
#define TP4_TP4_H

typedef struct Intervalle{
    int borneInf;
    int borneSup;
} T_inter;

typedef struct Noeud{
    T_inter date;
    int idInter;
    char* descrip;
    struct Noeud* fisGauche;
    struct Noeud* fisDroite;
} T_Noeud;

typedef T_Noeud* T_Arbre;

// fonction qui permet de vider le buffer d'entrée clavier
void viderBuffer ();

/*****************************************Fonctions des étudiant**********************************************/
/*void Intervalle_constructor(T_inter *p, int borneInf,int borneSup);

void Noeud_constructor( T_Noeud *p,
                        T_inter date,
                        int idInter,
                        char* descrip,
                        struct Noeud* fisGauche,
                        struct Noeud* fisDroite);*/

void insert_Noeud(T_Arbre *abr,T_Noeud *New);

int valide_interval(T_inter);
/*****************************************déclaration des fonctions à implémenter*****************************/

//1.Créer un noeud
T_Noeud *creer_noeud(int id_entr, char *objet, T_inter intervalle);

//2.Ajouter une réservation
void ajouter(T_Arbre *abr, int id_entr, char *objet, T_inter intervalle);

//3.Rechercher une réservation
T_Noeud *rechercher(T_Arbre abr, T_inter intervalle, int id_entr);

//4.Supprimer une réservation
void supprimer(T_Arbre *abr, T_inter intervalle, int id_entr);

//5.Modifier les dates d’une réservation
void modifier_old(T_Arbre* abr, int id_entr, T_inter actuel, T_inter nouveau);
void modifier(T_Arbre abr, int id_entr, T_inter actuel, T_inter nouveau);
//CHANGED PROTOTYPE

//6.Afficher toutes les réservations présentes dans l’arbre
void afficher_abr(T_Arbre abr);

//7.Afficher les réservations d’une entreprise
void afficher_entr(T_Arbre abr, int id_entr);

//8.Afficher toutes les réservations sur une période
void afficher_periode(T_Arbre abr, T_inter periode);

//9. Détruire tous les nœuds d’un arbre binaire :
void detruire_arbre(T_Arbre *abr);


/******Fonction Supplementaire*****/
int formaterDate(int, int, char); //Return la date formater MMDD  0 si date non valide
void deFormater_DayMonth(char [3], char [3], int date); //Recuperer le jour et le mois de format MMDD
char* deFormaterDate_String(int date); //retourner date deformater dd/mm
void free_noeud(T_Noeud*);
void afficher_noeud(T_Noeud*); //print les data d'un observation
void printTeteTab();
void readDate(int* debut, int* fin); //0 for born superiuer, 1 for born inferiuer
#endif //TP4_TP4_H
