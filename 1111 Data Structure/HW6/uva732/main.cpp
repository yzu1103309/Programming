#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

int main()
{
    string source, result;
    while(cin >> source >> result)
    {
        stack<char> ST;
        priority_queue<string> output;
        string tmp;
        if(source.size() != result.size())
        {
            cout << '[' << endl << ']' << endl;
            break;
        }

        size_t length = source.size();

        for(size_t s = 1; s <= length; ++s)
        {
            for(size_t t = 0; t < s; ++t)
            {
                ST.push(source[t]);
                tmp.push_back('i');
            }
            if(ST.top() != result.front()) break;
            else{ ST.pop(); tmp.push_back('o'); }

        }
    }
}
