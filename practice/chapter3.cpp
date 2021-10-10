#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;
int main(){
    string s1;
    string s2;
    string s3;
    string sum;
    //cin>>s1>>s2>>s3;
    //cout<<s1<<s2<<s3<<endl;
    //cout<<s1<<" "<<s2<<" "<<s3<<" "<<endl;
    for(int i=0;i<2;i++){
        string s;
        cin>>s;
        sum+=s+" ";
    }
    cout<<sum<<endl;

    return 0;

}

