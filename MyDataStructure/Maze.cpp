//
// Created by 杜臻 on 17/3/29.
//

#include "Maze.h"
#include <iostream>

using namespace std;

void move(Direction direction, Location &location) {
    switch (direction) {
        case UP:
            location.y--;
            break;
        case DOWN:
            location.y++;
            break;
        case LEFT:
            location.x--;
            break;
        case RIGHT:
            location.x++;
            break;
        case UPLEFT:
            location.y--;
            location.x--;
            break;
        case UPRIGHT:
            location.y--;
            location.x++;
            break;
        case DOWNLEFT:
            location.y++;
            location.x--;
            break;
        case DOWNRIGHT:
            location.y++;
            location.x++;
            break;

        default:
            cout << "不可能来到这里" << endl;
            exit(-1);

    }
}

//m是行数，n是列数
void getPath(int** &maze, int m, int n) {
    //首先我们需要在外面加一层0，防止寻路的时候走出去
    //为此我们在这里面需要定义一个新的数组，这个数组的工作就是在原有数组后面加一圈0
    //首先我们需要new一个二维数组
    int **newmaze = new int *[m + 2];
    for (int i = 0; i < m + 2; ++i) {
        newmaze[i] = new int[n + 2];
    }
    //现在变成了一个m+1行，n+1列的数组，然后我们使用传入的数组初始化新的数组
    for (int j = 0; j < m + 2; ++j) {
        for (int i = 0; i < n + 2; ++i) {
            //第一行和最后一行我们直接给一行0
            if (j == 0 || j == m+1) {
                newmaze[j][i] = 0;
            } else {
                //如果不是第一行和最后一行，那就在一行的第一个位置和最后一个位置添加0，初始的location从（0，0）变为（1，1）
                if (i == 0 || i == n+1) {
                    newmaze[j][i] = 0;
                } else {
                    //在第一列和最后一列之间的所有地方放传进来的
                    newmaze[j][i] = maze[j-1][i-1];
                }
            }

        }
    }

    //这里我们先delete输入数组
    for (int l = 0; l < m; ++l) {
        delete maze[l];
    }
    delete maze;

    maze = newmaze;
    //我们现在打印一下新的maze数组
    for (int k = 0; k < m+2; ++k) {
        for (int i = 0; i < n+2; ++i) {
            cout << maze[k][i] << " , ";
        }
        cout << endl;
    }


    //当函数结束的之后我们进行析构操作
    for (int l = 0; l < m+2; ++l) {
        delete maze[l];
    }

    //这里就进行完所有的预处理了，我们下面来进行真正的走迷宫的操作。








    //迷宫走完了
    delete maze;

}

