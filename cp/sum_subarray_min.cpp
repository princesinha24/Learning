// write a program to find the sum of minimum elements in all subarrays of a given array
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
// Function to calculate the sum of minimum elements in all subarrays
long long sumSubarrayMin(const vector<int>& arr) {
    stack<int> st; // Stack to store indices of array elements
    long long int ans = 0, i = 0; // Initialize answer and index
    const int mod = 1e9 + 7; // Modulo value to prevent overflow

    // Iterate through the array
    for (; i < arr.size(); i++) {
        // Process elements in the stack while the current element is smaller
        while (!st.empty()) {
            if (arr[st.top()] < arr[i]) {
                break; // Stop if the top of the stack is smaller
            }
            int num = st.top(); // Index of the top element
            int k;
            st.pop(); // Remove the top element
            if (st.empty()) {
                k = -1; // If stack is empty, set k to -1
            } else {
                k = st.top(); // Otherwise, set k to the new top
            }
            // Calculate contribution of the popped element
            ans += (arr[num] * (i - num) * (num - k));
            ans %= mod; // Apply modulo to prevent overflow
        }
        st.push(i); // Push the current index onto the stack
    }

    // Process remaining elements in the stack
    while (!st.empty()) {
        int num = st.top(); // Index of the top element
        int k;
        st.pop(); // Remove the top element
        if (st.empty()) {
            k = -1; // If stack is empty, set k to -1
        } else {
            k = st.top(); // Otherwise, set k to the new top
        }
        // Calculate contribution of the popped element
        ans += (arr[num] * (i - num) * (num - k));
        ans %= mod; // Apply modulo to prevent overflow
    }

    return ans; // Return the final answer
}

// Example usage
int main() {
    vector<int> arr = {3, 1, 2, 4}; //  Example array
    long long result = sumSubarrayMin(arr); // Calculate the sum of minimum elements in all subarrays
    cout << "Sum of minimum elements in all subarrays: " << result << endl; // Output the result
    return 0; // Exit the program
}
// This code calculates the sum of minimum elements in all subarrays of a given array using a stack to efficiently track the indices of elements. It iterates through the array, processing elements in a