#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <vector>
#include <string.h>
#include <netinet/in.h> 
#include <algorithm>
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

void function_6(int num){
	if(num==11){
		return;
	}
	cout<<num<<" "<<endl;
	function_6(num+1);
}


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


bool comp(int a,int b){
	return (a<b);
}

bool testsort(){
    vector<int> vec = {1,2,3,23,2,432,52,5,1};
    sort(vec.begin(),vec.end());
    for(auto x : vec){
        cout<<x<<" ";
    }
    cout<<endl;
}
// alignas 生效的情况

struct Info {
  uint8_t a;
  uint16_t b;
  uint8_t c;
};


struct alignas(2) Info2 {
  uint8_t a;
  uint16_t b;
};


void http_test(){
    char text[] = "GET /xxx.jpg HTTP/1.1";
    char* m_url = strpbrk(text,"\t");
    cout<<"m_url"<<m_url<<endl;
    cout<<"m_url"<<*m_url<<endl;
    //cout<<"*m_url"<<*m_url<<endl;
} 

int test_while(){
    cout<<"function running"<<endl;
    return 1;
}

void myswap(vector<int> &nums,int i,int j) 
{
    //nums[i] = nums[i] ^ nums[j];
    //nums[j] = nums[i] ^ nums[j];
    //nums[i] = nums[i] ^ nums[j];
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
    cout<<i<<"和"<<j<<"调换: ";
    for(int num : nums)
    {
        cout<<num<<" ";
    }
    cout<<endl;
}


void selectSort(vector<int>& nums)
{
    int count = 0;
    int n = nums.size();
    //if(n<2 || nums == nullptr){
    //    return ;
    //}

    for(int i = 0;i<n-1;i++){
        int minIndex = i;
        for(int j = i+1;j<n;j++){
            minIndex = nums[j] < nums[minIndex] ? j : minIndex;
            count++;
        }
        myswap(nums,i,minIndex); 
    }
    cout<<"比较了:"<<count<<"次"<<endl;


}

void bubbleSort(vector<int>& nums)
{
    int n = nums.size();
    int count = 0;

    for(int i = 0;i<n-1;i++){
        for(int j = i+1;j<n;j++){
            if(nums[i]>nums[j]){
                myswap(nums,i,j);
            }
            count++;
        }
    }
    cout<<"比较了:"<<count<<"次"<<endl;
}

int main(){ 
    vector<int> nums = {1,4,2,5,3};
    cout<<"before: ";
    for(int num : nums)
    {
        cout<<num<<" ";
    }
    cout<<endl;
    cout<<endl;

    //sort(nums.begin(),nums.end());
    //myswap(nums,0,1);
    selectSort(nums);
    //bubbleSort(nums);
    cout<<endl;
    cout<<"after:  ";
    for(int num : nums)
    {
        cout<<num<<" ";
    }
    cout<<endl;
    return 0;
}



