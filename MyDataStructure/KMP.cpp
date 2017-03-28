//
//  KMP.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include "KMP.h"
#include <iostream>

using namespace std;

int *pre_handle(string patch_string) {
    //对准备去匹配的小字符串进行预处理，返回一个数组
    //这个数组通过最大公共子字符串得出如果匹配失败
    //匹配的小字符串向前挪动多少
    int *returnArr = new int[patch_string.length()];

    int tmp = -1;

    for (int i = 0; i < patch_string.length(); i++) {
        if (i == 0) {
            returnArr[i] = -1;
            continue;
        }

        if (patch_string[i] == patch_string[tmp + 1]) {
            //如果发现有最大公共子字符串的可能性
            tmp++;
        } else {
            tmp = -1;
        }

        returnArr[i] = tmp;

    }

//    for(int  i = 0 ; i < patch_string.length() ; i++){
//        cout << returnArr[i] << ",";
//    }
//    cout << endl;
    return returnArr;
}

int KMPSearch(string patch_string, string goal_string) {
    //我们首先先进行预处理，需要delete这个堆区数组
    int *pre_handle_arr = pre_handle(patch_string);


    //然后进行比较
    int compare_continue = -1;

    int patch_string_index = 0;
    int goal_string_index = 0;

    //退出这个循环主要是两种情况，首先就是目标字符串走完了，还有就是要匹配别人的小字符串走完了，前者代表失败，后者代表成功
    while (patch_string_index < patch_string.length() && goal_string_index < goal_string.length()) {

        if (patch_string[patch_string_index] == goal_string[goal_string_index]) {
            compare_continue = pre_handle_arr[patch_string_index];
            patch_string_index++;
            goal_string_index++;
        } else {
            //如果没有匹配成功，并且这个时候compare_continue是-1，说明在已匹配子串中没有最大公共子序列
            //那么我们直接匹配目标字符串的下一位
            if (compare_continue == -1) {
                goal_string_index++;
                patch_string_index = 0;
            } else {
                //如果在某一位匹配失败，并且有公共子序列，那么就利用公共子序列，将公共子序列的前半部分向前挪到后半部分的位置
                patch_string_index = compare_continue + 1;

                compare_continue = pre_handle_arr[compare_continue];
//                cout << patch_string_index << "," << compare_continue << endl;
            }
        }

//        cout << patch_string_index << "," << goal_string_index << endl;
    }

    delete pre_handle_arr;

    if (patch_string_index == patch_string.length()) {
        //匹配成功返回一开始匹配上的初始位置
        return goal_string_index - int(patch_string_index);
    }

    if (goal_string_index == patch_string.length()) {
        //匹配失败返回-1
        return -1;
    }



    //不可能到这里
    return -2;
}
