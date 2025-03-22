/** Слияние отсортированных последовательностей
 * 
 * Вам дано n упорядоченных по возрастанию последовательностей целых чисел, каждая из которых имеет длину m. Необходимо 
 * слить их в одну упорядоченную по возрастанию последовательность целых чисел длины mn. Сложность алгоритма не должна превышать
 * O(mnlogn), затраты памяти — O(mn).
 */

#include <iostream>
#include <vector>

std::vector<int> MergeTwoArrays(const std::vector<int>& array_a,
                                const std::vector<int>& array_b) {
    std::vector<int> result;
    size_t index_i = 0;
    size_t index_j = 0;

    while (index_i < array_a.size() && index_j < array_b.size()) {
        if (array_a[index_i] < array_b[index_j]) {
            result.push_back(array_a[index_i]);
            index_i++;
        } else {
            result.push_back(array_b[index_j]);
            index_j++;
        }
    }

    for (; index_i < array_a.size(); ++index_i) {
        result.push_back(array_a[index_i]);
    }
    for (; index_j < array_b.size(); ++index_j) {
        result.push_back(array_b[index_j]);
    }

    return result;
}

std::vector<int> MergeArrays(std::vector<std::vector<int>>& sequences) {
    while (sequences.size() > 1) {
        std::vector<std::vector<int>> result;

        for (size_t i = 0; i < sequences.size(); i += 2) {
            if (i + 1 < sequences.size()) {
                result.push_back(
                    MergeTwoArrays(sequences[i], sequences[i + 1]));
            } else {
                result.push_back(sequences[i]);
            }
        }

        sequences = result;
    }

    return sequences[0];
}

int main() {
    int row_count;
    int element_size;
    std::cin >> row_count >> element_size;

    std::vector<std::vector<int>> sequences(row_count,
                                            std::vector<int>(element_size));

    for (auto& sequence : sequences) {
        for (int& element : sequence) {
            std::cin >> element;
        }
    }

    std::vector<int> result = MergeArrays(sequences);

    for (const int& element : result) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
