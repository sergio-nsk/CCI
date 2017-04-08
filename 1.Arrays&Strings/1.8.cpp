// Zero Matrix: Write an algorithm such that if an element in an MxN matrix is 0, its entire row and
// column are set to 0.

#include "all.hpp"

template<typename T, size_t M, size_t N>
class array2d
{
public:
    array2d()
    {

    }

    array2d(std::initializer_list<std::array<T, N>> initArray)
    {
        size_t i = 0;
        for (auto &row : initArray)
        {
            std::copy(row.begin(), row.end(), &rawArray.at(i));
            i += N;
        }
    }

    T &at(size_t row, size_t col)
    {
        return rawArray.at(N * row + col);
    }

    const T &at(size_t row, size_t col) const
    {
        return rawArray.at(N * row + col);
    }

    array2d<T, M, N> &fillRow(size_t row, int value = 0)
    {
        for (size_t col = 0; col < N; ++col)
            at(row, col) = value;
        return *this;
    }

    array2d<T, M, N> &fillCol(size_t col, int value = 0)
    {
        for (size_t row = 0; row < M; ++row)
            at(row, col) = value;
        return *this;
    }

    const size_t RowCount = M;
    const size_t ColCount = N;

  private:
    std::array<T, M * N> rawArray;
};

template<typename T, size_t M, size_t N>
bool zero(array2d<T, M, N> &matrix)
{
    bool zeroFirstRow = false;

    for (size_t row = 0; row < M; ++row)
    {
        bool zeroRow = false;
        for (size_t col = 0; col < N; ++col)
        {
            if (matrix.at(row, col) == 0)
            {
                if (row == 0)
                {
                    // skip the first row, it is used to store zerroed columns
                    zeroFirstRow = true;
                    break;
                }
                matrix.at(0, col) = 0;
                zeroRow = true;
            }
        }
        if (zeroRow)
            matrix.fillRow(row);
    }

    for (size_t col = 0; col < N; ++col)
    {
        if (matrix.at(0, col) == 0)
            matrix.fillCol(col);
    }

    if (zeroFirstRow)
        matrix.fillRow(0);

    return true;
}

template<typename T, size_t M, size_t N>
void print(bool result, const array2d<T, M, N> &matrix)
{
    for (size_t row = 0; row < matrix.RowCount; ++row)
    {
        for (size_t col = 0; col < matrix.ColCount; ++col)
        {
            if (col != 0)
                std::cout << ", ";
            int v = matrix.at(row, col);
            if (v == 0)
                std::cout << " ";
            std::cout << v;
        }
        std::cout << std::endl;
    }
}

int main()
{
    array2d<int, 9, 7> matrix
        {
            {11, 12, 13, 14, 15, 16, 17},
            {21, 22, 23, 24, 25, 26, 27},
            {31, 32, 33, 34, 35, 36, 37},
            {41,  0, 43, 44, 45, 46, 47},
            {51, 52, 53, 54, 55, 56, 57},
            {61, 62, 63, 64, 65,  0, 67},
            {71, 72, 73, 74, 75, 76, 77},
            {81, 82, 83, 84, 85, 86, 87},
            {91, 92, 93, 94, 95, 96, 97}
        };

    test(zero<int, 9, 7>, print<int, 9, 7>, matrix);
}
