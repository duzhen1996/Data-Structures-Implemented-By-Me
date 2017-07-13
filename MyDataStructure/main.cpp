//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "ALVTree.h"

typedef ldiv_t;;
using namespace std;


int main(int argc, const char *argv[]) {
    ALVTree<int> *alvTree = new ALVTree<int>(0);
    //测试右旋函数
    alvTree->insert(0);
    alvTree->insert(1);
    alvTree->insert(-3);
    alvTree->insert(-4);
    alvTree->insert(-2);
    alvTree->insert(2);
    alvTree->insert(-1);


    alvTree->deleteItem(2);

    alvTree->pre_scan(alvTree->getRoot());

}
