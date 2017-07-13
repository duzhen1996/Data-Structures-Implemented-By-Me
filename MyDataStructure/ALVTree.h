//
// Created by 杜臻 on 2017/7/11.
//

#ifndef MYDATASTRUCTURE_ALVTREE_H
#define MYDATASTRUCTURE_ALVTREE_H

#include <iostream>

using namespace std;

template<class T>
class ALVTreeItem;

//关于ALV树的实现
template<class T>
class ALVTree {
public:
    ALVTree(T rootElement);

    //插入函数，我们先像二叉树一样插入，插入使用一个对子树插入元素的递归过程
    void insert(T element);

    //对树进行打印，方便检查
    void pre_scan(ALVTreeItem<T> *item);

    ALVTreeItem<T> *getRoot() const;

    //子树左旋和右旋的函数，返回左旋和右旋之后的新根
    ALVTreeItem<T> *rightRot(ALVTreeItem<T> *subRoot);

    //左旋函数，返回新的根
    ALVTreeItem<T> *leftRot(ALVTreeItem<T> *subRoot);

    //删除函数
    void deleteItem(T element);


private:
    //删除子树的元素
    ALVTreeItem<T> *subTreeDelete(ALVTreeItem<T> *subTree, T element);

    //对子树插入元素
    ALVTreeItem<T> *subTreeInsert(ALVTreeItem<T> *subTree, T element);

    //更新子树的高度
    void updateHeight(ALVTreeItem<T> *subRoot);

    ALVTreeItem<T> *root;
};

//插入函数
template<class T>
void ALVTree<T>::insert(T element) {
    //我们首先向二叉树一样地插入，这个插入是一个递归过程
    root = subTreeInsert(root, element);
}

template<class T>
ALVTreeItem<T> *ALVTree<T>::subTreeInsert(ALVTreeItem<T> *subTree, T element) {
    cout << endl << "=========================" << endl;

    cout << "当前节点" << element << endl;

    //和当前元素做对比
    if (element < subTree->element) {
        //往左边走
        //左边没有子树了
        if (subTree->LeftTree == 0) {
            subTree->LeftTree = new ALVTreeItem<T>(0, 0, element, 0);
        } else {
            //左边还有子树，那就进行递归操作
            subTree->LeftTree = subTreeInsert(subTree->LeftTree, element);
        }
    }

    if (element > subTree->element) {
        //向右边走
        if (subTree->RightTree == 0) {
            subTree->RightTree = new ALVTreeItem<T>(0, 0, element, 0);
        } else {
            subTree->RightTree = subTreeInsert(subTree->RightTree, element);
        }
    }

    //插入完之后更新高度
    updateHeight(subTree);

    //查看有没有出现高度不一致的情况
    //看左侧的高度
    int leftHeight = 0;
    if (subTree->LeftTree == 0) {
        leftHeight = -1;
    } else {
        leftHeight = subTree->LeftTree->height;
    }

    //右侧的高度
    int rightHeight = 0;
    if (subTree->RightTree == 0) {
        rightHeight = -1;
    } else {
        rightHeight = subTree->RightTree->height;
    }

    //比较两侧的高度
    if (rightHeight - leftHeight >= 2) {
        //右侧比较高
        //看看是RR还是RL
        cout << "插入之后发现右侧比较高" << endl;
        if (element < subTree->RightTree->element) {
            cout << "RL型，在右子树执行一次右旋，然后在当前节点执行一次左旋" << endl;

            subTree->RightTree = rightRot(subTree->RightTree);
            subTree = leftRot(subTree);
        }
        if (element > subTree->RightTree->element) {
            cout << "RR型，在当前节点执行一个左旋" << endl;

            //左旋
            subTree = leftRot(subTree);
        }
    }

    if (leftHeight - rightHeight >= 2) {
        cout << "左侧比右侧高" << endl;
        if (element > subTree->LeftTree->element) {
            cout << "LR型，现在左子树进行一次左旋，然后在当前节点执行右旋" << endl;

            subTree->LeftTree = leftRot(subTree->LeftTree);
            subTree = rightRot(subTree);
        }

        if (element < subTree->LeftTree->element) {
            cout << "LL型，在当前节点执行右旋" << endl;

            subTree = rightRot(subTree);
        }
    }

    //因为旋转之后已经更新的高度，应该不用管了。
    return subTree;

}


template<class T>
ALVTreeItem<T> *ALVTree<T>::leftRot(ALVTreeItem<T> *subRoot) {
    ALVTreeItem<T> *root = subRoot;
    ALVTreeItem<T> *rightTree = subRoot->RightTree;
    ALVTreeItem<T> *rightLeftTree = subRoot->RightTree->LeftTree;

    //这里做旋转操作
    subRoot = rightTree;
    subRoot->LeftTree = root;
    subRoot->LeftTree->RightTree = rightLeftTree;

    //这里进行高度的更新操作
    updateHeight(subRoot->LeftTree);
    updateHeight(subRoot);

    return subRoot;
}

template<class T>
void ALVTree<T>::updateHeight(ALVTreeItem<T> *subRoot) {
    //高度更新
    if (subRoot->LeftTree != 0 && subRoot->RightTree != 0) {
        //这里处理同时有左子树和右子树的情况
        subRoot->height = subRoot->LeftTree->height;

        if (subRoot->height < subRoot->RightTree->height) {
            subRoot->height = subRoot->RightTree->height;
        }
    } else if (subRoot->LeftTree != 0 && subRoot->RightTree == 0) {
        //这里处理只有左子树的情况
        subRoot->height = subRoot->LeftTree->height;
    } else if (subRoot->LeftTree == 0 && subRoot->RightTree != 0) {
        //只有右子树
        subRoot->height = subRoot->RightTree->height;
    } else {
        //两个子树都没有
        subRoot->height = -1;
    }

    //比子树高一层
    subRoot->height++;
}


template<class T>
ALVTreeItem<T> *ALVTree<T>::rightRot(ALVTreeItem<T> *subRoot) {
    //先进行树型的变化
    //主要就是修改这三个位置
    ALVTreeItem<T> *root = subRoot;
    ALVTreeItem<T> *leftTree = subRoot->LeftTree;
    ALVTreeItem<T> *leftRightTree = subRoot->LeftTree->RightTree;

    subRoot = leftTree;
    subRoot->RightTree = root;
    subRoot->RightTree->LeftTree = leftRightTree;

//    cout << subRoot->element << endl;

    //修改height，这里我们就修改子树的height，但是实际上一路向上的所有节点的height都要解决，我们不在这个函数里面处理
    //subRoot和subRoot->Right两个节点的height要修改
    //从下到上进行修改
    updateHeight(subRoot->RightTree);

//    cout << subRoot->RightTree->height << endl;

    updateHeight(subRoot);



    //因为高度的检查是从插入点一路向上的，我们在每次检查前都要更新一下当前节点height
    return subRoot;
}

template<class T>
ALVTree<T>::ALVTree(T rootElement) {
    root = new ALVTreeItem<T>(0, 0, rootElement, 0);
}

template<class T>
void ALVTree<T>::pre_scan(ALVTreeItem<T> *item) {
    if (item != 0) {
        cout << "(" << item->element << " , " << item->height << ")";
        pre_scan(item->LeftTree);
        pre_scan(item->RightTree);
    }
}

template<class T>
ALVTreeItem<T> *ALVTree<T>::getRoot() const {
    return root;
}

template<class T>
void ALVTree<T>::deleteItem(T element) {
    //调用从根开始进行的删除

    if (element == root->element && root->LeftTree == 0 && root->RightTree == 0) {
        delete root;
        //所有节点都已经删除了
        cout << "已删除全部节点" << endl;
        root = 0;
        delete this;
    } else {
        root = subTreeDelete(root, element);
    }

    //如果只剩下一个根节点，那就可以不用进行递归了，直接这个树析构掉

}

template<class T>
ALVTreeItem<T> *ALVTree<T>::subTreeDelete(ALVTreeItem<T> *subTree, T element) {
    //首先按照删除二叉查找树的方式删除节点
    if (element < subTree->element) {
        //要删除的东西在左子树
        //如果左子树没有东西，那就说明这个东西找不到了
        if (subTree->LeftTree == 0) {
            cout << "没有找到了" << endl;
        } else {
            //有左子树就要向左子树搜寻
            subTree->LeftTree = subTreeDelete(subTree->LeftTree, element);
        }
    } else if (element > subTree->element) {
        //要删除的是右子树
        if (subTree->RightTree == 0) {
            cout << "没有找到" << endl;
        } else {
            subTree->RightTree = subTreeDelete(subTree->RightTree, element);

        }
    } else if (element == subTree->element) {
        //删除当前节点
        //如果当前节点是叶子节点，那就直接删除
        if (subTree->RightTree == 0 && subTree->LeftTree == 0) {
            cout << "在叶子节点上面发现元素，直接删除" << subTree->element << endl;
            delete subTree;
            subTree = 0;
            //这个位置没有向下的递归，也没有高度的重构，直接返回。
            return subTree;
        }
        //如果只剩下左节点就直接拼接
        if (subTree->RightTree == 0 && subTree->LeftTree != 0) {
            cout << "从左侧拼接" << endl;
            ALVTreeItem<T> *left = subTree->LeftTree;

            //去除当前节点
            delete subTree;
            //从左侧拼过来
            subTree = left;

            //不能结束，之后还要有调整height的过程
        }

        //如果只剩下右边的节点也直接拼接
        if (subTree->LeftTree == 0 && subTree->RightTree != 0) {
            cout << "从右侧直接拼接" << endl;
            ALVTreeItem<T> *right = subTree->RightTree;

            //去除当前节点
            delete subTree;
            //从右侧拼接过来
            subTree = right;
        }

        //如果两个子树都有，那么就需要后继节点
        if (subTree->LeftTree != 0 && subTree->RightTree != 0) {
            cout << "找到后继节点" << endl;
            //往右边走一个，然后一口气走到最左边
            ALVTreeItem<T> *deleteItem = subTree->RightTree;
            while (deleteItem->LeftTree != 0) {
                deleteItem = deleteItem->LeftTree;
            }

            //这里的deleteItem里面存的就是我们需要的东西了
            //我们把他的值拿上来，然后直接从当前节点的右子树开始递归删除他
            //我们这里不能直接删除，因为直接的删除，height的重置不好弄
            subTree->element = deleteItem->element;

            //从右子树递归删除
            subTree->RightTree = subTreeDelete(subTree->RightTree, deleteItem->element);
        }
    }

    //这里重构高度
    updateHeight(subTree);
    cout << "高度已更新" << subTree->element << ":" << subTree->height << endl;

    //然后这里进行旋转
    //我们先看height有没有相差2
    int leftHeight = -1;
    int rightHeight = -1;

    if (subTree->LeftTree != 0) {
        leftHeight = subTree->LeftTree->height;
    }

    if (subTree->RightTree != 0) {
        rightHeight = subTree->RightTree->height;
    }


    if (leftHeight >= rightHeight + 2) {
        //左边高
        cout << "删除之后发现左边比较高" << endl;
        //看是LL还是LR
        leftHeight = -1;
        rightHeight = -1;

        ALVTreeItem<T> *left = subTree->LeftTree;

        if (left->LeftTree != 0) {
            leftHeight = left->LeftTree->height;
        }

        if (left->RightTree != 0) {
            rightHeight = left->RightTree->height;
        }

        if (leftHeight > rightHeight) {
            //这个就是ll，两次都是左边高
            //在SubTree上执行一次右旋
            cout << "发现是ll" << endl;
            subTree = rightRot(subTree);
        }
        if (leftHeight < rightHeight) {
            //这个就是LR，先在left上执行左旋，然后在sub上执行右旋
            cout << "发现是lr" << endl;
            subTree->LeftTree = leftRot(subTree->LeftTree);
            subTree = rightRot(subTree);
        }
        return subTree;
    }

    if (rightHeight >= leftHeight + 2) {
        //左边高
        cout << "删除之后发现右边比较高" << endl;
        //看是LL还是LR
        leftHeight = -1;
        rightHeight = -1;

        ALVTreeItem<T> *right = subTree->RightTree;

        if (right->LeftTree != 0) {
            leftHeight = right->LeftTree->height;
        }

        if (right->RightTree != 0) {
            rightHeight = right->RightTree->height;
        }

        if (leftHeight < rightHeight) {
            cout << "发现是rr" << endl;
            subTree = leftRot(subTree);
        }
        if (leftHeight > rightHeight) {
            cout << "发现是rl" << endl;
            subTree->RightTree = rightRot(subTree->RightTree);
            subTree = leftRot(subTree);
        }
        return subTree;
    }

    return subTree;
}


//关于ALV树节点的实现
template<class T>
class ALVTreeItem {
    friend class ALVTree<T>;

public:
    ALVTreeItem(ALVTreeItem *leftTree, ALVTreeItem *RightTree, T element, int height);

//private:
    ALVTreeItem<T> *LeftTree;
    ALVTreeItem<T> *RightTree;
    T element;
    int height;
};

template<class T>
ALVTreeItem<T>::ALVTreeItem(ALVTreeItem<T> *leftTree, ALVTreeItem<T> *RightTree, T element, int height) : LeftTree(
        leftTree),
                                                                                                          RightTree(
                                                                                                                  RightTree),
                                                                                                          element(element),
                                                                                                          height(height) {}

#endif //MYDATASTRUCTURE_ALVTREE_H
