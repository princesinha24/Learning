// You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.

// Node class to represent an element in the priority queue
class Node {
    public:
        int data; // Value of the element
        int pos;  // Position of the element in its list
        int col;  // Index of the list the element belongs to
};

// Custom comparator for the priority queue to sort nodes by their data value
class compare {
    public:
        bool operator()(Node* a, Node* b) {
            return a->data > b->data; // Min-heap based on data value
        }
};

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        // Priority queue to store nodes, sorted by their data value
        priority_queue<Node*, vector<Node*>, compare> pq;
        int maxVal = -1e6; // Track the maximum value in the current range
        vector<int> ans(2, 0); // Store the smallest range [start, end]
        int minDif = 1e7; // Minimum difference between max and min values in the range

        // Initialize the priority queue with the first element of each list
        for (int i = 0; i < nums.size(); i++) {
            maxVal = max(maxVal, nums[i][0]); // Update maxVal with the first element of each list
            Node* temp = new Node{nums[i][0], 0, i}; // Create a new node
            pq.push(temp); // Push the node into the priority queue
        }

        // Process the priority queue to find the smallest range
        while (true) {
            Node* temp = pq.top(); // Get the smallest element from the priority queue
            pq.pop(); // Remove the smallest element

            // Update the smallest range if the current range is smaller
            if (minDif > maxVal - temp->data) {
                minDif = maxVal - temp->data; // Update the minimum difference
                ans[0] = temp->data; // Update the start of the range
                ans[1] = maxVal; // Update the end of the range
            }

            // Check if there are more elements in the current list
            if (nums[temp->col].size() - 1 > temp->pos) {
                // Create a new node for the next element in the current list
                Node* temp1 = new Node{nums[temp->col][temp->pos + 1], temp->pos + 1, temp->col};
                pq.push(temp1); // Push the new node into the priority queue
                maxVal = max(maxVal, temp1->data); // Update maxVal with the new element
            } else {
                // If the current list is exhausted, break the loop
                break;
            }
        }

        return ans; // Return the smallest range
    }
};

// Example usage
#include <iostream>
#include <vector>
using namespace std;

int main() {
    Solution sol;
    vector<vector<int>> nums = {{1, 2, 3}, {4, 5}, {1, 2}};
    vector<int> result = sol.smallestRange(nums);
    cout << "Smallest range: [" << result[0] << ", " << result[1] << "]" << endl;
    return 0;
}