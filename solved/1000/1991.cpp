#include <iostream>

using namespace std;
struct node {
    char data;
    node *left = nullptr;
    node *right = nullptr;
};
int n;
void preorder(node *n) {
    cout << n->data;
    if (n->left != nullptr) {
        preorder(n->left);
    }
    if (n->right != nullptr) {
        preorder(n->right);
    }
}

void inorder(node *n) {
    if (n->left != nullptr) {
        inorder(n->left);
    }
    cout << n->data;
    if (n->right != nullptr) {
        inorder(n->right);
    }
}

void postorder(node *n) {
    if (n->left != nullptr) {
        postorder(n->left);
    }
    if (n->right != nullptr) {
        postorder(n->right);
    }
    cout << n->data;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    node arr[n];
    char s, e, t;
    for (int i = 0; i < n; i++) {
        cin >> s >> e >> t;
        arr[i].data = 'A' + i;
        if (e != '.') {
            arr[s - 'A'].left = &arr[e - 'A'];
        }
        if (t != '.') {
            arr[s - 'A'].right = &arr[t - 'A'];
        }
    }
    preorder(&arr[0]);
    cout << '\n';
    inorder(&arr[0]);
    cout << '\n';
    postorder(&arr[0]);
}