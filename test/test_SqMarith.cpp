#include "mcalc/SqMarith.hpp"
#include <iostream>

using namespace mcalc;

#define DONE (std::cout << "done" << std::endl)

int main() {
    std::cout << "test of SqMarith.hpp" << std::endl;
    std::cout << std::endl;
    SqMarith<double> a({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
    SqMarith<double> b({{0, 1, 2}, {2, 0, 1}, {1, 2, 0}});
    SqMarith<double> i = SqMarith<double>::identity(3);
    SqMarith<double> p_ic = SqMarith<double>::elementary_ic(3, 0, 1);
    SqMarith<double> p_mtpl = SqMarith<double>::elementary_mtpl(3, 2, 10);
    SqMarith<double> p_add = SqMarith<double>::elementary_add(3, 2, 1, -5);
    SqMarith<double> add_a_b = a + b;
    std::cout << "a = " << a << "\tsize of a = " << a.getSize() << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << std::endl;
    std::cout << "a + b = " << add_a_b << "\n";
    std::cout << "a * b = " << a * b << "\n";
    std::cout << "echelon matrix of a = " << a.echelon() << "\n";
    std::cout << "determinant of a = " << a.determinant() << "\n";
    std::cout << "boolian of \"a is a regular matrix\": " << (a.isRegular() ? "true" : "false") << "\n";
    std::cout << "echelon matrix of b = " << b.echelon() << "\n";
    std::cout << "determinant of b = " << b.determinant() << "\n";
    std::cout << "boolian of \"b is a regular matrix\": " << (b.isRegular() ? "true" : "false") << "\n";
    std::cout << std::endl;
    std::cout << "identity matrix =" << i << "\n";
    std::cout << "elementary matricies = " << p_ic << ", " << p_mtpl << ", " << p_add << "\n";
    std::cout << std::endl;
    try {
        std::cout << SqMarith<float>({{1,2}}) << "\n";
    } catch (bad_cast &e) {
        std::cerr << "try to make SqMarith from non-square matrix -> " << e.what() << "\n";
    }
    std::cout << std::endl;

    return 0;
}