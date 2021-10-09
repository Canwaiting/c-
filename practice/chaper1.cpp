#include <iostream>
using namespace std;
int main(){
    unsigned u = 10,u2=42;
    std::cout<<u2-u<<std::endl; //32
    std::cout<<u-u2<<std::endl; //-32
    int i = 10,i2=42;
    int sum=0;
    std::cout<<i2-i<<std::endl; //32
    std::cout<<i-i2<<std::endl; //-32
    std::cout<<i-u<<std::endl; //0
    std::cout<<u-i<<std::endl; //0
    std::cout<<"who goes \145hello\012"<<::endl;
    std::cout<<"+++++++++++++++++++"<<::endl;
    std::cout<<"2\x4d\n"<<::endl;
    std::cout<<"2\t"<<::endl; 
    for(int i=0;i<10;i++){
        sum +=i;
    } 
    std::cout<<"sum="<<sum<<::endl; 
    return 0;

}

