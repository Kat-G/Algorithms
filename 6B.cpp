/** Зашифрованное сообщение
 * 
 *  Вам дано зашифрованное сообщение Y, а также последовательность циклических сдвигов, с помощью которых зашифрованное сообщение 
 *  было получено из исходного сообщения X.Каждый циклический сдвиг задан тремя параметрами i,j и k. Применить к текущей строке 
 *  Z циклический сдвиг с параметрами (i,j,k) означает k раз циклически сдвинуть вправо подстроку Z[i..j] (с i-го символа по 
 *  j-й включительно). Символы в сообщениях нумеруются с единицы. Имея такую информацию, вам нужно восстановить исходное сообщение.
 */

#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <vector>

struct Node {
    char value;
    int priority;
    int size;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    explicit Node(char val)
        : value(val),
          priority(rand()),
          size(1),
          left(nullptr),
          right(nullptr) {}
};

using NodePtr = std::shared_ptr<Node>;

class ImplicitTreap {
private:
    NodePtr root_;

    static int GetSize(const NodePtr& node) { return node ? node->size : 0; }

    static void Update(NodePtr node) {
        if (node) {
            node->size = 1 + GetSize(node->left) + GetSize(node->right);
        }
    }

    void Split(NodePtr node, int key, NodePtr& left, NodePtr& right) {
        if (!node) {
            left = right = nullptr;
        } else if (GetSize(node->left) >= key) {
            Split(node->left, key, left, node->left);
            right = node;
        } else {
            Split(node->right, key - GetSize(node->left) - 1, node->right,
                  right);
            left = node;
        }
        Update(node);
    }

    NodePtr Merge(NodePtr left, NodePtr right) {
        if (!left || !right) {
            return left ? left : right;
        }
        if (left->priority > right->priority) {
            left->right = Merge(left->right, right);
            Update(left);
            return left;
        }
        right->left = Merge(left, right->left);
        Update(right);
        return right;
    }

    void Traverse(const NodePtr& node, std::string& result) const {
        if (!node) {
            return;
        }
        Traverse(node->left, result);
        result += node->value;
        Traverse(node->right, result);
    }

public:
    explicit ImplicitTreap(const std::string& string) {
        for (char ch : string) {
            root_ = Merge(root_, std::make_shared<Node>(ch));
        }
    }

    void ReverseCyclicShift(int start, int end, int shift) {
        NodePtr left;
        NodePtr mid;
        NodePtr right;
        Split(root_, end, mid, right);
        Split(mid, start - 1, left, mid);

        int length = end - start + 1;
        shift %= length;

        if (shift > 0) {
            NodePtr part_a;
            NodePtr part_b;
            Split(mid, length - shift, part_a, part_b);
            mid = Merge(part_b, part_a);
        }

        root_ = Merge(Merge(left, mid), right);
    }

    std::string GetResult() const {
        std::string result;
        Traverse(root_, result);
        return result;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string encrypted;
    std::cin >> encrypted;

    int shifts;
    std::cin >> shifts;

    std::vector<std::tuple<int, int, int>> operations(shifts);
    for (int i = 0; i < shifts; ++i) {
        int start;
        int end;
        int shift;
        std::cin >> start >> end >> shift;
        operations[i] = {start, end, shift};
    }

    ImplicitTreap treap(encrypted);

    for (int i = shifts - 1; i >= 0; --i) {
        auto [start, end, shift] = operations[i];
        treap.ReverseCyclicShift(start, end, end - start + 1 - shift);
    }

    std::cout << treap.GetResult() << std::endl;
    return 0;
}
