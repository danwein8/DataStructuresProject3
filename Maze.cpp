//================================================================================================================================
// Name        : Maze Container
// Author      : S. Miller
// Version     : 1.1
// Copyright   : S.Miller, usage permitted in unedited form by all current CS students of Westchester Community College
//================================================================================================================================

#include <stdexcept>
#include <vector>
#include "Maze.h"

namespace DS_Maze {

    Maze::Maze() : matrix(nullptr), start(nullptr), end(nullptr), row_count(0), col_count(0), food_count(0) {
    }

    Maze::Maze(const std::string &filename) : Maze() {
        readFile(filename);
    }

    Maze::Maze(const Maze& source) : Maze() {
        copyMaze(source);
    }

    Maze::~Maze() {
        resetMaze();
    }

    Maze& Maze::operator=(const Maze& source) {
        //Test for self assignment
        if ( this == &source )
            return *this;
        //Clear old maze
        resetMaze();
        copyMaze(source);
        return *this;
    }

    void Maze::copyMaze(const Maze& source) {
        row_count = source.row_count;
        col_count = source.col_count;
        food_count = source.food_count;
        if ( source.matrix != nullptr ) {
            matrix = new std::vector<MazeCell*>{row_count * col_count, nullptr};
            //Deep copy
            for (size_t i = 0; i < source.matrix->size() ; ++i ) {
                if ( matrix->at(i) != nullptr )
                    matrix->at(i) = new MazeCell(*source.matrix->at(i));
            }
            start = source.start;
            end = source.end;
        } else
            matrix = nullptr;
    }

    void Maze::resetMaze() {
        row_count = col_count = food_count = 0;
        start = nullptr;
        end = nullptr;
        if ( matrix != nullptr ) {
            for (auto c: *matrix)
                delete c;
            delete matrix;
            matrix = nullptr;
        }
    }

    std::ostream& operator <<(std::ostream& out, const Maze& maze) {
        auto it = maze.matrix->cbegin();

#if MAZE_HEADERS
        out << "   ";
        for ( std::size_t i = 0 ; i < maze.col_count ; ++i )
            out << std::setfill(' ') << std::setw(2) << std::hex << i << " ";
#endif

        for( std::size_t i=0 ; it < maze.matrix->cend(); ++it, ++i ) {
            if (i % maze.col_count == 0) {
                out << std::endl;
#if MAZE_HEADERS
                out << std::setfill(' ') << std::setw(2) << std::hex << i / maze.col_count << " ";
#endif
            }
            if ( *it == nullptr ) {
                out << std::setfill(' ') << std::setw(2) << "XX" << " ";
            } else {
                out << std::setfill(' ') << std::setw(2) << std::hex << (*it)->getFlags() << " ";
            }
        }
        return out;
    }

    void Maze::readFile(const std::string &filename) {
        std::ifstream mazeStream;
        char cell;
        const char NEWLINE = '\n';
        const char OPEN = 'O'; //Any character except X. s. e. o is considered open
        const char WALL = 'X';
        const char START = 's';
        const char END = 'e';
        const char FOOD = 'o';
        const char BLANK = ' ';

        resetMaze();
        mazeStream.open(filename);
        if (mazeStream.is_open()) {
            //Get size of maze matrix
            mazeStream >> row_count;
            mazeStream >> col_count;
            if (mazeStream.bad())
                throw std::runtime_error("Maze integrity violated, missing row and column count.");

            matrix = new std::vector<MazeCell *>{row_count * col_count, nullptr};

            //First set flags by reading the file
            for (size_t r = 0; r < row_count; ++r) {
                for (unsigned int c = 0; c < col_count; ++c) {
                    size_t index = r * col_count + c;

                    if (mazeStream.peek() == BLANK ) {
                        mazeStream.ignore(1);
                        cell = OPEN;
                    } else {
                        mazeStream >> cell;
                        if (mazeStream.fail())
                            throw std::runtime_error("Maze integrity violated, invalid character count.");
                    }
                    if (cell != WALL) {

                        MazeCell *north = nullptr, *west = nullptr;
                        unsigned char cellFlags = 0;
                        //matrix.at(index).setOpen();

                        if (cell == START) {
                            if (start == nullptr) {
                                cellFlags |= MazeCell::START;
                                //start = &matrix.at(index);
                                //matrix.at(index).setStart();
                            } else
                                throw std::runtime_error("Maze integrity violated, multiple starts found.");
                        }

                        if (cell == END) {
                            if (end == nullptr) {
                                cellFlags |= MazeCell::FINISH;
                                //end = &matrix.at(index);
                                //matrix.at(index).setFinish();
                            } else
                                throw std::runtime_error("Maze integrity violated, multiple ends found.");
                        }

                        if (cell == FOOD) {
                            ++food_count;
                            cellFlags |= MazeCell::FOOD;
                            //matrix.at(index).addFood();
                        }

                        if (r > 0 && matrix->at(index - col_count) != nullptr) {
                            north = matrix->at(index - col_count);
                        }
                        if (c > 0 && matrix->at(index - 1) != nullptr ) {
                            west = matrix->at(index - 1);
                        }

                        //Now create cell
                        matrix->at(index) = new MazeCell(MazeCoordinate(r, c), cellFlags, north, west);

                        if (cell == START)
                            start = matrix->at(index);
                        if (cell == END)
                            end = matrix->at(index);

                    }

                    while (mazeStream && mazeStream.peek() == NEWLINE ) {
                        mazeStream.ignore(1);
                    }
                }
            }
            mazeStream.close();

            if ( start == nullptr )
                throw std::runtime_error("Maze integrity violated, no start found.");
            if ( end == nullptr )
                throw std::runtime_error("Maze integrity violated, no end found.");

        } else {
            throw std::runtime_error("Unable to open file, check file path.");
        }
    }

} /* namespace DS_Maze */