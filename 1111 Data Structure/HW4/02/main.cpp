#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

int main()
{
    map<string, string> Dic;
    string all, en, un;

    while( getline(cin, all, '\n') )
    {
        if(all[0] == char()) break;

        stringstream line(all);

        getline(line, en, ' ');
        getline(line, un, '\n');
        Dic[un] = en;
    }
    while(cin >> all)
    {
        if(!Dic[all].empty())
            cout << Dic[all] << endl;
        else
            cout << "eh" << endl;
    }
}

