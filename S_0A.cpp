#include <iostream>
#include <string>
#include <vector>

std::vector<int> FindPrefix(const std::string kString) {
    size_t string_size = kString.size();
    std::vector<int> pref(string_size, 0);

    for (size_t index = 1; index < string_size; ++index) {
        size_t elem = pref[index - 1];
        while (elem > 0 && kString[index] != kString[elem]) {
            elem = pref[elem - 1];
        }
        if (kString[index] == kString[elem]) {
            elem++;
        }
        pref[index] = elem;
    }

    return pref;
}

int main() {
    std::string s_string;
    std::cin >> s_string;

    std::vector<int> pref_vector = FindPrefix(s_string);

    for (size_t index = 0; index < pref_vector.size(); ++index) {
        std::cout << pref_vector[index] << " ";
    }
}
