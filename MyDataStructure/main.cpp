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

    linkedBTree->addRight(2);
    linkedBTree->addLeft(3);
    

    cout << linkedBTree->readNow() << endl;

    delete linkedBTree;

    return 0;
}
