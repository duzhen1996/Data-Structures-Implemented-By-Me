//
// Created by 杜臻 on 2017/5/19.
//

#ifndef MYDATASTRUCTURE_KRUSKAL_H
#define MYDATASTRUCTURE_KRUSKAL_H

#include "Graph.h"
#include <iostream>

//我们把边做出来
class KruskalEdge {
public:
    //插入数据分别是图的两个端点的编号
    KruskalEdge(int v, int u, int cost) {
        this->u = u;
        this->v = v;
        this->cost = cost;
    }

    //重载等号运算符，因为是无向边
    bool operator==(const KruskalEdge otherEage) {
//        cout << "进入比较函数" << endl;
        if (this->u == otherEage.u && this->v == otherEage.v) {
            return true;
        }
        if (this->u == otherEage.v && this->v == otherEage.u) {
            return true;
        }

        return false;
    }

    //重载打印运算
    friend ostream &operator<<(ostream &out, const KruskalEdge *edge);

    friend Graph *Kruskal(Graph *inputGraph);

private:
    int v;
    int u;
    int cost;
};

//Kruskal最小生成树算法
//返回边的集合，边是一种新的对象，最后我们可以将这些边的集合重新构造成一个图
//最后返回的是一个图，但是这个图实际上是一个最小代价生成树。
Graph *Kruskal(Graph *inputGraph) {
    //创建一个边的集合
    //集合的大小尽可能大
    KruskalEdge **edgeTree = new KruskalEdge *[1000];
    //集合的最大有效索引
    int edgeTreeValid = -1;
    //这个数组记录节点颜色，黑色代表顶点已经在树中，如果两个顶点已经都是黑色，那么这两个
    //顶点对应的边就不能加入集合
    //0为白色，2为黑色
    int *color = new int[inputGraph->getGraphSize()];

    for (int i = 0; i < inputGraph->getGraphSize(); ++i) {
        color[i] = 0;
    }

    KruskalEdge **edgeMin2Max = new KruskalEdge *[1000];
    int edgeMin2MaxValid = -1;

    //首先我们将所有的边从图中拿出来，放到一个数组中，并且去做一个从小到大的排序
    for (int j = 0; j < inputGraph->getGraphSize(); ++j) {
        //从树中拿一个节点出来
        GraphItem *scan = inputGraph->itemArr[j];
        while (scan != 0) {
            //我们在edgeMin2Max数组中进行插入排序
            //默认插入在尾部
            int insertPosition = edgeMin2MaxValid + 1;
            for (int i = edgeMin2MaxValid; i >= 0; --i) {
                //我们不断向后挪动，为插入的节点腾出位置
                if (scan->cost < edgeMin2Max[i]->cost) {
                    //向后挪动
                    edgeMin2Max[i + 1] = edgeMin2Max[i];
                    //插入位置更新
                    insertPosition = i;
                } else {
                    //如果发现插入排序的数组的节点已经比要插入的节点小的，那就不应挪动就好了
                    break;
                }
            }
            //这里进行插入
            edgeMin2Max[insertPosition] = new KruskalEdge(j, scan->itemCode, scan->cost);
            edgeMin2MaxValid++;
            scan = scan->next;
        }
    }
    cout << "打印所有的节点" << endl;
    //这里是将所有边整理成从小到大的数组了，我们打印一下整理之后的内容
    for (int k = 0; k <= edgeMin2MaxValid; ++k) {
        cout << edgeMin2Max[k] << endl;
    }
    cout << "打印完毕" << endl;

    //这个时候我们从小到大将插入排序的数组中按顺序将节点一点点加入最小生成树集合
    for (int l = 0; l <= edgeMin2MaxValid; ++l) {
        //首先先判重
        //一个判断能不能进行将边加入最小生成树
        cout << l << endl;
        bool judgeTree = true;
        for (int i = 0; i <= edgeTreeValid; ++i) {

//            cout << edgeMin2Max[l] << " , " << edgeTree[i] << endl;

            if (*edgeMin2Max[l] == *edgeTree[i]) {
                //这说明两条边是一样的，因为是无向连通图
                //不需要插入
                judgeTree = false;
                break;
            }
        }

        if (judgeTree == false) {
            //已经不需要加入最小生成树了
//            cout << "不需要加入" << endl;
            continue;
        }

        //然后根据节点颜色看看会不会构成环
        if (color[edgeMin2Max[l]->u] == 2 && color[edgeMin2Max[l]->v] == 2) {
            continue;
        }

        //这里说明当前的边可以加入最小生成树
        edgeTreeValid++;
        edgeTree[edgeTreeValid] = edgeMin2Max[l];
        color[edgeTree[edgeTreeValid]->v] = 2;
        color[edgeTree[edgeTreeValid]->u] = 2;
    }

    cout << "打印所有的节点" << endl;
    //这里是将所有边整理成从小到大的数组了，我们打印一下整理之后的内容
    for (int k = 0; k <= edgeTreeValid; ++k) {
        cout << edgeTree[k] << endl;
    }
    cout << "打印完毕" << endl;

//    //重新整理图
//    Graph *returnGraph = new Graph(inputGraph->getGraphSize());
//
//    //将数组中的所有边加入新的图中
//    for (int m = 0; m <edgeTreeValid++ ; ++m) {
//
//    }
}

ostream &operator<<(ostream &out, const KruskalEdge *edge) {
    //打印
    out << " ( " << edge->u << " , " << edge->v << " , " << edge->cost << " ) ";

    return out;
}

#endif //MYDATASTRUCTURE_KRUSKAL_H
