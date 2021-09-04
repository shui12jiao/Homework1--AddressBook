#ifndef RBTREE_H__
#define RBTREE_H__

enum RBTColor { RED, BLACK };

template <typename T>
class RBTNode {
   public:
    RBTColor color;
    T val;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
};

class RBTree {};

#endif  // RETREE_H__