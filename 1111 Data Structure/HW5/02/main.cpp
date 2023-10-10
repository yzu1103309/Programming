#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

int main()
{
    size_t count, command, cases = 0;
    while(cin >> count >> command && count != 0 && command != 0)
    {
        deque<unsigned> Q;
        ++cases;
        for(size_t t = 0; t < min(count, command); t++)
        {
            Q.emplace_back(t+1);
        }
        cout << "Case " << cases << ':' << endl;
        for(size_t t = 0; t < command; t++)
        {
            char C;
            cin >> C;

            switch (C)
            {
                case 'N':
                    cout << Q.front() << endl;
                    Q.emplace_back(Q.front());
                    Q.pop_front();
                    break;
                case 'E':
                    unsigned id;
                    cin >> id;
                    for(auto it = Q.begin(); it != Q.end(); ++it)
                    {
                        if(*it == id)
                        {
                            Q.erase(it);
                            break;
                        }
                    }
                    Q.emplace_front(id);
            }
        }
    }
}
