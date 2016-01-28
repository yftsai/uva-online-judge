#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct node
{
    char ch;
    map<char, node *> child;
    node *parent, *suffix, *dictionary;
    vector<int> word_index;

    node(node *p, char c):
        ch(c),
        parent(p),
        suffix(NULL),
        dictionary(NULL)
    {
    }

    ~node()
    {
        for (auto &cc : child)
            delete cc.second;
    }
};

int main()
{
    for (int n; (cin >> n) && n!=0;) {
        string pattern[150];
        for (int i=0; i<n; i++)
            cin >> pattern[i];

        // Aho–Corasick algorithm
        node *t = new node(NULL, '\0');
        int count[150];
        for (int i=0; i<n; i++) {
            node *p = t;
            for (size_t j=0; j<pattern[i].size(); j++) {
                char c = pattern[i].at(j);
                if (p->child[c] == NULL)
                    p->child[c] = new node(p, c);
                p = p->child[c];
            }
            p->word_index.push_back(i);
            count[i] = 0;
        }

        queue<node *> q;
        for (auto &it : t->child)
            q.push(it.second);
        for (; !q.empty(); q.pop()) {
            node *n = q.front();
            for (auto &it : n->child)
                q.push(it.second);

            const char c = n->ch;
            n->suffix = t;
            for (node *p = n->parent; p->suffix != NULL; p = p->parent) {
                auto q = p->suffix->child.find(c);
                if (q != p->suffix->child.end()) {
                    n->suffix = q->second;
                    break;
                }
            }
            
            for (node *p = n->suffix; p->suffix != NULL; p = p->suffix) {
                if (p->word_index.size()>0){
                    n->dictionary = p;
                    break;
                }
            }
        }
        
        string text;
        cin >> text;
        node *p = t;
        for (char c : text) {
            while (true) {
                auto cq = p->child.find(c);
                if (cq != p->child.end()) {
                    p = cq->second;
                    break;
                }
                else if (p->suffix != NULL)
                    p = p->suffix;
                else
                    break;
            }

            for (node *q = p; q != NULL; q = q->dictionary)
                for (int i : q->word_index)
                    count[i]++;
        }

        delete t;

        int maxcount = 0;
        for (int i=0; i<n; i++)
            maxcount = max(count[i], maxcount);

        cout << maxcount << endl;
        for (int i=0; i<n; i++)
            if (count[i] == maxcount)
                cout << pattern[i] << endl;
    }

    return 0;
}
