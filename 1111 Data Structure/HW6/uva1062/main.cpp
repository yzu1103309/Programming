#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    size_t count = 1;
    string input;

    while(cin >> input)
    {
        if(input == "end") break;

        vector<int> stack_top;
        vector<char> same_stack;

        for(size_t t = 0; t < input.size(); ++t)
        {
            if(stack_top.empty()) stack_top.push_back(input[t]); //create a new stack
            else{
                size_t pos = -1;
                int min = 300;
                for(size_t s = 0; s < stack_top.size(); ++s)
                {
                    if(input[t] <= stack_top[s])
                    {
                        if(stack_top[s] <= min)
                        {
                            min = stack_top[s];
                            pos = s;
                        }
                    }
                }
                if(pos == -1) stack_top.push_back(input[t]);
                else stack_top[pos] = input[t];
            }

            if(same_stack.empty()) same_stack.push_back(input[t]);
            else
            {
                bool duplicate = false;
                for(size_t s = 0; s < same_stack.size(); ++s)
                {
                    if(input[t] == same_stack[s])
                    {
                        duplicate = true;
                        break;
                    }
                }
                if(!duplicate)
                    same_stack.push_back(input[t]);
            }
        }
        size_t better = (stack_top.size() < same_stack.size())? stack_top.size() : same_stack.size();
        cout << "Case " << count << ": " << better << endl;

        count++;
    }
}
