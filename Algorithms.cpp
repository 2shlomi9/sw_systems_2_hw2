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

        
        
    // ---------------- q1 : isConnected function ---------------------



    //------- helper function ---------

    void dfsRecursive(const std::vector<std::vector<int>>& matrix, std::vector<int>& colors, size_t vertex) {
        if (vertex < colors.size()) {
            colors[vertex] = 1; // gray

            // Visit all adjacent vertices of the current vertex
            for (size_t i = 0; i < matrix[vertex].size(); ++i) {
                if (matrix[vertex][i] && i < colors.size() && colors[i] == 0) { // If there is an edge and the adjacent vertex is not visited
                    dfsRecursive(matrix, colors, i); // Recursively visit the adjacent vertex
                }
            }

            colors[vertex] = 2; // black
        } else {
            // Handle invalid index (e.g., throw an exception, print an error message)
            std::cerr << "Invalid vertex index: " << vertex << std::endl;
            return;
        }
    }

    bool Algorithms::isConnected(const Graph& graph) {
        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();
        std::vector<int> colors(n, 0); // Initialize colors array

        // Start DFS from vertex 0
        dfsRecursive(matrix, colors, 0);

        // Check if all vertices are visited
        for (int c : colors) {
            if (c == 0) { // If any vertex is not visited, the graph is not connected
                return false;
            }
        }

        // Reset colors array
        std::fill(colors.begin(), colors.end(), 0);

        // Reverse the graph (transpose the adjacency matrix)
        std::vector<std::vector<int>> reversedMatrix(n, std::vector<int>(n, 0));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                reversedMatrix[i][j] = matrix[j][i];
            }
        }

        // Start DFS from every vertex
        for (size_t i = 0; i < n; ++i) {
            dfsRecursive(reversedMatrix, colors, i);

            // Check if all vertices are visited
            for (int c : colors) {
                if (c == 0) { // If any vertex is not visited, the graph is not strongly connected
                    return false;
                }
            }

            // Reset colors array for the next iteration
            std::fill(colors.begin(), colors.end(), 0);
        }

        // If all vertices are visited in every DFS, the graph is strongly connected
        return true;
    }




    // ---------------- q2 :  shortestPath  function ---------------------

    
    
    
    // Create a INF variable :

    const int INF = std::numeric_limits<int>::max();
    
    //------- helper functions : ---------

    // Check if the graph is directed graph:

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




    // Relax function (Use in Bellman-Ford algorithm)

    
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

    // ---------------- shortest path implemation ---------------------

    std::string Algorithms::shortestPath(const Graph& graph, int start, int end) {
        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();
        std::vector<int> d(n, INF);
        std::vector<int> p(n, -1);
        if (start >= 0 && start < static_cast<int>(n)) {
            d[static_cast<size_t>(start)] = 0;
        } else {
            // Handle invalid start vertex index
            return "Invalid start vertex index: " + std::to_string(start);
        }
        bool isDirected = isDirectedGraph(matrix);
        if (isDirected) {
            for (size_t i = 0; i < n - 1; ++i) {
                for (size_t u = 0; u < n; ++u) {
                    for (size_t v = 0; v < n; ++v) {
                        if (matrix[u][v] != 0 && d[u] != INF) {
                            relax(u, v, matrix[u][v], d, p);

                        }
                    }
                }
            }

            // Check for negative-weight cycles
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (matrix[u][v] != 0 && u < n && v < n && d[u] != INF && d[v] != INF && d[v] > d[u] + matrix[u][v]) {
                        return "No shortest path exists." ;
                    }
                }
            }
        } else {
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = u + 1; v < n; ++v) {  // Iterate only over one direction of each edge
                    if (matrix[u][v] != 0 && d[u] != INF) {
                        relax(u, v, matrix[u][v], d, p);

                    }
                }
            }
        }

        // Check for negative-weight cycles
        for (size_t u = 0; u < n; ++u) {
            for (size_t v = u + 1; v < n; ++v) {  // Iterate only over one direction of each edge
                if (matrix[u][v] != 0 && u < n && v < n && d[u] != INF && d[v] != INF && d[v] > d[u] + matrix[u][v]) {
                    return "No shortest path exists." ;
                }
            }
        }
    }

        // Reconstruct shortest path
        if (end >= 0 && end < static_cast<int>(n)) {
            if (d[static_cast<size_t>(end)] == INF) {
                return "-1"; // No path exists between start and end
            } else {
                std::stringstream ss;
                for (int v = end; v != -1; v = p[static_cast<size_t>(v)]) {
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




    std::string isContainsCycleHelper(const std::vector<std::vector<int>>& matrix, size_t v, std::vector<int>& p, std::vector<bool>& visited) {
        size_t n = matrix.size();
        visited[v] = true;
        for (size_t i = 0; i < n; i++) {
            if (matrix[v][i] != 0) { // There is an edge between v and i
                if (!visited[i]) {
                    p[i] = v;
                    std::string result = isContainsCycleHelper(matrix, i, p, visited); // Update `v` to `i`
                    if (result != "0") {
                        return result;
                    }
                } else if (p[v] != static_cast<int>(i)) {
                    // Cycle found
                    std::stack<int> stack; // Stack to store the cycle

                    // Start with current node `i` and push to the stack
                    for (int current = v; current != i; current = p[static_cast<size_t>(current)]) {
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
        return "0"; // No cycle found
    }




    std::string Algorithms::isContainsCycle(const Graph& graph) {
        size_t v =0; // Initialize the first vertex
        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();
        std::vector<int> p(n, -1); // Initialize ps array
        std::vector<bool> visited(n, false); // Initialize ps array
        return isContainsCycleHelper(matrix,v,p,visited);
    }





    // ---------------- q3 : isBipartite : ---------------------



    std::string Algorithms::isBipartite(const Graph& graph) {
        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();


        // Initialize colors array (0 - uncolored, 1 - first color, 2 - second color)
        std::vector<int> colors(n, 0);

        // Perform BFS from an arbitrary vertex
        std::queue<size_t> q;
        q.push(0); // Start with vertex 0
        colors[0] = 1; // Assign the first color to the starting vertex

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
            return "The graph is not bipartite (adjacent vertices have the same color).";
        }
    }



    // ---------------- q5 : negativeCycle : ---------------------



    bool Algorithms::negativeCycle(const Graph& graph) {
        const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();

        // Initialize distances array
        std::vector<std::vector<int>> dist(matrix); // Use a copy of the adjacency matrix

        if(isDirectedGraph(matrix)){
                // Floyd-Warshall algorithm to detect negative cycles
        for (size_t k = 0; k < n; ++k) {
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        // Update the distance between i and j
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t i = 0; i < n; ++i) {
            if (dist[i][i] < 0) {
                // Negative cycle detected
                return true;
            }
        }
            
        }
        else{

        // Floyd-Warshall algorithm to detect negative cycles
        for (size_t k = 0; k < n; ++k) {
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = i + 1; j < n; ++j) { // Iterate only over one direction of each edge
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        // Update the distance between i and j
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                        dist[j][i] = dist[i][j]; // Update the symmetric entry
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t i = 0; i < n; ++i) {
            if (dist[i][i] < 0) {
                // Negative cycle detected
                return true;
            }
        }
        }

        return false;
    }

}
