#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

int main()
{
    int cases = int();
    cin >> cases;
    cin.ignore();
    cin.ignore();

    for(size_t t = 1; t <= cases; t++)
    {
        double sum = 0;
        map<string, double> trees;
        char input[30];
        while( cin.getline(input, 30) )
        {
            if(input[0] == char()) break;
            string name = input;
            trees[name]++;
            ++sum;
        }

        for(map<string, double>::iterator it = trees.begin(); it != trees.end(); ++it)
        {
            double percent = (it->second / sum) * 100;
            cout << it->first << ' ' << fixed << setprecision(4) << percent << endl;
        }
        if(t == cases) break;
        cout << endl;
    }
}
