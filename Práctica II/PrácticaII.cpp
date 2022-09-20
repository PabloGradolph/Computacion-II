/* 
Programa la función F, de funciones, que a cada función real le hace 
corresponder otra función real con la siguiente definición:
F(g)(x) = 2.5 si g(x)<1, 2 si 1<=g(x)<=2, 1.5 si 2<=g(x)<=3, 1 si 3<g(x).

Para funciones g(x) definidas en el intervalo x pertenece a [0,1]. Prueba 
la función anterior en un punto x perteneciente al intervalo [0,1] con 
los siguientes ejemplos desde un programa principal: sin(x), exp(5x), ln(0.01 + x).
*/

#include <iostream>
#include <math.h>
using namespace std;

// Esta función retornará el valor de F en función del valor de g(x).
double F(double g){
    // Definimos la variable F
    double F = 0.;
    
    // Calculamos su valor en función de g.
    if (g<1){
        F = 2.5;
    } else if (1<=g && g<2){
        F = 2.;
    } else if (2<=g && g<=3){
        F = 1.5;
    } else {
        F = 1.;
    }
    // Retornamos el valor F.
    return F;
}
// Esta función calcula el valor de g, y le manda el valor a la función anterior para calcular F.
void DistintosEjemplos(double PuntoX){
    // Cálculo de g en los distintos casos.
    double g1, g2, g3;
    g1 = sin(PuntoX);
    g2 = exp(5*PuntoX);
    g3 = log(0.01 + PuntoX);
    
    // Cálculo de F a través de la función F().
    double F1, F2, F3;
    F1 = F(g1);
    F2 = F(g2);
    F3 = F(g3);

    // Se imprimen los resultados por pantalla.
    cout<<"Para el ejemplo g(x) = sin(x), con el punto "<<PuntoX<<" --> F(g)(x) = "<<F1<<endl;
    cout<<"Para el ejemplo g(x) = exp(5x), con el punto "<<PuntoX<<" --> F(g)(x) = "<<F2<<endl;
    cout<<"Para el ejemplo g(x) = ln(0.01 + x), con el punto "<<PuntoX<<" --> F(g)(x) = "<<F3<<endl;
}

// Programa principal donde se llama a la función DistintosEjemplos() 
// y se elige un punto x del intervalo [0,1].
int main(){

    // Se explica por pantalla lo que hace el programa
    cout<<"Vamos a probar la función:"<<endl;
    cout<<"F(g)(x) = 2.5 si g(x)<1, 2 si 1<=g(x)<=2, 1.5 si 2<=g(x)<=3, 1 si 3<g(x)"<<endl;
    cout<<"Para los ejemplos sin(x), exp(5x) y ln(0.01 + x)"<<endl;

    // Se pide el valor de x al usuario.
    double PuntoX;
    cout<<"Por favor, ingrese un punto dentro del intervalo [0,1]: ";cin>>PuntoX;

    // El valor de x tiene que estar en el intervalo [0,1].
    while (PuntoX<0 || PuntoX>1){ // Esto ocurre si el punto x no está en el intervalo.
        cout<<"El punto no se encuentra dentro del intervalo."<<endl;
        cout<<"Por favor, ingrese un punto dentro del intervalo [0,1]: ";cin>>PuntoX;
    }

    // Si el punto x es correcto se llama a la función para que ejecute todo.
    DistintosEjemplos(PuntoX);

    return 0;
}