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
        size_t size() const;
        int get_edge(const size_t i, const size_t j) const;
        vector<int> at(const size_t i) const;
        bool isDirectedGraph() const;
        bool isContainsNegativeEdge() const;

        /*
         * This function loads a graph from a given matrix.
         * The function checks if the matrix is empty.
         * The function checks if the matrix is a square matrix.
         * The function checks if the matrix is symmetric - if it is, the graph is undirected.
         * The function checks if the matrix contains negative edges.
         * The function checks if the distance from a vertex to itself isn't 0.
         */
        void loadGraph(std::vector<std::vector<int>> graph);

        /*
         * The function prints the graph as a matrix.
         * The function counts the number of edges in the graph.
         * The function prints the number of vertices and edges in the graph.
         */
        void printGraph();

        /*
         * This function creates an undirected graph from a directed graph.
         * The function creates a new graph with the same vertices as the original graph.
         * The function then copies the edges from the original graph to the new graph.
         * The function then copies the edges from the original graph to the new graph in reverse order.
         * The function then sets the new graph as undirected.
         * @returns the new undirected graph.
         */
        static Graph MakeUndirectedGraph(Graph g);
    };
};
#endif
