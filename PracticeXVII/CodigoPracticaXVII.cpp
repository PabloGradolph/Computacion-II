// Código Práctica XVII
// Resolución de ecuaciones diferenciales de segundo orden con condiciones de contorno:
// Método de las diferencias finitas.
// Autor: Pablo Gradolph Oliva
// Fecha: 05/12/2022

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Solución exacta para comparar resultados al final.
double uReal(double r){
    double u1 = 110.0, R1 = 5.0, R2 = 10.0;
    double u = 0.0;
    u = ((u1*R1)/r) * ((R2-r)/(R2-R1));
    return u;
}

// Función que devuelve el polinomio p(x) para nuestro caso
double polP(double x){
    double p = -2/x;
    return p;
}

// Función que devuelve el polinomio q(x) para nuestro caso
double polQ(double x){
    // Cambiar el valor del polinomio q(x) cuando sea necesario.
    // En este caso el polinomio es igual a cero.
    double q = 0.0;
    return q;
}

// Función que devuelve el polinomio r(x) para nuestro caso
double polR(double x){
    // Cambiar el valor del polinomio r(x) cuando sea necesario.
    // En este caso el polinomio es igual a cero.
    double r = 0.0;
    return r;
}

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

// Función para comprobar si la matriz es cuadrada.
bool Cuadrada(matrix<double> A){
    // Definimos el tamaño de la matriz A pasada como argumento.
    int arows = 0, acols = 0;
    arows = A.rowno();
    acols = A.colno();

    // Booleano que define si la matriz es cuadrada o no.
    bool cuadrada = false;
    if (arows == acols){
        cuadrada = true;
    }

    return cuadrada;
}

// Función que devuelve true o false en función de si el número de columnas de A es igual al número de filas de B.
bool FilasColumnas(matrix<double> A, matrix<double> B){
    // Comparamos las filas de A con las columnas de B.
    int acols = 0, brows = 0;
    acols = A.colno(); brows = B.rowno();

    bool iguales = false;
    if (acols == brows){
        iguales = true;
    }

    return iguales;
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

    // Bucle en el que se dan los valores correspondientes a estos 3 vectores. Son las 3 diagonales.
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

    return x;
}

matrix<double> EDODiferenciasFinitas(double h, double xmin, double xmax, double u0, double un){
    // Definimos el número de pasos e inicializamos x.
    double n = 0.0, x = xmin;
    n = (xmax - xmin)/h;
    cout<<"Dividimos el intervalo ["<<xmin<<","<<xmax<<"] en "<<n<<" subintervalos de longitud "<<h<<endl;

    // Hacemos n entero para poder definir el tamaño de las matrices.
    n = int(n);

    // La que será la matriz solución
    matrix<double> X;

    // Creamos las matrices con los valores de p(x), q(x) y r(x) para los distintos valores de x.
    // La primera fila depende de los p1, q1, r1, no de los cero.

    // Matriz p
    matrix<double> p(n,1); p.null();
    for (int i=0; i<=n; i++){
        p(i,0) = polP(x);
        x = x + h;
    }

    // Matriz q
    matrix<double> q(n,1); q.null();
    for (int i=0; i<=n; i++){
        q(i,0) = polQ(x);
        x = x + h;
    }

    // Matriz r
    matrix<double> r(n,1); r.null();
    for (int i=0; i<=n; i++){
        r(i,0) = polR(x);
        x = x + h;
    }

    // Creamos las matrices A y b.
    matrix<double> A(n,n); A.null();
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i==j){
                A(i,j) = 2 + (h*h*q(i+1,0));
            } else if (i-j == 1){
                A(i,j) = -(h/2. * p(i+1,0) + 1);
            } else if (i-j == -1){
                A(i,j) = (h/2. * p(i+1,0)) - 1;
            } else {
                A(i,j) = 0.0;
            }
        }
    }

    matrix<double> b(n,1); b.null();
    for (int i=0; i<n; i++){
        if (i==0){
            b(i,0) = -(h*h*r(i+1,0)) + (h/2. * p(i+1,0) + 1)*u0;
        } else if (i==n-1){
            b(i,0) = -(h*h*r(i+1,0)) - (h/2. * p(i+1,0) - 1)*un;
        } else {
            b(i,0) = -(h*h*r(i+1,0));
        }
    }

    // Comprobamos que la matriz A es tridiagonal y cuadrada mediante las funciones que hemos creado anteriormente.
    bool tridiagonal, cuadrada;
    tridiagonal = Tridiagonal(A);
    cuadrada = Cuadrada(A);

    // Tanto si es tridiagonal como si no, se avisa.
    if (tridiagonal == true){
        cout<<"La matriz A es tridiagonal"<<endl;
    } else {
        cout<<"La matriz A no es tridiagonal"<<endl;
    }

    // Tanto si la matriz es cuadrada como si no, se avisa.
    if (cuadrada == true){
        cout<<"La matriz A es cuadrada"<<endl;
    } else {
        cout<<"La matriz A no es cuadrada"<<endl;
    }

    // Sólo en caso de ser tridiagonal, seguiremos adelante.
    if (tridiagonal == true && cuadrada == true){
        // Comprobamos que el número de columnas de A es igual que el número de filas de F.
        bool iguales;
        iguales = FilasColumnas(A, b);

        if (iguales==true){
            // Calculamos la matriz solución X mediante la función definida anteriormente.
            X = LuTridiagonal(A, b);
        }

        // Comprobamos si la matriz solución es correcta para una cierta tolerancia.
        bool correcto = false;
        correcto = ResultadoCorrecto(A, b, X, 0.0001);
        if (correcto==true){
            cout<<"La matriz solución X es correcta para una tolerancia 0.0001"<<endl;
        } else {
            cout<<"La matriz solución X NO es correcta para una tolerancia 0.0001"<<endl;
        }
    }

    return X;
}

int main(){
    // Definimos las variables que vamos a utilizar posteriormente.
    double h = 0.05, rmin = 5, rmax = 10, u0 = 110.0, un = 0.0, error = 0.0;
    matrix<double> Solucion; Solucion.null();

    double npasos = (rmax-rmin)/h;
    npasos = int(npasos);
    Solucion = EDODiferenciasFinitas(h, rmin, rmax, u0, un);
    string file = "MatrizU_h0.05.txt";
    ofstream ff(file);
    if (ff.is_open()){
        double r;
        r = rmin;
        error = fabs(u0-uReal(r));
        ff << "r\tu(DF)\tu(exacta)\terror" << endl;
        ff << r << "\t" << u0 << "\t" << uReal(r) << "\t" << error << endl;
        for (int i=0; i<npasos-1; i++){
            r = r + h;
            error = fabs(Solucion(i,0)-uReal(r));
            ff << r << "\t" << Solucion(i,0) << "\t" << uReal(r) << "\t" << error << endl;
        }
        r = rmax;
        error = fabs(un-uReal(r));
        ff << r << "\t" << un << "\t" << uReal(r) << "\t" << error << endl;
        cout<<"Resultado en el fichero: "<<file<<endl;
    }

    cout<<endl;
    h = 0.02;
    npasos = (rmax-rmin)/h;
    npasos = int(npasos);
    Solucion = EDODiferenciasFinitas(h, rmin, rmax, u0, un);
    string ffile = "MatrizU_h0.02.txt";
    ofstream f(ffile);
    if (f.is_open()){
        double r;
        r = rmin;
        error = fabs(u0-uReal(r));
        f << "r\tu(DF)\tu(exacta)\terror" << endl;
        f << r << "\t" << u0 << "\t" << uReal(r) << "\t" << error << endl;
        for (int i=0; i<npasos-1; i++){
            r = r + h;
            error = fabs(Solucion(i,0)-uReal(r));
            f << r << "\t" << Solucion(i,0) << "\t" << uReal(r) << "\t" << error << endl;
        }
        r = rmax;
        error = fabs(un-uReal(r));
        f << r << "\t" << un << "\t" << uReal(r) << "\t" << error << endl;
        cout<<"Resultado en el fichero: "<<ffile<<endl;
    }

    cout<<endl;
    h = 0.01;
    npasos = (rmax-rmin)/h;
    npasos = int(npasos);
    Solucion = EDODiferenciasFinitas(h, rmin, rmax, u0, un);
    string files = "MatrizU_h0.01.txt";
    ofstream fff(files);
    if (fff.is_open()){
        double r;
        r = rmin;
        error = fabs(u0-uReal(r));
        fff << "r\tu(DF)\tu(exacta)\terror" << endl;
        fff << r << "\t" << u0 << "\t" << uReal(r) << "\t" << error << endl;
        for (int i=0; i<npasos-1; i++){
            r = r + h;
            error = fabs(Solucion(i,0)-uReal(r));
            fff << r << "\t" << Solucion(i,0) << "\t" << uReal(r) << "\t" << error << endl;
        }
        r = rmax;
        error = fabs(un-uReal(r));
        fff << r << "\t" << un << "\t" << uReal(r) << "\t" << error << endl;
        cout<<"Resultado en el fichero: "<<files<<endl;
    }

    return 0;
}
