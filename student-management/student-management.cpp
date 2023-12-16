#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant {
    char nom[100];
    int age;
} Etudiant;

typedef struct cellule {
    Etudiant etud;
    struct cellule* suivant;
} cellule;

typedef cellule* pile;

void creer_pile(pile* p) {
    *p = NULL;
}

int vide_pile(pile p) {
    return (p == NULL);
}

Etudiant* sommet_pile(pile p) {
    return &(p->etud);
}

void empiler_pile(pile* p, Etudiant etudiant) {
    cellule* nouveaucellule = (cellule*)malloc(sizeof(cellule));
    nouveaucellule->etud = etudiant;
    nouveaucellule->suivant = *p;
    *p = nouveaucellule;
}

void depiler_pile(pile* p) {
    if (vide_pile(*p)) {
        printf("La pile est vide.\n");
        return;
    }

    cellule* sommet = *p;
    *p = sommet->suivant;
    free(sommet);
}

pile copie_pile(pile p) {
    pile pCopie = NULL;
    pile pInverse = NULL;

    while (!vide_pile(p)) {
        Etudiant etudiant = *(sommet_pile(p));
        empiler_pile(&pInverse, etudiant);
        depiler_pile(&p);
    }

    while (!vide_pile(pInverse)) {
        Etudiant etudiant = *(sommet_pile(pInverse));
        empiler_pile(&p, etudiant);
        empiler_pile(&pCopie, etudiant);
        depiler_pile(&pInverse);
    }

    return pCopie;
}

pile inverser_pile(pile p) {
    pile pileInverse = NULL;
    pile pileTemp = NULL;

    while (!vide_pile(p)) {
        Etudiant etudiant = *(sommet_pile(p));
        empiler_pile(&pileInverse, etudiant);
        empiler_pile(&pileTemp, etudiant);
        depiler_pile(&p);
    }

    while (!vide_pile(pileTemp)) {
        Etudiant etudiant = *(sommet_pile(pileTemp));
        empiler_pile(&p, etudiant);
        depiler_pile(&pileTemp);
    }

    return pileInverse;
}

int taille_pile(pile p) {
    int taille = 0;
    pile pTemp = NULL;

    while (!vide_pile(p)) {
        Etudiant etudiant = *(sommet_pile(p));
        empiler_pile(&pTemp, etudiant);
        depiler_pile(&p);
        taille++;
    }

    while (!vide_pile(pTemp)) {
        Etudiant etudiant = *(sommet_pile(pTemp));
        empiler_pile(&p, etudiant);
        depiler_pile(&pTemp);
    }

    return taille;
}

void afficher_etudiant(Etudiant etudiant) {
    printf("Nom: %s, Age: %d\n", etudiant.nom, etudiant.age);
}

void afficher_pile(pile p) {
    pile pTemporaire = NULL;
    while (!vide_pile(p)) {
        Etudiant etudiant = *(sommet_pile(p));
        afficher_etudiant(etudiant);
        empiler_pile(&pTemporaire, etudiant);
        depiler_pile(&p);
    }

    while (!vide_pile(pTemporaire)) {
        Etudiant etudiant = *(sommet_pile(pTemporaire));
        empiler_pile(&p, etudiant);
        depiler_pile(&pTemporaire);
    }
}
void permuter_premier_dernier(pile* p) {
    if (vide_pile(*p)) {
        printf("La pile est vide.\n");
        return;
    }

    if ((*p)->suivant == NULL) {
        printf("La pile ne contient qu'un seul élément.\n");
        return;
    }

    pile pileTemp = NULL;
    cellule* premier = *p;
    cellule* dernier = *p;
    cellule* avantDernier = NULL;

    
    while (dernier->suivant != NULL) {
        avantDernier = dernier;
        dernier = dernier->suivant;
    }

    avantDernier->suivant = premier;
    dernier->suivant = premier->suivant;
    premier->suivant = NULL;
    *p = dernier;
}


void saisir_etudiant(Etudiant* etudiant) {
    printf("Saisir le nom de l'etudiant: ");
    scanf("%s", etudiant->nom);
    printf("Saisir l'age de l'etudiant: ");
    scanf("%d", &(etudiant->age));
}

int main() {
    pile maPile;
    creer_pile(&maPile);

    int choix = 0;

    while (1) {
        printf("\nchoix Menu des etudiantes \n");
        printf("1. Empiler un Etudiant\n");
        printf("2. Depiler un Etudiant\n");
        printf("3. Afficher la pile\n");
        printf("4. Copier la pile\n");
        printf("5. Inverser la pile\n");
        printf("6. Permuter le premier et le dernier element de la pile\n");
        printf("7. Obtenir la taille de la pile\n");
        printf("8. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                Etudiant etudiant;
                saisir_etudiant(&etudiant);
                empiler_pile(&maPile, etudiant);
                printf("Etudiant empile.\n");
                break;
            }
            case 2: {
                depiler_pile(&maPile);
                printf("Etudiant depile.\n");
                break;
            }
            case 3: {
                printf("\nPile:\n");
                afficher_pile(maPile);
                break;
            }
            case 4: {
                pile pileCopie = copie_pile(maPile);
                printf("\nCopie de la pile:\n");
                afficher_pile(pileCopie);
                break;
            }
            case 5: {
                pile pileInverse = inverser_pile(maPile);
                printf("\nPile inversee:\n");
                afficher_pile(pileInverse);
                break;
            }
            case 6: {
                permuter_premier_dernier(&maPile);
                printf("Permutation effectuee .\n");
                break;
            }
            case 7: {
                int taille = taille_pile(maPile);
                printf("Taille de la pile: %d\n", taille);
                break;
            }
            case 8: {
                
                while (!vide_pile(maPile)) {
                    depiler_pile(&maPile);
                }
                printf("Programme terminé.\n");
                return 0;
            }
            default: {
                printf("Choix invalide Veuillez ressayer.\n");
                break;
            }
        }
    }
}
