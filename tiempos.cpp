#include <iostream>
#include "dyv.h"
#include <cassert>
#include <cmath>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Peor caso: Cadena ascendente (obliga a combinar y expandir)
string generarPeorCaso(int longitud) {
    string s = "";
    for (int i = 0; i < longitud; ++i) {
        s += 'a' + (i % 26);
    }
    return s;
}

// Mejor caso: Cadena descendente (la racha se corta siempre en el medio)
string generarMejorCaso(int longitud) {
    string s = "";
    for (int i = 0; i < longitud; ++i) {
        s += 'z' - (i % 26);
    }
    return s;
}

// Mide el tiempo en milisegundos
double medirTiempo(const string& secuencia, int m) {
    auto start = chrono::high_resolution_clock::now();

    // Llamada a tu función DyV
    dyv(0, secuencia.size() - 1, secuencia, m);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = end - start;
    return duracion.count();
}

double calcularMediana(vector<double> v) {
    int n = v.size();
    if (n == 0) return 0.0;
    sort(v.begin(), v.end());
    if (n % 2 == 1)
        return v[n / 2];
    else
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

int main() {
    vector<int> longitudes;
    for (int i = 0; i <= 12; i++) {
        longitudes.push_back(1000 * pow(2, i));
    }

    ofstream csv("tiempos_dyv.csv");
    csv << "Longitud,MejorCaso,PeorCaso\n";

    cout << "Iniciando medicion de tiempos..." << endl;

    for (int longitud : longitudes) {
        int m = 100; 

        // Medir Mejor Caso
        string mejorCaso = generarMejorCaso(longitud);
        vector<double> tiemposMejor;
        for (int j = 0; j < 10; j++) {
            tiemposMejor.push_back(medirTiempo(mejorCaso, m));
        }
        double medMejor = calcularMediana(tiemposMejor);

        // Medir Peor Caso
        string peorCaso = generarPeorCaso(longitud);
        vector<double> tiemposPeor;
        for (int j = 0; j < 10; j++) {
            tiemposPeor.push_back(medirTiempo(peorCaso, m));
        }
        double medPeor = calcularMediana(tiemposPeor);

        csv << longitud << "," << medMejor << "," << medPeor << "\n";
        cout << "N: " << longitud << " procesado." << endl;
    }

    csv.close();
    cout << "Fichero tiempos_dyv.csv generado con exito." << endl;
    return 0;
}