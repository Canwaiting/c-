#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <string.h>
#include <netinet/in.h> 

using namespace std;

int main(){ 
    vector<int> ar = {-1,0,1,2,-1,-4};
    //ar.push_back(100);

    int temp = 0;
      
    // Declaring iterator to a vector
    vector<int>::iterator ptr;
    vector<int>::iterator ptr1;
    vector<int>::iterator ptr2;
    vector<int>::iterator ptr3;
      
    cout << "--------the original vector--------" << endl;
    for (ptr1 = ar.begin(); ptr1 < ar.end(); ptr1++){
        cout << *ptr1 << " ";
    }
    cout<<endl;
    cout << "--------the original vector--------" << endl;
    // Displaying vector elements using begin() and end()
    for (ptr1 = ar.begin(); ptr1 < ar.end()-2; ptr1++)
    { 

        //the pointer 2
        for(ptr2=ptr1+1;ptr2<ar.end()-1;ptr2++){ 
            //the pointer 3
            for(ptr3=ptr2+1;ptr3<ar.end();ptr3++){ 
                temp = *ptr1 + *ptr2 + *ptr3; 
                if(temp==0){ 
                    cout << *ptr1 << " " << *ptr2 << " " << *ptr3 <<" = "<<temp<<endl;
                    vector<int> res = {*ptr1,*ptr2,*ptr3};
                    for (ptr = res.begin(); ptr < res.end(); ptr++){
                        cout << *ptr << " ";
                    } 
                    cout<<endl;
                }
            }
        }
    }


    return 0;
}



