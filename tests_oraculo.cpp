#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <random>
#include <utility>
#include "dyv.h"

using namespace std;

string generarStringAleatorio(int longitud, unsigned int semilla) {
    string secuencia = "";
    mt19937 gen(semilla);
    uniform_int_distribution<> dist('a', 'z');

    for (int i = 0; i < longitud; ++i) {
        secuencia += (char)dist(gen);
    }

    return secuencia;
}

int main() {
    unsigned int semilla = 42;
    vector<int> longitudes = {5, 10, 20, 50, 100, 1000};
    int m = 4;

    for (size_t i = 0; i < longitudes.size(); ++i) {
        int longitud = longitudes[i];
        string secuencia = generarStringAleatorio(longitud, semilla + i);
        
        pair<int, int> dyvOutput = dyv(secuencia, m);
        pair<int, int> resultadoIterativo = iterativa(secuencia, m);
        
        cout << "Longitud de la secuencia: " << longitud << endl;
        cout << "Resultado DyV (Inicio, Long): " << dyvOutput.first << ", " << dyvOutput.second << endl;
        cout << "Resultado Iterativo (Inicio, Long): " << resultadoIterativo.first << ", " << resultadoIterativo.second << endl;
        cout << "-----------------------------------" << endl;

        assert(dyvOutput.second == resultadoIterativo.second);
    }

    cout << "Todos los tests aleatorios pasaron!" << endl;

    return 0;
}