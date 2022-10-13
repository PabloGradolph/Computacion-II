#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

#include <chrono>
using namespace chrono;

// Función que retorn true o false en función de si la solución X del sistema A*X = B es correcta.
// Para ello calcula A*X - B y tiene que estar muy cercano a cero en función de una tolerancia.
bool ResultadoCorrecto(matrix<double> A, matrix<double> B, matrix<double> X, double tol){
    // Definimos el tamaño de las matrices pasadas como argumentos.
    int brows = 0, bcols = 0;
    brows = B.rowno();
    bcols = B.colno();

    matrix<double> x;
    x = A*X - B;

    bool correcto = true;

    for (int i=0; i<brows; i++){
        if (fabs(x(i,0)) < tol){
            continue;
        } else {
            correcto = false;
            break;
        }
    }

    return correcto;
}

// Función que retorna true o false en función de si la matriz pasada como argumento es tridiagonal o no.
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
                        sum = sum + fabs(A(i,j));
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
                        sum = sum + fabs(A(i,j));
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
                        sum = sum + fabs(A(i,j));
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

// Función que ejecuta el método LU para el caso donde la matriz A pasada como argumento es tridiagonal.
matrix<double> LuTridiagonal(matrix<double> A, matrix<double>F){
    // Definimos el tamaño de las matrices pasadas como argumentos.
    int arows = 0, acols = 0, frows = 0, fcols = 0;
    arows = A.rowno();
    acols = A.colno();
    frows = F.rowno();
    fcols = F.colno();

    // Definimos los 3 vectores de las 3 diagonales
    matrix<double> b(arows, 1); b.null();
    matrix<double> a(arows-1, 1); a.null();
    matrix<double> c(arows-1, 1); c.null();

    // Bucle en el que se dan los valores correspondientes a estos 3 vectores.
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

    // Definimos las matrices L y U.
    matrix<double> L(arows, acols); L.null();
    matrix<double> U(arows, acols); U.null();

    // Bucle en el que se dan los valores correspondientes a las matrices L y U.
    U(0,0) = b(0,0);
    L(0,0) = 1;
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i==j && i!=0){
                L(i,j) = 1;
                U(i,j) = b(i,0) - L(i,i-1)*c(i-1,0);
            } else if (i-j == -1){
                U(i,j) = c(i,0);
            } else if (i-j == 1){
                L(i,j) = a(i-1,0)/U(i-1,i-1);
            }
        }
    }
    
    // Calculamos la matriz z (Lz = F)
    matrix<double> z(frows, fcols); z.null();
    z(0,0) = F(0,0);
    for (int i=1; i<frows; i++){
        z(i,0) = F(i,0) - L(i,i-1)*z(i-1,0);
    }
    
    // Calculamos la matriz x (Ux = z)
    matrix<double> x(frows, fcols); x.null();
    x(frows-1,0) = z(frows-1,0)/U(frows-1,frows-1);
    for (int i=frows-2; i>=0; i--){
        x(i,0) = (z(i,0) - c(i,0)*x(i+1,0)) / U(i,i);
    }

    // El método de cálculo de estas dos matrizes (z y x) está sacado de la teoría.
    
    //
    // Comprobaciones hechas para asegurarme de que la solución es correcta. 
    // x = L*U - A; x Da cero. :)
    // x = L*z - F; x Da cero. :)
    // x = U*x - z; x Da cero. :)
    // x = abs((A*x) - F); x Da cero. :)
    //

    // Retornamos el valor de la matriz solución.
    return x;
}

// Función principal.
int main(){
    // Abrimos los ficheros de dónde leemos los datos de las matrices.
    // Estas matrices se han generado mediante el código del fichero 'CreacionMatrices.cpp'.
    string ainfile = "matrizA.txt";
    string finfile = "matrizF.txt";
    ifstream ffile(ainfile);
    ifstream ff(finfile);
    if (ffile.is_open()){
        if(ff.is_open()){
            
            // Para este caso el número de filas de las matrices es 10.
            // Cambiar en caso necesario.
            int n = 10;

            // Traemos a la matriz A del fichero. Ya sabemos el tamaño de dicha matriz.
            matrix<double> A(n,n);
            ffile >> A;

            // Comprobamos que la matriz A es tridiagonal mediante la función que hemos creado anteriormente.
            bool tridiagonal;
            tridiagonal = Tridiagonal(A);

            // Tanto si es tridiagonal como si no, se avisa.
            if (tridiagonal == true){
                cout<<"La matriz A es tridiagonal"<<endl;
            } else {
                cout<<"La matriz A no es tridiagonal"<<endl;
            }

            // Sólo en caso de ser tridiagonal, seguiremos adelante.
            if (tridiagonal == true){
                // Leemos del fichero la matriz F.
                matrix<double> F(n,1);
                ff >> F;

                // Medimos cuanto tarda el proceso de cálculo de X a partir de A y F
                time_point<system_clock> start, end;
                duration<double> elapsed_seconds;
                start = system_clock::now();

                // Calculamos la matriz solución X mediante la función definida anteriormente.
                matrix<double> X;
                X = LuTridiagonal(A, F);

                // Aquí se termina de medir el tiempo y se imprime por pantalla.
                end = system_clock::now();
                elapsed_seconds = end - start;
                cout<<"* Tiempo LU Tridiagonal (s) = "<<elapsed_seconds.count()<<endl;

                // Comprobamos si la matriz solución es correcta para una cierta tolerancia.
                bool correcto = false;
                correcto = ResultadoCorrecto(A, F, X, 0.0001);
                if (correcto==true){
                    cout<<"La matriz solución X es correcta para una tolerancia 0.0001"<<endl;
                } else {
                    cout<<"La matriz solución X NO es correcta para una tolerancia 0.0001"<<endl;
                }

                // Se guarda el resultado en un fichero externo.
                string infile = "ResultadoLuTridiagonal.txt";
                ofstream file(infile);
                if (file.is_open()){
                    file << "La matriz solución tras aplicar el método LU para matrices tridiagonales es:"<<endl;
                    file << X;
                }
            }
        }
    }
}