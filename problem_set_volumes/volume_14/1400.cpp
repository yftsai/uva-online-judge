// #dynamic_programming
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct interval
{
    int64_t sum, value, lval, rval;
    pair<int, int> indexes;
    int lindex, rindex;
};

struct table
{
    struct interval intv;
    unique_ptr<table> left, right;
};

void shift(int i, interval *intv)
{
    intv->indexes.first += i;
    intv->indexes.second += i;
    intv->lindex += i;
    intv->rindex += i;
}

interval get_interval(const int *values, int count, int a, int b, unique_ptr<table> &t)
{
    const int64_t unknown = INT64_MIN;
    if (t == nullptr && a != b)
        (t = unique_ptr<table>(new table()))->intv.sum = unknown;

    const int m = count / 2;
    if (a == b) {
        interval intv;
        intv.sum = intv.value = intv.lval = intv.rval = values[a];
        intv.indexes.first = intv.indexes.second = intv.lindex = intv.rindex = a;
        return intv;
    }
    else if (b < m)
        return get_interval(values, m, a, b, t->left);
    else if (m <= a) {
        interval intv = get_interval(values + m, count - m, a - m, b - m, t->right);
        shift(m, &intv);
        return intv;
    }
    else if (a == 0 && b == count - 1 && t->intv.sum != unknown)
        return t->intv;
    else {
        const interval intvl = get_interval(values, m, a, m - 1, t->left);
        interval intvr = get_interval(values + m, count - m, 0, b - m, t->right);
        shift(m,  &intvr);

        interval intv;
        intv.sum = intvl.sum + intvr.sum;
        const int64_t mvalue = intvl.rval + intvr.lval;
        intv.value = max(intvl.value, max(mvalue, intvr.value));
        if (intv.value == intvl.value)
            intv.indexes = intvl.indexes;
        else if (intv.value == mvalue)
            intv.indexes = make_pair(intvl.rindex, intvr.lindex);
        else
            intv.indexes = intvr.indexes;
        intv.lval    = max(intvl.lval, intvl.sum + intvr.lval);
        intv.lindex  = (intv.lval == intvl.lval) ? intvl.lindex : intvr.lindex;
        const int64_t rval = intvl.rval + intvr.sum;
        intv.rval    = max(rval, intvr.rval);
        intv.rindex  = (intv.rval == rval) ? intvl.rindex : intvr.rindex;

        return (a == 0 && b == count - 1) ? (t->intv = intv) : intv;
    }
}

int main()
{
    vector<int> values;
    for (int n, m, case_number = 1; cin >> n >> m; case_number++) {
        cout << "Case " << case_number << ":" << endl;
        values.resize(n);
        for (int &v: values)
            cin >> v;

        unique_ptr<table> t;
        for (int a, b; m > 0 && cin >> a >> b; m--) {
            interval intv = get_interval(values.data(), n, a - 1, b - 1, t);
            cout << (intv.indexes.first + 1) << " " << (intv.indexes.second + 1) << endl;
        }
    }
    return 0;
}
