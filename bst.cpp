#include <sstream>
#include "bst.h"
#include <string>
#include <queue>


using namespace std;

template <typename D, typename K>
BST<D,K>::BST()
/* Pre:  None.
 * Post: Constructs an empty BST with root == nullptr. */
{
    root = nullptr;
};


template <typename D, typename K>
BST<D,K>::~BST()
/* Pre:  This BST object exists.
 * Post: All dynamically allocated nodes reachable from root are deallocated. */
{
    // Node* x = root;
    // if (x !=nullptr) {
    //     ~BST(x->left);
    //     delete [] x->key;
    //     ~BST(x->right);
    clear(root);    
};


template <typename D, typename K>
BST<D,K>::BST (const BST<D,K> & rbst)
/* Pre:  rbst is a valid BST.
 * Post: Initializes this BST with rbst.root (shallow copy of pointer). */
{
//     Node* x = root;
//     if x !=nullptr {
//         BST(x.left);
//         delete [] x.key;
//         BST (x.right);
//     }
    root = rbst.root;

};


template <typename D, typename K>
bool BST<D,K>::empty()
/* Pre:  None.
 * Post: Returns true iff root == nullptr. Tree is not modified. */
{
    return (this->root == nullptr);
};


template <typename D, typename K>
void BST<D,K>::insert(D data, K key)
/* Pre:  Keys are comparable with operator< and operator==; BST property holds for existing nodes.
 * Post: A new node containing (data, key) is inserted so that the BST property is preserved. */
{
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
D BST<D,K>::get(K k)
/* Pre:  Keys in the tree are comparable with k.
 * Post: Returns data stored at the node with key == k if found; otherwise returns default-constructed D(). Tree is unchanged. */
{
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
void BST<D,K>::remove(K k)
/* Pre:  Keys are comparable and the BST property holds.
 * Post: If a node with key k exists, it is removed and the BST property is preserved; otherwise the tree is unchanged. */
{
    Node* temp = search_key(k);
    if (temp!=nullptr){
        remove_helper(temp);}
};

template <typename D, typename K>
D BST<D,K>::min_data_rec(Node* n, D best)
/* Pre:  n is a pointer to a node in this BST (or nullptr). D supports operator<.
 * Post: Returns the minimum value among data fields in the subtree rooted at n (or best if n == nullptr). Does not modify the tree. */
{
    if (n == nullptr) return best;
    if (n->data < best) best = n->data;
    best = min_data_rec(n->left,  best);
    best = min_data_rec(n->right, best);
    return best;
}

template <typename D, typename K>
D BST<D,K>::max_data_rec(Node* n, D best)
/* Pre:  n is a pointer to a node in this BST (or nullptr). D supports operator<.
 * Post: Returns the maximum value among data fields in the subtree rooted at n (or best if n == nullptr). Does not modify the tree. */
{
    if (n == nullptr) return best;
    if (best < n->data) best = n->data;
    best = max_data_rec(n->left,  best);
    best = max_data_rec(n->right, best);
    return best;
}

template <typename D, typename K>
D BST<D,K>::max_data()
/* Pre:  Tree is non-empty; D supports operator< for comparisons.
 * Post: Returns the maximum data value stored anywhere in the BST; tree is not modified. Throws if tree is empty. */
{
    if (root == nullptr) {
        throw std::runtime_error("max_data() called on an empty BST");
    }
    return max_data_rec(root, root->data);
}

template <typename D, typename K>
K BST<D,K>::max_key()
/* Pre:  Tree is non-empty; K supports operator<.
 * Post: Returns the maximum key present in the BST (rightmost node). Throws if tree is empty. */
{
    if (root == nullptr) { throw "max_key() called on an empty BST"; }
    Node* cur = root;
    while (cur->right != nullptr) {
        cur = cur->right;
    }
    return cur->key;
}

template <typename D, typename K>
D BST<D,K>::min_data()
/* Pre:  Tree is non-empty; D supports operator< for comparisons.
 * Post: Returns the minimum data value stored anywhere in the BST; tree is not modified. Throws if tree is empty. */
{
    if (root == nullptr) {
        throw std::runtime_error("min_data() called on an empty BST");
    }
    return min_data_rec(root, root->data);
}

template <typename D, typename K>
K BST<D,K>::min_key()
/* Pre:  Tree is non-empty; K supports operator<.
 * Post: Returns the minimum key present in the BST (leftmost node). Throws if tree is empty. */
{
    if (root == nullptr) { throw "min_key() called on an empty BST"; }
    Node* cur = root;
    while (cur->left != nullptr) {
        cur = cur->left;
    }
    return cur->key;
}

template <typename D, typename K>
K BST<D,K>::successor(K key)
/* Pre:  Keys are comparable; BST property holds.
 * Post: Returns the key that immediately follows 'key' in in-order traversal, or default-constructed K() if none exists or key not found. Tree is unchanged. */
{
    Node* x = search_key(key);

    if (x == nullptr || x->key == max_key()) {
        return K();
    }
    else if (x->right != nullptr) {
        x = x->right;
        while (x->left != nullptr) {
            x = x->left;
        }
        return x->key;
    } else {
        Node* y = x->p;
        while (y != nullptr & x == y->right) {
            x = y;
            y = y->p; 
        }
        return y->key;
    }
};

template <typename D, typename K>
string BST<D,K>::in_order()
/* Pre:  None.
 * Post: Returns a space-separated string of keys in in-order traversal with a trailing space removed. Tree is unchanged. */
{
    string ss;

    ss = inorder_helper(root);
    ss.pop_back();

    return ss;
};

template <typename D, typename K>
void BST<D,K>::trim (K low, K high)
/* Pre:  Keys are comparable; low and high define an inclusive range (low <= high not enforced by code).
 * Post: Removes any nodes with key < low or key > high; remaining tree preserves BST property. */
{
    root = trim_helper(root, low, high);
};

template <typename D, typename K>
string BST<D,K>::to_string()
/* Pre:  None.
 * Post: Returns a space-separated string of keys in level-order (BFS), with trailing space removed. Tree is unchanged. */
{
    string ss;

    ss = to_string_helper(root);
    ss.pop_back();

    return ss;
};

template <typename D, typename K>
void BST<D, K>::clear(Node* node)
/* Pre:  node is a pointer to a node in this BST (or nullptr).
 * Post: Recursively deallocates the subtree rooted at node. */
{
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

template <typename D, typename K>
string BST<D, K>::to_string_helper(Node* node)
/* Pre:  node is a pointer to the root of a (sub)tree (may be nullptr).
 * Post: Returns a space-separated string of keys produced by a BFS starting at node. Tree is unchanged. */
{
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
string BST<D, K>::inorder_helper(Node* node)
/* Pre:  node is a pointer to the root of a (sub)tree (may be nullptr).
 * Post: Returns a space-separated string of keys produced by an in-order traversal of the subtree rooted at node. Tree is unchanged. */
{
    stringstream ss;

    Node* curr = node;
    if (curr != nullptr) {
        inorder_helper(curr->left);
        ss << curr->key << " ";
        inorder_helper(curr->right); 
    }

    return ss.str();
}

template <typename D, typename K>
typename BST<D,K>::Node* BST<D,K>::search_key(K k)
/* Pre:  Keys in the tree are comparable with k.
 * Post: Returns a pointer to the node whose key == k if found; otherwise returns nullptr. Tree is unchanged. */
{
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
    //if it reaches here, no node with key k was found
    return nullptr;
}

template <typename D, typename K>
void BST<D,K>::remove_helper(Node* temp)
/* Pre:  temp points to a node currently in this BST.
 * Post: Removes the node pointed to by temp. BST property is preserved. */
{
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
        K successor_key = successor(temp->key);
        Node* replace = search_key(successor_key);
        Node* replace_parent = replace->p;

        temp->key = replace->key;
        temp->data = replace->data;

        if (replace->right != nullptr){
            replace_parent->left = replace->right;
            replace->right->p = replace_parent;
        }
        else {replace_parent->left = nullptr;}
    }
}

template <typename D, typename K>
typename BST<D,K>::Node* BST<D, K>::trim_helper(Node* node, K low, K high)
/* Pre:  Keys are comparable; low and high specify an inclusive range.
 * Post: Returns the root of a subtree equal to the original subtree but with nodes outside [low, high] removed; BST property preserved. */
{

    if (node == nullptr) {
        return nullptr;
    }

    node->left = trim_helper(node->left, low, high);
    node->right = trim_helper(node->right, low, high);

    if (node->key < low) {
        Node* right_subtree = node->right;
        delete node;
        return right_subtree;
    } else if (node->key > high) {
        Node* left_subtree = node->left;
        delete node;
        return left_subtree;
    } else {
        return node;
    }
}
