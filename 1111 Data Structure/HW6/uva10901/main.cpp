#include <iostream>
#include <queue>
using namespace std;

struct car
{
    int arrive; //arrival time
    int unload = 0;
};

int main()
{
    int c;
    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int time,n,m; //n: capacity; m lines of command
        cin >> n >> time >> m;
        int current = 0; //even: left; odd: right;
        int spent = 0;
        vector<size_t> order;
        vector<car> cars[2];
        size_t pos[2] = {0, 0};
        for(int k = 0; k < m; ++k)
        {
            int minute;
            string bank;
            car tmp;
            cin >> minute >> bank;
            tmp.arrive = minute;
            if(bank == "left")
            {
                order.emplace_back(0);
                cars[0].emplace_back(tmp);
            }
            else if(bank == "right")
            {
                order.emplace_back(1);
                cars[1].emplace_back(tmp);
            }
        }

        spent = cars[order.front()].front().arrive; //the set off time

        while(pos[0] < cars[0].size() || pos[1] < cars[1].size())
        {
            spent += time; //the ferry must go to the other side
            size_t side = current % 2;
            size_t *p = &pos[side];
            size_t oside = (current+1)%2;
            size_t *op = &pos[oside];
            for(size_t t = 0; t < n; ++t)
            {
                if(*p < cars[side].size() && cars[side].at(*p).arrive <= spent - time)
                {
                    cars[side].at(*p).unload = spent;
                    ++(*p);
                }
                else if(t == 0)
                {
                    if(*p < cars[side].size() && *op < cars[oside].size())
                    {
                        if(cars[side].at(*p).arrive < cars[oside].at(*op).arrive && cars[side].at(*p).arrive >= spent)
                        {
                            spent = cars[side].at(*p).arrive;
                            --current;
                        }
                        else if(cars[oside].at(*op).arrive >= spent)
                        {
                            spent = cars[oside].at(*op).arrive + time;
                        }
                    }
                    else if(*p < cars[side].size() && cars[side].at(*p).arrive >= spent)
                    {
                        spent = cars[side].at(*p).arrive;
                        --current;
                    }
                    else if(*op < cars[oside].size() && cars[oside].at(*op).arrive >= spent)
                        spent = cars[oside].at(*op).arrive + time;
                    break;
                }
                else
                    break;
            }
            ++current;
        }
        pos[0] = 0; pos[1] = 0;
        for(size_t t = 0; t < order.size(); ++t)
        {
            cout << cars[order[t]].at(pos[order[t]]).unload << endl;
            ++pos[order[t]];
        }
        if(i < c - 1) cout << endl;
    }
}
