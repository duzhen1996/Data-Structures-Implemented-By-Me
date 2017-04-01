//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

int main(int argc, const char *argv[]) {
    LinkedList<int>* linkedList = new LinkedList<int>(1);

    linkedList->insert(0, 2);
    linkedList->insert(1, 3);
    linkedList->insert(0, 4);

    linkedList->printLinkedList();

    linkedList->deleteItem(2);



    linkedList->printLinkedList();

    return 0;
}
