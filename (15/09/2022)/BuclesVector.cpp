#include <iostream>
using namespace std;

int main(){

    int nlen = 5, vector1[5] = {1,2,3,4,5};

    cout<<"Usando bulce for:"<<endl;
    for (int i = 0; i<nlen; ++i){
        cout<< "vector[" << i << "]="<<vector1[i]<<endl;
    }

    int i = 0;
    
    cout<<"Usando bulce while:"<<endl;
    while (i<nlen){
        cout<< "vector[" << i << "]="<<vector1[i]<<endl;
        i++;
    }

    int j = 0;

    cout<<"Usando do con while:"<<endl;
    do{
        cout<< "vector[" << j << "]="<<vector1[j]<<endl;
        ++j;
    }while(j<nlen);

    cout<<endl;
    cout<<"Comparando los números del vector con el valor 2:"<<endl;

    int num = 2;
    for (i=0; i<nlen; ++i){
        if (vector1[i]>num){
            cout<<vector1[i]<<" es mayor que "<<num<<endl;
        }else if (vector1[i]==num){
            cout<<vector1[i]<<" es igual que "<<num<<endl;
        }else {
            cout<<vector1[i]<<" es menor que "<<num<<endl;
        }
    }
    return 0;
}