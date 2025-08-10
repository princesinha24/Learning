// using topological sort to find the shortest path in a Directed Acyclic Graph (DAG)
// other method is dijkstra's algorithm -> solved by priority queue with minimum distance

// Function to perform topological sort on the graph
vector<int> topological_sort(const vector<vector<pair<int,int>>> &a, vector<int> &order, int n)
{
    vector<int>v; // Vector to store the topological order
    for(int i=0;i<n;i++){
        if(order[i]==0){ // If the node has no incoming edges, add it to the order
            v.push_back(i);
        }
    }
    for(int i=0;i<v.size();i++){
        for(int j=0;j<a[v[i]].size();j++){
            order[a[v[i]][j].first]--; // Reduce the incoming edge count for adjacent nodes
            if(order[a[v[i]][j].first]==0){ // If no incoming edges remain, add to the order
                v.push_back(a[v[i]][j].first);
            }
        }
    }
    return v; // Return the topological order
}

// Function to find the shortest path in a Directed Acyclic Graph (DAG)
vector<int> shortestPathInDAG(int n, int m, vector<vector<int>> &edges, int pos)
{
    // Create adjacency list representation of the graph
    vector<vector<pair<int,int>>> a(n);
    vector<int>order(n,0); // Array to store the count of incoming edges for each node
    for(int i=0;i<m;i++){
        a[edges[i][0]].push_back(make_pair(edges[i][1],edges[i][2])); // Add edge with weight
        order[edges[i][1]]++; // Increment incoming edge count for the destination node
    }
    
    // Perform topological sort
    vector<int>v;
    v=topological_sort(a,order,n);
    
    // Initialize the shortest path distances
    vector<int>ans(n,-1); // -1 indicates unreachable nodes
    ans[pos]=0; // Set the starting node's distance to 0
    // Process nodes in topological order
    for(int i=0;i<v.size();i++){
        if(ans[v[i]]==-1){ // Skip if the node is unreachable
            continue;
        }
        for(int j=0;j<a[v[i]].size();j++){
            // Update the shortest path distance for adjacent nodes
            if(ans[a[v[i]][j].first]==-1){
                ans[a[v[i]][j].first]=a[v[i]][j].second+ans[v[i]];
            }
            else{
                ans[a[v[i]][j].first]=min(ans[a[v[i]][j].first],a[v[i]][j].second+ans[v[i]]);
            }
        }
    }
    return ans; // Return the shortest path distances
}