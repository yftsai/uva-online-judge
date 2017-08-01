// #dynamic_programming
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int ncases;
    for (cin >> ncases; ncases>0; --ncases) {
        uint32_t ferry_length;
        vector<uint32_t> car_lengths;
        cin >> ferry_length;
        ferry_length *= 100;
        // The ferry could only accommodate up to 200 cars.
        for (int car_length; (cin >> car_length) && car_length!=0; )
            if (car_lengths.size() < 200)
                car_lengths.push_back(car_length);

        vector<int> total_lengths;
        vector<vector<bool>> left_states;
        left_states.reserve(car_lengths.size());
        if (car_lengths.size() > 0 && car_lengths[0] <= ferry_length) {
            int car_length = car_lengths[0];
            total_lengths.push_back(car_length);
            left_states.emplace_back(car_length + 1, false);
            left_states[0][car_length] = true;
        }
        for (size_t i = 1; i < car_lengths.size() && i == left_states.size(); ++i) {
            int car_length = car_lengths[i];
            total_lengths.push_back(total_lengths.back() + car_length);
            left_states.emplace_back(min<size_t>(ferry_length + 1, left_states[i-1].size() + car_length), false);

            for (size_t left_length = 0, right_length = total_lengths.back(); left_length < left_states[i-1].size(); ++left_length, --right_length)
                if (left_states[i-1][left_length]) {
                    if (left_length + car_length < left_states[i].size())
                        left_states[i][ left_length + car_length ] = true;
                    if (right_length <= ferry_length)
                        left_states[i][left_length] = true;
                }

            if (find(left_states[i].begin(), left_states[i].end(), true) == left_states[i].end())
                total_lengths.pop_back(), left_states.pop_back();
        }

        cout << left_states.size() << endl;
        vector<string> directions;
        if (left_states.size() > 0) {
            int left_length = find(left_states.back().begin(), left_states.back().end(), true) - left_states.back().begin();
            for (int i=int(left_states.size())-1; i>=0; --i) {
                int car_length = car_lengths[i];
                if (i==0 || (left_length >= car_length && left_states[i-1][left_length - car_length]))
                    directions.push_back("port"), left_length -= car_length;
                else
                    directions.push_back("starboard");
            }
            reverse(directions.begin(), directions.end());
        }
        for (auto s: directions)
            cout << s << endl;
        if (ncases > 1)
            cout << endl;
    }

    return 0;
}
