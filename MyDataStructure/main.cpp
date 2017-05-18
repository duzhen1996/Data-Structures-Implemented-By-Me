//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "Graph.h"

using namespace std;


int main(int argc, const char *argv[]) {
    Graph *graph = new Graph(5);

    graph->insert(0, 1);
    graph->insert(0, 4);
    graph->insert(1, 0);
    graph->insert(1, 4);
    graph->insert(1, 2);
    graph->insert(1, 3);
    graph->insert(2, 1);
    graph->insert(2, 3);
    graph->insert(3, 1);
    graph->insert(3, 4);
    graph->insert(3, 2);
    graph->insert(4, 3);
    graph->insert(4, 0);
    graph->insert(4, 1);


    int *parent;

//    int *length;

    int *inTime;

    int *outTime;

    graph->DSF(parent, inTime, outTime);

//    cout << endl << "打印每个节点与根之间的距离:" << endl;
//
//    for (int i = 0; i < graph->getGraphSize(); ++i) {
//        cout << length[i] << endl;
//    }
//
//    cout << endl;


    cout << endl << "打印每个节点的父节点:" << endl;

    for (int i = 0; i < graph->getGraphSize(); ++i) {
        cout << parent[i] << endl;
    }

    cout << endl;

    cout << endl << "打印入栈时间戳:" << endl;

    for (int i = 0; i < graph->getGraphSize(); ++i) {
        cout << inTime[i] << endl;
    }

    cout << endl;

    cout << endl << "打印出栈时间戳:" << endl;

    for (int i = 0; i < graph->getGraphSize(); ++i) {
        cout << outTime[i] << endl;
    }

    cout << endl;

    cout << graph << endl;

    return 0;
}
