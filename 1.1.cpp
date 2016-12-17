// Is Unique: Implement an algorithm to determine if a string has all unique characters. What if you
// cannot use additional data structures?

#include <iostream>
#include <unordered_set>
#include <locale>
#include <codecvt>
#include <string>

auto test = [](auto &&func, auto &&printResult, auto &&...params)
{
    auto &&result = std::forward<decltype(func)>(func) (std::forward<decltype(params)>(params)...);
    std::forward<decltype(printResult)>(printResult) (result, std::forward<decltype(params)>(params)...);
};

bool isUnique(const std::string &chars)
{
    // [a-zA-z]
    uint64_t setChars = 0;

    for (auto &c : chars)
    {
        if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
            throw;
        uint64_t bit = (1ULL << (c - 'A'));
        if (setChars & bit)
            return false;
        setChars |= bit;
    }

    return true;
}

bool isUniqueW(const std::wstring &chars)
{
    // all wchars
    std::unordered_set<wchar_t> setChars;

    for (auto &c : chars)
    {
        if (setChars.find(c) != setChars.end())
            return false;
        setChars.emplace(c);
    }

    return true;
}

auto printResult = [](bool result, auto &&chars)
{
    std::cout << '"' << chars << "\" " << (result ? "passed " : "failed") << std::endl;
};

auto printResultW = [](bool result, auto &&chars)
{
    // wide to utf-8
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    printResult(result, convert.to_bytes(chars));
};

int main()
{
    test(isUnique, printResult, std::string("IsUnique"));
    test(isUnique, printResult, std::string("IsUniqueTest"));
    test(isUniqueW, printResultW, std::wstring(L"IsUnique\u0423\u043d\u0438\u043a\u0430\u043b\u044c")); // IsUniqueУникаль
    test(isUniqueW, printResultW, std::wstring(L"IsUnique\u0423\u043d\u0438\u043a\u0430\u043b\u044c\u043d\u044b\u0439")); // IsUniqueУникальный
    test(isUniqueW, printResultW, std::wstring(L"z\u00df\u6c34\U0001f34c")); // zß水🍌
    test(isUniqueW, printResultW, std::wstring(L"z\u00df\u6c34\U0001f34c\u00df")); // zß水🍌ß
    return 0;
}