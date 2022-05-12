//================================================================================================================================
// Name        : Maze Cell Container
// Author      : S. Miller
// Version     : 1.1
// Copyright   : S.Miller, usage permitted in unedited form by all current CS students of Westchester Community College
//================================================================================================================================


#include "MazeCell.h"

namespace DS_Maze {

    std::ostream& operator <<(std::ostream& out, const MazeCoordinate& p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }

    MazeCell::MazeCell(MazeCoordinate coordinate, unsigned char flags, MazeCell *north, MazeCell *west) :
            coordinate(coordinate), flags(flags), north(north), west(west), east(nullptr), south(nullptr){
        if ( north != nullptr) {
            this->flags |= NORTH;
            setDirection(north, SOUTH, this);
        }
        if ( west != nullptr ) {
            this->flags |= WEST;
            setDirection(west, EAST, this);
        }
    }

    void MazeCell::setDirection(MazeCell *from, unsigned char direction, MazeCell *leadsTo) {
        //from = leadsTo;
        from->flags |= direction;
        switch (direction) {
            case NORTH:
                from->north = leadsTo; break;
            case WEST:
                from->west = leadsTo; break;
            case EAST:
                from->east = leadsTo; break;
            case SOUTH: default:
                from->south = leadsTo; break;
        }
    }
} /* namespace DS_Maze */