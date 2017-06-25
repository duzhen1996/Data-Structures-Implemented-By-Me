//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "Dijkstra.h"

using namespace std;


int main(int argc, const char *argv[]) {

    int itemCount = 7;

    int *dist = new int[itemCount];

    int *prev = new int[itemCount];

    //创造二维矩阵
    int **Graph = new int *[itemCount];

    for (int i = 0; i < itemCount; ++i) {
        Graph[i] = new int[itemCount];
    }

    //邻接矩阵初始化
    for (int k = 0; k < itemCount; ++k) {
        for (int i = 0; i < itemCount; ++i) {
            Graph[k][i] = MAX_INT;
        }
    }

    //加入几条边
    Graph[0][5] = 10;
    Graph[0][1] = 22;
    Graph[1][2] = 6;
    Graph[5][6] = 7;
    Graph[6][1] = 2;
    Graph[6][4] = 11;
    Graph[3][2] = 23;
    Graph[3][4] = 12;

    Dijkstra(dist, Graph, prev, itemCount, 0);

    for (int k = 0; k < itemCount; ++k) {
        cout << dist[k] << endl;
    }

    //析构
    delete[]dist;
    delete[]prev;

    for (int j = 0; j < itemCount; ++j) {
        delete[]Graph[j];
    }

    return 0;
}
