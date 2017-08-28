// #dynamic_programming
// On IA-32/64, the right operands of shifting operations is limited to the bit count, i.e. 0 - (2**c-1).
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main()
{
    int case_count;
    for (cin >> case_count; case_count > 0; case_count--) {
        uint16_t n, person_ws[100];
        cin >> n;
        for (uint16_t i = 0; i < n; i++)
            cin >> person_ws[i];
        if (n % 2 == 1)
            person_ws[n++] = 0;

        typedef uint64_t weights;
        const uint8_t bit_count = sizeof(weights) * 8;
        vector<weights> team_ws[51];        // people count -> team weight bits
        team_ws[0].push_back(1);            // weight = 0
        for (int i = 0; i < n; i++) {
            const uint16_t gshift = person_ws[i] / bit_count;
            const uint16_t bshift = person_ws[i] % bit_count;
            for (int16_t count = min(i, n/2 - 1); count >= 0; count--) {
                const vector<weights> &ws = team_ws[count];
                if (bshift == 0 || (ws.back() >> (bit_count - bshift)) == 0)
                    team_ws[count + 1].resize(max(team_ws[count + 1].size(), ws.size() + gshift), 0);
                else
                    team_ws[count + 1].resize(max(team_ws[count + 1].size(), ws.size() + gshift + 1), 0);

                for (size_t j = 0; j < team_ws[count].size(); j++) {
                    // less significant bits
                    team_ws[count + 1][j + gshift] |= team_ws[count][j] << bshift;
                    // more significant bits
                    if (j + gshift + 1 < team_ws[count + 1].size() && bshift > 0)
                        team_ws[count + 1][j + gshift + 1] |= team_ws[count][j] >> (bit_count - bshift);
                }
            }
        }

        const vector<weights> &ws = team_ws[n/2];
        uint16_t total_weight = accumulate(person_ws, person_ws + n, 0), w;
        for (w = total_weight /2; (ws[w /bit_count] & (weights(1) << (w %bit_count))) == 0; w--)
            ;
        cout << w << " " << (total_weight - w) << endl;
        if (case_count > 1)
            cout << endl;
    }

    return 0;
}
