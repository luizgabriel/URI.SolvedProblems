#include <iostream>
#include <limits>
#include <vector>
#include <stack>

using namespace std;

template<typename ValueType>
class graph {
private:
    vector<vector<ValueType>> _weighs;

public:
    constexpr graph(size_t numberOfVertices, ValueType initialValue)
            : _weighs(numberOfVertices, vector<ValueType>(numberOfVertices, initialValue)) {
    }

    [[nodiscard]] constexpr auto vertices() const {
        return _weighs.size();
    }

    constexpr inline const auto &operator[](size_t i) const {
        return _weighs[i];
    }

    constexpr inline auto &operator[](size_t i) {
        return _weighs[i];
    }
};

template<typename ValueType>
graph(size_t, ValueType) -> graph<ValueType>;

template<typename ValueType>
int count_movements(const graph<ValueType> &g, size_t startNode) {
    int count = -1;

    auto visited = vector<bool>(g.vertices(), false);
    auto unvisited = stack<size_t>{};

    unvisited.push(startNode);

    while (!unvisited.empty()) {
        size_t v = unvisited.top();
        unvisited.pop();

        if (visited[v])
            continue;

        visited[v] = true;
        count++;

        for (int i = 0; i < g.vertices(); ++i) {
            if (g[v][i] == 1) {
                unvisited.push(i);
            }
        }
    }

    return count;
}

int main() {
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    for (int k = 0; k < t; ++k) {
        size_t n, v, a;
        cin >> n >> v >> a;

        auto g = graph{v, 0u};

        for (int i = 0; i < a; ++i) {
            size_t x, y;
            cin >> x >> y;

            g[x][y] = 1;
            g[y][x] = 1;
        }

        cout << count_movements(g, n) * 2 << '\n';
    }

    return 0;
}
