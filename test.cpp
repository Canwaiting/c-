#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

class person{
public:
    person():age(10){}
public:
    int age; 
};

int main(){ 
    /*get person_age*/
    person* p1 = new person();
    cout<<"hello world"<<endl; 
    cout<<"person_age:"<<p1->age<<endl;
    return 0;
}



