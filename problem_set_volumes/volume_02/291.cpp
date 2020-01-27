// #easy
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void enumerate(uint16_t n, string &sequence, vector<vector<uint16_t>> &graph)
{
    if (sequence.size() == 9)
        cout << sequence << endl;
    else if (graph[n].size() > 0) {
        for (uint16_t i = 0; i < graph[n].size(); ++i) {
            const uint16_t m = graph[n][i];
            sequence.push_back('1' + m);

            remove(graph[n].begin(), graph[n].end(), m);
            graph[n].pop_back();
            remove(graph[m].begin(), graph[m].end(), n);
            graph[m].pop_back();
            enumerate(m, sequence, graph);

            sequence.pop_back();
            graph[n].push_back(m);
            sort(graph[n].begin(), graph[n].end());
            graph[m].push_back(n);
            sort(graph[m].begin(), graph[m].end());
        }
    }
}

int main()
{
   vector<vector<uint16_t>> graph = {
        { 1, 2, 4 },
        { 0, 2, 4 },
        { 0, 1, 3, 4 },
        { 2, 4 },
        { 0, 1, 2, 3 }
    };
    string sequence = "1";

    enumerate(0, sequence, graph);

    return 0;
}
