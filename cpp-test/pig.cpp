#include <iostream>
using namespace std;
int main(){ 
    //input the number
    int number[3];
    int max=0;
    for(int i=0;i<3;i++){
        cout << "please input the number:" <<endl; 
        cin >> number[i];
    }
    //judge the number and output the window
    for(int j=0;j<3;j++){
        if(number[j]>max){
            max = number[j];
        } 
    }

    cout <<"the max number is:"<<endl;
    cout << max << endl; 
    return 0;
}

