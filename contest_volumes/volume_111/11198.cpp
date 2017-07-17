// breadth_first_search
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main()
{
    const set<int> primes = {2, 3, 5, 7, 11, 13};
    vector<int> digits(8);

    for (int case_number = 1; cin >> digits[0] && digits[0] != 0; case_number++) {
        for (int i=1; i<8; i++)
            cin >> digits[i];

        set<int> male;
        for (int i=0; i<8; i++)
            if (digits[i] > 0)
                male.insert(digits[i]);
            else
                digits[i] *= -1;

        int v = 0;
        for (int i = 8, b = 1; i>0; i--, b*=10)
            v += digits[i-1] *b;

        const int INVALID_COUNT = -1;
        int min_dance_count = (v == 12345678) ? 0 : INVALID_COUNT;
        queue<pair<int, int>> q(deque<pair<int, int>>({pair<int, int>(v, 0)})); // value_of_digits, dance_count
        set<int> s = {v};

        while (!q.empty() && min_dance_count == INVALID_COUNT) {
            int v = q.front().first;
            int dance_count = q.front().second;
            q.pop();

            for (int i = 8, b_i = 1; i > 0; i--, b_i*=10)
                for (int j = i-1, b_j = b_i*10; j>0; j--, b_j*=10) {
                    // it is more efficient to use shift operations if the values are properly encoded
                    int prefix = v /b_j /10;
                    int d_j = v /b_j %10;
                    int seq_ji = v %b_j /b_i /10;
                    int d_i = v /b_i %10;
                    int suffix = v %b_i;

                    if ((male.find(d_j) == male.end()) != (male.find(d_i) == male.end())
                        && primes.find(d_j + d_i) != primes.end()) {
                        int vs[] = {
                            prefix *b_j *10 + d_j *b_j + d_i *b_j /10 + seq_ji *b_i + suffix,
                            prefix *b_j *10 + d_i *b_j + d_j *b_j /10 + seq_ji *b_i + suffix,
                            prefix *b_j *10 + seq_ji *b_i *100 + d_j *b_i *10 + d_i *b_i + suffix,
                            prefix *b_j *10 + seq_ji *b_i *100 + d_i *b_i *10 + d_j *b_i + suffix };
                        for (auto v: vs)
                            if (v == 12345678)
                                min_dance_count = dance_count + 1;
                            else if (s.find(v) == s.end())
                                s.insert(v), q.push(pair<int, int>(v, dance_count+1));
                    }
                }
        }

        cout << "Case " << case_number << ": " << min_dance_count << endl;
    }

    return 0;
}
