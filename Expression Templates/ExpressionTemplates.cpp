#include <vector>
#include <assert.h>
#include <iostream>

// class Vector
// {
// public:
//     Vector(std::size_t n) : elems(n)
//     {
//     }

//     double &operator[](std::size_t i)
//     {
//         return elems[i];
//     }

//     double operator[](std::size_t i) const
//     {
//         return elems[i];
//     }

//     std::size_t size() const
//     {
//         return elems.size();
//     }

// private:
//     std::vector<double> elems;
// };
//
// Vector operator + (const Vector &u, const Vector &v)
// {
//     assert(u.size() == v.size());
//     Vector sum(u.size());
//     for (std::size_t i = 0; i < u.size(); ++i)
//          sum[i] = u[i] + v[i];
//     return sum;
// }

template <typename E>
class VectorExpression
{
public:
    double operator [] (std::size_t i) const
    {
        return static_cast<const E&>(*this)[i];
    }

    std::size_t size() const
    {
        return static_cast<const E&>(*this).size();
    }

    // The following overload conversions to E, the template argument type;
    // e.g., for VecExpression<VecSum>, this is a conversion to VecSum.
    operator E& ()
    {
        return static_cast<E&>(*this);
    }

    operator const E& () const
    {
        return static_cast<const E&>(*this);
    }
};

class Vector : public VectorExpression<Vector>
{
public:
    Vector(std::size_t n) : elems(n)
    {
    }

    // construct vector using initializer list
    Vector(std::initializer_list<double> init)
    {
        for(auto i: init)
            elems.push_back(i);
    }

    // construct from any VectorExpression, forcing its evaluation.
    template <typename E>
    Vector(const VectorExpression<E>& vec) : elems(vec.size())
    {
        for (std::size_t i = 0; i != vec.size(); ++i) {
            elems[i] = vec[i];
        }
    }

    double &operator[](std::size_t i)
    {
        return elems[i];
    }

    double operator[](std::size_t i) const
    {
        return elems[i];
    }

    std::size_t size() const
    {
        return elems.size();
    }

private:
    std::vector<double> elems;
};

template <typename E1, typename E2>
class VectorSum : public VectorExpression<VectorSum<E1, E2> >
{
    const E1& _u;
    const E2& _v;

public:
    VectorSum(const E1& u, const E2& v) : _u(u), _v(v)
    {
        assert(u.size() == v.size());
    }

    double operator[](std::size_t i) const
    {
        return _u[i] + _v[i];
    }

    std::size_t size() const
    {
        return _v.size();
    }
};

template <typename E1, typename E2>
const VectorSum<E1, E2> operator + (const E1& u, const E2& v)
{
    return VectorSum<E1, E2>(u, v);
}

// With the above definitions, the expression a + b + c is of type
// VectorSum<VectorSum<Vector, Vector>, Vector>
// so Vector x = a + b + c invokes the templated Vector constructor with this type as its E template argument. Inside this constructor, the loop body
// elems[i] = v[i];
// is effectively expanded (following the recursive definitions of operator+ and operator[] on this type) to
// elems[i] = a.elems[i] + b.elems[i] + c.elems[i];
// with no temporary vectors needed and only one pass through each memory block.

int main()
{
    Vector v0 = {23.4,  12.5,  144.56, 90.56};
    Vector v1 = {67.12,  34.8,  90.34, 89.30};
    Vector v2 = {34.90, 111.9,  45.12, 90.5 };
    VectorSum<VectorSum<Vector, Vector>, Vector> sum = v0 + v1 + v2;

    Vector v3(4);

    for (auto i = 0U; i < v0.size(); ++i)
         v3[i] = sum[i];

    for (auto i = 0U; i < v3.size(); ++i)
         std::cout << v3[i] << std::endl;
}