#include <iostream>
#include <vector>
#include <map>

typedef struct Node {
    std::pair<int, int> p;
    int degree;
    int height = 1;

    struct Node* left = nullptr;
    struct Node* right = nullptr;
} node_t;

bool doesnt_intersect(std::pair<int, int> p, std::pair<int, int> q) {
    if (p.second < q.first || q.second < p.first) {
        return true;
    }

    return false;
}

bool include_head_p(std::pair<int, int> head_interval, std::pair<int, int> p) {
    if (p.first <= head_interval.first && head_interval.second <= p.second) {
        return true;
    }

    return false;
}

bool include_p_head(std::pair<int, int> head_interval, std::pair<int, int> p) {
    if (head_interval.first <= p.first && p.second <= head_interval.second) {
        return true;
    }

    return false;
}

int height(node_t *N) {
    if (!N)
        return 0;

    return N->height;
}

node_t* rightRotate(node_t* y){
    node_t *x = y->left;
    node_t *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left),
                         height(y->right)) + 1;
    x->height = std::max(height(x->left),
                         height(x->right)) + 1;

    // Return new root
    return x;
}

node_t* leftRotate(node_t* x) {
    node_t *y = x->right;
    node_t *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(height(x->left),
                         height(x->right)) + 1;
    y->height = std::max(height(y->left),
                         height(y->right)) + 1;

    // Return new root
    return y;
}

int getBalance(Node *N) {
    if (!N) {
        return 0;
    }

    return height(N->left) - height(N->right);
}

node_t* balancing(node_t* head) {
    head->height = 1 + std::max(height(head->left),
                                height(head->right));

    int balance = getBalance(head);

    if (balance > 1)
        return rightRotate(head);

    if (balance < -1)
        return leftRotate(head);


    return head;
}

node_t* add_node(node_t* head, std::pair<int, int> inserted_pair, int degree) {
    bool worse_case = false;

    if (!head) {
        auto new_head = new node_t;

        new_head->p = inserted_pair;
        new_head->degree = degree;

        return new_head;
    }

    std::pair<int, int> head_interval = head->p;

    if (doesnt_intersect(head_interval, inserted_pair)) {
        if (head_interval.first > inserted_pair.first) {
            head->left = add_node(head->left, inserted_pair, degree);
        }
        else {
            head->right = add_node(head->right, inserted_pair, degree);
        }
    }

    else {
        if (head_interval == inserted_pair) {
            worse_case = true;
        }
        if (include_p_head(head_interval, inserted_pair)) { // [head1    [p1  p2]   head2]
            std::pair<int, int> split1 = {head_interval.first, inserted_pair.first - 1};
            std::pair<int, int> split2 = inserted_pair;
            std::pair<int, int> split3 = {inserted_pair.second + 1, head_interval.second};

            int remember_old_degree = head->degree;

            head->p = split2;
            head->degree += degree;

            if (head_interval.first <= inserted_pair.first - 1) {
                auto new_left = new node_t;

                new_left->p = split1;
                new_left->degree = remember_old_degree;
                new_left->left = head->left;
                new_left = balancing(new_left);
                head->left = new_left;
            }
            if (inserted_pair.second + 1 <= head_interval.second) {
                auto new_right = new node_t;

                new_right->p = split3;
                new_right->degree = remember_old_degree;
                new_right->right = head->right;
                new_right = balancing(new_right);
                head->right = new_right;
            }
        }
        else if (include_head_p(head_interval, inserted_pair)) { // [p1   [head1    head2]   p2]
            std::pair<int, int> split1 = {inserted_pair.first, head_interval.first - 1};
            std::pair<int, int> split2 = head_interval;
            std::pair<int, int> split3 = {head_interval.second + 1, inserted_pair.second};

            head->degree += degree;
            head->p = split2;

            if (inserted_pair.first <= head_interval.first - 1) {
                head->left = add_node(head->left, split1, degree);
            }
            if (head_interval.second + 1 <= inserted_pair.second) {
                head->right = add_node(head->right, split3, degree);
            }
        }
        else { // (1) {head1    [p1    head2}      p2]  or (2) {p1     [head1     p2}   head2]
            if (head_interval.first <= inserted_pair.first &&
                head_interval.second <= inserted_pair.second) { // (1)
                std::pair<int, int> split1 = {head_interval.first, inserted_pair.first - 1};
                std::pair<int, int> split2 = {inserted_pair.first, head_interval.second};
                std::pair<int, int> split3 = {head_interval.second + 1, inserted_pair.second};

                head->p = split2;
                head->degree += degree;

                if (head_interval.first <= inserted_pair.first - 1) {
                    auto new_left = new node_t;

                    new_left->p = split1;
                    new_left->degree = head->degree - degree;
                    new_left->left = head->left;
                    new_left = balancing(new_left);
                    head->left = new_left;
                }
                if (head_interval.second + 1 <= inserted_pair.second) {
                    head->right = add_node(head->right, split3, degree);
                }
            }
            else { // (2): {p1     [head1     p2}   head2]
                std::pair<int, int> split1 = {inserted_pair.first, head_interval.first -1};
                std::pair<int, int> split2 = {head_interval.first, inserted_pair.second};
                std::pair<int, int> split3 = {inserted_pair.second + 1, head_interval.second};

                head->p = split2;
                head->degree += degree;

                if (inserted_pair.second + 1 <=  head_interval.second) {
                    auto new_right = new node_t;

                    new_right->p = split3;
                    new_right->degree = head->degree - degree;
                    new_right->right = head->right;
                    new_right = balancing(new_right);
                    head->right = new_right;
                }
                if (inserted_pair.first <= head_interval.first -1) {
                    head->left = add_node(head->left, split1, degree);
                }
            }
        }
    }

    if (!worse_case)
        return balancing(head);

    return head;
}

int length(std::pair<int, int> p) {
    return p.second - p.first + 1;
}

void convert_from_AVL_to_map(node_t* head, std::map<int, int>& map) {
    if (!head) {
        return;
    }

    map[head->degree] += length(head->p);

    convert_from_AVL_to_map(head->left, map);
    convert_from_AVL_to_map(head->right, map);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    int a, b, c;
    std::map<int, int> m;  // degree->number_of_elem;

    std::cin >> n;
    node_t* head = nullptr;

    for (int i = 0; i < n; i++) {
        std::cin >> a >> b >> c;

        head = add_node(head, {a,b}, c); 
    }

    convert_from_AVL_to_map(head, m);

    uint64_t unordered_pairs_number = 0;
    uint64_t sum_of_elements;

    auto it = m.begin();
    auto it2 = it++;

    if (m.size() == 1) {
        std::cout << 0 << "\n";

        return 0;
    }

    unordered_pairs_number = it->second * it2->second;
    sum_of_elements = it->second + it2->second;

    for (std::map<int,int>::iterator i = m.begin(); i != m.end(); i++) {
        if (i != it && i != it2) {
            unordered_pairs_number += sum_of_elements * i->second;
            sum_of_elements += i->second;
        }
    }

    std::cout << unordered_pairs_number << "\n";

    return 0;
}
