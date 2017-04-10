//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "LinkedBTree.h"
#include "BinaryTree.h"

using namespace std;

int main(int argc, const char *argv[]) {
    BinaryTree<int> *binaryTree = new BinaryTree<int>(1);

    binaryTree->editLeft(2);
    binaryTree->editRight(3);

    binaryTree->goLeft();
    binaryTree->editLeft(4);
    binaryTree->editRight(5);

    binaryTree->toRoot();

    binaryTree->goRight();
    binaryTree->editLeft(6);
    binaryTree->editRight(7);

    binaryTree->pre_order(1);
    cout << endl;
    binaryTree->post_order(1);
    cout << endl;
    binaryTree->in_order(1);
    cout << endl;
    return 0;
}
