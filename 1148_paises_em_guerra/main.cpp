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
pair<size_t, ValueType> unvisited_neighbor(const vector<ValueType> &dists, const vector<bool> &visited) {
    auto minCost = numeric_limits<ValueType>::max();
    size_t minVertex = 0;

    for (int adj = 0; adj < dists.size(); ++adj) {
        const auto cost = dists[adj];
        if (!visited[adj] && cost < minCost) {
            minVertex = adj;
            minCost = cost;
        }
    }

    return {minVertex, minCost};
}

template<typename ValueType>
ValueType dijkstra(const graph<ValueType> &g, size_t o, size_t d) {
    constexpr auto max = numeric_limits<ValueType>::max();
    auto dists = vector<ValueType>(g.vertices(), max);
    auto visited = vector<bool>(g.vertices(), false);
    dists[o] = 0;

    for (int i = 0; i < g.vertices(); ++i) {
        auto[min, minCost] = unvisited_neighbor(dists, visited);
        visited[min] = true;

        for (int adj = 0; adj < g.vertices(); ++adj) {
            const auto cost = g[min][adj];
            const auto newCost = minCost + cost;
            if (!visited[adj] && cost != max && newCost < dists[adj]) {
                dists[adj] = newCost;
            }
        }
    }

    return dists[d];
}

int main() {
    ios_base::sync_with_stdio(false);
    size_t nVertices, nEdges;
    constexpr auto max = numeric_limits<uint16_t>::max();

    while (true) {
        cin >> nVertices >> nEdges;

        if (nVertices == 0 && nEdges == 0)
            break;

        auto g = graph{nVertices, max};

        for (int i = 0; i < nEdges; ++i) {
            size_t x, y;
            uint16_t h;
            cin >> x >> y >> h;

            // Cities in same country
            if (g[y - 1][x - 1] < max) {
                g[y - 1][x - 1] = 0;
                h = 0;
            }

            g[x - 1][y - 1] = h;
        }

        int k;
        cin >> k;
        for (int i = 0; i < k; i++) {
            size_t o, d;
            cin >> o >> d;
            auto cost = dijkstra(g, o - 1, d - 1);

            if (cost < max)
                cout << cost << '\n';
            else
                cout << "Nao e possivel entregar a carta\n";
        }

        cout << '\n';
    }

    return 0;
}
