#include <iostream>
#include <unordered_map>

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        Node* pre = head;
        Node* newhead = new Node(head->val);
        Node* curr = head->next;
        Node* temp = newhead;

        while (curr != nullptr) {
            temp->next = new Node(curr->val);
            temp->random = pre;  // Tạm thời trỏ `random` về node gốc
            pre->next = temp;    // Lưu liên kết từ node gốc -> node sao chép
            temp = temp->next;
            pre = curr;
            curr = curr->next;
        }

        temp->random = pre;
        pre->next = temp;

        // Bước 2: Cập nhật `random` của danh sách sao chép
        Node* clone = newhead;
        while (clone != nullptr) {
            if(clone->random->random == nullptr){
                clone->random = nullptr;
            } else{
                clone->random = clone->random->random->next;
            }

            clone = clone->next;
        }

        return newhead;
    }
};

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << "Node value: " << temp->val;
        if (temp->random) {
            std::cout << ", Random points to: " << temp->random->val;
        } else {
            std::cout << ", Random points to: nullptr";
        }
        std::cout << std::endl;
        temp = temp->next;
    }
}

int main() {
    // Create a sample linked list with random pointers
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    node1->random = node3;
    node2->random = node1;
    node3->random = node4;
    node4->random = node2;

    Solution solution;
    Node* copiedList = solution.copyRandomList(node1);

    std::cout << "Original list:" << std::endl;
    printList(node1);

    std::cout << "Copied list:" << std::endl;
    printList(copiedList);

    return 0;
}
