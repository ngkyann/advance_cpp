\# Advance C++ Library (adv::)



\*\*Advance\*\* là một hệ sinh thái các thư viện C++ Modern Header-only, được xây dựng với mục tiêu: \*\*"Nhanh hơn - Ít lỗi hơn - Thân thiện hơn"\*\*.



Dự án này cung cấp các công cụ và cấu trúc dữ liệu cải tiến, giúp lập trình viên C++ xử lý các tác vụ phức tạp bằng những cú pháp ngắn gọn và an toàn, mang lại trải nghiệm giống như các ngôn ngữ bậc cao (Python, JavaScript) nhưng vẫn giữ nguyên hiệu năng của C++.



---



\## ✨ Triết lý thiết kế

\- \*\*Header-only:\*\* Chỉ cần include là dùng, không cần cấu hình build phức tạp.

\- \*\*Tính trực quan:\*\* Cú pháp gần gũi, hỗ trợ hầu hết các nhu cầu phổ biến.

\- \*\*Quản lý lỗi thông minh:\*\* Cho phép linh hoạt lựa chọn giữa ném ngoại lệ (Exception) hoặc sử dụng mã thoát (Exit code).

\- \*\*Tính tương thích:\*\* Dễ dàng chuyển đổi qua lại với các container chuẩn của STL (`std::vector`, `std::deque`, `std::array`).



\## 📦 Các thành phần chính



\### 1. adv::store (v1.0 - Ổn định)

Cấu trúc dữ liệu danh sách cải tiến, kế thừa từ `std::deque` với những thứ đặc trưng là:

\- \*\*Slicing:\*\* Hỗ trợ cắt lát mảng cực nhanh: `s(start, end, step)`.

\- \*\*Set Operations:\*\* Hỗ trợ các phép toán tập hợp trực quan: `|` (hợp), `\&` (giao), `-` (hiệu), `%` (phần bù).

\- \*\*Utility:\*\* Tích hợp sẵn `print()`, `sort()`, `filter()`, `transform()` và các hàm chuyển đổi kiểu (`to\_int`, `to\_string`,...).

\### 2. adv::store (v1.1 - Hiện đang trong quá trình kiểm thử)

\### 3. adv::store (v2.0 - Hiện đang trong quá trình phát triển)

\### 4. adv::astring (v1.0 - Hiện đang trong quá trình phát triển)

---



\## 🛠 Cách sử dụng

Vì là thư viện Header-only, bạn chỉ cần tải thư mục `include/adv` và đặt vào dự án của mình.
Lưu ý: thư viện này chỉ hỗ trợ từ C++17 trở lên (bản gốc).

\## ⚖️ Bản quyền và bảo mật

- License: MIT License.
- Security: SLSA Level 3 Certified.
- Product ID: Mỗi sản phẩm (thư viện) thuộc adv:: sở hữu một mã định danh(id) duy nhất để ngăn chặn việc tái bản, giả mạo mã nguồn.(ví dụ trong store v1.0 có id là: #.4ß&Q3O$i:M<J<tn).
