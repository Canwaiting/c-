#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int main(){
    string a = "hello";
    cout<<"the original:"<<a<<endl;
    //bzero(&a,1);
    cout<<"the bzero:"<<a<<endl;
    return 0;
}
