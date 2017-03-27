//
//  main.cpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#include <iostream>
#include <string>
#include "KMP.h"
using namespace std;

int main(int argc, const char * argv[]) {
    cout << KMPSearch("abcabc", "aqwewabcabcabc");
    
    return 0;
}
