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
  std::vector<int> preorderTraversal(const TreeNode* root) const {
    std::vector<int> out;
    Traversal(root, out);
    return out;
  }

 private:
  void Traversal(const TreeNode* root, std::vector<int>& out) const {
    if (!root)
      return;
    out.push_back(root->val);
    Traversal(root->left, out);
    Traversal(root->right, out);
  }
};

class SolutionIterative {
 public:
  std::vector<int> preorderTraversal(const TreeNode* root) const {
    std::vector<int> out;
    std::stack<const TreeNode*> st;
    if (!root)
      return out;
    out.push_back(root->val);
    st.push(root);
    while (true) {
      if (root->left) {
        root = root->left;
      } else if (root->right) {
        root = root->right;
      } else {
        while (true) {
          st.pop();
          if (st.empty())
            break;
          const TreeNode* up = st.top();
          if (up->right && root != up->right) {
            root = up;
            break;
          }
          root = up;
        }
        if (st.empty())
          break;
        root = root->right;
      }
      out.push_back(root->val);
      st.push(root);
    }
    return out;
  }
};