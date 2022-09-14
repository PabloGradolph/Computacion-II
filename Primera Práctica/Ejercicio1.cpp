//Erjercicio 1. Realizar sumatorio.

#include <iostream>
#include <cmath>
using namespace std;

int main(){

    //Definimos las variables
    //Si ponemos más ceros en el max sale como resultado inf (por ser número demasiado grande para un double)
    int max = 10000;
    double sum = 0, pi = M_PI, sumatorio, error;

    //Bucle hasta un número alto haciendo el sumatorio.
    for(int i=1; i<=max; i++){
        sum += 1./(i*i);
    }

    cout<<"El sumatorio para "<<max<<" iteraciones es: "<<sum<<endl;

    //Calculamos el error que se produce
    sumatorio = (pi*pi)/6;
    error = sumatorio - sum;
    cout<<"El valor exacto para el sumatorio es: "<<sumatorio<<endl;
    cout<<"Por lo tanto, el error cometido es de "<<error<<endl;

    return 0;
}