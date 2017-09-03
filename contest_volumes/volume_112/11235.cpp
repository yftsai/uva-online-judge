// #dynamic_programming
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct sequence
{
    int length;
    int val, count;
    int lval, lcount;
    int rval, rcount;
    shared_ptr<const struct sequence> lseq, rseq;
};

shared_ptr<const struct sequence> append(const shared_ptr<const struct sequence> lseq, const shared_ptr<const struct sequence> rseq)
{
    auto s = make_shared<struct sequence>();
    s->length = lseq->length + rseq->length;

    if (lseq->val == rseq->val)
        s->val = lseq->val, s->count = lseq->count + rseq->count;
    else if (lseq->count < rseq->count)
        s->val = rseq->val, s->count = rseq->count;
    else
        s->val = lseq->val, s->count = lseq->count;

    if (lseq->rval == rseq->lval && lseq->rcount + rseq->lcount > s->count)
        s->val = lseq->rval, s->count = lseq->rcount + rseq->lcount;

    s->lval = lseq->lval;
    s->lcount = lseq->lcount + ((lseq->lval == rseq->lval) ? rseq->lcount : 0);
    s->rval = rseq->rval;
    s->rcount = rseq->rcount + ((lseq->rval == rseq->rval) ? lseq->rcount : 0);

    s->lseq = lseq;
    s->rseq = rseq;

    return s;
}

shared_ptr<const struct sequence> build(const vector<int> &as, int start, int length)
{
    if (length == 1) {
        auto s = make_shared<struct sequence>();
        s->length = s->count = s->lcount = s->rcount = 1;
        s->val = s->lval = s->rval = as[start];
        return s;
    }
    else
        return append(build(as, start, length/2), build(as, start + length/2, length - length/2));
}

shared_ptr<const struct sequence> slice(const shared_ptr<const struct sequence> &seq, int start, int length)
{
    if (start == 0 && length == seq->length)
        return seq;
    else if (start + length <= seq->lseq->length)
        return slice(seq->lseq, start, length);
    else if (start >= seq->lseq->length)
        return slice(seq->rseq, start - seq->lseq->length, length);
    else
        return append(slice(seq->lseq, start, seq->lseq->length - start),
                      slice(seq->rseq, 0, start + length - seq->lseq->length));
}

int main()
{
    for (int n, q; cin >> n >> q && n != 0; ) {
        vector<int> as(n);
        for (auto &a: as)
            cin >> a;

        shared_ptr<const struct sequence> seq = build(as, 0, as.size());
        for(int i, j; q > 0 && cin >> i >> j; q--)
            cout << slice(seq, i-1, j-i+1)->count << endl;;
    }

    return 0;
}
