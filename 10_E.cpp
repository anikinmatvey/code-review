#include <iostream>
#include <queue>
#include <vector>

const int kSigma = 10;

struct Node {
  std::vector<long long> to;
  long long deep;
  long long prev;
  long long count_of_term;
  bool term;
  Node() {
    to.resize(kSigma, -1);
    deep = 0;
    prev = -1;
    count_of_term = 0;
    term = false;
  }
};

long long max_deep = 0;
std::vector<Node> trie;
std::vector<long long> answers;

void AddString(const std::string& str) {
  if (trie.empty()) {
    trie.emplace_back();
  }
  long long vertex = 0;
  for (char letter : str) {
    if (trie[vertex].to[letter - '0'] == -1) {
      trie[vertex].to[letter - '0'] = static_cast<int>(trie.size());
      trie.emplace_back();
      trie.back().deep = trie[vertex].deep + 1;
      trie.back().prev = vertex;
      max_deep = std::max(max_deep, trie.back().deep / 2);
    }
    vertex = trie[vertex].to[letter - '0'];
  }
  trie[vertex].term = true;
  long long index = vertex;
  while (index >= 0) {
    ++trie[index].count_of_term;
    index = trie[index].prev;
  }
}

void Dfs(long long size) {
  answers.resize(max_deep + 1, 0);
  for (const auto& iter : trie) {
    if (iter.count_of_term >= size && iter.deep % 2 == 0) {
      ++answers[iter.deep / 2];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long count;
  long long size;
  std::cin >> count >> size;
  std::string number;
  for (long long i = 0; i < count; ++i) {
    std::cin >> number;
    std::string new_number;
    for (size_t letter = 0; letter < number.size(); ++letter) {
      new_number += number[letter];
      new_number += number[number.size() - letter - 1];
    }
    AddString(new_number);
  }
  Dfs(size);
  long long length;
  long long request_count;
  std::cin >> request_count;
  for (long long i = 0; i < request_count; ++i) {
    std::cin >> length;
    if (length >= static_cast<long long>(answers.size())) {
      std::cout << 0 << '\n';
    } else {
      std::cout << answers[length] << '\n';
    }
  }
  return 0;
}