#include <iostream>
#include <vector>
#include <queue>


typedef struct Triple {
    int counter;
    std::pair<int, int> coordinate;

    Triple(int count, int coord1, int coord2) : counter(count), coordinate({coord1, coord2}) {}
}triple;

struct ElementComparator {
    bool operator()(const triple & a, const triple& b) const {
        return a.counter > b.counter;
    }
};

// Checks if the coordinate is valid, it is 
// returns true if coordinate is inside of the board
// and false otherwise.
bool is_valid(int x_now, int y_now, int n, int m) {
    if (x_now < n && x_now >= 0  && y_now < m && y_now >= 0) {
        return true;
    }

    return false;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;

    std::cin >> n >> m;

    std::vector<std::vector<char>> tab(n, std::vector<char>(m));
    std::vector<std::vector<bool> > visited(n, std::vector<bool>(m, false));
    char a;
    int x,y;
    int c,d;

    // Read input and remember A and B 
    // coordinates.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a;
            tab[i][j] = a;

            if (a == 'A') {
                x = i;
                y = j;
            }
            else if (a == 'B'){
                c = i;
                d = j;
            }
        }
    }


    std::priority_queue<triple, std::vector<triple>, ElementComparator> q;
    std::pair<int,int> end = {c,d};
    std::pair<int, int> p;

    q.push(Triple(0, x, y));
    visited[x][y] = true;

    // Implementation of Dijkstra algorithm.
    while (!q.empty()) {
        auto top = q.top();
        q.pop();
        p = top.coordinate;

        if (top.coordinate == end) {
            std::cout << top.counter;
            
            break;
        }

        if (is_valid(p.first + 1, p.second, n, m) && !visited[p.first + 1][p.second]) {
            if (tab[p.first + 1][p.second] == '#') {
                visited[p.first + 1][p.second] = true;
                q.push(Triple(top.counter + 1, p.first + 1, p.second));
            }
            else {
                visited[p.first + 1][p.second] = true;
                q.push(Triple(top.counter, p.first + 1, p.second));
            }
        }
        if (is_valid(p.first - 1, p.second, n, m) && !visited[p.first - 1][p.second]) {
            if (tab[p.first - 1][p.second] == '#') {
                visited[p.first - 1][p.second] = true;
                q.push(Triple(top.counter + 1, p.first - 1, p.second));
            }
            else {
                visited[p.first - 1][p.second] = true;
                q.push(Triple(top.counter, p.first - 1, p.second));
            }
        }

        if (is_valid(p.first, p.second  +1, n, m) && !visited[p.first][p.second + 1]) {
            if (tab[p.first][p.second + 1] == '#') {
                visited[p.first][p.second + 1] = true;
                q.push(Triple(top.counter + 1, p.first, p.second + 1));
            }
            else {
                visited[p.first][p.second + 1] = true;
                q.push(Triple(top.counter, p.first, p.second + 1));
            }
        }

        if (is_valid(p.first, p.second - 1, n, m) && !visited[p.first][p.second - 1]) {
            if (tab[p.first][p.second - 1] == '#') {
                visited[p.first][p.second - 1] = true;
                q.push(Triple(top.counter + 1, p.first, p.second - 1));
            }
            else {
                visited[p.first][p.second-  1] = true;
                q.push(Triple(top.counter, p.first, p.second - 1));
            }
        }
    }


    return 0;
}
