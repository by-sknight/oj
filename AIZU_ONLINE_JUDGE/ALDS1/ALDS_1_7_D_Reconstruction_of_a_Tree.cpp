#include <bits/stdc++.h>
#include <iomanip>

#define MAX 50

struct Node {
    int left = -1;
    int right = -1;
};

int preorder[MAX];
int inorder[MAX];
Node nodes[MAX];
int root;

void build_tree(int p_left, int i_left, int len) {
    int now = preorder[p_left];
    int pos = i_left;
    while (pos < i_left + len) {
        if (inorder[pos] == now) {
            break;
        }
        pos++;
    }
    if (pos != i_left) { // have a left tree
        nodes[now].left = preorder[p_left + 1];
        build_tree(p_left + 1, i_left, pos - i_left);
    }
    if (pos != i_left + len - 1) { // have a right tree
        nodes[now].right = preorder[p_left + pos - i_left + 1];
        build_tree(p_left + pos - i_left + 1, pos + 1, i_left + len - pos - 1);
    }
}

bool first_output = true;
void postorder(int now) {
    if (now == -1)
        return;
    postorder(nodes[now].left);
    postorder(nodes[now].right);
    if (!first_output) {
        std::cout << " ";
    }
    std::cout << now;
    first_output = false;
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> preorder[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> inorder[i];
    }
    build_tree(0, 0, n);
    root = preorder[0];
    postorder(root);
    std::cout << std::endl;
}

// 主要思路是理解遍历
//   前序遍历是先自己，然后左子树，然后右子树
//   中序遍历是先左子树，然后自己，最后右子树
// 因此重建树的时候，前序遍历的首元素a，就是当前子树的根节点，然后中序遍历中，找到它的位置m，如果前面有元素，就意味着存在左子树，因此前序遍历中，a下一个元素，就是a的左子树的根节点
//   如果m后面有元素，就意味着存在右子树，前序遍历中，找到 m-中序首元素位置 是左子树中节点数量，a向后找对应数量+1的元素，就是右子树的根节点，然后依次拆分递归下去，构建出所有的树
