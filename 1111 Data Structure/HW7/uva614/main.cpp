#include <iostream>
#include <iomanip>
using namespace std;

#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4
#define ANY 5

struct vertex
{
    int visited = 0; //0: not visited; 1: visited; -1: ???
    int footprint = 0;
    int walls = 0;
    bool goal = false;
};

class graph
{
public:
    graph(int h, int w, int goal_x, int goal_y);
    ~graph();
    void dfs(int x, int y);
    void print();

private:
    int height, width, steps = 0;
    bool finished = false;
    vertex **rows = nullptr;
    vertex &cell(int x, int y) { return rows[y][x]; };
    bool allow(int dir, int x, int y);
};

int main()
{
    int height, width, startY, startX, goalY, goalX, count = 0;
    while(cin >> height >> width >> startY >> startX >> goalY >> goalX && height * width != 0)
    {
        startX -= 1;
        startY -= 1;
        goalX -= 1;
        goalY -= 1;
        graph maze(height, width, goalX, goalY);
        maze.dfs(startX,startY);
        cout << "Maze " << ++count << endl << endl;
        maze.print();
        cout << endl << endl;
    }
}

void graph::dfs(int x, int y)
{
    ++steps;
    cell(x,y).footprint = steps;
    cell(x,y).visited = 1;
    if(cell(x,y).goal){
        finished = true;
        return;
    }
    if( !finished && allow(LEFT, x, y) )
    {
        dfs(x-1, y);
    }
    if( !finished && allow(UP, x, y) )
    {
        dfs(x, y-1);
    }
    if( !finished && allow(RIGHT, x, y) )
    {
        dfs(x+1, y);
    }
    if( !finished && allow(DOWN, x, y) )
    {
        dfs(x, y+1);
    }
    if( !finished && !allow(ANY, x, y) )
    {
        cell(x,y).footprint = 0;
        cell(x,y).visited = -1;
        --steps;
    }
};

bool graph::allow(int dir ,int x, int y)
{
    switch (dir)
    {
        case 1:
            return (x > 0 && !cell(x-1, y).visited && cell(x-1,y).walls != 1 && cell(x-1,y).walls != 3);
        case 2:
            return (y > 0 && !cell(x,y-1).visited && cell(x,y-1).walls != 2 && cell(x,y-1).walls != 3);
        case 3:
            return (cell(x,y).walls != 3 && cell(x,y).walls != 1 && x + 1 < width && !cell(x+1, y).visited);
        case 4:
            return (cell(x,y).walls != 3 && cell(x,y).walls != 2 && y + 1 < height && !cell(x, y+1).visited);
        case 5:
            return allow(1,x,y) || allow(2,x,y) || allow(3,x,y) || allow(4,x,y);
    }
}

void graph::print()
{
    for(int t = 0; t < width; ++t)
    {
        cout << "+---";
    }
    cout << '+' << endl;
    for(int y = 0; y < height; ++y)
    {
        cout << '|';
        for(int x = 0; x < width; ++x)
        {
            if(cell(x,y).visited == 1)
                cout << setfill(' ') << setw(3) << cell(x,y).footprint;
            else if(cell(x,y).visited == -1)
                cout << "???";
            else
                cout << "   ";

            if(x != width - 1 && (cell(x,y).walls == 1 || cell(x,y).walls == 3) )
                cout << '|';
            else if(x != width - 1)
                cout << ' ';
        }
        cout << '|' << endl;
        if(y != height - 1)
        {
            cout << '+';
            for(int x = 0; x < width; ++x)
            {
                if(cell(x,y).walls == 2 || cell(x,y).walls == 3)
                    cout << "---";
                else
                    cout << "   ";
                cout << '+';
            }
            cout << endl;
        }
    }
    for(int t = 0; t < width; ++t)
    {
        cout << "+---";
    }
    cout << '+' << endl;
}

graph::graph(int h, int w, int goal_x, int goal_y)
        : height(h), width(w)
{
    rows = new vertex * [height];
    for(int t = 0; t < height; ++t)
    {
        rows[t] = new vertex [width];
        for(int n = 0; n < width; ++n)
            cin >> rows[t][n].walls;
    }
    cell(goal_x, goal_y).goal = true;
};

graph::~graph()
{
    for(int t = 0; t < height; ++t)
    {
        delete [] rows[t];
    }
    delete [] rows;
}

