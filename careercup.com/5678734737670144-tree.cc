// Google
// Find the Lexicographic next word of the input word from a list of words
// Example
// Words list [cat, dog, cow, donkey, zebra, monkey]
// Input: duck
// Output: monkey
// Input: dog
// Output: donkey
// Can you use trie to solve it?
// public String findNextWord(List<String> words, String input)
// {
// }

#include <string>
#include <memory>
#include <iostream>

class Node {
 public:
  Node(const std::string &word) : word_(word) {}
  const std::string &word() const { return word_; }

  static void insertWord(std::unique_ptr<Node> &tree, const std::string &word)
  {
    if (tree.get() == nullptr)
      tree.reset(new Node(word));
    else if (word < tree->word())
      insertWord(tree->childs_[0], word);
    else
      insertWord(tree->childs_[1], word);
  }

  std::string findNextWord(const std::string &word)
  {
    if (word < word_) {
      std::string w;
      if (childs_[0])
        w = childs_[0]->findNextWord(word);
      return w.empty() ? word_ : w; // if less than me not found then return me
    } else {
      if (!childs_[1])
        return std::string(); // not found
      return childs_[1]->findNextWord(word);
    }
  }

private:
  std::string word_;
  std::unique_ptr<Node> childs_[2];
};

int main() {
  std::unique_ptr<Node> tree;
  for (decltype(auto) w : {"cat", "dog", "cow", "donkey", "zebra", "monkey"})
    Node::insertWord(tree, w);

  std::string w;
  while (true)
  {
    std::cout << "Input: ";
    std::cin >> w;
    if (std::cin.eof())
      break;
    std::cout << "Output: " << tree->findNextWord(w) << std::endl;
  }
}
