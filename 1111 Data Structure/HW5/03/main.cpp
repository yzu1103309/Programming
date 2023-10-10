#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct query
{
    int id = int();
    int sec = int();
    query(int q, int s)
    :id(q), sec(s){};
    bool operator >(query const& q2) const
    {
        if(sec == q2.sec) return id > q2.id;
        return sec > q2.sec;
    }
};

int main()
{
    priority_queue<query, vector<query>, greater<query>> list;
    vector<query> command;
    string dump;
    while(cin >> dump)
    {
        if(dump[0] == '#') break;
        int q, s;
        cin >> q >> s;
        command.emplace_back(query(q, s));
        list.emplace(query(q, s));
    }
    int count;
    cin >> count;

    for(int i = 1; i <= count; ++i)
    {
        for(size_t t = 0; t < command.size(); ++t)
        {
            list.emplace(query(command[t].id,command[t].sec * (i+1) ));
        }
    }

    for(int i = 0; i < count; ++i)
    {
        cout << list.top().id << endl;
        list.pop();
    }
}
