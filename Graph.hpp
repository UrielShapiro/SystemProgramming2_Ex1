namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int>> graph;
    public:
        Graph();
        void loadGraph(vector<vector<int>> graph);
        void printGraph();
        int size();
        int get_edge(int i, int j);
        vector<int> at(int i);
    };
};

