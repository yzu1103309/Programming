#include <queue>
#include <iostream>
#include <stack>
using namespace std;

int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; ++i)
	{
		int battles, gcount, bcount;
		cin >> battles >> gcount >> bcount;
		stack<int> gwin, bwin;
		priority_queue<int> blue, green;
		for (int t = 0; t < gcount; ++t)
		{
			int input;
			cin >> input;
			green.emplace(input);
		}
		for (int t = 0; t < bcount; ++t)
		{
			int input;
			cin >> input;
			blue.emplace(input);
		}
		bool end = 0;
		while (!end)
		{
			for (int t = 0; !blue.empty() && !green.empty() && t < battles; ++t)
			{
				int g = green.top(), b = blue.top();
				green.pop(); blue.pop();
				if (g > b)
				{
					gwin.emplace(g - b);
				}
				else if (b > g)
				{
					bwin.emplace(b - g);
				}
			}
			while (!gwin.empty())
			{
				green.emplace(gwin.top());
				gwin.pop();
			}
			while (!bwin.empty())
			{
				blue.emplace(bwin.top());
				bwin.pop();
			}
			if (green.empty() || blue.empty())
			{
				end = 1;
				if (green.empty() && blue.empty())
					cout << "green and blue died" << endl;
				else if (green.empty())
					cout << "blue wins" << endl;
				else if (blue.empty())
					cout << "green wins" << endl;

				while (!green.empty())
				{
					cout << green.top() << endl;
					green.pop();
				}
				while (!blue.empty())
				{
					cout << blue.top() << endl;
					blue.pop();
				}
			}
		}
		if (i < cases - 1) cout << endl;
	}
}