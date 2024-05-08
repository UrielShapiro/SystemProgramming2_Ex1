#include "Graph.hpp"
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <iostream>
#include <algorithm>
#include "Algorithms.hpp"
using ariel::Graph;

#define INFINITY INT_MAX
// #define DEBUG
//   #define DELETE

namespace ariel
{
#ifdef DELETE
    void Algorithms::BFS(Graph graph, int startNode, vector<bool> &visited) // Simple implementation of BFS algorithm to find if a graph is connected.
    {
        queue<int> Q;
        Q.push(startNode);
        visited[startNode] = true;

        while (!Q.empty())
        {
            int currentNode = Q.front();
            Q.pop();

            // Explore all unvisited neighbors of the current node
            for (int neighbor : graph.at(currentNode))
            {
                if (!visited[neighbor] && graph.get_edge(currentNode, neighbor) != 0)
                {
                    visited[neighbor] = true;
                    Q.push(neighbor);
                }
            }
        }
    }
#endif

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
                         std::vector<bool> &inStack)
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
            }
            if (!visited[neighbor] && g.get_edge(neighbor, current) != 0)
            {
#ifdef DEBUG
                cout << "Running DFS from " << neighbor << ". His parent is: " << current << endl;
#endif

                DFS(g, neighbor, current, visited, inStack);
            }
        }
        inStack[current] = false;
    }

    enum Visited
    {
        WHITE,
        GREY,
        BLACK
    };

    size_t DFSCycleCheck(Graph g, size_t current, size_t parent, std::vector<Visited> &visited,
                         std::vector<size_t> &parents, std::vector<size_t> &cycleNodes)
    {

#ifdef DEBUG
        cout << "Running DFSCycleCheck with: " << current << endl;
#endif
        visited[current] = GREY;
        parents[current] = parent;
        cycleNodes.push_back(current);
#ifdef DEBUG
        if (visited[current] == GREY)
            cout << "Grey" << endl;
#endif
        for (size_t neighbor = 0; neighbor < g.at(current).size(); neighbor++)
        {
            if (!g.isDirectedGraph() && neighbor == parent) // Skip the parent node in undirected graphs.
            {
                continue;
            }
            if (visited[neighbor] == GREY && g.get_edge(neighbor, current) != 0)
            {
#ifdef DEBUG
                cout << "The cycle is: " << current << "->" << neighbor << endl;
#endif
                parents[neighbor] = current;
#ifdef DEBUG
                cout << "The parent of " << neighbor << " is: " << parents[neighbor] << endl;
#endif
                cycleNodes.push_back(neighbor);
                return current;
            }
            else if (visited[neighbor] == WHITE && g.get_edge(neighbor, current) != 0)
            {
#ifdef DEBUG
                cout << "Running DFS from " << neighbor << ". His parent is: " << current << endl;
#endif
                parents[neighbor] = current;

#ifdef DEBUG
                cout << "The parent of " << neighbor << " is: " << parents[neighbor] << endl;
#endif

                if (DFSCycleCheck(g, neighbor, current, visited, parents, cycleNodes) != INFINITY)
                {
                    return current;
                }
            }
        }
        visited[current] = BLACK;
        cycleNodes.pop_back();
        return INFINITY;
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
#ifdef DELETE
    bool Algorithms::colorGraph(Graph g, size_t current, size_t parent, std::vector<Color> &colors)
    {
        for (size_t i = 0; i < g.size(); i++)
        {
            if (!g.isDirectedGraph() && i == parent || i == current)
            {
                continue;
            }
            if (g.get_edge(current, i) != 0)
            {
#ifdef DEBUG
                cout << "Checking edge: " << current << " -> " << i << endl;
#endif
                if (colors[i] == UNCOLORED)
                {
                    colors[i] = colors[current] == RED ? BLUE : RED;
#ifdef DEBUG
                    cout << "Coloring node: " << i << " with: " << colors[i] << endl;
#endif
                    if (!colorGraph(g, i, current, colors))
                    {
#ifdef DEBUG
                        cout << "vertex " << i << " failed" << endl;
#endif
                        return false;
                    }
                }
                else if (colors[i] == colors[current])
                {
#ifdef DEBUG
                    cout << "vertex " << i << " color is the same as vertex: " << current << endl;
#endif
                    return false;
                }
            }
        }
        return true;
    }
#endif

    bool Algorithms::BFSColoring(Graph g, size_t start, std::vector<Color> &colors)
    {
        std::queue<size_t> Q;
        Q.push(start);
        colors[start] = RED;

        while (!Q.empty())
        {
            size_t current = Q.front();
            Q.pop();

            for (size_t i = 0; i < g.size(); i++)
            {
#ifdef DEBUG
                cout << "Checking edge: " << current << " -> " << i << endl;
#endif
                if (g.get_edge(current, i) != 0 && colors[i] == UNCOLORED)
                {
                    Q.push(i);
                    colors[i] = colors[current] == RED ? BLUE : RED;
#ifdef DEBUG
                    cout << "Coloring node: " << i << " with: " << colors[i] << endl;
#endif
                }
                if (i != current && g.get_edge(current, i) != 0 && colors[i] == colors[current])
                {
#ifdef DEBUG
                    cout << "vertex " << i << " color is the same as vertex: " << current << endl;
#endif
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

        std::vector<bool> visited(g.size(), false);          // Create a visited array for the graph nodes. initialized to false.
        std::vector<bool> inStack(g.size(), false);          // Create a stack array for the graph nodes. initialized to false.
        DFS(g, 0, INFINITY, visited, inStack); // Perform DFS starting from the first node.

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
        DFS(g, start, INFINITY, visited, inStack); // Check if start is connected to end.
        if (!visited[end])
        {
            return "-1"; // If the start node is not connected to the end node, return -1.
        }

        std::vector<int> dist(g.size(), INFINITY);         // Initialize all distances to infinity.
        bool negative_cycle = BellmanFord(g, start, dist); // Run Bellman-Ford algorithm to find the shortest path.

#ifdef DEBUG
        for (size_t i = 0; i < dist.size(); i++)
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
        while (current != start) // Build the path from the end node to the start node (backwards
        {
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

    string printPath(size_t src, size_t parent, std::vector<size_t> parents)
    {
        if (parent == src)
        {
            return to_string(src);
        }
        else if (parent == INFINITY)
        {
            return "No path";
        }
        return printPath(src, parents[parent], parents) + "->" + to_string(parent);
    }

    string Algorithms::isContainsCycle(Graph g)
    {
        std::vector<Visited> visited(g.size(), WHITE);   // Create a visited array for the graph nodes. initialized to false.
        std::vector<size_t> parents(g.size(), INFINITY); // Create a stack vector for the graph nodes. initialized to false.
        size_t cycle_node;
        for (size_t i = 0; auto iter = find(visited.begin(), visited.end(), WHITE) != visited.end(); i++)
        {
            if (visited[i] != WHITE)
            {
#ifdef DEBUG
                cout << "The node is already visited: " << i << endl;
#endif
                continue;
            }

#ifdef DEBUG
            cout << "Running DFS from: " << i << endl;
            for (Visited v : visited)
            {
                if (v == WHITE)
                {
                    cout << "White ";
                }
                else if (v == GREY)
                {
                    cout << "Grey ";
                }
                else
                {
                    cout << "Black ";
                }
            }
            cout << endl;
#endif
            std::vector<size_t> cycleNodes;
            cycle_node = DFSCycleCheck(g, i, INFINITY, visited, parents, cycleNodes);
#ifdef DEBUG
            cout << "The cycle node is: " << cycle_node << endl;
            cout << endl;
            cout << "The cycle nodes are: ";
            for (auto a : cycleNodes)
            {
                cout << a << " ";
            }
            cout << endl;
#endif
            if (cycle_node != INFINITY)
            {
#ifdef DEBUG
                for (auto a : parents)
                {
                    cout << a << " ";
                }
                cout << endl;
#endif
                string path = "The cycle is: ";
                //                 size_t current = parents[cycle_node];
                //                 while (current != cycle_node && current < parents.size())
                //                 {
                // #ifdef DEBUG
                //                     cout << "The current node is: " << current << endl;
                //                     cout << "The parent of the current node is: " << parents[current] << endl;
                //                     cout << "Graph size: " << g.size() << endl;
                // #endif
                //                     path += to_string(current) + "->";
                //                     current = parents[current];
                // #ifdef DEBUG
                //                     cout << "The path is: " << path << endl;
                //                     cout << "The current node is: " << current << endl;
                // #endif
                //                 }
                path += printPath(cycle_node, parents[cycle_node], parents);
                path += "->" + to_string(cycle_node);
#ifdef DEBUG
                cout << path << endl;
#endif
                return path;
            }
        }
        return "0"; // If the graph does not contain a cycle, return false.
    }

    string Algorithms::isBipartite(Graph g)
    {
        // Create a color array for the graph nodes. initialized all nodes to UNCOLORED.
        std::vector<Color> colors(g.size(), UNCOLORED);
        for (size_t i = 0; i < g.size(); i++)
        {
            if (colors[i] == UNCOLORED)
            {
                if (!BFSColoring(g, i, colors))
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
        // TODO: ADD AN OPTION TO RETURN THE CYCLE
        if (isContainsCycle(g) == "0")
        {
            return false;
        }
        // If the Bellman-Ford algorithm returns an empty vector, the graph contains a negative cycle.

        std::vector<int> distance(g.size(), INFINITY);
        return BellmanFord(g, 0, distance);
        // Bellman-Ford function returns a vector by value and not by reference.
        // Therefore, we will copy it using the copy constructor of the vector class.
        // Then check if the copied vector is empty or not.
    }
};