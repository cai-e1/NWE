
#ifndef BST_H
#define BST_H
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename D, typename K>
class BST{
private: 
    struct Node{
        // Node Attributes
        D data;
        K key;
        Node* p;
        Node* left;
        Node* right;

        // Node Constructors
        Node() : data(D()), key (K()) {};
        Node(D d, K k) {
            data = d;
            key = k;
            p = nullptr;
            left = nullptr;
            right = nullptr;
        };
    };

    // BST Atrributes
    Node* root;


public:

    // BST Constructors & Destructor
    BST();
    ~BST();
    BST(const BST<D,K>& rbst);

    // BST Methods
    bool empty ();
    void insert (D data, K key);
    D get (K k);
    void remove (K k);
    Node* search_key(K k);
    D max_data();
    K max_key();
    D min_data();
    K min_key();
    K successor(K key);
    string in_order();
    void trim (K low, K high);

    // BST Helper Functions
    Node* trim_helper(Node* node, K low, K high);
    void remove_helper (Node* node);
    string to_string_helper(Node* node);
    string inorder_helper(Node* node);
    void clear(Node * node);

    // to_string() method
    string to_string ();
};

#endif
