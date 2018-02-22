// #iterative_deepening_a_star
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

const vector<pair<char, int>> steps = {
    make_pair('U', -4),
    make_pair('D', 4),
    make_pair('L', -1),
    make_pair('R', 1)};

bool is_solvable(const string &frame, int s)
{
    int inverse_count = 0;
    for (int i = 0; i < int(frame.size()); ++i)
        for (int j = i+1; j < int(frame.size()); ++j)
            if (i != s && j != s)
                inverse_count += (frame[i] > frame[j]) ? 1 : 0;
    return ((s/4)%2 == 1) != (inverse_count%2 == 1);
}

int get_min_steps(const string &frame, int s)
{
    int steps = 0;
    for (int i = 0; i < int(frame.size()); ++i)
        if (i != s)
            steps += abs(i/4 - (frame[i]-'A')/4) + abs(i%4 - (frame[i]-'A')%4);
    return steps;
}

bool search(string &frame, int s, int bound, set<string> &states, int &min_steps, string &path)
{
    int h = get_min_steps(frame, s);
    if (h == 0)
        return true;
    else if (states.find(frame) != states.end())
        return false;
    else if (int(path.size()) + h > bound) {
        min_steps = min(min_steps, (int)path.size() + get_min_steps(frame, s));
        return false;
    }
    else {
        states.insert(frame);
        for (const pair<char, int> &step: steps) {
            int t = s + step.second;
            if (0 <= t && t < 16 && (t%4==s%4) != (t/4==s/4)) {
                swap(frame[s], frame[t]);
                path.push_back(step.first);
                if (search(frame, t, bound, states, min_steps, path))
                    return true;
                path.pop_back();
                swap(frame[s], frame[t]);
            }
        }
        states.erase(frame);
        return false;
    }
}

bool search(string &frame, int s, string &path)
{
    set<string> states;
    for (int bound = get_min_steps(frame, s), min_steps; bound < 46; bound = min_steps)
        if (search(frame, s, bound, states, min_steps = 46, path))
            return true;
    return false;
}

int main()
{
    int n;
    for (cin >> n; n>0; n--) {
        string frame(16, ' ');
        int s = 0;
        for (int i=0, j; i<16 && cin >> j; ++i)
            if (j == 0)
                s = i;
            else
                frame[i] = char('A' + j - 1);

        string path;
        if (is_solvable(frame, s) && search(frame, s, path))
            cout << path << endl;
        else
            cout << "This puzzle is not solvable." << endl;
    }
    return 0;
}
