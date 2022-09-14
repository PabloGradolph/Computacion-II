//Ejercicio 2.
//Ordenar de menor a mayor la siguiente serie de números enteros:
//34, 70, 5, 89, 6, 3220, 1

#include <iostream>
#include <algorithm>
using namespace std;

int main(){

    //Definimos la lista con los números
    int lista[7] = {34, 70, 5, 89, 6, 3220, 1};

    //Ordenamos la lista
    sort(lista, lista+7);

    //La imprimimos por pantalla
    cout<<"Imprimiendo la lista de números ordenada:"<<endl;
    for (int i=0; i<7; i++){
        cout<<lista[i]<<" - ";
    }
    
    return 0;
}