// Using toString() on Custom Types in C++
// https://www.fluentcpp.com/2017/06/06/using-tostring-custom-types-cpp/

#include <string>
#include <iostream>
#include <experimental/type_traits>

// 1 - detecting if std::to_string is valid on T

template<typename T>
using std_to_string_expression = decltype(std::to_string(std::declval<T>()));

template<typename T>
constexpr bool has_std_to_string = std::experimental::is_detected<std_to_string_expression, T>;


// 2 - detecting if to_string is valid on T

template<typename T>
using to_string_expression = decltype(to_string(std::declval<T>()));

template<typename T>
constexpr bool has_to_string = std::experimental::is_detected<to_string_expression, T>;


// 3 - detecting if T can be sent to an ostringstream

template<typename T>
using ostringstream_expression = decltype(std::declval<std::ostringstream&>() << std::declval<T>());

template<typename T>
constexpr bool has_ostringstream = std::experimental::is_detected<ostringstream_expression, T>;

// 1 -  std::to_string is valid on T
template<typename T, typename std::enable_if<has_std_to_string<T>, int>::type = 0>
std::string toString(T const& t)
{
    return std::to_string(t);
}

// 2 -  std::to_string is not valid on T, but to_string is
template<typename T, typename std::enable_if<!has_std_to_string<T> && has_to_string<T>, int>::type = 0>
std::string toString(T const& t)
{
    return to_string(t);
}

// 3 -  neither std::string nor to_string work on T, let's stream it then
template<typename T, typename std::enable_if<!has_std_to_string<T> && !has_to_string<T> && has_ostringstream<T>, int>::type = 0>
std::string toString(T const& t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

namespace NA
{
    class A {};
    std::string to_string(A const&) { return "to_string(A)"; }
}

namespace NB
{
    class B {};
    std::ostream& operator<<(std::ostream& os, B const&) { os << "oss(B)"; return os; }
}

int main()
{
    std::cout << toString(42) << '\n';
    std::cout << toString(NA::A()) << '\n';
    std::cout << toString(NB::B()) << std::endl;

    // The above code outputs:
    //
    // 42
    // to_string(A)
    // oss(B)
}
