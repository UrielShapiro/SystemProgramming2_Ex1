//ID: 314779745
//Mail: uriel1999@gmail.com

#include <iostream>
#include <vector>
using namespace std;

class Graph {
    private:
        vector<vector<int>> graph;

    public:
        Graph()
        {
            this->graph = vector<vector<int>>();
        }
        void loadGraph(vector<vector<int>> graph)
        {
            if(graph.at(0).size() != graph.size())
            {
                throw invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
            for (size_t i = 0; i < graph.size() ; i++)
            {
                for (size_t j = 0; j < graph.size(); j++)
                {
                    this->graph.at(i).push_back(graph.at(i).at(j));
                }
            } 
        }

        void printGraph()
        {
            int edges = 0;
            for (size_t i = 0; i < this->graph.size(); i++)
            {
                for (size_t j = 0; j < this->graph.size(); j++)
                {
                    cout << this->graph.at(i).at(j) << "\t";
                    if (this->graph.at(i).at(j) != 0)
                    {
                        edges++;
                    }
                }
                cout << endl;
            }
            cout << "Graph with " << this->graph.size() << " vertices and " << edges << " edges." << endl;  
        }

        int size()
        {
            return this->graph.size();
        }
        int get_edge(int i, int j)
        {
            return this->graph.at(i).at(j);
        }
        vector<int> at(int i)
        {
            return this->graph.at(i);
        }
};