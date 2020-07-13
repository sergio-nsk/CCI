#include <cassert>
#include <sstream>
#include <string>
#include <vector>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

void trimLeftTrailingSpaces(std::string& input) {
  input.erase(input.begin(), find_if(input.begin(), input.end(),
                                     [](int ch) { return !isspace(ch); }));
}

void trimRightTrailingSpaces(std::string& input) {
  input.erase(
      find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); })
          .base(),
      input.end());
}

std::vector<int> stringToIntegerVector(std::string input) {
  std::vector<int> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  std::stringstream ss;
  ss.str(input);
  std::string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(stoi(item));
  }
  return output;
}

std::vector<std::string> stringToStringVector(std::string input) {
  std::vector<std::string> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  std::stringstream ss;
  ss.str(input);
  std::string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(item);
  }
  return output;
}

int stringToInteger(const std::string& input) {
  return std::stoi(input);
}

std::string integerVectorToString(const std::vector<int>& list,
                                  int length = -1) {
  if (length == -1)
    length = list.size();

  if (length == 0)
    return "[]";

  std::string result;
  for (int index = 0; index < length; index++) {
    int number = list[index];
    result += std::to_string(number) + ", ";
  }
  return "[" + result.substr(0, result.length() - 2) + "]";
}

std::string vectorOfIntegerVectorsToString(
    const std::vector<std::vector<int>>& list,
    int length = -1) {
  if (length == -1)
    length = list.size();

  if (length == 0)
    return "[]";

  std::string result;
  for (int index = 0; index < length; index++) {
    const std::vector<int>& intVector = list[index];
    result += integerVectorToString(intVector) + ", ";
  }
  return "[" + result.substr(0, result.length() - 2) + "]";
}

ListNode* stringToListNode(const std::string& input) {
  // Generate list from the input
  std::vector<int> list = stringToIntegerVector(input);

  // Now convert that list into linked list
  ListNode* dummyRoot = new ListNode(0);
  ListNode* ptr = dummyRoot;
  for (int item : list) {
    ptr->next = new ListNode(item);
    ptr = ptr->next;
  }
  ptr = dummyRoot->next;
  delete dummyRoot;
  return ptr;
}

std::string listNodeToString(const ListNode* node) {
  if (node == nullptr) {
    return "[]";
  }

  std::string result;
  while (node) {
    result += std::to_string(node->val) + ", ";
    node = node->next;
  }
  return "[" + result.substr(0, result.length() - 2) + "]";
}

std::string stringToString(const std::string& input) {
  assert(input.length() >= 2);
  std::string result;
  for (int i = 1; i < input.length() - 1; i++) {
    char currentChar = input[i];
    if (input[i] == '\\') {
      char nextChar = input[i + 1];
      switch (nextChar) {
        case '\"':
          result.push_back('\"');
          break;
        case '/':
          result.push_back('/');
          break;
        case '\\':
          result.push_back('\\');
          break;
        case 'b':
          result.push_back('\b');
          break;
        case 'f':
          result.push_back('\f');
          break;
        case 'r':
          result.push_back('\r');
          break;
        case 'n':
          result.push_back('\n');
          break;
        case 't':
          result.push_back('\t');
          break;
        default:
          break;
      }
      i++;
    } else {
      result.push_back(currentChar);
    }
  }
  return result;
}

std::string boolToString(bool input) {
  return input ? "True" : "False";
}
