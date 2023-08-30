#include <iostream>
#include <vector>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::map<int, int> map;
    int n, q;
    int index;
    int l, r, d;
    int answer;

    std::cin >> n >> q;

    for (int i = 0; i < n; i++) {
        std::cin >> index;
        map[index]++;
    }

    for (int i = 0; i < q; i++) {
        std::cin >> l >> r >> d;

        std::map<int, int>::iterator it1, it2;
        int remember = -1;

        answer = 0;
        it1 = map.lower_bound(l);
        it2 = map.lower_bound(r);

        if (it1 == map.end() || it2 == map.end()) {
            if (it1 == map.end()) {
                std::cout << 0 << "\n";
                continue;
            }
            else {
                it2 = (--map.end());
            }
        }

        if (it1->first > r) {
            std::cout << 0 << "\n";
            continue;
        }

        if (it2->first > r) {
            it2--;
        }

        for (auto j = it1; j->first <= it2->first && j != map.end(); j++) {
            if (j->first == d) {
                remember = j->second;
            }
            else {
                answer += j->second;
            }
        }

        if (it1 == it2) {
            map.erase(it1);
        }
        else {
            map.erase(it1, it2);
            map.erase(it2);
        }

        if (remember == -1) {
            std::cout << answer << "\n";
            map[d] = answer;
        }
        else {
            std::cout << answer << "\n";
            map[d] += answer + remember;
        }
    }

    return 0;
}
