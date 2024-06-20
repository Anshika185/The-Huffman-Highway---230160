#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* rotateRight(Node* head, int k) {
    if (!head || k == 0) {
        return head;
    }

    Node* current = head;
    int length = 1;
    while (current->next != nullptr) {
        current = current->next;
        length++;
    }

    // Connect the last node to the head to make it circular
    current->next = head;

    // Find the new tail and the new head
    k = k % length;
    int stepsToNewHead = length - k;
    Node* newTail = head;
    for (int i = 0; i < stepsToNewHead - 1; i++) {
        newTail = newTail->next;
    }
    Node* newHead = newTail->next;

    // Break the circle
    newTail->next = nullptr;

    return newHead;
}

// Function to print the linked list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Function to create a linked list from user input
Node* createLinkedList() {
    int n, value;
    cout << "Enter the number of elements in the linked list: ";
    cin >> n;

    if (n <= 0) {
        return nullptr;
    }

    cout << "Enter the elements: ";
    cin >> value;
    Node* head = new Node(value);
    Node* current = head;

    for (int i = 1; i < n; ++i) {
        cin >> value;
        current->next = new Node(value);
        current = current->next;
    }

    return head;
}

int main() {
    Node* head = createLinkedList();

    int k;
    cout << "Enter the value of k: ";
    cin >> k;

    head = rotateRight(head, k);

    cout << "Rotated list: ";
    printList(head);

    return 0;
}