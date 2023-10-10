#include <iostream>
#include <list>
using namespace std;

int main()
{
    list<char> text;
    char in;
    auto cursor = text.begin();
    while(cin.get(in))
    {
        if(in == '[')
            cursor = text.begin();
        else if(in == ']')
            cursor = text.end();
        else
        {
            if(in == '\n')
            {
                for (auto it = text.begin(); it != text.end(); ++it)
                    cout << *it;

                text.clear();
                cursor = text.begin();
                cout << endl;
            }
            else text.insert(cursor, in);
        }
    }
}
