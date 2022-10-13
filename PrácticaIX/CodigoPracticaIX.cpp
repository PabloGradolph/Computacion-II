#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

bool Tridiagonal(matrix<double> A){
    // Definimos el tamaño de la matriz A pasada como argumento.
    int arows = 0, acols = 0;
    arows = A.rowno();
    acols = A.colno();

    bool Tridiagonal = false;

    // Comprobamos si todos los elementos de fuera de las tres diagonales son ceros.
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i!=j && i - j != 1 && i - j != -1){
                if (A(i,j) == 0){
                    Tridiagonal = true;
                } else {
                    Tridiagonal = false;
                    break;
                }
            }
        }
    }

    // Si todos los elementos de fuera de las tres diagonales son ceros.
    // Comprobamos que ninguna de las diagonales sea entera igual a cero.
    if (Tridiagonal == true){
        // Comprobamos la diagonal principal.
        for (int i=0; i<3; i++){
            double sum = 0.0;
            for (int i=0; i<arows; i++){
                for (int j=0; j<acols; j++){
                    if (i==j){
                        sum = sum + A(i,j);
                    }
                }
            }

            if (sum==0){
                Tridiagonal = false;
                break;
            }

            // Comprobamos la diagonal adyacente de abajo.
            sum = 0.0;
            for (int i=0; i<arows; i++){
                for (int j=0; j<acols; j++){
                    if (i-j==1){
                        sum = sum + A(i,j);
                    }
                }
            }

            if (sum==0){
                Tridiagonal = false;
                break;
            }

            // Comprobamos la diagonal adyacente de arriba.
            sum = 0.0;
            for (int i=0; i<arows; i++){
                for (int j=0; j<acols; j++){
                    if (i-j==-1){
                        sum = sum + A(i,j);
                    }
                }
            }

            if (sum==0){
                Tridiagonal = false;
                break;
            }
        }
    }

    return Tridiagonal;
}

matrix<double> LuTridiagonal(matrix<double> A, matrix<double>F){
    int arows = 0, acols = 0, frows = 0, fcols = 0;
    arows = A.rowno();
    acols = A.colno();
    frows = F.rowno();
    fcols = F.colno();

    // Definimos los 3 vectores de las 3 diagonales
    matrix<double> b(arows, 1); b.null();
    matrix<double> a(arows-1, 1); a.null();
    matrix<double> c(arows-1, 1); c.null();

    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i==j){
                b(i,0) = A(i,j);
            } else if (i-j == 1){
                a(i-1,0) = A(i,j);
            } else if (i-j == -1){
                c(i,0) = A(i,j);
            }
        }
    }

    matrix<double> L(arows, acols); L.null();
    matrix<double> U(arows, acols); U.null();

    // Definimos la matriz U.
    U(0,0) = b(0,0);
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i==j && i!=0){
                U(i,j) = b(i,0);
            } else if (i-j == -1){
                U(i,j) = c(i,0);
            }
        }
    }

    // A partir de la matriz U, ya podemos calcular la matriz L.
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i==j){
                L(i,j) = 1;
            }
            if (i-j == 1){
                L(i,j) = a(i-1,0)/b(i-1,0);
            }
        }
    }

    // Calculamos la matriz z (Lz = F)
    matrix<double> z(frows, fcols); z.null();
    z(0,0) = F(0,0);
    for (int i=1; i<frows; i++){
        z(i,0) = F(i,0) - L(i,i-1)*z(i-1,0);
    }
    cout<<"L*z - F:"<<endl;
    cout<<L*z - F;
    
    // Calculamos la matriz x (Ux = z)
    matrix<double> x(frows, fcols); x.null();
    x(frows-1,0) = z(frows-1,0)/b(frows-1,0);
    for (int i=frows-2; i>=0; i--){
        x(i,0) = (z(i,0) - c(i,0)*x(i+1,0)) / b(i,0);
    }
    
    //x = abs((A*x) - F);
    return x;
}

int main(){
    string ainfile = "matrizA.txt";
    string finfile = "matrizF.txt";
    ifstream ffile(ainfile);
    ifstream ff(finfile);
    if (ffile.is_open()){
        if(ff.is_open()){
            
            // Para este caso el número de filas de las matrices es 1000.
            int n = 10;

            matrix<double> A(n,n);
            ffile >> A;

            // Comprobamos que la matriz A es tridiagonal.
            bool tridiagonal;
            tridiagonal = Tridiagonal(A);
            if (tridiagonal == true){
                cout<<"La matriz A es tridiagonal"<<endl;
            } else {
                cout<<"La matriz A no es tridiagonal"<<endl;
            }

            if (tridiagonal == true){
                matrix<double> F(n,1);
                ff >> F;

                matrix<double> X;
                X = LuTridiagonal(A, F);
                //cout<<X;
            }
            

            // Comprobación de la matriz F para ver que funciona la función Tridiagonal.
            /* matrix<double> F(n,n);
            ff >> F;

            tridiagonal = Tridiagonal(F);
            if (tridiagonal == true){
                cout<<"La matriz F es tridiagonal"<<endl;
            } else {
                cout<<"La matriz F no es tridiagonal"<<endl;
            }*/
        }
    }
}