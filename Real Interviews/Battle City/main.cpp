#include "level.h"

int main()
{
    Level level;
    if (!level.loadFromFile("level.txt"))
        return 1;
    return 0;
}
