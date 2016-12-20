
//  Copyright © 2016 Oh Jun Kwon. All rights reserved.

#include "MyGenerator.hpp"
#include "Maze.hpp"
#include <ics46/factory/DynamicFactory.hpp>

#include <iostream>
#include <string>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MyGenerator, "My Generator! (Required)");

Direction direction(int a){
    if (a==0)
        return Direction::up;
    else if (a==1)
        return Direction::down;
    else if (a==2)
        return Direction::right;
    else if (a==3)
        return Direction::left;
}

char* pick_dir(std::vector<char*> storage, int check){
    int num;
    char* answer;
    num = rand()%check;
    answer=storage[num];

    return answer;
}

void create(Maze& maze, std::vector<std::vector<bool>>& m, int w, int h){
    int check=0;
    m[w][h] = true;
    std::vector<char*> storage;

    if ((h>0) && (m[w][h-1]==false)){
        storage.push_back("up");
        check++;
    }
    if ((h<maze.getHeight()-1) && (m[w][h+1]==false)){
        storage.push_back("down");
        check++;
    }
    if ((w>0) && (m[w-1][h]==false)){
        storage.push_back("left");
        check++;
    }
    if ((w<maze.getWidth()-1) && (m[w+1][h]==false)){
        storage.push_back("right");
        check++;
    }
    if (check==0)
        return;
           
    char* p;
    if (p=pick_dir(storage, check)){
        if (strcmp(p, "up")==0){
            maze.removeWall(w,h,direction(0));
            h--;
        }
        if (strcmp(p,"down")==0){
            maze.removeWall(w,h,direction(1));
            h++;
        }
        if (strcmp(p,"right")==0){
            maze.removeWall(w,h,direction(2));
            w++;
        }
        if (strcmp(p,"left")==0){
            maze.removeWall(w,h,direction(3));
            w--;
        }
    } 
    create(maze, m, w, h);
    
    if (m[w][h] == true){

        create(maze, m ,w, h);

    }

}

void MyGenerator::generateMaze(Maze & maze){

    maze.addAllWalls();
   
    std::vector<std::vector<bool>> m;
    int height = maze.getHeight();
    int width = maze.getWidth();

    m.resize(width, std::vector<bool>(height, 0));    


    create(maze, m, rand()%(maze.getWidth()), rand()%(maze.getHeight()));

}

