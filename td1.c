Exercice 1 : Gestion de PointsCet exercice explore la manipulation des structures, le passage par valeur/adresse et l'allocation dynamique.1. Définition de la structurePour utiliser le mot Point directement, on utilise typedef.C
typedef struct {
    int x;
    int y;
} Point;
2 & 3. Saisie et AffichageC
Point SaisirPoint() {
    Point p;
    printf("Entrez x et y : ");
    scanf("%d %d", &p.x, &p.y);
    return p;
}

void AfficherPoint(Point p) {
    printf("(%d,%d)", p.x, p.y);
}
4. Tableaux (Statique et Dynamique)C// Version statique (ex: 10 points)
Point tabStatique[10];

// Version dynamique
int n = 5; 
Point *tabDynamique = (Point*)malloc(n * sizeof(Point));
5. Distance par rapport à l'origineLa distance $d$ d'un point $(x, y)$ est donnée par :$$d = \sqrt{x^2 + y^2}$$Par valeur :C
float distanceVal(Point p) {
    return sqrt(p.x*p.x + p.y*p.y);
}
Par adresse :Cfloat distancePtr(Point *p) {
    return sqrt(p->x*p->x + p->y*p->y);
}
6 & 7. Tri et Programme de test.C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void trierPoints(Point tab[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (distanceVal(tab[j]) > distanceVal(tab[j+1])) {
                Point temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
}

int main() {
    int n = 3;
    Point *T = (Point*)malloc(n * sizeof(Point));

    for(int i=0; i<n; i++) T[i] = SaisirPoint();

    trierPoints(T, n);

    printf("Points triés : ");
    for(int i=0; i<n; i++) {
        AfficherPoint(T[i]);
        printf(" ");
    }

    free(T);
    return 0;
}
Exercice 2 : Structure HeureIci, la difficulté réside dans la gestion des retenues (60 secondes = 1 minute, etc.).Structure de baseC
typedef struct {
    int hh;
    int mm;
    int ss;
} Heure;
1 & 2. ConversionsCes fonctions facilitent énormément les calculs d'addition et de différence.C
int HeureEnSecondes(Heure h) {
    return h.hh * 3600 + h.mm * 60 + h.ss;
}

Hees SecondesEnHeure(int s) {
    Heure h;
    h.hh = s / 3600;
    s %= 3600;
    h.mm = s / 60;
    h.ss = s % 60;
    return h;
}
3 & 4. Addition et DifférenceEn utilisant les fonctions de conversion ci-dessus, le code devient très simple et robuste :C
int Heure ajouterHeures(Heure h1, Heure h2) {
    int totalSec = HeureEnSecondes(h1) + HeureEnSecondes(h2);
    return SecondesEnHeure(totalSec);
}

int Heure differenceHeures(Heure h1, Heure h2) {
    int s1 = HeureEnSecondes(h1);
    int s2 = HeureEnSecondes(h2);
    int diff = abs(s1 - s2);
    return SecondesEnHeure(diff);
}*
