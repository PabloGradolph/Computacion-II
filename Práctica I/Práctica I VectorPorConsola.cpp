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
    int len;
    double max = 0., min = 0.;

    // El usuario establece la longitud del vector.
    cout<<"Introduce la longitud del vector: "; cin>>len;

    // Si la longitud es menor o igual que cero no continuará el programa.
    if (len<=0){
        cout<<"Longitud del vector no válida.";
    } else{
        // Definimos el vector con su longitud.
        double vector[len];

        // El usuario construye el vector.
        cout<<"Introduzca el primer elemento del vector: "; cin>>vector[0];
        for (int i=1; i<len; ++i){
            cout<<"Introduzca otro elemento del vector: "; cin>>vector[i];
        }
        cout<<endl;

        // Llamamos a la función para que se ejecute.
        MaxMinIndice(vector, len, max, min);
    }

    return 0;
}




