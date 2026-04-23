# 🚀 ngkyann's Development Workspace

**Chào mừng bạn đến với kho lưu trữ mã nguồn của Nguyễn Kỳ An.**  
Đây là không gian thử nghiệm và phát triển các cấu trúc dữ liệu nâng cao, thư viện hiệu năng cao và các giải pháp lập trình hiện đại. Với hơn nhiều năm kinh nghiệm trong lĩnh vực lập trình, tôi tập trung xây dựng những công cụ giúp developer viết code nhanh hơn, chạy hiệu quả hơn và dễ bảo trì hơn.

## ✨ Triết lý thiết kế (Design Philosophy)

Mọi dòng code trong không gian này đều được xây dựng dựa trên **3 trụ cột chính**:

1. **Hiệu năng là cốt lõi (Performance First)**  
   Tận dụng tối đa sức mạnh của ngôn ngữ (C++17, C#) để đạt tốc độ xử lý cao nhất với mức tiêu thụ tài nguyên thấp nhất. Các thư viện được tối ưu sâu về bộ nhớ, cache-friendly và thời gian chạy.

2. **Trải nghiệm người dùng (Developer Experience)**  
   Code không chỉ để máy chạy, mà phải để người đọc cảm thấy dễ chịu. Tôi ưu tiên các cú pháp ngắn gọn, an toàn, hiện đại và gần với ngôn ngữ tự nhiên (Python-style indexing, LINQ-like operations,…).

3. **Cấu trúc tinh gọn (Keep It Simple)**  
   Thiết kế theo hướng module hóa, header-only (C++) hoặc idiomatic .NET (C#), giúp việc tích hợp vào các dự án khác trở nên nhanh chóng mà không cần cấu hình phức tạp.

## 🌟 Các Dự Án Nổi Bật

### 📁 C++ Workspace – Thư viện Store Tối Ưu C++17
- **store.hpp**: Phiên bản container generic `store<T>` được tối ưu toàn diện cho C++17.
- **Cải thiện hiệu năng**: 25-40% cho workload thông thường (nối chuỗi nhanh hơn 51%, tìm kiếm nhanh hơn 22%, clone nhanh hơn 10%,…) so với bản cũ.
- Sử dụng nhiều tính năng C++17: `std::string_view`, `std::optional`, structured bindings, `constexpr`, `[[nodiscard]]`, move semantics,… giúp nâng cao chất lượng.
- Code sạch hơn, an toàn kiểu mạnh hơn, dễ bảo trì và tương thích ngược cao.

### 📁 C# & .NET Workspace – Store<T> cho Game & Ứng dụng OOP
- **Store<T>**: Phiên bản C# hoàn chỉnh được chuyển đổi từ C++ với phong cách idiomatic .NET.
- Hỗ trợ đầy đủ: index âm (Python-style), slice, clone system, quản lý lỗi thread-safe (`ThreadLocal`), LINQ integration, collection initializer…
- Tích hợp hoàn hảo với Unity, WPF, MAUI và các dự án .NET 10+.
- Hiện đang trong quá trình phát triển để hỗ trợ game và ứng dụng khác.

## 📂 Cấu trúc dự án (Project Structure)

Dự án được chia thành các phân vùng chuyên biệt. Để xem chi tiết các tính năng, benchmark, ví dụ sử dụng và hướng dẫn di chuyển, vui lòng truy cập vào từng thư mục:

* **[📁 C++ Workspace](./cpp/advance)**: Hệ sinh thái các thư viện Modern C++ tối ưu, phục vụ cho các thuật toán và giải quyết các bài toán hiệu quả.  
  *(Chứa `store.hpp` và vài thứ khác)*

* **[📁 C# & Unity Workspace](./csharp/Advance)**: Nơi hỗ trợ Game, ứng dụng OOP và quy trình phát triển Game cũng như các dự án khác. 
  *(Chứa `Store<T>` và vài thứ khác)*

## 🛠️ Công cụ & Công nghệ

Tôi sử dụng các công nghệ hiện đại để đảm bảo quy trình phát triển được an toàn, nhất quán và hiệu quả cao:

* **Ngôn ngữ chính:**  
  - **C++17** (ISO/IEC 14882:2017) – Tối ưu hiệu năng và xử lí mạnh mẽ.
  - **C# (.NET 10+)** – Phát triển nhanh, hiện đại và dễ bảo trì.

* **Công cụ hỗ trợ:**  
  - Compiler: MSVC, GCC, Clang (C++17). 
  - .NET SDK cho C#.
  - Benchmarking tools và unit testing.

## 🛡️ Bảo mật & Bản quyền

* Mọi đóng góp về lỗi bảo mật, vui lòng xem tại **[SECURITY.md]** ở mỗi ngôn ngữ/thư viện.
* Toàn bộ mã nguồn được phát hành dưới giấy phép **MIT License** – bạn hoàn toàn tự do sử dụng, sửa đổi và phân phối.
* Created with ❤️ by [Nguyen Ky An](https://github.com/ngkyann). 
* "Code faster, stay safer."
