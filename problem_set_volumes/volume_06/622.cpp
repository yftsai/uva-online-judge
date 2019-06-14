// #parsing
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

struct rule
{
    char lhs;
    int values[2];
    uint16_t count;

    rule(char l):
        lhs(l),
        count(0)    {}
};

bool consume(stringstream *ss, char c)
{
    char d;
    if ((*ss) >> d) {
        if (d == c)
            return true;
        else {
            ss->putback(d);
            return false;
        }
    }
    else
        return false;
}

void pop(vector<rule> *stack, int value)
{
    stack->pop_back();
    stack->back().values[stack->back().count++] = value;
}

int main()
{
    vector<rule> stack;
    string line;
    getline(cin, line);
    for (int n = stoi(line); n > 0 && getline(cin, line); --n) {
        stringstream ss(line);
        stack.assign(1, rule('e'));
        while (stack.back().lhs != 'E') {
            auto *f = &stack.back();
            if (f->lhs == 'e') {
                if (f->count == 0)
                    stack.emplace_back('c');
                else if (f->count == 1 && consume(&ss, '+'))
                    stack.emplace_back('e');
                else if (stack.size() == 1)
                    break;
                else if (f->count == 1)
                    pop(&stack, f->values[0]);
                else
                    pop(&stack, f->values[0] + f->values[1]);
            }
            else if (f->lhs == 'c') {
                if (f->count == 0)
                    stack.emplace_back('f');
                else if (f->count == 1 && consume(&ss, '*'))
                    stack.emplace_back('c');
                else if (f->count == 1)
                    pop(&stack, f->values[0]);
                else
                    pop(&stack, f->values[0] * f->values[1]);
            }
            else {
                if (f->count == 0 && consume(&ss, '('))
                    stack.emplace_back('e');
                else if (f->count == 1 && consume(&ss, ')'))
                    pop(&stack, f->values[0]);
                else if (f->count == 1)
                    stack.emplace_back('E');
                else {
                    int value;
                    if (consume(&ss, '+') || !(ss >> value) || value < 0)
                        stack.emplace_back('E');    // A zero should be considered invalid though.
                    else
                        pop(&stack, value);
                }
            }
        }

        char c;
        if (stack.back().lhs == 'E' || stack.size() > 1 || (ss >> c))
            cout << "ERROR" << endl;
        else {
            auto &f = stack.back();
            cout << (f.values[0] + (f.count > 1 ? f.values[1] : 0)) << endl;
        }
    }
    return 0;
}
