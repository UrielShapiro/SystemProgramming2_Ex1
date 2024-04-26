#include <iostream>
#include <vector>
#include <stdexcept>
#include "Graph.hpp"
using namespace std;
namespace ariel
{
    Graph::Graph()
    {
        this->graph = vector<vector<int>>();
    }
    void Graph::loadGraph(vector<vector<int>> graph)
    {
        if (graph.at(0).size() != graph.size())
        {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
        for (size_t i = 0; i < graph.size(); i++)
        {
            for (size_t j = 0; j < graph.size(); j++)
            {
                if (1 == j && graph.at(i).at(j) != 0)
                {
                    throw invalid_argument("Invalid graph: The distance from a vertex to itself must be 0.");
                }
                this->graph.at(i).push_back(graph.at(i).at(j));
            }
        }
    }

    void Graph::printGraph()
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

    size_t Graph::size()
    {
        return (size_t)this->graph.size();
    }
    int Graph::get_edge(size_t i, size_t j)
    {
        return this->graph.at(i).at(j);
    }
    vector<int> Graph::at(size_t i)
    {
        return this->graph.at(i);
    }
};
