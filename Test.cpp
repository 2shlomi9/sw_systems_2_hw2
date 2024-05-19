#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using ariel::Graph;

using namespace std;

TEST_CASE("Test addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    g3+=g3;

    CHECK(g3.printGraph() == "[0, 4, 2]\n[4, 0, 6]\n[2, 6, 0]");

    +g3;
    CHECK(g3.printGraph() == "[0, 4, 2]\n[4, 0, 6]\n[2, 6, 0]");

}

TEST_CASE("Test subtraction"){

    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 - g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, -1},
        {0, 0, -1},
        {-1, -1, 0}};
    CHECK(g3.printGraph() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]");

    g3 -= g2;
    CHECK(g3.printGraph() == "[0, -1, -2]\n[-1, 0, -3]\n[-2, -3, 0]");

    -g3;
    CHECK(g3.printGraph() == "[0, 1, 2]\n[1, 0, 3]\n[2, 3, 0]");

}



TEST_CASE("Test multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
    g4*=2;
    CHECK(g4.printGraph() == "[2, 0, 4]\n[2, 6, 2]\n[2, 0, 4]");

}
TEST_CASE("Test Division"){

    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 4, 0},
        {4, 0, 4},
        {0, 4, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    g1/=2;
    CHECK(g1.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    g2/=2;
    CHECK(g2.printGraph() == "[0, 0, 0]\n[0, 0, 1]\n[0, 1, 0]");

}

TEST_CASE("Test Comparison"){
    

    ariel::Graph g1;

    vector<vector<int>> graph1 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    g1.loadGraph(graph1); 

    ariel::Graph g2;

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g2.loadGraph(graph2); 

    
    ariel::Graph g3;

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}};
    g3.loadGraph(graph3); 

    bool ans = (g1==g2);
    CHECK(ans ==  0);
    ans = (g1<g2);
    CHECK(ans ==  1);
    ans = (g3<=g2);
    CHECK(ans ==  1);
}

TEST_CASE("Test Prefix"){
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ++g1;
    CHECK(g1.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    --g1;
    CHECK(g1.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    
}
TEST_CASE("Test Postfix"){
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2 = g1++;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    g2 = g1 --;
    CHECK(g2.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    CHECK(g1.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");


    
}


TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g2.loadGraph(graph2);
    CHECK_THROWS(g2 * g1);

    // Addition of two graphs with different dimensions
    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g3.loadGraph(graph3);
    CHECK_THROWS(g1 + g3);


    ariel::Graph g;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(g.loadGraph(weightedGraph));

}
