//Tên: store
//Phiên bản: 1.0
//ID: #.4ß&Q3O$i:M<J<tn



#pragma once
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <deque>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <sstream>

namespace adv
{
using std::cout;
using std::deque;
using std::endl;
using std::initializer_list;
using std::ostream;
using std::size_t;
using std::string;
using std::vector;
using std::cin;
// =======================
// Lop quan li loi 
// =======================
class Errors
{
  private:
	bool m_exit_code_mode{false}; // false: nem loi, true: tra ve ma loi
	int m_last_error_code{0};	  // Kiem tra ma loi cuoi

  public:
	// =======================
	// Cau hinh che do
	// =======================

	/// @brief Dat che do ma thoat
	/// @param mode true cho ma loi, false cho ngoai le
	void has_exit_code(bool mode) noexcept
	{
		m_exit_code_mode = mode;
	}

	/// @brief Lay che do hien tai
	/// @return true neu che do ma loi
	bool get_exit_code_mode() const noexcept
	{
		return m_exit_code_mode;
	}

	/// @brief Lay ma loi cuoi cung
	/// @return Tra ve ma loi cuoi cung
	int get_last_error_code() const noexcept
	{
		return m_last_error_code;
	}

	// =======================
	// Phuong thuc loi - Phien ban ngoai le (khong tra ve)
	// =======================

	/// @brief Nem ngoai le out_of_range
	[[noreturn]] void throw_out_of_range(const string& msg = "Error: Out of range") const
	{
		throw std::out_of_range(msg);
	}

	/// @brief Nem ngoai le invalid_argument
	[[noreturn]] void throw_invalid_argument(const string& msg = "Error: Invalid argument") const
	{
		throw std::invalid_argument(msg);
	}

	/// @brief Nem ngoai le runtime_error
	[[noreturn]] void throw_runtime_error(const string& msg = "Error: Runtime error") const
	{
		throw std::runtime_error(msg);
	}

	// =======================
	// Phuong thuc loi - Phien ban ma loi (tra ve int)
	// =======================

	/// @brief Tra ve ma loi out_of_range
	/// @return Ma loi -1
	int return_out_of_range() noexcept
	{
		m_last_error_code = -1;
		return -1;
	}

	/// @brief Tra ve ma loi invalid_argument
	/// @return Ma loi -2
	int return_invalid_argument() noexcept
	{
		m_last_error_code = -2;
		return -2;
	}

	/// @brief Tra ve ma loi runtime_error
	/// @return Ma loi -3
	int return_runtime_error() noexcept
	{
		m_last_error_code = -3;
		return -3;
	}

	// =======================
	// Phuong thuc loi duy nhat (che do tu nhan dien)
	// =======================

	/// @brief Xu ly out_of_range
	/// @return Ma loi neu trong che do ma loi, nguoc lai ngoai le
	[[noreturn]] int out_of_range(const string& msg = "")
	{
		if (m_exit_code_mode)
		{
			std::exit(return_out_of_range());
		}
		throw_out_of_range(msg);
	}

	/// @brief Xu ly invalid_argument
	/// @return Ma loi neu trong che do ma loi, nguoc lai ngoai le
	[[noreturn]] int invalid_argument(const string& msg = "")
	{
		if (m_exit_code_mode)
		{
			std::exit(return_invalid_argument());
		}
		throw_invalid_argument(msg);
	}

	/// @brief Xu ly runtime_error
	/// @return Ma loi neu trong che do ma loi, nguoc lai ngoai le
	[[noreturn]] int runtime_error(const string& msg = "")
	{
		if (m_exit_code_mode)
		{
			std::exit(return_runtime_error());
		}
		throw_runtime_error(msg);
	}

	// =======================
	// Phuong thuc loi khong thoat (cho cac ham tra ve ma loi)
	// =======================

	/// @brief Lay ma loi out_of_range
	/// @return Ma loi -1
	int get_out_of_range_code() noexcept
	{
		m_last_error_code = -1;
		return -1;
	}

	/// @brief Lay ma loi invalid_argument
	/// @return Ma loi -2
	int get_invalid_argument_code() noexcept
	{
		m_last_error_code = -2;
		return -2;
	}

	/// @brief Lay ma loi runtime_error
	/// @return Ma loi -3
	int get_runtime_error_code() noexcept
	{
		m_last_error_code = -3;
		return -3;
	}
};

// =======================
// Lop khuon mau store
// =======================
template <typename T>
class store
{
  private:
	deque<T> m_data;	   //Luu tru noi bo
	inline static Errors s_error; //Quan li loi

  public:
	// =======================
	// Khoi tao & Pha huy
	// =======================

	/// @brief Khoi tao mac dinh
	store() = default;

	/// @brief Khoi tao voi kich thuoc
	/// @param Kich thuoc ban dau cua store
	explicit store(size_t size) : m_data(size) {}

	/// @brief Khoi tao voi danh sach khoi tao
	/// @param Danh sach khoi tao khoi tao cac gia tri phan tu
	store(initializer_list<T> list) : m_data(list) {}

	/// @brief Khoi tao voi con tro lap pham vi
	/// @tparam Kieu con tro lap
	/// @param Con tro lap bat dau begin
	/// @param Con tro lap ket thuc end
	template <typename Iterator>
	store(Iterator begin, Iterator end) : m_data(begin, end) {}

	/// @brief Khoi tao voi pham vi
	/// @tparam Kieu pham vi
	/// @param Pham vi dau vao
	template <typename Range>
	explicit store(const Range &range) : m_data(range.begin(), range.end()) {}

	/// @brief Sao chep khoi tao
	store(const store&) = default;

	/// @brief Di chuyen khoi tao
	store(store&&) noexcept = default;

	/// @brief Sao chep gan
	store& operator=(const store&) = default;

	/// @brief Di chuyen gan
	store& operator=(store&&) noexcept = default;

	// =======================
	// Truy cap phan tu
	// =======================

	/// @brief Truy cap phan tu voi kiem tra
	/// @param Vi tri kiem tra pos
	/// @return Tham chieu den phan tu tai vi tri
	/// @throws std::out_of_range neu vi tri khong hop le
	T &at(size_t pos)
	{
		if (pos >= m_data.size())
		{
			s_error.throw_out_of_range("Index " + std::to_string(pos) + " out of range");
		}
		return m_data[pos];
	}

	/// @brief Truy cap hang so phan tu voi kiem tra
	/// @param Vi tri kiem tra pos
	/// @return Tham chieu hang so den phan tu tai vi tri
	/// @throws std::out_of_range neu vi tri khong hop le
	const T &at(size_t pos) const
	{
		if (pos >= m_data.size())
		{
			s_error.throw_out_of_range("Index " + std::to_string(pos) + " out of range");
		}
		return m_data[pos];
	}

	/// @brief Truy cap phan tu voi khong kiem tra
	/// @param Vi tri kiem tra pos
	/// @return Tham chieu den phan tu tai vi tri
	T &operator[](size_t pos) noexcept
	{
		return m_data[pos];
	}

	/// @brief Truy cap hang so phan tu voi khong kiem tra
	/// @param Vi tri kiem tra pos
	/// @return Tham chieu hang so den phan tu tai vi tri
	const T &operator[](size_t pos) const noexcept
	{
		return m_data[pos];
	}

	/// @brief Lay phan tu dau tien
	/// @return Tham chieu hang so den phan tu dau tien
	/// @throws std::out_of_range neu store rong
	const T &front() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range("store is empty");
		}
		return m_data.front();
	}

	/// @brief Lay phan tu giua
	/// @return Tham chieu hang so den phan tu giua
	/// @throws std::out_of_range neu store rong
	const T &mid() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range("store is empty");
		}
		return m_data[m_data.size() / 2];
	}

	/// @brief Lay phan tu cuoi
	/// @return Tham chieu hang so den phan tu cuoi
	/// @throws std::out_of_range neu store rong
	const T &back() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range("store is empty");
		}
		return m_data.back();
	}

	/// @brief Lay phan tu lon nhat
	/// @return Tham chieu hang so den phan tu lon nhat
	/// @throws std::out_of_range neu store rong
	const T &max() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range("store is empty");
		}
		return *std::max_element(m_data.begin(), m_data.end());
	}

	/// @brief Lay phan tu nho nhat
	/// @return Tham chieu hang so den phan tu nho nhat
	/// @throws std::out_of_range neu store rong
	const T &min() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range("store is empty");
		}
		return *std::min_element(m_data.begin(), m_data.end());
	}

	// =======================
	// Dung luong
	// =======================

	/// @brief Lay kich thuoc hien tai
	/// @return So phan tu trong store
	size_t size() const noexcept
	{
		return m_data.size();
	}

	/// @brief Kiem tra neu store rong
	/// @return true neu store rong, nguoc lai false
	bool empty() const noexcept
	{
		return m_data.empty();
	}
	
	// =======================
	// Toan tu chuyen doi
	// =======================

	/// @brief Chuyen doi qua vector
	/// @return vector chua cac phan tu cua store
	operator vector<T>() const
	{
		return vector<T>(m_data.begin(), m_data.end());
	}

	/// @brief Chuyen doi qua deque
	/// @return deque chua cac phan tu cua store
	operator deque<T>() const
	{
		return m_data;
	}

	// =======================
	// Con tro lap
	// =======================
	auto begin() noexcept { return m_data.begin(); }
	auto end() noexcept { return m_data.end(); }
	auto begin() const noexcept { return m_data.begin(); }
	auto end() const noexcept { return m_data.end(); }
	auto cbegin() const noexcept { return m_data.cbegin(); }
	auto cend() const noexcept { return m_data.cend(); }
	auto rbegin() noexcept { return m_data.rbegin(); }
	auto rend() noexcept { return m_data.rend(); }
	auto rbegin() const noexcept { return m_data.rbegin(); }
	auto rend() const noexcept { return m_data.rend(); }

	// =======================
	// Toan tu co ban
	// =======================

	/// @brief Thay doi kich thuoc store
	/// @param Kich thuoc moi cua store new_size
	void resize(size_t new_size)
	{
		m_data.resize(new_size);
	}

	/// @brief Xoa toan bo phan tu
	void clear() noexcept
	{
		m_data.clear();
	}

	/// @brief Xoa phan tu dau
	/// @throws std::out_of_range neu mang rong
	void pop_front()
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range("Cannot pop_front from empty store");
		}
		m_data.pop_front();
	}

	/// @brief Xoa phan tu cuoi
	/// @throws std::out_of_range neu mang rong
	void pop_back()
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range("Cannot pop_back from empty store");
		}
		m_data.pop_back();
	}

	/// @brief Xoa phan tu tai vi tri
	/// @param Vi tri xoa pos
	/// @throws std::out_of_range neu vi tri khong hop le
	void remove_at(size_t pos)
	{
		if (pos >= m_data.size())
		{
			s_error.throw_out_of_range("Index " + std::to_string(pos) + " out of range");
		}
		m_data.erase(m_data.begin() + pos);
	}

	/// @brief Chen phan tu tai vi tri
	/// @param Gia tri chen value
	/// @param Vi tri chen pos
	/// @throws std::out_of_range neu vi tri khong hop le
	void insert(const T&value, size_t pos)
	{
		if (pos > m_data.size())
		{
			s_error.throw_out_of_range("Index " + std::to_string(pos) + " out of range");
		}
		m_data.insert(m_data.begin() + pos, value);
	}

	/// @brief Thay the phan tu tai vi tri
	/// @param Gia tri moi value
	/// @param Vi tri thay the pos
	/// @throws std::out_of_range neu vi tri khong hop le
	void replace_at(const T&value, size_t pos)
	{
		if (pos >= m_data.size())
		{
			s_error.throw_out_of_range("Index " + std::to_string(pos) + " out of range");
		}
		m_data[pos] = value;
	}

	/// @brief Thay the tat ca gia tri cua mot gia tri
	/// @param Gia tri can thay the old_value
	/// @param Gia tri moi new_value
	void replace_all(const T &old_value, const T &new_value)
	{
		std::replace(m_data.begin(), m_data.end(), old_value, new_value);
	}

	/// @brief Lap day store voi gia tri
	/// @param Gia tri lap day value
	void fill(const T &value)
	{
		std::fill(m_data.begin(), m_data.end(), value);
	}

	/// @brief Dao nguoc cac phan tu trong mang
	void reverse()
	{
		std::reverse(m_data.begin(), m_data.end());
	}

	/// @brief Hoan doi phan tu voi store khac
	/// @param Store khac muon thay doi other
	void swap(store<T> &other) noexcept
	{
		m_data.swap(other.m_data);
	}

    // =======================
	// Ham in nang cao
	// =======================
	
	/// @brief In cac phan tu cua store
	/// @param Co in xuong dong o cuoi new_line (mac dinh: true)
	/// @param Dau phan cach giua cac phan tu sep (mac dinh: " ")
	/// @param Ky tu ket thuc end (mac dinh: "\n")
	void print(bool new_line = true, string sep = " ", string end = "\n") const
	{
	    for (size_t i = 0; i < m_data.size(); ++i)
	    {
	        cout << m_data[i];
	        if (i < m_data.size() - 1)
	        {
	            cout << sep;
	        }
	    }
	    if (new_line)
	    {
	        cout << end;
	    }
	}
	
	// =======================
	// operator() - cat lat
	// =======================
	
	/// @brief Cat lat
	/// @param Vi tri bat dau start(bao gom)
	/// @param Vi tri ket thuc end (loai tru)
	/// @param Buoc nhay step (mac dinh: 1)
	/// @return Store moi voi cac gia tri duoc cat
	store<T> operator()(int start, int end, int step = 1) const
	{
	    if (step == 0)
	    {
	        return store<T>();
	    }
	
	    // Xu ly chi so am
	    size_t size = m_data.size();
	    size_t start_idx = (start >= 0) ? static_cast<size_t>(start) : size + start;
	    size_t end_idx = (end >= 0) ? static_cast<size_t>(end) : size + end;
	
	    // Gioi han chi so trong pham vi hop le
	    if (start_idx > size) start_idx = size;
	    if (end_idx > size) end_idx = size;
	
	    store<T> result;
	
	    if (step > 0)
	    {
	        // Cat lat tien
	        for (size_t i = start_idx; i < end_idx; i += step)
	        {
	            if (i < size)
	            {
	                result.push_back(m_data[i]);
	            }
	        }
	    }
	    else
	    {
	        // Cat lat nguoc
	        if (start_idx >= size) start_idx = size - 1;
	        if (end_idx >= size) end_idx = size - 1;
	
	        for (int i = static_cast<int>(start_idx); i > static_cast<int>(end_idx); i += step)
	        {
	            if (i >= 0 && static_cast<size_t>(i) < size)
	            {
	                result.push_back(m_data[i]);
	            }
	        }
	    }
	
	    return result;
	}
	
	// =======================
	// count - Dem so lan xuat hien gia tri
	// =======================
	
	/// @brief Dem so lan xuat hien gia tri
	/// @param Gia tri de dem value
	/// @return So lan xuat hien
	size_t count(const T& value) const noexcept
	{
	    return std::count(m_data.begin(), m_data.end(), value);
	}
	
	// =======================
	// count_if - Dem phan tu thoa man dieu kien
	// =======================
	
	/// @brief Dem phan tu thoa man dieu kien
	/// @tparam Kieu dieu kien Pred
	/// @param Ham dieu kien pred
	/// @return So phan tu thoa man dieu kien
	template <typename Pred>
	size_t count_if(Pred pred) const
	{
	    return std::count_if(m_data.begin(), m_data.end(), pred);
	}

	// =======================
	// Them phan tu
	// =======================

	/// @brief Them container vao dau
	/// @tparam Kieu vat chua Container
	/// @param Vat chua de them container
	template <typename Container>
	void push_front(const Container &container)
	{
		m_data.insert(m_data.begin(), container.begin(), container.end());
	}

	/// @brief Them di chuyen container vao dau
	/// @tparam Kieu vat chua Container
	/// @param Vat chua de di chuyen container
	template <typename Container>
	void push_front(Container &&container)
	{
		m_data.insert(m_data.begin(),
					  std::make_move_iterator(container.begin()),
					  std::make_move_iterator(container.end()));
	}

	/// @brief Them danh sach khoi tao vao dau
	/// @param Danh sach khoi tao de them list
	void push_front(initializer_list<T> list)
	{
		m_data.insert(m_data.begin(), list.begin(), list.end());
	}

	/// @brief Them gia tri vao dau
	/// @param Gia tri de them value
	void push_front(const T &value)
	{
		m_data.push_front(value);
	}

	/// @brief Them di chuyen gia tri vao dau
	/// @param Gia tri de di chuyen value
	void push_front(T &&value)
	{
		m_data.push_front(std::move(value));
	}

	/// @brief Them container vao cuoi
	/// @tparam Kieu vat chua Container
	/// @param Vat chua de them container
	template <typename Container>
	void push_back(const Container &container)
	{
		m_data.insert(m_data.end(), container.begin(), container.end());
	}

	/// @brief Them danh sach khoi tao vao cuoi
	/// @param Danh sach khoi tao de them list
	void push_back(initializer_list<T> list)
	{
		m_data.insert(m_data.end(), list.begin(), list.end());
	}

	/// @brief Them gia tri vao cuoi
	/// @param Gia tri de them value
	void push_back(const T &value)
	{
		m_data.push_back(value);
	}

	/// @brief Them di chuyen gia tri vao dau
	/// @param Gia tri de di chuyen value
	void push_back(T &&value)
	{
		m_data.push_back(std::move(value));
	}

	/// @brief Dat phan tu vao cuoi
	/// @tparam Kieu doi so Args
	/// @param Cac loai doi so args
	template <typename... Args>
	T& emplace_back(Args &&... args)
	{
		return m_data.emplace_back(std::forward<Args>(args)...);
	}

	/// @brief Dat phan tu vao dau
	/// @tparam Kieu doi so Args
	/// @param Cac loai doi so args
	template <typename... Args>
	T& emplace_front(Args &&... args)
	{
		return m_data.emplace_front(std::forward<Args>(args)...);
	}

	// =======================
	// Tim kiem & kiem tra
	// =======================

	/// @brief Kiem tra neu store chua gia tri
	/// @param Gia tri de tim kiem value
	/// @return true neu tim thay gia tri, nguoc lai false
	bool contains(const T &value) const
	{
		return std::find(m_data.begin(), m_data.end(), value) != m_data.end();
	}

	/// @brief Kiem tra neu bat ky phan tu thoa man dieu kien
	/// @tparam Kieu dieu kien Pred
	/// @param Ham dieu kien pred
	/// @return true neu bat ky phan tu thoa man dieu kien
	template <typename Pred>
	bool any_of(Pred pred) const
	{
		return std::any_of(m_data.begin(), m_data.end(), pred);
	}

	/// @brief Kiem tra neu bat ky phan tu bang gia tri
	/// @param Gia tri de so sanh value
	/// @return true neu bat ky phan tu bang gia tri
	bool any_of(const T &value) const
	{
		return std::any_of(m_data.begin(), m_data.end(),
						   [&](const T &elem) { return elem == value; });
	}

	/// @brief Kiem tra neu tat ca phan tu thoa man dieu kien
	/// @tparam Kieu dieu kien Pred
	/// @param Ham dieu kien pred
	/// @return true neu tat ca phan tu thoa man dieu kien
	template <typename Pred>
	bool all_of(Pred pred) const
	{
		return std::all_of(m_data.begin(), m_data.end(), pred);
	}

	/// @brief Kiem tra neu tat ca phan tu bang gia tri
	/// @param Gia tri de so sanh value
	/// @return true neu tat ca phan tu bang gia tri
	bool all_of(const T &value) const
	{
		return std::all_of(m_data.begin(), m_data.end(),
						   [&](const T &elem) { return elem == value; });
	}

	/// @brief Kiem tra neu khong phan tu nao thoa man dieu kien
	/// @tparam Kieu dieu kien Pred
	/// @param Ham dieu kien pred
	/// @return true neu khong phan tu nao thoa man dieu kien
	template <typename Pred>
	bool none_of(Pred pred) const
	{
		return std::none_of(m_data.begin(), m_data.end(), pred);
	}

	/// @brief Kiem tra neu khong phan tu nao bang gia tri
	/// @param Gia tri de so sanh value
	/// @return true neu khong phan tu nao bang gia tri
	bool none_of(const T &value) const
	{
		return std::none_of(m_data.begin(), m_data.end(),
							[&](const T &elem) { return elem == value; });
	}

	/// @brief Tim tat ca vi tri cua gia tri
	/// @param Gia tri de tim value
	/// @return vector cac vi tri xuat hien
	vector<size_t> find_all_of(const T &value) const
	{
		vector<size_t> positions;
		for (size_t i = 0; i < m_data.size(); ++i)
		{
			if (m_data[i] == value)
			{
				positions.push_back(i);
			}
		}
		return positions;
	}

	/// @brief Tim tat ca vi tri phan tu thoa man dieu kien
	/// @tparam Kieu dieu kien Pred
	/// @param Ham dieu kien pred
	/// @return vector cac vi tri thoa man dieu kien
	template <typename Pred>
	vector<size_t> find_all_if(Pred pred) const
	{
		vector<size_t> positions;
		for (size_t i = 0; i < m_data.size(); ++i)
		{
			if (pred(m_data[i]))
			{
				positions.push_back(i);
			}
		}
		return positions;
	}
	
	/// @brief Tim iterator phan tu dau tien >= value
	/// @param Gia tri can tim value
	/// @return iterator den phan tu tim thay hoac end()
	typename deque<T>::iterator lower_bound(const T& value) {
	    return std::lower_bound(m_data.begin(), m_data.end(), value);
	}
	
	/// @brief Tim vi tri cua phan tu dau tien >= value
	/// @param Gia tri can tim value
	/// @return size_t index (neu khong thay se tra ve size())
	size_t lower_bound_index(const T& value) const {
	    typename deque<T>::const_iterator it = std::lower_bound(m_data.begin(), m_data.end(), value);
	    return static_cast<size_t>(std::distance(m_data.begin(), it));
	}
	
	/// @brief Tim iterator phan tu dau tien > value
	/// @param Gia tri can tim value
	/// @return iterator den phan tu tim thay hoac end()
	typename deque<T>::iterator upper_bound(const T& value) {
	    return std::upper_bound(m_data.begin(), m_data.end(), value);
	}
	
	/// @brief Tim vi tri cua phan tu dau tien >= value
	/// @param Gia tri can tim value
	/// @return size_t index (neu khong thay se tra ve size())
	size_t upper_bound_index(const T& value) const {
	    typename deque<T>::const_iterator it = std::upper_bound(m_data.begin(), m_data.end(), value);
	    return static_cast<size_t>(std::distance(m_data.begin(), it));
	}
	
	// =======================
	// Bien doi & Loc
	// =======================

	/// @brief Bien doi cac phan tu tai cho
	/// @tparam Kieu ham Func
	/// @param Ham bien doi func
	template <typename Func>
	void transform(Func func)
	{
		std::transform(m_data.begin(), m_data.end(), m_data.begin(), func);
	}

	/// @brief Loc cac phan tu theo dieu kien
	/// @tparam Kieu dieu kien Pred
	/// @param Ham dieu kein pred
	/// @return store moi voi cac phan tu duoc loc
	template <typename Pred>
	store<T> filter(Pred pred) const
	{
		store<T> result;
		for (const auto &elem : m_data)
		{
			if (pred(elem))
			{
				result.push_back(elem);
			}
		}
		return result;
	}

	// =======================
	// Sap xep
	// =======================

	/// @brief Sap xep phan tu
	/// @param Sap xep theo thu tu tang dan ascending (mac dinh: true)
	void sort(bool ascending = true)
	{
	    std::vector<T> temp(m_data.begin(), m_data.end());
		if (ascending)
		{
			std::sort(temp.begin(), temp.end());
		}
		else
		{
			std::sort(temp.begin(), temp.end(), std::greater<T>());
		}
		m_data.assign(std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
	}

	/// @brief Sap xep voi bo so sanh tuy chinh
	/// @tparam Kieu so sanh Compare
	/// @param Ham so sanh comp
	template <typename Compare>
	void sort(Compare comp)
	{
	    std::vector<T> temp(m_data.begin(), m_data.end());
		std::sort(temp.begin(), temp.end(), comp);
		m_data.assign(std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()));
	}

	/// @brief Xoa bo phan tu trung nhau
	/// @param Sap xep truoc khi xoa auto_sort (mac dinh: true)
	void unique(bool auto_sort = true)
	{
		if (auto_sort)
		{
			sort();
		}
		auto it = std::unique(m_data.begin(), m_data.end());
		m_data.erase(it, m_data.end());
	}

	// =======================
	// Chuyen doi kieu
	// =======================

	/// @brief Chuyen doi thanh store so nguyen
	/// @return store moi voi gia tri so nguyen
	store<int> to_int() const
	{
		static_assert(std::is_arithmetic_v<T> || std::is_same_v<T, string>,
					  "Type must be arithmetic or string for conversion to int");

		store<int> result;
		for (const auto &val : m_data)
		{
			if constexpr (std::is_same_v<T, string>)
			{
				try
				{
					result.push_back(std::stoi(val));
				}
				catch (...)
				{
					result.push_back(0);
				}
			}
			else
			{
				result.push_back(static_cast<int>(val));
			}
		}
		return result;
	}

	/// @brief Chuyen doi thanh store so thuc
	/// @return store moi voi gia tri so thuc
	store<double> to_double() const
	{
		static_assert(std::is_arithmetic_v<T> || std::is_same_v<T, string>,
					  "Type must be arithmetic or string for conversion to double");

		store<double> result;
		for (const auto &val : m_data)
		{
			if constexpr (std::is_same_v<T, string>)
			{
				try
				{
					result.push_back(std::stod(val));
				}
				catch (...)
				{
					result.push_back(0.0);
				}
			}
			else
			{
				result.push_back(static_cast<double>(val));
			}
		}
		return result;
	}

	/// @brief Chuyen doi thanh store ki tu
	/// @return store moi voi gia tri ki tu
	store<char> to_char() const
	{
		static_assert(std::is_arithmetic_v<T> || std::is_same_v<T, string>,
					  "Type must be arithmetic or string for conversion to char");

		store<char> result;
		for (const auto &val : m_data)
		{
			if constexpr (std::is_same_v<T, string>)
			{
				if (!val.empty())
				{
					result.push_back(val[0]);
				}
				else
				{
					result.push_back('\0');
				}
			}
			else
			{
				result.push_back(static_cast<char>(val));
			}
		}
		return result;
	}

	/// @brief Chuyen doi thanh store chuoi
	/// @return store moi voi gia tri chuoi
	store<string> to_string() const
	{
		store<string> result;
		for (const auto &val : m_data)
		{
			if constexpr (std::is_arithmetic_v<T>)
			{
				result.push_back(std::to_string(val));
			}
			else if constexpr (std::is_same_v<T, char>)
			{
				result.push_back(string(1, val));
			}
			else if constexpr (std::is_same_v<T, string>)
			{
				result.push_back(val);
			}
			else
			{
				std::ostringstream oss;
				oss << val;
				result.push_back(oss.str());
			}
		}
		return result;
	}

	// =======================
	// Toan tu tap hop
	// =======================

	/// @brief Hop (A | B)
	store<T> operator|(const store<T>& other) const
	{
		std::vector<T> temp_this(m_data.begin(), m_data.end());
		std::vector<T> temp_other(other.m_data.begin(), other.m_data.end());

		std::sort(temp_this.begin(), temp_this.end());
		std::sort(temp_other.begin(), temp_other.end());

		std::vector<T> result;
		std::set_union(temp_this.begin(), temp_this.end(),
					   temp_other.begin(), temp_other.end(),
					   std::back_inserter(result));

		return store<T>(result.begin(), result.end());
	}

	/// @brief Giao (A & B)
	store<T> operator&(const store<T>& other) const
	{
		std::vector<T> temp_this(m_data.begin(), m_data.end());
		std::vector<T> temp_other(other.m_data.begin(), other.m_data.end());

		std::sort(temp_this.begin(), temp_this.end());
		std::sort(temp_other.begin(), temp_other.end());

		std::vector<T> result;
		std::set_intersection(temp_this.begin(), temp_this.end(),
							  temp_other.begin(), temp_other.end(),
							  std::back_inserter(result));

		return store<T>(result.begin(), result.end());
	}

	/// @brief Hieu (A - B)
	store<T> operator-(const store<T>& other) const
	{
		std::vector<T> temp_this(m_data.begin(), m_data.end());
		std::vector<T> temp_other(other.m_data.begin(), other.m_data.end());

		std::sort(temp_this.begin(), temp_this.end());
		std::sort(temp_other.begin(), temp_other.end());

		std::vector<T> result;
		std::set_difference(temp_this.begin(), temp_this.end(),
							temp_other.begin(), temp_other.end(),
							std::back_inserter(result));

		return store<T>(result.begin(), result.end());
	}

	/// @brief Phan bu (A % B)
	store<T> operator%(const store<T>& other) const
	{
		std::vector<T> temp_this(m_data.begin(), m_data.end());
		std::vector<T> temp_other(other.m_data.begin(), other.m_data.end());

		std::sort(temp_this.begin(), temp_this.end());
		std::sort(temp_other.begin(), temp_other.end());

		std::vector<T> result;
		std::set_symmetric_difference(temp_this.begin(), temp_this.end(),
									  temp_other.begin(), temp_other.end(),
									  std::back_inserter(result));

		return store<T>(result.begin(), result.end());
	}

	// =======================
	// Toan tu gan phuc hop
	// =======================

	/// @brief Hop va gan
	store<T>& operator|=(const store<T>& other)
	{
		*this = *this | other;
		return *this;
	}

	/// @brief Giao va gan
	store<T>& operator&=(const store<T>& other)
	{
		*this = *this & other;
		return *this;
	}

	/// @brief Hieu va gan
	store<T>& operator-=(const store<T>& other)
	{
		*this = *this - other;
		return *this;
	}

	/// @brief Phan bu va gan
	store<T>& operator%=(const store<T>& other)
	{
		*this = *this % other;
		return *this;
	}

	// =======================
	// Ten phuong thuc
	// =======================

	/// @brief Hop
	store<T> _union_(const store<T>& other) const { return *this | other; }

	/// @brief Giao
	store<T> _inter_(const store<T>& other) const { return *this & other; }

	/// @brief Hieu
	store<T> _diff_(const store<T>& other) const { return *this - other; }

	/// @brief Phan bu
	store<T> _comp_(const store<T>& other) const { return *this % other; }
};

	// =======================
	// Toan tu khong phai thanh vien
	// =======================
	
	/// @brief Toan tu dau ra
	template<typename T>
	std::ostream& operator<<(std::ostream& os, const store<T>& store)
	{
		for (size_t i = 0; i < store.size(); ++i)
		{
			os << store[i];
			if (i < store.size() - 1) os << " ";
		}
		return os;
	}
	/// @brief Toan tu so sanh bang
	template<typename T>
	bool operator==(const store<T>& lhs, const store<T>& rhs)
	{
		if (lhs.size() != rhs.size()) return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	
	/// @brief Toan tu so sanh khac
	template<typename T>
	bool operator!=(const store<T>& lhs, const store<T>& rhs)
	{
		return !(lhs == rhs);
	}

} // namespace adv
