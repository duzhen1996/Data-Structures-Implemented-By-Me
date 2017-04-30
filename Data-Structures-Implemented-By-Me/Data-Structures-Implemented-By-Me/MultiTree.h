//
// Created by 杜臻 on 2017/4/18.
//

#ifndef MYDATASTRUCTURE_MULTITREE_H
#define MYDATASTRUCTURE_MULTITREE_H

#include <iostream>
#include "Queue.h"

using namespace std;


//这里我们实现一个不限制叉树的多叉树，左子右兄弟
template<class T>
class MultiTreeNode;

template<class T>
class MultiTree {
public:
    //构造函数
    MultiTree(T rootContent);

    //往儿子方向走
    void goChild();

    //往兄弟方向走
    void goBrother();

    //获取当前节点的内容
    T getContent();

    //添加子节点，形参为为添加的内容，以及要添加在第几个儿子后面
    void addChild(T content, int position);

    void goParent();

    //删除第n个子节点
    T delChild(int n);

    //析构函数
    ~MultiTree();

private:
    //根节点
    MultiTreeNode<T> *root;
    //用来遍历树的指针
    MultiTreeNode<T> *now;
};


template<class T>
MultiTree<T>::MultiTree(T rootContent) {
    //首先创造一个根对象
    root = new MultiTreeNode<T>();
    //设置跟对象的成员
    root->content = rootContent;
    root->parent = 0;
    root->child = 0;
    root->brother = 0;
    now = root;
}

template<class T>
void MultiTree<T>::goChild() {
    //我们向子节点移动
    if (now->child != 0) {
        now = now->child;
    }
}

template<class T>
void MultiTree<T>::goBrother() {
    //向兄弟节点移动
    if (now->brother != 0) {
        now = now->brother;
    }
}


template<class T>
T MultiTree<T>::getContent() {
    return now->content;
}

template<class T>
void MultiTree<T>::addChild(T content, int position) {
    //我们为一个节点添加儿子
    //我们首先添加一个指针，这个添加一个儿子
    //如果position的值远超过儿子的数量，那就直接加在最后一个儿子尾部
    //首先找到那个指向新节点的指针
    MultiTreeNode<T> *scanPtr = now->child;
    MultiTreeNode<T> *history = now;
    int nowPos = 1;
    //在没到最后一个节点以及没有到固定
    while (scanPtr != 0 && nowPos != position) {
        history = scanPtr;
        scanPtr = scanPtr->brother;
        nowPos++;
    }
    //这里已经到达了指定位置
    //我们在指定位置插入元素
    //也就是插在scanPtr的前面
    //创建目标元素
    MultiTreeNode<T> *newPtr = new MultiTreeNode<T>();
    newPtr->content = content;
    newPtr->parent = now;
    newPtr->brother = scanPtr;
    newPtr->child = 0;

    //第一个元素特殊处理
    if (position == 1) {
        history->child = newPtr;
    } else {
        history->brother = newPtr;
    }
}

template<class T>
void MultiTree<T>::goParent() {
    //有父节点才往父节点跳
    if (now->parent != 0) {
        now = now->parent;
    }
}

template<class T>
T MultiTree<T>::delChild(int n) {

    //我们首先找到我们想要的子节点。
    MultiTreeNode<T> *scanPtr = now->child;
    int nowPosition = 1;

    //为了可以更好地解决插入问题，我们引入一个history指针，放在扫描节点的前面
    MultiTreeNode<T> *history = now;

    while (nowPosition != n) {
        //首先查看当前节点的下一个节点是不是空的
        //如果是空的，那就说明已经顶到头了
        if (scanPtr->brother == 0) {
            //已经到头了
            cout << "不存在这个节点" << endl;
            return NULL;
        } else {
            //如果没有到头，那就扫描节点向后走一个
            history = scanPtr;
            scanPtr = scanPtr->brother;
            nowPosition++;
        }
    }

    //到了这里的时候，scanPtr指针所指的位置就是我们要删除元素的位置
    T returnValue = scanPtr->content;
    //如果是第一个节点
    if (n == 1) {
        history->child = scanPtr->brother;
        delete scanPtr;
    } else {
        //如果不是第一个节点，就改变前溯节点的brother指针
        history->brother = scanPtr->brother;
        delete scanPtr;
    }

    return returnValue;
}


template<class T>
MultiTree<T>::~MultiTree() {
    //我们使用广度优先搜索来解决整个树的析构的问题
    //我们创造一个队列来放置要析构的数节点
    Queue<MultiTreeNode<T> *> *delQueue = new Queue<MultiTreeNode<T> *>(20);

    //然后我们把根节点放在队列中
    delQueue->add(root);

    cout << "析构函数运行" << endl;

    //然后进行删除操作，直到队列为空为止
    while (!delQueue->IsEmpty()) {
        //准备删除头部节点，在删除头部节点之前要把头部节点的子节点放进来
        //先加入子节点
        //首先获取要删除的节点
        MultiTreeNode<T> *delNode = *(delQueue->Delete());
        //看看有没有要入队的子节点
        if (delNode->child != 0) {
            //这里添加一个节点
            MultiTreeNode<T> *childnode = delNode->child;
            while (childnode != 0) {
                delQueue->add(childnode);
                childnode = childnode->brother;
            }
        }
        //这里删除父节点
        cout << "析构节点内容：" << delNode->content << endl;
        delete delNode;
    }

    delete delQueue;
}


template<class T>
class MultiTreeNode {
    friend class MultiTree<T>;

private:
    //父节点
    MultiTreeNode<T> *parent;
    MultiTreeNode<T> *brother;
    MultiTreeNode<T> *child;
    T content;
};


#endif //MYDATASTRUCTURE_MULTITREE_H
