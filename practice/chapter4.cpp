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

void test3(){
    string text;
    char ch;
    char prech ='\0';
    unsigned sum=0;
    unsigned tab=0;
    unsigned space=0;
    unsigned nextline=0;
    unsigned hello=0;
    for(int i=0;i<5;i++){
        cin>>std::noskipws>>ch;
        switch(ch){ 
            case 'A': sum++;break;
            case 'E': sum++;break;
            case 'I': sum++;break;
            case 'O': sum++;break;
            case 'U': sum++;break;
            case 'a': sum++;break;
            case 'e': sum++;break;
            case 'i': sum++;break;
            case 'o': sum++;break;
            case 'u': sum++;break;
            case ' ': space++;break;
            case '\t': tab++;break;
            case '\n': nextline++;break; 
            case 'h': if(prech='e') ++hello;break;
        }
    }

    cout<<"=============="<<endl;
    cout<<"the sum is:"<<sum<<endl;
    cout<<"the tab is:"<<tab<<endl;
    cout<<"the space is:"<<space<<endl;
    cout<<"the nextline is:"<<nextline<<endl;
    cout<<"the hello is:"<<hello<<endl;

}

int main(){
    test3();
    return 0;
}
