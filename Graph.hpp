/*

Author : shlomi zecharia
ID : 315141242
Email : 2shlomiariel9@gmail.com

*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

namespace ariel {

    class Graph {

        private:

            std::vector<std::vector<int>> adjacencyMatrix;

        public:

            Graph() = default;

            void loadGraph(const std::vector<std::vector<int>>& graph);

            std::string printGraph() const;

            size_t numOfEdegs() const;

            bool contains(const ariel::Graph &other) const ;

            const std::vector<std::vector<int>>& getAdjacencyMatrix() const {
                return adjacencyMatrix;
            }


            //------- Operators -------

            //add
            Graph operator+(const Graph& other);
            Graph operator+=(const Graph& other);
            Graph operator+();
            //sub
            Graph operator-(const Graph& other);
            Graph operator-=(const Graph& other);
            Graph operator-();
            //mul
            Graph operator*=(const int c);
            Graph operator*(const Graph& other);
            //div
            Graph operator/=(const int c);

            //comparison
            bool operator ==(const Graph &other) const;
            bool operator >=(const Graph &other) const;
            bool operator <=(const Graph &other) const;
            bool operator >(const Graph &other) const;
            bool operator <(const Graph &other) const;


            //output
            friend std::ostream &operator <<(std::ostream &os, const Graph &graph);

            //prefix
            Graph& operator++();
            Graph& operator--();

            //postfix
            Graph operator++(int);
            Graph operator--(int);

    };

} 

#endif // GRAPH_HPP

