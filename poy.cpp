#include <iostream>
#include <vector>

struct var {
  long number, exponent;
};

static var mult_sub(const var &num, const var &divisor, const var &mult) {
  var minus = {divisor.number * mult.number, divisor.exponent + mult.exponent};
  var ans{2147483647, minus.exponent};
  if (num.exponent == minus.exponent)
    ans.number = num.number - minus.number;
  return ans;
}

void divide(std::vector<var> &dividend, const std::vector<var> &divisor,
            std::vector<var> &quotient) {
  for (unsigned i = 0; i < dividend.size(); i++) {
    var mult = {1, dividend[0].exponent - divisor[0].exponent};
    if (dividend[0].number != 0 && divisor[0].number != 0)
      mult.number = dividend[0].number / divisor[0].number;

    for (unsigned t = 0; t < divisor.size(); t++)
      if (mult_sub(dividend[t], divisor[t], mult).number == 2147483647)
        return;
    quotient.push_back(mult);

    unsigned offset = 0;
    for (unsigned t = 0; t < divisor.size(); t++) {
      dividend[t - offset] = mult_sub(dividend[t - offset], divisor[t], mult);

      if (dividend[t - offset].number == 0) {
        if (dividend.size() == 1)
          return;
        dividend.erase(dividend.begin() + t);
        offset++;
      }
    }
    i -= offset;
  }
}

void output(const std::vector<var> &i) {
  for (unsigned long t = 0; t < i.size(); t++) {
    std::cout << i[t].number << "*x^" << i[t].exponent << " ";
  }
}

int main() {
  std::vector<var> c1 = {{4, 3}, {2, 2}, {-6, 1}, {3, 0}};
  std::vector<var> d1 = {{1, 1}, {-3, 0}};
  std::vector<var> q1;
  divide(c1, d1, q1);
  std::cout << "Quotient: ";
  output(q1);
  std::cout << " Remainder: ";
  output(c1);
  std::cout << "\n";

  std::vector<var> c2 = {{2, 4}, {-9, 3}, {21, 2}, {-26, 1}, {12, 0}};
  std::vector<var> d2 = {{2, 1}, {-3, 0}};
  std::vector<var> q2;
  divide(c2, d2, q2);
  std::cout << "Quotient: ";
  output(q2);
  std::cout << " Remainder: ";
  output(c2);
  std::cout << "\n";

  std::vector<var> c3 = {{10, 4}, {0, 3}, {-7, 2}, {0, 1}, {-1, 0}};
  std::vector<var> d3 = {{1, 2}, {-1, 1}, {3, 0}};
  std::vector<var> q3;
  divide(c3, d3, q3);
  std::cout << "Quotient: ";
  output(q3);
  std::cout << " Remainder: ";
  output(c3);
}
