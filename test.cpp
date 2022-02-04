#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <string.h>
#include <netinet/in.h> 

using namespace std;


void function_3(){
    int same;
    vector<int> v{ 1, 5, 8, 9, 6, 7, 3, 4, 2, 0 };
    vector<int> merge;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    

    //cout<<"the size:"<<strs.size()<<endl;
    cout<<strs[0]<<endl;
    cout<<v.back()<<endl;
    cout<<"strs"<<!strs.size()<<endl;
}

void function_4(){
    vector<vector<int>> intervals = {{1,3},{2,3},{2,3},{2,3},{2,3},{2,3}};
    cout<<intervals[0][0]<<endl;

}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        /*初始化一条链表*/
        ListNode* mergeTwoLists
        bool empty1 = CheckEmpty(list1);
        bool empty2 = CheckEmpty(list2);
        //边界
        /*某一条为空*/
        if(empty1==false && empty2==true){
        }
        if(empty1==true && empty2==false){
        }
        /*两条都是空的*/
        if(empty1==false && empty2==false){
        }
        /*两条都不是空的*/
        if(empty1 == true && empty2 == true){
        }

        return  mergeTwoLists;

        
        
    }
};

int main(){ 
    function_3();
    return 0;
}



