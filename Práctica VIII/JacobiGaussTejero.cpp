//COMPUTACIÓN I - PRÁCTICA VIII - EJERCICIO I
//FECHA: 06/10/2022
//RESOLUCIÓN DE SISTEMAS - MÉTODOS DE JACOBI Y GAUSS-SEIDEL
#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>

using namespace std;

const int n=4;

double norma(double x[n], int n);
void jacobi(double A[n][n], double b[n], double x[n], int n, double tolerancia);
void gaussseidel(double A[n][n], double b[n], double x[n], int n, double tolerancia);
bool convergencia(double A[n][n]);

int main(){
	
	cout<<"COMPUTACION II: PRACTICA VI"<<endl;
	cout<<"RESOLUCION DE SISTEMAS DE ECUACIONES MEDIANTE DOS METODOS"<<endl;
	cout<<"METODO DE JACOBI Y METODO DE GAUSS-SEIDEL"<<endl<<endl;
	system("PAUSE");
	cout<<endl;
	
	char ficheromat[30];
	double A[n][n];
	
	cout<<"Introduzca nombre del archivo de entrada: ";
	cin>>ficheromat;
	ifstream fentry(ficheromat, ios::in); // Creamos un flujo de entrada para el arichvo que contiene la matriz
	
	cout<<endl;
	cout << "MATRIZ A: " << endl;
	for (int i=0; i<n; i++){
  		for (int j=0; j<n; j++){  
			fentry >> A[i][j];
			cout << A[i][j] << "  ";
		}
	cout<<endl;
	}
	cout<<endl;		
	
	fentry.close(); // Cerramos el flujo de entrada
	
		double b[n]={3, -4, 5, -2};
  		double x[n];
  		
  		double tolerancia;
  		cout<<"Introduzca la tolerancia deseada: ";
  		cin>>tolerancia;
  		cout<<endl;
  		
		jacobi(A, b, x, n, tolerancia);
		system("PAUSE");
		gaussseidel(A, b, x, n, tolerancia);	
	
  	return 0;
}

bool convergencia(double A[n][n]){
	
	int i, j;
	float sum = 0;
	
	for (i=0; i<n; i++){
		sum = 0;
		for (j=0; j<n; j++){
			if (i!=j){
				sum = sum + fabs(A[i][j]);
		}}
		cout<<"Sumatorio fila "<<i+1<<": "<<sum<<endl;
		if (fabs(A[i][i])<sum){
			cout<<endl<<sum<<" > "<<fabs(A[i][i])<<endl<<endl;	
			return false;	
	}}
	
	cout<<endl<<"DIAGONAL DOMINANTE"<<endl<<endl;
	return true;
}

double norma (double x[n], int n){

	double suma=0.0;
    
	for (int i=0; i<=n-1; i++){
           suma=suma+x[i]*x[i];
       }
       
	return (sqrt(suma));
}

void jacobi(double a[n][n], double b[n], double newx[n], int n, double tolerancia){
	
	int contador=0;
	double oldx[n]; // La aproximación inicial se almacena en el vector oldx --> oldx[i]= b[i]/a[i][i]
	
	for (int i=0; i<=n-1; i++){  
		oldx[i]=b[i]/a[i][i];
		newx[i]=oldx[i];
		cout<<newx[i]<<endl;
	}
	cout<<endl;

	do {
		
		for (int i=0; i<n; i++){
			oldx[i]=newx[i]; 
		}
		
		for (int i=0; i<n; i++){	
			newx[i]=b[i]/a[i][i];
			for (int j=0; j<n; j++){
				if (j != i){
					newx[i]=newx[i] - (a[i][j]/ a[i][i])*oldx[j]; 
				}        
			}
			cout<<newx[i]<<endl;
		}	 
 	contador= contador + 1;
	} while (fabs (norma(newx,n) - norma(oldx,n)) > tolerancia);
	
cout <<"METODO DE JACOBI"<<endl;
cout<<"Numero de iteraciones: "<<contador<<endl;
  for(int i=0;i<n;i++){
    cout<<"x["<<i<<"] = "<<newx[i]<<endl;
	}
    cout<<endl;
}

void gaussseidel(double a[n][n], double b[n], double newx[n], int n, double tolerancia){
	
	int contador=0;
	double oldx[n]; // La aproximación inicial se almacena en el vector oldx --> oldx[i]= b[i]/a[i][i]
	
	for (int i=0; i<n; i++) {  
		oldx[i]=b[i]/a[i][i];
		newx[i]=oldx[i];
	}
	
	do {
		
		for (int i=0; i<=n-1; i++){ 
			oldx[i]=newx[i]; 
		} 
		
		for (int i=0; i<=n-1; i++){	
			newx[i]=b[i]/a[i][i];
			for (int j=0; j<=n-1; j++){
				if (j != i){ 
					newx[i]=newx[i] - (a[i][j]/ a[i][i])*newx[j]; 
				}        
			} 
		}
		
 	contador= contador + 1;
	} while ((fabs (norma(newx,n) - norma(oldx,n))) > tolerancia);
	
	cout <<"METODO DE GAUSS-SEIDEL:"<<endl;
	cout<<"Numero de iteraciones: "<<contador<<endl;
  	for(int i=0;i<n;i++){
    	cout<<"x["<<i<<"] = "<<newx[i]<<endl;
	}
    cout<<endl;
}