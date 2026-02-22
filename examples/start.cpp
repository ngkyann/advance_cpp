#include "../include/adv/store.hpp"
#include <iostream>

int main() {
    // 1. Khởi tạo cực nhanh
    adv::store<int> a = {1, 2, 3, 4, 5};
    adv::store<int> b = {4, 5, 6, 7, 8};

    std::cout << "Store A: "; a.print();
    std::cout << "Store B: "; b.print();

    // 2. Phép toán tập hợp (Set operations)
    auto union_set = a | b; 
    std::cout << "Hop (A | B): "; union_set.print();

    // 3. Cắt lát (Slicing) kiểu Python
    // Lấy từ index 0 đến 5, bước nhảy 2
    auto sliced = union_set(0, 5, 2); 
    std::cout << "Sliced (0:5:2): "; sliced.print();

    // 4. Chuyển đổi kiểu (Conversion)
    auto str_store = sliced.to_string();
    std::cout << "Converted to string: "; str_store.print(true, " | ");

    return 0;
}