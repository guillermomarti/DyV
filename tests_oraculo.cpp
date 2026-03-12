#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cassert>
#include <utility>
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

pair<int, int> solve_iterativo(string A, int m){
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

int main() {
    unsigned int semilla_base = 12345;
    vector<int> longitudes = {10, 50, 100, 500, 1000};
    
    for (size_t i = 0; i < longitudes.size(); ++i) {
        int n = longitudes[i];
        m = n / 3; 
        A = generarCadenaAleatoria(n, semilla_base + i);
        int len_A = A.length();
        
        
        pair<int, int> sol_real = dyv({0, n - 1});
        
        
        int len_C = sol_real.second - sol_real.first + 1;
        if (len_C > m) {
            sol_real = acortar(sol_real);
            len_C = m;
        } 
        if (len_A - sol_real.first < m) {
            sol_real.first = len_A - m;
        }

        
        int pos_dyv_base1 = sol_real.first + 1;

        
        pair<int, int> itOutput = solve_iterativo(A, m);
        
        cout << "--- Test con n=" << n << " y m=" << m << " ---" << endl;
        cout << "Resultado DyV: [" << pos_dyv_base1 << ", " << len_C << "]" << endl;
        cout << "Resultado Iterativo: [" << itOutput.first << ", " << itOutput.second << "]" << endl;
        
        
        assert(len_C == itOutput.second);

        // Verificamos racha si hay empate de posición
        if (pos_dyv_base1 != itOutput.first) {
            cout << "[Aviso] Empate detectado: Diferente posicion pero misma longitud maxima." << endl;
            // IMPORTANTE: k usa el índice real (Base 0) para acceder a A
            for(int k = sol_real.first; k < sol_real.first + len_C - 1; ++k) {
                assert(A[k] <= A[k+1]);
            }
        }
        cout << "Perfecto." << endl << endl;
    }

    cout << "Todos los tests del oráculo han pasado correctamente." << endl;
    return 0;
}