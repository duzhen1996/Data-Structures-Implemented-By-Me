//
// Created by 杜臻 on 2017/4/17.
//

#ifndef MYDATASTRUCTURE_RANDOM_SELECT_H
#define MYDATASTRUCTURE_RANDOM_SELECT_H

#include <cstdlib>
#include "time.h"
#include <iostream>

using namespace std;

//第一个形参的输入数组，第二个形参为参与随机选择的数组的起始位置，第三个为参与随机选择的数组结束位置
//第四个为我们要找的是当前范围第rank小的元素
//我们借助快速排序从小到大排序
template<class T>
T random_select_fun(T *inputArr, int start, int end, int rank) {
    //我们确定一个递归结束条件，这个if应该永远不会进入的
    if (start > end) {
        cout << "发生了错误" << endl;
        return NULL;
    }


    //我们首先加入随机过程，随机制定start和end之间的数为桩
    //首先我们摇一个种子
    srand(time(0));
    //找出一个桩
    int stake = rand() % (end - start + 1) + start;
    int tmp = inputArr[end];
    inputArr[end] = inputArr[stake];
    inputArr[stake] = tmp;
    stake = end;

    //桩的数值大小
    int stackNum = inputArr[stake];

    //然后进行类似于快速排序的工作，声明两个索引，一个是放在数组的第一位一个是放在-1位
    //数组的扫描索引
    int j;
    //比桩变量小的数组的最大索引，i+1就是桩，i+2就是比桩大的第一个数
    int i = start - 1;

    for (int j = start; j <= end; ++j) {
        //遍历我们要进行扫描和处理的数组
        if (inputArr[j] <= stackNum) {
            //发现有比桩小的数组，我们就把他们放到start和i（包括i）之间，主要是使用交换的方式
            //因为桩还没有换过来，所以i+1就是比桩大的部分。
            i++;
            tmp = inputArr[i];
            inputArr[i] = inputArr[j];
            inputArr[j] = tmp;
        }
    }

    //最后i就是桩所在的位置
    //我们看看这个桩是不是我们需要的
    //这里要注意，我们虽然发现桩是i，但是实际上i索引所对应的排位应该是i-start+1
    if (rank == i - start + 1) {
        return inputArr[i];
    }

    //如果我们要的数的排序比i+1要小，那么就要进行桩左部数组的递归
    if (rank < i - start + 1) {
        return random_select_fun(inputArr, start, i - 1, rank);
    }

    //如果我们要的数的排序比i+1要打，那么就要进行右部的递归
    //我们首先要知道比i小的数在这个部分一共有多少个，也就是在i左面有多少个数，我们让i和start重合，取一个特殊值就知道有i-start个。
    //所以rank要减去一个i还要减去i左边的数rank - (i - start) - 1
    if (rank > i - start + 1) {
        //这里递归调用的形参要好好注意
        return random_select_fun(inputArr, i + 1, end, rank - (i - start) - 1);
    }
}


template<class T>
T random_select(T *inputArr, int len, int rank) {
    return random_select_fun(inputArr, 0, len - 1, rank);
}


#endif //MYDATASTRUCTURE_RANDOM_SELECT_H
