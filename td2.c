2.1 Exercice 1 :
int premierIndiceMin(int T[], int N) {
    int indiceMin = 0; // On suppose que le premier élément est le min
    for (int i = 1; i < N; i++) {
        if (T[i] < T[indiceMin]) {
            indiceMin = i;
        }
    }
    return indiceMin;
}

2.2 Exercice 2 :
int miniMax(int n, int m, int Mat[n][m]) {
    int min_des_max;
    
    for (int i = 0; i < n; i++) {
        int max_ligne = Mat[i][0];
        for (int j = 1; j < m; j++) {
            if (Mat[i][j] > max_ligne) 
                max_ligne = Mat[i][j];
        }
        
        if (i == 0 || max_ligne < min_des_max) {
            min_des_max = max_ligne;
        }
    }
    return min_des_max;
}
2.3 Exercice 3 :
int puissance(int a, int i) {
    if (i == 0) return 1;
    return a * puissance(a, i - 1);
}
int puissanceRapide(int a, int i) {
    if (i == 0) return 1;
    int moitie = puissanceRapide(a, i / 2);
    if (i % 2 == 0)
        return moitie * moitie;
    else
        return a * moitie * moitie;
}
4 & 5. Somme récursive 
int sommePuissance(int a, int n) {
    if (n == 0) return 1; // a^0 = 1
    return puissanceRapide(a, n) + sommePuissance(a, n - 1);
}
