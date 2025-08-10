// Three-way sort implementation in C++ (Dutch National Flag Problem)
// This program sorts an array containing negative, zero, and positive integers
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to perform three-way sort
void threeWaySort(vector<int>& arr) {
    int low = 0, mid = 0, high = arr.size() - 1;

    // Loop until mid crosses high
    while (mid <= high) {
        if (arr[mid] < 0) { 
            // If the current element is negative, swap it with the element at 'low'
            swap(arr[low], arr[mid]);
            low++; // Move 'low' pointer forward
            mid++; // Move 'mid' pointer forward
        } else if (arr[mid] > 0) {
            // If the current element is positive, swap it with the element at 'high'
            swap(arr[mid], arr[high]);
            high--; // Move 'high' pointer backward
        } else {
            // If the current element is zero, just move 'mid' pointer forward
            mid++;
        }
    }
}

int main() {
    // Input array containing negative, zero, and positive integers
    vector<int> arr = {0, -1, 2, 0, -3, 1, 0, -2};

    // Perform three-way sort
    threeWaySort(arr);

    // Print the sorted array
    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
