//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "BinarySearchTree.h"

using namespace std;


int main(int argc, const char *argv[]) {
    BinarySearchTree<int>* tree = new BinarySearchTree<int>(8);

    tree->insert(4);
    tree->insert(12);
    tree->insert(2);
    tree->insert(6);
    tree->insert(10);
    tree->insert(14);
    tree->insert(1);
    tree->insert(3);
    tree->insert(5);
    tree->insert(7);
    tree->insert(9);
    tree->insert(11);
    tree->insert(13);
    tree->insert(15);

    tree->delItem(10);
    tree->delItem(11);
    tree->delItem(4);

//    tree->insert(2);
//
//    tree->insert(3);
//
//    cout << tree->ifExist(2) << endl;

//    tree->delItem(2);
//
//    cout << tree->ifExist(2) << endl;

    delete tree;

    return 0;
}
