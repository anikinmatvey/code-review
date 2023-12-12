#include <iostream>

const unsigned long long kShift = 30;

std::pair<unsigned long long, unsigned long long> Decomposition(
    unsigned long long pp) {
  unsigned long long count = 0;
  while (pp % 2 == 0) {
    ++count;
    pp /= 2;
  }
  std::pair<unsigned long long, unsigned long long> result(count, pp);
  return result;
}

unsigned long long BinPow(unsigned long long xx, unsigned long long yy,
                          unsigned long long zz) {
  if (yy == 0) {
    return 1;
  }
  if (yy % 2 == 0) {
    return (BinPow(xx, yy / 2, zz) * BinPow(xx, yy / 2, zz)) % zz;
  }
  return (xx * BinPow(xx, yy - 1, zz)) % zz;
}

void GetAnswer(unsigned long long aa, unsigned long long pp) {
  std::cout << BinPow(aa, (pp + 1) / 4, pp) << '\n';
}

void Solution(unsigned long long aa, unsigned long long pp) {
  std::pair<unsigned long long, unsigned long long> decomposition =
      Decomposition(pp - 1);
  unsigned long long ss = decomposition.first;
  unsigned long long qq = decomposition.second;
  if (ss <= 1) {
    GetAnswer(aa, pp);
    return;
  }
  unsigned long long zz = 2;
  while (BinPow(zz, (pp - 1) / 2, pp) != pp - 1) {
    ++zz;
  }
  unsigned long long mm = ss;
  unsigned long long cc = BinPow(zz, qq, pp);
  unsigned long long tt = BinPow(aa, qq, pp);
  unsigned long long rr = BinPow(aa, (qq + 1) / 2, pp);
  while (true) {
    if (tt % pp == 1) {
      std::cout << rr % pp << '\n';
      return;
    }
    unsigned long long findi = 0;
    unsigned long long tempt = tt;
    while (tempt != 1) {
      ++findi;
      tempt = (tempt * tempt) % pp;
    }
    unsigned long long shift = mm - findi - 1;
    if (shift < 0 || shift > kShift) {
      return;
    }
    unsigned long long bb = BinPow(cc, (1 << shift), pp);
    rr = (rr * bb) % pp;
    cc = (bb * bb) % pp;
    tt = (tt * cc) % pp;
    mm = findi;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  unsigned long long count;
  unsigned long long aa;
  unsigned long long pp;
  std::cin >> count;
  for (unsigned long long iter = 0; iter < count; ++iter) {
    std::cin >> aa >> pp;
    if (pp == 2) {
      std::cout << aa << '\n';
    } else if (BinPow(aa, (pp - 1) / 2, pp) == 1) {
      Solution(aa, pp);
    } else {
      std::cout << "IMPOSSIBLE" << '\n';
    }
  }
  return 0;
}