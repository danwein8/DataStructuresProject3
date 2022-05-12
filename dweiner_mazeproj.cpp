#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS and srand
#include <ctime>      // assist to seed to pseudo random generator
#include "Maze.h"
#include "MazeCell.h"

using namespace std;
using namespace DS_Maze;

//precondition: *a is a valid MazeCell pointer that points to the start of a valid maze
//postcondition: maze is traversed and best path with most food is found
std::vector<MazeCell*> processMaze(MazeCell* a, std::vector<MazeCell*> b, std::vector<MazeCell*> &best, MazeCell* &end, MazeCell* &start, size_t &food, size_t &oldFood){
    //inside if statement is where you compare current and best vectors
    if (a->isFinish()) {    //base case if you reach the end
        end = a;
        b.push_back(a);

        if (best.empty()) { //if best is empty, then just push back the current vector and amount of food
            best = b;
            oldFood = food;
            return b;
        }

        if (food >= oldFood && b.size() < best.size()) {    //if the amount of food is greater than the old food and the 
            best = b;                                        //current vector is smaller than the best vector, then
            oldFood = food;                                  //set best to current vector and set old food to current food
            return b;
        }
    }

    if (!a->isExplored()) { //if not explored then push MazeCell* to vector
        b.push_back(a);
    }

    a->setExplored();    //set explored

    if (a->isFood()){    //if food is found increment food counter
        ++food;
    }

    if (a->hasNorth() && !a->getNorth()->isExplored()) {    //recursively search north
        b = processMaze(a->getNorth(), b, best, end, start, food, oldFood);
        b.pop_back();

    }

    if (a->hasEast() && !a->getEast()->isExplored()) {  //recursively search east
        b = processMaze(a->getEast(), b, best, end, start, food, oldFood);
        b.pop_back();

    }

    if (a->hasSouth() && !a->getSouth()->isExplored()) {    //recursively search south
        b = processMaze(a->getSouth(), b, best, end, start, food, oldFood);
        b.pop_back();

    }

    if (a->hasWest() && !a->getWest()->isExplored()) {  //recursively search west
        b = processMaze(a->getWest(), b, best, end, start, food, oldFood);
        b.pop_back();

    }

    if (a->isFood()){   //if you are at a food cell you need to decrement food
        --food;
    }

    a->setUnExplored(); //set cell to unexplored 
    return b;
}

//I COMMENTED OUT MY OUTPUT TO MATCH THE OUTPUT OF THE ASSIGNMENT BUT I KEPT THE CODE FOR DEBUGGING PURPOSES

int main(int argc, char const *argv[])
{
    std::vector<MazeCell*> path;
    std::vector<MazeCell*> best;
    MazeCell* end;
    MazeCell* start;
    size_t food = 0;
    size_t oldFood = 0;
    for (size_t argi=1 ; argi < argc ; ++argi ) {
        //std::cout << argv[argi];
        //std::cout << '\n';
        Maze m(argv[argi]);
        //std::cout << m;
        start = m.getStart();
        MazeCell *mptr = m.getStart();
        path = processMaze(mptr, path, best, end, start, food, oldFood);
        //std::cout << '\n';

 /*       std::cout << std::dec << '\n';
        std::cout << "End: ";
        std::cout << end->getCoordinates();
        std::cout << '\n';
        std::cout << "Start: ";
        std::cout << start->getCoordinates();
        std::cout << '\n';
        std::cout << "Length of best path: ";
        std::cout << best.size();*/
       

        /*for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i]->getCoordinates();
        }*/
        //std::cout << '\n' << '\n';
        std::cout << "Shortest Path: ->";

        for (size_t i = 0; i < best.size(); ++i){
            std::cout << best[i]->getCoordinates();
            if (i != best.size() - 1){
                std::cout << "->";
            }
        }
        std::cout << '\n';
        std::cout << "Food Consumed: ";
        std::cout << oldFood;
    }


    return EXIT_SUCCESS;
}

namespace DS {
}