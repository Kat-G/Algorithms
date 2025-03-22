/** МАКСИМУМ В СКОЛЬЗЯЩЕМ ОКНЕ
 * 
 * Пусть задан массив из n целых чисел. По этому массиву будут ходить два указателя l и r (1 ≤ l, r ≤ n). Изначально оба 
 * они указывают на первый элемент массива (l = r = 1). Оба указателя могут двигаться только вправо, на одну позицию за раз. 
 * При этом указатель l никогда не оказывается правее указателя r, и ни один из них не выходит за пределы массива. Вам нужно 
 * после каждого перемещения указателя определить максимум всех элементов от указателя l вправо до указателя r (включая 
 * позиции, на которые указывают l и r).
 * 
 * Указание. Учетная стоимость обработки каждого запроса на перемещение и подсчет максимума должна оказаться O(1).
 */

#include <deque>
#include <iostream>
#include <vector>

std::vector<int> FindMax(std::vector<int>& array, std::vector<char>& moves) {
    int left = 0;
    int right = 0;
    std::deque<int> deq;

    deq.push_back(0);

    std::vector<int> results;

    for (size_t index = 0; index < moves.size(); ++index) {
        if (moves[index] == 'R') {
            ++right;

            while (!deq.empty() && array[deq.back()] <= array[right]) {
                deq.pop_back();
            }

            deq.push_back(right);
        } else if (moves[index] == 'L') {
            ++left;

            if (deq.front() < left) {
                deq.pop_front();
            }
        }

        results.push_back(array[deq.front()]);
    }

    return results;
}

int main() {
    int array_size;
    std::cin >> array_size;
    std::vector<int> array(array_size);

    for (int i = 0; i < array_size; ++i) {
        std::cin >> array[i];
    }

    int moves_size;
    std::cin >> moves_size;
    std::vector<char> moves(moves_size);

    for (int i = 0; i < moves_size; ++i) {
        std::cin >> moves[i];
    }

    std::vector<int> results = FindMax(array, moves);

    for (int i = 0; i < moves_size; ++i) {
        std::cout << results[i] << " ";
    }

    return 0;
}
