#include <iostream>
#include <cassert>
#include <string>
#include <utility>
#include "dyv.h"

void testPrincipio() {
    std::string A = "abcdeffxyz"; 
    int m = 5;
    std::pair<int, int> resultado = dyv(0, A.length() - 1, A, m);
    assert(resultado.first == 0); 
    assert(resultado.second == 5);
}

void testMitad() {
    std::string A = "zyxabcdzyx"; 
    int m = 6;
    std::pair<int, int> resultado = dyv(0, A.length() - 1, A, m);
    assert(resultado.second == 4); 
}

void testDecreciente() {
    std::string A = "fedcba";
    int m = 3;
    std::pair<int, int> resultado = dyv(0, A.length() - 1, A, m);
    assert(resultado.second == 1);
}


void testCreciente() {
    std::string A = "abcdefghijk";
    int m = 4;
    std::pair<int, int> resultado = dyv(0, A.length() - 1, A, m);
    assert(resultado.second == 4); 
}


void testEmpate() {
    std::string A = "abcde12345";
    int m = 5;
    std::pair<int, int> resultado = dyv(0, A.length() - 1, A, m);
    assert(resultado.second == 5);
}

int main() {
    testPrincipio();
    testMitad();
    testDecreciente();
    testCreciente();
    testEmpate();
    
    std::cout << "¡Todos los tests unitarios pasaron con éxito!" << std::endl;
    return 0;
}