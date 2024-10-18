// COMSC-210 | Midterm 1 | Dan Pokhrel
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private: // Variables here cannot be accessed outside of the class
    // Node of a linked list, it holds some data plus pointers to the nodes following and preceding it
    struct Node {
        int data; // The data stored in this node
        Node* prev; // pointer to the node the comes before this node
        Node* next; // pointer to the node that comes after this node
        // Constructor
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            // Sets the node's variables to the parameters that were accessed during construction
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // Pointer to the first node in the list
    Node* tail; // Pointer to the last node in the list

public: // Variables/Functions that can be accessed outside of the class
    // Default constructor, used when no parameters are given, sets the head and tail pointers to null pointer
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // Inserts a node with data set to "value" after the node at the index "position"
    void insert_after(int value, int position) {
        if (position < 0) { // Checks for invalid index value
            cout << "Position must be >= 0." << endl;
            return; // If invalid, code execution stops here and returns to where the function was called
        }

        // Uses dynamic memory allocation to create a new node variable with data set to "value"
        Node* newNode = new Node(value);
        if (!head) { // If head is nullptr; i.e. there isn't a head node; the list is empty
            // Sets the head and tail pointers to point to this new node and returns to where this function was called
            head = tail = newNode;
            return;
        }

        Node* temp = head; // A temporary variable that is a pointer to the head node\
        // Iterates through list until it reaches the node at "position" or until the end of the list
        for (int i = 0; i < position && temp; ++i) 
            temp = temp->next; // sets tmp to point to the node that comes after the node it's currently pointing to

        if (!temp) { // tmp is a null pointer, which means the previous loop went past the last node
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // deallocates memory occupied by newNode
            return; // returns code execution to where the function was called
        }

        // This codeblock inserts newNode between tmp and the node after temp
        newNode->next = temp->next; // Sets newNode's next pointer to point to the node after temp
        newNode->prev = temp; // Sets newNode's previous pointer to point to temp
        if (temp->next) // if there exists a node after temp
            temp->next->prev = newNode; // sets the previous of the node after temp to point to newNode
        else // there is no node after temp; ie it's a tail node
            tail = newNode; // update's tail to point to newNode
        temp->next = newNode; // Sets temp's next to point to newNode
    }

    void delete_val(int value) { // Deletes the first node whose data is equal to "value"
        if (!head) return; // Don't do anything if the list is empty

        Node* temp = head; // A temporary variable that points to the head of the list
        
        // Iterate through list until it reaches the node with data equal to "value" or until the end of the list
        while (temp && temp->data != value) 
            temp = temp->next; // Moves temp pointer to the node that comes after temp

        // temp is a null pointer, which means the desired node wasn't found, and return to where this function was called
        if (!temp) return;

        // This code block reroutes the prev and next pointers for the nodes around temp
        if (temp->prev) // if there is a node before temp
            temp->prev->next = temp->next; // set the next of the node before temp to point to the node after temp
        else // if temp is pointing to the first node
            head = temp->next; // set head to point to the node after temp

        if (temp->next) // if there is a node after temp
            temp->next->prev = temp->prev; // set the prev of the node after temp to point to the node before temp
        else // if temp is pointing to the last node
            tail = temp->prev; // set tail to point to the node before temp

        delete temp; // deallocates the node pointed to by temp
    }

    void delete_pos(int pos) { // Deletes the node at index "pos"
        if (!head) { // if list is empty
            cout << "List is empty." << endl;
            return; // return to where this function was called
        }
    
        if (pos == 1) { // Wants to delete the first node in list
            pop_front(); // deletes the first node
            return; // returns to where this function was called
        }
    
        Node* temp = head; // a temporay variable that points to the head node
    
        for (int i = 1; i < pos; i++){ // Loops through the list until the node at index "pos" is reached
            if (!temp) { // went past the end of the list
                cout << "Position doesn't exist." << endl;
                return; // returns to where this function was called
            }
            else // within the list
                temp = temp->next; // move temp to point to the node after temp
        }
        if (!temp) { // went past the end of the list
            cout << "Position doesn't exist." << endl;
            return; // returns to where this function was called
        }
    
        if (!temp->next) { // there is no node after temp; ie temp points to the tail
            pop_back(); // delete the tail node
            return; // return to where this function was called
        }
    
        Node* tempPrev = temp->prev; // new variable pointing to the node before temp
        tempPrev->next = temp->next; // sets the next pointer of the node before temp to point to the node after temp
        temp->next->prev = tempPrev; // sets the prev pointer of the node after temp to point to the node before temp
        delete temp; // deallocates the node pointed to by temp
    }

    void push_back(int v) { // adds new node with data set to "v" at the end of the list
        Node* newNode = new Node(v); // dynamically allocates a new node with data set to "v"
        if (!tail) // if list is empty
            head = tail = newNode; // sets head and tail to point to this new node
        else { // list is not empty
            tail->next = newNode; // sets the next of the tail node to point to this new node
            newNode->prev = tail; // sets prev of new node to point to the tail node
            tail = newNode; // updates the tail to point to the new node
        }
    }
    
    void push_front(int v) { // add new node with data set to "v" at the beginning of the list
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}