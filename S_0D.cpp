#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<size_t> ComputeZFunction(const std::string& k_string) {
    size_t size = k_string.size();
    std::vector<size_t> z_func(size, 0);

    size_t left = 0;
    size_t right = 0;
    for (size_t index = 1; index < size; ++index) {
        if (index <= right) {
            z_func[index] = std::min(right - index + 1, z_func[index - left]);
        }

        while (index + z_func[index] < size &&
               k_string[z_func[index]] == k_string[index + z_func[index]]) {
            z_func[index]++;
        }

        if (index + z_func[index] - 1 > right) {
            left = index;
            right = index + z_func[index] - 1;
        }
    }

    return z_func;
}

int MaxRepeatingSubstring(const std::string& k_string) {
    size_t size = k_string.size();
    int max_k = 1;

    for (size_t index_i = 0; index_i < size; ++index_i) {
        std::vector<size_t> z_vector =
            ComputeZFunction(k_string.substr(index_i));

        for (size_t index_j = 1; index_j < z_vector.size(); ++index_j) {
            if (z_vector[index_j] >= index_j) {
                int curr_k = z_vector[index_j] / index_j + 1;
                if (curr_k > max_k) {
                    max_k = curr_k;
                }
            }
        }
    }

    return max_k;
}

int main() {
    std::string s_string;
    std::cin >> s_string;

    std::cout << MaxRepeatingSubstring(s_string) << std::endl;
}
