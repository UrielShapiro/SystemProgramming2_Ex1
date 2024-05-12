# Makefile Documentation

## Targets

### `all`

- Compiles the `demo` and `test` targets, which are the primary executables for running the program and tests.

### `debug`

- Compiles `Algorithms.cpp` with debugging symbols (Changes #define DEBUG to be defined) and runs the `test` target.

### `run`

- Executes the `demo` target, which is the main program.

### `test`

- Compiles the `TestCounter.o`, `Test.o`, and other object files into the `test` executable and runs it.

### `tidy`

- Runs `clang-tidy` on the source files with a set of predefined checks for bugs, performance, portability, and readability. It treats warnings as errors except for those explicitly allowed.

### `valgrind`

- Runs Valgrind on both the `demo` and `test` executables to detect memory leaks and other memory-related issues.

### `clean`

- Removes all generated object files and executables, cleaning up the build directory.

## Usage

To compile and run the program, simply execute `make` in the terminal. To run the tests, execute `make test`. For debugging, use `make debug`. To clean up the build artifacts, use `make clean`.


# Ariel Graph Library

This library provides a simple and intuitive interface for working with graphs that are represented as adjecency matrix. It supports both directed and undirected graphs, and allows for the manipulation and analysis of these structures. Below is a detailed explanation of the provided code.

## Overview

The library defines a `Graph` class within the `ariel` namespace. This class encapsulates the functionality required to create, manipulate, and analyze graphs. The graphs are represented internally as adjacency matrices, where each cell `[i][j]` represents the weight of the edge between vertices `i` and `j`.

### Class Members

- **`graph`**: A 2D vector representing the adjacency matrix of the graph.
- **`isDirected`**: A boolean flag indicating whether the graph is directed or not.
- **`containsNegativeEdge`**: A boolean flag indicating whether the graph contains negative edges.

### Constructor

Initializes the 2D vector of representing the graph.
Initializes the `isDirected` as `false`, assuming each graph is undirected untill proved otherwise.
Initializes the `isDirected` as `false`, assuming each graph has positive edges untill proved otherwise.



### Member Functions

#### `size()`
Returns the number of vertices in the graph.

#### `get_edge(i, j)`
Returns the weight of the edge between vertices `i` and `j`.

#### `at(i)`
Returns the adjacency list of vertex `i`.

#### `isDirectedGraph()`
Returns `true` if the graph is directed, `false` otherwise.

#### `isContainsNegativeEdge()`
Returns `true` if the graph contains negative edges, `false` otherwise.

#### `MakeUndirectedGraph(Graph g)`
Creates an undirected graph from a directed graph. It copies the edges from the original graph to the new graph in both directions and marks the new graph as undirected.

#### `loadGraph(std::vector<std::vector<int>> g)`
Loads a graph from a given matrix. It checks for validity conditions such as non-emptiness, square matrix, symmetry (for undirectedness), and existence of negative edges. Throws an exception if any condition is not met.

#### `printGraph()`
Prints the graph as a matrix and outputs the number of vertices and edges.

### Example Usage


# Graph Algorithms Implementation

This class contains an implementation of various graph algorithms including Dijkstra's algorithm, Bellman-Ford algorithm, Depth-First Search (DFS), and Breadth-First Search (BFS). These algorithms are implemented within the `ariel` namespace under `Algorithms` and are designed to work with a custom `Graph` class.


## Functions Overview

### `isConnected`
Checks if the graph is connected.
In order to check if the graph is connected and not just strongly connected, the function creates a new undirected graph. and run a Depth First Search (DFS) algorithm on that graph.
Afterwards, the function checks if there is a node that wasn't visited.
If there is a node that was not visited, the graph is not connected. otherwise, it is.

### `shortestPath`
Finds the shortest path between two nodes in the graph, using either Dijkstra's or Bellman-Ford algorithm based on the presence of negative edges.
If there isn't a negative cycle, the function will return a string containing the nodes in the shortest path from the src node to the dst node.

### `isContainsCycle`
Checks if the graph contains a cycle.
The function uses Depth First Search (DFS) to check if the graph contains a cycle (if there is a back-edge, there is a cycle).
If a cycle exists in the graph, the function will return a string containing the nodes in the cycle.


### `isBipartite`
Checks if the graph is bipartite.
The function uses Breadth First Search (BFS) to color the graph in two colors (RED and BLUE).
If the graph is 2-colorable, it is bipartite.
If the graph is bipartite, the function returns a string containing the division of the graph to 2 sets of vertices.
otherwise, it will return "0".

### `negativeCycle`
Checks if the graph contains a negative cycle.
Note: The function won't work on directed graphs that contain a negative cycle.
The function uses the Bellman-Ford algorithm to check if the graph contains a negative cycle.
If it does, a string with the nodes in the negative cycle will be returned.

## Contributing

Contributions are welcome Please feel free to submit pull requests or open issues for discussion.

## License

This project is licensed under the MIT License.

