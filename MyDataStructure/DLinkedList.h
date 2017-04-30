//
// Created by 杜臻 on 2017/4/4.
//

#ifndef MYDATASTRUCTURE_DLINKEDLIST_H
#define MYDATASTRUCTURE_DLINKEDLIST_H

#include <iostream>


using namespace std;

template<class T>
class DLinkedItem;

template<class T>
class DLinkedList {
public:
    DLinkedList();

    void goLeft();

    void goRight();

    void addLeft(T element);

    void addRight(T element);

    T deleteItem();

    //让遍历链表的指针回到一开始的位置
    void toFirst();

    //打印整个链表
    void printLinkedList();

    //打印链表当前位置的值
    void printNowItem();

    ~DLinkedList();

private:
    //指向头结点（空节点）的指针
    DLinkedItem<T> *first;
    //链表当前指向的位置
    DLinkedItem<T> *now;
    //为了方便双向链表是不是空白的判断，我们还是使用一个变量来记录链表的长度。
    int length;
};


template<class T>
DLinkedList<T>::DLinkedList() {
    //这里我们进行初始化的操作
    //首先我们新建空白头结点
    first = new DLinkedItem<T>();
    //头结点的左右指针全部指向自己
    first->left = first;
    first->right = first;
    first->content = 0;
    now = first;
    length = 0;
}

template<class T>
void DLinkedList<T>::goRight() {
    //就是往右边走一个
    if (length == 0) {
        //现在链表还是空的
        cout << "现在链表还是空的，不要进行这些操作" << endl;
        return;
    }
    now = now->right;
}

template<class T>
void DLinkedList<T>::goLeft() {
    //就是往右边走一个
    if (length == 0) {
        //现在链表还是空的
        cout << "现在链表还是空的，不要进行这些操作" << endl;
        return;
    }
    now = now->left;
}

template<class T>
void DLinkedList<T>::addLeft(T element) {
    //我们在当前节点的左侧添加一个节点我们首先需要先获取当前左侧的节点
    DLinkedItem<T> *lastLeft = now->left;
    //然后创建一个要添加的节点对象
    DLinkedItem<T> *addItem = new DLinkedItem<T>();
    addItem->left = lastLeft;
    addItem->right = now;
    addItem->content = element;
    now->left = addItem;
    lastLeft->right = lastLeft;
    length++;
}

template<class T>
void DLinkedList<T>::addRight(T element) {

    DLinkedItem<T> *lastRight = now->right;

    DLinkedItem<T> *addItem = new DLinkedItem<T>();

    addItem->right = lastRight;
    addItem->left = now;
    addItem->content = element;

    now->right = addItem;

    lastRight->left = addItem;

    length++;
}

template<class T>
void DLinkedList<T>::toFirst() {
    now = first;
}

template<class T>
T DLinkedList<T>::deleteItem() {
    //首先看看当前有多少个链表元素
    if (length == 0) {
        cout << "现在没有元素可以用来删除" << endl;
        return NULL;
    }

    if (now == first) {
        cout << "当前节点是first节点，不能删除" << endl;
        return NULL;
    }


    //这个函数用来删除当前元素
    DLinkedItem<T> *nowLeft = now->left;
    DLinkedItem<T> *nowRight = now->right;

    //现在删除当前元素并返回
    T returnContent = now->content;

    //重新构建指针
    nowLeft->right = nowRight;
    nowRight->left = nowLeft;

    delete now;
    length--;

    //析构完成后，统一指向右边的节点
    now = nowRight;

    return returnContent;
}

template<class T>
void DLinkedList<T>::printLinkedList() {
    if (length == 0) {
        cout << "现在链表是空的，不能打印" << endl;
        return;
    }


    //先声明遍历链表的指针
    DLinkedItem<T> *nowItem = first->right;
    //然后我们向右遍历整个链表，直到回到first为止
    while (nowItem != first) {
        cout << nowItem->content << " , ";
        nowItem = nowItem->right;
    }

    cout << endl;
}

template<class T>
DLinkedList<T>::~DLinkedList() {
    //这里我们析构掉所有的绩点
    now = first->right;
    for (int i = 0; i < length - 1; ++i) {
        deleteItem();
    }
}

template <class T>
void DLinkedList<T>::printNowItem() {
    if (now == first){
        cout << "这个是头结点，不能打印" <<endl;
        return;
    }

    cout << now->content <<endl;
}


template<class T>
class DLinkedItem {
//设定链表元素的友元，
    friend class DLinkedList<T>;

public:
    void printItem();

private:
    T content;
    DLinkedItem<T> *left;
    DLinkedItem<T> *right;
};

template<class T>
void DLinkedItem<T>::printItem() {
    cout << content << endl;
}


#endif //MYDATASTRUCTURE_DLINKEDLIST_H
