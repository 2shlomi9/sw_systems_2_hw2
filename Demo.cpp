/*

Author : shlomi zecharia
ID : 315141242
Email : 2shlomiariel9@gmail.com

*/

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

using ariel::Algorithms;


int main()
{
    ariel::Graph g1;
    ariel::Graph g2;
    ariel::Graph g3;


    cout<< "\ngraph g1 :\n";
    vector<vector<int>> graph1 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    g1.loadGraph(graph1); 

    cout<< "\ngraph g2 :\n";

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g2.loadGraph(graph2); 

    
    cout<< "\ngraph g3 :\n";

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}};
    g3.loadGraph(graph3); 


// --------Before changes Graph g1-------

    cout<<"g1 : \n"<< g1 <<endl;
    cout<<"isConnected:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g1) << endl;        // Should print: "1" 
    cout<<"shortestPath(0,2):"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // Should print: 0->1->2
    cout<<"isContainsCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isContainsCycle(g1) << endl;    // Should print: "0"
    cout<<"isBipartite:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isBipartite(g1) << endl;        // Should print: "A={0, 2}, B={1}"
    cout<<"negativeCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::negativeCycle(g1) << endl;      // Should print: "0"

//  ---------- After Changes graph g1 ------------ 

    cout<<"g1++ : \n"<< g1++ <<endl;

    cout<<"++g1 : \n"<< ++g1 <<endl;

    cout<<"isConnected:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g1) << endl;        // Should print: "1" 
    cout<<"shortestPath(0,2):"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // Should print: 0->1->2
    cout<<"isContainsCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isContainsCycle(g1) << endl;    // Should print: "0"
    cout<<"isBipartite:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isBipartite(g1) << endl;        // Should print: "A={0, 2}, B={1}"
    cout<<"negativeCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::negativeCycle(g1) << endl;      // Should print: "0"

    cout<<"g1-- : \n"<< g1-- <<endl;


    cout<<"--g1 : \n"<< --g1 <<endl;



    g1 *= -2; 

    cout<<"g1 * (-2) : \n"<<g1<<endl; 
    
    cout<<"isConnected:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g1) << endl;        // Should print: "1" 
    cout<<"shortestPath(0,2):"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // Should print: 0->1->2
    cout<<"isContainsCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isContainsCycle(g1) << endl;    // Should print: "0"
    cout<<"isBipartite:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isBipartite(g1) << endl;        // Should print: "A={0, 2}, B={1}"
    cout<<"negativeCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::negativeCycle(g1) << endl;      // Should print: "0"

    
    g1 /= -2; 
    
    cout<<"g1 / (-2) :\n"<<g1<<endl; 

    cout<<"isConnected:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g1) << endl;        // Should print: "1" 
    cout<<"shortestPath(0,2):"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // Should print: 0->1->2
    cout<<"isContainsCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isContainsCycle(g1) << endl;    // Should print: "0"
    cout<<"isBipartite:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isBipartite(g1) << endl;        // Should print: "A={0, 2}, B={1}"
    cout<<"negativeCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::negativeCycle(g1) << endl;      // Should print: "0"

    cout<<"g1 + (unary) :\n" <<+g1<<endl; 
    

    cout<<"g1 - (unary) :\n" << -g1<<endl; 


// -------- Mul graphs g1 and g2 --------------

    ariel::Graph g_mul;
    g_mul = g1*g2;
    cout<<"g1 : \n"<<g1<<endl;
    cout<<"g2 : \n"<<g2<<endl;
    cout<<"g1*g2 : \n"<<g_mul<<endl;

    cout<<"isConnected:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g_mul) << endl;        // Should print: "1" 
    cout<<"shortestPath(0,2):"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::shortestPath(g_mul, 0, 2) << endl; // Should print: 0->1->2
    cout<<"isContainsCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isContainsCycle(g_mul) << endl;    // Should print: "0"
    cout<<"isBipartite:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isBipartite(g_mul) << endl;        // Should print: "A={0, 2}, B={1}"
    cout<<"negativeCycle:"<<endl;                              // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::negativeCycle(g_mul) << endl;      // Should print: "0"

// ----------- Comparison g1 , g2 , g3 -------------

    bool ans = (g1==g2);
    cout<<"g1 == g2 ? "<< ans <<endl;
    ans = (g1<g2);
    cout<<"g1 < g2 ? "<< ans <<endl;
    cout<<"\ng3 : \n"<<g3<<endl;
    ans = (g3<=g2);
    cout<<"g3 <= g2 ?"<<ans<<endl;

}
