#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;


void test(){
    vector<int> vec={0,1,2,3,4,5,6,7,8,9}; 
    cout<<"original"<<endl;
    for(auto j :vec){
        cout<<j<<" ";
    } 
    cout<<endl;
    cout<<"changed"<<endl;
    for(auto &i :vec){
        if(i%2!=0){
            i *=2;
        }
        cout<<i<<" "; 
    }
    cout<<endl;
}

void test1(){
    vector<int> vec={0,1,2,3,4,5,6,7,8,9}; 
    for(int i:vec){
        cout<<i<<" "; 
        string result = i<5 ? "less than 5" : i<7 ? "less than 7" : "bigger than 7";
        cout<<result<<endl;
    } 
}


void test2(){
    int *p = new int;
    cout<<"p size:"<<sizeof(p)<<endl;
    cout<<"int size:"<<sizeof(*p)<<endl;
}

int main(){
    test2();
    return 0;
}
