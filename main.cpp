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
    AVLTree<int> *AVL = new AVLTree<int>();

    for (int i = 0; i < 11; ++i) {
        AVL->insert(i);
    }

    printB(AVL->root);
    cout << endl << endl;

    if (AVL->remove(5) == nullptr) {
        cout << "sucess" << endl;
    } else {
        cout << "fail" << endl;
    }

    if (AVL->remove(5) == nullptr) {
        cout << "sucess" << endl;
    } else {
        cout << "fail" << endl;
    }

    printB(AVL->root);

    return 0;
}