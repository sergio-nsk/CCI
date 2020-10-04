// Binary Tree Preorder Traversal
//
// Input: [1,null,2,3]
//    1
//     \
//      2
//     /
//    3
// Output: [1,2,3]
// Follow up: Recursive solution is trivial, could you do it iteratively?

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <stack>
#include <vector>

class Solution {
 public:
  std::vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> out;
    Traversal(root, out);
    return out;
  }

 private:
  void Traversal(TreeNode* root, std::vector<int>& out) {
    if (!root)
      return;
    Traversal(root->left, out);
    out.push_back(root->val);
    Traversal(root->right, out);
  }
};

class SolutionIterative {
 public:
  std::vector<int> inorderTraversal(const TreeNode* root) const {
    std::vector<int> out;
    std::stack<const TreeNode*> st;
    if (!root)
      return out;
    while (true) {
      if (!root) {
        if (st.empty())
          break;
        root = st.top();
        st.pop();
        out.push_back(root->val);
        root = root->right;
        continue;
      }
      if (root->left) {
        st.push(root);
        root = root->left;
      } else {
        out.push_back(root->val);
        root = root->right;
      }
    }
    return out;
  }
};