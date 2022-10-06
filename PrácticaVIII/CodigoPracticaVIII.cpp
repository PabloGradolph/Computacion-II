#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

bool DominanteDiagonal(matrix<double> A){
    bool dominante = false;
    int arows = 0, acols = 0;
    arows = A.rowno(); acols = A.colno();
    int vectorbool[arows] = {0, 0, 0, 0}; 
    
    double sum = 0.0;
    for (int i=0; i<arows; i++){
        sum = 0.0;
        for (int j=0; j<acols; j++){
            if (i!=j){
                sum = sum + A(i, j);
            } 
        }
        if (fabs(A(i,i)) > fabs(sum)){
            vectorbool[i] = 1;
        }
    }

    for (int i=0; i<arows; i++){
        if (vectorbool[i] == 0){
            dominante = 0;
            break;
        }
    }

    return dominante;
}
double NormaMaximaVector(double vector[], int len){
    double maximo = 0.0;
    for (int i=0; i<len; i++){
        if (vector[i]>maximo){
            maximo = vector[i];
        }
    }

    return maximo;
}

double NormaMaximaMatriz(matrix<double> A){
    int arows = 0, acols = 0;
    arows = A.rowno();
    acols = A.colno();

    double sumatorio = 0.0, fila_anterior = 0.0, maximo = 0.0;
    for (int i=0; i<arows; i++){
        fila_anterior = sumatorio;
        sumatorio = 0.0;
        for (int j=0; j<acols; j++){
            sumatorio = sumatorio + fabs(A(i,j));
        }
        if (sumatorio>fila_anterior){
            maximo = sumatorio;
        }
    }

    return maximo;
}

matrix<double> MetodoJacobi(matrix<double> A, matrix<double> B){
    int iteraciones = 0;
    int arows = 0, acols = 0, brows = 0, bcols = 0;
    arows = A.rowno();
    acols = A.colno();
    brows = B.rowno();
    bcols = B.colno();

    matrix<double> old_x(arows, acols); old_x.null();
    matrix<double> new_x(arows, acols); new_x.null();

    for (int i=0; i<arows; i++){
        B(i,0) = B(i,0)/A(i,i);
        for(int j=0; j<acols; j++){
            if(i!=j){
                A(i,j) = A(i,j)/A(i,i);
            } else {
                A(i,j) = 0;
            }
            
        }
    }

    return A;
}

int main(){
    string ainfile = "matrizA.txt";
    string binfile = "matrizB.txt";
    ifstream ffile(ainfile);
    ifstream ff(binfile);
    if (ffile.is_open()){
        if(ff.is_open()){
            // Filas y columnas de las matrices.
            int arows = 0, acols = 0, brows = 0, bcols = 0;

            // Definimos la matriz A.
            ffile >> arows >> acols;
            matrix<double> A(arows, acols);
            ffile >> A;

            // Definimos la matriz B.
            ff >> brows >> bcols;
            matrix<double> B(brows, bcols);
            ff >> B;

            // Cerramos los ficheros.
            ffile.close();
            ff.close();

            // Comprobamos si la matriz pasada es diagonal dominante mediante la función.
            bool dominante;
            dominante = DominanteDiagonal(A);
            if (dominante == true){
                cout<<"La matriz A es diagonal dominante."<<endl;
            } else {
                cout<<"¡Cuidado! La matriz A no es diagonal dominante."<<endl;
            }

            matrix<double> X(brows, bcols);
            X = MetodoJacobi(A, B);
            cout<<X;

            /*double maximo = 0.0;
            maximo = NormaMaximaMatriz(A);
            cout<<maximo<<endl;

            int len = 3;
            double vector[len] = {-5, 2, 8};
            maximo = NormaMaximaVector(vector, len);
            cout<<maximo<<endl;*/

        }
    }

    return 0;
}