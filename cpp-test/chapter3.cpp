#include <iostream>
#include <string>
#include <vector>
#include "function.h"
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::begin;
using std::end;

int main(){ 
	int a[2] ={1,2};
	int arr[3][4] = 
    { 
        { 0, 1, 2, 3 },
        { 4, 5, 6, 7 },
        { 8, 9, 10, 11 }
    };
	for(const int(&row)[4]:arr)
		for(int col:row) cout<<col<<" ";
	cout<<endl; 
	cout<<"========="<<endl;
	for(size_t i = 0;i!=3;++i)
		for(size_t j = 0;j!=4;++j) cout<<arr[i][j]<<" ";
	cout<<endl; 
	cout<<"========="<<endl;
	for(int (*row)[4] = arr;row!=arr+3;++row)
		for(int *col = *row;col!=*row+4;++col) cout<<*col<<" ";
	cout<<endl;

	cout<<a[1]<<endl;

    return 0;

}

