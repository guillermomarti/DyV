#include <iostream>
#include <cassert>
#include <string>
#include <utility>
#include "dyv.h"

using namespace std;

void testPrincipio() {
    string S = "abcbcdeab"; 
    int m = 3;
    pair<int, int> resultado = dyv(S, m);
    assert(resultado.first == 1);
    assert(resultado.second == 3); 
}

void testFinal() {
    string S = "cbabadeabcd";
    int m = 4;
    pair<int, int> resultado = dyv(S, m);
    assert(resultado.first == 8);
    assert(resultado.second == 4);
}

void testMitad() {
    string S = "abcefghijkab";
    int m = 6;
    pair<int, int> resultado = dyv(S, m);
    assert(resultado.first == 1);
    assert(resultado.second == 6);
    
}

void testDecreciente() {
    string S = "fedcba";
    int m = 3;
    pair<int, int> resultado = dyv(S, m);
    assert(resultado.first == 1);
    assert(resultado.second == 1);
}

void testCreciente() {
    string S = "abcdefgh";
    int m = 5;
    pair<int, int> resultado = dyv(S, m);
    assert(resultado.first == 1);
    assert(resultado.second == 5);
}

int main() {
    testPrincipio();
    testMitad();
    testFinal();
    testDecreciente();
    testCreciente();
    cout << "Todos los tests pasaron!" << endl;
    return 0;
}