// write a code for articulation point in a graph using DFS
#include <iostream>
#include <vector>
using namespace std;
// Function to perform DFS and find articulation points in the graph
void dfs(int node, int parent, vector<int> &tin, vector<int> &low, vector<vector<int>> &adj, vector<int> &articulationPoints, int &timer) {
    tin[node] = low[node] = timer++; // Initialize discovery time and low
    int children = 0; // Count of children for the current node
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue; // Skip the parent node
        if (tin[neighbor] == -1) { // If the neighbor is not visited
            dfs(neighbor, node, tin, low, adj, articulationPoints, timer); // Recursive DFS call
            low[node] = min(low[node], low[neighbor]); // Update low value
            if (low[neighbor] >= tin[node] && parent != -1) { // Check if the node is an articulation point
                articulationPoints.push_back(node); // Store the articulation point
            }
            children++; // Increment the count of children
        } else { // If the neighbor is already visited
            low[node] = min(low[node], tin[neighbor]); // Update low value
        }
    }
    if (parent == -1 && children > 1) { // If the root node has more than one child, it is an articulation point
        articulationPoints.push_back(node); // Store the articulation point
    }
}
// Function to find articulation points in the graph
vector<int> findArticulationPoints(int n, vector<vector<int>> &edges) {
    vector<vector<int>> adj(n); // Adjacency list representation of the graph
    for (const auto &edge : edges) {
        adj[edge[0]].push_back(edge[1]); // Add edge to the adjacency list
        adj[edge[1]].push_back(edge[0]); // Add reverse edge for undirected graph
    }
    vector<int> tin(n, -1); // Discovery time of each node
    vector<int> low(n, -1); // Low value of each node
    vector<int> articulationPoints; // Vector to store articulation points
    int timer = 0; // Timer to track discovery time
    for (int i = 0; i < n; i++) {
        if (tin[i] == -1) { // If the node is not visited
            dfs(i, -1, tin, low, adj, articulationPoints, timer); // Start DFS from the node
        }
    }
    return articulationPoints; // Return the list of articulation points found in the graph
}
// Example usage
int main() {
    int n = 5; // Number of nodes in the graph
    vector<vector<int>> edges = {
        {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}
    }; // Edges of the graph
    vector<int> articulationPoints = findArticulationPoints(n, edges); // Find articulation points
    cout << "Articulation points in the graph:\n";
    for (int point : articulationPoints) {
        cout << point << " "; // Print each articulation point
    }
    cout << endl;
    return 0; // Exit the program
}
// This code detects articulation points in an undirected graph using DFS. It initializes discovery and low
// values, performs DFS to find articulation points, and stores them in a vector. The main function demonstrates how to use the `findArticulationPoints` function and prints the results. The
// articulation points are nodes that, when removed, increase the number of connected components in the graph.
// This is useful for network reliability analysis, where identifying critical nodes can help in understanding the robustness
// of the network structure.
// The algorithm runs in O(V + E) time complexity, where V is the number of vertices and E is the number of edges in the graph.
// This is efficient for large graphs, making it suitable for real-world applications in network analysis and graph theory.
// The code can be further optimized or modified to handle directed graphs or weighted edges if needed,
// but the current implementation focuses on undirected graphs for articulation point detection.
// The code is structured to be easily understandable, with clear variable names and comments explaining each step
// of the process. This makes it suitable for educational purposes as well as practical applications in competitive programming and algorithm design.
// The use of recursion in the DFS function allows for a clean and concise implementation
// of the depth-first search algorithm, which is a fundamental technique in graph traversal.