#include <iostream>
using namespace std;
#include <string>
#include <iomanip>
#include <sstream>

string fname(double xmin, double xmax, double h){
  ostringstream oss; 
  oss << setprecision(1) << xmin;
  string fend = "_xmin"+oss.str(); 

  oss.str(string());
  oss << setprecision(1) << xmax;
  fend = fend+"_xmax"+oss.str();

  oss.str(string());
  oss << setprecision(1) << h;
  fend = fend+"_h"+oss.str()+".txt";

  return fend;
}


string a2fname(double a2, double xmin, double xmax, double h){
  ostringstream oss;
  oss << setprecision(1) << a2;
  string fend = "_a"+oss.str(); 

  oss << setprecision(1) << xmin;
  fend = fend+"_xmin"+oss.str(); 

  oss.str(string());
  oss << setprecision(1) << xmax;
  fend = fend+"_xmax"+oss.str();

  oss.str(string());
  oss << setprecision(1) << h;
  fend = fend+"_h"+oss.str()+".txt";

  return fend;
}

int main(){
  double xmin=0., xmax=0.6, y0=-1.,a2=1.;
  int lenh = 2;
  double h[lenh]={0.1, 0.4};
  
  for (int i=0; i<lenh; ++i){
    string filend = fname(xmin,xmax,h[i]);
    cout << filend << endl;
    
    string a2filend = a2fname(a2,xmin,xmax,h[i]);
    cout << filend << endl;
  }

  return 0;
}