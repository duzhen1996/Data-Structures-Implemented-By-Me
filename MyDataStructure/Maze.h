//
// Created by 杜臻 on 17/3/29.
//

#ifndef MYDATASTRUCTURE_MAZE_H_H
#define MYDATASTRUCTURE_MAZE_H_H

//在这里我们要进行一个走迷宫的操作，我们的主要工作主要首先我们需要一个栈数组来获得已经走过的路径
//然后我们需要一个二维数组来存储整个迷宫的路线。
//然后我们还需要一个二维数组来获取走过的地方。我个人认为主要是尝试栈中元素以及因为所有的点已经走完

//迷宫的入口从00开始，出口在输入的二维数组的右下角

//我们首先需要去声明一个可以表达方向的枚举
enum Direction {
    //向上
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    UPLEFT = 4,
    UPRIGHT = 5,
    DOWNLEFT = 6,
    DOWNRIGHT = 7,
    NONE = 8
};

struct Location {
    //这里存储着用户当前的位置
    int x = 0;
    int y = 0;
};


//申请一个数组来保存历史数据
//之前打算使用枚举的，发现不好用，我们使用int来表达方向
struct History{
    Location location;
    int direction;
};



//设置移动的数组，第一个形参是移动的防线，第二个形参是当前的位置
Location move(int direction, Location location);

//我们这个是路径查找的核心函数，会打印一个路径出来。是每一步的位置，输入是一个二维数组
//
void getPath(int** maze, int m, int n);


#endif //MYDATASTRUCTURE_MAZE_H_H
