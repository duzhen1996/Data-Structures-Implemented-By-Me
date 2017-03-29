//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "Maze.h"

using namespace std;

int main(int argc, const char *argv[]) {

    //我们先规定输入数组，是一个3x3的输入数组
    int **inputMaze = new int *[3];
    for (int i = 0; i < 3; ++i) {
        inputMaze[i] = new int[3];
    }

    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 3; ++i) {
            inputMaze[j][i] = 1;
        }
    }

    //然后我们把这个迷宫放到走迷宫的函数中
    getPath(inputMaze , 3,3);


    return 0;
}
