/* Realiza una función que obtenga el máximo, el mínimo y los índices 
correspondientes de los elementos de un vector. */
#include <iostream>
using namespace std;

// Definimos la función que nos va a dar el máximo y el mínimo del vector
double MaxMinIndice(const double vector[], const int len, double& max, double& min){

    // Variables que vamos a utilizar
    double valor = 0.;
    max = vector[0]; min = vector[0];

    // Bucle con el cuál estableceremos los índices con sus valores y el máximo y mínimo del vector
    for (int i=0; i<len; ++i){
        valor = vector[i];
        cout<<"Índice "<<i<<" --> Valor: "<<valor<<endl;
        if (max<valor){
            max = valor;
        } else if (min>valor){
            min = valor;
        } else{
            continue;
        }
    }
    
    int posicionMax, posicionMin;
    for (int i=0; i<len; ++i){
        valor = vector[i];
        if (max==valor){
            posicionMax = i;
        } else if (min==valor){
            posicionMin = i;
        }
    }
    // Imprimimos por pantalla el máximo y el mínimo del vector.
    cout<<"El máximo del vector es: "<<max<<" --> Índice: "<<posicionMax<<endl;
    cout<<"El mínimo del vector es: "<<min<<" --> Índice: "<<posicionMin<<endl;
}

int main(){
    // Definimos las variables que vamos a pasar a la función.
    int len = 5;
    double max = 0., min = 0.;

    // Definimos el vector con su longitud.
    double vector[len] = {-54.3, -12, 0, 587, 340.8};

    // Llamamos a la función para que se ejecute.
    MaxMinIndice(vector, len, max, min);

    return 0;
}