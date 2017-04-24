//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "LinkedBTree.h"

using namespace std;


int main(int argc, const char *argv[]) {
    LinkedBTree<int>* linkedBTree = new LinkedBTree<int>(1);

    linkedBTree->addLeft(2);

    linkedBTree->addRight(3);

    linkedBTree->goLeft();

    linkedBTree->addLeft(4);

    linkedBTree->addRight(5);

    linkedBTree->toRoot();

    linkedBTree->goRight();

    linkedBTree->addLeft(6);

    linkedBTree->addRight(7);

    linkedBTree->post_order();

    delete linkedBTree;

    return 0;
}
