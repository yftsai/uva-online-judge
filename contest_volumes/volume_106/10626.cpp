// #greedy
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void insert_1_5(int16_t times, int16_t *c, int16_t *n1, int16_t *n5)
{
    *c -= times;
    *n1 -= 3 * times;
    *n5 -= times;
}

void insert_1_10(int16_t times, int16_t *c, int16_t *n1, int16_t *n5, int16_t *n10)
{
    *c -= times;
    *n1 -= 3 * times;
    *n5 += times;
    *n10 -= times;
}
void insert_10(int16_t times, int16_t *c, int16_t *n1, int16_t *n10)
{
    *c -= times;
    *n1 += 2 * times;
    *n10 -= times;
}

void insert_5(int16_t times, int16_t *c, int16_t *n1, int16_t *n5)
{
    *c -= times;
    *n1 += 2 * times;
    *n5 -= 2 * times;
}

int main()
{
    uint16_t test_count;
    for (cin >> test_count; test_count > 0; --test_count) {
        int16_t c, n1, n5, n10;
        cin >> c >> n1 >> n5 >> n10;

        int16_t min_insertion_count = 8 * c;

        // 10-valued coins should be used up as much as possible. If a solution
        // includes an insertion of coins other than a single 10-valued coin
        // and there is any 10-valued coin left. This solution is not optimal
        // as that insertion can be replaced by inserting one 10-valued coin.
        //
        // Inserting a single 10-valued coin is independent of other insertions, so
        // the number of these insertions can be decided first.
        for (int16_t c_10 = 0; min(c, n10) >= 0; insert_10(1, &c, &n1, &n10), ++c_10) {
            // The left 10-valued coins should be used in the other way:
            // inserting three 1-valued coins and then one 10-valued coin. The
            // problem is that there may not be sufficient amount of 1-valued
            // coins. In this case, inserting two 5-valued coins to get more
            // 1-valued coins.
            int16_t c_1_10 = 0, c_5 = 0;
            while (min(c, n10) > 0 && (n1 >= 3 || n5 >= 2))
                if (n1 >= 3) {
                    const int16_t t = min<int16_t>(min(c, n10), n1 / 3);
                    insert_1_10(t, &c, &n1, &n5, &n10);
                    c_1_10 += t;
                }
                else {
                    insert_5(1, &c, &n1, &n5);
                    c_5 += 1;
                }

            // At this point, 10-valued coins should be used as much as possible.
            if (min(c, n10) == 0) {
                // With only 1-valued and 5-valued coins to consider, inserting
                // three 1-valued coins and then one 5-valued coin is better
                // than inserting two 5-valued coins if 5-valued coins are no
                // more than the cokes to buy.
                //
                // If there are more 5-valued coins, use two of them at a time
                // until the count of them is no more than the count of cokes to
                // buy.
                if (n5 > c) {
                    const int16_t t = min<int16_t>(c, n5 - c);
                    insert_5(t, &c, &n1, &n5);
                    c_5 += t;
                }

                // Insert by the ``better'' way as much as possible.
                // Similarly, there may not be enough 1-valued coins. In this
                // case, insert two 5-valued coins instead to get more 1-valued
                // coins.
                int c_1_5 = 0;
                while (min(c, n5) > 0)
                    if (n1 >= 3) {
                        const int16_t t = min<int16_t>(min(c, n5), n1 / 3);
                        insert_1_5(t, &c, &n1, &n5);
                        c_1_5 += t;
                    }
                    else {
                        insert_5(1, &c, &n1, &n5);
                        c_5 += 1;
                    }

                const int16_t insertion_count =
                    c_10 + c_1_10 * 4 + c_5 * 2 + c_1_5 * 4 + c * 8;
                min_insertion_count = min(min_insertion_count, insertion_count);

                insert_1_5(-c_1_5, &c, &n1, &n5);
            }

            insert_5(-c_5, &c, &n1, &n5);
            insert_1_10(-c_1_10, &c, &n1, &n5, &n10);
        }

        cout << min_insertion_count << endl;
    }

    return 0;
}
