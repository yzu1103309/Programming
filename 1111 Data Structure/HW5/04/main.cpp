#include <iostream>
#include <queue>
using namespace std;

int main()
{
    priority_queue<int, vector<int>, greater<int>> s;
    int count;

    while( cin >> count && count != 0)
    {
        int input;
        for(int k = 0; k < count; k++)
        {
            cin >> input;
            s.emplace(input);
        }

        int cost = 0, tmp;

        while(s.size() > 1)
        {
            tmp = s.top(); s.pop();
            tmp += s.top(); s.pop();
            s.emplace(tmp);
            cost += tmp;
        }
        cout << cost << endl;
        s.pop();
    }
}
