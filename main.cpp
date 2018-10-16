/* copyright (c) Grant Rostig 2018
   MIT license
*/ 


#include "../../Dropbox/src/utils/cpp_headers.h"
#include "../../Dropbox/src/utils/math_grostig.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// template <typename T> // utility f() to print vectors
// std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
//  if (!v.empty()) {
//    out << '[';
//    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
//    out << "\b\b]";
//  }
//  return out;
//}

// double n_Choose_k(unsigned long const n,
//                  unsigned long k) // copy of k is mutated.
//{
//  if (k > n)
//    return 0;
//  if (k * 2 > n)
//    k = n - k;
//  if (k == 0)
//    return 1;

//  double result = n;
//  for (unsigned long i = 2; i <= k; ++i) {
//    result *= (n - i + 1);
//    result /= i;
//  }
//  return result;
//}

// double factorial(unsigned long const x, unsigned long const result = 1) {
//  if (x == 1)
//    return result;
//  else
//    return factorial(x - 1, x * result);
//}

// double m_subH_max(unsigned long const n_uc, unsigned long const vc_dim) {
//  double sum = 0;
//  for (unsigned long i = 0; i <= vc_dim; i++) {
//    sum += n_Choose_k(n_uc, i);
//  }
//  return sum;
//}

int main(/*int argc, char *argv[]*/) {
  //    cout << "\n 50 choose 3 is: "<< nChoosek(50, 3);
  //    cout << "\n factorial(20) : " <<
  //    factorial(20)/*/factorial(3)*factorial(50-3)*/;

  //    unsigned long n = 480000;
  //    cout << "\n std::pow(n,2): " << std::pow(n,2);

  double delta = 0.05;
  unsigned long vc_dim = 10;

  //    cout << "\n m_subH_max, approx N^VCdim: " << m_subH_max(n,vc_dim) << ",
  //    " << pow(n,vc_dim);
  //    double result1 =
  //    std::sqrt((8.0/n)*log(4.0*(m_subH_max(2.0*n,vc_dim)/delta)));

  auto generalization_error_est = [vc_dim, delta](double n) {
    double z = std::sqrt((8.0 / n) * log(4.0 * (pow(2.0 * n, vc_dim) / delta)));
    return z;
  };
  auto generalization_error = [vc_dim, delta](double n) {
    double z =
        std::sqrt((8.0 / n) * log(4.0 * (m_subH_max(2 * n, vc_dim) / delta)));
    return z;
  };
  std::vector<double> n_tests = {400'000, 420'000, 440'000, 460'000, 480'000};
  std::vector<double> ge_est; // trick to easily create destination for results.
                              // todo better way to do that using auto??
  ge_est.reserve(n_tests.size()); // coded here just for reference, not needed
                                  // due to small size. Don't do this when
                                  // push_back is to be used unless you know
                                  // eventual size??? todo
  std::vector<double> ge; // trick to easily create destination for results.
                          // todo better way to do that using auto??
  // https://www.fluentcpp.com/2017/02/13/transform-central-algorithm/
  std::transform(n_tests.begin(), n_tests.end(), std::back_inserter(ge_est),
                 generalization_error_est);
  std::transform(n_tests.begin(), n_tests.end(), std::back_inserter(ge),
                 generalization_error);
  cout << "\n ge_est: " << ge_est;
  cout << "\n ge    : " << ge;
  // another way to approach above problem:
  // http://nbviewer.jupyter.org/github/tournami/Learning-From-Data-MOOC/blob/master/Homework%204.html

  unsigned long n = 10000;
  vc_dim = 50;

  double result1 =
      std::sqrt((8.0 / n) * log(4.0 * (pow(2.0 * n, vc_dim) / delta)));

  double result1a =
      std::sqrt((8.0 / n) * log(4.0 * (m_subH_max(2.0 * n, vc_dim) / delta)));

  double result2 = std::sqrt(2 * log(2 * n * (m_subH_max(n, vc_dim)) / n)) +
                   sqrt((2 / n) * log(1 / delta)) + 1 / n;
  double result3 = ge_converge1(vc_dim, n, delta);
  double result4 = ge_converge2(vc_dim, n, delta);

  cout << "\n result 1, 1a, 2, 3, 4 : " << result1 << ", " << result1a << ", "
       << result2 << ", " << result3 << ", " << result4;

  n = 5;
  vc_dim = 50;

  result1 = std::sqrt((8.0 / n) * log(4.0 * (pow(2.0 * n, vc_dim) / delta)));

  result1a =
      std::sqrt((8.0 / n) * log(4.0 * (m_subH_max(2.0 * n, vc_dim) / delta)));

  result2 = std::sqrt(2 * log(2 * n * (m_subH_max(n, vc_dim)) / n)) +
            sqrt((2 / n) * log(1 / delta)) + 1 / n;
  result3 = ge_converge1(vc_dim, n, delta);
  result4 = ge_converge2(vc_dim, n, delta);

  cout << "\n result 1, 1a, 2, 3, 4 : " << result1 << ", " << result1a << ", "
       << result2 << ", " << result3 << ", " << result4;
  cout << "\n ###" << endl;

  return 0;
}
