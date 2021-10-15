#include <iostream>
#include <string>
#include <math.h>
using namespace std;


void test(){
    bool b;
    int *ptr = new int;
    cout<<"ptr="<<ptr<<endl;
    int j=1,k=2;
    int i=0;
    cout<<i<<endl;
    cout<<(j<k)<<endl;
    if(i!=j<k){
        cout<<"true"<<endl;
    }
    else{
        cout<<"true"<<endl;
    }

}

int main(){
    test();
    return 0;
}
