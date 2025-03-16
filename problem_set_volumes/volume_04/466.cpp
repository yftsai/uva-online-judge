// #trivial
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

void rotate(uint16_t n, string &pattern, string &temp)
{
    for (uint16_t r = 0; r < n; r++)
        for (uint16_t c = 0; c < n; c++)
            temp[n * c + (n - 1 - r)] = pattern[n * r + c];
    pattern.swap(temp);
}

void reflect(uint16_t n, string &pattern)
{
    for (uint16_t r = 0; r < n - 1 - r; r++)
        for (uint16_t c = 0; c < n; c++)
            swap(pattern[n * r + c], pattern[n * (n - 1 - r) + c]);
}

void print_matching(uint16_t n, string &pattern, string &temp, const string &transformed)
{
    temp.resize(pattern.size());
    if (pattern == transformed) {
        cout << "preserved.";
        return;
    }
    for (uint16_t i = 1; i <= 3; i++) {
        rotate(n, pattern, temp);
        if (pattern == transformed) {
            cout << "rotated " << (90 * i) << " degrees.";
            return;
        }
    }

    rotate(n, pattern, temp);
    reflect(n, pattern);
    if (pattern == transformed) {
        cout << "reflected vertically.";
        return;
    }

    for (uint16_t i = 1; i <= 3; i++) {
        rotate(n, pattern, temp);
        if (pattern == transformed) {
            cout << "reflected vertically and rotated " << (90 * i) << " degrees.";
            return;
        }
    }

    cout << "improperly transformed.";
}

int main()
{
    string original, transformed, temp, line;
    for (uint32_t size, p = 1; cin >> size; p++) {
        original.clear();
        transformed.clear();
        for (uint16_t i = 0; i < size; i++) {
            cin >> line;
            original.append(line);
            cin >> line;
            transformed.append(line);
        }

        cout << "Pattern " << p << " was ";
        print_matching(size, original, temp, transformed);
        cout << endl;
    }
    return 0;
}
