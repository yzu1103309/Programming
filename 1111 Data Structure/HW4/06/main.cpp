#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int cases;
    cin >> cases;
    for(int i = 0; i < cases; ++i)
    {
        int count;
        cin >> count;
        vector<int> snow;
        unordered_set<int> uni;
        int max = 0;
        for(int k = 0; k < count; k++)
        {
            int input;
            cin >> input;
            while(uni.count(input))
            {
                uni.erase(*snow.begin());
                snow.erase(snow.begin());
            }

            uni.insert(input);
            snow.push_back(input);

            if(uni.size() > max)
                max = snow.size();
        }
        cout << max << endl;
    }
}