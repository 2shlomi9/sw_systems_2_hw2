/*

Author : shlomi zecharia
ID : 315141242
Email : 2shlomiariel9@gmail.com

*/
#include "Graph.hpp"
#include <vector>
#include <stdexcept>
#include <iostream>

namespace ariel{

    // Implementation of the loadGraph function
    
    void Graph::loadGraph(const std::vector<std::vector<int>>& graph) {

        int n = graph.size();
        for (const auto& row : graph) {
            if (row.size() != n) {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }

        adjacencyMatrix = graph;
    }
    
    // Implemetation of printGraph function
    
    std::string Graph::printGraph() const {
        size_t n = this->getAdjacencyMatrix().size();
        std::string result = "";

        if (n == 0) {
            return "[]";
        }

        for (size_t i = 0; i < n; i++) {
            result += "[";
            for (size_t j = 0; j < n - 1; j++) {
                result += std::to_string(this->getAdjacencyMatrix()[i][j]) + ", ";
            }
            result += std::to_string(this->getAdjacencyMatrix()[i][n - 1]) + "]";
            if (i != n - 1) { // Add newline character if not the last row
                result += "\n";
            }
        }

        return result;
    }



    //implemetation of numOfEdegs function 
    //return num of edegs for directed or undirected graph

    size_t ariel::Graph::numOfEdegs() const{
        size_t n = this-> adjacencyMatrix.size();
        size_t Edegs = 0;
        bool isDirected = false;

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < i; j++) {
                if (this->adjacencyMatrix[i][j] != this->adjacencyMatrix[j][i]) {
                    isDirected = true; 
                }
            }
        }
        

        for (size_t i = 0; i < n; i++){
            for(size_t j=0; j<n; j++){
                if(this->adjacencyMatrix[i][j] != 0){
                    Edegs++;
                }
            }
        }

        if(isDirected){
            return Edegs;
        }
        return Edegs/2;
    
    }

    //implemetation of contains function
    //this function check if graph(other) contains in graph(this)
    
    bool ariel::Graph::contains(const ariel::Graph &other) const {
        size_t n_this = adjacencyMatrix.size();
        size_t n_other = other.adjacencyMatrix.size();

        // Check if the size of the other graph is smaller than or equal to the size of this graph
        if (n_other > n_this) {
            return false;
        }

        for (size_t i = 0; i < n_other; ++i) {
            for (size_t j = 0; j < n_other; ++j) {
                // Check if any edge in other is not present in this
                if (other.adjacencyMatrix[i][j] && !adjacencyMatrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    // ---------- Operators -----------

    //----------- Add -------------

    ariel::Graph Graph:: operator+(const ariel::Graph& other) {
        size_t n = this-> adjacencyMatrix.size();
        if (n != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Both of the matrix should be in the same size !");
            return *this;

        }

        std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                result[i][j] += this->adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
            }
            
        }
        Graph res;
        res.loadGraph(result);

        return res;
    }
    ariel::Graph Graph::  operator+(){return *this;}


    ariel::Graph Graph:: operator+=(const ariel::Graph& other) {
        size_t n = this-> adjacencyMatrix.size();
        if (n != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Both of the matrix should be in the same size !");
            return *this;

        }
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                this->adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
            
        }
        return *this;
    }


    //----------- Sub -------------


    ariel::Graph Graph:: operator-(const ariel::Graph& other) {
        size_t n = this-> adjacencyMatrix.size();
        if (n != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Both of the matrix should be in the same size !");
            return *this;
        }

        std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                result[i][j] += this->adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
            }
            
        }
        Graph res;
        res.loadGraph(result);

        return res;
    }
    ariel::Graph Graph:: operator-=(const ariel::Graph& other) {
        size_t n = this-> adjacencyMatrix.size();
        if (n != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Both of the matrix should be in the same size !");
            return *this;
        }
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                this->adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
            
        }
        return *this;
    }

    ariel::Graph Graph:: operator-(){
        size_t n = this-> adjacencyMatrix.size();
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                this->adjacencyMatrix[i][j] *= -1;
            }
            
        }
        return *this;
    }


    //----------- Mul -------------


    ariel::Graph Graph:: operator*=(const int c) {
        size_t n = this-> adjacencyMatrix.size();
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                this->adjacencyMatrix[i][j] *= c;
            }
            
        }
        return *this;
    }

    ariel::Graph Graph:: operator*(const ariel::Graph& other){
        size_t n = this-> adjacencyMatrix.size();
        if (n != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Both of the matrix should be in the same size !");
            return *this;
        }
        std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                for (size_t k = 0; k < n; ++k) {
                    result[i][j] += this->adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
            }
        }
        Graph res;
        res.loadGraph(result);

        return res;

    }


    //-------- Div ----------


    ariel::Graph Graph:: operator/=(const int c) {
        if(c == 0){
            throw std::invalid_argument("Can't divide by zero !");
            return *this;

        }
        size_t n = this-> adjacencyMatrix.size();
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                this->adjacencyMatrix[i][j] /= c;
            }
            
        }
        return *this;
    }




    // --------- output -----------

    std::ostream &operator<<(std::ostream &os, const Graph &graph) {
        size_t n = graph.getAdjacencyMatrix().size();
        if (n == 0) {
            os << "[]";
            return os;
        }

        for (size_t i = 0; i < n; i++) {
            os << "[";

            for (size_t j = 0; j < n - 1; j++) {
                os << graph.getAdjacencyMatrix()[i][j] << ", ";
            }
            os << graph.getAdjacencyMatrix()[i][n - 1] << "]\n";
        }

        return os;
    }

    // ------- Comparison ---------

    bool ariel::Graph::operator==(const ariel::Graph &other) const{
        size_t n = this-> adjacencyMatrix.size();
        if (n != other.adjacencyMatrix.size())
        {
            return false;
        }
         for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if(this->adjacencyMatrix[i][j] != other.adjacencyMatrix[i][j]){
                    return false;
                }
            }
            
        }
        return true;
    }

    bool ariel::Graph::operator>=(const ariel::Graph &other) const{

        if(*this == other){
            return true;
        }
        size_t n_this = this->adjacencyMatrix.size();
        size_t n_other = other.adjacencyMatrix.size();
        
        if (this->contains(other)) {
            return true;
        }

        if (this->numOfEdegs() != other.numOfEdegs()) {
            return this->numOfEdegs() >= other.numOfEdegs();
        }

        return other.adjacencyMatrix.size() > adjacencyMatrix.size();

    }

    bool ariel::Graph::operator<=(const ariel::Graph &other) const{

        if(*this == other){
            return true;
        }
        size_t n_this = this->adjacencyMatrix.size();
        size_t n_other = other.adjacencyMatrix.size();
        
        if (other.contains(*this)) {
            return true;
        }

        if (this->numOfEdegs() != other.numOfEdegs()) {
            return this->numOfEdegs() <= other.numOfEdegs();
        }

        return other.adjacencyMatrix.size() < adjacencyMatrix.size();
    }

    bool ariel::Graph::operator>(const ariel::Graph &other) const{
        if(!(*this <= other)){
            return true;
        }
        return false;
    }

    bool ariel::Graph::operator<(const ariel::Graph &other) const{
        if(!(*this >= other)){
            return true;
        }
        return false;
    }



    // ------- prefix ---------

    ariel::Graph& Graph :: operator++(){
        size_t n = this->getAdjacencyMatrix().size();
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if(this->adjacencyMatrix[i][j]!=0){
                    this->adjacencyMatrix[i][j] += 1;
                }
            }
            
        }
        return *this;
        
    }
    ariel::Graph& Graph :: operator--(){
        size_t n = this->getAdjacencyMatrix().size();
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if(this->adjacencyMatrix[i][j]!=0){
                    this->adjacencyMatrix[i][j] -= 1;
                }
            }
            
        }
        return *this;
        
    }

    
    // -------- postfix ---------

    ariel::Graph Graph :: operator++(int){
        Graph tmp = *this;
        size_t n = this->getAdjacencyMatrix().size();
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if(this->adjacencyMatrix[i][j]!=0){
                    this->adjacencyMatrix[i][j] += 1;
                }
            }
            
        }

        return tmp;
        
    }

    ariel::Graph Graph :: operator--(int){
        Graph tmp = *this;
        size_t n = this->getAdjacencyMatrix().size();
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if(this->adjacencyMatrix[i][j]!=0){
                    this->adjacencyMatrix[i][j] -= 1;
                }
            }
            
        }

        return tmp;
        
    }


    
}
    

