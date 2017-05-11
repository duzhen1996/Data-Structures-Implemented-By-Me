//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "LostTree.h"

using namespace std;


int main(int argc, const char *argv[]) {
    LostTree *lostTree = new LostTree(8);

    lostTree->buffer[0] = 10;
    lostTree->buffer[1] = 9;
    lostTree->buffer[2] = 20;
    lostTree->buffer[3] = 6;
    lostTree->buffer[4] = 8;
    lostTree->buffer[5] = 9;
    lostTree->buffer[6] = 90;
    lostTree->buffer[7] = 17;


    lostTree->treeBuild();

    lostTree->printLostTree();

    lostTree->popAndInsert(18);

    lostTree->printLostTree();

    return 0;
}
