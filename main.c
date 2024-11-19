#include <stdio.h>
#include <string.h>

#define MAX_MEMORY 5

int main() {
    //========Initialisation=========//
    //Creation d'un memoire (liste de matrices)
    // ============= MENU UTILISATEUR ============= */
    char choix = ' ';
    while (choix != '7') {
        printf("\n======================================");
        printf("\n1. Afficher toutes les réservations ");
        printf("\n2. Afficher les réservations d’une entreprise ");
        printf("\n3. Afficher les réservations sur une période ");
        printf("\n4. Ajouter une réservation ");
        printf("\n5. Modifier une réservation ");
        printf("\n6. Supprimer une réservation");
        printf("\n7. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();

        switch (choix) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            default:
                break;
        }
        printf("\n\n\n");
        //viderBuffer();
    }
    return 0;
}

