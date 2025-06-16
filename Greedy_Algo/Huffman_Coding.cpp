#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct TreeNode{
    char ch;
    int val;
    TreeNode *left, *right;
    TreeNode(char c, int v) : ch(c), val(v), left(nullptr), right(nullptr) {}
    TreeNode(int v, TreeNode* l, TreeNode* r) : ch('\0'), val(v), left(l), right(r) {}
};

struct Compare {
    bool operator()(TreeNode* a, TreeNode* b) {
        return a->val > b->val;
    }
};

TreeNode* huffmanCoding(string list, vector<int> freq){
    priority_queue<TreeNode*, vector<TreeNode*>, Compare> priority_node;
    for(int i = 0; i < list.size(); ++i){
        priority_node.push(new TreeNode(list[i], freq[i]));
    }

    while(priority_node.size() > 1){
        TreeNode* left = priority_node.top(); priority_node.pop();
        TreeNode* right = priority_node.top(); priority_node.pop();
        priority_node.push(new TreeNode(left->val + right->val, left, right));
    }
    return priority_node.top();
}

void preOrder(TreeNode *root, vector<pair<char, string>> &ans, string curr){
    if(!root) return;
    if(!root->left && !root->right){
        ans.emplace_back(root->ch, curr);
        return;
    }
    preOrder(root->left, ans, curr + '0');
    preOrder(root->right, ans, curr + '1');
}

int main(){
    string list = "abcdef";
    vector<int> freq = {12, 2, 7, 13, 14, 85};
    vector<pair<char, string>> ans;
    TreeNode *root = huffmanCoding(list, freq);
    preOrder(root, ans, "");

    for (auto &[ch, code] : ans) {
        cout << ch << ": " << code << endl;
    }

    return 0;
}
