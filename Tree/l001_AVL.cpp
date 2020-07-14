#include <iostream>
#include <vector>

using namespace std;

// Avl is a self balancing tree (BST) =================================
// condition for height of tree at every node to be balanced is | -1<=(lh - rh)<=1 |
// A prefect balanced BST is AVL;

class Node
{
public:
    int data;
    Node *left = nullptr;  // Node* left=nullptr;
    Node *right = nullptr; // Node* right=nullptr;
    int height;
    int bal;

    Node(int data)
    {
        this->data = data;
        this->height = 0;
        this->bal = 0;
    }
};

void updatedHeight_Balance(Node *node)
{
    int lh = -1, rh = -1;
    if (node->left != nullptr) // getting left height;
        lh = node->left->height;
    if (node->right != nullptr) // getting right height;
        rh = node->right->height;

    node->height = (lh + rh) + 1;
    node->bal = lh - rh;
}

// rr rotation for a ll structure tree ==========================
Node *rrRotaion(Node *A)
{
    Node *B = A->left;
    Node *BkaRight = B->right;

    B->right = A;
    A->left = BkaRight;

    updatedHeight_Balance(A);
    updatedHeight_Balance(B);
    return B;
}

// ll rotation for a rr structure tree ==========================
Node *rrRotaion(Node *A)
{
    Node *B = A->right;
    Node *BkaLeft = B->left;

    B->left = A;
    A->right = BkaLeft;

    updatedHeight_Balance(A);
    updatedHeight_Balance(B);
    return B;
}

int idx = 0;
Node *constructBST(vector<int> &arr, int si, int ei)
{
    if (si > ei)
        return nullptr;

    int mid = (si + ei) >> 1; // (si+ei)/2;
    Node *node = new Node(arr[mid]);
    node->left = constructBST(arr, si, mid - 1);
    node->right = constructBST(arr, mid + 1, ei);

    return node;
}

void display(Node *node)
{
    if (node == nullptr)
        return;

    string str = "";
    str += ((node->left != nullptr) ? to_string(node->left->data) : ".");
    str += " <- " + to_string(node->data) + " -> ";
    str += ((node->right != nullptr) ? to_string(node->right->data) : ".");
    cout << (str) << endl;

    display(node->left);
    display(node->right);
}

void solve()
{
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130};
    Node *root = constructBST(arr, 0, arr.size() - 1);
    display(root);
}

int main()
{
    solve();
    return 0;
}