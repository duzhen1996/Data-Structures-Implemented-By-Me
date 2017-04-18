//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "MultiTree.h"

using namespace std;


int main(int argc, const char *argv[]) {
    MultiTree<int> *multiTree = new MultiTree<int>(1);

    multiTree->addChild(2, 1);

    multiTree->addChild(3, 1);

    multiTree->goChild();

    multiTree->goBrother();

    multiTree->goParent();

    multiTree->delChild(2);

    cout << multiTree->getContent() << endl;

    delete multiTree;

    return 0;
}
