#ifndef OVERLOADED__HPP
#define OVERLOADED__HPP
template <typename... Ts> struct Overload : Ts... { using Ts::operator()...; };
template <typename... Ts> Overload(Ts...) -> Overload<Ts...>;
#endif // OVERLOADED__HPP
