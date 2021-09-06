#include <ctime>

#include "address_book.h"

using namespace std;

void printB(AVLTNode<int> *tree) {
    if (tree == nullptr) {
        return;
    }
    printB(tree->left);
    std::cout << tree->key << ' ';
    printB(tree->right);
}

void printC(AVLTNode<int> *tree) {
    if (tree == nullptr) {
        return;
    }
    printC(tree->left);
    printC(tree->right);
    std::cout << tree->key << ' ';
}

void printA(AVLTNode<int> *tree) {
    if (tree == nullptr) {
        return;
    }
    std::cout << tree->key << ' ';
    printA(tree->left);
    printA(tree->right);
}

int main() {
    srand(time(NULL));

    Array<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr.push(rand() % 20 + 1);
    }
    for (int i = 0; i < arr.number; ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;

    return 0;
}