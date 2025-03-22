#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> PrefixToZ(const std::vector<int>& p_func) {
    int size = p_func.size();
    std::vector<int> z_func(size);

    z_func[0] = size;
    for (int index = 1; index < size; ++index) {
        int prefix_curr = p_func[index];
        if (prefix_curr != 0) {
            z_func[index - prefix_curr + 1] = prefix_curr;
        }
    }

    int first_z_value = z_func[1];
    if (first_z_value != 0) {
        for (int index = 1; index < first_z_value; ++index) {
            z_func[index + 1] = first_z_value - index;
        }
    }

    for (int index = first_z_value + 1; index < size - 1; ++index) {
        int z_value_curr = z_func[index];
        int z_value_next = z_func[index + 1];

        if ((z_value_curr != 0) && (z_value_next == 0)) {
            int length = 1;

            while ((length < z_value_curr) &&
                   (z_func[index + length] <= z_func[length])) {
                z_func[index + length] =
                    std::min(z_func[length], z_value_curr - length);
                ++length;
            }

            index += --length;
        }
    }

    return z_func;
}

int main() {
    int size;
    std::cin >> size;
    std::vector<int> p_func(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> p_func[i];
    }

    std::vector<int> z_func = PrefixToZ(p_func);

    for (size_t i = 0; i < z_func.size(); ++i) {
        std::cout << z_func[i] << " ";
    }
}
