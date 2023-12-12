#include <iostream>
#include <vector>

const int kSigma = 256;

int FindDegree(int length) {
  int count_bits = 0;
  int count_ones = 0;
  while (length != 0) {
    ++count_bits;
    if ((length & 1) != 0) {
      count_ones++;
    }
    length >>= 1;
  }
  if (count_ones == 1) {
    return count_bits - 1;
  }
  return count_bits;
}

void Print(std::string& str, const std::vector<int>& answer, int length) {
  for (int iter = 0; iter < length; ++iter) {
    std::cout << str[(answer[iter] + length - 1) % length];
  }
}

int Preparing(std::string& str, std::vector<int>& answer,
              std::vector<int>& equivalence, std::vector<int>& cnt,
              int length) {
  for (int iter = 0; iter < length; ++iter) {
    ++cnt[str[iter]];
  }
  for (int iter = 1; iter < kSigma; ++iter) {
    cnt[iter] += cnt[iter - 1];
  }
  for (int iter = 0; iter < length; ++iter) {
    answer[--cnt[str[iter]]] = iter;
  }
  equivalence[answer[0]] = 0;
  int classes = 1;
  for (int iter = 1; iter < length; ++iter) {
    if (str[answer[iter]] != str[answer[iter - 1]]) {
      ++classes;
    }
    equivalence[answer[iter]] = classes - 1;
  }
  return classes;
}

void Solution(std::string& str) {
  int length = static_cast<int>(str.length());
  int max_degree = FindDegree(length);
  std::vector<int> answer(length);
  std::vector<int> equivalence(length);
  std::vector<int> cnt(kSigma, 0);
  std::vector<int> answer_new(length);
  std::vector<int> equivalence_new(length);
  int classes = Preparing(str, answer, equivalence, cnt, length);
  for (int deg = 0; deg < max_degree; ++deg) {
    for (int iter = 0; iter < length; ++iter) {
      answer_new[iter] = answer[iter] - (1 << deg);
      if (answer_new[iter] < 0) {
        answer_new[iter] += length;
      }
    }
    for (int iter = 0; iter < classes; ++iter) {
      if (iter >= static_cast<int>(cnt.size())) {
        cnt.push_back(0);
      }
      cnt[iter] = 0;
    }
    for (int iter = 0; iter < length; ++iter) {
      ++cnt[equivalence[answer_new[iter]]];
    }
    for (int iter = 1; iter < classes; ++iter) {
      cnt[iter] += cnt[iter - 1];
    }
    for (int iter = length - 1; iter >= 0; --iter) {
      answer[--cnt[equivalence[answer_new[iter]]]] = answer_new[iter];
    }
    equivalence_new[answer[0]] = 0;
    classes = 1;
    for (int iter = 1; iter < length; ++iter) {
      int mid_first = (answer[iter] + (1 << deg)) % length;
      int mid_second = (answer[iter - 1] + (1 << deg)) % length;
      if (equivalence[answer[iter]] != equivalence[answer[iter - 1]] ||
          equivalence[mid_first] != equivalence[mid_second]) {
        ++classes;
      }
      equivalence_new[answer[iter]] = classes - 1;
    }
    for (int iter = 0; iter < length; ++iter) {
      equivalence[iter] = equivalence_new[iter];
    }
  }
  Print(str, answer, length);
}

int main() {
  std::string str;
  std::cin >> str;
  Solution(str);
  return 0;
}