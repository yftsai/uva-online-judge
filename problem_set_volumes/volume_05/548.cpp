// #binary_tree
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <iterator>
using namespace std;

class btree
{
    private:
        int val;
        unique_ptr<btree> left, right;

    public:
        btree(int, unique_ptr<btree>, unique_ptr<btree>);
        pair<int, int> get_leaf_with_min_path(int path = 0);
};

btree::btree(int v, unique_ptr<btree> l, unique_ptr<btree> r):
    val(v), left(move(l)), right(move(r))
{}

unique_ptr<btree> construct(vector<int> &in_vals, vector<int> &post_vals, const int *in_terminator = nullptr)
{
    if (post_vals.size()==0 || (in_terminator != nullptr && in_vals.back() == *in_terminator))
        return nullptr;
    else if (post_vals.back()==in_vals.back()) {
        int v = post_vals.back();
        post_vals.pop_back();
        in_vals.pop_back();
        unique_ptr<btree> l = construct(in_vals, post_vals, in_terminator);
        return unique_ptr<btree>(new btree(v, move(l), nullptr));
    }
    else {
        int v = post_vals.back();
        post_vals.pop_back();
        unique_ptr<btree> r = construct(in_vals, post_vals, &v);
        in_vals.pop_back();
        unique_ptr<btree> l = construct(in_vals, post_vals, in_terminator);
        return unique_ptr<btree>(new btree(v, move(l), move(r)));
    }
}

pair<int, int> btree::get_leaf_with_min_path(int path)
{
    if (left==nullptr && right==nullptr)
        return pair<int, int>(path + val, val);
    else if (left==nullptr)
        return right->get_leaf_with_min_path(path + val);
    else if (right==nullptr)
        return left->get_leaf_with_min_path(path + val);
    else {
        auto pl = left->get_leaf_with_min_path(path + val);
        auto pr = right->get_leaf_with_min_path(path + val);
        return pl < pr ? pl : pr;
    }
}

int main()
{
    string in_line, post_line;

    while (getline(cin, in_line) && getline(cin, post_line)){
        vector<int> in_vals, post_vals;

        istringstream in_ss(in_line);
        copy(istream_iterator<int>(in_ss), istream_iterator<int>(), back_inserter(in_vals));
        istringstream post_ss(post_line);
        copy(istream_iterator<int>(post_ss), istream_iterator<int>(), back_inserter(post_vals));

        unique_ptr<btree> t = construct(in_vals, post_vals);
        cout << t->get_leaf_with_min_path().second << endl;
    }

    return 0;
}
