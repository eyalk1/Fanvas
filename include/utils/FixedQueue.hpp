#include <array>
#include <cstddef>
#include <optional>
#include <type_traits>

template <typename T, std::size_t N> struct FixedQueue {
  using value_type = T;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using ArrayT = std::array<std::optional<value_type>, N>;
  constexpr auto at(size_type s) -> reference { return *c.at(s); }
  constexpr auto at(size_type s) const -> const_reference { return *c.at(s); }
  constexpr auto end() -> iterator { return optaddr(*(c.begin() + end_ptr)); }
  constexpr auto end() const -> const_iterator {
    return optaddr(*(c.begin() + end_ptr));
  }
  constexpr auto cend() const -> const_iterator {
    return optaddr(*(c.begin() + end_ptr));
  }
  constexpr auto rend() -> iterator { return optaddr(*(c.rend() - end_ptr)); }
  constexpr auto rend() const -> const_iterator {
    return optaddr(*(c.rend() - end_ptr));
  }
  constexpr auto crend() const -> const_iterator {
    return optaddr(*(c.rend() - end_ptr));
  }
  constexpr auto begin() -> iterator {
    std::optional<value_type> opt = *(c.begin() + begin_ptr);
    if (!opt)
      return std::nullptr_t();
    return &(*(opt));
  }
  constexpr auto begin() const -> const_iterator {
    return optaddr(*(c.begin() + begin_ptr));
  }
  constexpr auto cbegin() const -> const_iterator {
    return optaddr(*(c.begin() + begin_ptr));
  }
  constexpr auto rbegin() -> iterator {
    return optaddr(*(c.rbegin() + begin_ptr));
  }
  constexpr auto rbegin() const -> const_iterator {
    return optaddr(*(c.rbegin() + begin_ptr));
  }
  constexpr auto crbegin() const -> const_iterator {
    return optaddr(*(c.rbegin() + begin_ptr));
  }
  constexpr auto back(size_type s) -> reference { return c.back(s); }
  constexpr auto back(size_type s) const -> const_reference {
    return c.back(s);
  }
  constexpr auto data(size_type s) noexcept -> value_type * {
    return c.data(s);
  }
  constexpr auto data(size_type s) const noexcept -> value_type const * {
    return c.data(s);
  }
  constexpr auto fill(value_type const &val) { c.fill(val); }
  constexpr auto swap(FixedQueue<T, N> &other) noexcept -> void {
    c.swap(other.c);
  }
  constexpr auto max_size() const noexcept -> size_type { return N; }
  constexpr auto operator[](size_type pos) -> reference { return c[pos]; }
  constexpr auto operator[](size_type pos) const -> const_reference {
    return c[pos];
  }

  friend constexpr auto operator==(FixedQueue<T, N> &lhs, FixedQueue<T, N> &rhs)
      -> bool {
    return lhs.c == rhs.c;
  }

  friend constexpr auto operator<=>(FixedQueue<T, N> &lhs,
                                    FixedQueue<T, N> &rhs) {
    return lhs.c <=> rhs.c;
  }

  std::size_t begin_ptr{};
  std::size_t end_ptr{};
  typename ArrayT::reference front() { return *c[begin_ptr]; }
  typename ArrayT::const_reference front() const { return *c[begin_ptr]; }
  typename ArrayT::reference back() { return *c[((end_ptr - 1) + N) % N]; }
  typename ArrayT::const_reference back() const {
    return *c[((end_ptr - 1) + N) % N];
  }
  [[nodiscard]] constexpr auto empty() const noexcept -> bool {
    return size() == 0;
  }
  constexpr auto size() -> typename ArrayT::size_type {
    if (!c[begin_ptr])
      return 0;

    auto distance = end_ptr - begin_ptr;
    distance = (distance + N) % N;
    return distance;
  }
  auto full() -> bool { return size() == N; }
  auto push_back(T const &val) -> void {
    c[end_ptr].reset();
    c[end_ptr] = val;
    advance();
  }
  auto push_back(T &&val) -> void {
    c[end_ptr].reset();
    c[end_ptr] = val;
    advance();
  }
  template <typename... insertT> decltype(auto) emplace_back(insertT &&...ts) {
    //overwrite
    c[end_ptr].emplace(std::forward<insertT...>(ts...));
    advance();
  }
  auto pop() -> void {
    if (empty())
      return;
    c[begin_ptr].reset();
    advance_single(begin_ptr);
  }

private:
  auto optaddr(std::optional<value_type> &opt) -> iterator { return &(opt); }
  ArrayT c{};
  auto advance() -> void {
    advance_single(end_ptr);
    if (end_ptr == begin_ptr)
      advance_single(begin_ptr);
  }
  auto advance_single(std::integral auto &number) -> void {
    number = (number + 1) % N;
  }
};
