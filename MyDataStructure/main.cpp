//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "QuickSort.h"

using namespace std;

int main(int argc, const char *argv[]) {
    int A[] = {9,8,7,6,5,4,3,2,1};

    quick_sort(A , 9);

    for (int i = 0; i < 9; ++i) {
        cout << A[i] << endl;
    }

    return 0;
}
