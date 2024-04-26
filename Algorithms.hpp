#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <string>
#include "Graph.hpp"
namespace ariel
{
    class Algorithms
    {
    public:
        static int isConnected(Graph g);
        static string shortestPath(Graph g, size_t start, size_t end);
        static int isContainsCycle(Graph g);
        static string isBipartite(Graph g);
        bool negativeCycle(Graph g);
        // static void BFS(Graph graph, int startNode, vector<bool> &visited);
        static bool relax(Graph g, size_t v, size_t u, vector<int> &distance);
        static vector<int> BellmanFord(Graph g, size_t start, size_t end);
        static bool DFS(Graph g, size_t v, vector<bool> &visited, vector<bool> &inStack);
        enum Color
        {
            UNCOLORED,
            RED,
            BLUE
        };
        static bool colorGraph(Graph g, size_t v, vector<Color> &colors);
    };
};
#endif