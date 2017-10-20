// #easy
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    uint32_t case_number = 1;
    for (uint16_t n, m; cin >> n &&  n > 0; case_number++) {
        int numbers[n], q;
        for (auto &num: numbers)
            cin >> num;
        sort(numbers, numbers + n);

        cin >> m;
        cout << "Case " << case_number << ":" << endl;
        for (; m > 0 && cin >> q; m--) {
            uint16_t i = 0;
            uint16_t j = max<uint16_t>(1, min<uint16_t>(n - 1, upper_bound(numbers, numbers + n, q) - numbers));
            int sum = numbers[i] + numbers[j];
            while (i + 1 < j && sum != q) {
                if (numbers[i] + numbers[j] < q)
                    i++;
                else
                    j--;
                sum = (abs(numbers[i] + numbers[j] - q) < abs(sum - q)) ? (numbers[i] + numbers[j]) : sum;
            }
            cout << "Closest sum to " << q << " is " << sum << "." << endl;
        }
    }
    return 0;
}
