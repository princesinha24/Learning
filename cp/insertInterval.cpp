/*
You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and 
the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval 
newInterval = [start, end] that represents the start and end of another interval. Insert newInterval into intervals such 
that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals 
(merge overlapping intervals if necessary).
*/

#include <bits/stdc++.h>
using namespace std;


class Solution {
    public:
        vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
            vector<vector<int>> ans;
            int i = 0, n = intervals.size();
            
            // Handle intervals that come completely before the new interval
            for (i = 0; i < n; i++) {
                if (newInterval[0] > intervals[i][1]) {
                    ans.push_back(intervals[i]);
                } else {
                    break;
                }
            }
    
            // Handle the overlapping intervals
            vector<int> temp;
            temp.push_back(newInterval[0]); // Start of the merged interval
            if (i < n) {
                temp[0] = min(temp[0], intervals[i][0]); // Adjust start if overlapping
            }
            int val = newInterval[1]; // End of the merged interval
            while (i < n) {
                if (newInterval[1] < intervals[i][0]) {
                    break; // No more overlap
                } else {
                    val = max(val, intervals[i][1]); // Extend the end of the merged interval
                    i += 1;
                }
            }
            temp.push_back(val); // Add the end of the merged interval
            ans.push_back(temp);
    
            // Handle intervals that come completely after the new interval
            while (i < n) {
                ans.push_back(intervals[i]);
                i += 1;
            }
            return ans;
        }
    };
