#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

static vector<tuple<int,char,uint64_t>> remove_copies(vector<tuple<int,char,int>>& original_intervals) {
    uint64_t sum;
    int i = 0;
    int get_number;
    char get_color;
    int length = original_intervals.size();
    vector<tuple<int,char,uint64_t>> without_copies;

    while (i < length) {
        get_number = get<0>(original_intervals[i]);
        get_color = get<1>(original_intervals[i]);
        sum = 0;

        if (i + 1 < length && std::get<0>(original_intervals[i + 1]) == get_number &&
              get<1>(original_intervals[i + 1]) == get_color) {
                    int j = i;

                    while (j < length &&
                            get<0>(original_intervals[j]) == get_number &&
                            get<1>(original_intervals[j]) == get_color) {
                                sum += get<2>(original_intervals[j]);
                                j++;
                    }

              without_copies.emplace_back(get_number, get_color, sum);
              i = j;
        }
        else {
            without_copies.emplace_back(get_number, get_color, get<2>(original_intervals[i]));
            i++;
        }
    }

    return without_copies;
}

static void generate_partition(vector<tuple<int,char,uint64_t>>& without_copies,
                               map<uint64_t, uint64_t>& final_map) {
    uint64_t sum;
    int index = 1;
    int length = without_copies.size();
    int start_point = get<0>(without_copies[0]);
    sum = get<2>(without_copies[0]);

    while (index < length) {
        char znak = get<1>(without_copies[index]);
        int end_point = get<0>(without_copies[index]);
        uint64_t multiplicity = get<2>(without_copies[index]);

        if (znak == '+') {
            final_map[sum] += (end_point - start_point); // Length of interval.
            start_point = end_point;
            sum += multiplicity;
            index++;
        }
        else {
            if (start_point == end_point) {
                final_map[sum] += 1;
                sum -= multiplicity;

                if (sum != 0) {
                    start_point++;
                    index++;
                }
                else {
                    index++;

                    if (index < length) {
                        start_point = get<0>(without_copies[index]);
                        sum = get<2>(without_copies[index]);
                        index++;
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                final_map[sum] += end_point - start_point + 1; // Length of interval.
                sum -= multiplicity;

                if (sum != 0) {
                    start_point = end_point + 1;
                    index++;
                }
                else {
                    index++;

                    if (index < length) {
                        start_point = get<0>(without_copies[index]);
                        sum = get<2>(without_copies[index]);
                        index++;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    int a,b,c;
    int local_index1 = 0;
    map<uint64_t, uint64_t> final_map; // Will contatin multiplicity -> number of elements with that degree.
    vector<tuple<int, char, int>> original_intervals(2 * n); 

    for (int i = 0; i < n; i++) {
        std::cin >> a >> b >> c;

        original_intervals[local_index1] = {a, '+', c};
        original_intervals[local_index1 + 1] = {b, '-', c};

        local_index1 = local_index1 + 2;
    }
    
    sort(original_intervals.begin(), original_intervals.end());
    auto without_copies = remove_copies(original_intervals);
    generate_partition(without_copies, final_map); // partition will be stored in final_map

    if (final_map.size() == 1) {
        cout << 0 << "\n";

        return 0;
    }

    uint64_t unordered_pairs_number;
    uint64_t sum_of_elements;
    int counter = 0;

    // Walk through final_map to find the number of unordered pairs with different multiplicity
    for (auto i : final_map) {
        if (counter == 0) {
            unordered_pairs_number = i.second;
            sum_of_elements = i.second;
            counter++;
        }
        else if (counter == 1) {
            unordered_pairs_number *= i.second;
            sum_of_elements += i.second;
            counter++;
        }
        else {
            unordered_pairs_number += sum_of_elements * i.second;
            sum_of_elements += i.second;

        }
    }

    std::cout << unordered_pairs_number << "\n";

    return 0;
}
