#ifndef BST_NODE_H
#define BST_NODE_H

// Binary Search Tree Node Template
// D = data 
// K = key 

template <typename D, typename K>
struct BSTNode {
    D data;                 
    K key;                 
    BSTNode* left;           // left child
    BSTNode* right;          // right child
    BSTNode* parent;         // parent pointer

    // Constructor
    BSTNode(const D& d, const K& k,
            BSTNode* l = nullptr,
            BSTNode* r = nullptr,
            BSTNode* p = nullptr)
        : data(d), key(k), left(l), right(r), parent(p) {}
};

#endif // BST_NODE_H
