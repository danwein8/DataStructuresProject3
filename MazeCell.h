//================================================================================================================================
// Name        : Maze Cell Container
// Author      : S. Miller
// Version     : 1.1
// Copyright   : S.Miller, usage permitted in unedited form by all current CS students of Westchester Community College
//================================================================================================================================


#ifndef MAZECELL_H_
#define MAZECELL_H_

#include <iostream>
#include <stack>

namespace DS_Maze {

    struct MazeCoordinate {
        MazeCoordinate() = delete;
        MazeCoordinate(size_t x, size_t y) : x(x), y(y) {}
        size_t x;
        size_t y;
    };
    std::ostream& operator <<(std::ostream& out, const MazeCoordinate& p);


    class MazeCell {
    public:
        //No default constructor
        MazeCell() = delete;

        MazeCell(MazeCoordinate coordinate, unsigned char flags, MazeCell* north, MazeCell *west);

        //Return the flags, this is here to be able to OUTPUT the max with all the numbers
        //Returns a number instead of char so that it does not need to be cast
        [[nodiscard]] unsigned short getFlags() const { return flags; }

        MazeCell* getNorth() { return north; }
        MazeCell* getWest() { return west; }
        MazeCell* getEast() { return east; }
        MazeCell* getSouth() { return south; }
        [[nodiscard]] const MazeCoordinate& getCoordinates() const { return coordinate; }

        //===MAINTAIN DIRECTION===
        //Each cell keeps track of which directions you can go from the cell as North, East, South, West
        // If a direction is open, a move is permitted in this direction
        // If a direction is closed, a move is NOT permitted in this direction

        void openNorth() { flags |= NORTH; north->flags |= SOUTH; }
        void openEast() { flags |= EAST; east->flags |= WEST; }
        void openWest() { flags |= WEST; west->flags |= EAST; }
        void openSouth() { flags |= SOUTH; south->flags |= NORTH; }
        void closeNorth() { flags &= ~NORTH; north->flags &= ~SOUTH; }
        void closeEast() { flags &= ~EAST; east->flags &= ~WEST; }
        void closeWest() { flags &= ~WEST; west->flags &= ~EAST; }
        void closeSouth() { flags &= ~SOUTH; south->flags &= ~NORTH; }

        //Conditionals for direction
        //[[nodiscard]] bool isWall() const { return flags == WALL; } //Walls should contain no other flags
        [[nodiscard]] bool isNorthOpen() const { return (flags & NORTH) == NORTH; }
        [[nodiscard]] bool isEastOpen() const { return (flags & EAST) == EAST; }
        [[nodiscard]] bool isWestOpen() const { return (flags & WEST) == WEST; }
        [[nodiscard]] bool isSouthOpen() const { return (flags & SOUTH) == SOUTH; }
        [[nodiscard]] bool isBlocked() const { return !(isNorthOpen() || isEastOpen() || isSouthOpen() || isWestOpen()); }

        [[nodiscard]] bool hasNorth() const { return north != nullptr; }
        [[nodiscard]] bool hasWest() const { return west != nullptr; }
        [[nodiscard]] bool hasEast() const { return east != nullptr; }
        [[nodiscard]] bool hasSouth() const { return south != nullptr; }

        //Food, does the cell contain food
        [[nodiscard]] bool isFood() const { return (flags & FOOD) == FOOD; }
        void addFood() { flags |= FOOD; }
        void removeFood() { flags &= ~FOOD; }

        //Mark a call as explored
        [[nodiscard]] bool isExplored() const { return (flags & EXPLORED) == EXPLORED; }
        void setExplored() { flags |= EXPLORED; }
        void setUnExplored() { flags &= ~EXPLORED; }


        //Sets the start of the maze, used by Maze
        void setStart() { flags |= START;  }
        //Sets the finish of the maze, used by Maze
        void setFinish() { flags |= FINISH;  }
        //Is the cell the start cell
        [[nodiscard]] bool isStart() const { return (flags & START) == START; }
        //Is the cell the finish cell
        [[nodiscard]] bool isFinish() const { return (flags & FINISH) == FINISH; }

        enum Flags
        {
            NORTH = 1 << 0,     //1
            WEST = 1 << 1,      //2
            EAST = 1 << 2,      //4
            SOUTH = 1 << 3,     //8
            FOOD = 1 << 4,      //16 (1x)
            START = 1 << 5,     //32 (2x)
            FINISH = 1 << 6,    //64 (4x)
            EXPLORED = 1 << 7   //128 (8x)
        };
    private:
        MazeCoordinate coordinate;
        unsigned char flags;
        MazeCell * north;
        MazeCell * west;
        MazeCell * east;
        MazeCell * south;

        //set Direction that a cell can go
        static void setDirection(MazeCell* from, unsigned char direction, MazeCell* leadsTo);
    };

} /* namespace DS_Maze */

#endif /* MAZECELL_H_ */