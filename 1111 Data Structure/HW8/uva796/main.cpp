#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define bridge pair<int, int>

struct point
{
    int dfn = 0;
    int low = 0;
    vector<int> neighbors;
};

class graph
{
public:
    void dfs(int index, int parent);
    void result()
    {
        cout << critical.size() << " critical links" << endl;
        sort(critical.begin(), critical.end(), [](bridge A, bridge B)
        {
            if(A.first < B.first)
                return true;
            else if(A.first == B.first)
            {
                if(A.second < B.second)
                    return true;
                else
                    return false;
            }
            else return false;
        });
        for(size_t t = 0; t < critical.size(); ++t)
        {
            cout << critical[t].first << " - " << critical[t].second << endl;
        }
        cout << endl;
    }
    graph(int size)
    {
        points.resize(size);
        char parentheses;
        for(int t = 0; t < size; ++t)
        {
            int id, num;
            cin >> id >> parentheses >> num >> parentheses;
            for(int s = 0; s < num; ++s)
            {
                int neighbor; cin >> neighbor;
                points[id].neighbors.emplace_back(neighbor);
            }
        }
    }

private:
    vector<point> points;
    vector<bridge> critical;
    int depth = 0;
};

int main()
{
    int count;
    while( cin >> count )
    {
        graph network(count);

        for(int t = 0; t < count; ++t)
        {
            network.dfs(t,-1);
        }
        network.result();
    }
}

void graph::dfs(int index, int parent)
{
    if(points[index].dfn == 0)
    {
        points[index].dfn = points[index].low = ++ depth ;
        for(int t = 0; t < points[index].neighbors.size(); ++t)
        {
            int next = points[index].neighbors[t];
            if(points[next].dfn == 0)
            {
                dfs(next, index);
                points[index].low = min(points[index].low, points[next].low);
            }
            else if(next != parent)
            {
                //"next" is already visited, but not my parent
                //if next dfn larger: forward edge;
                //if next dfn smaller: back edge;
                points[index].low = min(points[index].low, points[next].dfn);
            }

            if(points[next].low > points[index].dfn) //it's a bridge
            {
                bridge tmp = {min(index,next),max(index,next)};
                critical.push_back(tmp);
            }
        }
    }
}