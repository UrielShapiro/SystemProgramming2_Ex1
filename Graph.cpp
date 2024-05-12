#include <iostream>
#include <vector>
#include <stdexcept>    // invalid_argument

#include "Graph.hpp"
using namespace ariel;

size_t Graph::size() const
{
    return this->graph.size();
}
int Graph::get_edge(const size_t i, const size_t j) const
{
    return this->graph.at(i).at(j);
}
std::vector<int> Graph::at(const size_t i) const
{
    return this->graph.at(i);
}
bool Graph::isDirectedGraph() const
{
    return this->isDirected;
}
bool Graph::isContainsNegativeEdge() const
{
    return this->containsNegativeEdge;
}

ariel::Graph::Graph()
{
    this->graph = std::vector<std::vector<int>>(); // Initialize the graph as an empty integer matrix.
    this->isDirected = false;                      // We asume that the graph is undirected untill proven otherwise.
    this->containsNegativeEdge = false;            // We asume that the graph does not contain negative edges untill proven otherwise.
}

/*
    * This function creates an undirected graph from a directed graph.
    * The function creates a new graph with the same vertices as the original graph.
    * The function then copies the edges from the original graph to the new graph.
    * The function then copies the edges from the original graph to the new graph in reverse order.
    * The function then sets the new graph as undirected.
    * The function returns the new undirected graph.
*/
Graph ariel::Graph::MakeUndirectedGraph(Graph g)
{
    Graph undirectedGraph;
    std::vector<std::vector<int>> newGraph(g.graph);
    undirectedGraph.loadGraph(newGraph);    // Load the original graph to the new graph.
    for (size_t i = 0; i < g.size(); i++)
    {
        for (size_t j = 0; j < g.size(); j++)
        {
            if (g.graph.at(i).at(j) != 0)
            {
                undirectedGraph.graph.at(j).at(i) = g.graph.at(i).at(j);    // Copy g[i][j] to undirectedGraph[j][i].
            }
        }
    }
    undirectedGraph.isDirected = false;   // Set the new graph as undirected.
    return undirectedGraph;
}

/*
    * This function loads a graph from a given matrix.
    * The function checks if the matrix is empty.
    * The function checks if the matrix is a square matrix.
    * The function checks if the matrix is symmetric - if it is, the graph is undirected.
    * The function checks if the matrix contains negative edges.
    * The function checks if the distance from a vertex to itself isn't 0.
*/
void ariel::Graph::loadGraph(std::vector<std::vector<int>> g)
{
    if (g.size() == 0)
    {
        throw invalid_argument("Invalid graph: The graph is empty.");
    }
    if (g.size() != g.at(0).size()) // Check if the matrix is a square matrix.
    {
        throw invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
    this->graph.clear();    // Clear the graph, if it was already initialized.
    std::vector<int> row;
    for (size_t i = 0; i < g.size(); i++)
    {
        for (size_t j = 0; j < g.size(); j++)
        {
            row.push_back(g.at(i).at(j));   // Copy the row from the matrix to the graph.
            if (g.at(i).at(j) != g.at(j).at(i))
            {
                this->isDirected = true; // If the matrix is not symmetric, the graph is directed.
            }
            if (g.at(i).at(j) < 0)  // If the matrix contains negative edge, we will mark this graph as containing negative edges.
            {
                this->containsNegativeEdge = true;
            }
        }
        if (row.at(i) != 0) // Check if the distance from a vertex to itself isn't 0.
        {
            throw invalid_argument("Invalid graph: The distance from a vertex to itself must be 0.");
        }
        this->graph.push_back(row);
        row.clear();    // Clear the row, for the next iteration.
    }
}

/*
    * The function prints the graph as a matrix.
    * The function counts the number of edges in the graph.
    * The function prints the number of vertices and edges in the graph.
*/
void ariel::Graph::printGraph()
{
    int edges = 0;
    for (size_t i = 0; i < this->graph.size(); i++)
    {
        for (size_t j = 0; j < this->graph.size(); j++)
        {
            cout << this->graph.at(i).at(j) << "\t";
            if (this->graph.at(i).at(j) != 0)
            {
                edges++;
            }
        }
        cout << endl;
    }
    cout << "Graph with " << this->graph.size() << " vertices and " << edges << " edges." << endl;
}
