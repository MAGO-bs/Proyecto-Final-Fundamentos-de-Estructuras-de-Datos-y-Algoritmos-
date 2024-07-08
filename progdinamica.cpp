#include <iostream>
#include <vector>
#include <string>

using namespace std;

int editDistanceDP(string S,string T);

int main(){
    string S = "RED LIGHT"; 
    string T = "BLUE KNIGHT CLASS";
    int min = editDistanceDP(S, T);
    cout << "La distancia minima es: " << min << endl;
}

// Edit Distance con Progamacion Dinamica utilizando Insert y Delete

int editDistanceDP(string S, string T)
{
    int n_plus = S.size() + 1;
    int m_plus = T.size() + 1;

    vector<int> result(m_plus); 

    // Inicializamos vector en 0, 1, 2, 3, ..., m 
    for (int j = 0; j < m_plus; j++)
        result[j] = j;

    //Casos intermedios
    int prev, aux;
    for (int i = 1; i < n_plus; i++)  
    {
        result[0] = i; // Caso base filas
        prev = i - 1; // Variable auxiliar para conservar valor anterior

        for (int j = 1; j < m_plus; j++)
        {
            aux = result[j];

            if (S[i - 1] == T[j - 1]) // Ultima letra igual
                result[j] = prev;
            else    // Caso intermedio con insert y delete
            {
                result[j] = 1 + min(result[j], result[j - 1]);
            }
            prev = aux;
        }
    }
    return result[m_plus - 1];
}