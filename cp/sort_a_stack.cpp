#include <iostream>
#include <stack>
using namespace std;

void SortedStack(stack<int> &s, int num) {
    // Base case: if the stack is empty or the top element is less than or equal to num, push num onto the stack
    if(s.empty() || s.top()<=num){
        s.push(num);
        return;
    }
    int val=s.top(); 
    s.pop();		// Pop the top element from the stack
    SortedStack(s, num); // Recursively call SortedStack to insert num in sorted order
    s.push(val); // Push the popped element back onto the stack
}

// Function to sort a stack using recursion
void sortStack(stack<int> &s) {
    if(s.empty()){
        return;
    }
    int num=s.top();
    s.pop();
    sortStack(s); // Recursively sort the remaining stack
    SortedStack(s, num); // Insert the popped element in sorted order
}

// provide test cases
int main() {
    stack<int> s;
    s.push(3);
    s.push(1);
    s.push(4);
    s.push(2);
    s.push(1);
    cout << "Original stack: ";
    stack<int> temp = s; // Create a temporary stack to print the original stack
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
    sortStack(s);
    cout << "Sorted stack: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    return 0;
}