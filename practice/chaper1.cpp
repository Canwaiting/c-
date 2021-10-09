#include <iostream>
using namespace std;
int main(){
    std::cout<<"+++++++++++++++++++"<<::endl;
    int a=1,b=2;
    int* a1=&a,*b1=&b;
    std::cout<<"a:"<<a<<std::endl;
    std::cout<<"*a:"<<a1<<std::endl;
    std::cout<<"b:"<<b<<std::endl;
    std::cout<<"*b:"<<b1<<std::endl;
    a1=b1;
    std::cout<<"after changed"<<std::endl;
    std::cout<<"the a1=b"<<std::endl;
    std::cout<<*a1<<" "<<b<<std::endl;
    std::cout<<"+++++++++++++++++++"<<::endl;
    int i=42,j;
    std::cout<<i*i<<std::endl;
    std::cout<<i*i<<std::endl;





    return 0;

}

