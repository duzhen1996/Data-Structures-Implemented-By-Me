//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "BTree.h"

using namespace std;


int main(int argc, const char *argv[]) {
    BTree<int> *bTree = new BTree<int>(8, 6);

    bTree->printTree();
    bTree->insertKey(7, bTree->root);
    bTree->insertKey(6, bTree->root);
    bTree->insertKey(9, bTree->root);
    bTree->insertKey(10, bTree->root);
    bTree->insertKey(11, bTree->root);
    bTree->insertKey(12, bTree->root);
    bTree->insertKey(13, bTree->root);
    bTree->insertKey(14, bTree->root);
    bTree->insertKey(15, bTree->root);
    bTree->insertKey(16, bTree->root);

    for (int i = 17; i < 30; ++i) {
        bTree->insertKey(i, bTree->root);
    }

//    BTreeItem<int> *prePtr = bTree->getPost(bTree->root, 1);

//    bTree->delItemKey();

    bTree->printTree();


    bTree->delItemKey(11);

    bTree->printTree();

    return 0;
}
