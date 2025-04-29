#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

const char *inputFilePath = "matrix.in.txt";
const int n = 3; // Tamano d la matriz

struct stVector
{
    float coeff[n];
};
// MAIN VARIABLES
FILE *inputFile;

// Valores iniciales para leer
float a[n][n];
float b[n]; // T'erminos independientes
// Matrices para el m'etodo de Jacobi
float M[n][n]; // matriz M
float C[n];    // matriz C
// Vector soluciones aproximadas
vector<stVector> solutionVectors; // Vectores soluci'on obtenidos en cada iteraci'on

// SECONDARY FUNCTIONS
void Initialize();
void ReadInitialMatrix();
void SetMMatrix();
void SetCMatrix();
void ShowSolutionVectors();

int main()
{
    Initialize();

    // Anadir el vector nulo como primer vector dentro del grupo de vectores soluci'on
    stVector tmpVectorNulo;
    for (int i = 0; i < n; i++)
        tmpVectorNulo.coeff[i] = 0;
    solutionVectors.push_back(tmpVectorNulo);

    int currentTime = 1; // N'umero actual de iteraci'on
    int times = 10;      // N'umero total de iteraciones
    do
    {
        stVector newVector;

        for (int i = 0; i < n; i++)
        {
            newVector.coeff[i] = 0;
            for (int j = 0; j < n; j++)
            {
                newVector.coeff[i] += M[i][j]*solutionVectors[currentTime-1].coeff[i];
            }
            newVector.coeff[i] += C[i];
        }
        solutionVectors.push_back(newVector);

        currentTime++;
    } while (currentTime <= times);

    ShowSolutionVectors();
    return 0;
}

void ShowSolutionVectors()
{
    for (int i = 0; i < solutionVectors.size(); i++)
    {
        printf("iteration %d: ", i + 1);
        for (int j = 0; j < n ; j++)
        {
            printf("x%d: %f, ", j + 1, solutionVectors[i].coeff[j]);
        }
        printf("\n");
    }
}
void Initialize()
{
    /*
     *Inicializa variables y ejecuta procedimientos iniciales necesarios
     */
    inputFile = fopen(inputFilePath, "r");
    ReadInitialMatrix();
    SetMMatrix();
    SetCMatrix();
}

void SetCMatrix()
{
    /*
     *Calcula los valores d la matriz C
     */
    for (int i = 0; i < n; i++)
    {
        C[i] = b[i] / a[i][i];
    }
}
void SetMMatrix()
{
    /*
     *Calcula los valores de la matriz M
     */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                M[i][j] = 0; // Diagonal principal evaluada a 0
            else
            {
                M[i][j] = -a[i][j] / a[i][i];
            }
        }
    }
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
            fscanf(inputFile, "%f", &a[i][j]); // Lee coeficiente sub_j de la fila sub_i
        }
        fscanf(inputFile, "%f", &b[i]); // Lee t'ermino indepediente de la fila sub_i
    }
}
