#include <iostream>
#include <vector>
#include <cassert>

template <typename T>
class Vector
{
    std::vector<T> cont;

  public:
    Vector(const std::size_t n) : cont(n)
    {
    }

    Vector(const std::size_t n, const double initialValue) : cont(n, initialValue)
    {
    }

    std::size_t size() const
    {
        return cont.size();
    }

    T operator [] (const std::size_t i) const
    {
        return cont[i];
    }

    T &operator[] (const std::size_t i)
    {
        return cont[i];
    }
};

// Function template for the + operator
template <typename T>
Vector<T> operator + (const Vector<T> &a, const Vector<T> &b)
{
    Vector<T> result(a.size());
    for (std::size_t s = 0; s < a.size(); ++s)
    {
        result[s] = a[s] + b[s];
    }
    return result;
}

// Function template for the * operator
template <typename T>
Vector<T> operator * (const Vector<T> &a, const Vector<T> &b)
{
    Vector<T> result(a.size());
    for (std::size_t s = 0; s < a.size(); ++s)
    {
        result[s] = a[s] * b[s];
    }
    return result;
}

// Function template for << operator
template <typename T>
std::ostream &operator << (std::ostream &os, const Vector<T> &cont)
{
    for (std::size_t i = 0; i < cont.size(); ++i)
    {
        os << cont[i] << ' ';
    }
    return os;
}

template <typename T, typename Cont = std::vector<T>>
class MyVector
{
    Cont cont;

  public:
    MyVector(const std::size_t n) : cont(n)
    {
    }

    MyVector(const std::size_t n, const double initialValue) : cont(n, initialValue)
    {
    }

    MyVector(const Cont &other) : cont(other)
    {
    }

    // assignment operator for MyVector of different type
    template <typename T2, typename R2>
    MyVector &operator = (const MyVector<T2, R2> &other)
    {
        assert(size() == other.size());
        for (std::size_t i = 0; i < cont.size(); ++i)
            cont[i] = other[i];
        return *this;
    }

    std::size_t size() const
    {
        return cont.size();
    }

    T operator [] (const std::size_t i) const
    {
        return cont[i];
    }

    T &operator [] (const std::size_t i)
    {
        return cont[i];
    }

    const Cont &data() const
    {
        return cont;
    }

    Cont &data()
    {
        return cont;
    }
};

// MyVector + MyVector
template <typename T, typename Op1, typename Op2>
class MyVectorAdd
{
    const Op1 &op1;
    const Op2 &op2;

  public:
    MyVectorAdd(const Op1 &a, const Op2 &b) : op1(a), op2(b) {}

    T operator[](const std::size_t i) const
    {
        return op1[i] + op2[i];
    }

    std::size_t size() const
    {
        return op1.size();
    }
};

// elementwise MyVector * MyVector
template <typename T, typename Op1, typename Op2>
class MyVectorMul
{
    const Op1 &op1;
    const Op2 &op2;

  public:
    MyVectorMul(const Op1 &a, const Op2 &b) : op1(a), op2(b) {}

    T operator[](const std::size_t i) const
    {
        return op1[i] * op2[i];
    }

    std::size_t size() const
    {
        return op1.size();
    }
};

template <typename T, typename R1, typename R2>
MyVector<T, MyVectorAdd<T, R1, R2>> operator + (const MyVector<T, R1> &a, const MyVector<T, R2> &b)
{
    return MyVector<T, MyVectorAdd<T, R1, R2>>(MyVectorAdd<T, R1, R2>(a.data(), b.data()));
}

// function template for the * operator
template <typename T, typename R1, typename R2>
MyVector<T, MyVectorMul<T, R1, R2>> operator * (const MyVector<T, R1> &a, const MyVector<T, R2> &b)
{
    return MyVector<T, MyVectorMul<T, R1, R2>>(MyVectorMul<T, R1, R2>(a.data(), b.data()));
}

// function template for << operator
template <typename T>
std::ostream &operator << (std::ostream &os, const MyVector<T> &cont)
{
    for (std::size_t i = 0; i < cont.size(); ++i)
    {
        os << cont[i] << ' ';
    }
    return os;
}

int main()
{
    Vector<double> x(10, 5.4);
    Vector<double> y(10, 10.3);

    Vector<double> result(10);

    result = x + x + y * y;

    std::cout << result << std::endl;

    MyVector<double> u(10, 5.4);
    MyVector<double> v(10, 10.3);

    MyVector<double> z(10);

    z = u + u + v * v;

    std::cout << z << std::endl;
}
