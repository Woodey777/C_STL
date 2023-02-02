#include <string.h>

#include <initializer_list>
#include <iostream>
#include <list>

#include "Algorithms.h"
#include "Container.h"
#include "Exceptions.h"
#include "Iterator.h"

struct Deal {
  std::string prodName;
  double price;
  int quantity;
  std::string buyer;

  Deal() noexcept : prodName("\0"), price(.0), quantity(0), buyer("\0") {}

  Deal(const std::string& prod, double pr, int q,
       const std::string& consumer) noexcept
      : prodName(prod), price(pr), quantity(q), buyer(consumer) {}

  friend bool isEmpty(const Deal& el) {
    return ((el.prodName == "") && (el.price == 0) && (el.quantity == 0) &&
            (el.buyer == ""));
  }

  friend std::ostream& operator<<(std::ostream& out, const Deal& el) noexcept {
    if (!isEmpty(el)) {
      out << "Product:" << el.prodName << std::endl;
      out << "Price:" << el.price << std::endl;
      out << "Quantity:" << el.quantity << std::endl;
      out << "Buyer's name:" << el.buyer << std::endl;
    } else {
      out << "Object is empty" << std::endl;
    }
    return out;
  }
};

class SumFunctor {
  long sum;

 public:
  SumFunctor() : sum(0) {}
  void operator()(int& it) { sum += it; }
  void PrintSum() { std::cout << sum << std::endl; }
};

auto print = [](const auto& x) {
  std::cout << x << endl;
  return x;
};

int main() {
  std::list<int> ls({1, 2, 3});
  Vector<int> v1(ls.begin(), ls.end());
  SumFunctor sum;

  sum = forEach(v1.begin(), v1.end(), sum);
  cout << "Sum of v1 elements = ";
  sum.PrintSum();

  Vector<int>::iterator res = minElement(v1.begin(), v1.end());
  std::cout << "MinElement in v1 - ";
  print(*res);

  try {
    std::cout << "\t\tTest Create" << std::endl;
    Vector<Deal> t1{{"PSP", 1000, 50, "GameStop"}, {"Chair", 500, 200, "Hoff"}};
    forEach(t1.begin(), t1.end(), print);

    std::cout << "\t\tTest PushBack" << std::endl;
    Deal new1{"PC", 5000, 20, "MSTU"};
    Vector<Deal> t2;
    t2.pushBack(new1);
    forEach(t2.begin(), t2.end(), print);

    std::cout << "\t\tTest Insert1" << std::endl;
    Deal new2{"HDD", 1000, 300, "Google"};
    t2.insert(t2.end(), new2);
    forEach(t2.begin(), t2.end(), print);

    std::cout << "\t\tTest Insert2" << std::endl;
    t1.insert(t1.begin(), t2.begin(), t2.end());
    forEach(t1.begin(), t1.end(), print);

    std::cout << "\t\tTest FindIf" << std::endl;
    Vector<Deal>::iterator found =
        findIf(t1.begin(), t1.end(),
               [](const auto& it) { return it.buyer == "Google"; });
    print(*found);

    std::cout << "\t\tTest Sort" << std::endl;
    Sort(t1.begin(), t1.end(), [](const auto& it1, const auto& it2) {
      return it1.price < it2.price;
    });
    forEach(t1.begin(), t1.end(), print);

    std::cout << "\t\tTest CopyIf" << std::endl;
    copyIf(t1.begin(), t1.end(), t2.begin(),
           [](const auto& el) { return el.price >= 5000; });
    forEach(t2.begin(), t2.end(), print);
  } catch (const std::exception& err) {
    std::cout << err.what();
  }
  return 0;
}
