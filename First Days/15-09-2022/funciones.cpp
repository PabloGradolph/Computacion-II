//Trabajando con funciones en C++
#include <iostream>
using namespace std;

// Definimos una función void(vacío) por lo que no hace falta return.
void area(){
  // Definimos pi
  float pi = 22./7.;

  // Pide que se escriba un número en la terminal
  cout << "Escribe el radio:";
  float rad=0.;
  cin >> rad;

  // Escribe el área del círculo
  cout << "Área del círculo = "<< pi*rad*rad << endl;

}

// Declarando una función con parámetros
double area_circulo(double radio){
    double area = 0.;
    float pi = 22./7.;
    area = pi * radio * radio;
    return area;
}

// Declarando una función con parámetros opcionales. (El segundo lo podemos pasar o no)
double area_circle(double radio, double pi = 3.141592){
    double area = 0.;
    area = pi * radio * radio;
    return area;
}

// En el main() hay que llamar a la función para que se ejecute.
int main(){
  area();
  //No tenemos acceso a pi desde main
  //cout<<pi;
  //Para declarar la constante pi como global debe estar fuera de la función
  
  //Pedimos un radio por la consola
  double radio = 0., area1 = 0., area2 = 0.;
  cout<<"Introduce un radio: "; cin>>radio;
  
  //Llamamos a la función con parámetro y guardamos lo retornado en una variable.
  area1 = area_circulo(radio);
  cout<<"Área del círculo = "<<area1<<endl;
  
  //Llamamos a la función con parámetro opcional 
  area2 = area_circle(radio);
  cout<<"Área del círculo = "<<area2<<endl;
  
  return 0;
}