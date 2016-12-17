#include <utility>

auto test = [](auto &&func, auto &&printResult, auto &&...params)
{
    auto &&result = std::forward<decltype(func)>(func) (std::forward<decltype(params)>(params)...);
    std::forward<decltype(printResult)>(printResult) (result, std::forward<decltype(params)>(params)...);
};
