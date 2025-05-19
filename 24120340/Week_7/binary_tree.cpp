#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
using namespace std;

struct NODE{
    int key;
    NODE *p_left;
    NODE *p_right;
    NODE() : key(0), p_left(nullptr), p_right(nullptr) {}
    NODE(int x) : key(x), p_left(nullptr), p_right(nullptr) {}
    NODE(int x, NODE *left, NODE *right) : key(x), p_left(left), p_right(right) {}
};

// --- Define function prototypes ---
NODE* createNode(int data);
NODE* createTree(const vector<int>& pRoot, int null_val);
void preorder(NODE *pRoot, vector<int> &traversal);
vector<int> NLR(NODE *pRoot);
void inorder(NODE *pRoot, vector<int> &traversal);
vector<int> LNR(NODE *pRoot);
void postorder(NODE *pRoot, vector<int> &traversal);
vector<int> LRN(NODE *pRoot);
vector<vector<int>> LevelOrder(NODE *pRoot);
int countNode(NODE *pRoot);
int sumNode(NODE *pRoot);
int height(NODE *pRoot, int value, int &h, bool &found);
int heightNode(NODE* pRoot, int value);
int Level(NODE *pRoot, NODE *p);
int countLeaf(NODE *pRoot);
void deleteTree(NODE* pRoot);

NODE* createNode(int data) {
    return new NODE(data);
}

NODE *createTree(const vector<int>& pRoot, int null_val){
    if (pRoot.empty() || pRoot[0] == null_val) return nullptr;
    NODE *pRootNode = createNode(pRoot[0]);
    std::queue<NODE *> queue;
    queue.push(pRootNode);
    int i = 1;
    while(!queue.empty() && i < pRoot.size()){
        NODE *temp = queue.front();
        queue.pop();
        if(i < pRoot.size() && pRoot[i] != null_val){
            temp->p_left = createNode(pRoot[i]);
            queue.push(temp->p_left);
        }
        i++;
        if(i < pRoot.size() && pRoot[i] != null_val){
            temp->p_right = createNode(pRoot[i]);
            queue.push(temp->p_right);
        }
        i++;
    }
    return pRootNode;
}

void preorder(NODE *pRoot, vector<int> & traversal){
    if(!pRoot) return;
    traversal.push_back(pRoot->key);
    preorder(pRoot->p_left, traversal);
    preorder(pRoot->p_right, traversal);
}

vector<int> NLR(NODE *pRoot){
    vector<int> traversal;
    preorder(pRoot, traversal);
    return traversal;
}

void inorder(NODE *pRoot, vector<int> & traversal){
    if(!pRoot) return;
    inorder(pRoot->p_left, traversal);
    traversal.push_back(pRoot->key);
    inorder(pRoot->p_right, traversal);
}

vector<int> LNR(NODE *pRoot){
    vector<int> traversal;
    inorder(pRoot, traversal);
    return traversal;
}

void postorder(NODE *pRoot, vector<int> & traversal){
    if(!pRoot) return;
    postorder(pRoot->p_left, traversal);
    postorder(pRoot->p_right, traversal);
    traversal.push_back(pRoot->key);
}

vector<int> LRN(NODE *pRoot){
    vector<int> traversal;
    postorder(pRoot, traversal);
    return traversal;
}

vector<vector<int>> LevelOrder(NODE *pRoot){
    vector<vector<int>> res;
    if(!pRoot) return res;
    std::queue<NODE *> queue;
    int index = 0;
    queue.push(pRoot); queue.push(nullptr);
    res.push_back({});
    while(!queue.empty()){
        NODE *temp = queue.front(); queue.pop();
        if(temp == nullptr){
            if(!queue.empty()){
                queue.push(nullptr);
                res.push_back({});
                index++;
            }
        }
        else{
            res[index].push_back(temp->key);
            if(temp->p_left) queue.push(temp->p_left);
            if(temp->p_right) queue.push(temp->p_right);
        }
    }
    return res;   
}

int countNode(NODE *pRoot){
    if(!pRoot) return 0;
    return countNode(pRoot->p_left) + 1 + countNode(pRoot->p_right);
}

int sumNode(NODE *pRoot){
    if(!pRoot) return 0;
    return sumNode(pRoot->p_left) + pRoot->key + sumNode(pRoot->p_right);
}

int height(NODE *pRoot, int value, int &h, bool &found){
    if(!pRoot) return -1;

    int left = height(pRoot->p_left, value, h, found);
    int right = height(pRoot->p_right, value, h, found);

    int res = max(left, right) + 1;

    if(pRoot->key == value) {
        h = res;
        found = true;
    }
    return res;
}

int heightNode(NODE* pRoot, int value) {
    int h = -1;
    bool found = false;
    height(pRoot, value, h, found);
    return found ? h : -1;
}


int Level(NODE *pRoot, NODE *p) {
    if (!pRoot || !p) return -1;
    std::queue<std::pair<NODE*, int>> q;
    q.push({pRoot, 1});
    while (!q.empty()) {
        auto [node, lvl] = q.front(); q.pop();
        if (node == p) return lvl;
        if (node->p_left) q.push({node->p_left, lvl + 1});
        if (node->p_right) q.push({node->p_right, lvl + 1});
    }
    return -1;
}

int countLeaf(NODE *pRoot){
    if(!pRoot) return 0;
    if(!pRoot->p_left && !pRoot->p_right) return 1;

    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}

// Helper function to avoid memory leaks
void deleteTree(NODE* pRoot) {
    if (!pRoot) return;
    deleteTree(pRoot->p_left);
    deleteTree(pRoot->p_right);
    delete pRoot;
}
