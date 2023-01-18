/*
Realiza un programa que lea números reales de un fichero
y guarde en otro fichero la raíz cuadrada de aquellos que 
sean mayores que 1.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

int main(){

    // Definimos el nombre del fichero del que sacaremos los datos.
    string filename = "reales.txt";

    // Variables que vamos a utilizar.
    string row; // Guardar cada fila del fichero.
    int length; // Cantidad de filas del fichero.
    char ca;    // Carácteres del fichero, nos servirá para ver si hay un salto de línea o no.

    // Contamos el número de líneas del fichero 'reales.txt'.
    FILE *puntero;
    puntero = fopen("reales.txt", "r");

    while(1){

        // Cogemos cada carácter del fichero.
        ca = fgetc(puntero);

        // Si el carácter es un salto de línea sumamos 1 a length.
        if(ca == '\n'){
            length++;
        }

        // Si el carácter es un end of file, terminamos.
        if(ca == EOF){
            break;
        }
    }

    // Leemos el fichero y guardamos los datos en el array.
    ifstream ffin(filename);
        if (ffin.is_open()){

            // Variables array y posición en el array.
            float array[length];
            int ii = 0;
            
            // Guardamos los datos del fichero en el array.
            while(getline(ffin, row)){
                array[ii] = stod(row);
                ii++;
            }

            // Contamos cuantos valores del array son mayores que 1.
            int cont = 0;
            for (int i=0; i<=length; i++){
                if (array[i]>1){
                    cont++;
                }
            }

            // Creamos otro array con la cantidad de valores mayores que 1.
            float array_positivos[cont];
            int jj = 0;

            // Guardamos esos valores mayores que 1 en el nuevo array.
            for (int i=0; i<=length; i++){
                if (array[i]>1){
                    array_positivos[jj] = array[i];
                    jj++;
                }
            }

            // Por cada valor calculamos su raíz cuadrada.
            for (int i=0; i<cont; i++){
                array_positivos[i] = sqrt(array_positivos[i]);
            }

            // Creamos el nuevo fichero donde irán los nuevos datos calculados.
            string infile = "raices.txt";

            ofstream ff(infile);
            if (ff.is_open()){
                
                // Metemos los datos en el fichero.
                for (int i=0; i<cont; i++){
                    ff << array_positivos[i] << endl;
                }

                // Cerramos el fichero 'raices.txt'.
                ff.close();

            }else{
                cout<<"The file can not be open.";
            }

            // Cerramos el fichero 'reales.txt'.
            ffin.close();

        }else{
            cout<<"The file can not be open.";
        }

    return 0;
}