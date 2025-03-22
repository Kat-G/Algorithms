#include <iostream>
#include <vector>

std::vector<int> ZToPrefix(const std::vector<int>& z_func) {
    int size = z_func.size();
    std::vector<int> p_func(size, 0);

    for (int i_index = 1; i_index < size; ++i_index) {
        for (int j_index = z_func[i_index] - 1; j_index >= 0; --j_index) {
            if (p_func[i_index + j_index] <= 0) {
                p_func[i_index + j_index] = j_index + 1;
            } else {
                break;
            }
        }
    }

    return p_func;
}

int main() {
    int size;
    std::cin >> size;
    std::vector<int> z_func(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> z_func[i];
    }

    std::vector<int> p_func = ZToPrefix(z_func);

    for (int i = 0; i < size; ++i) {
        std::cout << p_func[i] << " ";
    }
}
