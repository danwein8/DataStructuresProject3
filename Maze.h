//==========================================================================================================================
// Name        : Maze Container
// Author      : S. Miller
// Version     : 1.1
// Copyright   : S.Miller, usage permitted in unedited form by all current CS students of Westchester Community College
//================================================================================================================================


#ifndef MAZE_H_
#define MAZE_H_

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "MazeCell.h"

//Should the output of maze output the row/column numbers
//Set to 1 for yes, 0 for no
#define MAZE_HEADERS 1

namespace DS_Maze {

    class Maze {
    public:
        //Constructors and other items to make Maze variant safe
        Maze();
        Maze(const Maze&);
        ~Maze();
        Maze& operator=(const Maze&);

        //Create a maze and load a file, will crash if text file is invalid
        Maze(const std::string&);
        //Load a maze file, will crash if text file is invalid
        void readFile(const std::string &filename);

        //Returns the mazes starting point
        MazeCell* getStart() { return start; };

        //Get the amount of food that exists in the maze
        [[nodiscard]] std::size_t getFoodCount() const { return food_count; }

        //Output the entire maze in HEX numeric format, the output here will take time to understand
        //Left most value
        //8 = Explored
        //4 = finish
        //2 = start
        //1 = food            Note: No cell can combine start, food, and finish
        //Right most value
        //1 = can go north
        //2 = can go West
        //4 = can fo East
        //8 = can go south
        //The flags can be added
        //For example, if you can go both RIGHT and LEFT in a MazeCell that contains food, you will see
        //  16   (the 1 is food, 4 + 2 = 6
        friend std::ostream& operator <<(std::ostream&, const Maze&);

    private:
        std::vector<MazeCell*> * matrix;
        MazeCell * start;
        MazeCell * end;
        std::size_t row_count;
        std::size_t col_count;
        std::size_t food_count;

        void copyMaze(const Maze&);
        void resetMaze();
    };

} /* namespace DS_Maze */

#endif /* MAZE_H_ */