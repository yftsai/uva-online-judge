// #binary_tree
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class tree_description
{
    public:
        void initialize(vector<bool> *desc, uint32_t pos, uint32_t len);
        void mutate(uint32_t a, uint32_t b, bool team);
        void inverse(uint32_t a, uint32_t b);
        uint32_t get_count(uint32_t a, uint32_t b);

    private:
        static constexpr uint16_t max_leaf_size = 64;
        uint32_t begin;
        uint32_t end;
        uint32_t length;
        bool is_leaf;

        unique_ptr<tree_description> children[2];
        uint32_t count;
        union {
            vector<bool> *description;
            bool is_inverse;
        };

        // propagate the summary of count and is_inverse to the immediate children
        void update_children();
};

void tree_description::initialize(vector<bool> *desc, uint32_t pos, uint32_t len)
{
    begin = pos;
    end = pos + len;
    length = len;
    is_leaf = len <= max_leaf_size;
    if (len <= max_leaf_size) {
        count = std::count(desc->begin() + begin, desc->begin() + end, true);
        description = desc;
    }
    else {
        if (children[0] == nullptr)
            children[0].reset(new tree_description());
        children[0]->initialize(desc, begin, len / 2);

        if (children[1] == nullptr)
            children[1].reset(new tree_description());
        children[1]->initialize(desc, begin + len / 2, len - len / 2);

        count = children[0]->count + children[1]->count;
        is_inverse = false;
    }
}

void tree_description::update_children()
{
    if (!is_leaf) {
        if (is_inverse) {
            children[0]->inverse(children[0]->begin, children[0]->end - 1);
            children[1]->inverse(children[1]->begin, children[1]->end - 1);
            count = length - count;
            is_inverse = false;
        }

        if (count == 0 || count == length) {
            children[0]->mutate(children[0]->begin, children[0]->end - 1, count == length);
            children[1]->mutate(children[1]->begin, children[1]->end - 1, count == length);
        }
    }
}

void tree_description::mutate(uint32_t a, uint32_t b, bool team)
{
    const bool is_leaf = (length <= max_leaf_size);
    if (is_leaf) {
        fill(description->begin() + a, description->begin() + b + 1, team);
        count = std::count(description->begin() + begin, description->begin() + end, true);
    }
    else if (a == begin && b + 1 >= end) {
        is_inverse = false;
        count = team ? length : 0;
    }
    else {
        update_children();

        if (a < children[0]->end)
            children[0]->mutate(a, min(b, children[1]->begin - 1), team);
        if (b >= children[1]->begin)
            children[1]->mutate(max(a, children[1]->begin), b, team);

        count = children[0]->get_count(children[0]->begin, children[0]->end - 1)
              + children[1]->get_count(children[1]->begin, children[1]->end - 1);
    }
}

void tree_description::inverse(uint32_t a, uint32_t b)
{
    const bool is_leaf = (length <= max_leaf_size);
    if (is_leaf) {
        for_each(description->begin() + a, description->begin() + b + 1,
            [](vector<bool>::reference b) { b = !b; });
        count = std::count(description->begin() + begin, description->begin() + end, true);
    }
    else if (a == begin && b + 1 >= end)
        is_inverse = !is_inverse;
    else {
        update_children();

        if (a < children[0]->end)
            children[0]->inverse(a, min(b, children[0]->end - 1));
        if (children[1]->begin <= b)
            children[1]->inverse(max(a, children[1]->begin), b);

        count = children[0]->get_count(children[0]->begin, children[0]->end - 1)
              + children[1]->get_count(children[1]->begin, children[1]->end - 1);
    }
}

uint32_t tree_description::get_count(uint32_t a, uint32_t b)
{
    uint32_t sum = 0;
    if (a == begin && b + 1 >= end)
        sum = (!is_leaf && is_inverse) ? (length - count) : count;
    else if (is_leaf)
        sum = std::count(description->begin() + a, description->begin() + b + 1, true);
    else {
        update_children();

        if (a < children[0]->end)
            sum += children[0]->get_count(a, min(b, children[0]->end - 1));
        if (children[1]->begin <= b)
            sum += children[1]->get_count(max(a, children[1]->begin), b);
    }

    return sum;
}

int main()
{
    vector<bool> pirate_description(1024 * 1000);
    tree_description tree_desc;

    string pirates;
    uint32_t t;
    cin >> t;
    for (uint32_t case_number = 1; case_number <= t; ++case_number) {
        uint16_t m, t;
        cin >> m;
        pirate_description.clear();
        for (uint16_t i = 0; i < m; ++i) {
            cin >> t >> pirates;
            for (uint16_t j = 0; j < t; ++j)
                for (const char c: pirates)
                    pirate_description.push_back(c != '0');
        }

        tree_desc.initialize(&pirate_description, 0, pirate_description.size());

        cout << "Case " << case_number << ":" << endl;
        char query_type;
        uint32_t a, b;
        uint16_t q, query_count = 0;
        for (cin >> q; q > 0 && cin >> query_type >> a >> b; --q) {
            if (query_type == 'F')
                tree_desc.mutate(a, b, true);
            else if (query_type == 'E')
                tree_desc.mutate(a, b, false);
            else if (query_type == 'I')
                tree_desc.inverse(a, b);
            if (query_type == 'S')
                cout << 'Q' << ++query_count << ": " << tree_desc.get_count(a, b) << endl;
        }
    }

    return 0;
}
