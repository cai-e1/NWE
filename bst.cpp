
#include <sstream>
#include "bst.h"
#include <string>
#include <queue>


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
D BST<D,K>::get(K k){
    Node* temp = root;
    while (temp!=nullptr){
        if (temp->key == k){
            return (temp->data);
        }
        else if (temp->key < k){
            temp = temp->right;
        }
        else if (temp->key > k){
            temp = temp->left;
        }
    }
    return (D());
};

template <typename D, typename K>
void BST<D,K>::remove(K k){
    Node* temp = search(k);
    remove_helper(temp);
};

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
    ss.pop_back();

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
    queue<Node*> temp;
    temp.push(node);

    while (!temp.empty()) {
        Node* current = temp.front();
        temp.pop();
        ss << current->key << " ";
        if (current->left != nullptr) {
            temp.push(current->left);
        } 
        if (current->right != nullptr) {
            temp.push(current->right);
        }
    }

    return ss.str();
};

template <typename D, typename K>
K BST<D,K>::search_key(K k){
    Node* temp = root;
    while (temp!=nullptr){
        if (temp->key == k){
            return (temp);
        }
        else if (temp->key < k){
            temp = temp->right;
        }
        else if (temp->key > k){
            temp = temp->left;
        }
    }
    return (K());
}

template <typename D, typename K>
void BST<D,K>::remove_helper(Node* temp){
    //no children
    if ((temp->left ==nullptr)&&(temp->right==nullptr)){
        if (temp->p == nullptr){root = nullptr;}
        else if (temp == temp->p->left){
            temp->p->left = nullptr;
        }
        else{
            temp->p->right = nullptr;
        }
    }

    //scenario 1 where the node that is being deleted only has one child
    else if ((temp->left == nullptr)&&(temp->right!=nullptr)){
        if (temp->p == nullptr){root = temp->right;}
        else{temp->p->right = temp->right;}
        temp->right->p = temp->p;
        delete temp;
    }
    
    else if ((temp->right == nullptr)&&(temp->left!=nullptr)){
        if (temp->p == nullptr){root = temp->left;}
        else{temp->p->left = temp->left;}
        temp->left->p = temp->p;
        delete temp;
    }
    

    //scenario 2 where there are multiple children
    else{
        Node* replace = successor(temp->key);
        Node* replace_parent = replace->p;

        temp->key = replace->key;
        temp->data = replace->data;

        if (replace->right != nullptr){
            replace_parent->left = replace->right;
            replace->right->p = replace_parent;
        }
    }
}

