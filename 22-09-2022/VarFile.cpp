#include <iostream> // For output/input by terminal.
#include <fstream>  // For output/input by file.
#include <string>   // For working with string variables.
using namespace std;

int main(){
  // We ask for 2 integers.
  cout << "Escribe 2 enteros separados por un espacio: ";
  int num1=0, num2=0;
  cin >> num1 >> num2;

  // We define the array.
  double vector[5] = {1, 2, 0, -1.4, -3};
  
  // We define the file and we open it.
  string infile = "integer.txt";
  ofstream ff(infile);
  if (ff.is_open()){
    /* Usually a header is added
     indicating what each column of the file contains */
    ff << "# Integers" << endl;

    // We write the two integers in the file.
    ff << num1 << endl;
    ff << num2 << endl;
    
    // We write the arra in the file.
    ff << "# Array" << endl;
    for (int i=0; i<5; ++i){
        ff << vector[i] << endl;
    }

    // We close the file
    cout << "Generated file: " << infile << endl;
    ff.close();
    
  } else cout << "The file can not be open: " << infile << endl;

  return 0;
}