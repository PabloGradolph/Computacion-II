#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;


matrix<double> MetodoLU(matrix<double> A, matrix<double> B){
    int arows = 0, acols = 0, brows = 0, bcols = 0;
    arows = A.rowno();
    acols = A.colno();
    brows = B.rowno();
    bcols = B.colno();

    matrix<double> L(arows, acols); L.null();
    matrix<double> U(arows, acols); U.null();

    // Establecemos los números por defecto que tienen L y U (ceros y unos).
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i==j){
                L(i,j) = 1;
            }else if (i>j){
                U(i,j) = 0;
            }else{
                L(i,j) = 0;
            }
        }
    }

    // Establecemos la primera fila de la matriz U.
    for(int i=0; i<acols; i++){
        U(0,i) = A(0, i);
    }

    // Calculamos la columna[0] de la matriz L.
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i>j && j==0){
                L(i,j) = (1/U(0,0))*A(i,j);
            }
        }
    }

    // Calculamos el resto de números de las matrices
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            // Si i = j, calculamos el valor de U(i,j)
            if (i==j){
                matrix<double> SUM(arows, acols); SUM.null();
                for (int k=0; k<i; k++){
                    SUM(i,j) = SUM(i,j) + (L(i,k)*U(k,j));
                    U(i,j) = A(i,j) - SUM(i,j);
                }
            // Si i>j y no estamos en la primera columna(ya calculada) calculamos el valor de L(i,j)
            } else if(i>j && j!=0){
                matrix<double> SUM(arows, acols); SUM.null();
                for (int k=0; k<j; k++){
                    SUM(i,j) = SUM(i,j) + (L(i,k)*U(k,j));
                    L(i,j) = (A(i,j)/U(j,j)) - (SUM(i,j)/U(j,j));
                }
            // Si j>i calculamos el valor de U(i,j)
            } else if(j>i){
                matrix<double> SUM(arows, acols); SUM.null();
                for (int k=0; k<i; k++){
                    SUM(i,j) = SUM(i,j) + (L(i,k)*U(k,j));
                    U(i,j) = A(i,j) - SUM(i,j);
                  }
            }
        }
    }

    // Resolvemos ahora L*z = b
    matrix<double> z(brows, bcols); z.null();
    z(0,0) = B(0,0);
    for (int i=0; i<arows; i++){
        double sum=0.0;
        for (int j=0; j<acols; j++){
            sum = sum + L(i,j)*z(j,0);
        }
        if (i!=0){
            z(i,0) = B(i,0) - sum;
        }
    }

    // Resolvemos ahora U*x=z
    matrix<double> x(brows, bcols); x.null();
    for (int i=arows-1; i>=0; i--){
        double sum=0.0;
        for (int j=0; j<acols; j++){
            sum = sum + U(i,j)*x(j,0);
        }
        x(i,0) = (z(i,0) - sum)/U(i,i);
    }
    return x;
}

int main(){
    string ainfile = "matrizA2.txt";
    string binfile = "matrizB2.txt";
    ifstream ffile(ainfile);
    ifstream ff(binfile);
    if (ffile.is_open()){
        if (ff.is_open()){
            // Filas y columnas de ambas matrices.
            int arows = 0, acols = 0, brows = 0, bcols = 0;
            
            // Definimos la matriz A.
            ffile >> arows >> acols;
            matrix<double> A(arows, acols);
            ffile >> A;

            // Para el caso del ejercicio 2 hay 6 valores que tenemos que modificar.
            // Para el ejercicio 1 hay que borrar/comentar este bucle y cambiar el nombre del archivo.
            for (int i=0; i<arows; i++){
                for (int j=1; j<acols; j++){
                    if (j==1){
                        A(i,j)=pow(A(i,j),-2);
                    } else if (j==2){
                        A(i,j)=pow(A(i,j),-4);
                    }
                }
            }
            
            // Definimos la matriz B.
            ff >> brows >> bcols;
            matrix<double> B(brows, bcols);
            ff >> B;

            // Cerramos los ficheros.
            ffile.close();
            ff.close();

            // Definimos la que será la matriz solución por el método LU
            matrix<double> X; X.null();
            X = MetodoLU(A, B);
            cout<<"La matriz de soluciones es:"<<endl; cout<<X;
        }else {
            cout<<"No se ha podido abrir el fichero "<<binfile<<endl;
        }

    }else{
        cout<<"No se ha podido abrir el fichero "<<ainfile<<endl;
    }

    return 0;

}