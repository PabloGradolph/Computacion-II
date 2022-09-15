#include <iostream>
#include <cmath>
using namespace std;

//Definiendo pi correctamente con la librería cmath
const double pi1 = atan(1)*4.;
const double pi2 = M_PI;



double doble(double num){
  return num*2.;
}

double mitad(double num){
  return num/2.;
}

//Función como parámetro de otra función
void resultado(const double num, double (*f)(double)){
  cout << "Resultado = " << (f(num)) << endl;
}

int main(){
  //Imprimiendo los pi
  cout<<"Primera definición de pi: "<<pi1<<endl;
  cout<<"Segunda definición de pi: "<<pi2<<endl;
  // Pide un número
  cout << "Real:";
  double num = 0.;
  cin >> num;

  // Pide la operación
  cout << "Doble (1) o Mitad (0):";
  int op;
  cin >> op;

  // Realiza el cálculo pedido
  if (op == 0){resultado(num, &mitad);}
  else if (op == 1){resultado(num, &doble);}
  else{
    cout << "Introduce 1 o 0";
    return 1;
  }
  return 0;
}