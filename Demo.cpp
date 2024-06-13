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


    vector<vector<int>> graph1 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    g1.loadGraph(graph1); 


    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g2.loadGraph(graph2); 

    

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}};
    g3.loadGraph(graph3); 


// --------Before changes Graph g1-------

    cout<<"g1 : \n"<< g1 <<endl;

    cout<<"isConnected:"<<endl;                              
    cout << Algorithms::isConnected(g1) << endl;        // Should print: "0" 
    cout<<"shortestPath(0,2):"<<endl;                   
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // Should print: "0->1->2"
    cout<<"isContainsCycle:"<<endl;                              
    cout << Algorithms::isContainsCycle(g1) << endl;    // Should print: "The cycle is: 0 -> 1 -> 2 -> 0"
    cout<<"isBipartite:"<<endl;                             
    cout << Algorithms::isBipartite(g1) << endl;        // Should print: "The graph is not bipartite (adjacent vertices have the same color)"
    cout<<"negativeCycle:"<<endl;                          
    cout << Algorithms::negativeCycle(g1) << endl;      // Should print: "0"

//  ---------- After Changes graph g1 ------------ 

    cout<<"\ng1++ : \n"<< g1++ <<endl;

    cout<<"++g1 : \n"<< ++g1 <<endl;

    cout<<"isConnected:"<<endl;                              
    cout << Algorithms::isConnected(g1) << endl;        // Should print: "0" 
    cout<<"shortestPath(0,2):"<<endl;                              
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // Should print: "0->2"
    cout<<"isContainsCycle:"<<endl;                            
    cout << Algorithms::isContainsCycle(g1) << endl;    // Should print: "The cycle is: 0 -> 1 -> 2 -> 0"
    cout<<"isBipartite:"<<endl;                              
    cout << Algorithms::isBipartite(g1) << endl;        // Should print: "The graph is not bipartite (adjacent vertices have the same color)"
    cout<<"negativeCycle:"<<endl;                              
    cout << Algorithms::negativeCycle(g1) << endl;      // Should print: "0"

    cout<<"g1-- : \n"<< g1-- <<endl;


    cout<<"--g1 : \n"<< --g1 <<endl;



    g1 *= -2; 

    cout<<"g1 * (-2) : \n"<<g1<<endl; 
    
    cout<<"isConnected:"<<endl;                              
    cout << Algorithms::isConnected(g1) << endl;        // Should print: "0" 
    cout<<"shortestPath(0,2):"<<endl;                              
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // Should print: "Detect negative cycle, no shortest path"
    cout<<"isContainsCycle:"<<endl;                              
    cout << Algorithms::isContainsCycle(g1) << endl;    // Should print: "0 -> 1 -> 2 -> 0"
    cout<<"isBipartite:"<<endl;                              
    cout << Algorithms::isBipartite(g1) << endl;        // Should print: "The graph is not bipartite (adjacent vertices have the same color)"
    cout<<"negativeCycle:"<<endl;                              
    cout << Algorithms::negativeCycle(g1) << endl;      // Should print: "1"

    
    g1 /= -2; 
    
    cout<<"\ng1 / (-2) :\n"<<g1<<endl; 

    cout<<"isConnected:"<<endl;                              
    cout << Algorithms::isConnected(g1) << endl;        // Should print: "0" 
    cout<<"shortestPath(0,2):"<<endl;                              
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // Should print: 0->2
    cout<<"isContainsCycle:"<<endl;                              
    cout << Algorithms::isContainsCycle(g1) << endl;    // Should print: "0 -> 1 -> 2 -> 0"
    cout<<"isBipartite:"<<endl;                              
    cout << Algorithms::isBipartite(g1) << endl;        // Should print: "The graph is not bipartite (adjacent vertices have the same color)"
    cout<<"negativeCycle:"<<endl;                              
    cout << Algorithms::negativeCycle(g1) << endl;      // Should print: "0"

    cout<<"g1 + (unary) :\n" <<+g1<<endl; 
    

    cout<<"g1 - (unary) :\n" << -g1<<endl; 


// -------- Mul graphs g1 and g2 --------------

    ariel::Graph g_mul;
    g_mul = g1*g2;
    cout<<"g1 : \n"<<g1<<endl;
    cout<<"g2 : \n"<<g2<<endl;
    cout<<"g1*g2 : \n"<<g_mul<<endl;

    cout<<"isConnected:"<<endl;                              
    cout << Algorithms::isConnected(g_mul) << endl;        // Should print: "1" 
    cout<<"shortestPath(0,2):"<<endl;                              
    cout << Algorithms::shortestPath(g_mul, 0, 2) << endl; // Should print: "Detect negative cycle, no shortest path"
    cout<<"isContainsCycle:"<<endl;                              
    cout << Algorithms::isContainsCycle(g_mul) << endl;    // Should print: "The cycle is: 0 -> 0"
    cout<<"isBipartite:"<<endl;                             
    cout << Algorithms::isBipartite(g_mul) << endl;        // Should print: "The graph is not bipartite (adjacent vertices have the same color)"
    cout<<"negativeCycle:"<<endl;                              
    cout << Algorithms::negativeCycle(g_mul) << endl;      // Should print: "1"

// ----------- Comparison g1 , g2 , g3 -------------

    bool ans = (g1==g2);
    cout<<"g1 == g2 ? "<< ans <<endl;                      // Should print: "0"
    ans = (g1<g2);                                         
    cout<<"g1 < g2 ? "<< ans <<endl;                       // Should print: "1"
    cout<<"\ng3 : \n"<<g3<<endl;
    ans = (g3<=g2);                                        // Should print: "1"
    cout<<"g3 <= g2 ?"<<ans<<endl;


// ----------- Extreme cases -------------

    //Compare undirected graph with directed graph

    vector<vector<int>> graph4 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g1.loadGraph(graph4); 

    

    vector<vector<int>> graph5 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 1, 0, 0}};
    g2.loadGraph(graph5); 

    ans = (g1==g2);
    cout<<"\ng1 == g2 ? "<< ans <<endl;                    // Should print: "0"
    ans = (g1<g2);                                         
    cout<<"g1 < g2 ? "<< ans <<endl;                       // Should print: "1"

    //Compare by number of edges when, g1 size > g2 size

    vector<vector<int>> graph6 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g1.loadGraph(graph6); 
  

    vector<vector<int>> graph7 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0}};
    g2.loadGraph(graph7); 

    ans = (g1==g2);
    cout<<"\ng1 == g2 ? "<< ans <<endl;                    // Should print: "0"
    ans = (g1<g2);                                         
    cout<<"g1 < g2 ? "<< ans <<endl;                       // Should print: "0"



    //Compare by size of the matrix, when g1 number of edges = g2 number of edges

    vector<vector<int>> graph8 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 0},
        {0, 0, 0, 0, 0}};
    g1.loadGraph(graph8); 

    
    vector<vector<int>> graph9 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0}};
    g2.loadGraph(graph9); 

    ans = (g1==g2);
    cout<<"\ng1 == g2 ? "<< ans <<endl;                    // Should print: "0"
    ans = (g1<g2);                                         
    cout<<"g1 < g2 ? "<< ans <<endl;                       // Should print: "0"



    //Compare by edges weight, when g1 number of edges = g2 number of edges && g1 size == g2 size

    vector<vector<int>> graph10 = {
        {0, 3, 2, 0, 0},
        {3, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 7},
        {0, 0, 0, 7, 0}};
    g1.loadGraph(graph10); 

    
    vector<vector<int>> graph11 = {
        {0, 1, 2, 0, 0},
        {1, 0, 4, 0, 0},
        {2, 4, 0, 5, 0},
        {0, 0, 5, 0, 12},
        {0, 0, 0, 12, 0}};
    g2.loadGraph(graph11); 

    ans = (g1==g2);
    cout<<"\ng1 == g2 ? "<< ans <<endl;                    // Should print: "1"
    ans = (g1<=g2);                                         
    cout<<"g1 <= g2 ? "<< ans <<endl;                       // Should print: "1"
    ans = (g1>=g2);                                         
    cout<<"g1 >= g2 ? "<< ans <<endl;                       // Should print: "1"
    ans = (g1<g2);                                         
    cout<<"g1 < g2 ? "<< ans <<endl;                       // Should print: "0"
    ans = (g1>g2);                                         
    cout<<"g1 > g2 ? "<< ans <<endl;                       // Should print: "0"

    
}
