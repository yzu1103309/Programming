#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

#define NIL -1
#define MAX 999999 //added

struct element
{
	int id = 0;
	int weight = 0;
    size_t vector_index; //added
    bool visited = false; //added
	vector<int> connected;
};

struct edge
{
	int a;
	int b;
    int weight; //added
};

struct cmp //added
{ //added
    bool operator()(element left, element right) //added
    {
        if(left.weight > right.weight) return true; //added
        else if(left.weight < right.weight) return false; //added
        else { if(left.id > right.id) return true; else return false; } //added
    } //added
}; //added

class graph
{
public:
	int result() { //added
		while(!min.empty()) { //added
            element top = min.top(); min.pop(); //added
            bfs(top.vector_index, NIL);
        } //added
        int minimum = MAX;
        for(int t = 0; t < dest_index.size(); ++t){ minimum = std::min( minimum, elements[dest_index[t]].weight); }
        return minimum;
	}
	void bfs(int index, int parent);
	
	graph(int size, int dest)
	{
		for (int s = 0; s < size; ++s)
		{
			int speed; cin >> speed;
			speeds.emplace_back(speed);
		}
		for (int s = 0; s <= size; ++s) //modified
		{
            int index = 0; //added
			string line;
			getline(cin, line);
			stringstream ss(line);
			int arrive;
			while (ss >> arrive)
			{
                if(arrive == dest) dest_index.emplace_back(elements.size()); //added
                int id = 100 * (s) + arrive; //added
                if(index++ == 0){ if(arrive == 0){ edges.emplace_back( edge{0, int(elements.size()), 0 }); //added
                    elements[0].connected.emplace_back(edges.size()-1);} }//added
                else{ edges.emplace_back( edge{int(elements.size()-1),int(elements.size()),(id-elements.back().id)*speeds[s]}); //added
                    elements.back().connected.emplace_back(edges.size()-1); }  //added
                elements.emplace_back( element{id,MAX,elements.size()} ); //added
                if( index-1!=0||(index-1==0 && arrive==0) ) elements.back().connected.emplace_back(edges.size()-1); //added
                //min.push(element{id,MAX, elements.size()}); //added
			} //added
		} //added

        for(int n = 1; n < elements.size() - 1; ++n){ //added
            for( int t = n + 1; t < elements.size() - 1; ++t){ //added
                if(elements[n].id % 100 == elements[t].id % 100){ //added
                edges.emplace_back( edge{int(elements[n].vector_index),int(elements[t].vector_index),60} ); //added
                elements[n].connected.emplace_back(edges.size()-1); //added
                elements[t].connected.emplace_back(edges.size()-1);} //added
            } //added
        } //added

        min.emplace(element{0,0, 0}); //added
        elements.emplace_back( element{700,MAX, elements.size()} ); //added
        min.emplace(element{700,MAX, elements.size()-1}); //added
        edges.emplace_back( edge{int(elements.size()-2),int(elements.size()-1),0} ); //added
        elements[elements.size()-2].connected.emplace_back(edges.size()-1);
        elements[elements.size()-1].connected.emplace_back(edges.size()-1);
	}
private:
	vector<element> elements = vector<element>(1); //never use [0]
	vector<edge> edges;
    vector<int> dest_index; //added
	vector<int> speeds = vector<int>(1); //never use [0]
    priority_queue<element, vector<element>, cmp> min; //added
};

int main()
{
	int Ecount, Dest;
	while (cin >> Ecount >> Dest)
	{
		graph G(Ecount, Dest);
        int r = G.result(); //added
        if(r == MAX)
            cout << "IMPOSSIBLE" << endl; //added
        else
            cout << r << endl;
	}
}

void graph::bfs(int index, int parent)
{
	for(int t = 0; t < elements[index].connected.size(); ++t)
    {
        int edge_index = elements[index].connected[t];
        elements[index].visited = true;
        int next = (edges[edge_index].a == index)?edges[edge_index].b:edges[edge_index].a;
        int new_w = elements[index].weight + edges[edge_index].weight;
        if( new_w < elements[next].weight ){ elements[next].weight = new_w;
        if(!elements[next].visited ) min.emplace(elements[next]);
        }
    }
}