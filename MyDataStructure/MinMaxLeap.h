//
// Created by 杜臻 on 2017/5/12.
//

#ifndef MYDATASTRUCTURE_MINMAXLEAP_H
#define MYDATASTRUCTURE_MINMAXLEAP_H

#include <iostream>
#include <math.h>

using namespace std;

template<class T>
class MinMaxLeapItem;

//这个里面放一个最小最大堆的实现
//这是一种双端优先队列的实现方式
//我们在当中存一次键值对试试
template<class T>
class MinMaxLeap {
public:
    //这里决定了我们一开始申请的堆空间大小
    MinMaxLeap(int leapSize);

    //插入元素
    void Insert(int Key, T Value);

    //弹出并删除最大值
    MinMaxLeapItem<T> *deleteMin();

    //弹出并删除最大值
    MinMaxLeapItem<T> *deleteMax();

    //打印堆中所有元素
    void printAll();

private:
    //这里我们定义一个log2的计算
    int log2(int value);

    //这里建立一个子树删除重构的递归函数
    void reBuildTree(int rootIndex, MinMaxLeapItem<T> *addtionItem);

    //首先一个指针数组存储当前元素
    MinMaxLeapItem<T> **leapContent;

    //然后使用一个指针存储最后一个值对应的索引
    int validIndex;
};

template<class T>
ostream &operator<<(ostream &out, const MinMaxLeapItem<T> *minMaxLeapItem) {
//    out << "进入" << endl;
    out << minMaxLeapItem->getKey() << " , " << minMaxLeapItem->getValue();
    //递归返回，方便级联调用
    //并且因为cout并没有实现良好的拷贝构造函数，所以我们必须返回引用
    return out;
};

template<class T>
void MinMaxLeap<T>::printAll() {
    //打印堆的值
    for (int i = 1; i <= validIndex; ++i) {
        cout << leapContent[i] << endl;
    }
}

template<class T>
void MinMaxLeap<T>::Insert(int Key, T Value) {
    //这个函数的主要工作就是在最小最大堆中插入一个节点
    //首先我们创建要插入的节点
    MinMaxLeapItem<T> *minMaxLeapItem = new MinMaxLeapItem<T>(Key, Value);

    //然后我们插入在堆数组的最后一个位置
    validIndex++;

    leapContent[validIndex] = minMaxLeapItem;

    //然后进行重构，使用循环来重构。
    //首先判断是要跟最大层比还是最小层比。
    //首先看有没有父节点
    //这里说明有父节点，需要重构比较
    if (validIndex != 1) {
        //这里开始重构操作
        //首先和父节点比较，看看要和最小层还是最大层比
        if (leapContent[validIndex] <= leapContent[validIndex / 2]) {
            cout << "与最小层的进行比较" << endl;

            //这里说明和到根的所有最小层比较就好了
            //这里我们先看看当前节点是最大层还是最小层
            //首先看看在第几层
            int deep = log2(validIndex);
            int nextIndex;
            int nowIndex = validIndex;
            //然后看看是不是偶数层
            if (deep % 2 == 0) {
                //这里说明是偶数层，也就是当前节点在最小层
                nextIndex = validIndex / 4;
            } else {
                //这里说明新加入节点在最大层
                nextIndex = validIndex / 2;
            }

            while (nextIndex > 0) {
                //如果nextIndex到0，说明根节点已经换过了
                //如果比父节点小那就往上换
                if (leapContent[nowIndex]->getKey() <= leapContent[nextIndex]->getKey()) {
                    //首先先动数组
                    MinMaxLeapItem<T> *tmpItem = leapContent[nextIndex];
                    leapContent[nextIndex] = leapContent[nowIndex];
                    leapContent[nowIndex] = tmpItem;
                    //然后解决索引
                    nowIndex = nextIndex;
                    nextIndex = nextIndex / 4;
                } else {
                    //这里说明比最小层的节点大，那么就留着吧
                    break;
                }
            }

        } else {
            //这里说明要和最大层的节点比。
            cout << "和最大层的节点比" << endl;
            int deep = log2(validIndex);
            int nextIndex;
            int nowIndex = validIndex;
            //然后看看是不是偶数层
            if (deep % 2 == 0) {
                //这里说明是偶数层，也就是当前节点在最小层
                nextIndex = validIndex / 2;
            } else {
                //这里说明新加入节点在最大层
                nextIndex = validIndex / 4;
            }

            //我们向上和最大层比
            //nextIndex <= 1时说明函数已经搞定了
            while (nextIndex > 1) {
                //和最大层的元素比，如果比最大层元素大就换上去。
                if (leapContent[nowIndex]->getKey() > leapContent[nextIndex]->getKey()) {
                    //先处理数组
                    //首先先动数组
                    MinMaxLeapItem<T> *tmpItem = leapContent[nextIndex];
                    leapContent[nextIndex] = leapContent[nowIndex];
                    leapContent[nowIndex] = tmpItem;
                    //然后解决索引
                    nowIndex = nextIndex;
                    nextIndex = nextIndex / 4;
                } else {
                    break;
                }
            }
        }
    }

    cout << "插入完成" << endl;
}

template<class T>
MinMaxLeap<T>::MinMaxLeap(int leapSize) {
    //我们创建一个空堆
    leapContent = new MinMaxLeapItem<T> *[leapSize];
    //然后初始化数组有效做索引的最后一位
    validIndex = 0;
}

template<class T>
int MinMaxLeap<T>::log2(int value) {
    return log10(value) / log10(2);
}

template<class T>
MinMaxLeapItem<T> *MinMaxLeap<T>::deleteMin() {
    //删除并弹出最小值
    //首先先把最小的节点取出来
    MinMaxLeapItem<T> *returnPtr = leapContent[1];

    //然后拿出最后一个节点，作为补位节点
    MinMaxLeapItem<T> *additionItem = leapContent[validIndex];

    validIndex--;
    cout << validIndex << endl;

    //我们设计一个递归函数这个函数两个形参，一个是当前需要进行堆重构的根节点
    //还有一个是补位节点
    reBuildTree(1, additionItem);

    return returnPtr;

}

template<class T>
void MinMaxLeap<T>::reBuildTree(int rootIndex, MinMaxLeapItem<T> *addtionItem) {
    //首先从根节点的儿子和孙子节点中找到次小值
    //首先是儿子节点
    //次小值的索引


    //如果不可能找到次小值就会进入这里
    //那么就直接补位

    if(rootIndex * 2 > validIndex){
        leapContent[rootIndex] = addtionItem;
        return;
    }

    int nextSmall = rootIndex * 2;
    for (int i = rootIndex * 2 + 1; i <= rootIndex * 2 + 1 && i <= validIndex; ++i) {
        if (leapContent[i]->getKey() < leapContent[nextSmall]->getKey()) {
            //这里说明发现一个更小的，那么我们就可以把更小的记录下来
            nextSmall = i;
        }
    }

    //再看孙子节点
    for (int j = rootIndex * 4; j <= rootIndex * 4 + 3 && j <= validIndex; ++j) {
        if (leapContent[j]->getKey() < leapContent[nextSmall]->getKey()) {
            //更小
            nextSmall = j;
        }
    }

    //如果补位节点比次小值还要小的话，直接把补位节点换到根节点上
    if (addtionItem->getKey() < leapContent[nextSmall]->getKey()) {
        leapContent[rootIndex] = addtionItem;
        return;
    }


    //如果次小值在子节点上，次小值换到跟上，补位节点换到次小值上
    if (nextSmall >= rootIndex * 2 && nextSmall <= rootIndex * 2 + 1) {
        cout << "次小值在子节点上" << endl;
        leapContent[rootIndex] = leapContent[nextSmall];
        leapContent[nextSmall] = addtionItem;
        return;
    }

    //如果次小值在孙子节点上
    if (nextSmall >= rootIndex * 4 && nextSmall <= rootIndex * 4 + 3) {
        cout << "次小值在孙子节点上" << endl;
        leapContent[rootIndex] = leapContent[nextSmall];

        //其次我们就看看次小节点的父节点和补位节点之间的比较
        if (leapContent[nextSmall / 2]->getKey() < addtionItem->getKey()) {
            //将补位节点与父节点呼唤
            MinMaxLeapItem<T> *tmpItem = leapContent[nextSmall / 2];
            leapContent[nextSmall / 2] = addtionItem;
            addtionItem = tmpItem;
        }

        reBuildTree(nextSmall, addtionItem);
        return;
    }

    cout << "不可能到这里" << endl;
}


template<class T>
class MinMaxLeapItem {
    friend class MinMaxLeap<T>;

public:
    //我们重载一下打印的运算符
//    friend ostream &operator<<(ostream& out, const MinMaxLeapItem<T>& minMaxLeapItem);

    //构造函数
    MinMaxLeapItem(int key, T value);

    int getKey() const;

    T getValue() const;

private:
    int key;
    T value;
};

template<class T>
MinMaxLeapItem<T>::MinMaxLeapItem(int key, T value) : key(key), value(value) {}

template<class T>
int MinMaxLeapItem<T>::getKey() const {
    return key;
}

template<class T>
T MinMaxLeapItem<T>::getValue() const {
    return value;
}


#endif //MYDATASTRUCTURE_MINMAXLEAP_H
