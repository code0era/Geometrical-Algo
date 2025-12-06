#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;

    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

int height(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

void updateHeight(Node* n) {
    if (n)
        n->height = 1 + max(height(n->left), height(n->right));
}
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void rangeQuery(Node* root, int low, int high) {
    if (!root) return;

    if (low < root->key)
        rangeQuery(root->left, low, high);

    if (low <= root->key && root->key <= high)
        cout << root->key << " ";

    if (root->key < high)
        rangeQuery(root->right, low, high);
}



int main() {
    Node* root = nullptr;
    int values[] = {50, 20, 10, 30, 70, 60, 80, 90, 41,66,97,100};
   

    for (int val : values)
        root = insert(root, val);

    int low = 18, high = 77;
    cout << "Range [" << low << ":" << high << "] -> ";
    rangeQuery(root, low, high);
    cout << "\n";

    return 0;
}


