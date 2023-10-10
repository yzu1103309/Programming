#include <iostream>
#include <set>
using namespace std;

int main()
{
    int days;
    while(cin >> days && days != 0)
    {
        multiset<int> bills;
        unsigned long total = 0;
        for(int t = 0; t < days; ++t)
        {
            int count;
            cin >> count;
            for(int i = 0; i < count; ++i)
            {
                unsigned long amount;
                cin >> amount;
                bills.insert(amount);
            }
            auto itB = --bills.end();
            auto itS = bills.begin();
            total += *itB - *itS;
            bills.erase(itB);
            bills.erase(itS);
        }
        cout << total << endl;
    }
}
