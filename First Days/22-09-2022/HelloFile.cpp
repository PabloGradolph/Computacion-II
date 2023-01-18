#include <iostream> // For output/input by terminal.
#include <fstream>  // For output/input by file.
#include <string> // For working with string variables.
using namespace std;

int main(){
  
  // We save the file name in a variable.
  string filename;
  filename = "myfile.txt";

  // We are only going to write in the file.
  ofstream ff(filename);

  if (ff.is_open()){
    // We only write on the file if it is correctly open.
    ff << "Hello file \n" << endl;
    cout << "The file's name is: "<<filename<<endl; 
    cout<<"And it is opened successfully."<<endl;
    // We close the file
    ff.close();
    
  } else cout << "The file can not be open" << endl;

  return 0;
}