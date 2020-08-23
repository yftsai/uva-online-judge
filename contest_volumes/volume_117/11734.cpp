// #trivial
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string team_output, judge_output;
    getline(cin, team_output);
    const int t = stoi(team_output);
    for (int case_number = 1; case_number <= t; ++case_number) {
        getline(cin, team_output);
        getline(cin, judge_output);

        cout << "Case " << case_number << ": ";
        if (team_output == judge_output)
            cout << "Yes" << endl;
        else {
            team_output.erase(remove(team_output.begin(), team_output.end(), ' '), team_output.end());
            if (team_output == judge_output)
                cout << "Output Format Error" << endl;
            else
                cout << "Wrong Answer" << endl;
        }
    }

    return 0;
}
