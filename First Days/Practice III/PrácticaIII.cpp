/* 
Realiza un programa que obtenga los siguientes sumatorio y producto:
    - Sumatorio: desde i=0 hasta 8 de los xi elevados al cuadrado.
    - Producto: desde i=0 hasta 8 de los e elevados a xi.
Donde los xi son nueve números que leerá de un fichero.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

int main(){
    // Definimos el vector que contendrá los datos 
    // y el nombre del fichero del que sacaremos los datos.
    int array[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    string filename = "numbers.txt";

    // Leemos el fichero y guardamos los datos en el array.
    ifstream ffin(filename);
        if (ffin.is_open()){
            string row;
            int ii = 0;
            while(getline(ffin, row)){
                array[ii] = stoi(row);
                ii = ii + 1;
            }

            // Calculamos la suma y el producto.
            int sum = 0;
            double producto = 1.;
            for (int i=0; i<=8; i++){
                sum += pow(array[i], 2);
                producto = producto * exp(array[i]);
            }
            
            // Los imprimimos por pantalla.
            cout<<"Sumatorio = "<<sum<<endl;
            cout<<"Producto = "<<producto<<endl;

            ffin.close();
        } else {
            cout<<"The file can not be open.";
        }

    return 0;
}
