/** МИНИМАЛЬНЫЙ МАКСИМУМ
 *  
 *  Даны n нестрого возрастающих массивов Ai и m нестрого убывающих массивов Bj. Все массивы имеют одну и ту же длину l. 
 *  Далее даны q запросов вида (i, j), ответ на запрос — такое k, что max(Aik,Bjk) минимален. Если таких k несколько, можно 
 *  вернуть любое.
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int findMinMaxIndex(const std::vector<int>& array_a,
                    const std::vector<int>& array_b) {
    int left = 0, right = array_a.size() - 1;
    int best_k = 0;
    int min_max_value = std::max(array_a[0], array_b[0]);

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int current_max = std::max(array_a[mid], array_b[mid]);

        if (current_max < min_max_value) {
            min_max_value = current_max;
            best_k = mid;
        }

        if (array_a[mid] < array_b[mid]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return best_k + 1;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int size_a, size_b, size_elements, size_requests;
    std::cin >> size_a >> size_b >> size_elements;

    std::vector<std::vector<int>> array_a(size_a,
                                          std::vector<int>(size_elements));
    std::vector<std::vector<int>> array_b(size_b,
                                          std::vector<int>(size_elements));

    for (int i = 0; i < size_a; ++i) {
        for (int j = 0; j < size_elements; ++j) {
            std::cin >> array_a[i][j];
        }
    }

    for (int i = 0; i < size_b; ++i) {
        for (int j = 0; j < size_elements; ++j) {
            std::cin >> array_b[i][j];
        }
    }

    std::cin >> size_requests;
    std::vector<std::pair<int, int>> requests(size_requests);

    for (int i = 0; i < size_requests; ++i) {
        int index_i_for_a, index_j_for_b;
        std::cin >> index_i_for_a >> index_j_for_b;
        requests[i] = {index_i_for_a - 1, index_j_for_b - 1};
    }

    for (const auto& request : requests) {
        int index_i_for_a = request.first;
        int index_j_for_b = request.second;

        int result =
            findMinMaxIndex(array_a[index_i_for_a], array_b[index_j_for_b]);

        std::cout << result << std::endl;
    }

    return 0;
}
