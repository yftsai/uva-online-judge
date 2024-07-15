// #easy
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main()
{
    unordered_map<uint32_t, uint32_t> slock_owners, elock_owners;
    unordered_set<uint32_t> blocked_threads;
    constexpr uint32_t MULTI = 0;

    string line;
    getline(cin, line);
    for (uint32_t ncases = stoi(line); ncases > 0; ncases--) {
        slock_owners.clear();
        elock_owners.clear();
        blocked_threads.clear();
        getline(cin, line);
        while (getline(cin, line) && line.length() > 1) {
            char mode;
            uint32_t tid, item;
            stringstream ss(line);
            ss >> mode >> tid >> item;

            decltype(slock_owners)::iterator it;
            if (blocked_threads.find(tid) != blocked_threads.end()) {
                cout << "IGNORED" << endl;
            }
            else if ((it = elock_owners.find(item)) != elock_owners.end()) {
                if (it->second == tid)
                    cout << "GRANTED" << endl;
                else {
                    cout << "DENIED" << endl;
                    blocked_threads.insert(tid);
                }
            }
            else if ((it = slock_owners.find(item)) != slock_owners.end()) {
                if (mode == 'S') {
                    cout << "GRANTED" << endl;
                    if (it->second != tid && it->second != MULTI)
                        it->second = MULTI;
                }
                else if (it->second == tid) {
                    cout << "GRANTED" << endl;
                    slock_owners.erase(it);
                    elock_owners[item] = tid;
                }
                else {
                    cout << "DENIED" << endl;
                    blocked_threads.insert(tid);
                }
            }
            else if (mode == 'S') {
                cout << "GRANTED" << endl;
                slock_owners[item] = tid;
            }
            else {
                cout << "GRANTED" << endl;
                elock_owners[item] = tid;
            }
        }

        if (ncases > 1)
            cout << endl;
    }

    return 0;
}
