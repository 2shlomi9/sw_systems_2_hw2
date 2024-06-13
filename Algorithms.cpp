/*

Author : shlomi zecharia
ID : 315141242
Email : 2shlomiariel9@gmail.com

*/

#include "Algorithms.hpp"
#include <limits>
#include <algorithm>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include "Graph.hpp"

namespace ariel {

   
   // Create a INF variable :
    const int INF = std::numeric_limits<int>::max();


// ----------------------------- Helper Functions & Graph Algorithms -----------------------------


    // ------------ isDirectedGraph function -----------
    //       (Check if the graph is directed graph)

    bool isDirectedGraph(const std::vector<std::vector<int>>& matrix) {
        size_t n = matrix.size();
        
        // Check if the matrix is square
        if (n != matrix[0].size()) {
            return false; // Not a valid adjacency matrix
        }

        // Check for symmetry and equality of corresponding elements
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (matrix[i][j] != matrix[j][i]) {
                    return true; // Asymmetric elements found, indicating a directed graph
                }
            }
        }

        // If no asymmetric elements were found, the graph is undirected
        return false;
    }


// ------------------------ : DFS algorithm :  ------------------------ 

    // -------------- DFS function --------------

    void dfs(const std::vector<std::vector<int>>& matrix, std::vector<int>& colors, size_t vertex) {
        if (vertex < colors.size()) {
            colors[vertex] = 1; // gray

            // Visit all adjacent vertices of the current vertex
            for (size_t i = 0; i < matrix[vertex].size(); i++) {
                if (matrix[vertex][i] && i < colors.size() && colors[i] == 0) { // If there is an edge and the adjacent vertex is not visited
                    dfs(matrix, colors, i); // Recursively visit the adjacent vertex
                }
            }

            colors[vertex] = 2; // black
        } else {
            // Handle invalid index (e.g., throw an exception, print an error message)
            std::cerr << "Invalid vertex index: " << vertex << std::endl;
            return;
        }
    }



    // -------------- DFS to detect cycle function --------------

    std::string dfsCycleDetection(const std::vector<std::vector<int>>& matrix, size_t v, std::vector<int>& parent, std::vector<int>& color) {
        const size_t n = matrix.size();
        color[v] = 1; // Mark the current vertex as gray (being visited)
        for (size_t i = 0; i < n; i++) {
            if (matrix[v][i] != 0) { // There is an edge between v and i
                if (color[i] == 0) { // If vertex i is white (not visited)
                    parent[i] = v;
                    std::string result = dfsCycleDetection(matrix, i, parent, color); // Visit vertex i
                    if (result != "0") {
                        return result; // Return the cycle if found
                    }
                } else if (color[i] == 1 && parent[v] != static_cast<int>(i)) { // If vertex i is gray and not the parent
                    // Cycle found
                    std::stack<int> stack; // Stack to store the cycle

                    // Start with current node i and push to the stack
                    for (int current = v; current != i; current = parent[static_cast<size_t>(current)]) {
                        stack.push(current);
                    }
                    stack.push(i); // Push the starting node of the cycle

                    // Create the cycle string
                    std::string cycle = "The cycle is: " + std::to_string(stack.top());
                    stack.pop();
                    while (!stack.empty()) {
                        cycle += " -> " + std::to_string(stack.top());
                        stack.pop();
                    }
                    cycle += " -> " + std::to_string(i); // complete the cycle

                    return cycle;
                }
            }
        }
        color[v] = 2; // Mark the current vertex as black (visited)
        return "0"; // No cycle found
    }


// ------------------------ : Kosaraju's algorithm :  ------------------------


    // -------------- Transpose function --------------
    //         (Transpose the edges of the graph)

    std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>>& matrix) {
        size_t n = matrix.size();
        std::vector<std::vector<int>> transposedMatrix(n, std::vector<int>(n, 0));

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                transposedMatrix[j][i] = matrix[i][j];
            }
        }

        return transposedMatrix;
    }


    // -------------- DFS to Order vertex by Finish Time --------------

    void dfsFillOrder(const std::vector<std::vector<int>>& matrix, size_t vertex, std::vector<int>& colors, std::stack<int>& stack) {
        colors[vertex] = 1; // gray

        // Visit all adjacent vertices of the current vertex
        for (size_t i = 0; i < matrix[vertex].size(); i++) {
            if (matrix[vertex][i] && colors[i] == 0) { // If there is an edge and the adjacent vertex is not visited
                dfsFillOrder(matrix, i, colors, stack); // Recursively visit the adjacent vertex
            }
        }

        stack.push(vertex); // Push the current vertex onto the stack
    }

    // -------------- Kosaraju's function --------------

    bool kosaraju(const std::vector<std::vector<int>>& matrix) {
        
        size_t n = matrix.size();

        // Perform the first DFS traversal to fill the stack
        std::stack<int> stack;
        std::vector<int> colors(n, 0); // Initialize colors array

        for (size_t i = 0; i < n; ++i) {
            if (colors[i] == 0) {
                dfsFillOrder(matrix, i, colors, stack);
            }
        }

        // Transpose the graph
        std::vector<std::vector<int>> transposedMatrix = transpose(matrix);

        // Reset colors array for the second DFS traversal
        std::fill(colors.begin(), colors.end(), 0);

        // Perform the second DFS traversal using the transposed graph
        while (!stack.empty()) {
            size_t vertex = static_cast<size_t>(stack.top());
            stack.pop();

            if (colors[vertex] == 0) {
                dfs(transposedMatrix, colors, vertex);
            }
        }

        // Check if all vertices are visited in the second traversal
        for (int c : colors) {
            if (c == 0) {
                return false;
            }
        }

        return true;
    }


// ------------------------ : Bellman-Ford algorithm :  ------------------------


    // -------------- Relax function --------------
    
    void relax(size_t u, size_t v, int weight, std::vector<int>& d, std::vector<int>& p) {

        if (u < d.size() && v < d.size()) {
            if (d[u] != INF && d[v] > d[u] + weight) {
                d[v] = d[u] + weight;
                p[v] = u;
            }
        } 
        else {
            std::cerr << "Invalid vertex index: " << u << " or " << v << std::endl;
        }
    }


    // -------------- Bellman-Ford function --------------        

    void bellmanFord(const std::vector<std::vector<int>>& matrix, int start, std::vector<int>& dist, std::vector<int>& parent, std::vector<int>& isNegativeCycle) {
        
        size_t n = matrix.size();

        if (start >= 0 && start < static_cast<int>(n)) {
            dist[static_cast<size_t>(start)] = 0;
        } else {
            // Handle invalid index (e.g., throw an exception, print an error message)
            std::cerr << "Invalid vertex index: " << start << std::endl;
            return;
        }

        // Iterate over all vertices n-1 times (Relax all the edegs n-1 times)
        for(size_t i = 0; i < n-1; i++){
            // Iterate all over the edegs in the graph
            for (size_t u = 0; u < n; u++) {
                for (size_t v = 0; v < n; v++) {
                    if(isDirectedGraph(matrix)){
                        if(u != v && matrix[u][v] != 0){ 
                            relax(u,v,matrix[u][v],dist,parent); // relax edge (u,v)
                        }
                    }
                    else{
                        if(u != v && matrix[u][v] != 0 && v!=parent[u]){ 
                            relax(u,v,matrix[u][v],dist,parent); // relax edge (u,v)
                        }
                    }
                }
            }
        }

        // Check for negative cycle :
        for (size_t u = 0; u < n; u++) {
            for (size_t v = 0; v < n; v++) {
                if(isDirectedGraph(matrix)){
                    if(u != v && matrix[u][v] != 0){
                        int distance = dist[v];
                        relax(u,v,matrix[u][v],dist,parent);
                        if(distance > dist[v]) {
                            isNegativeCycle[v] = 1; // Negative cycle found in v
                        }
                    }
                }
                else{
                    if(u != v && matrix[u][v] != 0 && v!=parent[u]){
                        int distance = dist[v];
                        relax(u,v,matrix[u][v],dist,parent);
                        if(distance > dist[v]) {
                            isNegativeCycle[v] = 1; // Negative cycle found in v
                        }
                    }
                }
            }
        }    
    }


    
// ------------------------ : Floyd-Warshall algorithm :  ------------------------

    // -------------- Floyd-Warshall function --------------
    void floydWarshall(std::vector<std::vector<int>>& dist) {
    
        size_t n = dist.size(); 
        
        // Initialize the distance matrix: set the distance to infinity for all pairs except self-loops
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (dist[i][j] == 0 && i != j) {
                    dist[i][j] = INF; // Set the distance to infinity for non-self-loop pairs with a zero value
                }
            }
        }
        
        // Floyd-Warshall algorithm
        for (size_t k = 0; k < n; k++) { // Iterate through all vertices as intermediate points
            for (size_t i = 0; i < n; i++) { 
                for (size_t j = 0; j < n; j++) { 
                
                    // If there is a shorter path through vertex k, update the distance
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }



// ----------------------------- Graph Functions -----------------------------

        

    // ------------------- q1 : isConnected function ------------------------
    /*
    -Checks whether a given graph is strongly connected or not
    -Using : dfs function & kosaraju function
    -If the graph directed - Call kosaraju function
    -If the graph undirected - Call dfs from vertex 0
    */

    // ---------------- isConnected implemation ---------------------



    bool Algorithms::isConnected(const Graph& graph) {
        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();
        std::vector<int> colors(n, 0); // Initialize colors array

        // check if the graph is directed
        if(isDirectedGraph(matrix)){

            return kosaraju(matrix);
        }

        else{
            dfs(matrix,colors,0);
             // Check if all vertices are visited
            for (int c : colors) {
                if (c == 0) { // If any vertex is not visited, the graph is not strongly connected
                    return false;
                }
            }
        }

        return true;
    }



    // ------------------- q2 : shortestPath function -----------------------
 
    /*
    -Finds the shortest path between two vertices in the graph
    -Using : bellmanFord function
    -If a negative cycle found - Return "No path exists between start and end"
    -Returns the shortest path as a string
    */

    // ---------------- shortest path implemation ---------------------


    std::string Algorithms::shortestPath(const Graph& graph, int start, int end) {

        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();

        std::vector<int> dist(n, INF);  // Distances from the start vertex
        std::vector<int> parent(n, -1); // Parent of each vertex (for path reconstruction)
        std::vector<int> isNegativeCycle(n, 0);// Detect negative cycles

        // Run the Bellman-Ford algorithm
        bellmanFord(matrix, start, dist, parent, isNegativeCycle);
        // Reconstruct the shortest path
        if (end >= 0 && end < static_cast<int>(n)) {
            
            if (dist[static_cast<size_t>(end)] == INF) {
                return "No path exists between " + std::to_string(start) + " and " + std::to_string(end); // No path exists between start and end
            }
            else if (isNegativeCycle[static_cast<size_t>(end)] == 1) {
                return "Detect negative cycle, no shortest path"; // No path exists between start and end (Negative cycle)
            } else {
                std::stringstream ss;
                for (int v = end; v != -1; v = parent[static_cast<size_t>(v)]) {
                    ss << v;
                    if (v != start) {
                        ss << ">-";
                    }
                }
                std::string path = ss.str();
                std::reverse(path.begin(), path.end());
                return path;
            }
        } else {
            // Handle invalid end vertex index
            return "Invalid end vertex index: " + std::to_string(end);
        }
    }




    // ---------------- q3 : isContaionsCycle : ---------------------
    
    /*
    -Checks whether the graph contains a cycle or not
    -Using : dfsCycleDetection function
    -Return the cycle as a string
    */


    // ---------------- isContainsCycle implemation ---------------------

    std::string Algorithms::isContainsCycle(const Graph& graph) {
        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        const size_t n = matrix.size();
        std::vector<int> parent(n, -1); // Initialize parent array
        std::vector<int> color(n, 0); // Initialize color array (0 for white, 1 for gray, 2 for black)
        std::string result;

        // Perform DFS from each vertex to check for cycles
        for (size_t i = 0; i < n; ++i) {
            if (color[i] == 0) { // If vertex is white (not visited)
                result = dfsCycleDetection(matrix, i, parent, color);
                if (result != "0") {
                    return result; // Return the cycle if found
                }
            }
        }

        return "No cycle found in the graph";
    }




    // ---------------- q4 : isBipartite : ---------------------
    
    /*
    -Checks whether the graph is bipartite or not
    -Uses BFS to color the vertices of the graph in two different colors
    -Returns the two groups of vertices if bipartite as a string
    */


    // ---------------- isBipartite implemation ---------------------


    std::string Algorithms::isBipartite(const Graph& graph) {
        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();


        // Initialize colors array (0 - uncolored, 1 - Blue, 2 - Red)
        std::vector<int> colors(n, 0);

        // Perform BFS from an arbitrary vertex
        std::queue<size_t> q;
        q.push(0); // Start with vertex 0
        colors[0] = 1; // Mark the starting vertex as blue

        std::string groupA = "A={" + std::to_string(0) + ", "; // Add starting vertex to group A
        std::string groupB = "B={";

        bool isBipartite = true;
        while (!q.empty()) {
            size_t u = q.front();
            q.pop();

            // Iterate through adjacent vertices of the current vertex
            for (size_t v = 0; v < n; ++v) {
                if (matrix[u][v] && colors[v] == 0) { // If there is an edge and the adjacent vertex is uncolored
                    colors[v] = 3 - colors[u]; // Assign the opposite color to the adjacent vertex
                    q.push(v); // Add the adjacent vertex to the queue

                    if (colors[v] == 1) {
                        groupA += std::to_string(v) + ", ";
                    } else {
                        groupB += std::to_string(v) + ", ";
                    }
                } else if (matrix[u][v] && colors[v] == colors[u]) { // Check for color conflicts
                    isBipartite = false;
                    break; // Stop BFS if a conflict is found
                }
            }
        }

        // If no color conflicts are found, the graph is bipartite
        if (isBipartite) {
            groupA.pop_back(); // Remove the trailing comma
            groupA.pop_back(); // Remove the space
            groupA += "}";
            groupB.pop_back(); // Remove the trailing comma
            groupB.pop_back(); // Remove the space
            groupB += "}";
            return groupA + " " + groupB;
        } else {
            return "The graph is not bipartite (adjacent vertices have the same color)";
        }
    }



    // ---------------- q5 : negativeCycle : ---------------------
    
    /*
    -Checks whether the graph contains a negative cycle or not
    -Using : Bellman-Ford algorithm & floydWarshall
    -Returns true If a negative cycle found
    */


    // ---------------- negativeCycle implemation ---------------------
    
    bool Algorithms::negativeCycle(const Graph& graph) {
        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();

        // check if the graph SSC 
        if(isConnected(graph)){
            int start = 0;
            std::vector<int> dist(n, INF);  // Distances from the start vertex
            std::vector<int> parent(n, -1); // Parent of each vertex (for path reconstruction)
            std::vector<int> isNegativeCycle(n, 0);// Detect negative cycles
            // Run the Bellman-Ford algorithm
            bellmanFord(matrix, start, dist, parent, isNegativeCycle);
            for (size_t i = 0; i < n; i++){
                if(isNegativeCycle[i] == 1) {
                        return true;
                }
            }
        }
        // For directed graph use Floyd-Warshall
        if(isDirectedGraph(matrix)){
            std::vector<std::vector<int>> dist(matrix); // Initialize distance matrix with the input adjacency matrix
            // Run the Floyd-Warshall algorithm
            floydWarshall(dist);
            for (size_t i = 0; i < n; i++){
                if(dist[i][i] < 0) {
                        return true;
                }
            }
        }

        // For undirected graph use Bellman-Ford
        else{

            for (int start = 0; start < n; ++start) {
                std::vector<int> dist(n, INF);  // Distances from the start vertex
                std::vector<int> parent(n, -1); // Parent of each vertex (for path reconstruction)
                std::vector<int> isNegativeCycle(n, 0); // Detect negative cycles
                // Run the Bellman-Ford algorithm
                bellmanFord(matrix, start, dist, parent, isNegativeCycle);
                
                for (size_t i = 0; i < n; i++) {
                    if (isNegativeCycle[i] == 1) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
}
