#include <string>
#include <memory>

#include "gameobject.h"


class Level
{
    static constexpr int BoardSize = 13;

    std::shared_ptr<GameObject> board[BoardSize][BoardSize];

public:
    bool loadFromFile(const std::string &path);

private:
    bool initBoardLine(int y, const std::array<std::string, GameObject::CellCount> levelLine);
};
