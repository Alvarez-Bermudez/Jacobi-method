#include <stdio.h>
#include <iostream>
#include <vector>
#include<math.h>
#include<windows.h>


using namespace std;

const char *inputFilePath = "matrix.in.txt";
const int n = 3; // Tamano d la matriz

struct stVector
{
    double coeff[n];
};
// MAIN VARIABLES
FILE *inputFile;

// Valores iniciales para leer
double a[n][n];
double b[n]; // T'erminos independientes
// Matrices para el m'etodo de Jacobi
double M[n][n]; // matriz M
double C[n];    // matriz C
double eta=0.5f;// m'aximo margen de error deseado 
double alpha=.0f;// norma d la matriz M

// Vector soluciones aproximadas
vector<stVector> solutionVectors; // Vectores soluci'on obtenidos en cada iteraci'on

double max(double,double);
double min(double,double);

// SECONDARY FUNCTIONS
void Initialize();
void ReadInitialMatrix();
void SetMMatrix();
void SetCMatrix();
void SetAlphaValue();
void ShowSolutionVectors();
void ShowMMatrix();
void ShowCMatrix();

int main()
{
    Initialize();

    // Anadir el vector nulo como primer vector dentro del grupo de vectores soluci'on
    stVector tmpVectorNulo;
    for (int i = 0; i < n; i++)
        tmpVectorNulo.coeff[i] = 0;
    solutionVectors.push_back(tmpVectorNulo);

    int currentTime = 1; // N'umero actual de iteraci'on
    int times = 9;      // N'umero total de iteraciones
    
    //ShowMMatrix();
    //ShowCMatrix();
    double Error;
    do
    {
        Error=.0f;

        stVector newVector;

        for (int i = 0; i < n; i++)
        {
            newVector.coeff[i] = 0;
            for (int j = 0; j < n; j++)
            {
                newVector.coeff[i] += M[i][j]*solutionVectors[currentTime-1].coeff[j];
            }
            newVector.coeff[i] += C[i];
            double helperError=abs(newVector.coeff[i]-solutionVectors[currentTime-1].coeff[i]);
            
            if (helperError>Error) Error=helperError;
            
            printf("helperError %f Error %f \n",helperError,Error);
        }

        solutionVectors.push_back(newVector);
        
        Error*=(alpha)/(1.0f-alpha);

        currentTime++;

        //Show solution at i itteration 
        printf("Iteration %d: ",  currentTime);
        for (int j = 0; j < n ; j++)
        {
            printf("x%d: %f, ", j + 1, solutionVectors[currentTime].coeff[j]);
        }
        printf("\n");

        Sleep(300);
    } while (Error <= eta);

    ShowSolutionVectors();
    return 0;
}

void SetAlphaValue(){
    double helper_row=.0f;

    for (int i  =0;i<n;i++){
        helper_row=.0f;

        for (int j=0;j<n;j++){
            helper_row+=abs(M[i][j]);

        }
        alpha=max(alpha,helper_row);
    }
}

double max(double a,double b){
if (a>=b)return a;
else return b;
}
double min(double a,double b){
    if (a<=b)return a;
else return b;
}

void ShowCMatrix(){
    cout<<"M Matrix\n";
    for (int i=0;i<n;i++){
        cout<<C[i]<<"\n";
    }
    cout<<"end M Matrix\n";
}
void ShowMMatrix(){
    
    cout<<"M Matrix\n";
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cout<<M[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"end M Matrix\n";
    
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
    SetAlphaValue();

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
