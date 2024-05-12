#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
using namespace std;
namespace ariel
{
    class Graph
    {
    private:
        std::vector<std::vector<int>> graph;
        bool isDirected;
        bool containsNegativeEdge;
    public:
        Graph();
        void loadGraph(std::vector<std::vector<int>> graph);
        void printGraph();
        size_t size() const;
        int get_edge(const size_t i, const size_t j) const;
        vector<int> at(const size_t i) const;
        bool isDirectedGraph() const;
        bool isContainsNegativeEdge() const;
        static Graph MakeUndirectedGraph(Graph g);
    };
};
#endif
