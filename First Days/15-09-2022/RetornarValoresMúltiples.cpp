#include <iostream>
#include <cmath>
using namespace std;

// Definimos la constante pi
const double pi = M_PI;

// Definimos la función geo_circulo que retorna los varlores perímetro y área
double geo_circulo(const double radio, double& area, double& perimetro){
    perimetro = pi * radio * 2;
    area = pi * radio * radio;
}

// Función principal
int main(){

    // Definimos la variable radio y la pedimos por consola
    int radio;
    cout<<"Introduce un radio: ";cin>>radio;

    // Definimos las variables área y perímetro y llamamos a la función geo_circulo
    double area = 0., perimetro = 0.;
    geo_circulo(radio, area, perimetro);

    // Imprimimos los valores retornados por pantalla
    cout<<"El valor del área de un círculo de radio "<<radio<<" es: "<<area<<endl;
    cout<<"El valor del perímetro de un círculo de radio "<<radio<<" es: "<<perimetro<<endl;

    return 0;
}