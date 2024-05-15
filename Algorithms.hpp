/**
 * Last digits of ID: 9745
 * Mail: uriel1999@gmail.com
*/

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <string>
#include "Graph.hpp"
namespace ariel
{
    class Algorithms
    {
    private:
        enum Color
        {
            UNCOLORED,
            RED,
            BLUE
        };
        enum Visited
        {
            WHITE,
            GREY,
            BLACK
        };

        /*
         * A function that finds the neighbor with the minimum distance from the source.
         * @return The index of the neighbor with the minimum distance from the source.
         */
        static size_t min_neighbor(const std::vector<int> &dist, const std::vector<bool> &converged);

        /*
         * A function that checks if a vertex should be relaxed or not.
         * @return True if the vertex should be relaxed, False otherwise.
         */
        static bool should_relax(size_t u, size_t v, int weight, std::vector<int> dist);

        /*
         * Function that implements Dijkstra's single source shortest path algorithm
         * for a graph represented using adjacency matrix
         * @return A vector that stores the shortest distance from the source to each vertex in the graph.
         */
        static void dijkstra(Graph g, size_t src, size_t end, std::vector<int> &dist, std::vector<size_t> &parents);

        /*
         * This function relaxes the edge between two nodes in the graph.
         * If the distance from the source node to the current node is shorter than the current distance,
         * the function will update the distance to the new shorter distance (in the distance vector).
         * @return true if the distance was updated, false otherwise.
         */
        static bool relax(Graph g, size_t v, size_t u, std::vector<int> &distance, std::vector<size_t> &parents);

        /*
         * This function implements the Bellman-Ford algorithm to find the shortest path in a graph.
         * @return True if the graph contains a negative cycle, False otherwise.
         */
        static bool BellmanFord(Graph g, size_t src, std::vector<int> &dist, std::vector<size_t> &parents, std::vector<size_t> &cycleNodes);

        /*
         * This function performs a Depth First Search (DFS) on the graph to check connactivity.
         * This function is used to check if the graph is strongly connected (1 SCC).
         */
        static void DFS(Graph g, size_t current, size_t parent, std::vector<bool> &visited, std::vector<bool> &inStack);

        /*
         * This function colors the graph using the Breadth First Search (BFS) algorithm.
         * The function colors the graph in two colors (RED and BLUE) and checks if the graph is bipartite.
         * Theorom: A graph is bipartite if and only if it is 2-colorable.
         * @return True if the graph is bipartite, False otherwise.
         */
        static bool BFSColoring(Graph g, size_t start, std::vector<Color> &colors);

        /*
         * This function performs a Depth First Search (DFS) on the graph.
         * It is used to check if the graph contains a cycle.
         * @return The node in which the cycle starts.
         */
        static size_t DFSCycleCheck(Graph g, size_t current, size_t parent, std::vector<Visited> &visited,
                                    std::vector<size_t> &parents, std::vector<size_t> &cycleNodes);

        /*
         * This function prints the path from the source node to the end node.
         * @return The path from the source node to the end node.
         */
        static std::string printPath(size_t src, size_t parent, std::vector<size_t> parents);

    public:
        /*
         * This function checks if the graph is connected.
         * In order to check if the graph is connected and not just strongly connected, the function creates a new undirected graph.
         * And run a Depth First Search (DFS) algorithm on that graph.
         * @return True if the graph is strongly connected, False otherwise.
         */
        static bool isConnected(Graph g);

        /*
         * This function finds the shortest path between two nodes in the graph.
         * If the graph has no negative edges, The function uses Dijkstra's algorithm to find the shortest path.
         * Else, the function uses the Bellman-Ford algorithm to find the shortest path.
         * @return The shortest path between the start and end nodes. if there is no path, the function returns -1.
         */
        static std::string shortestPath(Graph g, size_t start, size_t end);

        /*
         * This function checks if the graph contains a cycle.
         * The function uses Depth First Search (DFS) to check if the graph contains a cycle.
         * @return The cycle in the graph if it contains a cycle, "0" otherwise.
         */
        static std::string isContainsCycle(Graph g);

        /*
         * This function checks if the graph is bipartite.
         * The function uses Breadth First Search (BFS) to color the graph in two colors (RED and BLUE).
         * Theorom: A graph is bipartite if and only if it is 2-colorable.
         * @return The sets of vertices if the graph is bipartite, "0" otherwise.
         */
        static std::string isBipartite(Graph g);

        /*
         * This function checks if the graph contains a negative cycle.
         * The function won't work on directed graphs that contain a negative cycle.
         * The function uses the Bellman-Ford algorithm to check if the graph contains a negative cycle.
         * @return The cycle in the graph if it contains a negative cycle, "0" otherwise.
         */
        static std::string negativeCycle(Graph g);
    };
};
#endif