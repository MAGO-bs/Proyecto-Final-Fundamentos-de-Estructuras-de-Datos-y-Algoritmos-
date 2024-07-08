#include <iostream>
#include <vector>
#include <string>
#include <fstream> //Para escritura y lectura de datos
#include <chrono> // Calculo del tiempo con alta precision
#include <cmath>

using namespace std;

int editDistanceRecursive(string S, string T);
int editDistanceMemoization(string S,string T);
int editDistanceDP(string S, string T);
int recursiveCall(string S, string T, vector<vector<int>> &M, int i, int j);

double timeCalculation(string S, string T, int num);
double prom(vector<double> vec);

int main()
{    
    ifstream input("frases.txt");
    if (!input.is_open())
        cerr << "No se pudo abrir el archivo" << endl;
        
    int s = 0;
    string line;    
    while (getline(input, line)) {  // Obtenemos la cantidad de frases que tenemos
        s++;
    }

    input.clear();      // Reiniciamos el puntero para leer el archivo nuevamente desde 0 sin tener que cerrarlo
    input.seekg(0); 

    vector<string> vec(s);
    int k = 0;
    while (getline(input, line)) // Leemos para generar un vector con el que trabajaremos
    {
        vec[k] = line; 
        k++;
    }
    input.close();
        
    int exper = 50;
    int cases = 12;
    vector<double> all_rec(exper);
    vector<double> all_mem(exper);
    vector<double> all_dp(exper);

    vector<string> string_S(cases);
    vector<string> string_T(cases);

    vector<int> n_values(cases);
    vector<int> m_values(cases);

    vector<double> all_prom_rec(cases);
    vector<double> all_prom_mem(cases);
    vector<double> all_prom_dp(cases);

    vector<int> space_rec(cases);
    vector<int> space_mem(cases);
    vector<int> space_dp(cases);

    vector<int> caso(cases);
    int n, m;
    int case_num = 0;
    k = 0;

    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < s; j++)
        {  
            if (i != j)
            {
                n = vec[i].size();
                m = vec[j].size();
                k = 0;
                while (k < exper)
                {
                    //all_rec[k] = timeCalculation(vec[i], vec[j], 1); 
                    all_rec[k] = 0; 
                    all_mem[k] = timeCalculation(vec[i], vec[j], 2); 
                    all_dp[k]  = timeCalculation(vec[i], vec[j], 3); 
                    k++;
                }
                string_S[case_num] = "String " + to_string(i + 1);
                string_T[case_num] = "String " + to_string(j + 1);
                n_values[case_num] = vec[i].size();
                m_values[case_num] = vec[j].size();
                all_prom_rec[case_num] = prom(all_rec);
                all_prom_mem[case_num] = prom(all_mem);
                all_prom_dp[case_num] = prom(all_dp);
                space_rec[case_num] = (n + m) * 2 * sizeof(int);  //Consideramos el peor caso
                space_mem[case_num] = (n + 1) * (m + 1) * sizeof(int) + 2 * sizeof(int);
                space_dp[case_num] = (m + 1) * sizeof(int) + 4 * sizeof(int);
                caso[case_num] = case_num + 1;
                case_num++;
            }
        }
    }
    //printVector(all_prom_rec);
    //printVector(all_prom_mem);
    //printVector(all_prom_dp);

    ofstream output("experimentacion.csv");
    output << "Caso,S,T,n,m,Rec[us],Mem[us],DP[us],E.Rec[bytes],E.Mem[bytes],E.DP[bytes]" << endl;

    for (int i = 0; i < cases; i++)
    {
        output << caso[i] << "," << string_S[i] << "," << string_T[i] << "," << n_values[i] << "," << m_values[i] << "," 
        << all_prom_rec[i] << "," << all_prom_mem[i] << "," << all_prom_dp[i] << "," 
        << space_rec[i] << "," << space_mem[i]<< "," << space_dp[i] << endl;
    }
    output.close();
    return 0;
}

int editDistanceRecursive(string S, string T)
{
    int n = S.size();
    int m = T.size();

    // Casos base
    if (n == 0 || m == 0) 
        return n + m;
    else 
    {
        if (S[n-1] == T[m-1])
            return editDistanceRecursive(S.substr(0, n - 1), T.substr(0, m - 1));
        else
        {
            return 1 + min(editDistanceRecursive(S, T.substr(0, m - 1)), editDistanceRecursive(S.substr(0, n - 1), T));
        }
    }
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

double timeCalculation(string S, string T, int num)
{   
    int aux;
    double total;
    if (num == 1)
    {
        auto start_time = chrono::high_resolution_clock::now();     // Calculamos el tiempo total restando el tiempo posterior al edit distance menos el anterior
        aux = editDistanceRecursive(S, T);
        auto end_time = chrono::high_resolution_clock::now();
        cout << "Rec: " << aux << endl;
        total = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }
    else if (num == 2)
    {
        auto start_time = chrono::high_resolution_clock::now();     // Calculamos el tiempo total restando el tiempo posterior al edit distance menos el anterior
        aux = editDistanceMemoization(S, T);
        auto end_time = chrono::high_resolution_clock::now();
        cout << "Mem: " << aux << endl;
        total = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }
    else if (num == 3)
    {
        auto start_time = chrono::high_resolution_clock::now();     // Calculamos el tiempo total restando el tiempo posterior al edit distance menos el anterior
        aux = editDistanceDP(S, T);
        auto end_time = chrono::high_resolution_clock::now();
        cout << "DP: " << aux << endl;
        total = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }
    return total;
}

double prom(vector<double> vec)
{
    int n = vec.size();
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += vec[i];
    }   
    return sum / n; 
}