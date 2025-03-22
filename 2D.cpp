/** Одномерный почтальон
 * 
 *  В деревне Печалька живут n человек, их домики расположены ровно на оси абсцисс. Домик i-го человека находится в точке x_i.
 *  В деревню приехал и хочет там поселиться почтальон. Координату своего домика y он хочет выбрать так, чтобы суммарное расстояние
 *  от него до всех жителей деревни было минимально возможным. Вам дан массив x из n случайных целых чисел. Найдите точку y.
 */

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

const int kBitShift = 8;

unsigned int cur = 0;

unsigned int NextRand24(unsigned int number_a, unsigned int number_b) {
    cur = cur * number_a + number_b;
    return cur >> kBitShift;
}

unsigned int NextRand32(unsigned int number_a, unsigned int number_b) {
    unsigned int high = NextRand24(number_a, number_b);
    unsigned int low = NextRand24(number_a, number_b);
    return (high << kBitShift) ^ low;
}

unsigned int Quickselect(std::vector<unsigned int>& array, int left, int right,
                         int index) {
    if (left == right) {
        return array[left];
    }

    unsigned int pivot = array[left + (right - left) / 2];

    int low = left;
    int high = right;
    while (low <= high) {
        while (array[low] < pivot) {
            low++;
        }
        while (array[high] > pivot) {
            high--;
        }
        if (low <= high) {
            unsigned int temp_numb = array[low];
            array[low] = array[high];
            array[high] = temp_numb;
            low++;
            high--;
        }
    }

    if (left <= high && index <= high) {
        return Quickselect(array, left, high, index);
    }
    if (low <= right && index >= low) {
        return Quickselect(array, low, right, index);
    }
    return array[index];
}

int main() {
    int size;
    std::cin >> size;
    unsigned int number_a;
    unsigned int number_b;
    std::cin >> number_a >> number_b;

    std::vector<unsigned int> array(size);

    for (int i = 0; i < size; ++i) {
        array[i] = NextRand32(number_a, number_b);
    }

    unsigned int median = Quickselect(array, 0, size - 1, size / 2);

    uint64_t total_distance = 0;
    for (int i = 0; i < size; ++i) {
        total_distance += llabs(static_cast<int64_t>(array[i]) -
                                static_cast<int64_t>(median));
    }

    std::cout << total_distance;

    return 0;
}
