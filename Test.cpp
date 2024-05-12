#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <vector>

using namespace std;

TEST_CASE("Test isConnected - Connected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph3 = {
        {0, 0, -27, -9, 0},
        {0, 0, 0, 6, 0},
        {-27, 0, 0, 0, -29},
        {-9, 6, 0, 0, -22},
        {0, 0, -29, -22, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph4 = {
        {0, -50, 0, 0, -43, 14, 0, -39, -38, 0, 37, 8, 27, 23, 26, 49, -44},
        {-50, 0, -48, 0, 0, 0, -27, 0, 44, -6, 0, -39, -44, 43, 0, -5, -16},
        {0, -48, 0, -8, -50, 0, 0, 11, 19, 37, 32, 0, 0, 0, 0, 35, -23},
        {0, 0, -8, 0, 0, -9, 11, 20, 33, 43, -37, 0, 0, -1, 0, 0, -19},
        {-43, 0, -50, 0, 0, 13, 0, -23, -24, -35, -27, 0, 0, 44, 0, 0, -17},
        {14, 0, 0, -9, 13, 0, -34, 0, 0, 0, -42, 0, -23, 0, -39, 0, -1},
        {0, -27, 0, 11, 0, -34, 0, 0, 0, 0, 24, 0, -24, 0, -29, 0, 0},
        {-39, 0, 11, 20, -23, 0, 0, 0, 20, 0, 0, 18, 27, 39, 38, 0, 0},
        {-38, 44, 19, 33, -24, 0, 0, 20, 0, -19, 0, 0, 0, 14, 0, 16, -14},
        {0, -6, 37, 43, -35, 0, 0, 0, -19, 0, -26, -10, 0, 0, 0, 0, -23},
        {37, 0, 32, -37, -27, -42, 24, 0, 0, -26, 0, -13, 0, 0, 0, -38, 18},
        {8, -39, 0, 0, 0, 0, 0, 18, 0, -10, -13, 0, -18, 0, 0, 0, 0},
        {27, -44, 0, 0, 0, -23, -24, 27, 0, 0, 0, -18, 0, -48, 39, 10, 0},
        {23, 43, 0, -1, 44, 0, 0, 39, 14, 0, 0, 0, -48, 0, 0, -37, -25},
        {26, 0, 0, 0, 0, -39, -29, 38, 0, 0, 0, 0, 39, 0, 0, 12, 25},
        {49, -5, 35, 0, 0, 0, 0, 0, 16, 0, -38, 0, 10, -37, 12, 0, -31},
        {-44, -16, -23, -19, -17, -1, 0, 0, -14, -23, 18, 0, 0, -25, 25, -31, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph5 = {
        {0, 46, -47, 2},
        {46, 0, 21, -18},
        {-47, 21, 0, 0},
        {2, -18, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("isConnected - Not Connected")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph3 = {
        {0, 0, -39, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {-39, 0, 0, 46, 0, 0},
        {0, 0, 46, 0, 22, 0},
        {0, 0, 0, 22, 0, -23},
        {0, 0, 0, 0, -23, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph4 = {
        {0, 0, 19, 0, 0},
        {0, 0, 0, -22, -50},
        {19, 0, 0, 0, 0},
        {0, -22, 0, 0, 0},
        {0, -50, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph5 = {
        {0, 9, 0, 28, -32, -15, 13, 0, 27, 0, -49, -3, 0},
        {9, 0, 0, -9, 11, 0, 41, 0, 0, -46, 0, 9, 0},
        {0, 0, 0, -36, 47, 0, 18, 0, 7, 0, -36, 25, 0},
        {28, -9, -36, 0, 0, 0, 0, 0, 0, 0, 21, -1, 0},
        {-32, 11, 47, 0, 0, -42, 0, -27, -46, 2, -12, 16, 0},
        {-15, 0, 0, 0, -42, 0, -9, 0, 36, 15, -19, 16, 0},
        {13, 41, 18, 0, 0, -9, 0, 44, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, -27, 0, 44, 0, -12, -4, 0, 18, 0},
        {27, 0, 7, 0, -46, 36, 0, -12, 0, 0, 0, 0, 0},
        {0, -46, 0, 0, 2, 15, 0, -4, 0, 0, -27, 42, 0},
        {-49, 0, -36, 21, -12, -19, 0, 0, 0, -27, 0, 23, 0},
        {-3, 9, 25, -1, 16, 16, 0, 18, 0, 42, 23, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath - Positive edges")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->2->3->4");

    vector<vector<int>> graph4 = {
        {0, 43, 0, 35},
        {0, 0, 40, 0},
        {0, 0, 0, 31},
        {0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
}

TEST_CASE("Test shortestPath - Negative edges")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {0, 0, -1},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph1 = {
        {0, 37, -9, 11},
        {0, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 0, 0, 0}};

    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");

    vector<vector<int>> graph2 = {
        {0, 43, 0, 35},
        {0, 0, -40, 0},
        {0, 0, 0, 31},
        {0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
}

TEST_CASE("Test isContainsCycle - Not contained")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 0, 0, 0, -5},
        {0, 0, 0, 3, 0},
        {0, 0, 0, 20, 0},
        {0, 0, 0, 0, 0},
        {0, -10, 10, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph2 = {
        {0, 0, -10, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 3},
        {0, 3, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");
}

TEST_CASE("Test isContainsCycle - contained")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 33, 0, 20},
        {33, 0, 42, 30},
        {0, 42, 0, 0},
        {20, 30, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->3->0");

    vector<vector<int>> graph1 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graph2 = {
        {0, 41, 0, 37, 17, 10, 0},
        {41, 0, -3, 31, -1, 0, 25},
        {0, -3, 0, 0, 0, 16, -4},
        {37, 31, 0, 0, 42, 44, -3},
        {17, -1, 0, 42, 0, 0, 0},
        {10, 0, 16, 44, 0, 0, -3},
        {0, 25, -4, -3, 0, -3, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->5->0");
}

TEST_CASE("Test isBipartite - is bipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph1 = {
        {0, 12, 0, 4, 0},
        {12, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {4, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");

    vector<vector<int>> graph2 = {
        {0, -1, 0, 0, 0, 0, 0},
        {-1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 22, 0, 0, 0},
        {0, 0, 22, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 48, 20},
        {0, 0, 0, 3, 48, 0, 0},
        {0, 0, 0, 0, 20, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 5, 6}, B={1, 3, 4}");

    vector<vector<int>> graph3 = {
        {0, 0, 0, 20, 0},
        {0, 0, 0, 0, 20},
        {0, 0, 0, 37, 32},
        {20, 0, 37, 0, 0},
        {0, 20, 32, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 2}, B={3, 4}");
}

TEST_CASE("Test isBipartite - is not")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph4 = {
        {0, 0, 0, 2, 0},
        {0, 0, -1, -1, 0},
        {0, -1, 0, -1, 0},
        {2, -1, -1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph5 = {
        {0, 0, 0, 20, 3},
        {0, 0, 0, 0, 20},
        {0, 0, 0, 37, 32},
        {20, 0, 37, 0, 10},
        {3, 20, 32, 10, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph6 = {
        {0, -1, 25, 21, 0, 47},
        {-1, 0, 16, 0, 41, 8},
        {25, 16, 0, 31, 0, 49},
        {21, 0, 31, 0, -5, 11},
        {0, 41, 0, -5, 0, 34},
        {47, 8, 49, 11, 34, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph7 = {
        {0, 21, 11, 4, 46},
        {0, 0, -5, 0, 42},
        {0, 0, 0, -5, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph1 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5},
        {0, 0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph1));

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph2));

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 5, 7},
        {1, 0, 3, 0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph3));

    vector<vector<int>> graph4 = {
        {0, 1, 2, 0, 5, 7},
        {1, 0, 1, 0},
        {2, 3, 0, 4, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph4));
}

TEST_CASE("Test negativeCycle - Not negative cycles")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph does not contain a negative cycle.");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph does not contain a negative cycle.");

    vector<vector<int>> graph3 = {
        {0, 3, -10, 0},
        {3, 0, 0, 20},
        {-10, 0, 0, 30},
        {0, 20, 30, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph does not contain a negative cycle.");

    vector<vector<int>> graph4 = {
       {0, 5, 1, 0},
        {0, 0, 0, -10},
        {1, 0, 0, 30},
        {0, -10, 30, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph does not contain a negative cycle.");
}

TEST_CASE("Test negativeCycle - Negative cycles")
{
    ariel::Graph g;
    vector<vector<int>> graph3 = {
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, -1, -1, 0, 0, 0, 0},
        {0, -1, 0, -1, 0, 0, 0, 0},
        {2, -1, -1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 5},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 5},
        {0, 0, 0, 0, 5, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative cycle: 2->3->1->2");

    vector<vector<int>> graph4 = {
        {0, 0, 0, 2, 0},
        {0, 0, -1, -1, 0},
        {0, -1, 0, -1, 0},
        {2, -1, -1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative cycle: 2->3->1->2");

    vector<vector<int>> graph5 = {
        {0, 0, 0, 2, 0},
        {0, 0, -1, -1, 0},
        {0, -1, 0, -1, 0},
        {2, -1, -1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative cycle: 2->3->1->2");
}
