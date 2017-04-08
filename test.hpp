#include <utility>

auto test = [](auto &&func, auto &&printResult, auto &&...params)
{
    auto result = std::forward<decltype(func)>(func) (params...);
    std::forward<decltype(printResult)>(printResult) (std::move(result), std::forward<decltype(params)>(params)...);
};
