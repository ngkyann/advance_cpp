#include "../include/adv/store.hpp"
#include <cassert>
#include <iostream>
#include <vector>

void test_basic_ops() {
    adv::store<int> s = {1, 2, 3};
    assert(s.size() == 3);
    assert(s[0] == 1);
    assert(s.back() == 3);
    std::cout << "Test Basic Operations: PASSED\n";
}

void test_slicing() {
    adv::store<int> s = {0, 1, 2, 3, 4, 5};
    // Cắt từ 0 đến 4, bước nhảy 2 -> {0, 2}
    auto sliced = s(0, 4, 2);
    assert(sliced.size() == 2);
    assert(sliced[0] == 0);
    assert(sliced[1] == 2);
    std::cout << "Test Slicing: PASSED\n";
}

void test_set_operations() {
    adv::store<int> a = {1, 2, 3};
    adv::store<int> b = {3, 4, 5};

    // Phép hợp (Union)
    auto u = a | b; // {1, 2, 3, 4, 5}
    assert(u.size() == 5);
    assert(u.contains(1) && u.contains(5));

    // Phép giao (Intersection)
    auto i = a & b; // {3}
    assert(i.size() == 1);
    assert(i[0] == 3);

    // Phép hiệu (Difference)
    auto d = a - b; // {1, 2}
    assert(d.size() == 2);
    assert(!d.contains(3));

    std::cout << "Test Set Operations: PASSED\n";
}

void test_conversion() {
    adv::store<double> s = {1.1, 2.2, 3.3};
    auto s_int = s.to_int();
    assert(s_int[0] == 1);
    
    adv::store<int> s2 = {65, 66};
    auto s_char = s2.to_char();
    assert(s_char[0] == 'A');
    
    std::cout << "Test Conversion: PASSED\n";
}

int main() {
    try {
        test_basic_ops();
        test_slicing();
        test_set_operations();
        test_conversion();
        std::cout << "\nALL TESTS PASSED SUCCESSFULLY!\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}