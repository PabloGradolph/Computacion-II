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

// Función para el cálculo de la solución de un sistema de ecuaciones lineal por el método de factorización LU.
matrix<double> MetodoLU(matrix<double> A, matrix<double> B){
    // Guardamos el tamaño de las matrices pasadas como argumento. (A*X=B) siendo X la solución que buscamos.
    int arows = 0, acols = 0, brows = 0, bcols = 0;
    arows = A.rowno();
    acols = A.colno();
    brows = B.rowno();
    bcols = B.colno();

    // Definimos las matrices L y U que utilizaremos más adelante.
    matrix<double> L(arows, acols); L.null();
    matrix<double> U(arows, acols); U.null();

    // Establecemos los números por defecto que tienen L y U (ceros y unos).
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i==j){
                // Los elementos de la diagonal en L son unos.
                L(i,j) = 1;
            }else if (i>j){
                // Por debajo de la diagonal los elementos de U son ceros.
                U(i,j) = 0;
            }else{
                // Por encima de la diagonal los elementos de L son ceros.
                L(i,j) = 0;
            }
        }
    }

    // Establecemos la primera fila de la matriz U que es igual a la de coeficientes A.
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
            // Si i = j, calculamos el valor de U(i,j). Son los elementos de la diagonal, en L son los unos anteriores.
            if (i==j){
                matrix<double> SUM(arows, acols); SUM.null();
                for (int k=0; k<i; k++){
                    SUM(i,j) = SUM(i,j) + (L(i,k)*U(k,j));
                    U(i,j) = A(i,j) - SUM(i,j);
                }
            // Si i>j y no estamos en la primera columna (ya calculada) calculamos el valor de L(i,j)
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

    // Resolvemos ahora L*z = b. Sacamos el valor de z.
    matrix<double> z(brows, bcols); z.null();
    // Necesitamos el primer valor de z para calcular los siguientes. Gracias a la forma de L z(0,0) = B(0,0).
    z(0,0) = B(0,0);
    for (int i=0; i<arows; i++){
        double sum=0.0;
        for (int j=0; j<acols; j++){
            sum = sum + L(i,j)*z(j,0);
        }
        if (i!=0){
            // El valor donde i = 0 es el primero que hemos calculado.
            z(i,0) = B(i,0) - sum;
        }
    }

    // Resolvemos ahora U*x=z.
    matrix<double> x(brows, bcols); x.null();
    for (int i=arows-1; i>=0; i--){
        double sum=0.0;
        for (int j=0; j<acols; j++){
            sum = sum + U(i,j)*x(j,0);
        }
        x(i,0) = (z(i,0) - sum)/U(i,i);
    }
    return x;

    // Las fórmulas para los cálculos anteriores están en la teoría. Página 3 del pdf "SistemaslinealesMétodosdirectos".
}

// Función que calcula la solución de un sistema de ecuaciones lineales mediante el método iterativo de Jacobi.
int MetodoJacobi(matrix<double> inA, matrix<double> inB, double tol){
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
    return iteraciones;
}

// Función que calcula la solución de un sistema de ecuaciones lineales mediante el método iterativo de Gauss-Seidel.
int MetodoGauss(matrix<double> inA, matrix<double> inB, double tol){
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

    return iteraciones;
}

int main(){

    //
    // APARTADO A)
    //

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

            // Definimos la que será la matriz solución por el método LU
            matrix<double> X; X.null();
            X = MetodoLU(A, B);
            cout<<"La matriz de soluciones por el metodo LU es:"<<endl; cout<<X;

            // Comprobamos que nuestro resultado es correcto para una cierta tolerancia.
            double tol = 0.0001, max = 0.0;
            matrix<double> Sol; Sol.null();
            Sol = A*X-B; max = NormaMaximaMatriz(Sol);
            if (max > tol){
                cout<<endl;
                cout<<"Tras la comprobación A*X-B = 0, hay algún valor de la matriz que no está por debajo de la tolerancia."<<endl;
            }
        }else {
            cout<<"No se ha podido abrir el fichero "<<binfile<<endl;
        }
    }else{
        cout<<"No se ha podido abrir el fichero "<<ainfile<<endl;
    }

    //
    // APARTADOS B) Y C)
    //
    cout<<endl;

    // Guardamos la solución anterior en otra matriz llamada LU. (Tamaño de matriz B anterior)
    matrix<double> LU(5, 1); LU.null();
    LU(0,0) = -0.218474;
    LU(1,0) = -1.84989;
    LU(2,0) = 3.54294;
    LU(3,0) = -0.715102;
    LU(4,0) = 5.52125;

    // Leemos los archivos donde se encuentran las matrices de coeficientes y solución.
    string afile = "matrizAJacobiGauss.txt";
    string bfile = "matrizBJacobiGauss.txt";
    ifstream ffile(afile);
    ifstream ff(bfile);
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
            
            // Calculamos y guardamos los resultados en un fichero para el método de Jacobi.
            // Vamos variando la tolerancia.
            int iteraciones = 0; double tol = 0.000000000001;
            string Jacobifile = "IteracionesJacobi.txt";
            ofstream fichero(Jacobifile);
            if (fichero.is_open()){
                fichero<<"#ITERACIONES JACOBI PARA CIERTA TOLERANCIA"<<endl;
                fichero<<"eps\t\titeraciones"<<endl;
                for (double i=0.001; i>=tol; i=i/10){
                    iteraciones = MetodoJacobi(A, B, i);
                    fichero<<i<<"\t\t"<<iteraciones<<endl;
                }

                fichero.close();
            }

            string Gaussfile = "IteracionesGauss.txt";
            ofstream fich(Gaussfile);
            if (fich.is_open()){
                fich<<"#ITERACIONES GAUSS PARA CIERTA TOLERANCIA"<<endl;
                fich<<"eps\t\titeraciones"<<endl;
                for (double i=0.001; i>=tol; i=i/10){
                    iteraciones = MetodoGauss(A, B, i);
                    fich<<i<<"\t\t"<<iteraciones<<endl;
                }
            }
        }
    }

    cout<<endl;

    return 0;
}

