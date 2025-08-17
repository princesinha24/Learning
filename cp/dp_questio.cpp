// Ninja and his Friends


// 0

// 100
// Ninja has a grid of size R x C, where each cell contains some chocolates. He has two friends: Alice and Bob, and wants to collect as many chocolates as possible using their help.



// Alice starts at the top-left cell (0, 0)
// Bob starts at the top-right cell (0, C - 1)
// Both can only move to the next row, and from position (i, j), they can move to:
// (i + 1, j)
// (i + 1, j - 1)
// (i + 1, j + 1)

// write the code to find the maximum number of chocolates Ninja can collect with the help of Alice and Bob.

#include <bits/stdc++.h>
using namespace std;

class Solution {
    int getMax(int i, int j1, int j2, vector<vector<int>>& g, vector<vector<vector<int>>>& dp){
        int n=g.size(),m=g[0].size();
        if(j1<0 || j1 >= m || j2<0 || j2>=m){
            return -1e8;
        }
        if(!dp[i][j1][j2]){
            return dp[i][j1][j2];
        }
        if(i==n-1){
            if(j1 == j2){
                dp[i][j1][j2]=g[i][j1];
            }
            else{
                dp[i][j1][j2]=g[i][j1]+g[i][j2];
            }
            return dp[i][j1][j2];
        }
        int maxi=-1e8;
        for (int k1=-1;k1<=1;k1++){
            for(int k2=-1;k2<=1;k2++){
                int val=g[i][j1];
                if(j1!=j2){
                    val+=g[i][j2];
                }
                val+=getMax(i+1, j1+k1, j2+k2, g, dp);
                maxi=max(maxi, val);
            }
        }
        dp[i][j1][j2]=maxi;
        return dp[i][j1][j2];
    }
public:
    int maxChocolates(vector<vector<int>>& g) {
        // Your code goes here
        int n=g.size(),m=g[0].size(); 
        vector<vector<vector<int>>>dp(n,vector<vector<int>>(m,vector<int>(m,0)));
        return getMax(0,0,m-1,g,dp);
    }
};
int main() {
    int R, C;
    cin >> R >> C;
    vector<vector<int>> grid(R, vector<int>(C));
    
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> grid[i][j];
        }
    }

    cout << maxChocolates(R, C, grid) << endl;

    return 0;
}