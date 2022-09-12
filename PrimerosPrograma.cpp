//Resta de dos números
//Suma de dos vectores

#include <iostream>

using namespace std;

int main(){

    // Definimos las variables
    int a = 5, b = 3, resta;
    int vector1[3] = {1,2,3}, vector2[3] = {4,5,6}, suma[3];

    // Operaciones necesarias
    resta = a - b;
    for (int i=0; i<5; i++){
        suma[i] = vector1[i] + vector2[i];
    }

    // Imprimimos resultados
    cout<<"La resta de 5 menos 3 es igual a: "<<resta<<endl;
    cout<<"La suma de los vectores {1,2,3} y {4,5,6} es igual a: ";
    for (int i=0;i<3;i++){
        cout<<suma[i]<<" ";
    }
    
    return 0;
}
    
	