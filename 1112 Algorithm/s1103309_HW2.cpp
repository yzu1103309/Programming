#include <iostream>
#include <vector>
using namespace std;

struct vertex
{
    int d = 0;
    int parent = -1;
    vector<int> neighbors;
};

class edge
{
public:
    edge(int a, int b)
    {
        p1 = a;
        p2 = b;
    }
    bool equal(int a, int b)
    {
        if(a == p1 && b == p2)
            return true;
        else if(b == p1 && a == p2)
            return true;
        else
            return false;
    }
    int p1;
    int p2;
    bool dfs = false;
    int cycle_count = 0;
};

class Graph {
public:
    Graph(int size)
    {
        total_points = size;
        vertices.resize(size + 1);
    }
    void add_edge(int p1, int p2)
    {
        vertices[p1].neighbors.emplace_back(p2);
        vertices[p2].neighbors.emplace_back(p1);
        edges.emplace_back(p1,p2);
        edge_count++;
    }
    void answer()
    {
        dfs(1, 1);
        if(total_points != dfs_points || edge_count - 1 <= dfs_edges)
        {
            cout << "n" << endl;
        }
        else
        {
            cout << "y" << endl;
            if(edge_count - 3 >= dfs_edges)
            {
                cout << "There are at least three cycles." << endl;
            }
            else
            {
                for(int t = 0; t < edges.size(); ++t)
                {
                    if(!edges[t].dfs)
                    {
                        int p1 = edges[t].p1;
                        int p2 = edges[t].p2;
                        if(vertices[p1].d > vertices[p2].d)
                        {
                            swap(p1,p2);
                        }
                        find_ancestor(p2, p1);
                    }
                }
                for(int t = 0; t < edges.size(); ++t)
                {
                    if(edges[t].cycle_count >= 2)
                    {
                        cout << "There are at least three cycles." << endl;
                        break;
                    }
                }
            }
        }
    }
    void dfs(int v, int d)
    {
        vertices[v].d = d;
        dfs_points++;
        for(int t = 0; t < vertices[v].neighbors.size(); ++t)
        {
            int next = vertices[v].neighbors[t];
            if(!vertices[next].d)
            {
                edges[edge_index(v, next)].dfs = true;
                ++dfs_edges;
                dfs(next, d+1);
                vertices[next].parent = v;
            }
        }
    }
    void find_ancestor(int start, int dest)
    {
        int parent = vertices[start].parent;
        if(parent != -1)
        {
            ++edges[edge_index(start, parent)].cycle_count;
            if(parent != dest)
            {
                find_ancestor(parent, dest);
            }
        }
    }
    int edge_index(int p1, int p2)
    {
        for(int t = 0; t < edges.size(); ++t)
        {
            if(edges[t].equal(p1, p2))
            {
                return t;
            }
        }
        return -1; //won't be executed if no error
    }
private:
    int total_points;
    int edge_count = 0;
    int dfs_edges = 0;
    int dfs_points = 0;
    vector<vertex> vertices;
    vector<edge> edges;
};

int main()
{
    int count, p1, p2;
    cin >> count;
    Graph graph(count);
    while(cin >> p1 && p1 != -1)
    {
        cin >> p2;
        graph.add_edge(p1, p2);
    }
   graph.answer();
}