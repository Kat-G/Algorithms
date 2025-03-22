/** ДЛИННЕЙШАЯ ЧЕРЕДУЮЩАЯСЯ ПОДПОСЛЕДОВАТЕЛЬНОСТЬ
 * 
 * Найдите наибольшую чередующуюся подпоследовательность ai1, ai2, …, aik последовательности , то есть такую подпоследовательность, 
 * для которой i1 < i2 < … < ik, любые два соседних элемента различны, и для любых трех соседних элементов ail - 1, ail, ail + 1 
 * либо ail - 1 < ail, ail > ail + 1, либо ail - 1 > ail, ail < ail + 1, при этом k — наибольшее возможное.
 */


#include <iostream>
#include <vector>

int findLongestSequence(const std::vector<int> &sequence, int start, int end,
                        bool lookingForGreater,
                        std::vector<std::vector<int>> &lookup,
                        std::vector<std::vector<int>> &prevIndex,
                        std::vector<int> &result) {
    if (lookup[start][lookingForGreater] != -1) {
        return lookup[start][lookingForGreater];
    }

    int maxLength = 0;
    int bestIndex = -1;

    for (int index = start; index <= end; ++index) {
        if (lookingForGreater && sequence[start - 1] < sequence[index]) {
            int length = 1 + findLongestSequence(sequence, index + 1, end,
                                                 !lookingForGreater, lookup,
                                                 prevIndex, result);
            if (length > maxLength) {
                maxLength = length;
                bestIndex = index;
            }
        } else if (!lookingForGreater && sequence[start - 1] > sequence[index]) {
            int length = 1 + findLongestSequence(sequence, index + 1, end,
                                                 !lookingForGreater, lookup,
                                                 prevIndex, result);
            if (length > maxLength) {
                maxLength = length;
                bestIndex = index;
            }
        }
    }

    prevIndex[start][lookingForGreater] = bestIndex;
    lookup[start][lookingForGreater] = maxLength;

    return maxLength;
}

void restoreSequence(const std::vector<int> &sequence, int start,
                     bool lookingForGreater,
                     const std::vector<std::vector<int>> &prevIndex,
                     std::vector<int> &result) {
    while (start != -1) {
        result.push_back(sequence[start]);
        start = prevIndex[start + 1][lookingForGreater];
        lookingForGreater = !lookingForGreater;
    }
}

std::vector<int> longestSequence(const std::vector<int> &sequence) {
    int seq_size = sequence.size();
    if (seq_size == 0) return {};

    std::vector<std::vector<int>> lookup(seq_size + 1, std::vector<int>(2, -1));
    std::vector<std::vector<int>> prevIndex(seq_size + 1,
                                            std::vector<int>(2, -1));

    std::vector<int> result;
    int maxLengthStartingWithIncrease = findLongestSequence(
        sequence, 1, seq_size - 1, true, lookup, prevIndex, result);
    int maxLengthStartingWithDecrease = findLongestSequence(
        sequence, 1, seq_size - 1, false, lookup, prevIndex, result);

    if (maxLengthStartingWithIncrease >= maxLengthStartingWithDecrease) {
        restoreSequence(sequence, 0, true, prevIndex, result);
    } else {
        restoreSequence(sequence, 0, false, prevIndex, result);
    }

    return result;
}

int main() {
    int sequence_size;
    std::cin >> sequence_size;
    std::vector<int> sequence(sequence_size);

    for (int i = 0; i < sequence_size; ++i) {
        std::cin >> sequence[i];
    }

    std::vector<int> result = longestSequence(sequence);
    for (int number : result) {
        std::cout << number << " ";
    }

    return 0;
}
