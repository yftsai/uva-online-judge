// #easy
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

bool is_transformable(const string &w1, const string &w2)
{
    if (w1.size() != w2.size())
        return false;
    else {
        int diff = 0;
        for (size_t i=0; i < w1.size(); ++i)
            diff += (w1[i] != w2[i]) ? 1 : 0;
        return diff == 1;
    }
}

int get_nstep(const vector<vector<int>> &trans, int start, int end)
{
    vector<bool> visited(trans.size(), false);
    queue<pair<int, int>> q;

    q.push(pair<int, int>(start, 0));
    visited[start] = true;
    while (!q.empty()){
        int i = q.front().first, nstep = q.front().second;
        q.pop();

        if (i == end)
            return nstep;
        else
            for (auto j: trans[i])
                if (! visited[j]) {
                    visited[j] = true;
                    q.push(pair<int, int>(j, nstep + 1));
                }
    }
    return -1;
}

int main()
{
    string line;
    getline(cin, line);
    int n = stoi(line);

    for (getline(cin, line); n>0; n--){
        map<string, size_t> indexes;
        vector<vector<int>> trans;

        while (getline(cin, line) && line != "*"){
            auto it = indexes.lower_bound(line);
            if (it == indexes.end() || it->first != line) {
                size_t i = indexes.size();
                indexes.insert(it, make_pair(line, i));
                trans.push_back(vector<int>());
                for (auto &p: indexes)
                    if (is_transformable(p.first, line)) {
                        trans[p.second].push_back(i);
                        trans[i].push_back(p.second);
                    }
            }
        }

        while (getline(cin, line) && line.size() > 0){
            string w[2];
            stringstream(line) >> w[0] >> w[1];
            cout << w[0] << " " << w[1] << " " << get_nstep(trans, indexes[w[0]], indexes[w[1]]) << endl;
        }
        if (n>1)
            cout << endl;
    }

    return 0;
}
