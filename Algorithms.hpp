#include <string>
namespace ariel
{
    class Algorithms
    {
    public:
        static int isConnected(Graph g);
        static string shortestPath(Graph g, size_t start, size_t end);
        static int isContainsCycle(Graph g);
        static string isBipartite(Graph g);
    };
};