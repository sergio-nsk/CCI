#include <bitset>

class FullArray;

enum class ObjectKind
{
    Wall = 'W',
    Brick = 'B',
    HeadQuarter = 'H',
    Space = '.'
};

class GameObject
{
public:
    // Game objects can be placed on 1/2 of level cell
    static constexpr int CellCount = 36;

    GameObject(std::bitset<CellCount * CellCount> &&c)
        : cells(c)
    {
    }

    virtual ~GameObject()
    {
    }

private:
    std::bitset<CellCount * CellCount> cells;
};
