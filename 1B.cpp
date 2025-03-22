/** ПРАВИЛЬНАЯ СКОБОЧНАЯ ПОДПОСЛЕДОВАТЕЛЬНОСТЬ
 * 
 *  Во входе задана непустая строка  длины не более 1 000 000, состоящая только из скобок (круглых, квадратных и/или фигурных).
 * Требуется определить, является ли она правильной скобочной последовательностью. Если да, выведите слово CORRECT Если нет, 
 * выведите длину максимального префикса , который либо сам является правильной скобочной последовательностью, либо может быть 
 * продолжен до таковой.
 */

#include <iostream>
#include <stack>
#include <string>

int IsCorrect(const std::string& sequence) {
    std::stack<char> brackets;
    int counter = 0;

    for (char bracket : sequence) {
        if (bracket == '(' || bracket == '{' || bracket == '[') {
            brackets.push(bracket);
            ++counter;
        } else {
            if (brackets.empty()) {
                return counter;
            }
            char top = brackets.top();
            if ((top == '(' && bracket == ')') ||
                (top == '{' && bracket == '}') ||
                (top == '[' && bracket == ']')) {
                brackets.pop();
                ++counter;
            } else {
                return counter;
            }
        }
    }

    if (brackets.empty()) {
        return -1;
    } else {
        return counter;
    }
}

int main() {
    std::string sequence;
    std::getline(std::cin, sequence);

    if (IsCorrect(sequence) == -1) {
        std::cout << "CORRECT\n";
    } else {
        std::cout << IsCorrect(sequence) << "\n";
    }

    return 0;
}
