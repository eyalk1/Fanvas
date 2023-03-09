#ifndef TUPLE_ENUM
#define TUPLE_ENUM
#include <tuple>

#define TUPLE_ENUM1(name, type1, index1)                                       \
  using name = std::tuple<types>;                                              \
  enum { index1 };

#define TUPLE_ENUM2(name, type1, index1, type2, index2)                        \
  using name = std::tuple<type1, type2>;                                       \
  enum { index1, index2 };

#define TUPLE_ENUM3(name, type1, index1, type2, index2, type3, index3)         \
  using name = std::tuple<type1, type2, type3>;                                \
  enum { index1, index2, index3 };

#define TUPLE_ENUM4(name, type1, index1, type2, index2, type3, index3, type4,  \
                    index4)                                                    \
  using name = std::tuple<type1, type2, type3, type4>;                         \
  enum {                                                                       \
    index1,                                                                    \
    index2,                                                                    \
    index3,                                                                    \
    index4,                                                                    \
  };

#endif // TUPLE_ENUM
