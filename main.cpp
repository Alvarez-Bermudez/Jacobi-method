#include <stdio.h>
#include <iostream>

using namespace std;

const char input_file_path = "matrix.in.txt";
const int n = 3; // Tamano d la matriz

// main variables
FILE *input_file;
float initial_matrix[n][n];
float M[n][n]; // matriz M
float b[n];    // T'erminos independientes

// secondary functions
void Initialize();
void ReadInitialMatrix();
void SetMMatrix();
int main()
{

    return 0;
}

void Initialize()
{
    /*
     *Inicializa variables y ejecuta procedimientos iniciales necesarios
     */
    input_file = fopen(input_file_path, "r");
    ReadInitialMatrix();
    SetMMatrix();
}
void ReadInitialMatrix()
{
    /*
     *Lee la matriz inicial del fichero de entrada
     */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> initial_matrix[i][j]; // Lee coeficiente sub_j de la fila sub_i
        }
        cin >> b[i]; // Lee t'ermino indepediente de la fila sub_i
    }
}
