#include "mcalc/Marith.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace mcalc;

int main() {
    std::cout << "test of Marith.hpp" << std::endl;
    std::cout << std::endl;
    double s = 3;
    Marith<double> a(V2<double>({{2, 2, 1}, {1, 2, 2}}));
    Marith<double> b(V2<double>({{1, 3, 5}, {2, 4, 6}}));
    Marith<double> ta = a.transpose();
    std::cout << "s = " << s << "\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << std::endl;
    std::cout << "^ta = " << ta << "\n";
    std::cout << "a + b = " << a + b << "\n";
    std::cout << "a - b = " << a - b << "\n";
    std::cout << "s * a = " << s * a << "\n";
    std::cout << "a * ^ta = " << a * a.transpose() << "\n";
    std::cout << std::endl;
    std::cout << "echelon matrix of a = " << a.echelon() << "\n";
    std::cout << "rank of a = " << a.getRank() << "\n";
    std::cout << std::endl;
    try {
        a.at(100, 100);
    } catch (const out_of_range &e) {
        std::cerr << "try a.at(100, 100) -> " << e.what() << '\n';
    }
    try {
        a * b;
    } catch (const range_error &e) {
        std::cerr << "try a * b -> " << e.what() << '\n';
    }
    std::cout << std::endl;

    std::cout << Marith<double>({{1, -1, 0, -1}, {2, 1, 1, -9}, {0, 3, -5, -1}, {4, -3, -2, 4}}).echelon() << std::endl;

    return 0;
}