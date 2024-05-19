# System Programming 2 Course Assignment 2
### For Computer Science B.Sc. Ariel University

**By Shlomi Zecharia**

## Description

This project is part of the System Programming 2 course assignment at Ariel University. The task involves expanding the Graph class to support various arithmetic and comparison operators, in addition to the graph algorithms implemented in the previous assignment.

### Files Included

* **Graph.hpp**: Header file containing the declaration of the Graph class and its member functions.

* **Algorithms.hpp**: Header file containing the declaration of the Algorithms class, which provides implementations of various graph algorithms.

* **Graph.cpp**: Source file containing the implementation of the Graph class member functions and the overloaded operators.

* **Algorithms.cpp**: Source file containing the implementation of the Algorithms class member functions.

## Explanation

### Arithmetic Operators

* **Addition**
  * `Graph operator+(const Graph& other)`: Adds the adjacency matrices of two graphs.
  * `Graph operator+=(const Graph& other)`: Adds another graph to the current graph.
  * `Graph operator+()`: Returns the current graph.

* **Subtraction**
  * `Graph operator-(const Graph& other)`: Subtracts the adjacency matrix of another graph from the current graph.
  * `Graph operator-=(const Graph& other)`: Subtracts another graph from the current graph.
  * `Graph operator-()`: Negates the adjacency matrix of the current graph.

* **Multiplication**
  * `Graph operator*=(const int c)`: Multiplies the adjacency matrix of the current graph by a scalar.
  * `Graph operator*(const Graph& other)`: Multiplies the adjacency matrices of two graphs.

* **Division**
  * `Graph operator/=(const int c)`: Divides the adjacency matrix of the current graph by a scalar.

### Comparison Operators

* `bool operator ==(const Graph &other) const`: Checks if two graphs are equal.
* `bool operator >=(const Graph &other) const`: Checks if the current graph is greater than or equal to another graph.
* `bool operator <=(const Graph &other) const`: Checks if the current graph is less than or equal to another graph.
* `bool operator >(const Graph &other) const`: Checks if the current graph is greater than another graph.
* `bool operator <(const Graph &other) const`: Checks if the current graph is less than another graph.

### Output Operator

* `friend std::ostream &operator <<(std::ostream &os, const Graph &graph)`: Outputs the adjacency matrix of a graph.

### Prefix and Postfix Operators

* **Prefix**
  * `Graph& operator++()`: Increments all non-zero elements of the adjacency matrix of the current graph.
  * `Graph& operator--()`: Decrements all non-zero elements of the adjacency matrix of the current graph.

* **Postfix**
  * `Graph operator++(int)`: Increments all non-zero elements of the adjacency matrix of the current graph, returning the original graph.
  * `Graph operator--(int)`: Decrements all non-zero elements of the adjacency matrix of the current graph, returning the original graph.

## Requirements

* Linux machine (Ubuntu 22.04.1 LTS preferable)
* GNU cpp (g++ Compiler)
* Make

## Building

```bash
# Cloning the repo to local machine.
git clone https://github.com/2shlomi9/sw_systems_2_hw1

# Install g++ compiler 
sudo apt-get install g++

# Building all the necessary files & the main programs.
make demo
make test
```
## Running:


##### Run Demo:
./demo

##### Run Tests:
./test

```
`