#include <iostream>
#include <cassert>
#include <string>
#include <utility>
#include "dyv.h"

int obtenerLongitud(std::pair<int, int> res) {
    return res.second - res.first + 1;
}

void testPrincipio() {
    A = "12323412";
    m = 10;
    std::pair<int, int> resultado = dyv({0, (int)A.length() - 1});
    assert(obtenerLongitud(resultado) == 3);
}

void testFinal() {
    A = "123234121234";
    m = 10;
    std::pair<int, int> resultado = dyv({0, (int)A.length() - 1});
    assert(obtenerLongitud(resultado) == 4);
}

void testMitad() {
    A = "12341234561234";
    m = 10;
    std::pair<int, int> resultado = dyv({0, (int)A.length() - 1});
    assert(obtenerLongitud(resultado) == 6);
}

void testDecreciente() {
    A = "54321";
    m = 10;
    std::pair<int, int> resultado = dyv({0, (int)A.length() - 1});
    assert(obtenerLongitud(resultado) == 1);
}

void testCreciente() {
    A = "12345";
    m = 10;
    std::pair<int, int> resultado = dyv({0, (int)A.length() - 1});
    assert(obtenerLongitud(resultado) == 5);
}

int main() {
    testPrincipio();
    testFinal();
    testMitad();
    testDecreciente();
    testCreciente();
    
    std::cout << "Todos los tests unitarios realizados con exito." << std::endl;
    return 0;
}