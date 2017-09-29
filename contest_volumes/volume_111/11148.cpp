// #easy
#include <iostream>
#include <string>
using namespace std;

int get_int(const string &line, size_t &i)
{
    size_t len = 1;
    for (; i + len < line.size() && isdigit(line[i + len]); len++)
        ;
    string n(line.begin() + i, line.begin() + i + len);
    i += len;
    return stoi(n);
}

int gcd(int n, int m)
{
    if (n % m == 0)
        return m;
    else
        return gcd(m, n % m);
}

int main()
{
    string line;
    getline(cin, line);
    for (int t = stoi(line); t > 0 && getline(cin, line); t--) {
        int num = 1, den = 1;
        for (size_t i = 0; i < line.size(); i++)
            if (isdigit(line[i])) {
                int n = get_int(line, i);

                if (i == line.size() || line[i] == ' ')
                    num *= n;
                else if (line[i] == '/') {
                    i++;
                    num *= n;
                    den *= get_int(line, i);
                }
                else if (line[i] == '-' && isdigit(line[i + 1])) {
                    i++;
                    int m = get_int(line, i);
                    i++;
                    int d = get_int(line, i);
                    num *= n * d + m;
                    den *= d;
                }
                i--;

                int g = gcd(num, den);
                num /= g;
                den /= g;
            }

        if (num % den == 0)
            cout << (num / den) << endl;
        else if (num > den)
            cout << (num / den) << "-" << (num % den) << "/" << den << endl;
        else
            cout << num << "/" << den << endl;
    }

    return 0;
}
