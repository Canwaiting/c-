#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

void printFunc(const vector<int>& v){ 
    cout<<"the original"<<endl;
    for(auto it = v.begin();it!=v.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}


void doubleFunc(vector<int>& v){

    for(auto it = v.begin();it!=v.end();++it){
        *it *=2;
    }
}
#endif