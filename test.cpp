#include <stdio.h>
#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <exception.h>

using namespace std;

class person{
public:
    person()throw(std::exception):age(10)
    {
        cout<<"the person initial function"<<endl;
        cout<<"hello world"<<endl;

    }
public:
    int age; 
};

int main(){ 
    /*get person_age*/
    person* p1 = new person();
    cout<<"hello world"<<endl; 
    cout<<"this is the test for github"<<endl;
    cout<<"the git for 2021-11-27"<<endl;
    cout<<"the git for 2021-11-28"<<endl;
    //cout<<"person_age:"<<p1->age<<endl;
    return 0;
}



