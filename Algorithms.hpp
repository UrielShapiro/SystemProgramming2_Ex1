namespace ariel
{
    class Algorithms
    {
    public:
        static int isConnected(Graph g);
        static string shortestPath(Graph g, int start, int end);
        static int isContainsCycle(Graph g);
        static string isBipartite(Graph g);
    };
};