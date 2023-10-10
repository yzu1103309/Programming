#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main()
{
    int cases;
    while(cin >> cases)
    {
        stack<int> ST;
        queue<int> QU;
        priority_queue<int> PQ;
        bool st = true, qu = true, pq = true, error = false;
        int count = 0;
        for(int i = 0; i < cases; i++)
        {
            int choice, x;
            cin >> choice >> x;
            switch (choice)
            {
                case 1:
                    if(st) ST.emplace(x);
                    if(qu) QU.emplace(x);
                    if(pq) PQ.emplace(x);
                    ++count;
                    break;
                case 2:
                    if(count == 0)
                    {
                        error = true;
                        break;
                    }
                    if(st)
                    {
                        if(x != ST.top()) st = false;
                        else ST.pop();
                    }
                    if(qu) {
                        if (x != QU.front()) qu = false;
                        else QU.pop();
                    }
                    if(pq)
                    {
                        if(x != PQ.top()) pq = false;
                        else PQ.pop();
                    }
                    count--;
            }
            if((!st && !qu && !pq) || error)
            {
                while(i + 1 < cases)
                {
                    cin >> choice >> x;
                    i++;
                }
                cout << "impossible" << endl;
            }
        }
        if((st || qu || pq) && !error)
        {
            if(st + qu + pq > 1)
                cout << "not sure" << endl;
            else if(st) cout << "stack" << endl;
            else if(qu) cout << "queue" << endl;
            else if(pq) cout << "priority queue" << endl;
        }
    }
}
