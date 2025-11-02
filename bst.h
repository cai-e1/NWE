
#ifndef BST_H
#define BST_H
#include <iostream>
#include <stdexcept>


using namespace std;

template <typename D, typename K>
class BST{
private: 
    struct Node{
        D data;
        K key;
        Node* p;
        Node* left;
        Node* right;

        Node() : data(D()), key (K()) {};
        Node(D d, K k) {
            data = d;
            key = k;
            p = nullptr;
            left = nullptr;
            right = nullptr;
        };
    };
    Node* root;
    D min_data_rec(Node* n, D best);
    D max_data_rec(Node* n, D best);

public:

    BST();
    ~BST();
    BST (const BST<D,K> & rbst);

    bool empty ();
    void insert (D data, K key);
    D get (K k);
    void remove (K k);
    K search_key(K k);
    void remove_helper (Node* node);
    D max_data();
    K max_key();
    D min_data();
    K min_key();
    K successor(K key);
    string in_order();
    void trim (K low, K high);
    void clear(Node* node);
    string print_strings(Node* node);

    string to_string ();
};





#endif
