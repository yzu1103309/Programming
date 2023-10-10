#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

struct block
{
    char lang;
    bool visited = false;
};

class graph
{
public:
    void process(int x, int y);
    graph(int h, int w)
    :height(h), width(w)
    {
        blocks = new block * [height];
        for(int t = 0; t < height; ++t)
        {
            blocks[t] = new block [width];
            for(int s = 0; s < width; ++s)
            {
                cin >> blocks[t][s].lang;
            }
        }
    }
    ~graph()
    {
        for(int s = 0; s < height; ++s)
        {
            delete [] blocks[s];
        }
        delete [] blocks;
    }
    block **blocks;
    map <char, int> count;
private:
    bool allow(int dir, int x, int y);
    int height, width;
};

int main()
{
    int cases;
    cin >> cases;
    for(int c = 0; c < cases; ++c)
    {
        int h, w;
        cin >> h >> w;
        graph G(h,w);
        for(int x = 0; x < h; ++x)
        {
            for(int y = 0; y < w; ++y)
            {
                if(!G.blocks[x][y].visited)
                {
                    G.process(x,y);
                    ++G.count[G.blocks[x][y].lang];
                }
            }
        }
        cout << "World #" << c+1 << endl;
        for(auto it = G.count.begin(); it != G.count.end(); ++it)
        {
            cout << it->first << ": " << it->second << endl;
        }
    }
}

void graph::process(int x, int y)
{
    if(blocks[x][y].visited)
        return;
    else
    {
        blocks[x][y].visited = true;
        if(allow(LEFT,x,y))
        {
            process(x,y-1);
        }
        else if(allow(UP,x,y))
        {
            process(x-1,y);
        }
        else if(allow(RIGHT,x,y))
        {
            process(x,y+1);
        }
        else if(allow(DOWN,x,y))
        {
            process(x+1,y);
        }
    }
}

bool graph::allow(int dir, int x, int y)
{
    switch (dir)
    {
        case LEFT:
            return (y-1 >= 0) && !blocks[x][y-1].visited && blocks[x][y-1].lang == blocks[x][y].lang;
        case RIGHT:
            return (y+1 < width) && !blocks[x][y+1].visited && blocks[x][y+1].lang == blocks[x][y].lang;
        case UP:
            return (x-1 >= 0) && !blocks[x-1][y].visited && blocks[x-1][y].lang == blocks[x][y].lang;
        case DOWN:
            return (x+1 < height) && !blocks[x+1][y].visited && blocks[x+1][y].lang == blocks[x][y].lang;
    }
}