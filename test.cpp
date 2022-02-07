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
    

    //cout<<"the size:"<<strs.size()<<endl;
    cout<<strs[0]<<endl;
    cout<<v.back()<<endl;
    cout<<"strs"<<!strs.size()<<endl;
}

void function_4(){
    vector<vector<int>> intervals = {{1,3},{2,3},{2,3},{2,3},{2,3},{2,3}};
    cout<<intervals[0][0]<<endl;

}



struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


int main(){ 
    unordered_map<int,int> map;
    map[1]=1;
    map[2]=1;
    map[1]=1;
    map[1]=1;
    map[1]=1;
    for(auto& a:map){
        cout<<a.first<<" "<<a.second<<endl;
    }
    return 0;
}

class Solution {
    int ans;
    int depth(TreeNode* root){
        if (root == NULL) return 0;
        int L = depth(root->left);
        int R = depth(root->right);
        ans = max(ans, L + R + 1);
        return max(L, R) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 1;
        depth(root);
        return ans - 1;
    }
};






