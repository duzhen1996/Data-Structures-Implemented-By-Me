//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "MinMaxLeap.h"
#include <string>

using namespace std;


int main(int argc, const char *argv[]) {
    MinMaxLeap<string> *minMaxLeap = new MinMaxLeap<string>(40);

    minMaxLeap->Insert(1, "h");
    minMaxLeap->Insert(2, "e");
    minMaxLeap->Insert(3, "l");
    minMaxLeap->Insert(4, "l");
    minMaxLeap->Insert(5, "o");
    minMaxLeap->Insert(6, " ");
    minMaxLeap->Insert(7, "w");
    minMaxLeap->Insert(8, "o");
    minMaxLeap->Insert(9, "r");
    minMaxLeap->Insert(10, "l");
    minMaxLeap->Insert(11, "d");
    minMaxLeap->Insert(12, " ");
    minMaxLeap->Insert(13, "m");
    minMaxLeap->Insert(14, "y");
    minMaxLeap->Insert(15, " ");
    minMaxLeap->Insert(16, "g");
    minMaxLeap->Insert(17, "o");
    minMaxLeap->Insert(18, "d");

    minMaxLeap->printAll();

    cout << endl;

    MinMaxLeapItem<string> *minMaxLeapItem = minMaxLeap->deleteMin();

    cout << "拿出节点: " << minMaxLeapItem << endl;

    minMaxLeap->printAll();

    return 0;
}
