
#include <sstream>
#include "bst.h"
#include <string>


using namespace std;

template <typename D, typename K>
BST<D,K>::BST(){
    root = nullptr;
};


template <typename D, typename K>
BST<D,K>::~BST(){
    // Node* x = root;
    // if (x !=nullptr) {
    //     ~BST(x->left);
    //     delete [] x->key;
    //     ~BST(x->right);
    clear(root);    
};


// template <typename D, typename K>
// BST<D,K>::BST (const BST<D,K> & rbst){
//     Node* x = root;
//     if x !=nullptr {
//         BST(x.left);
//         delete [] x.key;
//         BST (x.right);
//     }
// };


template <typename D, typename K>
bool BST<D,K>::empty(){
    return (this->root == nullptr);
};


template <typename D, typename K>
void BST<D,K>::insert(D data, K key){
    Node* z = new Node(data, key);
    Node* y = nullptr;
    Node* x = root;

    if (this->empty()) {
        root = z;
    }
    
    while (x != nullptr){
        y = x;
        if (z->key < x->key){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    z->p = y;

    if (y == nullptr){
        root = z;
    }

    else if (z->key < y->key){
        y->left = z;
    }
    else {y->right = z;}   
};

template <typename D, typename K>
D BST<D,K>::get(K key){};

template <typename D, typename K>
void BST<D,K>::remove(K key){};

template <typename D, typename K>
D BST<D,K>::max_data(){};

template <typename D, typename K>
K BST<D,K>::max_key(){};

template <typename D, typename K>
D BST<D,K>::min_data(){};

template <typename D, typename K>
K BST<D,K>::min_key(){};

template <typename D, typename K>
K BST<D,K>::successor(K key){};

template <typename D, typename K>
string BST<D,K>::in_order(){
    stringstream ss;

    ss << "hi";

    return ss.str();
};

template <typename D, typename K>
void BST<D,K>::trim (K low, K high){};

template <typename D, typename K>
string BST<D,K>::to_string (){
    string ss;

    ss = print_strings(root);

    return ss;
};

template <typename D, typename K>
void BST<D, K>::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

template <typename D, typename K>
string BST<D, K>::print_strings(Node* node) {
    stringstream ss;
    if (node != nullptr) {
        ss << print_strings(node->left) << " ";
        ss << print_strings(node->right) << " ";
        ss << node->key << " ";
    }

    return ss.str();
};
