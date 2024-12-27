#ifndef DIRECTIONUTILS_H
#define DIRECTIONUTILS_H

namespace DirectionUtils
{
    enum class Direction{Left,Right};

    inline Direction GetOppositeDirection(Direction dir)
    {
        if(dir == Direction::Left)
            return Direction::Right;

        return Direction::Left;
    }
}

#endif // DIRECTIONUTILS_H
