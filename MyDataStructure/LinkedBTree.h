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
