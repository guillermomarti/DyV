#include <iostream>
#include <algorithm>
using namespace std;

pair<int, int> solve(string A, int m){
    int longA = A.length();
    if (longA < 1) return {0,0};
    int pos = 1;
    int actual = 1;
    int maximo = 1;
    int i = 0;
    while (i < A.length() && actual < m){
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

int main(int argc, char const *argv[])
{
    string A;
    int m;
    cin >> A >> m;
    pair<int, int> sol = solve(A, m);
    cout << sol.first << " " << sol.second;
    return 0;
}