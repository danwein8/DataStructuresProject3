/*
Thanks to @AnonDrew for turning my recursive solution into a class
CLASS: MazeSolver builds a maze solution by finding the shortest path with as much - possibly all - food possible.
CONSTRUCTOR:
explicit MazeSolver(DS_Maze::Maze&)
 Precondition: Maze is a Miller Maze with valid integrity.
 Postcondition: path modified to shortest path with the most food.
                food modified to amount of food cells within path.
                testPath modified to most recent attempted path.
                testFood modified to amount of food cells with testPath.
PRIVATE MUTATOR (to be used within constructor):
void solve(DS_Maze::MazeCell*)
 Precondition: A MazeCell* to be used as a starting point in a valid Miller Maze.
 Postcondition: path modified to shortest path with the most food.
                food modified to amount of food cells within path.
                testPath modified to last attempted path.
                testFood modified to amount of food cells within testPath.
ACCESSORS:
std::stack<DS_Maze::MazeCell*> solution() const
 Precondition: N/a
 Postcondition: returns a copy of the path stack.
size_t length() const
 Precondition: N/a
 Postcondition: returns the size of the path stack.
size_t consumed() const
 Precondition: N/a
 Postcondition: returns the number of cells containing food stored within the path stack.
FRIEND FUNCTION:
std::ostream& operator<<(std::ostream&, MazeSolver&)
 Precondition: N/a
 Postcondition: All MazeCell coordinates in path are sent to the output stream in reverse order recursively and output
                using desired formatting
VALUE SEMANTICS:
Copy constructor may be used with MazeSolver objects. Assignments not implemented.
DYNAMIC MEMORY USAGE:
N/a
INVARIANT:
"Don't bother" as per Professor Miller.
*/

#ifndef MAZESOLVER_H_
#define MAZESOLVER_H_

#include <ostream>
#include <stack>
#include "Maze.h"

class MazeSolver {
public:
    //CONSTRUCTORS
    MazeSolver() = delete;
    MazeSolver(const MazeSolver&) = default;
    explicit MazeSolver(DS_Maze::Maze& maze) : food(0), testFood(0) { solve(maze.getStart()); }

    //DESTRUCTOR
    ~MazeSolver() = default;

    //ACCESSORS
    [[nodiscard]] std::stack<DS_Maze::MazeCell*> solution() const { return path; }
    [[nodiscard]] size_t length() const { return path.size(); }
    [[nodiscard]] size_t consumed() const { return food; }

    //FRIEND
    friend std::ostream& operator<<(std::ostream&, MazeSolver&);

private:
    std::stack<DS_Maze::MazeCell*> path, testPath;
    size_t food, testFood;

    //PRIVATE MUTATOR
    void solve(DS_Maze::MazeCell*);
};

#endif //MAZESOLVER_H_
