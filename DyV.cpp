#include <iostream>
#include <algorithm>
using namespace std;

//Operacion de busqueda de la longitud de la subcadena mayor en una ventana de tamaño m. O(m)
int long_subcadena_mayor(const string& A, int inicio, int m){ 
    int maximo = 0;
    int actual = 1;
    for (int i = inicio; i < inicio + m -1; i++){
        if (A[i] <= A[i+1]) actual++;
        else {
            maximo = max(maximo, actual);
            actual = 1;
        }
    }
    maximo = max(maximo, actual);
    return maximo;
}

//Operacion de combinación de las soluciones de las ramas izquierda y derecha. O(m^2)
pair<int, int> combinar(const string& A, int inicio, int fin, pair<int, int> s1, pair<int, int> s2, int mit, int m) {
    pair<int, int> mejor_cruce = {-1, -1};

    // Calculamos el rango de índices donde puede empezar una ventana que cruza la frontera. O(1)
    int r_inicio = max(inicio, mit - m + 2);
    int r_fin = min(fin - m + 1, mit);

    // Evaluamos cada una de las ventanas de cruce. O(m^2))
    for (int i = r_inicio; i <= r_fin; i++) { //O(m)
        int c_actual = long_subcadena_mayor(A, i, m); //O(m)
        if (c_actual > mejor_cruce.second) {
            mejor_cruce = {i, c_actual};
        }
    }

    // Comparamos el mejor del cruce con los mejores de las ramas izquierda (s1) y derecha (s2). O(1)
    pair<int, int> mejor = (s1.second >= s2.second) ? s1 : s2;
    
    if (mejor_cruce.second > mejor.second) {
        mejor = mejor_cruce;
    }

    return mejor;
}

//Algoritmo principal DyV. incluye caso base + 2 casos recursivos + combinación. O(n + m*log(n))
//T(n) = 2T(n/2) + O(m^2) => T(n) = O(n + m^2 * log(n))
pair<int, int> solucion_dyv(pair<int, int> par, const string& A, int m){ 
    int n = par.second - par.first + 1;                         
    
    //Casos base
    if (n < m) return {-1, -1}; //O(1)

    if (n == m) return {par.first, long_subcadena_mayor(A, par.first, m)};//O(m)

    //Recursividad
    int mit = (par.first + par.second) / 2;
    pair<int, int> s1 = solucion_dyv({par.first, mit}, A, m); //T(n/2)
    if (s1.second == m) return s1;

    pair<int, int> s2 = solucion_dyv({mit+1, par.second}, A, m); //T(n/2)
    if (s2.second == m) return s2;

    //Combinación
    return combinar(A, par.first, par.second, s1, s2, mit, m); //O(m^2)
}

// Sirve para ajustar el índice de posición. Así queda como en el ejemplo. No se puede
// implementar en la función anterior porque habría problemas con el acceso a la cadena.
pair<int, int> dyv(const string& A, int m) {
    pair<int, int> res = solucion_dyv({0, (int)A.size() - 1}, A, m);
    
    // Si encontró una solución, sumamos 1 al índice de inicio
    if (res.first != -1) {
        res.first = res.first + 1;
    }
    
    return res;
}

pair<int, int> iterativa(const string& A, int m){
    int longA = A.length();
    if (longA < 1) return {0,0};
    int pos = 1;
    int actual = 1;
    int maximo = 1;
    int i = 0;
    while (i < (int)A.length()-1 && actual < m){
        if (A[i] <= A[i+1]) actual++;
        else {
            if (actual > maximo){
                pos = i+2-actual;
                maximo = actual;
            }
            actual = 1;
        }
        i++;
    }

    if (actual >= m){
        pos = i+2-actual;
        maximo = actual;
    }
    else if (actual > maximo) {
        pos = i+2-actual;
        maximo = actual;
    }
    if (longA - pos +1 < m) pos = longA - m +1;
    return {pos, maximo};
}