//
// Created by 杜臻 on 2017/4/9.
//

#ifndef MYDATASTRUCTURE_QUICKSORT_H
#define MYDATASTRUCTURE_QUICKSORT_H

#include <iostream>

using namespace std;

template<class T>
void part_quick_sort(T *inputArr, int start, int end);

template<class T>
void quick_sort(T *inputArr, int len) {
    //这个是一个递归的算法
    part_quick_sort(inputArr, 0, len - 1);
}

//这个部分是要递归的函数，
template<class T>
void part_quick_sort(T *inputArr, int start, int end) {
    //判定递归停止
    if (start >= end ) {
        //递归停止
        return;
    }

    //我们需要初始化两个指针，一个指针从头开始扫描
    int i = start - 1;
    //这个变量是桩，桩在数组的最后
    int pile = inputArr[end];
    int tmp = 0;
    for (int j = start; j <= end; ++j) {
        //j这个索引从子列的头部开始扫描，如果发现桩比数组小，那么就让j当前指向的元素和i+1所在的元素交换，并且i向前移动
        //对于i这个索引来说，我们要保证i是比桩小的，i+1是比桩大的。
        //我们要把比桩小的往前扔
        if (inputArr[j] <= pile) {
            tmp = inputArr[j];
            inputArr[j] = inputArr[i + 1];
            inputArr[i + 1] = tmp;
            i++;
        }
    }
    //等循环结束之后，i所在的位置就是桩经过换到中间之后的位置。现在我们拆分数组，进行递归
    part_quick_sort(inputArr, 0, i - 1);
    part_quick_sort(inputArr, i + 1, end);
}

#endif //MYDATASTRUCTURE_QUICKSORT_H
