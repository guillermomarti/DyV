#ifndef DYV_H
#define DYV_H

#include <iostream>
#include <string>
#include <vector>

extern std::string A;
extern int m;

/**
 * @brief Resuelve el problema de la subcadena ascendente mediante Divide y Vencerás.
 * * @param p Índice de inicio del rango a analizar.
 * @param q Índice de fin del rango a analizar.
 * @param A Referencia a la cadena original.
 * @param m Tamaño de la ventana de búsqueda.
 * @return std::pair<int, int> Un par con el {índice_inicio, longitud_C}.
 */
std::pair<int, int> dyv(std::pair<int,int> par);

/**
 * @brief Combina las soluciones de dos subproblemas.
 */
std::pair<int, int> combinar(std::pair<int, int> s1, std::pair<int, int> s2, int p, int q, int mit);

/**
 * @brief Amplía un índice hacia la derecha buscando orden ascendente.
 */
int amp_der(int i);

/**
 * @brief Amplía un índice hacia la izquierda buscando orden ascendente.
 */
int amp_izq(int i);

/**
 * @brief Compara dos soluciones y devuelve la de mayor longitud.
 */
std::pair<int, int> cadena_mayor(std::pair<int, int> s1, std::pair<int, int> s2);

#endif 