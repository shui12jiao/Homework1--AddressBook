#include "avltree.h"

#include <iostream>

template <typename T>
AVLTree<T>::~AVLTree() {
    destroy(root);
}

template <typename T>
int AVLTree<T>::height(AVLTNode<T> *tree) const {
    if (tree == nullptr) {
        return 0;
    }
    return tree->height;
}

template <typename T>
void AVLTree<T>::destroy(AVLTNode<T> *tree) {
    if (tree == nullptr) {
        return;
    }
    destroy(tree->left);
    destroy(tree->right);
    delete (tree);
    tree = nullptr;
}

template <typename T>
AVLTNode<T> *AVLTree<T>::rotate_left(AVLTNode<T> *h) {
    AVLTNode<T> *x = h->right;
    h->right = x->left;
    x->left = h;
    h->height = (height(h->right) > height(h->left) ? height(h->right) : height(h->left)) + 1;
    x->height = (height(x->left) > height(h) ? height(x->left) : height(h)) + 1;
    return x;
}

template <typename T>
AVLTNode<T> *AVLTree<T>::rotate_right(AVLTNode<T> *h) {
    AVLTNode<T> *x = h->left;
    h->left = x->right;
    x->right = h;
    h->height = (height(h->right) > height(h->left) ? height(h->right) : height(h->left)) + 1;
    x->height = (height(x->right) > height(h) ? height(x->right) : height(h)) + 1;
    return x;
}

template <typename T>
void AVLTree<T>::insert(T key) {
    insert(key, root);
}

template <typename T>
void AVLTree<T>::remove(T key) {
    remove(key, root);
}

template <typename T>
void AVLTree<T>::search(T key) const {
    search(key, root);
}

template <typename T>
AVLTNode<T> *AVLTree<T>::insert(T key, AVLTNode<T> *tree) {
    if (tree == nullptr) {
        tree = new AVLTNode<T>(key);
    } else if (key < tree->key) {
        insert(key, tree->left);
    } else if (key > tree->key) {
        insert(key, tree->right);
    } else {
    }
    balance(tree);
    return tree;
}

template <typename T>
AVLTNode<T> *AVLTree<T>::remove(T key, AVLTNode<T> *tree) {
    if (tree == nullptr) {
        return nullptr;
    } else {
        if (key < tree->key) {
            delete (key, tree->left);
        } else if (key > tree->key) {
            delete (key, tree->right);
        } else {
            if (tree->left != nullptr && tree->right != nullptr) {
                if (height(tree->left) > height(tree->right)) {
                    tree->key = remove_max(tree->left);
                } else {
                    tree->key = remove_min(tree->right);
                }
            } else {
                AVLTNode<T> *temp = tree;
                tree = tree->left != nullptr ? tree->left : tree->right;
                delete temp;
            }
        }
        balance(tree);
    }
}

template <typename T>
AVLTNode<T> *AVLTree<T>::search(T key, AVLTNode<T> *tree) const {
    if (tree == nullptr) {
        return nullptr;
    } else {
        if (key < tree->key) {
            search(key, tree->left);
        } else if (key > tree->key) {
            search(key, tree->right);
        } else {
            return tree;
        }
    }
}

template <typename T>
int AVLTree<T>::get_balance_factor(AVLTNode<T> *tree) const {
    if (tree == nullptr) {
        return 0;
    } else {
        return height(tree->left) - height(tree->right);
    }
}

template <typename T>
AVLTNode<T> *AVLTree<T>::balance(AVLTNode<T> *tree) {
    int factor = get_balance_factor(tree);
    if (factor > 1 && get_balance_factor(tree->left) > 0) {
        return rotate_right(tree);
    } else if (factor > 1 && get_balance_factor(tree->left) <= 0) {
        tree->left = rotate_left(tree->left);
        return rotate_right(tree);
    } else if (factor < -1 && get_balance_factor(tree->right) < 0) {
        return rotate_left(tree);
    } else if (factor < -1 && get_balance_factor(tree->right) >= 0) {
        tree->right = rotate_right(tree->right);
        return rotate_left(tree);
    } else {
        return tree;
    }
    return tree;
}

template <typename T>
T AVLTree<T>::remove_min(AVLTNode<T> *tree) {
    if (tree == nullptr) return NULL;

    while (tree->left != nullptr) {
        tree = tree->left;
    }

    T temp = tree->key;
    delete tree;
    return temp;
}

template <typename T>
T AVLTree<T>::remove_max(AVLTNode<T> *tree) {
    if (tree == nullptr) return NULL;

    while (tree->right != nullptr) {
        tree = tree->right;
    }

    T temp = tree->key;
    delete tree;
    return temp;
}
