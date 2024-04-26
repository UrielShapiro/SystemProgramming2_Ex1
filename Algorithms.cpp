#include "Graph.hpp"
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <iostream>
#include <algorithm>
using namespace std;
using ariel::Graph;

class Algorithms
{
private:
    //     static void BFS(Graph graph, int startNode, vector<bool> &visited) // Simple implementation of BFS algorithm to find if a graph is connected.
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

    static bool relax(Graph g, size_t v, size_t u, vector<int> &distance)
    {
        if (distance[u] + g.get_edge(v, u) < distance[v])
        {
            distance[v] = distance[u] + g.get_edge(v, u);
            return true;
        }
        return false;
    }

    static vector<int> BellmanFord(Graph g, size_t start, size_t end)
    {
        vector<int> dist(g.size(), numeric_limits<int>::max()); // Initialize all distances to infinity.
        dist[start] = 0;                                        // The distance from the start node to itself is 0.

        for (size_t i = 0; i < g.size(); i++)
        {
            for (size_t j = 0; i < g.size(); i++)
            {
                if (g.get_edge(i, j) != 0)
                {
                    relax(g, i, j, dist);
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
                        cout << "Error: Graph contains a negative weight cycle." << endl;
                        return {};
                    }
                }
            }
        }
        return dist;
    }

    static bool DFS(Graph g, size_t v, vector<bool> &visited, vector<bool> &inStack)
    {
        visited[v] = true;
        inStack[v] = true;

        for (size_t i = 0; i < g.size(); i++)
        {
            if (g.get_edge(v, i) != 0)
            {
                if (!visited[i] && DFS(g, i, visited, inStack))
                {
                    return true;
                }
                else if (inStack[i])
                {
                    return true;
                }
            }
        }
        inStack[v] = false;
        return false;
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
    static bool colorGraph(Graph g, size_t v, vector<Color> &colors)
    {
        for (size_t i = 0; i < g.size(); i++)
        {
            if (g.get_edge(v, i) != 0)
            {
                if (colors[i] == UNCOLORED)
                {
                    colors[i] = colors[v] == RED ? BLUE : RED;
                    if (!colorGraph(g, i, colors))
                    {
                        return false;
                    }
                }
                else if (colors[i] == colors[v])
                {
                    return false;
                }
            }
        }
        return true;
    }

public:
    static int isConnected(Graph g)
    {
        if (g.size() == 0)
        {
            return false;                      // Empty graph is considered disconnected.
        }
        vector<bool> visited(g.size(), false); // Create a visited array for the graph nodes. initialized to false.
        vector<bool> inStack(g.size(), false); // Create a stack array for the graph nodes. initialized to false.

        DFS(g, 0, visited, inStack); // Perform BFS starting from the first node.

        auto iter = find(visited.begin(), visited.end(), false);
        if (iter != visited.end()) // The iterator found a false value in the visited array.
        {
            return false; // The graph is not connected.
        }
        return true; // The graph is connected if all nodes are visited
    }

    static string shortestPath(Graph g, size_t start, size_t end)
    {
        if (start == end)
        {
            return to_string(start); // If the start and end nodes are the same, the path is 0.
        }
        if (!isConnected(g))
        {
            return "-1";                               // If the graph is not connected, return -1.
        }
        vector<int> dist = BellmanFord(g, start, end); // Run Bellman-Ford algorithm to find the shortest path.
        if (dist.empty())
        {
            return "-1";              // If the graph contains a negative weight cycle, return -1.
        }
        string path = to_string(end); // Start building the path from the end node.
        size_t current = end;
        while (current != start) // Traverse the path from the end to the start (by ancestors).
        {
            for (size_t i = 0; i < g.size(); i++)
            {
                // Check if the current node is reachable and if we reached its ancestor in the shortest path.
                if (g.get_edge(i, current) != 0 && dist[i] + g.get_edge(i, current) == dist[current])
                {
                    path = to_string(i) + "->" + path;
                    current = i;
                    break; // Break the loop to avoid adding the same node multiple times.
                    // Will run the while loop again with the new current node, untill reaching the starting node.
                }
            }
        }
    }
    int isContainsCycle(Graph g)
    {
        vector<bool> visited(g.size(), false); // Create a visited array for the graph nodes. initialized to false.
        vector<bool> inStack(g.size(), false); // Create a stack array for the graph nodes. initialized to false.
        for (size_t i = 0; i < g.size(); i++)
        {
            if (!visited[i] && DFS(g, i, visited, inStack)) // Run DFS on all unvisited nodes.
            {
                return 1; // If a cycle is found, return true.
            }
        }
        return 0; // If no cycle is found, return false.
    }
    static string isBipartite(Graph g)
    {
        // Create a color array for the graph nodes. initialized all nodes to UNCOLORED.
        vector<Color> colors(g.size(), UNCOLORED);
        for (size_t i = 0; i < g.size(); i++)
        {
            if (colors[i] == UNCOLORED)
            {
                colors[i] = RED; // Color the first node with RED.
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
        A += "}";
        B += "}";
        return "The graph is bipartite: " + A + ", " + B;
    }

    static bool negativeCycle(Graph g);
};