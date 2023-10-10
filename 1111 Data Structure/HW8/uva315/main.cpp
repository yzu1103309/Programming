#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

#define NIL -1

struct point
{
    int dfn;
    int low;
    bool cutP = false;
    vector<int> connected;
};

class graph
{
public:
    int result(){
        dfs(1, NIL);
        return cut_count;
    };
    graph(int size)
    {
        points.resize(size + 1); //never use points[0]
        int id;
        while( cin >> id && id != 0)
        {
            string temp; int connect;
            getline(cin, temp);
            stringstream ss(temp);
            while(ss >> connect)
            {
                //Bidirectional
                points[id].connected.emplace_back(connect);
                points[connect].connected.emplace_back(id);
            }
        }
    }
private:
    void dfs(int index, int parent);

    vector<point> points;
    int depth = 0;
    int cut_count = 0;
};

int main()
{
    int size;
    while(cin >> size && size != 0)
    {
        graph network(size);

        //all connected, so start from points[1]
        cout << network.result() << endl;
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
                ++child;
                dfs(next, index);
                points[index].low = min(points[index].low, points[next].low);

                // if there's no back edge from child to ancestor
                if(points[next].low >= points[index].dfn)
                    points[index].cutP = true;
            }
            else if(next != parent) //next already visited, and it's not parent
            {
                points[index].low = min(points[index].low, points[next].dfn);
            }
        }

        if(parent == NIL) //if it's root
        {
            if(child > 1) //if it has more than one subtree
                points[index].cutP = true; //if root has more than two subs
            else
                points[index].cutP = false;
        }
        if(points[index].cutP) ++cut_count;
    }
}