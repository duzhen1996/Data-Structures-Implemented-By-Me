//
// Created by 杜臻 on 2017/5/16.
//

#ifndef MYDATASTRUCTURE_GRAPH_H
#define MYDATASTRUCTURE_GRAPH_H

#include <iostream>
#include <deque>

using namespace std;

class GraphItem;

//我们使用邻接表来实现一个图
//我们对图进行这样的设计，图中的每一个节点里面都包含一个数字作为节点的编号
//而统一使用有向图
class Graph {
public:
    Graph(int size);


    //为节点添加一条边，形参分别是边的起点和终点
    void insert(int start, int end);

    //这里进行图的邻接表的打印
    friend ostream &operator<<(ostream &out, const Graph *graph);

    //这里是广度优先遍历，我们传入多个数组，分别存放每一个节点与源节点之间的距离
    //并且存放每个节点在广度优先树之前的父节点，这都是为了方便得到最短路径

    //第1个形参是起始节点编号
    //第2个形参是一个数组，存的是每个节点的父节点编号
    //第3个形参是一个数组，存的是每个节点与起始节点之间的距离
    void BSF(int start, int *&parent, int *&length);

    //这里是深度优先遍历，我们设定两个同名函数来进行重载，这个是驱动函数
    void DSF(int *&parent, int *&inTime, int *&outTime);

    //这个是真正参与递归的函数
    void DSF(int start, int *parent, int *inTime, int *outTime, int *color, int &time);

    int getGraphSize() const;

private:
    //这里维护两个变量，一个是Graph节点的数量，一个是一个线性表
    GraphItem **itemArr;
    //节点数量
    int graphSize;
};


//设计一个类作为图的节点，主要就是作为线性表后面的链表而存在
class GraphItem {
    friend class Graph;

    //这里进行图的邻接表的打印
    friend ostream &operator<<(ostream &out, const Graph *graph);

public:
    GraphItem(GraphItem *next, int itemCode);

private:
    GraphItem *next;
    int itemCode;
};


#endif //MYDATASTRUCTURE_GRAPH_H
