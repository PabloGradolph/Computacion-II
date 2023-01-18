#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Función que calcula la nomra máxima de una matriz. Pasando como parámetro una matriz.
// Usaremos esta función para ver si nuestro resultado es correcto dentro de una tolerancia.
double NormaMaximaMatriz(matrix<double> A){
    // Tamaño de la matriz pasada como argumento.
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
        if (sumatorio>maximo){
            maximo = sumatorio;
        }
    }

    return maximo;
}

// Función que retorna True o False en función de si la matriz pasada como parámetro es Diagonal Dominante o no.
bool DominanteDiagonal(matrix<double> A){
    // Inicializamos las variables y calculamos el tamaño de la matriz pasada como argumento.
    bool dominante = false;
    int arows = 0, acols = 0;
    arows = A.rowno(); acols = A.colno();
    int vectorbool[arows] = {0}; 
    
    // Se calcula la suma por fila de los elementos que no están en la diagonal.
    // Se compara con el elemento de la diagonal y guardamos en el vectorbool un 1 o un 0 en función de si es mayor o no.
    double sum = 0.0;
    for (int i=0; i<arows; i++){
        sum = 0.0;
        for (int j=0; j<acols; j++){
            if (i!=j){
                sum = sum + fabs(A(i, j));
            } 
        }
        if (fabs(A(i,i)) > sum){
            vectorbool[i] = 1;
        }
    }

    // Si hay algún cero en el vector, la variable dominante es false y se retorna.
    for (int i=0; i<arows; i++){
        if (vectorbool[i] == 0){
            dominante = 0;
            break;
        }
    }

    return dominante;
}

// Función que calcula la solución de un sistema de ecuaciones lineales mediante el método iterativo de Gauss-Seidel.
matrix<double> MetodoGauss(matrix<double> inA, matrix<double> inB, double tol, double &error, int &iteraciones){
    // Calculamos el tamaño de las matrices pasadas como argumento.
    // Pasamos la matriz de coeficientes y la matriz solución del sistema.
    int arows = 0, acols = 0, brows = 0, bcols = 0;
    arows = inA.rowno();
    acols = inA.colno();
    brows = inB.rowno();
    bcols = inB.colno();

    matrix<double> A(arows,acols); A=inA;
    matrix<double> B(brows,bcols); B=inB;

    // Tres matrices que iremos usando durante las iteraciones.
    matrix<double> old_x(brows, bcols); old_x.null();
    matrix<double> new_x(brows, bcols); new_x.null();

    // Abrimos un archivo donde guardamos el error por cada iteración
    string Gaussfile = "ErroresIteracionesGauss.txt";
    ofstream ff(Gaussfile);
    if (ff.is_open()){
        ff<<"#ERRORES FRENTE ITERACIONES GAUSS PARA TOLERANCIA 10e-6"<<endl;
        ff<<"error\t\titeraciones"<<endl;
        // Calculamos las matrices de coeficientes
        for (int i=0; i<arows; i++){
            old_x(i,0) = B(i,0)/A(i,i);
            new_x(i,0) = old_x(i,0);
        }

        do{
            for (int i=0; i<arows; i++){
                old_x(i,0) = new_x(i,0);
            }

            for (int i=0; i<arows; i++){
                new_x(i,0) = B(i,0)/A(i,i);
                for (int j=0; j<acols; j++){
                    if (j!=i){
                        new_x(i,0) = new_x(i,0) - (A(i,j)/A(i,i))*new_x(j,0);
                    }
                }
            }

            iteraciones++;
            cout<<"new_x(" << iteraciones << ")= " << ~new_x << endl;

            //Calculamos el error en cada iteración:
            double error;
            error = NormaMaximaMatriz(inA*new_x-inB);
            ff<<error<<"\t\t"<<iteraciones<<endl;
        } while(NormaMaximaMatriz(inA*new_x-inB)>tol);
    }
    // Por el método de Gauss-Seidel se hacen estas iteraciones.
    cout<<"Método de Gauss-Seidel:"<<endl;
    cout<<"Número de iteraciones: "<<iteraciones<<endl;

    return new_x;
}

int main(){
    // Nombres de los archivos donde están las matrices y los abrimos en modo lectura.
    string ainfile = "matrizA.txt";
    string binfile = "matrizB.txt";
    ifstream file(ainfile);
    ifstream f(binfile);
    if (file.is_open()){
        if (f.is_open()){
            // Filas y columnas de ambas matrices.
            int arows = 0, acols = 0, brows = 0, bcols = 0;
            
            // Definimos la matriz A.
            file >> arows >> acols;
            matrix<double> A(arows, acols);
            file >> A;
            
            // Definimos la matriz B.
            f >> brows >> bcols;
            matrix<double> B(brows, bcols);
            f >> B;

            // Cerramos los ficheros.
            file.close();
            f.close();

            // Comprobamos si la matriz pasada es diagonal dominante mediante la función.
            bool dominante;
            dominante = DominanteDiagonal(A);
            if (dominante == true){
                cout<<"La matriz A es diagonal dominante."<<endl;
            } else {
                cout<<"¡Cuidado! La matriz A no es diagonal dominante."<<endl;
            }

            cout<<endl;

            // Calculamos la solución por Gauss-Seidel para una cierta tolerancia.
            double tol = 0.000001, error = 0.0;
            int iteraciones = 0;
            matrix<double> X(brows, bcols); X.null();
            X = MetodoGauss(A, B, tol, error, iteraciones);

            cout<<endl;
            cout<<"Matriz solución tras aplicar el método de Gauss-Seidel:"<<endl;
            cout<<X;

        }
    }

    return 0;
}