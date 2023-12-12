#include <math.h>

#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>

const long double kPI = acosl(-1.0);
const long double kTwo = 2.0;
const long double kHalf = 0.5;

size_t FindUpDegTwo(size_t number) {
  size_t deg = 1;
  while (deg < number) {
    deg *= 2;
  }
  return deg;
}

std::vector<std::complex<long double> > ComplexVector(
    const std::vector<int>& aa, size_t nn) {
  std::vector<std::complex<long double> > ca(
      nn, std::complex<long double>(0.0, 0.0));
  for (size_t iter = 0; iter < aa.size(); ++iter) {
    ca[iter] = std::complex<long double>(aa[iter], 0.0);
  }
  return ca;
}

std::vector<std::complex<long double> > MakeGeneralFFT(
    std::vector<std::complex<long double> > ca, std::complex<long double> qq) {
  if (ca.size() == 1) {
    return ca;
  }
  std::vector<std::complex<long double> > a0;
  std::vector<std::complex<long double> > a1;
  for (size_t iter = 0; iter < ca.size() / 2; ++iter) {
    a0.push_back(ca[2 * iter]);
    a1.push_back(ca[2 * iter + 1]);
  }
  a0 = MakeGeneralFFT(a0, qq * qq);
  a1 = MakeGeneralFFT(a1, qq * qq);
  std::complex<long double> ww(1.0, 0.0);
  for (size_t iter = 0; iter < ca.size() / 2; ++iter) {
    std::complex<long double> uu = a0[iter];
    std::complex<long double> vv = ww * a1[iter];
    ca[iter] = uu + vv;
    ca[iter + ca.size() / 2] = uu - vv;
    ww *= qq;
  }
  return ca;
}

std::vector<std::complex<long double> > MakeFFT(
    const std::vector<std::complex<long double> >& ca) {
  long double arg = kTwo * kPI / ca.size();
  return MakeGeneralFFT(ca, std::complex<long double>(cosl(arg), sinl(arg)));
}

std::vector<std::complex<long double> > MakeInverseFFT(
    std::vector<std::complex<long double> > ca) {
  long double arg = kTwo * kPI / ca.size();
  ca = MakeGeneralFFT(ca, std::complex<long double>(cosl(arg), -sinl(arg)));
  for (size_t iter = 0; iter < ca.size(); ++iter) {
    ca[iter] /= ca.size();
  }
  return ca;
}

std::vector<int> MakeIntVector(
    const std::vector<std::complex<long double> >& cc) {
  std::vector<int> ans(cc.size());
  for (size_t iter = 0; iter < cc.size(); ++iter) {
    ans[iter] = static_cast<int>(floorl(cc[iter].real() + kHalf));
  }
  return ans;
}

std::vector<int> MultiplicatePolynoms(const std::vector<int>& aa,
                                      const std::vector<int>& bb) {
  size_t nn = 2 * FindUpDegTwo(std::max(aa.size(), bb.size()));
  std::vector<std::complex<long double> > ca = ComplexVector(aa, nn);
  std::vector<std::complex<long double> > cb = ComplexVector(bb, nn);
  ca = MakeFFT(ca);
  cb = MakeFFT(cb);
  for (size_t iter = 0; iter < nn; ++iter) {
    ca[iter] *= cb[iter];
  }
  std::vector<std::complex<long double> > cc = MakeInverseFFT(ca);
  return MakeIntVector(cc);
}

int main() {
  size_t deg_a;
  size_t deg_b;
  std::cin >> deg_a;
  std::vector<int> aa(deg_a + 1, 0);
  for (size_t iter = 0; iter <= deg_a; ++iter) {
    std::cin >> aa[deg_a - iter];
  }
  std::cin >> deg_b;
  std::vector<int> bb(deg_b + 1, 0);
  for (size_t iter = 0; iter <= deg_b; ++iter) {
    std::cin >> bb[deg_b - iter];
  }
  std::vector<int> ans = MultiplicatePolynoms(aa, bb);
  int count_of_zeroes = 0;
  for (size_t iter = ans.size(); iter > 0; --iter) {
    if (ans[iter - 1] != 0) {
      break;
    }
    ++count_of_zeroes;
  }
  std::cout << ans.size() - count_of_zeroes - 1 << ' ';
  for (size_t iter = ans.size() - count_of_zeroes; iter > 0; --iter) {
    std::cout << ans[iter - 1] << ' ';
  }
  return 0;
}