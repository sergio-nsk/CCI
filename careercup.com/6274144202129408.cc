// https://careercup.com/question?id=6274144202129408
// Amazon
// You are given with a large paragraph and N words.
// You have to find a min length subparagraph of the paragraph which contain all those N words in any order.
// Here length of a paragraph is the count of words in the paragraph.

#include <unordered_map>
#include <string>
#include <deque>
#include <iostream>

class Slider {
 public:
  Slider(const std::deque<std::string>& para, const std::deque<std::string>& words) : para_(para) {
    if (para.size() < words.size())
      return;
    for (auto &w : words)
      words_[w]++;
    words_left_ = words.size();
    min_para_ = std::make_pair(0, -1);
  }

  bool next_word() {
    if (!words_left_) {
      next_site();
    }
    if (idx_ >= para_.size())
      return false;
    auto w = para_[idx_++];
    auto it = words_.find(w);
    if (it == words_.end()) {
      if (length_ == 0) {
        // if slider is empty then start with the next word; this condition can be removed.
        ++site_;
        return true;
      } else {
        ++length_;
      }
    } else {
      ++length_;
      // negative is ok, but if positive then less words left to find
      if ((--it->second) >= 0) {
        --words_left_;
      }
    }
    return true;
  }

  int site() const {
    return min_para_.first;
  }

  int length() const {
    return min_para_.second;
  }

 private:
  void next_site()
  {
    while (!words_left_) {
      // if no words to find left then check if new subparagraph is less than prev one
      if (min_para_.second == -1 || min_para_.second > length_) {
        min_para_.first = site_;
        min_para_.second = length_;
      }
      // try move slider right
      --length_;
      auto w = para_[site_++];
      auto it = words_.find(w);
      if (it != words_.end() && (++it->second) > 0) {
        ++words_left_;
      }
    }
  }

  const std::deque<std::string> &para_;
  std::unordered_map<std::string, int> words_; // words and word counts
  int words_left_;  // number of words left to find
  int site_ = 0;    // slider start
  int length_ = 0;  // slider length
  int idx_ = 0;     // next word following slider
  std::pair<int, int> min_para_;  // subparagraph idx and length
};

int main() {
  std::deque<std::string> para = {"alpha", "beta", "gamma", "beta", "aba", "beta", "zeta", "beta", "zen", "cat", "car", "beta", "aba", "beta", "broad"};
  std::deque<std::string> words = {"aba", "beta", "cat", "beta"};

  Slider slider(para, words);
  while (slider.next_word())
    ;
  if (slider.length() > 0)
    std::cout << "Min subparagraph length is " << slider.length() << std::endl;
}
