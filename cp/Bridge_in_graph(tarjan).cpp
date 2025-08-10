// Write a code to detect bridge in a graph using DFS (Tarjan's algorithm).
// The code should be able to handle undirected graphs and return the bridges found in the graph


// concept of low and tin is  tin is the time when the node is visited and low is the lowest reachable node from that node
// A bridge is an edge in a graph whose removal increases the number of connected components in the graph.
// In other words, if you remove a bridge, the graph becomes disconnected.
// To find bridges in a graph, we can use Depth First Search (DFS) and maintain two arrays: `tin` (time of first visit) and `low` (lowest reachable node).
// The `tin` array stores the time when a node is first visited, and the `low` array stores the lowest reachable node from that node.
// If `low[neighbor] > tin[node]`, then the edge (node, neighbor) is a bridge.
// This means that there is no back edge from the subtree rooted at `neighbor` to any ancestor of `node`, indicating that removing the edge (node, neighbor) will disconnect the graph.

// check this video for better understanding: https://www.youtube.com/watch?v=qrAub5z8FeA

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;    
// Function to perform DFS and find bridges in the graph
void dfs(int node, int parent, vector<int> &tin, vector<int> &low, vector<vector<int>> &adj, vector<pair<int, int>> &bridges, int &timer) {
    tin[node] = low[node] = timer++; // Initialize discovery time and low
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue; // Skip the parent node
        if (tin[neighbor] == -1) { // If the neighbor is not visited
            dfs(neighbor, node, tin, low, adj, bridges, timer); // Recursive DFS call
            low[node] = min(low[node], low[neighbor]); // Update        low value   
            if (low[neighbor] > tin[node]) { // Check if the edge is a bridge
                bridges.push_back({node, neighbor}); // Store the bridge
            }
        } else { // If the neighbor is already visited
            low[node] = min(low[node], tin[neighbor]); // Update low value
        }
    }
}
// Function to find bridges in the graph
vector<pair<int, int>> findBridges(int n, vector<vector<int>> &edges) {
    vector<vector<int>> adj(n); // Adjacency list representation of the graph
    for (const auto &edge : edges) {
        adj[edge[0]].push_back(edge[1]); // Add edge to the adjacency list
        adj[edge[1]].push_back(edge[0]); // Add reverse edge for undirected graph
    }
    vector<int> tin(n, -1); // Discovery time of each node
    vector<int> low(n, -1); // Low value of each node
    vector<pair<int, int>> bridges; // Vector to store bridges
    int timer = 0; // Timer to track discovery time
    for (int i = 0; i < n; i++) {   
        if (tin[i] == -1) { // If the node is not visited
            dfs(i, -1, tin, low, adj, bridges); // Start DFS from the node
        }
    }
    return bridges; // Return the list of bridges found in the graph
}   

// Example usage
int main() {
    int n = 5; // Number of nodes in the graph      
    vector<vector<int>> edges = {
        {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}
    }; // Edges of the graph
    vector<pair<int, int>> bridges = findBridges(n, edges); // Find bridges
    cout << "Bridges in the graph:\n";      
    for (const auto &bridge : bridges) {
        cout << bridge.first << " - " << bridge.second << endl; // Print each bridge
    }
    return 0; // Exit the program
}
// This code detects bridges in an undirected graph using DFS. It initializes discovery and low values