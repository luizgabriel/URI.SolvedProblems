#include <iostream>
#include <limits>
#include <vector>

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
ValueType dijkstra(const graph<ValueType> &g, size_t orig, size_t dest) {
    constexpr auto max = numeric_limits<ValueType>::max();
    auto dists = vector<ValueType>(g.vertices(), max);
    auto visited = vector<bool>(g.vertices(), false);
    dists[orig] = 0;

    for (int i = 0; i < g.vertices(); ++i) {
        auto minCost = max;
        size_t min = 0;

        for (int adj = 0; adj < dists.size(); ++adj) {
            const auto cost = dists[adj];
            if (!visited[adj] && cost < minCost) {
                min = adj;
                minCost = cost;
            }
        }

        visited[min] = true;

        for (int adj = 0; adj < g.vertices(); ++adj) {
            const auto cost = g[min][adj];
            const auto newCost = minCost + cost;
            if (!visited[adj] && cost != max && newCost < dists[adj]) {
                dists[adj] = newCost;
            }
        }
    }

    return dists[dest];
}

int main() {
    ios_base::sync_with_stdio(false);
    size_t n, m, c, k;
    constexpr auto max = numeric_limits<int>::max();

    while (true) {
        cin >> n >> m >> c >> k;

        if (n == 0 && m == 0 && c == 0 && k == 0)
            break;

        auto g = graph{n, max};

        for (int i = 0; i < m; ++i) {
            int u, v;
            int p;
            cin >> u >> v >> p;

            if ((u >= c && v >= c)  // se as duas cidades estiverem fora da rota
                || (u < c && v < c && abs(u - v) == 1)) { // OU se as duas cidades forem cidades consecutivas da rota
                g[u][v] = p;
                g[v][u] = p;
            }

            // se v pertencer à rota
            if (u >= c && v < c)
                g[u][v] = p; // adicione apenas a estrada que chega em v

            // se u pertencer à rota
            if (u < c && v >= c)
                g[v][u] = p; // adicione apenas a estrada que chega em u

        }

        cout << dijkstra(g, k, c - 1) << '\n';
    }

    return 0;
}
