#include <iostream>
#include <map>
#include <set>
using namespace std;

int main()
{
    for (int ncases=1, from, to; (cin >> from >> to) && from >= 0 ; ++ncases){
        map<int, int> inverse_edges;
        set<int> tree_nodes;
        bool is_tree=true;

        for (; from > 0; cin >> from >> to){
            auto it = inverse_edges.find(to);
            if (it != inverse_edges.end())
               is_tree = false;         // more than one incoming edge
            else if (is_tree) {
                inverse_edges.insert(it, make_pair(to, from));
                tree_nodes.insert(from);
            }
        }

        for (auto eit = inverse_edges.begin(); eit != inverse_edges.end() && is_tree; ++eit)
            tree_nodes.erase(eit->first);
        if (inverse_edges.size() > 0 && tree_nodes.size() != 1)
            is_tree = false;            // more than one root

        for (auto eit = inverse_edges.begin(); eit != inverse_edges.end() && is_tree; ++eit) {
            set<int> path = { eit->first };
            for (int from = eit->second; is_tree; from = inverse_edges[from])
                if (tree_nodes.find(from) != tree_nodes.end())
                    break;
                else if (path.find(from) != path.end())
                    is_tree = false;    // no path to the root
                else
                    path.insert(from);
            tree_nodes.insert(path.begin(), path.end());
        }

        cout << "Case " << ncases << " is" << (is_tree ? "" : " not") << " a tree." << endl;
    }

    return 0;
}
