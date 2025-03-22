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

int main() {
    std::string s_string;
    std::cin >> s_string;

    std::vector<size_t> z_func = ComputeZFunction(s_string);

    std::cout << s_string.size() << " ";
    for (size_t i = 1; i < z_func.size(); ++i) {
        std::cout << z_func[i] << " ";
    }
    std::cout << "\n";
}
