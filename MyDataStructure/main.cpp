//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main(int argc, const char *argv[]) {
    BinaryTree<int> *tree = new BinaryTree<int>(1);

    tree->editLeft(2);

    tree->editRight(3);

    tree->goRightChild();

    tree->editRight(4);

    tree->editLeft(5);

    tree->toRoot();

    tree->goRightChild();

    tree->delChildTree(tree->getNowIndex());

    int *contentArr = tree->getTreeContentPtr();

    for (int i = 0; i < 256; ++i) {
        cout << i << " : " << contentArr[i] << endl;
    }


    return 0;
}
