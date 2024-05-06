#include "Graph.hpp"
#include <vector>
#include <string>
// #include <queue>
#include <climits>
#include <iostream>
#include <algorithm>
#include "Algorithms.hpp"
using ariel::Graph;

#define INFINITY INT_MAX
// #define DEBUG

namespace ariel
{
    //     void Algorithms::BFS(Graph graph, int startNode, vector<bool> &visited) // Simple implementation of BFS algorithm to find if a graph is connected.
    //     {
    //     queue<int> Q;
    //     Q.push(startNode);
    //     visited[startNode] = true;

    //     while (!Q.empty()) {
    //         int currentNode = Q.front();
    //         Q.pop();

    //         // Explore all unvisited neighbors of the current node
    //         for (int neighbor : graph.at(currentNode)) {
    //             if (!visited[neighbor] && graph.get_edge(currentNode, neighbor) != 0)
    //             {
    //                 visited[neighbor] = true;
    //                 Q.push(neighbor);
    //             }
    //         }
    //     }
    // }

    bool Algorithms::relax(Graph g, size_t v, size_t u, std::vector<int> &distance)
    {
        if (distance[u] + g.get_edge(u, v) < distance[v])
        {
            distance[v] = distance[u] + g.get_edge(v, u);
#ifdef DEBUG
            cout << "Relaxing edge: " << u << " -> " << v << endl;
            cout << "The distance from " << u << " to " << v << " is: " << distance[v] << endl;
#endif
            return true;
        }
        return false;
    }

    bool Algorithms::BellmanFord(Graph g, size_t src, std::vector<int> &dist)
    {
        dist[src] = 0; // The distance from the start node to itself is 0.

        for (size_t times = 0; times < g.size() - 1; times++)
        {
            for (size_t i = 0; i < g.size(); i++)
            {
                for (size_t j = 0; j < g.size(); j++)
                {
                    if (g.get_edge(i, j) != 0)
                    {
                        relax(g, j, i, dist);
                    }
                }
            }
        }

        // Check for negative weight cycles (The asignment).
        for (size_t i = 0; i < g.size(); i++)
        {
            for (size_t j = 0; i < g.size(); i++)
            {
                if (g.get_edge(i, j) != 0)
                {
                    if (relax(g, i, j, dist))
                    {
#ifdef DEBUG
                        cout << "Negative cycle found" << endl;
#endif
                        return true; // The graph contains a negative cycle.
                    }
                }
            }
        }
        return false;
    }

    void Algorithms::DFS(Graph g, size_t current, size_t parent, std::vector<bool> &visited,
                         std::vector<bool> &inStack, bool &cycle)
    {
        visited[current] = true;
        inStack[current] = true;

        for (size_t neighbor = 0; neighbor < g.at(current).size(); neighbor++)
        {
            if (!g.isDirectedGraph() && neighbor == parent) // Skip the parent node in undirected graphs.
            {
#ifdef DEBUG
                cout << "The graph is directed: " << g.isDirectedGraph() << endl;
                cout << "The neighbor is the parent: " << neighbor << " == " << parent << endl;
#endif
                continue;
            }
            if (neighbor == current)
            {
                continue;
            }
            if (inStack[neighbor] && g.get_edge(neighbor, current) != 0)
            {
#ifdef DEBUG
                cout << "The cycle is: " << current << "->" << neighbor << endl;
#endif
                cycle = true;
            }
            if (!visited[neighbor] && g.get_edge(neighbor, current) != 0)
            {
#ifdef DEBUG
                cout << "Running DFS from " << neighbor << ". His parent is: " << current << endl;
#endif

                DFS(g, neighbor, current, visited, inStack, cycle);
            }
        }
        inStack[current] = false;
    }

    enum Color
    {
        UNCOLORED,
        RED,
        BLUE
    };

    /*
     * This function colors the graph nodes with two colors (Red and Blue) in a way that no two
     * adjacent nodes have the same color.
     */
    bool Algorithms::colorGraph(Graph g, size_t current, std::vector<Color> &colors)
    {
        for (size_t i = 0; i < g.size(); i++)
        {
            if (g.get_edge(current, i) != 0)
            {
                if (colors[i] == UNCOLORED)
                {
                    colors[i] = colors[current] == RED ? BLUE : RED;
                    if (!colorGraph(g, i, colors))
                    {
                        return false;
                    }
                }
                else if (colors[i] == colors[current])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool Algorithms::isConnected(Graph g)
    {
        if (g.size() == 0)
        {
#ifdef DEBUG
            cout << "Empty graph is considered not connected" << endl;
#endif
            return false;
        }

        std::vector<bool> visited(g.size(), false); // Create a visited array for the graph nodes. initialized to false.
        std::vector<bool> inStack(g.size(), false); // Create a stack array for the graph nodes. initialized to false.

        bool doenstMatter = false;                           // This variable will have the a boolean value that we don't care about (if the graph has a cycle).
        DFS(g, 0, INFINITY, visited, inStack, doenstMatter); // Perform DFS starting from the first node.

        auto iter = find(visited.begin(), visited.end(), false);
        if (iter != visited.end()) // The iterator found a false value in the visited array.
        {
            return false; // The graph is not connected.
        }
        return true; // The graph is connected if all nodes are visited
    }

    string Algorithms::shortestPath(Graph g, size_t start, size_t end)
    {
        if (start == end)
        {
            return "0"; // If the start and end nodes are the same, the path is 0.
        }

        std::vector<bool> visited(g.size(), false);
        std::vector<bool> inStack(g.size(), false);
        bool doenstMatter = false;
        DFS(g, start, INFINITY, visited, inStack, doenstMatter); // Check if start is connected to end.
        if(!visited[end])
        {
            return "-1"; // If the start node is not connected to the end node, return -1.
        }

        std::vector<int> dist(g.size(), INFINITY);         // Initialize all distances to infinity.
        bool negative_cycle = BellmanFord(g, start, dist); // Run Bellman-Ford algorithm to find the shortest path.

#ifdef DEBUG
        for (size_t i = 0; i < dist.size() ; i++)
        {
            cout << "Shotest path for vertex: " << i << " is: " << dist.at(i) << endl;
        }
#endif

        if (negative_cycle)
        {
            return "-1"; // If the graph contains a negative weight cycle, return -1.
        }
#ifdef DEBUG
        cout << "There is no negative cycle" << endl;
#endif
        string path = to_string(end); // Start building the path from the end node.
        size_t current = end;
        size_t runs = 25; // Maximum number of runs to avoid infinite loops.
        while (current != start && runs > 0) // Build the path from the end node to the start node (backwards
        {
            runs--;
#ifdef DEBUG
            cout << "Current node: " << current << endl;
            cout << "The path is: " << path << endl;
#endif
            bool breakLoop = false;
            for (size_t i = 0; i < g.size() && !breakLoop; i++)
            {
#ifdef DEBUG
                cout << "Checking node: " << i << endl;
#endif
                //  Check if the current node is reachable and if we reached its ancestor in the shortest path.
                if (g.get_edge(i, current) != 0 && dist[i] + g.get_edge(i, current) == dist[current])
                {
                    path = to_string(i) + "->" + path;
                    current = i;
                    breakLoop = true;
#ifdef DEBUG
                    cout << "Entered the if statement" << endl;
#endif
                    break; // Break the loop to avoid adding the same node multiple times.
                    // Will run the while loop again with the new current node, until reaching the starting node.
                }
                if (g.get_edge(i, current) != 0)
                {
#ifdef DEBUG
                    cout << "The edge from " << i << " to " << current << " is: " << g.get_edge(i, current) << endl;
                    cout << "The distance from " << i << " to " << current << " is: " << dist[i] << endl;
                    cout << "The distance from " << i << " to " << current << " + the edge is: " << dist[i] + g.get_edge(i, current) << endl;
                    cout << "The distance from " << start << " to " << current << " is: " << dist[current] << endl;
#endif
                }
            }
        }

        return path;
    }

    bool Algorithms::isContainsCycle(Graph g)
    {
        std::vector<bool> visited(g.size(), false); // Create a visited array for the graph nodes. initialized to false.
        std::vector<bool> inStack(g.size(), false); // Create a stack vector for the graph nodes. initialized to false.
        bool cycle = false;
        for (size_t i = 0; i < g.size(); i++)
        {
            if (visited[i])
                continue;

            DFS(g, i, INFINITY, visited, inStack, cycle);
        }
        return cycle;
    }

    string Algorithms::isBipartite(Graph g)
    {
        // Create a color array for the graph nodes. initialized all nodes to UNCOLORED.
        std::vector<Color> colors(g.size(), UNCOLORED);
        for (size_t i = 0; i < g.size(); i++)
        {
            if (colors[i] == UNCOLORED)
            {
                colors[i] = RED; // Color the first node in the connection component with RED.
                if (!colorGraph(g, i, colors))
                {
                    return "0"; // If the graph is not bipartite, return false.
                }
            }
        }
        string A = "A={";
        string B = "B={";
        for (size_t i = 0; i < g.size(); i++)
        {
            if (colors[i] == RED)
            {
                A += to_string(i) + ", ";
            }
            else
            {
                B += to_string(i) + ", ";
            }
        }
        // Remove the last comma and space in both strings:
        A = A.substr(0, A.size() - 2);
        B = B.substr(0, B.size() - 2);
        A += "}";
        B += "}";
        return "The graph is bipartite: " + A + ", " + B;
    }

    bool Algorithms::negativeCycle(Graph g)
    {
        if (!isContainsCycle(g))
        {
            return false;
        }
        // If the Bellman-Ford algorithm returns an empty vector, the graph contains a negative cycle.

        std::vector<int> distance(g.size(), INFINITY);
        bool negative_cycle = BellmanFord(g, 0, distance);
        return negative_cycle;
        // Bellman-Ford function returns a vector by value and not by reference.
        // Therefore, we will copy it using the copy constructor of the vector class.
        // Then check if the copied vector is empty or not.
    }
};