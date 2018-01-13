// Check if the tree is a binary search tree.

struct Node {
  Node* left;
  Node* right;
  int value;
};

static bool CheckBST(const Node* node, const int* min, const int* max) {
  if (!node)
    return true;
  if (min && node->value <= *min)
    return false;
  if (max && node->value > *max)
    return false;
  return CheckBST(node->left, min, &node->value) &&
         CheckBST(node->right, &node->value, max);
}

bool CheckBST(const Node* root) {
  return CheckBST(root, nullptr, nullptr);
}
