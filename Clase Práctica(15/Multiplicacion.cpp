//Multiplicación de números introducidos por terminal
#include <iostream>
#include <iomanip>
using namespace std;

int main(){

    float num1, num2;
    cout<<"Escribe un real: "; cin>>num1;
    
    cout<<"Escribe otro real: "; cin>>num2;

    //setprecision para las variables que se imprimen después de la función
    cout<<setprecision(3)<<num1<< " * " << num2<< " = " << num1*num2<<endl;
    
    return 0;
    
}