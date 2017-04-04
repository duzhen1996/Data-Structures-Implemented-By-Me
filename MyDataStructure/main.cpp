//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include <string>
#include "DLinkedList.h"
using namespace std;

int main(int argc, const char *argv[]) {
    DLinkedList<int>* list = new DLinkedList<int>();

    list->addRight(1);
    list->addRight(2);
    list->addRight(3);
    list->addRight(4);
    list->addRight(5);

    list -> printNowItem();

    list->goRight();
    list->printNowItem();

    list->goLeft();
    list->goLeft();
    list->printNowItem();

    list->printLinkedList();

    list->toFirst();

    list->goLeft();

    list->deleteItem();

    list->printLinkedList();


    delete list;
    return 0;
}
