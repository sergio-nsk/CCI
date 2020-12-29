#include <bitset>

class FullArray;

enum class ObjectKind
{
    Wall = 'W',
    Breaks = 'B',
    HeadQuarters = 'H',
    Space = '.'
};

class GameObject
{
public:
    // Game objects can be placed on 1/2 of level cell
    static constexpr int CellFactor = 2;

    GameObject(std::bitset<CellFactor * CellFactor> &&c)
        : cells(std::move(c))
    {
    }

    virtual ~GameObject()
    {
    }

private:
    std::bitset<CellFactor * CellFactor> cells;
};
