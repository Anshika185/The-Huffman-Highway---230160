#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* reverseList(Node* head) {
    Node* previous = nullptr;
    Node* curr = head;
    Node* next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = previous;
        previous = curr;
        curr = next;
    }
    return previous;
}

bool isPalindrome(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }

    // Find the middle of the linked list
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse the second half of the list
    Node* secondHalf = reverseList(slow);
    Node* secondHalfCopy = secondHalf; 

    // Compare the first and second half
    Node* firstHalf = head;
    bool isPalin = true;
    while (secondHalf != nullptr) {
        if (firstHalf->data != secondHalf->data) {
            isPalin = false;
            break;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    // Restore the second half back to original
    reverseList(secondHalfCopy);

    return isPalin;
}

// Function to print the linked list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

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

    if (isPalindrome(head)) {
        cout << "The given linked list is a palindrome." << endl;
    } else {
        cout << "The given linked list is not a palindrome." << endl;
    }

    printList(head); // List should be restored to its original state

    return 0;
}