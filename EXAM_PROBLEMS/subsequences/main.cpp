#include <iostream>
#include <map>
#include <tuple>
#include <iterator>

unsigned long long int count_all_subsequences(int *tab, int n, int k) {
    int left = 0;
    int right = 0;
    uint64_t answer = 0;
    std::map<int, int> distinct;
    std::map<int, int>::iterator it;

    while (left < n) {
        while (right < n && distinct.size() <= k) {
            it = distinct.find(tab[right]);

            if (it != distinct.end()) {
                it->second++;
                right++;
            }
            else {
                if (distinct.size() == k) {
                    break;
                }
                else {
                    distinct.insert(std::make_pair(tab[right], 1));
                    right++;
                }
            }
        }

        answer += right - left;

        if (right < n) {
            while (distinct.size() == k) {
                auto it1 = distinct.find(tab[left]);

                (it1->second)--;

                if (!it1->second) {
                    distinct.erase(it1);
                    left++;
                    break;
                }

                left++;
                answer += right - left;
            }
        }
        else {
            left++;
        }
    }

    return answer;
}


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;

    std::cin >> n;
    std::cin >> k;

    int tab[n];

    for (int i = 0; i < n; i++) {
        std::cin >> tab[i];
    }

    std::cout << count_all_subsequences(tab, n, k);

    return 0;
}
