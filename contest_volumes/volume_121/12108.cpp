// #cycle_detection
#include <iostream>
using namespace std;

int main()
{
    for (uint16_t case_number = 1, n; cin >> n && n > 0; case_number++) {
        uint16_t as[10], bs[10], student_states[10];
        for (uint16_t i = 0; i < n && cin >> as[i] >> bs[i] >> student_states[i]; i++)
            student_states[i]--;

        auto get_awake_count = [&n, &as] (uint16_t student_states[10]) {
            uint16_t awake_count = 0;
            for (uint16_t i = 0; i < n; i++)
                if (student_states[i] < as[i])
                    awake_count++;
            return awake_count;
        };
        auto next = [&] (uint16_t student_states[10]) {
            uint16_t awake_count = get_awake_count(student_states);
            for (uint16_t i = 0; i < n; i++)
                if (student_states[i] + 1 == as[i])
                    student_states[i] = (n - awake_count > awake_count) ? (student_states[i] + 1) : 0;
                else
                    student_states[i] = (student_states[i] + 1) % (as[i] + bs[i]);
            return student_states;
        };


        if (get_awake_count(student_states) == n)
            cout << "Case " << case_number << ": " << 1 << endl;
        else {
            uint16_t t, awake_count;
            decltype(student_states) lagged_states;
            for (uint16_t i = 0; i < n; i++)
                lagged_states[i] = student_states[i];
            for (next(student_states), t = 2; (awake_count = get_awake_count(student_states)) < n; t++) {
                bool has_cycle = true;
                for (uint16_t i = 0; i < n; i++)
                    has_cycle = has_cycle && (student_states[i] == lagged_states[i]);
                if (has_cycle)
                    break;
                else {
                    next(student_states);
                    if (t % 2 == 0)
                        next(lagged_states);
                }
            }

            if (awake_count == n)
                cout << "Case " << case_number << ": " << t << endl;
            else
                cout << "Case " << case_number << ": " << -1 << endl;
        }
    }
    return 0;
}
