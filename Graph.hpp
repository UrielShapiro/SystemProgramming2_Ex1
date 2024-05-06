#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
using namespace std;
namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int>> graph;
        bool isDirected;
    public:
        Graph();
        void loadGraph(vector<vector<int>> graph);
        void printGraph();
        size_t size();
        int get_edge(size_t i, size_t j);
        vector<int> at(size_t i);
        bool isDirectedGraph();
    };
};
#endif
