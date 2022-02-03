#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <string.h>
#include <netinet/in.h> 

using namespace std;

void function(){
    vector<int> ar = {-1,0,1,2,-1,-4};
    //ar.push_back(100);
    int target = 1;

    int temp = 0;
      
    // Declaring iterator to a vector
    vector<int>::iterator ptr;
    vector<int>::iterator ptr1;
    vector<int>::iterator ptr2;
    vector<int>::iterator ptr3;
    vector<int>::iterator save_ptr1;
    vector<int>::iterator save_ptr2;
    vector<int>::iterator save_ptr3;
      
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
                /*compare the target and save the result and the pointer*/
                /*if the result relativer than before,replace it*/
                /*ignore the negative and positive*/
                result = temp - target;


                /*equal the number*/
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

}

int main(){ 
    function();

    return 0;
}



