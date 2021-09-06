#include <ctime>

#include "address_book.h"
#include "avltree.hpp"

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
    AVLTree<int> *AVL = new AVLTree<int>();

    for (int i = 0; i < 10000; ++i) {
        AVL->insert(rand() % 10000);
    }

    // printB(AVL->root);
    cout << endl << endl;

    for (int i = 0; i < 5000; ++i) {
        AVL->remove(rand() % 10000);
    }

    // printB(AVL->root);

    return 0;
}