#ifndef DIRECTIONUTILS_H
#define DIRECTIONUTILS_H

namespace DirectionUtils
{
    enum class Direction{Left,Right};

    inline Direction GetOppositeDirection(Direction dir)
    {
        return dir == Direction::Left ? Direction::Right : Direction::Left;
    }
}

#endif // DIRECTIONUTILS_H
