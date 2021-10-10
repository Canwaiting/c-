#include <iostream>
#include <string>
#include <vector>
#include "function.h"
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::begin;
using std::end;

int main(){ 
    int arr1[]={1,2,3};
    int arr2[]={1,2,3};
    int arr3[]={1,3,3};
    if(compare(begin(arr1),begin(arr2),end(arr1),end(arr2))){
        cout<<"same"<<endl;
    }
    else{
        cout<<"not same"<<endl;
    }
    cout<<"=========="<<endl;
    if(compare(begin(arr1),begin(arr3),end(arr1),end(arr3))){
        cout<<"same"<<endl;
    }
    else{
        cout<<"not same"<<endl;
    }



    return 0;

}

