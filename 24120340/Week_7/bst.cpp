#include <iostream>
#include <queue>
#include <vector>
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
NODE* createNode(int value);
NODE* Search(NODE* pRoot, int x);
NODE *insertNode(NODE *&pRoot, int x);
void Insert(NODE*& pRoot, int x);
NODE* findMinNode(NODE* pRoot);
NODE* deletion(NODE* pRoot, int x);
void Remove(NODE*& pRoot, int x);
NODE* createTree(int a[], int n);
void removeTree(NODE*& pRoot);
int Height(NODE* pRoot);
int countLess(NODE* pRoot, int x);
int countGreater(NODE* pRoot, int x);
void BST(NODE* pRoot, bool& check, int& value);
bool isBST(NODE* pRoot);
bool fullBST(NODE* pRoot);
bool isFullBST(NODE* pRoot);
void deleteTree(NODE* pRoot);

NODE* createNode(int value) {
    return new NODE(value);
}

NODE *Search(NODE *pRoot, int x){
    if(!pRoot) return nullptr;
    if(pRoot->key == x) return pRoot;

    if(x > pRoot->key) return Search(pRoot->p_right, x);
    else return Search(pRoot->p_left, x);
}

NODE *insertNode(NODE *&pRoot, int x){
    if(!pRoot) return createNode(x);
    if(x > pRoot->key) pRoot->p_right = insertNode(pRoot->p_right, x);
    else pRoot->p_left = insertNode(pRoot->p_left, x);
    return pRoot;
}

void Insert(NODE* &pRoot, int x){
    pRoot = insertNode(pRoot, x);
}

NODE *findMinNode(NODE *pRoot){
    pRoot = pRoot->p_right;
    while(pRoot != nullptr && pRoot->p_left != nullptr) pRoot = pRoot->p_left;
    return pRoot;
}

NODE *deletion(NODE *pRoot, int x){
    if(!pRoot) return pRoot;
    if(x > pRoot->key) pRoot->p_right = deletion(pRoot->p_right, x);
    else if(x < pRoot->key) pRoot->p_left = deletion(pRoot->p_left, x);
    else{
        if(pRoot->p_left == nullptr){
            NODE * temp = pRoot->p_right;
            delete pRoot;
            return temp;
        }
        if(pRoot->p_right == nullptr){
            NODE *temp = pRoot->p_left;
            delete pRoot;
            return temp;
        }

        NODE *curr = findMinNode(pRoot);
        pRoot->key = curr->key;
        pRoot->p_right = deletion(pRoot->p_right, curr->key); 
    }

    return pRoot;
    
}

void Remove(NODE *&pRoot, int x){
    pRoot = deletion(pRoot, x);
}

NODE* createTree(int a[], int n) {
    NODE* pRoot = nullptr;
    for (int i = 0; i < n; ++i) {
        Insert(pRoot, a[i]);
    }
    return pRoot;
}

void removeTree(NODE *&pRoot){
    if (!pRoot) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

int Height(NODE *pRoot){
    if(!pRoot) return -1;
    
    int left = Height(pRoot->p_left);
    int right = Height(pRoot->p_right);

    return max(left, right) + 1;
}

int countLess(NODE *pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key < x) return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    else return countLess(pRoot->p_left, x);
}

int countGreater(NODE *pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key > x) return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    else return countGreater(pRoot->p_right, x);
}

void BST(NODE *pRoot, bool &check, int &value){
    if(!pRoot || !check) return;
    BST(pRoot->p_left, check, value);
    if(pRoot->key <= value){
        check = false;
        return;
    }
    value = pRoot->key;
    BST(pRoot->p_right, check, value);
}

bool isBST(NODE *pRoot){
    bool check = true;
    int value = INT_MIN;
    BST(pRoot, check, value);
    return check;
}

bool fullBST(NODE * pRoot){
    if(!pRoot) return true;
    if(!pRoot->p_left && !pRoot->p_right) return true;
    if(pRoot->p_left && pRoot->p_right) return fullBST(pRoot->p_left) && fullBST(pRoot->p_right);
    return false;
}

bool isFullBST(NODE *pRoot){
    return isBST(pRoot) && fullBST(pRoot);
}

// Helper function to avoid memory leaks
void deleteTree(NODE* pRoot) {
    if (!pRoot) return;
    deleteTree(pRoot->p_left);
    deleteTree(pRoot->p_right);
    delete pRoot;
}
