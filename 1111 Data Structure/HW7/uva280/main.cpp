#include <iostream>
#include <vector>
using namespace std;

struct vertex
{
    vector<int> neighbors;
    bool visited = false;
};

void dfs(vector<vertex> &graph, int v, int &remain)
{
    if(graph[v].visited) return;
    else
    {
        graph[v].visited = true;
        --remain;
        for(size_t t = 0; t < graph[v].neighbors.size(); ++t)
        {
            dfs(graph, graph[v].neighbors[t],remain);
        }
    }
};

int main()
{
    int count;
    while(cin >> count && count != 0)
    {
        vector<vertex> graph(1 + count);

        int current;
        while(cin >> current && current != 0)
        {
            int neighbor;
            while(cin >> neighbor && neighbor != 0)
            {
                graph[current].neighbors.emplace_back(neighbor);
            }
        }
        int start;
        cin >> start; //count of start vertex
        for(int n = 0; n < start; ++n)
        {
            int remain = count;
            vector<vertex> graph2 = graph;
            cin >> current;
            for(size_t t = 0; t < graph2[current].neighbors.size(); ++t)
            {
                if(remain > 0) dfs(graph2, graph2[current].neighbors[t], remain);
            }
            cout << remain;
            for(size_t t = 1; t < graph2.size(); ++t)
            {
                if(!graph2[t].visited) cout << ' ' << t;
            }
            cout << endl;
        }
    }
}
