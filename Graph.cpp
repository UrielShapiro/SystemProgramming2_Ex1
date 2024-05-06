#include <iostream>
#include <vector>
#include <stdexcept>
#include "Graph.hpp"
using namespace ariel;

size_t Graph::size()
{
    return this->graph.size();
}
int Graph::get_edge(size_t i, size_t j)
{
    return this->graph.at(i).at(j);
}
std::vector<int> Graph::at(size_t i)
{
    return this->graph.at(i);
}
bool Graph::isDirectedGraph()
{
    return this->isDirected;
}

ariel::Graph::Graph()
{
    this->graph = std::vector<std::vector<int>>();
    this->isDirected = false;               // We asume that the graph is undirected untill proven otherwise.
}
void ariel::Graph::loadGraph(std::vector<std::vector<int>> g)
{
    if (g.size() == 0)
    {
        throw invalid_argument("Invalid graph: The graph is empty.");
    }
    if(g.size() != g.at(0).size())
    {
        throw invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
    this->graph.clear();
    std::vector<int> row;
    for (size_t i = 0; i < g.size(); i++)
    {
        for (size_t j = 0; j < g.size(); j++)
        {
            row.push_back(g.at(i).at(j));
        }
        if (row.at(i) != 0)
        {
            throw invalid_argument("Invalid graph: The distance from a vertex to itself must be 0.");
        }
        this->graph.push_back(row);
        row.clear();
    }

    for (size_t i = 1; i < g.size(); i++)
    {
        for (size_t j = 0; j < g.size(); j++)
        {
            if (g.at(i).at(j) != g.at(j).at(i))
            {
                this->isDirected = true;    // If the matrix is not symmetric, the graph is directed.
            }
        }
    }
}

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
