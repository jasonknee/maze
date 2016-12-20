
//  Copyright © 2016 Oh Jun Kwon. All rights reserved.

#include "MySolver.hpp"
#include "Maze.hpp"

#include "MazeSolution.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MySolver, "My Solver! (Required)");


Direction direction1(int a){
    if (a==0)
        return Direction::up;
    else if (a==1)
        return Direction::down;
    else if (a==2)
        return Direction::right;
    else if (a==3)
        return Direction::left;
}

char* select_dir(std::vector<char*> storage, int check){
    int num;
    char* answer;
    num = rand()%check;
    answer = storage[num];

    return answer;
}

void create(const Maze& maze, std::vector<std::vector<bool>>& m, MazeSolution& mazeSolution, int h, int w){

    std::vector<char*> storage;
    int check=0;

point:
    if (mazeSolution.isComplete()==0){
        m[h][w] = true;

        if ((maze.wallExists(w,h,direction1(0))==0) && (m[h-1][w]==false)){
            storage.push_back("up");
            check++;
        }
        if ((maze.wallExists(w,h,direction1(1))==0) && (m[h+1][w]==false)){
            storage.push_back("down");
            check++;
        }
        if ((maze.wallExists(w,h,direction1(2))==0) && (m[h][w+1]==false)){
            storage.push_back("right");
            check++;
        }
        if ((maze.wallExists(w,h,direction1(3))==0) && (m[h][w-1]==false)){
            storage.push_back("left");
            check++;
        }

        if (check==0){
            mazeSolution.backUp();
            auto a = mazeSolution.getCells();
            
            w= a.back().first;
            h =a.back().second;
            goto point;
        }

        char* p;
        if (p=select_dir(storage, check)){
            if (strcmp(p, "up")==0){
                mazeSolution.extend(direction1(0));
                h--;       
            }
            if (strcmp(p, "down")==0){
                mazeSolution.extend(direction1(1));
                h++;
            }
            if (strcmp(p,"right")==0){
                mazeSolution.extend(direction1(2));
                w++;
            }
            if (strcmp(p,"left")==0){
                mazeSolution.extend(direction1(3));
                w--;
            }
        }

        create(maze,m,mazeSolution,h,w);         
        
    }
    else
        return;


}


void MySolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    std::vector<std::vector<bool>> m;
    int height = maze.getHeight();
    int width = maze.getWidth();
   
    m.resize(height, std::vector<bool>(width, false));
 
    create(maze, m, mazeSolution, 0,0);
}
