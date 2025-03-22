/** Остовное дерево 
 * 
 *  Дан связный граф G с множеством вершин V и множеством ребер E. На каждом ребре графа написан положительный целочисленный вес. 
 *  Остовным деревом T графа G называется такой граф, что его множество вершин V_T ровно совпадает с множеством V, множество его
 *  ребер E_T является подмножеством E и что T является при этом деревом. Требуется найти в G остовное дерево T, у которого 
 *  наибольший из весов всех ребер — наименьший возможный среди всех остовных деревьев графа G.
 *  Вершины графа G пронумерованы числами от 1 до n.
 *  Сложность алгоритма должна получиться O(m+nlogm) в худшем случае.
 */

#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

class DisjointSet {
public:
    explicit DisjointSet(int size) : parent_(size), rank_(size, 0) {
        for (int index = 0; index < size; ++index) {
            parent_[index] = index;
        }
    }

    int Find(int vertex) {
        while (vertex != parent_[vertex]) {
            vertex = parent_[vertex];
        }
        return vertex;
    }

    void Unite(int x_vetrex, int y_vertex) {
        int root_x = Find(x_vetrex);
        int root_y = Find(y_vertex);
        if (root_x != root_y) {
            if (rank_[root_x] < rank_[root_y]) {
                parent_[root_x] = root_y;
            } else if (rank_[root_x] > rank_[root_y]) {
                parent_[root_y] = root_x;
            } else {
                parent_[root_y] = root_x;
                ++rank_[root_x];
            }
        }
    }

private:
    std::vector<int> parent_;
    std::vector<int> rank_;
};

int Kruskal(int vertex_size,
            const std::vector<std::tuple<int, int, int>>& edges) {
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>, std::greater<>>
        pq(edges.begin(), edges.end());

    DisjointSet dsu(vertex_size);
    int max_weight = 0;
    int components = vertex_size;

    while (!pq.empty() && components > 1) {
        auto [weight, from, to] = pq.top();
        pq.pop();

        if (dsu.Find(from) != dsu.Find(to)) {
            dsu.Unite(from, to);
            max_weight = weight;
            --components;
        }
    }

    return max_weight;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int vertex_size;
    int edges_size;
    std::cin >> vertex_size >> edges_size;

    std::vector<std::tuple<int, int, int>> edges(edges_size);
    for (auto& [weight, from, to] : edges) {
        std::cin >> from >> to >> weight;
        --from;
        --to;
    }

    std::cout << Kruskal(vertex_size, edges) << '\n';
    return 0;
}
