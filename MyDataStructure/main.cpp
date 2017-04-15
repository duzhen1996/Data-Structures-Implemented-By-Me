//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "CountSort.h"

using namespace std;

int main(int argc, const char *argv[]) {
    int* input = new int[8];

    for (int j = 0; j < 8; ++j) {
        input[j] = 8-j;
    }

    count_sort(input , 8);

    for (int i = 0; i < 8; ++i) {
        cout << input[i] << " , ";
    }

    return 0;
}
