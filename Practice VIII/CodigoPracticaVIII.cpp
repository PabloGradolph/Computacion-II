#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

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

// Función que calcula la norma máxima de un vector. Pasando como parámetro un vector.
double NormaMaximaVector(double vector[], int len){
    double maximo = 0.0;
    for (int i=0; i<len; i++){
        if (fabs(vector[i])>maximo){
            maximo = fabs(vector[i]);
        }
    }

    return maximo;
}

// Función que calcula la nomra máxima de una matriz. Pasando como parámetro una matriz.
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
        if (sumatorio>maximo){
            maximo = sumatorio;
        }
    }

    return maximo;
}

// Función que calcula la solución de un sistema de ecuaciones lineales mediante el método iterativo de Jacobi.
matrix<double> MetodoJacobi(matrix<double> inA, matrix<double> inB, double tol){
    // Inicializamos las iteraciones a 0 y calculamos el tamaño de las matrices pasadas como argumento.
    // Pasamos la matriz de coeficientes y la matriz solución del sistema.
    int iteraciones = 0;
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

    // Calculamos las matrices de coeficientes
    for (int i=0; i<arows; i++){
        old_x(i,0) = B(i,0)/A(i,i);
        new_x(i,0) = old_x(i,0);
    }

    // Iteraciones
    do{
        for (int i=0; i<arows; i++){
            old_x(i,0) = new_x(i,0);
        }

        for (int i=0; i<arows; ++i){
            new_x(i,0)=B(i,0)/A(i,i);
      	    for (int j=0; j<acols; ++j){
      	        if (j != i){
                    new_x(i,0) = new_x(i,0) - (A(i,j)/A(i,i))*old_x(j,0) ;
                } 
      	    }
        }

        iteraciones++;
        cout<< "new_x(" << iteraciones <<")= " << ~new_x << endl;
    } while(NormaMaximaMatriz(inA*new_x-inB)>tol);

    // Por el método de Jacobi se hacen estas iteraciones.
    cout<<"Método de Jacobi:"<<endl;
    cout<<"Número de iteraciones: "<<iteraciones<<endl;

    // Retornamos nuestra matriz solución.
    return new_x;
}

// Función que calcula la solución de un sistema de ecuaciones lineales mediante el método iterativo de Gauss-Seidel.
matrix<double> MetodoGauss(matrix<double> inA, matrix<double> inB, double tol){
    // Inicializamos las iteraciones a 0 y calculamos el tamaño de las matrices pasadas como argumento.
    // Pasamos la matriz de coeficientes y la matriz solución del sistema.
    int iteraciones = 0;
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
    } while(NormaMaximaMatriz(inA*new_x-inB)>tol);

    // Por el método de Gauss-Seidel se hacen estas iteraciones.
    cout<<"Método de Gauss-Seidel:"<<endl;
    cout<<"Número de iteraciones: "<<iteraciones<<endl;

    return new_x;
}

int main(){
    // Leemos los archivos donde se encuentran las matrices de coeficientes y solución.
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

            cout<<endl;
            
            // Calculamos e imprimimos los resultados para el método de Jacobi.
            double tol = 0.000001;
            matrix<double> X(brows, bcols);
            X = MetodoJacobi(A, B, tol);
            cout<<"Matriz solución tras ese número de iteraciones: "<<endl<<X;
            cout<<endl;

            // Lo mismo para el método de Gauss.
            X = MetodoGauss(A, B, tol);
            cout<<"Matriz solución tras ese número de iteraciones: "<<endl<<X;
            cout<<endl;

        }
    }

    return 0;
}