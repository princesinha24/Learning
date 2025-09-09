/* 
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array 
 of the non-overlapping intervals that cover all the intervals in the input.

 logic:
 1. Sort the intervals based on the starting time. -> imp
 2. Initialize a new list to store merged intervals.
 3. Iterate through the sorted intervals:
    - If the current interval overlaps with the last merged interval, merge them.
    - Otherwise, add the current interval to the merged list.
*/

#include <bits/stdc++.h>
using namespace std;
class Solution {
    public:
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            // Sort the intervals based on the starting time
            sort(intervals.begin(), intervals.end());
            
            int j = 0, n = intervals.size();
            int first = intervals[0][0]; // Start of the first interval
            int last = 0, count = 1; // Initialize last and count
            vector<vector<int>> ans; // Resultant merged intervals
            
            // Iterate through the intervals
            for (int i = 1; i < n; i++) {
                // Process overlapping intervals
                while (j < n) {
                    if (intervals[j][1] < intervals[i][0]) {
                        // Update the last endpoint to the maximum of the current last and the interval's end
                        last = max(last, intervals[j][1]);
                        count--; // Decrease count as the interval is processed
                        j++;
                    } else {
                        break; // Stop if no overlap
                    }
                }
                // If no overlapping intervals remain
                if (count == 0) {
                    vector<int> temp;
                    temp.push_back(first); // Add the start of the merged interval
                    temp.push_back(last); // Add the end of the merged interval
                    ans.push_back(temp); // Add to the result
                    first = intervals[j][0]; // Update the start for the next interval
                }
                count++; // Increment count for the current interval
            }
            
            // Process remaining intervals
            while (j < n) {
                last = max(last, intervals[j][1]); // Update the last endpoint
                j++;
            }
            vector<int> temp;
            temp.push_back(first); // Add the start of the last merged interval
            temp.push_back(last); // Add the end of the last merged interval
            ans.push_back(temp); // Add to the result
            
            return ans; // Return the merged intervals
        }
    };