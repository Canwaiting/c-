#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <vector>
#include <string.h>
#include <netinet/in.h> 

using namespace std;


void function_3(){
    int same;
    vector<int> v{ 1, 5, 8, 9, 6, 7, 3, 4, 2, 0 };
    vector<int> merge;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    

    cout<<strs[0]<<endl;
    cout<<v.back()<<endl;
    cout<<"strs"<<!strs.size()<<endl;
}

void function_4(){
    vector<vector<int>> intervals = {{1,3},{2,3},{2,3},{2,3},{2,3},{2,3}};
    cout<<intervals[0][0]<<endl;

}

void function_5(){
    vector<vector<int>>  people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
	sort(people.begin(), people.end(), [](const vector<int>& u, const vector<int>& v) {
		//return u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]);
		return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]);
	});

	//for(const vector<int>& person:people){
	for(auto& person:people){
		cout<<person[0]<<","<<person[1]<<endl;
	}

}


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};



int main(){ 
	function_5();
    return 0;
}



