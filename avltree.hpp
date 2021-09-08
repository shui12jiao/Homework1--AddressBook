#ifndef AVLTREE_HPP__
#define AVLTREE_HPP__

template <typename T>
class AVLTNode {
   public:
    AVLTNode(T k, AVLTNode *l = nullptr, AVLTNode *r = nullptr) : key(k), height(0), left(l), right(r) {}
    T key;
    AVLTNode *left;
    AVLTNode *right;
    int height;
};

template <typename T>
class AVLTree {
    //    public:
   private:
    AVLTNode<T> *root;

   public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();

    int height(AVLTNode<T> *tree) const;
    void destroy(AVLTNode<T> *tree);
    int insert(T key);
    int remove(T key);
    AVLTNode<T> *search(T key) const;
    void print_tree() const;

   private:
    AVLTNode<T> *insert(T key, AVLTNode<T> *tree);
    AVLTNode<T> *remove(T key, AVLTNode<T> *tree);
    AVLTNode<T> *search(T key, AVLTNode<T> *tree) const;
    int get_balance_factor(AVLTNode<T> *tree) const;
    AVLTNode<T> *balance(AVLTNode<T> *tree);
    AVLTNode<T> *rotate_left(AVLTNode<T> *h);
    AVLTNode<T> *rotate_right(AVLTNode<T> *h);
    void print_tree(AVLTNode<T> *tree) const;
};

template <typename T>
AVLTree<T>::~AVLTree() {
    destroy(root);
    root = nullptr;
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
    delete tree;
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
void AVLTree<T>::print_tree() const {
    print_tree(root);
}

template <typename T>
int AVLTree<T>::insert(T key) {
    if (search(key, root) != nullptr) {
        return -1;
    }
    insert(key, root);
    if (search(key, root) == nullptr) {
        return 0;
    } else {
        return 1;
    }
}

template <typename T>
int AVLTree<T>::remove(T key) {
    if (search(key, root) == nullptr) {
        return -1;
    }
    remove(key, root);
    if (search(key, root) == nullptr) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
AVLTNode<T> *AVLTree<T>::search(T key) const {
    return search(key, root);
}

template <typename T>
AVLTNode<T> *AVLTree<T>::insert(T key, AVLTNode<T> *tree) {
    if (tree == nullptr) {
        tree = new AVLTNode<T>(key);
        if (root == nullptr) {
            root = tree;
        }
    } else if (key < tree->key) {
        tree->left = insert(key, tree->left);

    } else if (key > tree->key) {
        tree->right = insert(key, tree->right);
    }
    tree->height = (height(tree->left) > height(tree->right) ? height(tree->left) : height(tree->right)) + 1;
    return balance(tree);
}

template <typename T>
AVLTNode<T> *AVLTree<T>::remove(T key, AVLTNode<T> *tree) {
    if (tree != nullptr) {
        if (key < tree->key) {
            tree->left = remove(key, tree->left);
        } else if (key > tree->key) {
            tree->right = remove(key, tree->right);
        } else {
            if (tree->left != nullptr && tree->right != nullptr) {
                if (height(tree->left) > height(tree->right)) {
                    AVLTNode<T> *temp = tree->left;
                    while (temp->right != nullptr) {
                        temp = temp->right;
                    }
                    T key = temp->key;
                    remove(key, tree);
                    tree->key = key;
                } else {
                    AVLTNode<T> *temp = tree->right;
                    while (temp->left != nullptr) {
                        temp = temp->left;
                    }
                    T key = temp->key;
                    remove(key, tree);
                    tree->key = key;
                }
            } else if (tree->left != nullptr) {
                tree->key = tree->left->key;
                delete tree->left;
                tree->left = nullptr;
            } else if (tree->right != nullptr) {
                tree->key = tree->right->key;
                delete tree->right;
                tree->right = nullptr;
            } else {
                delete tree;
                return nullptr;
            }
        }
        tree->height = (height(tree->left) > height(tree->right) ? height(tree->left) : height(tree->right)) + 1;
        return balance(tree);
    } else {
        return tree;
    }
}

template <typename T>
AVLTNode<T> *AVLTree<T>::search(T key, AVLTNode<T> *tree) const {
    if (tree == nullptr) {
        return nullptr;
    } else {
        if (key < tree->key) {
            return search(key, tree->left);
        } else if (key > tree->key) {
            return search(key, tree->right);
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
    if (tree == nullptr) {
        return tree;
    }
    int factor = get_balance_factor(tree);
    if (factor > 1 && get_balance_factor(tree->left) > 0) {
        root = rotate_right(tree);
        return root;
    } else if (factor > 1 && get_balance_factor(tree->left) <= 0) {
        tree->left = rotate_left(tree->left);
        root = rotate_right(tree);
        return root;
    } else if (factor < -1 && get_balance_factor(tree->right) <= 0) {
        root = rotate_left(tree);
        return root;
    } else if (factor < -1 && get_balance_factor(tree->right) > 0) {
        tree->right = rotate_right(tree->right);
        root = rotate_left(tree);
        return root;
    }
    root = tree;
    return tree;
}

template <typename T>
void AVLTree<T>::print_tree(AVLTNode<T> *tree) const {
    if (tree == nullptr) {
        return;
    }
    print_tree(tree->left);
    std::cout << tree->key << std::endl;
    print_tree(tree->right);
}

#endif  // AVLTREE_HPP__