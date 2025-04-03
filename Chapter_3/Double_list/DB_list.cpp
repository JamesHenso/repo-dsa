#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *pre;

    Node(int info){
        data = info;
        next = NULL;
        pre = NULL;
    }
};

Node* createDoublyLinkedList(int numNodes) {
    if (numNodes <= 0) return NULL;

    srand(time(0)); // Seed for random number generation

    Node* head = new Node(rand() % 100); // Create the head node with a random value
    Node* current = head;

    for (int i = 1; i < numNodes; ++i) {
        Node* newNode = new Node(rand() % 100); // Create a new node with a random value
        current->next = newNode;
        newNode->pre = current;
        current = newNode;
    }

    return head;
}

Node* createDoublyLinkedListWithFiveNodes() {
    return createDoublyLinkedList(5);
}

void output_list(Node *head){
    if(head == NULL){
        return;
    } else{
        cout << "NULL";
        Node *temp = head;

        while(temp != NULL){
            cout << " <-> ";
            cout << temp->data;

            temp = temp->next;
        }

        cout << " <-> NULL";
    }
}

typedef int * (*forward_travel)(Node *head, char *);

int *ascending(Node *head){
    int count = 0;
    Node *temp = head;

    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    int *num = new int[count];
    temp = head;

    for(int i = 0; i < count; i++){
        num[i] = temp->data;
        temp = temp->next;
    }

    return num;
}

int *descending(Node *head){
    int count = 0;
    Node *temp = head;

    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    int *num = new int[count];
    temp = head;

    for(int i = count - 1; i >= 0; i--){
        num[i] = temp->data;
        temp = temp->next;
    }

    return num;
}

int *chose_foward(Node *head, char * str){
    if(strcmp(str, "ASC") == 0){
        return ascending(head);
    }
    else if(strcmp(str, "DESC") == 0){
        return descending(head);
    } else{
        return NULL;
    }
}

void insert_node(Node *head, int data, int position){
    Node *temp = head;
    Node *cur = new Node(data);
    int k = 1;

    if(position == 1){
        cur->next = head;
        head->pre = cur;
        cur->pre = NULL;
    }

    while(temp != NULL && k < position){
        temp = temp->next;
        k++;
    }

    if(k != position){
        return;
    } else{
        cur->next = temp;
        cur->pre = temp->pre;

        temp->pre = cur;
        cur->pre->next = cur;
    }
}

void deleteArray(int* arr) {
    delete[] arr;
}

int main()
{
    Node* head = createDoublyLinkedListWithFiveNodes();

    cout << "Original list:" << endl;
    output_list(head);
    cout << endl;

    char asc[] = "ASC";
    char desc[] = "DESC";

    int* ascArray = chose_foward(head, asc);
    int* descArray = chose_foward(head, desc);

    cout << "Ascending order:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << ascArray[i] << " ";
    }
    cout << endl;

    cout << "Descending order:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << descArray[i] << " ";
    }
    cout << endl;

    deleteArray(ascArray);
    deleteArray(descArray);

    // Insert a new node with value 50 at position 3
    insert_node(head, 50, 3);

    cout << "List after insertion:" << endl;
    output_list(head);
    cout << endl;

    return 0;
}