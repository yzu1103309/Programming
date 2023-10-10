#include <iostream>
using namespace std;

#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4
#define ANY 5

struct block
{
    char type;
    bool visited = false;
};

class map
{
public:
    int maxArea();
    map(int h, int w);
    ~map();
private:
    void print();
    int area(int x, int y);
    bool allow(int x, int y, int dir);
    int count = 0;
    int curX, curY;
    int max = 0;
    char land;
    int width, height;
    block **blocks;
};

int main()
{
    int h, w;
    while(cin >> h >> w && h * w != 0)
    {
        map globe(h, w);
        cout << globe.maxArea() << endl;
    }
}

int map::maxArea()
{
    //print();
    area(curX, curY); //dispose the result
    count++;
    //print();
    for(int x = 0; x < height; ++x)
    {
        for(int y = 0; y < width; ++y)
        {
            if(!blocks[x][y].visited && blocks[x][y].type == land)
            {
                int tmp = area(x,y);
                if(tmp > max)
                    max = tmp;
                ++count;
            }
        }
    }
    //print();
    return max;
}

int map::area(int x, int y)
{
    y+=width; y%=width; //go around
    blocks[x][y].visited = true;
    int left = 0, right = 0, up = 0, down = 0;
    if(allow(x,y,LEFT)) left = area(x, y-1);
    if(allow(x,y,UP)) up = area(x-1, y);
    if(allow(x,y,RIGHT)) right = area(x, y+1);
    if(allow(x,y,DOWN)) down = area(x+1,y);

    return 1 + left + up + right + down;
}

bool map::allow(int x, int y, int dir){
    switch(dir)
    {
        case LEFT:
            y -= 1; break;
        case UP:
            x -= 1; break;
        case RIGHT:
            y += 1; break;
        case DOWN:
            x += 1; break;
    }

    y += width; y %= width; //go around

    if(x < 0 || x >= height)
        return false;
    else if(blocks[x][y].visited || blocks[x][y].type != land)
        return false;
    else
        return true;
}

map::map(int h, int w)
:height(h), width(w)
{
    blocks = new block * [height];
    for(int x = 0; x < height; ++x)
    {
        blocks[x] = new block [width];
        for(int y = 0; y < width; ++y)
        {
            cin >> blocks[x][y].type;
        }
    }
    cin >> curX >> curY;
    land = blocks[curX][curY].type;
}

map::~map()
{
    for(int x = 0; x < height; ++x)
    {
        delete [] blocks[x];
    }
    delete [] blocks;
}

void map::print()
{
    for(int x = 0; x < height; ++x)
    {
        for(int y = 0; y < width; ++y)
        {
            cout << blocks[x][y].type << ' ';
        }
        cout << endl;
    }
    cout << endl;
}
