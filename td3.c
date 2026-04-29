//Avant de commencer les exercices, nous définissons la structure d'un nœud :
typedef struct Element {
    int valeur;
    struct Element *suivant;
} Element, *Liste;

3.1 Exercice 1 : Création d'une liste
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Liste creerListeAleatoire() {
    Liste L = NULL;
    srand(time(NULL)); // Initialisation du générateur aléatoire
    for (int i = 0; i < 100; i++) {
        Element *nouveau = malloc(sizeof(Element));
        nouveau->valeur = rand() % 100;
        nouveau->suivant = L; // Insertion en tête
        L = nouveau;
    }
    return L;
}
3.2 Exercice 2 : Recherche de valeur
int rechercherValeur(Liste L, int val) {
    Liste courant = L;
    while (courant != NULL) {
        if (courant->valeur == val) return 1; // Trouvé
        courant = courant->suivant;
    }
    return 0; // Non trouvé
}
3.3 Exercice 3 : Suppression du minimum
Liste supprimerMin(Liste L) {
    if (L == NULL) return NULL;

    // 1. Trouver la valeur min
    int min = L->valeur;
    Liste courant = L;
    while (courant != NULL) {
        if (courant->valeur < min) min = courant->valeur;
        courant = courant->suivant;
    }

    // 2. Supprimer la première occurrence du min
    Liste prec = NULL;
    courant = L;
    while (courant != NULL && courant->valeur != min) {
        prec = courant;
        courant = courant->suivant;
    }

    if (prec == NULL) { // Le min est en tête
        L = L->suivant;
    } else {
        prec->suivant = courant->suivant;
    }
    free(courant);
    return L;
}
3.4 Exercice 4 : Fusion alternée
Liste fusionnerAlterné(Liste A, Liste B) {
    Liste C = NULL, dernier = NULL;
    Liste pA = A, pB = B;

    while (pA != NULL || pB != NULL) {
        // Ajouter de A si disponible
        if (pA != NULL) {
            Element *nouv = malloc(sizeof(Element));
            nouv->valeur = pA->valeur;
            nouv->suivant = NULL;
            if (C == NULL) C = nouv; else dernier->suivant = nouv;
            dernier = nouv;
            pA = pA->suivant;
        }
        // Ajouter de B si disponible
        if (pB != NULL) {
            Element *nouv = malloc(sizeof(Element));
            nouv->valeur = pB->valeur;
            nouv->suivant = NULL;
            if (C == NULL) C = nouv; else dernier->suivant = nouv;
            dernier = nouv;
            pB = pB->suivant;
        }
    }
    return C;
}
3.5 Exercice 5 : Destruction d'une liste
void detruireListe(Liste L) {
    Liste temp;
    while (L != NULL) {
        temp = L;
        L = L->suivant; // On avance avant de libérer
        free(temp);
    }
}
3.6 Exercice 6 : Piles (LIFO - Last In First Out)
typedef struct Element {
    int valeur;
    struct Element *suivant;
} Element, *Pile;

// push : Empiler (insertion en tête)
void push(Pile *P, int x) {
    Element *nouv = malloc(sizeof(Element));
    nouv->valeur = x;
    nouv->suivant = *P;
    *P = nouv;
}

// pop : Dépiler (retrait en tête)
int pop(Pile *P) {
    if (*P == NULL) return -1; // Pile vide
    Element *temp = *P;
    int v = temp->valeur;
    *P = (*P)->suivant;
    free(temp);
    return v;
}
void PairImpair(Pile *P1, Pile *P2, Pile *P3) {
    int v;
    // Vider P1
    while (*P1 != NULL) {
        v = pop(P1);
        if (v % 2 == 0) {
            push(P3, v); // On stocke les pairs temporairement
        } else {
            push(P2, v); // On empile les impairs dans P2 (ils seront au-dessus)
        }
    }
    // Remettre les pairs de P3 vers P2 (ils finiront au-dessous des impairs)
    while (*P3 != NULL) {
        push(P2, pop(P3));
    }
}
3.7 Exercice 7 : Files (FIFO) et Palindromes
typedef struct File {
    Element *debut;
    Element *fin;
} File;

void enfiler(File *f, int x) {
    Element *nouv = malloc(sizeof(Element));
    nouv->valeur = x;
    nouv->suivant = NULL;
    if (f->fin == NULL) {
        f->debut = f->fin = nouv;
    } else {
        f->fin->suivant = nouv;
        f->fin = nouv;
    }
}

int defiler(File *f) {
    if (f->debut == NULL) return -1;
    Element *temp = f->debut;
    int v = temp->valeur;
    f->debut = f->debut->suivant;
    if (f->debut == NULL) f->fin = NULL;
    free(temp);
    return v;
}
void EcrireMessage(File *f, Pile *p) {
    char c;
    printf("Tapez votre message (finir par Entrée) : ");
    while ((c = getchar()) != '\n') {
        enfiler(f, c);
        push(p, c);
    }
}

int EstPalindrome() {
    File f = {NULL, NULL};
    Pile p = NULL;
    
    EcrireMessage(&f, &p);
    
    while (f.debut != NULL) {
        if (defiler(&f) != pop(&p)) {
            // Nettoyage si on quitte tôt
            // detruireListe(f.debut); detruireListe(p);
            return 0; // Pas un palindrome
        }
    }
    return 1; // C'est un palindrome
}
