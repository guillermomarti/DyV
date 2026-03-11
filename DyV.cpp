#include <iostream>
#include <vector>
#include "dyv.h"
using namespace std;

string A;
int m;

/*Funciones para ampliar un índice. Tanto por izquierda como por derecha. Devuelven el nuevo
índice que se habrá ampliado lo máximo posible*/
int amp_der (int i){ //O(m)
    int pasos = 1;

    while (i+1 < (int)A.length() && A[i] <= A[i+1] && pasos < m){
        i++;
        pasos++;
    }

    return i;
}

int amp_izq (int i){ //O(m)
    int pasos = 1;

    while (i-1 >= 0 && A[i] >= A[i-1] && pasos < m){
        i--;
        pasos++;
    }

    return i;
}
//Fuccion para saber cual de las dos cadenas representadas por pares es mayor.
pair<int, int> cadena_mayor(pair<int, int> s1, pair<int, int> s2){ //O(1)
    int p1 = s1.first;
    int q1 = s1.second;
    int p2 = s2.first;
    int q2 = s2.second;
    return (q1 - p1 > q2 - p2)? s1 : s2;
}

pair<int, int> combinar(pair<int, int> s1, pair<int, int> s2, int p, int q, int mit){
    /*Si el carácter en medio es mayor que su siguiente no existe una cadena ascendente
    que esté entre la izquierda y la derecha, entonces, devolvemos la mayor de las dos*/
    if (A[mit] > A[mit+1]) return cadena_mayor(s1, s2); 

    int p1 = s1.first, q1 = s1.second;
    int p2 = s2.first, q2 = s2.second;
    /*
    Ahora, si el final de la cadena izquierda coincide con el medio tenemos dos casos:
    - Que el principio de p2 coincida con el siguiente carácter del medio, entonces
        enlazamos ambas cadenas de principio a final.
    - Si no, ampliamos la cadena izquierda todo lo que se pueda y vemos cual de 
        las dos es más grande.
    */
    if (q1 == mit){
        if (p2 == mit+1) return {p1, q2}; //O(1)

        return cadena_mayor({p1, amp_der(q1)}, s2); //O(m)
    }
    /*Si el principio de la cadena derecha es el carácter de la derecha del medio, como 
    sabemos que este es mayor que el medio(comprobado al principio), devolvemos la cadena
    mayor entre la izquierda y la derecha ampliada hacia la izquierda*/
    if (p2 == mit+1) return cadena_mayor(s1, {amp_izq(p2), q2}); //O(m)
    /*Finalmente, nos queda el caso en el cual podamos crear una tercera subcadena ampliando
    desde el medio hacia ambas direcciones ya que ningún indice de s1 y s2 coincide con
    el medio. Entonces comparamos cual de las tres es la mayor y la devolvemos.*/
    pair<int, int> s3 = {amp_izq(mit), amp_der(mit+1)}; //O(2m)

    pair<int, int> mejor = cadena_mayor(s1, s2);

    return cadena_mayor(mejor, s3);
}


pair<int, int> dyv(pair<int, int> par){ //T(n) = 2T(n/2) + O(m) = O(n + m*log(n))
    int p = par.first;
    int q = par.second;
    //CASO BASE: si inicio es igual a fin devuelves el par.
    if (p == q) return par;

    int mit = (p+q)/2;
    //Calculamos dyv de la subcadena izquierda.
    pair<int, int> s1 = dyv({p,mit});
    /*Si es mayor que m, ya podemos salir de la función. Muy importante para ahorrarnos
    pasos de recursividad.*/
    if (s1.second - s1.first +1 >= m) return s1;
    //Calculamos dy de la subcadena derecha.
    pair<int, int> s2 = dyv({mit+1,q});
    if (s2.second - s2.first +1 >= m) return s2;
    //Buscamos la solución final con combinar.
    return combinar(s1, s2, p, q, mit);
}

pair<int, int> acortar(pair<int, int> par){
    return {par.first, par.first+m -1};
}

pair<int, int> alargar(pair<int, int> par){
    return {par.second-m-1, par.second};
}
/*
int main(int argc, char const *argv[])
{
    cin >> A;
    cin >> m;
    int len_A = A.length();
    Calculamos la solución.
    pair<int, int> sol = dyv({0, len_A -1});
    Cogemos la longitud.
    int len_C = sol.second - sol.first +1;
    Si es mayor que m la acortamos para que esté en el rango correcto.
    if (len_C > m) {
        sol = acortar(sol);
        len_C = m;  
    } 
    Si el inicio de la solución hace que la ventana de m quede fuera por el final,
    cambiamos el inicio de la solución para que del inicio al final hayan m carácteres
    y la ventana de tamaño m termine en el final de A.
    if (len_A - sol.first < m) {
        sol.first = len_A - m;
    }

    cout << sol.first +1 << " " << len_C;
    return 0;
}
*/