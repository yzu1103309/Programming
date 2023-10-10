#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

#define NIL -1

struct point
{
    int dfn = 0;
    int low = 0;
    bool cutP = false;
    vector<int> connected;
};

class graph
{
public:
    void print_result()
    {
        long long ans1 = 0, ans2 = 1;
        if(components.size() == 1) ans1 = 2, ans2 = components[0].size() * (components[0].size() - 1) / 2;
        else
        {
            for(int t = 0; t < components.size(); ++t)
            {
                int count = 0;
                for(int i = 0; i < components[t].size(); ++i)
                {
                    int p = components[t][i];
                    if(points[p].cutP) ++count;
                }
                if(count == 1) ++ans1, ans2 *= components[t].size() - 1;
            }
        }

        cout << ans1 << " " << ans2 << endl;
    }
    void dfs(int index, int parent);
    graph(int count)
    {
        for(int i = 0; i < count; ++i)
        {
            int a, b;
            cin >> a >> b;

            if(points.size() <= a || points.size() <= b)
                points.resize( max(a,b) + 1 );

            points[a].connected.emplace_back(b);
            points[b].connected.emplace_back(a);
        }
    }
private:
    vector<point> points; //never use points[0]
    stack<int> temp;
    vector<vector<int>> components;
    int depth = 0;
};

int main()
{
    int count;
    while( cin >> count && count != 0 )
    {
        graph mine(count);
        mine.dfs(1, NIL);
        mine.print_result();
    }
}

void graph::dfs(int index, int parent)
{
    if(points[index].dfn == 0)
    {
        points[index].dfn = points[index].low = ++depth;
        int child = 0;
        for(int t = 0; t < points[index].connected.size(); ++t)
        {
            int next = points[index].connected[t];
            if(points[next].dfn == 0)
            {
                temp.emplace(next);
                ++child;
                dfs(next, index);
                points[index].low = min(points[index].low, points[next].low);

                if(points[next].low >= points[index].dfn)
                    points[index].cutP = true;

                //start new component
                if(points[index].cutP = true)
                {
                    vector<int> component;
                    int element;
                    do {
                        element = temp.top(), temp.pop();
                        component.emplace_back(element);
                    } while (element != next);

                    component.push_back(index);
                    components.emplace_back(component);
                }
            }
            else if(next != parent)
            {
                points[index].low = min(points[index].low, points[next].dfn);
            }
        }
        if(parent == NIL && child == 1) points[index].cutP = false;
    }
}