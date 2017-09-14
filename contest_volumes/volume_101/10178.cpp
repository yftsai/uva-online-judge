// #geometry
// Explaination in details can be found in:
// http://pavelsimo.blogspot.com/2012/08/uva-10178-count-faces.html
// A more efficient algorithm may be based on Euler's formula: v - e + f = 2.
#include <iostream>
#include <map>
using namespace std;

char get_set_representation(map<char, char> &set_reps, char n)
{
    auto it = set_reps.find(n);
    if (it == set_reps.end())
        return n;
    else {
        char rep = get_set_representation(set_reps, it->second);
        it->second = rep;
        return rep;
    }
}

int main()
{
    for (int n, e; cin >> n >> e; ) {
        int face_count = 1;
        map<char, char> set_reps;
        char n1, n2;
        for (int i = 0; i < e && cin >> n1 >> n2; i++) {
            char r1 = get_set_representation(set_reps, n1);
            char r2 = get_set_representation(set_reps, n2);
            if (r1 == r2)
                face_count++;
            else
                set_reps[r2] = r1;
        }
        cout << face_count << endl;
    }
    return 0;
}
