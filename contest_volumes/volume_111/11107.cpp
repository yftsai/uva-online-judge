#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

class suffix
{
    private:
        const char *str;
        size_t pos;
    public:
        suffix(const char *s = nullptr, size_t p = 0);
        char operator[](size_t p) const;
        const char *term() const;
};

suffix::suffix(const char *s, size_t p):
    str(s), pos(p)
{
}

char suffix::operator[](size_t p) const
{
    return str[pos+p];
}
        
const char *suffix::term() const
{
    return str;
}

void longest_common_string(
    suffix *src, size_t len, suffix *tmp,
    string prefix,
    size_t mincount, set<string> &lcs)
{
    set<const char *> term;
    for (size_t i=0; i<len; i++)
        term.insert(src[i].term());
    if (term.size()<mincount)
        return;

    size_t depth = prefix.length();
    set<char> bucket;
    map<char, size_t> count, index;
    for (size_t i=0; i<len; i++) {
        char c = src[i][depth];
        bucket.insert(c);
        if (count.find(c)==count.end())
            count.insert(pair<char, size_t>(c, 1));
        else
            count.find(c)->second++;
    }

    size_t cnt = 0;
    for (char c: bucket) {
        index.insert(pair<char, size_t>(c, cnt));
        cnt += count.find(c)->second;
    }

    for (size_t i=0; i<len; i++) {
        char c = src[i][depth];
        size_t &j = index.find(c)->second;
        tmp[j] = src[i];
        j++;
    }

    for (char c: bucket)
        if (c!='\0') {
            size_t j = index.find(c)->second; 
            size_t k = count.find(c)->second;
            longest_common_string(tmp + j - k, k, src + j - k, prefix+c, mincount, lcs);
        }

    if (lcs.size()==0 || lcs.begin()->length() < prefix.length()) {
        lcs.clear();
        lcs.insert(prefix);
    }
    else if (lcs.begin()->length()==prefix.length())
        lcs.insert(prefix);
}

int main()
{
    bool is_first = true;
    
    for (int n; (cin >> n) && n!=0; is_first = false) {
        vector<string> str;
        vector<suffix> suf, tmp;
        str.resize(n);
        for (int i=0; i<n; i++) {
            cin >> str[i];
            for (size_t j=0; j<str[i].length(); j++)
                suf.push_back(suffix(str[i].c_str(), j));
        }
        tmp.resize(suf.size());

        set<string> lcs;
        longest_common_string(&suf[0], suf.size(), &tmp[0], "", str.size()/2+1, lcs);

        if (!is_first)
            cout << endl;
        if (lcs.size()==0 || lcs.begin()->length()==0)
            cout << "?" << endl;
        else
            for (const auto &s : lcs)
                cout << s << endl;
    }
    return 0;
}
