#include <iostream>
#include <vector>

/*
 * data[i][0] - existence of 1 in subtree,
 * data[i][1] - existence of 2 in subtree,
 * data[i][2] - existence of 3 in subtree,
 * data[i][3] - existence of sequence 1,2 in subtree,
 * data[i][4] - existence of sequence 2,3 in subtree,
 * data[i][5] - existence of sequence 1, 2, 3 in subtree.
 */


static int find_N(int n) {
    int answer = 1;

    while (answer < n) {
        answer *= 2;
    }

    return answer;
}

// do i - 1 from input
static int convert_index(int length_of_tree, int number_of_leaves, int i) {
    return length_of_tree - number_of_leaves + i;
}

static int parent(int index) {
    if (index % 2 == 0) {
        return index / 2 - 1;
    }

    return index / 2;
}

static int left_child(int parent_index) {
    return parent_index * 2 + 1;
}

static int right_child(int parent_index) {
    return parent_index * 2 + 2;
}

static bool is_leaf(int index, int length_of_tree, int number_of_leaves) {
    if (index >= length_of_tree - number_of_leaves) {
        return true;
    }

    return false;
}

static void update_element(std::vector<std::vector<bool>>& data, int i, int value,
                           int length_of_tree, int number_of_leaves) {
    int start = convert_index(length_of_tree, number_of_leaves, i);
    int end = 0;
    bool while_loop_controller = true;

    // Note that this will not update a root!
    while (while_loop_controller) {
        if (start == end) {
            while_loop_controller = false;
        }

        // Set to the false all node.

        for (int z = 0; z < 6; z++) {
            data[start][z] = false;
        }

        if (is_leaf(start, length_of_tree, number_of_leaves)) {
            data[start][value - 1] = true;
        }
        else {
            int left = left_child(start);
            int right = right_child(start);

            data[start][0] = (data[left][0] || data[right][0]);
            data[start][1] = (data[left][1] || data[right][1]);
            data[start][2] = (data[left][2] || data[right][2]);
            data[start][3] = (data[left][3] || data[right][3]);
            data[start][4] = (data[left][4] || data[right][4]);
            data[start][5] = (data[left][5] || data[right][5]);

            if (!data[start][3]) {
                data[start][3] = (data[left][0] && data[right][1]);
            }
            if (!data[start][4]) {
                data[start][4] = (data[left][1] && data[right][2]);
            }
            if (!data[start][5]) {
                data[start][5] = ((data[left][0] && data[right][4]) ||
                        (data[left][3] && data[right][2]));
            }
        }

        start = parent(start);
    }



}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int  n, m;

    std::cin >> n;

    int number_of_leaves = find_N(n);

    int length_of_tree = 2 * number_of_leaves - 1;

    std::vector<std::vector<bool>> data(length_of_tree, std::vector<bool>(6,false));
    int value, index, new_value;

    for (int i = 0; i < n; i++) {
        std::cin >> value;
        update_element(data, i, value, length_of_tree, number_of_leaves);
    }

    std::cin >> m;

    if (data[0][5]) {
        std::cout << "TAK" << "\n";
    }
    else {
        std::cout << "NIE" << "\n";
    }


    for (int z = 0; z < m; z++) {
        std::cin >> index >> new_value;
        update_element(data, index - 1, new_value, length_of_tree, number_of_leaves);

        if (data[0][5]){
            std::cout << "TAK" << "\n";
        }
        else {
            std::cout << "NIE" << "\n";
        }
    }

    return 0;
}
