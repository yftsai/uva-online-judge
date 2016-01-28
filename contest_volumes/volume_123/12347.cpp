#include <iostream>
#include <memory>
using namespace std;

class bst
{
    private:
        unsigned int value;
        unique_ptr<bst> left, right;
    public:
        bst(unsigned int);
        void insert(unsigned int);
        void print(ostream &) const;
};

bst::bst(unsigned int v):
    value(v)
{
}

void bst::insert(unsigned int v)
{
    auto &subtree = v < value ? left : right;
    if (v != value)
        if (subtree == nullptr)
            subtree.reset(new bst(v));
        else
            subtree->insert(v);
}

void bst::print(ostream &os) const
{
    if (left != nullptr)
        left->print(os);
    if (right != nullptr)
        right->print(os);
    cout << value << endl;
}

int main()
{
    unique_ptr<bst> root;
    
    for (int v; cin >> v; )
        if (root == nullptr)
            root.reset(new bst(v));
        else
            root->insert(v);

    if (root != nullptr)
        root->print(cout);
    
    return 0;
}
