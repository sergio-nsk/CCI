#include <vector>
#include <iostream>

// Inner product of two compressed vector ({a1,n1}, {a2,n2}, ...).
// Normal vector: (a1, a1, a1, a2, a2, a2, a2)
// Compressed vector: ({a1, 3}, {a2, 4})
// Example:
// v1 = ({1, 5}, {2, 3})
// v2 = ({2, 4}, {3, 2}, {4, 5})
// Result: 1*2 + 1*2 + 1*2 + 1*2 + 1*3 + 2*3 + 2*4 + 2*4 = 33

typedef std::pair<int, int> Chunk;

// Naive
class Adapter
{
public:
    Adapter(const std::vector<Chunk> &vec) : _vec(vec)
    {
        reset();
    }

    void reset()
    {
        _i = _vec.begin();
        _cnt = _i != _vec.end() ?  _i->second : 0;

    }

    std::pair<bool, int> get()
    {
        while (_i != _vec.end() && _cnt == 0)
        {
            ++_i;
            _cnt = _i->second;
        }
        if (_cnt != 0)
        {
            --_cnt;
            return std::make_pair(true, _i->first);
        }
        return std::make_pair(false, 0);
    }

  private:
    const std::vector<Chunk> &_vec;
    std::vector<Chunk>::const_iterator _i;
    int _cnt;
};

int innerProductNaive(const std::vector<Chunk> &vec1, const std::vector<Chunk> &vec2)
{
    int product = 0;
    Adapter a1(vec1);
    Adapter a2(vec2);
    std::pair<bool, int> v1;
    std::pair<bool, int> v2;
    while ((v1 = a1.get()).first && (v2 = a2.get()).first)
        product += v1.second * v2.second;
    return product;
}

// Optimal
int innerProduct(const std::vector<Chunk> &vec1, const std::vector<Chunk> &vec2)
{
    if (vec1.empty() || vec2.empty())
        return 0;

    int product = 0;
    int chunkSize1 = vec1[0].second;
    int chunkSize2 = vec2[0].second;

    auto i1 = vec1.begin();
    auto i2 = vec2.begin();

    while (i1 != vec1.end() && i2 != vec2.end())
    {
        auto commonSize = std::min(chunkSize1, chunkSize2);

        product += commonSize * i1->first * i2->first;

        if ((chunkSize1 -= commonSize) == 0)
        {
            ++i1;
            chunkSize1 = i1->second;
        }
        if ((chunkSize2 -= commonSize) == 0)
        {
            ++i2;
            chunkSize2 = i2->second;
        }
    }

    return product;
}

int main()
{
    std::vector<Chunk> vec1 = {{1, 5}, {2, 3}};
    std::vector<Chunk> vec2 = {{2, 4}, {3, 2}, {4, 5}};

    auto product = innerProductNaive(vec1, vec2);
    std::cout << product << std::endl;

    product = innerProduct(vec1, vec2);
    std::cout << product << std::endl;
}
