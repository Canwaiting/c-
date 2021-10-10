#include <iostream>
#include <string>
#include <vector>
#include "function.h"
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(){ 
    int a[10];
    int b[10];
    vector<int> v1(10);
    for(int i=0;i<10;i++){
        a[i] = i;
        cout<<a[i]<<" ";
    }
    cout<<endl;

    cout<<"=========="<<endl;
    for(int i=0;i<10;i++){
        b[i] = a[i];
        cout<<b[i]<<" ";
    }
    cout<<endl;

    cout<<"=====vector====="<<endl;
    for(int i=0;i<10;i++){
        v1[i] = a[i];
    } 

    vector<int> v2(v1);
    for(auto i:v2){
        cout<<i<<" ";
    }
    cout<<endl;




    return 0;

}

