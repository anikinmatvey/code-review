#include <iostream>
#include <queue>
#include <vector>

const int kSigma = 26;

struct Node {
  std::vector<int> to;
  std::vector<int> numbers;
  int length;
  bool term;
  Node() {
    to.resize(kSigma, -1);
    term = false;
    numbers.resize(0);
    length = 0;
  }
};

std::vector<Node> trie;

void AddString(const std::string& str, int number) {
  if (trie.empty()) {
    trie.emplace_back();
  }
  int vertex = 0;
  for (char letter : str) {
    if (trie[vertex].to[letter - 'a'] == -1) {
      trie[vertex].to[letter - 'a'] = static_cast<int>(trie.size());
      trie.emplace_back();
    }
    vertex = trie[vertex].to[letter - 'a'];
  }
  trie[vertex].term = true;
  trie[vertex].numbers.push_back(number);
  trie[vertex].length = static_cast<int>(str.size());
}

void PrintingAnswer(const std::vector<int>& comp,
                    const std::vector<std::vector<int>>& go,
                    const std::string& text, int count) {
  std::vector<int> counts(count);
  std::vector<std::vector<int>> positions(count);
  std::vector<int> answering(text.length() + 1);
  answering[0] = 0;
  for (int i = 1; i <= static_cast<int>(text.length()); ++i) {
    answering[i] = go[answering[i - 1]][text[i - 1] - 'a'];
    int index = answering[i];
    while (index > 0) {
      if (trie[index].term) {
        for (int num = 0; num < static_cast<int>(trie[index].numbers.size());
             ++num) {
          ++counts[trie[index].numbers[num]];
          positions[trie[index].numbers[num]].push_back(i - trie[index].length +
                                                        1);
        }
      }
      index = comp[index];
    }
  }
  for (int i = 0; i < count; ++i) {
    std::cout << counts[i] << ' ';
    for (int pos : positions[i]) {
      std::cout << pos << ' ';
    }
    std::cout << '\n';
  }
}

void Solution(const std::string& text, int count) {
  std::vector<int> comp(trie.size());
  std::vector<int> link(trie.size());
  std::vector<std::vector<int>> go(trie.size(), std::vector<int>(kSigma));
  link[0] = 0;
  comp[0] = 0;
  for (int letter = 0; letter < kSigma; ++letter) {
    go[0][letter] = trie[0].to[letter] != -1 ? trie[0].to[letter] : 0;
  }
  std::queue<int> my_queue;
  my_queue.push(0);
  while (!my_queue.empty()) {
    int vertex = my_queue.front();
    my_queue.pop();
    for (int letter = 0; letter < kSigma; ++letter) {
      int child = trie[vertex].to[letter];
      if (child == -1) {
        continue;
      }
      link[child] = (vertex == 0 ? 0 : go[link[vertex]][letter]);
      comp[child] = trie[link[child]].term ? link[child] : comp[link[child]];
      for (int nl = 0; nl < kSigma; ++nl) {
        go[child][nl] = (trie[child].to[nl] != -1 ? trie[child].to[nl]
                                                  : go[link[child]][nl]);
      }
      my_queue.push(child);
    }
  }
  PrintingAnswer(comp, go, text, count);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int count;
  std::string text;
  std::string word;
  std::cin >> text;
  std::cin >> count;
  for (int i = 0; i < count; ++i) {
    std::cin >> word;
    AddString(word, i);
  }
  Solution(text, count);
  return 0;
}