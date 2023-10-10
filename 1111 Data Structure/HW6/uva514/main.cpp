#include <iostream>
#include <stack>
#include <queue>
using namespace std;
int main()
{
    int count;

    while(cin >> count && count)
    {
        bool end = 0;
        while(!end)
        {
            stack<int> waiting;
            queue<int> input;
            for(int t = 1; t <= count && !end; ++t)
            {
                int num;
                cin >> num;

                if(num == 0) end = true;

                waiting.emplace(t);
                input.emplace(num);

                while(!waiting.empty() && !input.empty() && input.front() == waiting.top())
                {
                    waiting.pop();
                    input.pop();
                }
            }

            if(!end)
            {
                if(waiting.empty() && input.empty())
                    cout << "Yes" << endl;
                else
                    cout << "No" << endl;
            }
        }
        cout << endl;
    }
}
