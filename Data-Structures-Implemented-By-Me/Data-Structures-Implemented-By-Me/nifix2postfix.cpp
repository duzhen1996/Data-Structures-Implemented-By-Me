//
// Created by 杜臻 on 17/3/30.
//

#include <string>
#include <iostream>
#include "nifix2postfix.h"


using namespace std;



string nifix2postfix(string postfix){
    //首先我们创建一个栈，这个栈的大小设定为前缀表达式的长度大小
    char* stackArr = new char[postfix.length()];
    //这是栈的栈顶索引，栈顶索引为-1，说明栈是空的
    int stackArrIndex = -1;

    //这里是一个记录栈顶元素优先级的变量
    //*与/优先级是2
    //+和-优先级是1
    int topPre = 0;

    //然后开启一个for循环遍历数组
    for (int i = 0; i < postfix.length(); ++i) {

        if(postfix[i] == '('){
            topPre = 0;
            stackArrIndex++;
            stackArr[stackArrIndex] = postfix[i];
            //直接进行下次循环
            continue;
        }
        if(postfix[i] == ')'){
            //在符号栈中进行一系列弹栈操作，直到弹出第一个左括号
            topPre = 0;
            while(stackArr[stackArrIndex] != '('){
                cout << stackArr[stackArrIndex];
                stackArrIndex--;
            }

            //出循环的理由就是遇到一个左括号了，我们直接跳过这个左括号
            stackArrIndex--;

            //修改顶部运算符优先级
            if(stackArrIndex !=-1){
                if(stackArr[stackArrIndex] == '+' || stackArr[stackArrIndex] == '-'){
                    topPre = 1;
                }

                if (stackArr[stackArrIndex] == '*' || stackArr[stackArrIndex] == '/'){
                    topPre = 2;
                }
            }

            continue;
        }

        if (postfix[i] == '+' || postfix[i] == '-'){
            //如果这个时候栈顶优先级比较大，先把栈弹出
            //弹栈的方式有两种，一种是一口气弹干净，还有一种是弹到最近的一次左括号，其中左括号是不弹出的。

            if(topPre > 1){
                while(stackArrIndex != -1){
                    if (postfix[i] == '('){
                        break;
                    }
                    //在发现一个左括号之前一一弹栈
                    cout << postfix[i];
                    stackArrIndex--;
                }
            }

            //添加栈顶运算符优先级信息
            topPre = 1;
            stackArrIndex++;
            stackArr[stackArrIndex] = postfix[i];
            continue;
        }

        if (postfix[i] == '*' || postfix[i] == '/'){
            //最高优先级的运算符加到栈中，不需要考虑任何运算符优先级
            topPre = 2;
            stackArrIndex++;
            stackArr[stackArrIndex] = postfix[i];

            continue;
        }

        cout << postfix[i];


    }

    //当这个数组遍历完之后，我们弹出剩下的东西
    for (int j = stackArrIndex; j > -1 ; --j) {
        cout << stackArr[j];
    }

    //函数结束，析构符号栈
    delete[] stackArr;

	return "";
}