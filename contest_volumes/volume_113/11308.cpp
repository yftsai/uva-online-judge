// #easy
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
    string binder_name, ingredient, recipe_name;
    unordered_map<string, uint16_t> prices;
    vector<pair<uint32_t, string>> recipes;

    string line;
    stringstream ss;

    getline(cin, line);
    const uint16_t t = stoi(line);

    for (uint16_t s = 0; s < t; s++) {
        getline(cin, binder_name);
        transform(binder_name.begin(), binder_name.end(), binder_name.begin(), ::toupper);
        cout << binder_name << endl;

        uint16_t m, n;
        uint32_t b;
        getline(cin, line);
        ss.str(line);
        ss.clear();
        ss >> m >> n >> b;

        prices.clear();
        for (uint16_t i = 0, c; i < m && getline(cin, line); i++) {
            ss.str(line);
            ss.clear();
            ss >> ingredient >> c;
            prices[ingredient] = c;
        }

        recipes.clear();
        for (uint16_t i = 0; i < n && getline(cin, recipe_name); i++) {
            uint16_t k;
            getline(cin, line);
            ss.str(line);
            ss.clear();
            ss >> k;

            uint32_t cost = 0;
            for (uint16_t j = 0; j < k && getline(cin, line); j++) {
                uint32_t x;
                ss.str(line);
                ss.clear();
                ss >> ingredient >> x;
                cost += prices[ingredient] * x;
            }
            if (cost <= b)
                recipes.emplace_back(cost, recipe_name);
        }

        sort(recipes.begin(), recipes.end());
        if (recipes.size() == 0)
            cout << "Too expensive!" << endl;
        else
            for (auto &r: recipes)
                cout << r.second << endl;
        cout << endl;
    }

    return 0;
}
