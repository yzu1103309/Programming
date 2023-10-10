#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main()
{
    size_t cases;
    cin >> cases;
    for(size_t t = 0; t < cases; ++t)
    {
        int B, SG, SB;
        cin >> B >> SG >> SB;
        multiset<int> Green;
        multiset<int> Blue;
        for(int i = 0; i < SG; ++i)
        {
            int input;
            cin >> input;
            Green.insert(input);
        }
        for(int i = 0; i < SB; ++i)
        {
            int input;
            cin >> input;
            Blue.insert(input);
        }

        //battle starts
        while(!Blue.empty() && !Green.empty())
        {
            //the power of alive ones
            vector<int> reB;
            vector<int> reG;

            //battlefields
            for(int i = 0; i < B && !Blue.empty() && !Green.empty(); ++i)
            {
                auto itG = --Green.end();
                auto itB = --Blue.end();
                if(*itG > *itB)
                {
                    reG.push_back(*itG - *itB);
                }
                else if(*itG < *itB)
                {
                    reB.push_back(*itB - *itG);
                }
                Green.erase(itG);
                Blue.erase(itB);
            }
            for(size_t s = 0; s < reG.size(); s++)
            {
                Green.insert(reG[s]);
            }
            for(size_t s = 0; s < reB.size(); s++)
            {
                Blue.insert(reB[s]);
            }
        }
        if(Green.empty() && Blue.empty())
            cout << "green and blue died" << endl;
        else if(!Blue.empty())
        {
            cout << "blue wins" << endl;
            for(auto it = Blue.rbegin(); it != Blue.rend(); ++it)
            {
                cout << *it << endl;
            }
        }
        else
        {
            cout << "green wins" << endl;
            for(auto it = Green.rbegin(); it != Green.rend(); ++it)
            {
                cout << *it << endl;
            }
        }
        if(t != cases - 1)
            cout << endl;
    }
}
