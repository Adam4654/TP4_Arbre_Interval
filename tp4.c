//
// Created by xiangyang on 2024/11/26.
//
#include<stdio.h>
// fonction qui permet de vider le buffer d'entrée clavier
void viderBuffer (){
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


#include "tp4.h"
