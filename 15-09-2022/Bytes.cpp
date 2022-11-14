#include <iostream>
using namespace std;

int main(){
    // Número de bytes utilizados por cada tipo de dato.
    cout<<"Numero de bytes: "<<endl;
    cout<<"bool: "<<sizeof(bool)<<endl;
    cout<<"unsigned char: "<<sizeof(unsigned char)<<endl;
    cout<<"char: "<<sizeof(char)<<endl;
    cout<<"wchar_t: "<<sizeof(wchar_t)<<endl;
    cout<<"short: "<<sizeof(short)<<endl;
    cout<<"unsigned short: "<<sizeof(unsigned short)<<endl;
    cout<<"long: "<<sizeof(long)<<endl;
    cout<<"unsigned long: "<<sizeof(unsigned long)<<endl;
    cout<<"float: "<<sizeof(float)<<endl;
    cout<<"long long: "<<sizeof(long long)<<endl;
    cout<<"unsigned long long: "<<sizeof(unsigned long long)<<endl;
    cout<<"double: "<<sizeof(double)<<endl;
    cout<<"long double: "<<sizeof(long double)<<endl;

    return 0;
}