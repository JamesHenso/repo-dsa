
#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *pNext;
};

struct List
{
    Node *pHead;
};

void cre_list(List *list){
    list->pHead = NULL;
}

Node *cre_node(int data){
    Node *temp = new Node();
    temp->data = data;
    temp->pNext = NULL;

    return temp;
}

void add_node(List *list, int info){
    if(list->pHead == NULL){
        list->pHead = new Node; // Create a new node
        list->pHead->data = info;
        list->pHead->pNext = NULL; 
    } else{
        Node *temp = list->pHead;

        while(temp->pNext != NULL){ // Fix the loop condition
            temp = temp->pNext;
        }

        temp->pNext = new Node; // Create a new node
        temp->pNext->data = info;
        temp->pNext->pNext = NULL;
    }
}

void cre_node_list(List *list, int num){
    for(int i = 0; i < num; i++){
        int data = rand();

        add_node(list, data);
    }
}

void output(List list, int num){
    Node *temp = list.pHead; // Fix the loop condition

    while(temp != NULL){
        cout << temp->data << " -> ";
        temp = temp->pNext;
    }
    cout << "NULL" << endl;
}

void add_node_before(List *list, int data){
    Node *cur = cre_node(data);

    cur->pNext = list->pHead;
    list->pHead = cur;
}

void add_node_pos(List *list, int data, int position){
    Node *cur = cre_node(data);

    if(position == 1){
        cur->pNext = list->pHead->pNext;
        list->pHead->pNext = cur;
    } else {
        int k = 1;
        Node *temp = list->pHead;
        Node *pre_temp = NULL;

        while(temp != NULL && k < position){
            k++;
            pre_temp = temp;
            temp = temp->pNext;
        }

        if( k > position){
            cout << "No position";

            return;
        } else {
            pre_temp->pNext = cur;
            cur->pNext = temp;
        }
    }
}

void delete_node(List *list, int position){
    if(position == 1){
        Node *temp = list->pHead;
        list->pHead = list->pHead->pNext;
        delete temp;
    } else {
        int count = 1;
        Node *temp = list->pHead;
        Node *pre = NULL;

        while(temp != NULL  & count < position){
            count++;
            pre = temp;
            temp = temp->pNext;
        }

        if(count > position){
            return;
        } else{
            pre->pNext = temp->pNext;
            delete temp;
        }
    }
}

void delete_list(List *list){
    Node *cur = list->pHead;
    Node *next = new Node();

    while(cur != NULL){
        next = cur->pNext;
        delete cur;
        cur = next;
    }

    list->pHead = NULL;
}

int main()
{
    List l;

    cre_list(&l);

    cre_node_list(&l, 4);

    add_node_before(&l, 56);

    add_node_pos(&l, 34,2);

    delete_node(&l, 3);

    delete_list(&l);

    output(l, 4);

    return 0;
}
