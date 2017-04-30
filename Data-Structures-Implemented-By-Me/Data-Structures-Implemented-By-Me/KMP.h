//
//  KMP.hpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/27.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#ifndef KMP_h
#define KMP_h

#include <stdio.h>
#include <string>

using namespace std;

int *pre_handle(string patch_string);

//前面是要去匹配别人的小字符串，后面是被匹配到额字符串，返回的是匹配到的位置
int KMPSearch(string patch_string, string goal_string);

#endif /* KMP_hpp */
