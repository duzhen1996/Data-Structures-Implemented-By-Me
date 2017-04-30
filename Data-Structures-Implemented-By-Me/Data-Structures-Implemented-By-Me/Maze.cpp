//
// Created by 杜臻 on 17/3/29.
//

#include "Maze.h"
#include <iostream>

using namespace std;

Location move(int direction, Location location) {
//    cout << "direction : " << direction << endl;

    switch (direction) {
        case 0:
            location.y--;
            break;
        case 1:
            location.y++;
            break;
        case 2:
            location.x--;
            break;
        case 3:
            location.x++;
            break;
        case 4:
            location.y--;
            location.x--;
            break;
        case 5:
            location.y--;
            location.x++;
            break;
        case 6:
            location.y++;
            location.x--;
            break;
        case 7:
            location.y++;
            location.x++;
            break;

        default:
            cout << "can not be here" << endl;
            exit(-1);
    }
//    cout << location.x << " , " << location.y << endl;
    return location;

}

//m是行数，n是列数
void getPath(int **maze, int m, int n) {
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
            if (j == 0 || j == m + 1) {
                newmaze[j][i] = 0;
            } else {
                //如果不是第一行和最后一行，那就在一行的第一个位置和最后一个位置添加0，初始的location从（0，0）变为（1，1）
                if (i == 0 || i == n+1) {
                    newmaze[j][i] = 0;
                } else {
                    //在第一列和最后一列之间的所有地方放传进来的
                    newmaze[j][i] = maze[j - 1][i - 1];
                }
            }

        }
    }

    //这里我们先delete输入数组
    for (int l = 0; l < m ; ++l) {
        delete[] maze[l];
    }
    delete[] maze;

    maze = newmaze;
    //我们现在打印一下新的maze数组
    for (int k = 0; k < m + 2; ++k) {
        for (int i = 0; i < n + 2; ++i) {
            cout << maze[k][i] << " , ";
        }
        cout << endl;
    }




    //这里就进行完所有的预处理了，我们下面来进行真正的走迷宫的操作。
    //因为之前我们加了一圈0，所以这个时候入口是（1，1），出口是（m+1 , n+1）前面是m+1是上下方向的坐标，n+1是左右方向的坐标

    //首先申请一个栈来存储历史空间
    History *historyStack = new History[m * n];

    //这个是栈顶指针，当栈顶索引是-1的时候代表栈是空的
    int historyStackIndex = -1;

    //我们为栈中加入起点
    historyStackIndex++;
    historyStack[historyStackIndex].location.x = 1;
    historyStack[historyStackIndex].location.y = 1;
    //从上方开始，按照枚举的顺序进行尝试
    historyStack[historyStackIndex].direction = 0;

    //然后我们再创建一个数组，这个数组中存的是我们我们已经到过的点，所有曾经在这个栈中出现的位置都会被标记。不走重复路
    //已经走过的地方会在这个二维数组中被标记为1
    int **markedLocation = new int *[m + 2];
    for (int i1 = 0; i1 < m + 2; ++i1) {
        markedLocation[i1] = new int[n + 2];
    }

    for (int j1 = 0; j1 < m + 2; ++j1) {
        for (int i = 0; i < n + 2; ++i) {
            markedLocation[j1][i] = 0;
        }
    }

    markedLocation[1][1] = 1;


    while ((historyStack[historyStackIndex].location.x != n ) ||
           (historyStack[historyStackIndex].location.y != m )) {
        //当栈是空的，那么就说明真的找不到了直接退出循环
        if (historyStackIndex == -1) {
            cout << "没有从入口到出口的路径了" << endl;

            //当函数结束的之后我们进行析构操作
            for (int l = 0; l < m + 2; ++l) {
                delete maze[l];
            }

            //迷宫走完了
            delete[] maze;

            delete[] historyStack;

            return;
        }

        //这里说明栈不为空，那么我们就要进行各个方向的尝试
        for (int i = historyStack[historyStackIndex].direction; i < 8; ++i) {
            //我们通过一个move获得新的位置
//            cout << historyStack << endl;
            Location newlocation = move(i, historyStack[historyStackIndex].location);
            //然后我们看看这个位置是不是墙，以及这个位置是不是之前走过，
            cout << "maze[newlocation.y][newlocation.x] : " << maze[newlocation.y][newlocation.x] << endl;
            cout << "location : " << newlocation.x << " ,  " << newlocation.y << endl;
            if (maze[newlocation.y][newlocation.x] != 0
                && markedLocation[newlocation.y][newlocation.x] != 1) {
                //如果不是墙，也没有走过，那就加到栈顶，并且推出循环
                //我们先将当前位置的方向预制成下一个方向
                historyStack[historyStackIndex].direction++;

                historyStackIndex++;
                historyStack[historyStackIndex].location = newlocation;
                historyStack[historyStackIndex].direction = 0;

                //入栈之后设定为已达路径
                markedLocation[newlocation.y][newlocation.x] = 1;
                break;
            }

        }

        //如果推出循环的理由是循环跑满了，那就说明历史栈顶部的东西要退出了
        if (historyStack[historyStackIndex].direction == 8) {
            historyStackIndex--;
        }
    }


    //当函数结束的之后我们进行析构操作
    for (int l = 0; l < m + 2; ++l) {
        delete[] maze[l];
    }

    //迷宫走完了
    delete[] maze;

    delete[] historyStack;

}

