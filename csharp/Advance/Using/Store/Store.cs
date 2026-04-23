// Tên: store
// Phiên bản: 1.1 (C# Port)

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace adv
{
    /// <summary>
    /// Error management class with support for exception and error code modes
    /// </summary>
    internal static class ErrorManager
    {
        // Thread-local storage for error tracking
        private static readonly ThreadLocal<bool> ExitCodeMode = new(() => false);
        private static readonly ThreadLocal<short> LastErrorCode = new(() => 0);

        /// <summary>
        /// Set error handling mode
        /// </summary>
        public static void SetExitCodeMode(bool mode) => ExitCodeMode.Value = mode;

        /// <summary>
        /// Get current error mode
        /// </summary>
        public static bool GetExitCodeMode() => ExitCodeMode.Value;

        /// <summary>
        /// Get last error code
        /// </summary>
        public static short GetLastErrorCode() => LastErrorCode.Value;

        // =======================
        // Exception-based methods
        // =======================

        /// <summary>
        /// Throw IndexOutOfRangeException
        /// </summary>
        public static void ThrowOutOfRange(string msg = "Error: Out of range")
            => throw new IndexOutOfRangeException(msg);

        /// <summary>
        /// Throw ArgumentException
        /// </summary>
        public static void ThrowInvalidArgument(string msg = "Error: Invalid argument")
            => throw new ArgumentException(msg);

        /// <summary>
        /// Throw InvalidOperationException
        /// </summary>
        public static void ThrowRuntimeError(string msg = "Error: Runtime error")
            => throw new InvalidOperationException(msg);

        // =======================
        // Error code methods
        // =======================

        /// <summary>
        /// Get error code for out of range (-1)
        /// </summary>
        public static short GetOutOfRangeCode()
        {
            LastErrorCode.Value = -1;
            return -1;
        }

        /// <summary>
        /// Get error code for invalid argument (-2)
        /// </summary>
        public static short GetInvalidArgumentCode()
        {
            LastErrorCode.Value = -2;
            return -2;
        }

        /// <summary>
        /// Get error code for runtime error (-3)
        /// </summary>
        public static short GetRuntimeErrorCode()
        {
            LastErrorCode.Value = -3;
            return -3;
        }

        // =======================
        // Auto-detect methods
        // =======================

        /// <summary>
        /// Handle out of range error based on mode
        /// </summary>
        public static short HandleOutOfRange(string msg = "")
        {
            if (ExitCodeMode.Value)
                return GetOutOfRangeCode();
            ThrowOutOfRange(msg);
            return -1; // unreachable
        }

        /// <summary>
        /// Handle invalid argument error based on mode
        /// </summary>
        public static short HandleInvalidArgument(string msg = "")
        {
            if (ExitCodeMode.Value)
                return GetInvalidArgumentCode();
            ThrowInvalidArgument(msg);
            return -2; // unreachable
        }

        /// <summary>
        /// Handle runtime error based on mode
        /// </summary>
        public static short HandleRuntimeError(string msg = "")
        {
            if (ExitCodeMode.Value)
                return GetRuntimeErrorCode();
            ThrowRuntimeError(msg);
            return -3; // unreachable
        }
    }

    /// <summary>
    /// Generic container wrapper class providing enhanced functionality
    /// Similar to C++ std::vector with additional utility methods
    /// </summary>
    public class Store<T> : IEnumerable<T>, IEquatable<Store<T>>, ICollection<T>
    {
        private List<T> _data = new();
        private List<T>? _clone;

        // =======================
        // Constructors
        // =======================

        /// <summary>
        /// Default constructor
        /// </summary>
        public Store() { }

        /// <summary>
        /// Constructor with initial capacity
        /// </summary>
        public Store(int capacity) => _data = new(capacity);

        /// <summary>
        /// Constructor with size and initial value
        /// </summary>
        public Store(int size, T value)
        {
            _data = new(size);
            for (int i = 0; i < size; i++)
                _data.Add(value);
        }

        /// <summary>
        /// Constructor from enumerable
        /// </summary>
        public Store(IEnumerable<T> enumerable) => _data = new(enumerable);

        /// <summary>
        /// Copy constructor
        /// </summary>
        public Store(Store<T> other)
        {
            _data = new(other._data);
            if (other._clone != null)
                _clone = new(other._clone);
        }

        /// <summary>
        /// Assign values from enumerable
        /// </summary>
        public void Assign(IEnumerable<T> enumerable)
        {
            _data.Clear();
            _data.AddRange(enumerable);
        }

        /// <summary>
        /// Assign size copies of value
        /// </summary>
        public void Assign(int size, T value)
        {
            _data.Clear();
            for (int i = 0; i < size; i++)
                _data.Add(value);
        }

        // =======================
        // Element Access
        // =======================

        /// <summary>
        /// Get element at position with bounds checking
        /// </summary>
        public T At(int pos)
        {
            int index = NormalizeIndex(pos);
            if (index < 0 || index >= _data.Count)
                ErrorManager.ThrowOutOfRange($"Index {pos} out of range");
            return _data[index];
        }

        /// <summary>
        /// Get element at position without bounds checking
        /// </summary>
        public T Get(int pos) => _data[NormalizeIndex(pos)];

        /// <summary>
        /// Set element at position
        /// </summary>
        public void Set(int pos, T value) => _data[NormalizeIndex(pos)] = value;

        /// <summary>
        /// Get first element
        /// </summary>
        public T First
        {
            get
            {
                if (_data.Count == 0)
                    ErrorManager.ThrowOutOfRange("Store is empty");
                return _data[0];
            }
        }

        /// <summary>
        /// Get last element
        /// </summary>
        public T Last
        {
            get
            {
                if (_data.Count == 0)
                    ErrorManager.ThrowOutOfRange("Store is empty");
                return _data[_data.Count - 1];
            }
        }

        /// <summary>
        /// Get maximum element
        /// </summary>
        public T Max()
        {
            if (_data.Count == 0)
                ErrorManager.ThrowOutOfRange("Store is empty");
            return _data.Max()!;
        }

        /// <summary>
        /// Get minimum element
        /// </summary>
        public T Min()
        {
            if (_data.Count == 0)
                ErrorManager.ThrowOutOfRange("Store is empty");
            return _data.Min()!;
        }

        /// <summary>
        /// Get (max, min) tuple
        /// </summary>
        public (T Max, T Min) MaxMin()
        {
            if (_data.Count == 0)
                ErrorManager.ThrowOutOfRange("Store is empty");
            var max = _data.Max();
            var min = _data.Min();
            return (max!, min!);
        }

        /// <summary>
        /// Indexer for element access
        /// </summary>
        public T this[int index]
        {
            get => _data[NormalizeIndex(index)];
            set => _data[NormalizeIndex(index)] = value;
        }

        /// <summary>
        /// Normalize negative indices to positive
        /// </summary>
        private int NormalizeIndex(int index)
            => index < 0 ? _data.Count + index : index;

        // =======================
        // Size & Capacity
        // =======================

        /// <summary>
        /// Get current size
        /// </summary>
        public int Count => _data.Count;

        /// <summary>
        /// Check if empty
        /// </summary>
        public bool IsEmpty => _data.Count == 0;

        /// <summary>
        /// Allocate capacity
        /// </summary>
        public void Reserve(int capacity)
        {
            if (capacity > _data.Capacity)
                _data.Capacity = capacity;
        }

        /// <summary>
        /// Resize with default value
        /// </summary>
        public void Resize(int newSize)
        {
            while (_data.Count < newSize)
                _data.Add(default!);
            while (_data.Count > newSize)
                _data.RemoveAt(_data.Count - 1);
        }

        /// <summary>
        /// Resize with specific value
        /// </summary>
        public void Resize(int newSize, T value)
        {
            while (_data.Count < newSize)
                _data.Add(value);
            while (_data.Count > newSize)
                _data.RemoveAt(_data.Count - 1);
        }

        /// <summary>
        /// Clear all elements
        /// </summary>
        public void Clear() => _data.Clear();

        // =======================
        // Type Conversion
        // =======================

        /// <summary>
        /// Convert to List
        /// </summary>
        public List<T> ToList() => new(_data);

        /// <summary>
        /// Convert to array
        /// </summary>
        public T[] ToArray() => _data.ToArray();

        // =======================
        // Basic Operations
        // =======================

        /// <summary>
        /// Remove first element
        /// </summary>
        public void PopFront()
        {
            if (_data.Count == 0)
                ErrorManager.ThrowOutOfRange("Cannot pop_front from empty store");
            _data.RemoveAt(0);
        }

        /// <summary>
        /// Remove last element
        /// </summary>
        public void PopBack()
        {
            if (_data.Count == 0)
                ErrorManager.ThrowOutOfRange("Cannot pop_back from empty store");
            _data.RemoveAt(_data.Count - 1);
        }

        /// <summary>
        /// Remove element at position
        /// </summary>
        public void RemoveAt(int pos)
        {
            if (pos < 0 || pos >= _data.Count)
                ErrorManager.ThrowOutOfRange($"Index {pos} out of range");
            _data.RemoveAt(pos);
        }

        /// <summary>
        /// Insert element at position
        /// </summary>
        public void Insert(int pos, T value)
        {
            if (pos < 0 || pos > _data.Count)
                ErrorManager.ThrowOutOfRange($"Index {pos} out of range");
            _data.Insert(pos, value);
        }

        /// <summary>
        /// Replace element at position
        /// </summary>
        public void ReplaceAt(int pos, T value)
        {
            if (pos < 0 || pos >= _data.Count)
                ErrorManager.ThrowOutOfRange($"Index {pos} out of range");
            _data[pos] = value;
        }

        /// <summary>
        /// Replace all occurrences of value
        /// </summary>
        public void ReplaceAll(T oldValue, T newValue)
        {
            for (int i = 0; i < _data.Count; i++)
            {
                if (EqualityComparer<T>.Default.Equals(_data[i], oldValue))
                    _data[i] = newValue;
            }
        }

        /// <summary>
        /// Fill with value
        /// </summary>
        public void Fill(T value)
        {
            for (int i = 0; i < _data.Count; i++)
                _data[i] = value;
        }

        /// <summary>
        /// Reverse elements
        /// </summary>
        public void Reverse() => _data.Reverse();

        /// <summary>
        /// Swap with another store
        /// </summary>
        public void Swap(Store<T> other)
        {
            var temp = _data;
            _data = other._data;
            other._data = temp;
        }

        // =======================
        // String Formatting
        // =======================

        /// <summary>
        /// Join elements into string with separator
        /// </summary>
        public string Join(string separator = "") 
            => string.Join(separator, _data);

        /// <summary>
        /// Join elements with custom converter
        /// </summary>
        public string Join(string separator, Func<T, string> converter)
            => string.Join(separator, _data.Select(converter));

        // =======================
        // Slicing
        // =======================

        /// <summary>
        /// Slice with start, end, and step
        /// </summary>
        public Store<T> Slice(int start, int end, int step = 1)
        {
            if (step == 0)
                return new();
            int size = _data.Count;
            int s = start < 0 ? size + start : start;
            int e = end < 0 ? size + end : end;
            s = Math.Max(0, Math.Min(s, size));
            e = Math.Max(0, Math.Min(e, size));
            var result = new Store<T>();
            if (step > 0)
            {
                for (int i = s; i < e; i += step)
                    result.PushBack(_data[i]);
            }
            else
            {
                for (int i = e - 1; i >= s; i += step)
                    result.PushBack(_data[i]);
            }
            return result;
        }

        /// <summary>
        /// Slice with start and end
        /// </summary>
        public Store<T> Slice(int start, int end) => Slice(start, end, 1);

        // =======================
        // Counting & Searching
        // =======================

        /// <summary>
        /// Count occurrences of value
        /// </summary>
        public int CountOf(T value) 
            => _data.Count(x => EqualityComparer<T>.Default.Equals(x, value));

        /// <summary>
        /// Count elements matching predicate
        /// </summary>
        public int CountIf(Func<T, bool> predicate) 
            => _data.Count(predicate);

        /// <summary>
        /// Check if contains value
        /// </summary>
        public bool Contains(T value) 
            => _data.Contains(value);

        /// <summary>
        /// Check if any element matches predicate
        /// </summary>
        public bool AnyOf(Func<T, bool> predicate) 
            => _data.Any(predicate);

        /// <summary>
        /// Check if any element equals value
        /// </summary>
        public bool AnyOf(T value) 
            => _data.Contains(value);

        /// <summary>
        /// Check if all elements match predicate
        /// </summary>
        public bool AllOf(Func<T, bool> predicate) 
            => _data.All(predicate);

        /// <summary>
        /// Check if all elements equal value
        /// </summary>
        public bool AllOf(T value) 
            => _data.All(x => EqualityComparer<T>.Default.Equals(x, value));

        /// <summary>
        /// Check if no elements match predicate
        /// </summary>
        public bool NoneOf(Func<T, bool> predicate) 
            => !_data.Any(predicate);

        /// <summary>
        /// Check if no elements equal value
        /// </summary>
        public bool NoneOf(T value) 
            => !_data.Contains(value);

        /// <summary>
        /// Find all positions of value
        /// </summary>
        public List<int> FindAllOf(T value)
        {
            var positions = new List<int>();
            for (int i = 0; i < _data.Count; i++)
            {
                if (EqualityComparer<T>.Default.Equals(_data[i], value))
                    positions.Add(i);
            }
            return positions;
        }

        /// <summary>
        /// Find all positions matching predicate
        /// </summary>
        public List<int> FindAllIf(Func<T, bool> predicate)
        {
            var positions = new List<int>();
            for (int i = 0; i < _data.Count; i++)
            {
                if (predicate(_data[i]))
                    positions.Add(i);
            }
            return positions;
        }

        // =======================
        // Adding Elements
        // =======================

        /// <summary>
        /// Add element to front
        /// </summary>
        public void PushFront(T value) => _data.Insert(0, value);

        /// <summary>
        /// Add enumerable to front
        /// </summary>
        public void PushFront(IEnumerable<T> items) 
            => _data.InsertRange(0, items);

        /// <summary>
        /// Add element to back
        /// </summary>
        public void PushBack(T value) => _data.Add(value);

        /// <summary>
        /// Add element to back (supports collection initializer)
        /// </summary>
        public void Add(T value) => PushBack(value);

        // =======================
        // Transform & Filter
        // =======================

        /// <summary>
        /// Transform elements in-place
        /// </summary>
        public void Transform(Func<T, T> func)
        {
            for (int i = 0; i < _data.Count; i++)
                _data[i] = func(_data[i]);
        }

        /// <summary>
        /// Filter elements based on predicate
        /// </summary>
        public Store<T> Filter(Func<T, bool> predicate)
        {
            var result = new Store<T>();
            foreach (var item in _data.Where(predicate))
                result.PushBack(item);
            return result;
        }

        /// <summary>
        /// Project elements using function
        /// </summary>
        public Store<TResult> Map<TResult>(Func<T, TResult> selector)
        {
            var result = new Store<TResult>();
            foreach (var item in _data)
                result.PushBack(selector(item));
            return result;
        }

        // =======================
        // Sorting
        // =======================

        /// <summary>
        /// Sort elements
        /// </summary>
        public void Sort(bool ascending = true)
        {
            if (_data.Count < 2)
                return;
            if (ascending)
                _data.Sort();
            else
                _data.Sort((a, b) => Comparer<T>.Default.Compare(b, a));
        }

        /// <summary>
        /// Sort with custom comparer
        /// </summary>
        public void Sort(IComparer<T> comparer) => _data.Sort(comparer);

        /// <summary>
        /// Sort with comparison function
        /// </summary>
        public void Sort(Func<T, T, int> comparison) 
            => _data.Sort((a, b) => comparison(a, b));

        /// <summary>
        /// Remove duplicate elements
        /// </summary>
        public void Unique(bool autoSort = true)
        {
            if (_data.Count == 0)
                return;
            if (autoSort)
                Sort();
            var uniqueItems = _data.Distinct().ToList();
            _data.Clear();
            _data.AddRange(uniqueItems);
        }

        // =======================
        // Type Conversion
        // =======================

        /// <summary>
        /// Convert to long long
        /// </summary>
        public Store<long> ToLongLong()
        {
            var result = new Store<long>();
            foreach (var item in _data)
            {
                try
                {
                    if (typeof(T) == typeof(string))
                        result.PushBack(long.Parse((string)(object)item!));
                    else
                        result.PushBack(Convert.ToInt64(item));
                }
                catch
                {
                    ErrorManager.ThrowRuntimeError();
                }
            }
            return result;
        }

        /// <summary>
        /// Convert to double
        /// </summary>
        public Store<double> ToDouble()
        {
            var result = new Store<double>();
            foreach (var item in _data)
            {
                try
                {
                    if (typeof(T) == typeof(string))
                        result.PushBack(double.Parse((string)(object)item!));
                    else
                        result.PushBack(Convert.ToDouble(item));
                }
                catch
                {
                    ErrorManager.ThrowRuntimeError();
                }
            }
            return result;
        }

        /// <summary>
        /// Convert to string
        /// </summary>
        public Store<string> ToStr()
        {
            var result = new Store<string>();
            foreach (var item in _data)
            {
                result.PushBack(item?.ToString() ?? "");
            }
            return result;
        }

        // =======================
        // Clone Management
        // =======================

        /// <summary>
        /// Save clone
        /// </summary>
        public void SetClone() => _clone = new(_data);

        /// <summary>
        /// Get clone as new Store
        /// </summary>
        public Store<T> GetClone()
        {
            if (_clone == null)
                ErrorManager.ThrowRuntimeError("Clone is empty");
            return new Store<T>(_clone!);
        }

        /// <summary>
        /// Delete clone
        /// </summary>
        public void DeleteClone() => _clone = null;

        /// <summary>
        /// Swap with clone
        /// </summary>
        public void SwapClone()
        {
            if (_clone == null)
                ErrorManager.ThrowRuntimeError("No clone to swap");
            var temp = _data;
            _data = _clone!;
            _clone = temp;
        }

        /// <summary>
        /// Restore from clone
        /// </summary>
        public void RestoreClone()
        {
            if (_clone == null)
                ErrorManager.ThrowRuntimeError("No clone available");
            _data = new(_clone!);
        }

        // =======================
        // Comparison Operators
        // =======================

        /// <summary>
        /// Equality comparison
        /// </summary>
        public bool Equals(Store<T>? other)
        {
            if (other == null)
                return false;
            if (Count != other.Count)
                return false;
            return _data.SequenceEqual(other._data);
        }

        public override bool Equals(object? obj) => Equals(obj as Store<T>);

        public override int GetHashCode() 
            => _data.Aggregate(0, (acc, x) => acc ^ (x?.GetHashCode() ?? 0));

        public static bool operator ==(Store<T>? left, Store<T>? right)
        {
            if (ReferenceEquals(left, right))
                return true;
            if (left is null || right is null)
                return false;
            return left.Equals(right);
        }

        public static bool operator !=(Store<T>? left, Store<T>? right) 
            => !(left == right);

        public static bool operator <(Store<T> left, Store<T> right)
        {
            var leftList = left._data;
            var rightList = right._data;
            int minLength = Math.Min(leftList.Count, rightList.Count);
            for (int i = 0; i < minLength; i++)
            {
                var cmp = Comparer<T>.Default.Compare(leftList[i], rightList[i]);
                if (cmp != 0)
                    return cmp < 0;
            }
            return leftList.Count < rightList.Count;
        }

        public static bool operator >(Store<T> left, Store<T> right)
        {
            var leftList = left._data;
            var rightList = right._data;
            int minLength = Math.Min(leftList.Count, rightList.Count);
            for (int i = 0; i < minLength; i++)
            {
                var cmp = Comparer<T>.Default.Compare(leftList[i], rightList[i]);
                if (cmp != 0)
                    return cmp > 0;
            }
            return leftList.Count > rightList.Count;
        }

        public static bool operator <=(Store<T> left, Store<T> right) 
            => left < right || left == right;

        public static bool operator >=(Store<T> left, Store<T> right) 
            => left > right || left == right;

        // =======================
        // Range Generation
        // =======================

        /// <summary>
        /// Generate range of numeric values (static)
        /// </summary>
        public static List<long> Range(long start, long stop, long step = 1)
        {
            var result = new List<long>();
            if (step == 0)
                return result;
            if (step > 0)
            {
                for (long i = start; i < stop; i += step)
                    result.Add(i);
            }
            else
            {
                for (long i = start; i > stop; i += step)
                    result.Add(i);
            }
            return result;
        }

        /// <summary>
        /// Generate range from 0 to stop (static)
        /// </summary>
        public static List<long> Range(long stop) => Range(0, stop, 1);

        // =======================
        // IEnumerable Implementation
        // =======================

        public IEnumerator<T> GetEnumerator() => _data.GetEnumerator();

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() 
            => _data.GetEnumerator();

        // =======================
        // ICollection<T> Implementation
        // =======================

        public bool IsReadOnly => false;

        void ICollection<T>.CopyTo(T[] array, int arrayIndex) => _data.CopyTo(array, 
arrayIndex);

        bool ICollection<T>.Remove(T item) => _data.Remove(item);
    }
}