// Código proporcionado por la profesora para ayudar con la resolución de la práctica.
// Computación II: Práctica XVIII

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

double pi = acos(-1.);
double g = 9.8;
double w = 7.29*1e-5;
double l = 20.;
double psi = pi/4.;
double P = 2*pi*sqrt(l/g);

matrix<double> func(double t, matrix<double> y0){
  int n = y0.rowno();
  matrix<double> ff(n,1); ff.null();

  double z1 = y0(0,0);
  double z2 = y0(1,0);
  double z3 = y0(2,0);
  double z4 = y0(3,0);

  double k = sqrt(g/l);

  ff(0,0) = z3;
  ff(1,0) = z4;
  ff(2,0) = 2.*w*sin(psi)*z4 - k*k*z1 ;
  ff(3,0) = -2.*w*sin(psi)*z3 - k*k*z2 ;
  
  return ff;
}

string fname(double a, double b){
  ostringstream oss; 
  oss << setprecision(3) << a;
  string fend = "_t"+oss.str(); 

  oss.str(string());
  oss << setprecision(3) << b;
  fend = fend+"_"+oss.str()+".txt";
  return fend;
}


matrix<double> rk4(const double tau,
		   const double tmin, const double tmax,
		   const matrix<double> z0,
		   matrix<double>(*f)(double, matrix<double>),
		   string filend, bool verbose=false){
  // NÃºmero de pasos
  double nstep=(tmax-tmin)/tau;

  // Nombre del fichero de salida
  string outf = "rk4"+filend;
  ofstream ff(outf);
  
  // Inicializa los vectores
  int n = z0.rowno();
  matrix<double> lastz(n,1); lastz = z0;
  double lastt=0.;
  
  // Declara los parÃ¡metros Runge-Kutta
  matrix<double> k1(n,1); k1.null();
  matrix<double> k2(n,1); k2.null();
  matrix<double> k3(n,1); k3.null(); 
  matrix<double> k4(n,1); k4.null(); 
  
  // Encuentra la soluciÃ³n
  if (ff.is_open()){
    ff << fixed << showpoint; ff << setprecision(15);
    ff << tmin << " " << z0(0,0) << " "<< z0(1,0) <<
      " " << z0(2,0) << " "<< z0(3,0) << 
      " " << tmin/P << " " << asin(z0(1,0)/z0(0,0)) << endl;
    
    double t=0.;
    matrix<double> z(n,1); z.null();
    for (int i=1; i<nstep+1; ++i){
      t = tmin + i*tau;
      lastt = t-tau;
      
      k1 = f(lastt,lastz);
      k2 = f(lastt+tau/2.0,lastz+k1*tau/2.0);
      k3 = f(lastt+tau/2.0,lastz+k2*tau/2.0);
      k4 = f(lastt+tau,lastz+k3*tau);
      
      z = lastz + (k1 + 2.0*k2 + 2.0*k3 + k4)*tau/6.0;
      
      if (verbose){
	cout << fixed << showpoint; cout << setprecision(15);
	cout << lastt << " =(t-tau), lastz: " << ~lastz << endl;}

      ff << t << " " << z(0,0) << " "<< z(1,0) <<
	" " << z(2,0) << " "<< z(3,0) <<
	" " << t/P << " " << asin(z(1,0)/z(0,0)) << endl;

      if (abs(t/P - 3.) < 1e-3){
	cout << "t=" << t << ", t/P-3=" << abs(t/P - 3.) << endl;
	cout << "x=" << z(0,0) << ", y=" << z(1,0) << endl;
	double angle = abs(atan(z(1,0)/z(0,0))*180./pi/3.);
	double horas = P*360./angle/3600.;
	cout << "Ãngulo despuÃ©s de 3 periodos (deg)    = " << angle*3. << endl;
	cout << "Ãngulo promedio de cada periodo (deg) = " << angle << endl;
	cout << "Horas en dar una rotaciÃ³n completa    = " << horas << endl;
      }
      lastz = z; 
    }
    
    ff.close();
    //cout << "Fichero de salida: " << outf << endl;
  }else cout<<"No se ha podido abrir "<<outf<<endl;

  return lastz;
}


int main(){ 
  double eps = 1e-6;
  int neq = 4;
  
  // Valores iniciales
  double tmin=0., tmax=300.;
  string filend = fname(tmin,tmax);

  matrix<double> z0(neq,1); z0.null();
  z0(0,0) = 5.;
  z0(1,0) = 0.;
  z0(2,0) = 0.;
  z0(3,0) = 0.;
  
  // Primer intento con un h inicial
  double  h = 1.;
  matrix<double> lastz0(neq,1); lastz0.null();
  lastz0 = rk4(h,tmin,tmax,z0,func,filend);

  matrix<double> zz(neq,1); zz.null();
  double diff;
  do{
    h = h*0.2;
    zz = rk4(h,tmin,tmax,z0,func,filend);
    
    diff = (abs(lastz0(0,0)-zz(0,0))+
	    abs(lastz0(1,0)-zz(1,0))+
	    abs(lastz0(2,0)-zz(2,0))+
	    abs(lastz0(3,0)-zz(3,0)))/4.;
    lastz0 = zz;
  }while(diff>1e-6);
  
  cout << "dt=" << h << " s" << endl;
  
  return 0;
}