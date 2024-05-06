#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <string>
#include "Graph.hpp"
namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(Graph g);
        static string shortestPath(Graph g, size_t start, size_t end);
        static bool isContainsCycle(Graph g);
        /*
            * A graph is Bipartite if it can be colored using two colors 
            * such that vertices in a set are colored with the same color.
            * @return The sets of vertices if the graph is bipartite, "0" otherwise.
        */
        static string isBipartite(Graph g);
        bool negativeCycle(Graph g);
        // static void BFS(Graph graph, int startNode, vector<bool> &visited);

        /*
         * This function relaxes the edge between two nodes in the graph.
         * If the distance from the source node to the current node is shorter than the current distance,
         * update the distance to the new shorter distance (in the distance vector).
         * @return true if the distance was updated, false otherwise.
         * @param g  the graph.
         * @param v  the current node.
         * @param u  the neighbor node.
         * @param distance  the distance vector.
         */
        static bool relax(Graph g, size_t v, size_t u, vector<int> &distance);


        /*
         * This function finds the shortest path between two nodes in the graph using the Bellman-Ford algorithm.
         * @return a vector representing the shortest path between the two nodes.
         * @param g  the graph.
         * @param src  the source node.
         */
        static bool BellmanFord(Graph g, size_t src, vector<int> &dist);
        static void DFS(Graph g, size_t current, size_t parent, std::vector<bool> &visited, std::vector<bool> &inStack, bool &cycle);
        enum Color
        {
            UNCOLORED,
            RED,
            BLUE
        };
        static bool colorGraph(Graph g, size_t current,size_t parent, vector<Color> &colors);
        static bool BFSColoring(Graph g, size_t start, std::vector<Color> &colors);
    };
};
#endif