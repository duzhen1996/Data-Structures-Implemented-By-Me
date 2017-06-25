//
// Created by 杜臻 on 2017/6/25.
//

#ifndef MYDATASTRUCTURE_DIJKSTRA_H
#define MYDATASTRUCTURE_DIJKSTRA_H

#include <iostream>

using namespace std;
//使用最大值来代表不连通的点，在邻接矩阵和好dist中表达不可达边和初始化数据
const int MAX_INT = 32767;

//传入形参包括dist，int数组，用来存储最短路径
//Graph，是一个二维邻接矩阵，用来存储一个有向带权图的
//prev前趋节点数组的指针，这个是用来找出最短路径的
//itemCount是点的数量
//start是源节点编号
void Dijkstra(int *dist, int **Graph, int *prev, int itemCount, int start) {
    //已经找到最短路径的节点会在这个数据里记录一个true
    bool *S = new bool[itemCount];
    //已经是true的节点计数
    int alreadyJoin = 0;

    //首先我们进行初始化
    //在初始化的时候源节点以及源节点的周边节点就已经顺道弄好了
    for (int i = 0; i < itemCount; ++i) {
        //我们顺便把与源节点相邻的节点dist更新好
        //找出与源节点相邻的节点
        if (Graph[start][i] != MAX_INT) {
            dist[i] = Graph[start][i];
            //暂时写入prev
            prev[i] = start;
        } else {
            //如果不相邻那就是使用最大int值
            dist[i] = MAX_INT;
            prev[i] = -1;
        }
        S[i] = false;

    }

    //初始化源节点
    S[start] = true;
    dist[start] = 0;
    alreadyJoin++;

//    for (int k = 0; k < itemCount; ++k) {
//        cout << dist[k] << endl;
//    }

    //直到所有节点都已经加入S集合了，这个过程就会停止
    //我们整个过程就是，不断从S的邻接节点中找到和源节点距离最近的节点，然后将这个新节点加入S，并且更新
    //和这个新加入节点的邻居节点的dist
    while (alreadyJoin != itemCount) {
        //找出与S集合相邻的节点中和源节点最近的节点
        //两个过程变量，分别找到距离的最小值和距离最小的节点
        int minDist = MAX_INT;
        int minItem = -1;
        for (int j = 0; j < itemCount; ++j) {
            if (!S[j] && dist[j] < minDist) {
                minItem = j;
                minDist = dist[j];
            }
        }

        //经过上面的过程，minItem存储了要加入S集合的节点编号，如果没有要加入的，说明实际上图中有
        //源节点的不可达节点，那么整个最短路径的寻找就可以停止了
        if (minItem == -1) {
            break;
        }
        S[minItem] = true;
        alreadyJoin++;

        //之后遍历所有的minItem不在S集合内的直接相邻节点，进行relax操作并且在需要relax的节点上修改prev
        for (int i = 0; i < itemCount; ++i) {
            if (!S[i] && Graph[minItem][i] != MAX_INT && (dist[i] > dist[minItem] + Graph[minItem][i])) {
                //这里说明在新的路径上单源路径更短
                dist[i] = dist[minItem] + Graph[minItem][i];
                //暂时更新prev
                prev[i] = minItem;
            }
        }
    }

    delete[]S;
}

#endif //MYDATASTRUCTURE_DIJKSTRA_H
