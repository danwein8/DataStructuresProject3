//Thanks to @AnonDrew for making a class out of my recursive solution

#include <ostream>
#include <stack>
#include "MazeSolver.h"

//FRIEND
std::ostream& operator<<(std::ostream& outs, MazeSolver& solution) {
    if (!solution.path.empty()) {
        DS_Maze::MazeCell* top = solution.path.top();
        solution.path.pop();
        operator<<(outs, solution);
        outs << "->" << top->getCoordinates();
        solution.path.push(top);
    }
    return outs;
}

//PRIVATE MUTATOR
void MazeSolver::solve(DS_Maze::MazeCell* cell) {
    testPath.push(cell);
    cell->setExplored();
    if (cell->isFood()) {
        ++testFood;
    }
    //base case
    if (cell->isFinish()) {
        //case: on first run, path will always be empty; otherwise only change solution if a better one was found
        if (path.empty() || food < testFood || (food == testFood && path.size() > testPath.size())) {
            path = testPath;
            food = testFood;
        }
    }
    //traverses the maze in one direction until no longer possible, then backtracks and tries the most recent alternative
    if (cell->hasNorth() && !cell->getNorth()->isExplored()) {
        MazeSolver::solve(cell->getNorth());
    }
    if (cell->hasEast() && !cell->getEast()->isExplored()) {
        MazeSolver::solve(cell->getEast());
    }
    if (cell->hasSouth() && !cell->getSouth()->isExplored()) {
        MazeSolver::solve(cell->getSouth());
    }
    if (cell->hasWest() && !cell->getWest()->isExplored()) {
        MazeSolver::solve(cell->getWest());
    }
    //pops cells up to the most recent multi-directional cell in testPath
    testPath.pop();
    //allows for exploring previously explored paths but from an alternative approach
    cell->setUnExplored();
    //make sure testFood is accurate after backtracking
    if (cell->isFood()) {
        --testFood;
    }
}
