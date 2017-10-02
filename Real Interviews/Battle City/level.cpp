#include <fstream>
#include <array>

#include "level.h"

bool Level::loadFromFile(const std::string &path)
{
    std::array<std::string, GameObject::CellCount> levelLine;
    std::ifstream file(path);
    std::string line;
    for (int j = 0; j < BoardSize; ++j)
    {
        for (int i = 0; i < levelLine.size(); )
        {
            if (!file.good()) // if error or eof
                return false;

            file >> levelLine[i];
            if (levelLine[i].length() < BoardSize)
                return false;

            if (levelLine[i][0] == '#')
                continue;
            ++i;
        }
        if (!initBoardLine(j, levelLine))
            return false;
    }
    return true;
}

bool Level::initBoardLine(int y, const std::array<std::string, GameObject::CellCount> levelLine)
{
    for (int x = 0; x < BoardSize; ++x)
    {
        std::bitset<GameObject::CellCount * GameObject::CellCount> cells;
        auto kind = ObjectKind::Space;

        for (int i = 0; i < GameObject::CellCount; ++ i)
        {
            for (int j = x * GameObject::CellCount; j < (x + 1) * GameObject::CellCount; ++j)
            {
                if (kind == ObjectKind::Space)
                    kind = static_cast<ObjectKind>(levelLine[i][j]);

                cells << 1;

                if (levelLine[i][j] != static_cast<char>(ObjectKind::Space))
                {
                    if (levelLine[i][j] == static_cast<char>(kind))
                        cells |= 1;
                    else
                        return false;
                }
            }
        }

        board[y][x] = std::make_shared<GameObject>(std::move(cells));
    }
    return true;
}
