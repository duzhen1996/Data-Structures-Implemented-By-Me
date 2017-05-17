//
// Created by 杜臻 on 2017/5/16.
//

#include "Graph.h"
#include <iostream>

using namespace std;

GraphItem::GraphItem(GraphItem *next, int itemCode) : next(next), itemCode(itemCode) {}

Graph::Graph(int size) {
    graphSize = size;
    itemArr = new GraphItem *[size];
    //置为空指针
    for (int i = 0; i < graphSize; ++i) {
        itemArr[i] = 0;
    }
}

void Graph::insert(int start, int end) {

    if (start > graphSize - 1 || end > graphSize - 1) {
        cout << "节点不在图中" << endl;
        return;
    }

    //在start后面插入节点，这里声明指针的引用才能真正改到对应节点的指针
    GraphItem *insertPtr = itemArr[start];

    if (insertPtr == 0) {
        itemArr[start] = new GraphItem(0, end);
        return;
    }

    while (insertPtr->next != 0) {
        insertPtr = insertPtr->next;
    }

    //插入
    insertPtr->next = new GraphItem(0, end);
}

//在函数的形参里使用const是一种搞笑的行为，因为是拷贝传值+强制const类型转化，只能约束里面
ostream &operator<<(ostream &out, const Graph *graph) {
    //这里我们进行打印
    for (int i = 0; i < graph->graphSize; ++i) {
        //一行一行打印
        out << "起点 " << i;
        out << "     终点:";

        //遍历链表的指针
        GraphItem *scan = graph->itemArr[i];

        while (scan != 0) {
            //打印
            cout << scan->itemCode << " , ";
            //移动
            scan = scan->next;
        }

        cout << endl;
    }

    return out;
}

void Graph::BSF(int start, int *&parent, int *&length) {
    //我们还有一个不需要传到外面的数组，就是节点的颜色问题
    //这个是必须的
    //0为白色，1为灰色，2为黑色
    int *color = new int[graphSize];

    //初始化成白色
    for (int i = 0; i < graphSize; ++i) {
        color[i] = 0;
    }

    //然后为parent和length创建数组
    parent = new int[graphSize];

    //一开始全部初始为-1
    for (int i = 0; i < graphSize; ++i) {
        parent[i] = -1;
    }

    length = new int[graphSize];

    for (int j = 0; j < graphSize; ++j) {
        length[j] = -1;
    }

    //创建队列
    deque<int> *search_deque = new deque<int>();

    //首先将start的parent置为-1，代表没有父节点
    parent[start] = -1;
    length[start] = 0;

    //然后我们将广度优先搜索的根节点置为黑色，并且放入队列
    color[start] = 1;
    search_deque->push_back(start);

    //开始循环，当队列为空的时候发现遍历已经结束
    while (!search_deque->empty()) {
        //将头部节点弹出，然后将头部节点的白色子节点放到队列中
        int top = search_deque->front();
        search_deque->pop_front();

        //找到头部节点的白色子节点
        GraphItem *scan = itemArr[top];

        //遍历头部节点的所有子节点
        while (scan != 0) {
            //白色子节点入队
            //入队之前设定parent数组和length数组
            if (color[scan->itemCode] == 0) {
                parent[scan->itemCode] = top;
                length[scan->itemCode] = length[top] + 1;
                //主要要改颜色
                color[scan->itemCode] = 1;

                //入队
                search_deque->push_back(scan->itemCode);
            }

            scan = scan->next;
        }
        //打印一下遍历完的节点
        cout << top << endl;
        //弹出的节点变成黑色
        color[top] = 2;
    }



    //析构
    delete[]color;
}

int Graph::getGraphSize() const {
    return graphSize;
}
