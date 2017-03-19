#include <vector>
#include <iostream>

long fibonacci(int n, std::vector<long> &fibs);

long fibonacci(int n)
{
    std::vector<long> fibs(n + 1);
    return fibonacci(n, fibs);
}

long fibonacci(int n, std::vector<long> &fibs)
{
    if (n == 0 || n == 1)
        return 1;
    if (fibs[n] == 0)
        fibs[n] = fibonacci(n - 1, fibs) + fibonacci(n - 2, fibs);
    return fibs[n];
}

long fibonacci_loop(int n)
{
    if (n == 0 || n == 1)
        return 1;

    long fibs[2] = {1, 1};
    for ( ; n > 2; --n)
        fibs[n & 1] = fibs[0] + fibs[1];
    return fibs[0] + fibs[1];
}

int main()
{
    int n = 100;
    std::cout << "fibonacci(" << n << "): " << fibonacci(n) << std::endl;
    std::cout << "fibonacci_loop(" << n << "): " << fibonacci_loop(n) << std::endl;
}
