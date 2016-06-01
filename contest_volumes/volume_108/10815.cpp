#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
    char a[53];
    string buffer;
    set<string> dic;

    for (char c= 'a'; c<='z'; c++)
        a[c-'a']=c;
    for (char c= 'A'; c<='Z'; c++)
        a[c-'A'+26]=c;
    a[52] = '\0';

    while (cin >> buffer){
        for (string::iterator it=buffer.begin(); it!=buffer.end(); it++)
            *it = tolower(*it);
        for (size_t start=0; (start = buffer.find_first_of(a, start))!=string::npos; ){
            size_t end = buffer.find_first_not_of(a, start);
            string word = buffer.substr(start, end-start);
            dic.insert(word);
            start = end;
        }
    }

    for (set<string>::iterator it=dic.begin(); it!=dic.end(); it++)
        cout << *it << endl;

    return 0;
}
