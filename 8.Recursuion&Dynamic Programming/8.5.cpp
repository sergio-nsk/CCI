// Recursive Multiply: Write a recursive function to multiply two positive integers without using
// the * operator (or / operator). You can use addition, subtraction, and bit shifting, but you should
// minimize the number of those operations.

#include <iostream>

class Product
{
    static int counter;

public:
    /* This is an algorithm called the peasant algorithm.
     * https://en.wikipedia.org/wiki/Multiplication_algorithm#Peasant_or_binary_multiplication
     */
    static int minProduct(int a, int b)
    {
        if (a < b)
            return minProduct(b, a);
        int value = 0;
        while (a > 0)
        {
            ++counter;
            if (a % 2 == 1)
                value += b;
            a >>= 1;
            b <<= 1;
        }
        return value;
    }

    static void main()
    {
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                int prod1 = minProduct(i, j);
                int prod2 = i * j;
                if (prod1 != prod2)
                    std::cout << "ERROR: " << i << " * " << j << " = " << prod2 << ", not " << prod1 << std::endl;
            }
        }
    }

};

int Product::counter = 0;

int main()
{
    Product::main();
}
