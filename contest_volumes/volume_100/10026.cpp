// Assuming an order of jobs, swapping any adjacent jobs doesn't change the
// fines of other jobs. By considering all possible swaps to minimize the
// total fines, it is essentially a sorting problem.
#include <iostream>
#include <tuple>
#include <algorithm>
using namespace std;

int main()
{
    typedef tuple<int, int, int> job;   // job ID, time, fine
    auto cmp = [](const job &t, const job &s) {
        return get<2>(s) * get<1>(t) < get<2>(t) * get<1>(s);
    };

    int case_count, job_count;
    job jobs[1000];
    for (cin >> case_count; case_count > 0; case_count--){
        cin >> job_count;
        for (int i = 0; i < job_count; i++) {
            get<0>(jobs[i]) = i + 1;
            cin >> get<1>(jobs[i]) >> get<2>(jobs[i]);
        }

        stable_sort(jobs, jobs + job_count, cmp);
        for (int i = 0; i < job_count - 1; i++)
            cout << get<0>(jobs[i]) << " ";
        cout << get<0>(jobs[job_count-1]) << endl;
        if (case_count > 1)
            cout << endl;
    }

    return 0;
}
