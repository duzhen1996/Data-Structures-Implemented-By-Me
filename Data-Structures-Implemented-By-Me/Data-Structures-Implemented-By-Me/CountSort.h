//
// Created by 杜臻 on 2017/4/10.
//

#ifndef MYDATASTRUCTURE_COUNTSORT_H
#define MYDATASTRUCTURE_COUNTSORT_H

#include <iostream>

using namespace std;

//输入参数为一个输入数组的指针，以及输入数组的长度
//这里我们对自然数进行排序
void count_sort(int* &inputArr, int len) {
    //首先我们设定一个临时数组，这个临时数组的大小和输入数组中所有元素的最大值有关系
    //我们遍历输入数组，然后我们找出最大值
    int large = -1;
    for (int i = 0; i < len; ++i) {
        if (large < inputArr[i]) {
            large = inputArr[i];
        }
    }
    //然后根据这个最大值创造一个数组，这里我们要注意这个数组的大小
    //我们要让输入数组的最大值与临时数组的最大索引保持一致
    int *temp_count = new int[large + 1];
    //这个计数数组的初始化
    for (int j = 0; j <= large; ++j) {
        temp_count[j] = 0;
    }
    //然后我们进行计数
    for (int k = 0; k < len; ++k) {
        temp_count[inputArr[k]]++;
    }

//    for (int j = 0; j <= large ; ++j) {
//        cout << temp_count[j] << " , ";
//    }
//    cout << endl;
    //然后我们进一步处理临时计数数组，让数组第n位记录输入数组中小于等于n的元素个数
    //处理方法就是不断从临时数组的第一位开始不断让相邻的两个数相加
    for (int l = 1; l <= large; ++l) {
        temp_count[l] = temp_count[l] + temp_count[l - 1];
    }

//    for (int j = 0; j <= large ; ++j) {
//        cout << temp_count[j] << " , ";
//    }
//    cout << endl;

    //建立输出数组
    int *output = new int[len];

    //然后我们遍历输入数组，为输入数组的每一个元素在输出数组中找到一个新的位置
    for (int m = 0; m < len; ++m) {
        //通过查看临时计数数组，给输入元素找在输出元素的位置
        output[temp_count[inputArr[m]]-1] = inputArr[m];
        //因为可能有重复元素，所以我们要在排序之后将计数值-1
        temp_count[inputArr[m]]--;
    }
    delete inputArr;
    inputArr = output;
}

#endif //MYDATASTRUCTURE_COUNTSORT_H
