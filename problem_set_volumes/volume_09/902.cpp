#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    int n;
    string text;

    while (cin >> n >> text){
        map<string, int> count;
        for (unsigned int i=0; i<text.length()-n; i++){
            string sub = text.substr(i, n);
            count.insert(pair<string, int>(sub, 0));
            count[sub]++;
        }

        map<string, int>::const_iterator pw = count.begin();
        for (map<string, int>::const_iterator it = count.begin(); it!=count.end(); it++){
            if (it->second > pw->second)
                pw = it;
        }
        cout << pw->first << endl;
    }

    return 0;
}
