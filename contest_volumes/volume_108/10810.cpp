// #sorting
#include <iostream>
using namespace std;

uint64_t merge_sort(int *const sequence, int length, int *temp, bool &is_in_sequence)
{
    if (length <= 1) {
        is_in_sequence = true;
        return 0;
    }
    else {
        int hlen = length / 2;      // length of the first half
        uint64_t swap_count = merge_sort(sequence, hlen, temp, is_in_sequence);
        int *const first = is_in_sequence ? sequence : temp;
        swap_count += merge_sort(sequence + hlen, length - hlen, temp + hlen, is_in_sequence);
        int *const second = is_in_sequence ? (sequence + hlen) : (temp + hlen);

        temp = (first == sequence) ? temp : sequence;
        is_in_sequence = !(first == sequence);
        for (int i = 0, j = 0, k = 0; i < hlen || j < length - hlen; )
            if (j >= length - hlen || (i < hlen && first[i] <= second[j]))
                temp[k++] = first[i++];
            else {
                temp[k++] = second[j++];
                swap_count += hlen - i;
            }
        return swap_count;
    }
}

int main()
{
    const int max_length = 500000;
    int sequence[max_length], temp[max_length];
    for (int n; cin >> n && n > 0; ) {
        for (int i = 0; i < n; i++)
            cin >> sequence[i];
        bool is_swapped;
        cout << merge_sort(sequence, n, temp, is_swapped) << endl;
    }
    return 0;
}
