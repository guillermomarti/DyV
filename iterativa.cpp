#include <iostream>
#include <algorithm>
using namespace std;

pair<int, int> solve(string A, int m){
    int longA = A.length(); //Cogemos la longitud de la cadena A, lo que sería n.
    if (longA < 1) return {0,0}; //Si la cadena es vacía devolvemos 0.
    int pos = 1; //Sino inicializamos las variables a 1 porque existe un primer carácter.
    int actual = 1; 
    int maximo = 1;
    int i = 0;
    /*Comienzo del bucle donde vamos a reccorer todos los caracteres de la cadena hasta n - 1
    para no salirnos del rango. También para el bucle en el caso que la longitud de la cadena 
    de caracteres ascendentes, de la cual almacenamos su tamaño en actual, sea => a m.*/
    while (i < A.length()-1 && actual < m){
        if (A[i] <= A[i+1]) actual++; //Aumentamos actual si el caracter siguiente es mayor.
        else { //Si no, si actual es mayor que el maximo, maximo coge el valor de actual.
            if (actual > maximo){
                pos = i+2-actual; //Calculo de la posición donde se inició la racha. 
                maximo = actual;
            }
            actual = 1; //Reiniciamos actual para empezar una nueva subcadena ascendente.
        }
        i++;
    }
    /*Al acabar el bucle hay q hacer de nuevo las comprobaciones, porque puede haber acabado 
    sin actualizar los datos por la condición de i o porque es => que m.*/
    if (actual >= m){ //Actualizamos datos de posición y máximo en cada caso.
        pos = i+2-actual;
        maximo = actual;
    }
    else if (actual > maximo) {
        pos = i+2-actual;
        maximo = actual;
    }
    /*Esta es la clave de la solución propuesta. Antes de dar la solución se comprueba si 
    pos, que es el inicio de m, hace que la ventana de m salga fuera de la cadena. Si es así,
    se recalcula la posición para que coincida con el inicio de los últimos m carácteres.*/
    if (longA - pos +1 < m) pos = longA - m +1;
    return {pos, maximo};
} 

int main(int argc, char const *argv[])
{
    string A;
    int m;
    cin >> A >> m;
    pair<int, int> sol = solve(A, m);
    cout << sol.first << " " << sol.second;
    return 0;
}