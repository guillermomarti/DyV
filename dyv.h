#ifndef DYV_H
#define DYV_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

extern std::string A;
extern int m;

/**
 * @brief Resuelve el problema de la subcadena ascendente mediante Divide y Vencerás.
 * @param par Un par con el {índice_inicio, índice_fin} del rango a analizar.
 * @return std::pair<int, int> Un par con el {índice_inicio, índice_fin} de la racha encontrada.
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

/**
 * @brief Recorta una racha para que su longitud sea exactamente m.
 * @param par Un par con el {índice_inicio, índice_fin}.
 * @return std::pair<int, int> El par recortado desde el inicio.
 */
std::pair<int, int> acortar(std::pair<int, int> par);

/**
 * @brief Ajusta una racha para que termine en su índice final con longitud m.
 * @param par Un par con el {índice_inicio, índice_fin}.
 * @return std::pair<int, int> El par ajustado hacia atrás.
 */
std::pair<int, int> alargar(std::pair<int, int> par);

#endif