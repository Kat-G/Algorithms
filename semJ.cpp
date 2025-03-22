/** Считалочка
 * 
 *  N детей играют в считалочку. Перед началом игры дети выстраиваются в круг. И, начиная с некоторого ребенка, последовательно
 *  нумеруются по часовой стрелке от 1 до N. Игра длится N раундов. В каждом раунде очередной ребенок выбывает из круга, а 
 *  оставшиеся продолжают стоять. В первом раунде выбывает ребенок с номером K. В каждом из следующих раундов выбывает K-й ребенок 
 *  по часовой стрелке от выбывшего на предыдущем раунде.
 *  Ваша задача — определить очередность выбывания детей из круга.
 */

#include <iostream>
#include <vector>

class Tree {
public:
    explicit Tree(size_t size) : tree_(size + 1, 0) {}

    void Update(size_t index, int delta) {
        while (index < tree_.size()) {
            tree_[index] += delta;
            index += index & -index;
        }
    }

    size_t Query(size_t index) const {
        size_t sum = 0;
        while (index > 0) {
            sum += tree_[index];
            index -= index & -index;
        }
        return sum;
    }

    size_t Find(size_t number) const {
        size_t index = 0;
        size_t step = 1;

        while (step < tree_.size()) {
            step <<= 1;
        }
        step >>= 1;

        while (step > 0) {
            if (index + step < tree_.size() && tree_[index + step] < number) {
                number -= tree_[index + step];
                index += step;
            }
            step >>= 1;
        }
        return index + 1;
    }

private:
    std::vector<size_t> tree_;
};

Tree InitializeTree(size_t count) {
    Tree tree(count);
    for (size_t i = 1; i <= count; ++i) {
        tree.Update(i, 1);
    }
    return tree;
}

std::vector<size_t> CalculateEliminationOrder(size_t count, size_t step_size) {
    Tree tree = InitializeTree(count);

    std::vector<size_t> elimination_order;
    size_t current_position = 0;

    for (size_t round = 0; round < count; ++round) {
        size_t remaining = count - round;
        current_position = (current_position + step_size - 1) % remaining;

        size_t eliminated_index = tree.Find(current_position + 1);
        elimination_order.push_back(eliminated_index);

        tree.Update(eliminated_index, -1);
    }
    return elimination_order;
}

int main() {
    size_t count;
    size_t step_size;
    std::cin >> count >> step_size;

    std::vector<size_t> elimination_order =
        CalculateEliminationOrder(count, step_size);
    for (size_t child : elimination_order) {
        std::cout << child << " ";
    }
    std::cout << "\n";

    return 0;
}
