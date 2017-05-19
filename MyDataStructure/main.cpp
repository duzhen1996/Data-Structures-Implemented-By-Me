//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include "Graph.h"
#include "Kruskal.h"

using namespace std;


int main(int argc, const char *argv[]) {
    Graph *graph = new Graph(5);




    cout << graph << endl;

    Kruskal(graph);


    return 0;
}
