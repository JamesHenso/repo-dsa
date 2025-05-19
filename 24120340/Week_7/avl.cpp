#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct NODE{
    int key;
    int height;
    NODE *p_left;
    NODE *p_right;
    NODE() : key(0), height(1), p_left(nullptr), p_right(nullptr) {}
    NODE(int x) : key(x), height(1), p_left(nullptr), p_right(nullptr) {}
    NODE(int x, NODE *left, NODE *right) : key(x), height(1), p_left(left), p_right(right) {}
};

NODE *createNode(int data);
int heightNode(NODE *pRoot);
NODE *leftRotate(NODE *pRoot);
NODE *rightRotate(NODE *pRoot);
int balanced(NODE *pRoot);
NODE *insert(NODE *pRoot, int x);
void Insert(NODE *&pRoot, int x);
NODE *findNode(NODE *pRoot);
NODE *remove(NODE *pRoot, int x);
void Remove(NODE *&pRoot, int x);
void BST(NODE *pRoot, bool &check, int &value);
bool isBST(NODE *pRoot);
bool isAVLUtil(NODE* pRoot, int& height);
bool isAVL(NODE *pRoot);
void deleteTree(NODE* pRoot);
NODE* findMinNode(NODE* pRoot);

NODE *createNode(int data){
    return new NODE(data);
}

int heightNode(NODE *pRoot){
    if(!pRoot) return 0;
    return pRoot->height;
}

NODE *leftRotate(NODE *pRoot){
    if (!pRoot || !pRoot->p_right) return pRoot;
    NODE *curr = pRoot->p_right;
    NODE *temp = curr->p_left;

    pRoot->p_right = temp;
    curr->p_left = pRoot;

    pRoot->height = 1 + max(heightNode(pRoot->p_left), heightNode(pRoot->p_right));
    curr->height = 1 + max(heightNode(curr->p_left), heightNode(curr->p_right));

    return curr;
}

NODE *rightRotate(NODE *pRoot){
    if (!pRoot || !pRoot->p_left) return pRoot;
    NODE *curr = pRoot->p_left;
    NODE *temp = curr->p_right;

    pRoot->p_left = temp;
    curr->p_right = pRoot;

    pRoot->height = 1 + max(heightNode(pRoot->p_left), heightNode(pRoot->p_right));
    curr->height = 1 + max(heightNode(curr->p_left), heightNode(curr->p_right));

    return curr;
}

int balanced(NODE *pRoot){
    if(!pRoot) return 0;
    return heightNode(pRoot->p_left) - heightNode(pRoot->p_right);
}

NODE * insert(NODE *pRoot, int x){
    if(!pRoot) return createNode(x);
    if(x > pRoot->key) pRoot->p_right = insert(pRoot->p_right, x);
    else if(x < pRoot->key) pRoot->p_left = insert(pRoot->p_left, x);
    else return pRoot;

    pRoot->height = 1 + max(heightNode(pRoot->p_left), heightNode(pRoot->p_right));
    int balance = balanced(pRoot);

    if(balance < -1 && x > pRoot->p_right->key) return leftRotate(pRoot);
    if(balance > 1 && x < pRoot->p_left->key) return rightRotate(pRoot);

    if(balance > 1 && x > pRoot->p_left->key){
        pRoot->p_left = leftRotate(pRoot->p_left);
        return rightRotate(pRoot);
    }
    if(balance < -1 && x < pRoot->p_right->key){
        pRoot->p_right = rightRotate(pRoot->p_right);
        return leftRotate(pRoot);
    }

    return pRoot;
}

void Insert(NODE *&pRoot, int x){
    pRoot = insert(pRoot, x);
}

NODE *findNode(NODE *pRoot){
    pRoot = pRoot->p_right;
    while(pRoot != nullptr && pRoot->p_left != nullptr) pRoot = pRoot->p_left;
    return pRoot;
}

NODE* findMinNode(NODE* pRoot) {
    while (pRoot && pRoot->p_left) pRoot = pRoot->p_left;
    return pRoot;
}

NODE* remove(NODE* pRoot, int x) {
    if (!pRoot) return nullptr;

    if (x < pRoot->key) {
        pRoot->p_left = remove(pRoot->p_left, x);
    }
    else if (x > pRoot->key) {
        pRoot->p_right = remove(pRoot->p_right, x);
    }
    else {
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            delete pRoot;
            return temp;
        }

        NODE* successor = findMinNode(pRoot->p_right);
        pRoot->key = successor->key;
        pRoot->p_right = remove(pRoot->p_right, successor->key);
    }

    pRoot->height = 1 + max(heightNode(pRoot->p_left), heightNode(pRoot->p_right));

    int balance = balanced(pRoot);

    // Left-Left
    if (balance > 1 && balanced(pRoot->p_left) >= 0)
        return rightRotate(pRoot);

    // Left-Right
    if (balance > 1 && balanced(pRoot->p_left) < 0) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        return rightRotate(pRoot);
    }

    // Right-Right
    if (balance < -1 && balanced(pRoot->p_right) <= 0)
        return leftRotate(pRoot);

    // Right-Left
    if (balance < -1 && balanced(pRoot->p_right) > 0) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        return leftRotate(pRoot);
    }

    return pRoot;
}

void Remove(NODE *&pRoot, int x){
    pRoot = remove(pRoot, x);
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
bool isAVLUtil(NODE* pRoot, int& height) {
    if (!pRoot) {
        height = 0;
        return true;
    }
    int lh = 0, rh = 0;
    bool left = isAVLUtil(pRoot->p_left, lh);
    bool right = isAVLUtil(pRoot->p_right, rh);
    height = 1 + max(lh, rh);
    if (abs(lh - rh) > 1) return false;
    return left && right;
}

bool isAVL(NODE *pRoot){
    if (!isBST(pRoot)) return false;
    int height = 0;
    return isAVLUtil(pRoot, height);
}

// Helper function to avoid memory leaks
void deleteTree(NODE* pRoot) {
    if (!pRoot) return;
    deleteTree(pRoot->p_left);
    deleteTree(pRoot->p_right);
    delete pRoot;
}
