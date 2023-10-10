#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

#define MAX 2147483647

struct edge
{
    int next;
    int weight;

    edge(int Next, int Weight)
    {
        next = Next;
        weight = Weight;
    }
};

struct vertex
{
    int d = MAX;
    int parent = -1;
    vector<edge> edges;
};

class graph
{
public:
    graph(int size)
    {
        vertices.resize(size);
        vertices[0].d = 0;
    }
    void newEdge(int p1, int p2, int weight)
    {
        vertices[p1].edges.emplace_back( edge(p2, weight) );
    }
    int answer()
    {
        stack<int> wait;
        wait.push(0);

        while(!wait.empty())
        {
            int current = wait.top();
            wait.pop();
            for(int e = 0; e < vertices[current].edges.size(); ++e)
            {
                int next = vertices[current].edges[e].next;
                int weight = vertices[current].edges[e].weight;
                if(vertices[current].d + weight < vertices[next].d)
                {
                    vertices[next].d = vertices[current].d + weight;
                    vertices[next].parent = current;
                    wait.push(next);
                }
            }
        }

        auto max = max_element( vertices.begin(), vertices.end(), [](auto l, auto r){ return l.d < r.d; } );
        return max->d;
    }
private:
    vector<vertex> vertices;
};

int main()
{
    int v, e; //number of vertices and edges

    while(cin >> v >> e)
    {
        graph G(v);
        for(int t = 0; t < e; ++t)
        {
            int p1, p2, weight;
            cin >> p1 >> p2 >> weight;
            G.newEdge(p1, p2, weight);
        }
        cout << G.answer() << endl;
    }
}
