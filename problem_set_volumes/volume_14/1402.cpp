// #splay_tree
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

template<typename T>
class tree
{
    private:
        typedef unique_ptr<tree<T>> ptr;

        T value;
        ptr left, right;
        size_t size;
        T minv;
        bool reversed;

        void reverse();
        T remove_right();
        void rotate_left();
        void rotate_right();

    public:
        tree(T v, ptr lt = nullptr, ptr rt = nullptr, bool r = false);
        tree(T* ptr, size_t length, bool r = false);

        void splay_min();
        void reverse_prefix();
        void remove_root();

        size_t get_prefix_length() const;
};

template<typename T>
tree<T>::tree(T v, ptr lt, ptr rt, bool r):
    value(v),
    left(move(lt)),
    right(move(rt)),
    reversed(r)
{
    size = 1 + (left == nullptr ? 0 : left->size) + (right == nullptr ? 0 : right->size);
    minv = min(value, (left == nullptr || left->size == 0) ? value : left->minv);
    minv = min(minv, (right == nullptr || right->size == 0) ? value : right->minv);
}

template<typename T>
tree<T>::tree(T *vs, size_t length, bool r):
    value(length == 0 ? T() : vs[length/2]),
    left(length <= 1 ? nullptr : new tree(vs, length/2)),
    right(length <= 2 ? nullptr : new tree(vs + length/2 + 1, length - length/2 -1)),
    size(length),
    reversed(r)
{
    minv = min(value, (left == nullptr || left->size == 0) ? value : left->minv);
    minv = min(minv, (right == nullptr || right->size == 0) ? value : right->minv);
}

template<typename T>
void tree<T>::reverse()
{
    if (reversed) {
        if (left != nullptr) left->reversed = !left->reversed;
        if (right != nullptr) right->reversed = !right->reversed;
        reversed = false;
        swap(left, right);
    }
}

template<typename T>
T tree<T>::remove_right()
{
    reverse();
    if (right == nullptr || right->size == 0) {
        T v = value;
        *this = (left == nullptr) ? tree(nullptr, 0) : move(*ptr(move(left)));
        return v;
    }
    else {
        T v = right->remove_right();
        *this = tree(value, move(left), move(right));
        return v;
    }
}

template<typename T>
void tree<T>::rotate_left()
{
    reverse();
    right->reverse();

    T v = right->value;
    ptr llt = move(left);
    ptr lrt = move(right->left);
    ptr rt = move(right->right);

    ptr lt = move(right);
    *lt = tree(value, move(llt), move(lrt));
    *this = tree(v, move(lt), move(rt));
}

template<typename T>
void tree<T>::rotate_right()
{
    reverse();
    left->reverse();

    T v = left->value;
    ptr lt = move(left->left);
    ptr rlt = move(left->right);
    ptr rrt = move(right);

    ptr rt = move(left);
    *rt = tree(value, move(rlt), move(rrt));
    *this = tree(v, move(lt), move(rt));
}

template<typename T>
void tree<T>::splay_min()
{
    reverse();
    if (minv == value)
        ;
    else if (left != nullptr && left->size > 0 && minv == left->minv) {
        left->splay_min();
        *this = tree(value, move(left), move(right));
        rotate_right();
    }
    else {
        right->splay_min();
        *this = tree(value, move(left), move(right));
        rotate_left();
    }
}

template<typename T>
void tree<T>::reverse_prefix()
{
    reverse();
    if (left != nullptr && left->size > 0)
        left->reversed = !left->reversed;
}

template<typename T>
void tree<T>::remove_root()
{
    reverse();
    if (size == 1)
        *this = tree(nullptr, 0);
    else if (left == nullptr || left->size == 0)
        *this = move(*ptr(move(right)));
    else {
        T v = left->remove_right();
        *this = tree(v, move(left), move(right));
    }
}

template<typename T>
size_t tree<T>::get_prefix_length() const
{
    return reversed ? (right == nullptr ? 0 : right->size) : (left == nullptr ? 0 : left->size);
}

int main()
{
    for (int n; cin >> n && n != 0; ) {
        vector<double> h(n);
        for (int i = 0; i < n && cin >> h[i]; ++i)
            h[i] += double(i)/n;

        tree<double> t(&h[0], h.size());
        vector<size_t> p(n);
        for (int i = 0; i < n; ++i) {
            t.splay_min();
            t.get_prefix_length();
            t.reverse_prefix();
            p[i] = 1 + i + t.get_prefix_length();
            t.remove_root();
        }

        for (int i = 0; i < n; ++i)
            cout << (i > 0 ? " " : "") << p[i];
        cout << endl;
    }
    return 0;
}
