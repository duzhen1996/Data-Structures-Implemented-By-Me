//
// Created by 杜臻 on 2017/4/5.
//

#ifndef MYDATASTRUCTURE_BINARYTREE_H
#define MYDATASTRUCTURE_BINARYTREE_H

#include <iostream>

//二叉树的数组实现
using namespace std;

template<class T>
class BinaryTree {
public:
    //通过定义根部的节点来初始化
    BinaryTree(T rootContent);

    //让nowIndex回到树的根部
    void toRoot();

    //向当前节点的左节点移动
    void goLeft();

    //向当前节点的右节点移动
    void goRight();

    //获取当前节点值
    T getElementValue();

    //向左节点修改或者添加一个值
    void editLeft(T content);

    //向右节点添加一个值
    void editRight(T content);

    //以rootIndex为根的子树删除
    void delChildTree(int rootIndex);

    int getNowIndex();

    T readNow();

    T *getTreeContentPtr();

    //以root节点为根进行前序遍历
    void pre_order(int root);

    //以root节点为根进行后续遍历
    void post_order(int root);

    //以root节点为根节点进行中序遍历
    void in_order(int root);

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
    for (int i = 0; i < 256; ++i) {
        treeContent[i] = -1;
    }

    treeContent[1] = rootContent;
}

template<class T>
void BinaryTree<T>::toRoot() {
    nowIndex = 1;
}

template<class T>
void BinaryTree<T>::goLeft() {
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
void BinaryTree<T>::goRight() {
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
T BinaryTree<T>::readNow() {
    return getElementValue();
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

template<class T>
void BinaryTree<T>::pre_order(int root) {
    //这是一个递归算法。
    //我们首先打印根节点元素，然后再分别递归左右节点
    //设定递归完成条件
    if (root >= 256 || treeContent[root] == -1) {
        //递归退出
        return;
    }
    //打印根节点
    cout << treeContent[root] << " , ";
    //递归左节点和右节点
    pre_order(root * 2);
    pre_order(root * 2 + 1);
}

template<class T>
void BinaryTree<T>::post_order(int root) {
    //首先规定递归退出条件
    if (root >= 256 || treeContent[root] == -1) {
        return;
    }

    //先左右节点递归，然后打印根节点
    post_order(root * 2);
    post_order(root * 2 + 1);
    cout << treeContent[root] << " , ";
}

template<class T>
void BinaryTree<T>::in_order(int root) {
    //规定退出条件
    if (root >= 256 || treeContent[root] == -1) {
        return;
    }
    //中序遍历，首先递归左节点、打印根节点、递归右节点
    in_order(root * 2);
    cout << treeContent[root] << " , ";
    in_order(root * 2 + 1);
}


#endif //MYDATASTRUCTURE_BINARYTREE_H
