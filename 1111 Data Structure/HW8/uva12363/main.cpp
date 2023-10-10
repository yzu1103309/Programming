#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct room
{
    bool visited = false;
    vector<int> connected;
};

class graph
{
public:
    graph(int size)
    {
        original.resize(size + 1); //never use room[0]
    }
    void set(int index, int connect)
    {
        if(std::find(original[index].connected.begin(),original[index].connected.end(), connect) == original[index].connected.end() )
        {
            original[index].connected.push_back(connect);
            original[connect].connected.push_back(index);
        }
    }
    void query(int start, int end)
    {
        rooms = original;
        simple_path(start, end);
        if(count == 1)
        {
            cout << 'Y' << endl;
        }
        else
        {
            cout << 'N' << endl;
        }
        count = 0;
    }
    void simple_path(int start, int end);
private:
    vector<room> original;
    vector<room> rooms;
    int count = 0;
};

int main()
{
    int R, C, Q;
    while(cin >> R >> C >> Q && R+C+Q != 0)
    {
        graph map(R);
        for(int t = 0; t < C; ++t)
        {
            int index, connect;
            cin >> index >> connect;
            map.set(index, connect);
        }
        for(int t = 0; t < Q; ++t)
        {
            int start, end;
            cin >> start >> end;
            map.query(start, end);
        }
        cout << '-' << endl;
    }
}

void graph::simple_path(int start, int end)
{
    rooms[start].visited = true;
    for(int t = 0; t < rooms[start].connected.size(); ++t)
    {
        int next = rooms[start].connected[t];
        if(next != end && !rooms[next].visited)
        {
            simple_path(next, end);
        }
        else if(next == end)
        {
            ++count;
        }
    }
}