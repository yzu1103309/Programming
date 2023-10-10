#include <iostream>
#include <vector>
#include<stack>
#include <algorithm>
using namespace std;

#define NIL -1

struct element
{
	int dfn = 0;
	int low = 0;
	int comp_id = 0;
	vector<int> connected;
};


class graph
{
public:
	int result()
	{
		for (int t = 1; t < elements.size(); ++t)
		{
			if (elements[t].dfn == 0)
			{
				dfs(t, NIL);
			}
		}
		return count;
	}
	void dfs(int index, int parent);
	graph(int size)
	{
		elements.resize(size + 1); //never use dominos[0]

		int lines; cin >> lines;
		for (int t = 0; t < lines; ++t)
		{
			int index, connect;
			cin >> index >> connect;
			elements[index].connected.emplace_back(connect);
		}
	}
private:
	vector<element> elements;
	stack<int> temp;
	int cur_comp_id = 1;
	int depth = 0;
	int count = 0;
	vector<int> comp_dg = vector<int>(1);
};

int main()
{
	int cases;
	cin >> cases;
	for (int c = 0; c < cases; ++c)
	{
		int size;
		cin >> size;
		graph dominos(size);
		cout << dominos.result() << endl;
	}
}

void graph::dfs(int index, int parent)
{
	if (elements[index].dfn == 0)
	{
		elements[index].dfn = elements[index].low = ++depth;
		temp.emplace(index);

		for (int t = 0; t < elements[index].connected.size(); ++t)
		{
			int next = elements[index].connected[t];

			if (elements[next].dfn == 0)
			{
				dfs(next, index);
				elements[index].low = min(elements[index].low, elements[next].low);

				if (elements[next].comp_id != 0 && elements[next].comp_id != cur_comp_id)
				{
					if (comp_dg[elements[next].comp_id] == 1)
					{
						++comp_dg[elements[next].comp_id];
						--count;
					}
				}
			}
			else if (elements[next].comp_id != 0 && elements[next].comp_id != cur_comp_id)
			{
				if (comp_dg[elements[next].comp_id] == 1)
				{
					++comp_dg[elements[next].comp_id];
					--count;
				}
			}
			else
			{
				elements[index].low = min(elements[index].low, elements[next].dfn);
			}
		}

		if (elements[index].dfn == elements[index].low)
		{
			comp_dg.push_back(1);
			int setID;
			do
			{
				setID = temp.top(); temp.pop();
				elements[setID].comp_id = cur_comp_id;
			} while (setID != index);

			++count;
			++cur_comp_id;
		}
	}
}
