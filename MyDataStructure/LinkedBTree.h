//
// Created by 杜臻 on 2017/4/7.
//

#ifndef MYDATASTRUCTURE_LINKEDBTREE_H
#define MYDATASTRUCTURE_LINKEDBTREE_H

#include <iostream>
#include "Queue.h"


using namespace std;

template<class T>
class LinkedBItem;

//二叉树的链表实现
template<class T>
class LinkedBTree {
public:
    LinkedBTree(T rootValue);

    //下一个函数就是移动now指针的
    void goLeft();

    void goRight();

    void addLeft(T value);

    void addRight(T value);

    void editNow(T value);

    //删除当前now指针指向的节点，这会导致一个级联删除
    T deleteNow();

    //回到根节点
    void toRoot();

    //获取now指针所指向节点的值
    T readNow();

    //后序遍历
    void post_order();

    ~LinkedBTree();

private:
    LinkedBItem<T> *root;
    LinkedBItem<T> *now;
};

template<class T>
LinkedBTree<T>::LinkedBTree(T rootValue) {

    root = new LinkedBItem<T>();

    root->element = rootValue;
    root->right = 0;
    root->left = 0;

    now = root;
}

template<class T>
void LinkedBTree<T>::addLeft(T value) {
    if (now->left != 0) {
        cout << "左节点已经有东西了" << endl;
        return;
    }


    //创建新的节点
    now->left = new LinkedBItem<T>();
    now->left->element = value;
    now->left->right = 0;
    now->left->left = 0;
}

template<class T>
void LinkedBTree<T>::addRight(T value) {
    if (now->right != 0) {
        cout << "右节点已经有东西了" << endl;
        return;
    }

    //创建新节点
    now->right = new LinkedBItem<T>();
    now->right->element = value;
    now->right->right = 0;
    now->right->left = 0;
}

template<class T>
void LinkedBTree<T>::goLeft() {
    if (now->left == 0) {
        cout << "没有左子节点" << endl;
        return;
    }

    now = now->left;
}

template<class T>
void LinkedBTree<T>::goRight() {
    if (now->right == 0) {
        cout << "没有右节点" << endl;
        return;
    }

    now = now->right;
}

template<class T>
void LinkedBTree<T>::editNow(T value) {
    now->element = value;
}

template<class T>
T LinkedBTree<T>::deleteNow() {
    T returnValue = now->element;

    delete now;

    toRoot();

    return returnValue;

}

template<class T>
void LinkedBTree<T>::toRoot() {
    now = root;
}

template<class T>
T LinkedBTree<T>::readNow() {

    return now->element;
}

template<class T>
LinkedBTree<T>::~LinkedBTree() {
    //利用广度优先搜索来进行析构操作，广度优先搜索的实现需要使用环状队列
    Queue<LinkedBItem<T> *> *deleteQueue = new Queue<LinkedBItem<T> *>(100);

    //进行广度优先遍历，将二叉树的要delete的节点放在队列中。
    now = root;

    //一开始先把节点放在头部
    deleteQueue->add(root);

    while (!deleteQueue->IsEmpty()) {
        //拿出要删除的元素
        LinkedBItem<T> *delItem = *(deleteQueue->Delete());
        //将要删除元素的左右节点加入到队列中（如果不为空）
        if (delItem->left != 0) {
            deleteQueue->add(delItem->left);
        }
        if (delItem->right != 0) {
            deleteQueue->add(delItem->right);
        }

        delete delItem;
    }


    //析构队列
    delete deleteQueue;
}

template<class T>
void LinkedBTree<T>::post_order() {
    //我们进行后序遍历，首先创建一个栈空间。
    //栈空间存放树的节点
    now = root;
    LinkedBItem<T> **stack = new LinkedBItem<T> *[100];
    //索引从-1开始，指向当前的栈顶
    int stackIndex = -1;
    //我们建立一个数组，主要是为了查看栈中节点的有没有右子树需要遍历，如果已经被遍历了，那就可以安心弹栈，如果没有被遍历
    //那就只能只能再把右节点压栈。压栈是一个"正反馈"的过程，一旦出现了压栈，那就会一压到底，不断向左节点走，直到不能再压
    //一旦压到不能再压，那就会进入弹栈程序，弹栈主要做的就是检查当前节点的右子树。
    int *hasScanRight = new int[100];

    //初始化数组
    for (int i = 0; i < 100; ++i) {
        hasScanRight[i] = 0;
    }


    //首先我们先让根节点入栈，然后触发"入栈正反馈"，直到now是空指针为止
    stack[++stackIndex] = root;

    if (root->right != 0) {
        hasScanRight[stackIndex] = 1;
    }

    while (stackIndex != -1) {
        now = stack[stackIndex];

        while (now->left != 0) {
            stack[++stackIndex] = now->left;
            //入栈之后查看右节点的情况，然后修改那个查看右子树是不是已经被遍历的数组
            if (stack[stackIndex]->right != 0) {
                hasScanRight[stackIndex] = 1;
            }

            now = now->left;
        }

        //当完成"入栈正反馈"之后，我们就可以弹栈过程，弹栈的时候我们就可以看看是不是右子树有没有东西
        while (stackIndex != -1 && hasScanRight[stackIndex] == 0) {
            //如果右子树没有东西，那就进入正常的弹栈过程，弹栈也是一个正反馈过程如果，如果一直右子树没有东西，就可以一直弹
            cout << stack[stackIndex]->element << " , ";
            stackIndex--;
        }

        //从这个while中出来有两种情况，一种就是发现右子树还在的，一种就是stack已经空了
        if (hasScanRight[stackIndex] == 1) {
            //如果右子树有东西，那么我们就要进行新一轮的压栈操作，压栈的之后还要看看新入栈的节点有没有右子树
            stack[stackIndex + 1] = stack[stackIndex]->right;

            //右节点已经入栈，修改hasScanRight数组
            hasScanRight[stackIndex] = 0;
            stackIndex++;

            if (stack[stackIndex]->right != NULL) {
                hasScanRight[stackIndex] = 1;
            }
        }
    }

    cout << endl;
    //析构申请的资源
    delete[]stack;

    delete[]hasScanRight;
}


//二叉树中每一个节点的结构
template<class T>
class LinkedBItem {
    friend class LinkedBTree<T>;

private:
    //每个节点分别是左子树和右子树的指针
    LinkedBItem<T> *left;
    LinkedBItem<T> *right;
    T element;
};


#endif //MYDATASTRUCTURE_LINKEDBTREE_H
