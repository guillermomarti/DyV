#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cassert>
#include "dyv.h"

using namespace std;

string generarCadenaAleatoria(int longitud, unsigned int semilla) {
    string cadena = "";
    mt19937 gen(semilla);
    uniform_int_distribution<> dist('a', 'z'); 

    for (int i = 0; i < longitud; ++i) {
        cadena += (char)dist(gen);
    }
    return cadena;
}

pair<int, int> solve_iterativo(const string& A, int m) {
    int n = A.length();
    if (n < 1) return {0, 0};
    
    int pos = 1, actual = 1, maximo = 1;
    for (int i = 0; i < n - 1; ++i) {
        if (A[i] <= A[i+1] && actual < m) {
            actual++;
        } else {
            if (actual > maximo) {
                maximo = actual;
                pos = i - actual + 2; 
            }
            actual = 1;
        }
    }
    if (actual > maximo) {
        maximo = actual;
        pos = n - actual + 1;
    }

    if (n - pos + 1 < m) pos = n - m + 1;
    
    return {pos, maximo};
}

int main() {
    unsigned int semilla_base = 12345;
    vector<int> longitudes = {10, 50, 100, 500, 1000};
    
    for (size_t i = 0; i < longitudes.size(); ++i) {
        int n = longitudes[i];
        int m = n / 3; 
        
        string secuencia = generarCadenaAleatoria(n, semilla_base + i);
        
        pair<int, int> dyvOutput = dyv(0, n - 1, secuencia, m);
        pair<int, int> itOutput = solve_iterativo(secuencia, m);
        
        cout << "--- Test con n=" << n << " y m=" << m << " ---" << endl;
        cout << "Resultado DyV: Pos=" << dyvOutput.first << ", Len=" << dyvOutput.second << endl;
        cout << "Resultado Iterativo: Pos=" << itOutput.first << ", Len=" << itOutput.second << endl;
        
        assert(dyvOutput.second == itOutput.second);
        cout << "¡OK!" << endl << endl;
    }

    cout << "Todos los tests del oráculo han pasado correctamente." << endl;
    return 0;
}