/*

Author : shlomi zecharia
ID : 315141242
Email : 2shlomiariel9@gmail.com

*/

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <vector>
#include <stdexcept>
#include <iostream>

namespace ariel {

    class Algorithms {

        public:
        
        Algorithms() = default;

        // Function to check if the graph is connected
        static bool isConnected(const Graph& graph);

        // Function to find the shortest path between two vertices
        static std::string shortestPath(const Graph& graph, int start, int end);

        // Function to check if the graph contains a cycle
        static std::string isContainsCycle(const Graph& graph);

        // Function to check if the graph is bipartite
        static std::string isBipartite(const Graph& graph);

        // Function to check if the graph contains a negative cycle
        static bool negativeCycle(const Graph& graph);

   

    };

} 

#endif // ALGORITHMS_HPP

