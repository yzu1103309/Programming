#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int set;
    cin >> set;
    for(int n = 0; n < set; ++n)
    {
        size_t N, S, Q;
        //N: Stations; S: Carrier Capacity; Q: Station Capacity;
        cin >> N >> S >> Q;
        vector<queue<int>> platforms (N) ;
        stack<int> carrier; //the truck
        size_t total = 0; //total cargo count
        for(size_t t = 0; t < N; ++t) //t: station ID;
        {
            size_t num;
            cin >> num; //count of cargos in each station
            total += num;
            for(size_t s = 0; s < num; ++s)
            {
                int cargo; //cargo label
                cin >> cargo;
                platforms[t].emplace(cargo);
            }
        }
        //the truck departs
        size_t time = 0, current = 0;
        while(total > 0)
        {
            while(carrier.size() < S && !platforms[current % N].empty())
            {
                carrier.emplace(platforms[current % N].front());
                platforms[current % N].pop();
                ++time;
            }
            ++current; time += 2;
            while(platforms[current % N].size() < Q && !carrier.empty())
            {
                if(carrier.top() == (current % N) + 1)
                {
                    carrier.pop();
                    --total;
                    ++time;
                }
                else
                {
                    platforms[current % N].emplace(carrier.top());
                    carrier.pop();
                    ++time;
                }
            }
            while(!carrier.empty() && carrier.top() == (current % N) + 1)
            {
                carrier.pop();
                --total;
                ++time;
            }
        }
        cout << time << endl;
    }
}
