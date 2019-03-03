// #cycle_detection
#include <iostream>
using namespace std;

int main()
{
    auto next = [](uint32_t v) { return ((v * v) / 100u) % 10000u; };

    for (uint32_t a; cin >> a && a != 0; ) {
        uint32_t b = a;
        for (uint32_t c = next(next(b)); b != c; b = next(b), c = next(next(c)))
            ;

        uint32_t count = 1u;
        for (uint32_t c = next(b); b != c; c = next(c))
            ++count;

        b = a;
        for (uint32_t i = 0; i < count; ++i)
            b = next(b);
        for (; a != b; a = next(a), b = next(b))
            ++count;

        cout << count << endl;
    }
    return 0;
}
