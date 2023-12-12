#include <iostream>

const int kEight = 8;
const int kFour = 4;

int Symbol(long long aa, long long pp) {
  if (aa == 1) {
    return 1;
  }
  if (aa % 2 == 0) {
    if (((pp * pp - 1) / kEight) % 2 == 0) {
      return Symbol(aa / 2, pp);
    }
    return -Symbol(aa / 2, pp);
  }
  if (((aa - 1) * (pp - 1) / kFour) % 2 == 0) {
    return Symbol(pp % aa, aa);
  }
  return -Symbol(pp % aa, aa);
}

std::pair<long long, long long> Decomposition(long long pp) {
  long long count = 0;
  while (pp % 2 == 0) {
    ++count;
    pp /= 2;
  }
  std::pair<long long, long long> result(count, pp);
  return result;
}

void GetAnswer(long long aa, long long pp) {
  long long answer = 1;
  for (long long iter = 0; iter < (pp + 1) / 4; ++iter) {
    answer = (answer * aa) % pp;
  }
  std::cout << answer << '\n';
}

void Solution(long long aa, long long pp) {
  const int kShift = 31;
  std::pair<long long, long long> decomposition = Decomposition(pp - 1);
  long long ss = decomposition.first;
  long long qq = decomposition.second;
  if (ss == 1) {
    GetAnswer(aa, pp);
    return;
  }
  long long zz = 2;
  long long cc = 1;
  long long tt = 1;
  for (long long iter = 0; iter < qq; ++iter) {
    cc = (cc * zz) % pp;
    tt = (tt * aa) % pp;
  }
  long long rr = 1;
  for (long long iter = 0; iter < (qq + 1) / 2; ++iter) {
    rr = (rr * aa) % pp;
  }
  long long mm = ss;
  while (true) {
    if (tt % pp == 1) {
      std::cout << rr % pp << '\n';
      return;
    }
    long long findi = 0;
    for (long long iter = 1; iter < mm; ++iter) {
      long long tempt = 1;
      for (long long deg = 0; deg < (1 << iter); ++deg) {
        tempt = (tempt * tt) % pp;
      }
      if (tempt % pp == 1) {
        findi = iter;
        break;
      }
    }
    long long bb = 1;
    int shift = static_cast<int>(mm - findi - 1);
    if (shift < 0) {
      shift = 0;
    }
    if (shift > kShift) {
      shift = kShift;
    }
    for (long long iter = 0; iter < (1 << shift); ++iter) {
      bb = (bb * cc) % pp;
    }
    rr = (rr * bb) % pp;
    tt = (tt * bb * bb) % pp;
    cc = (bb * bb) % pp;
    mm = findi;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long count;
  long long aa;
  long long pp;
  std::cin >> count;
  for (long long iter = 0; iter < count; ++iter) {
    std::cin >> aa >> pp;
    if (pp == 2) {
      std::cout << aa << '\n';
    } else if (Symbol(aa, pp) == 1) {
      Solution(aa, pp);
    } else {
      std::cout << "IMPOSSIBLE" << '\n';
    }
  }
  return 0;
}