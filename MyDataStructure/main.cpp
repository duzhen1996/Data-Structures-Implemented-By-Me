//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "Random_Select.h"

using namespace std;

int main(int argc, const char *argv[]) {
    int* input = new int[8]{5,3,6,7,2,4,5,0};

    cout << random_select(input , 8,6) << endl;

    return 0;
}
