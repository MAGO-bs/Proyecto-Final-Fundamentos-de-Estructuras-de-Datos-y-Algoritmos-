#include <iostream>
#include <vector>
#include <string>

using namespace std;

int editDistanceMemoization(string S,string T);
int recursiveCall(string S, string T, vector<vector<int>> &M, int i, int j);
void printMatrix(vector<vector<int>> M);

// Edit Distance con Memoization utilizando Insert y Delete

int main(){
    string S = "RED LIGHT"; 
    string T = "BLUE KNIGHT CLASS";
    int min;
    min = editDistanceMemoization(S, T);
    cout << "La distancia minima es: " << min << endl;
}

int editDistanceMemoization(string S,string T)
{
    int n_plus = S.length() + 1; 
    int m_plus = T.length() + 1;                               // Extiende el largo, el primer parametro de M es el largo n, el segundo es el vector de largo m inicializado en -1
    vector<vector<int>> M(n_plus, vector<int>(m_plus, -1)); // Genera la matriz de memoria. Llamadas "recursivas", y el llenado de la matriz de memoria. Vector de vectores de enteros.
    return recursiveCall(S, T, M, n_plus - 1, m_plus - 1);
}

int recursiveCall(string S, string T, vector<vector<int>> &M, int i, int j)
{
    if (M[i][j] != -1)
        return M[i][j];
    else if (i == 0 || j == 0)
        return M[i][j] = i + j;
    else
        if (S[i - 1] == T[j - 1])
            return M[i][j] = recursiveCall(S, T, M, i - 1, j - 1);
        else
        {
            return M[i][j] = 1 + min(recursiveCall(S, T, M, i, j - 1), recursiveCall(S, T, M, i - 1, j));
        }
}
void printMatrix(vector<vector<int>> M){
    int n_plus = M.size(); 
    int m_plus = M[0].size();                  //Tamano matriz
    for (int i = 0; i < n_plus; i++)
    {
        for (int j = 0; j < m_plus; j++)
        {
            cout << M[i][j] << "\t";
        }
        cout << endl;
    }
}