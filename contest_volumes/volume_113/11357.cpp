// #parsing #easy
#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

static bool consume(const char *&s, char c)
{
    bool b = (*s == c);
    if (b)
        ++s;
    return b;
}

struct variable
{
    bool is_set;
    bool value;

};

struct literal
{
    uint16_t index;
    bool is_negated;

    static unique_ptr<literal> parse(const char *&s)
    {
        unique_ptr<literal> lit(new literal);
        lit->is_negated = consume(s, '~');
        lit->index = *s - 'a';
        ++s;

        return lit;
    }

    bool satisfy(array<variable, 26> &vars) const
    {
        if (vars[index].is_set)
            return vars[index].value != is_negated;
        else {
            vars[index].is_set = true;
            vars[index].value = !is_negated;
            return true;
        }
    }
};

struct clause
{
    vector<unique_ptr<const literal>> literals;

    static unique_ptr<clause> parse(const char *&s)
    {
        unique_ptr<clause> c(new clause);
        ++s;    // '('
        do {
            c->literals.emplace_back(literal::parse(s));
        } while (consume(s, '&'));
        ++s;    // ')'
        return c;
    }

    bool satisfy() const
    {
        array<variable, 26> vars;
        for_each(vars.begin(), vars.end(), [](variable &v) { v.is_set = false; });

        for (const auto &lit: literals)
            if (!lit->satisfy(vars))
                return false;
        return true;
    }
};

struct formula
{
    std::vector<unique_ptr<const clause>> clauses;

    static unique_ptr<formula> parse(const char *&s)
    {
        unique_ptr<formula> f(new formula());
        do {
            f->clauses.emplace_back(clause::parse(s));
        } while (consume(s, '|'));
        return f;
    }

    bool satisfy() const
    {
        for (const auto &c: clauses)
            if (c->satisfy())
                return true;
        return false;
    }
};

int main()
{
    uint32_t t;
    string f;
    for (cin >> t; t > 0 && cin >> f; --t) {
        const char *s = f.c_str();
        unique_ptr<formula> t = formula::parse(s);
        cout << (t->satisfy() ? "YES" : "NO") << endl;
    }

    return 0;
}
