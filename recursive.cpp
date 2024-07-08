#include <iostream>
#include <string>

using namespace std;

int editDistanceRecursive(string S, string T);

int main()
{
    string S = "QWERTYUIOPASDFGHJ";
    string T = "qwertyuiopasdfghj";
    int min = editDistanceRecursive(S, T);
    cout << "La distancia minima es: " << min << endl;
}

// Edit Distance con Memoization utilizando Insert y Delete

int editDistanceRecursive(string S, string T)
{
    int n = S.size();
    int m = T.size();

    // Casos base
    if (n == 0 || m == 0) 
        return n + m;
    else 
    {
        if (S[n - 1] == T[m - 1])
            return editDistanceRecursive(S.substr(0, n - 1), T.substr(0, m - 1));
        else
        {
            return 1 + min(editDistanceRecursive(S, T.substr(0, m - 1)), editDistanceRecursive(S.substr(0, n - 1), T));
        }
    }
}