#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    int num;
    while(cin >> num && num != 0)
    {
        map<vector<int>, int> pop;
        vector< vector<int> > person(num);
        for(int i = 0; i < num; i++) //5 people
        {
            for(size_t t = 0; t < 5; t++) //5 courses
            {
                int course;
                cin >> course;
                person[i].push_back(course);
            }

            //sorting process
            //can be replaced by sort(person[i].begin(), person[i].end());
            /**/
            size_t wall = 0;
            while(wall < 4)
            {
                int min = person[i][wall];
                size_t pos = wall;
                for(size_t t = wall + 1; t < 5; t++)
                {
                    if(person[i][t] < min)
                    {
                        min = person[i][t];
                        pos = t;
                    }
                }
                if(pos != wall)
                {
                    int tmp = person[i][wall];
                    person[i][wall] = person[i][pos];
                    person[i][pos] = tmp;
                }
                wall++;
            }

            ++pop[person[i]];
        }
        int max = 0, total = 0;
        for(auto it = pop.begin(); it != pop.end(); ++it)
        {
            if(it->second > max) max = it->second;
        }
        for(auto it = pop.begin(); it != pop.end(); ++it)
        {
            if(it->second == max) total += max;
        }
        cout << total << endl;
    }
}
