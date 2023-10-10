#include <stack>
#include <iostream>
#include <string>
using namespace std;


int pr(char x)
{
	switch (x)
	{
	case '(':
		return 3;
		break;
	case '*':
		return 1;
		break;
	case'/':
		return 1;
		break;
	case '+':
		return 2;
		break;
	case '-':
		return 2;
		break;
	default:
		return -1;
	}
}

int main()
{
	int C;
	cin >> C;

	for (int i = 0; i < C; ++i)
	{
		string tmp, eq;
		stack<char> st;
		while (getline(cin, tmp))
		{
			if (tmp == "" && !eq.empty()) break;
			
			if(tmp != "") eq.push_back(tmp[0]);
		}

		for (size_t t = 0; t < eq.size(); ++t)
		{
			if (eq[t] == '(')
			{
				st.emplace(eq[t]);
			}
			else if (eq[t] == ')')
			{
				for (; st.top() != '('; st.pop())
				{
					cout << st.top();
				}
				st.pop();
			}
			else if (pr(eq[t]) == -1)
			{
				cout << eq[t];
			}
			else if (st.empty() || pr(eq[t]) < pr(st.top()))
			{
				st.emplace(eq[t]);
			}
			else 
			{
				for (; !st.empty() && pr(eq[t]) >= pr(st.top()); st.pop())
				{
					cout << st.top(); 
				}
				st.emplace(eq[t]);
			}
		}
		for (; !st.empty(); st.pop())
		{
			cout << st.top();
		}
		if (i < C - 1) cout << endl << endl;
		else cout << endl;
	}
}