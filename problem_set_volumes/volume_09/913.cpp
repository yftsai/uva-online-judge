#include <iostream>
#include <iomanip>
using namespace std;

#define SIZE 5
#define NDIGITS 4
#define BASE 10000

class bnum
{
    private:
        int num[SIZE];
    public:
        bnum(int);
        bnum operator+(const bnum &) const;
        bnum operator-(const bnum &) const;
        bnum operator*(const bnum &) const;
        bnum operator/(int) const;
        friend ostream &operator<<(ostream&, const bnum&);
};

bnum::bnum(int val)
{
    for (int i=0; i<SIZE; i++, val/=BASE)
        num[i] = val % BASE;
}

bnum bnum::operator+(const bnum &n2) const
{
    bnum ret = 0;
    int carry = 0;
    for (int i=0; i<SIZE; i++){
        ret.num[i] = num[i] + n2.num[i] + carry;
        carry = ret.num[i]/BASE;
        ret.num[i] %= BASE;
    }
    return ret;
}

bnum bnum::operator-(const bnum &n2) const
{
    bnum ret = *this;
    int borrow = 0;
    for (int i=0; i<SIZE; i++){
        ret.num[i] -= n2.num[i] + borrow;
        if (ret.num[i]>=0)
            borrow = 0;
        else
            ret.num[i]+=BASE, borrow=1;
    }
    return ret;
}

bnum bnum::operator*(const bnum &n2) const
{
    bnum ret = 0;
    for (int i=0; i<SIZE; i++)
        for (int j=i, carry=0; j<SIZE; j++){
            ret.num[j] += this->num[i] * n2.num[j-i] + carry;
            carry = ret.num[j]/BASE;
            ret.num[j] %= BASE;
        }
    return ret;
}

bnum bnum::operator/(int divisor) const
{
    bnum ret = *this;
    int carry = 0;
    for (int i=SIZE-1; i>=0; i--){
        ret.num[i] = ret.num[i] + carry*BASE;
        carry = ret.num[i]%divisor;
        ret.num[i]/=divisor;
    }
    return ret;
}

ostream &operator<<(ostream &os, const bnum &bn)
{
    bool zero = true;
    for (int i=SIZE-1; i>=0; i--)
        if (zero && bn.num[i]>0)
            os << bn.num[i], zero=false;
        else if (!zero)
            cout << setfill('0') << std::setw(NDIGITS) << bn.num[i];
    return os;
}

int main()
{
    const bnum one = 1, six = 6, nine = 9;
    int n;
    while (cin >> n)
        cout << (((bnum(n)+one)*(bnum(n)+one)/4)*six - nine) << endl;

    return 0;
}
