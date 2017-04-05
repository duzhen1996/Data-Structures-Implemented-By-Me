//
// Created by 杜臻 on 2017/4/5.
//

#ifndef MYDATASTRUCTURE_BINARYTREE_H
#define MYDATASTRUCTURE_BINARYTREE_H

#include <iostream>

using namespace std;

template<class T>
class BinaryTree {
public:
    //通过定义根部的节点来初始化
    BinaryTree(T rootContent);

    //让nowIndex回到树的根部
    void toRoot();

    //向当前节点的左节点移动
    void goLeftChild();

    //向当前节点的右节点移动
    void goRightChild();

    //获取当前节点值
    T getElementValue();

    //向左节点修改或者添加一个值
    void editLeft(T content);

    //向右节点添加一个值
    void editRight(T content);

    //以rootIndex为根的子树删除
    void delChildTree(int rootIndex);

    int getNowIndex();

    T *getTreeContentPtr();

    ~BinaryTree();

private:
    //我们会提供一个索引来对这个树的内容进行遍历和查询操作
    int nowIndex;
    //我们用一个数组来进行二叉树的内容的存储
    T *treeContent;
};

template<class T>
BinaryTree<T>::BinaryTree(T rootContent) {
    nowIndex = 1;
    treeContent = new T[256];//我们保证可以进行最少八层二叉树的存储。
    for (int i = 0; i < 256 ; ++i) {
        treeContent[i] = -1;
    }

    treeContent[1] = rootContent;
}

template<class T>
void BinaryTree<T>::toRoot() {
    nowIndex = 1;
}

template<class T>
void BinaryTree<T>::goLeftChild() {
    if (nowIndex * 2 >= 256) {
        cout << "访问的位置超过了给树预留的空间" << endl;
        return;
    } else if (treeContent[nowIndex * 2] == -1) {
        cout << "要访问的位置空的" << endl;
    } else {
        nowIndex = nowIndex * 2;
    }
}

template<class T>
void BinaryTree<T>::goRightChild() {
    if (nowIndex * 2 + 1 >= 256) {
        cout << "访问的位置超过了给树预留的空间" << endl;
        return;
    } else if (treeContent[nowIndex * 2 + 1] == -1) {
        cout << "要访问的位置空的" << endl;
    } else {
        nowIndex = nowIndex * 2 + 1;
    }
}

template<class T>
void BinaryTree<T>::editLeft(T content) {
    if (nowIndex * 2 >= 256) {
        cout << "访问的位置超过了给树预留的空间" << endl;
        return;
    } else {
        treeContent[nowIndex * 2] = content;
    }
}

template<class T>
void BinaryTree<T>::editRight(T content) {
    if (nowIndex * 2 + 1 >= 256) {
        cout << "访问的位置超过了给树预留的空间" << endl;
        return;
    } else {
        treeContent[nowIndex * 2 + 1] = content;
    }
}

template<class T>
BinaryTree<T>::~BinaryTree() {
    delete[] treeContent;
}

template<class T>
T BinaryTree<T>::getElementValue() {
    //获取当前节点的值
    return treeContent[nowIndex];
}


template<class T>
void BinaryTree<T>::delChildTree(int rootIndex) {
    //首先先删除根节点
    treeContent[rootIndex] = -1;
    //然后删除左右子树
    //看看左子树有没有内容
    int rightIndex = rootIndex * 2 + 1;
    int leftIndex = rootIndex * 2;
    if (rightIndex < 256 && treeContent[rightIndex] != -1) {
        //到达这里说明右子树有东西，需要删除右子树
        delChildTree(rightIndex);
    }
    if (leftIndex < 256 && treeContent[leftIndex] != -1) {
        delChildTree(leftIndex);
    }
}

template<class T>
int BinaryTree<T>::getNowIndex() {
    return nowIndex;
}

template<class T>
T *BinaryTree<T>::getTreeContentPtr() {
    return treeContent;
}


#endif //MYDATASTRUCTURE_BINARYTREE_H
