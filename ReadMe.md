# 常用数据结构与算法的实现

[TOC]

## KMP字符串匹配算法

有时候我们需要在一大段字符串中得到找到我们想要的位置，这个时候KMP字符串匹配算法是一种比较好的选择。

首先我们需要进行**匹配字符串的预处理**，即我们要在一个字符串中找另外一个字符串，我们需要预处理这个字符串。主要是查看这个字符串上有没有“最长公共子序列”。最长公共子序列是是KMP算法的核心概念。这决定了我们一位位向前移动匹配的时候，如果遇到匹配失败的我们应该如何处理，是整个匹配字符串向前挪动一位吗，其实不是挪动一位，只要我们可以知道最长公共子序列，那么我们就可以直接在比较发现不匹配之后，移动一个更大的距离，而不是一格，继续比较。而我们所说的那个“更大的距离”，就是由“最长公共子序列”决定的，我们需要知道，在已经匹配到的子字符串两头最大的公共部分是多少，下次比较的时候我们直接在匹配失败的时候把最大公共部分的前面那部分平移过来，前面那一部分最长公共子序列的下一位开始比较。

预处理还是很简单的：

```c++
//我们首先先进行预处理，需要delete这个堆区数组
    int *pre_handle_arr = pre_handle(patch_string);
    
    
    //然后进行比较
    int compare_continue = -1;
    
    int patch_string_index = 0;
    int goal_string_index = 0;
    
    //退出这个循环主要是两种情况，首先就是目标字符串走完了，还有就是要匹配别人的小字符串走完了，前者代表失败，后者代表成功
    while(patch_string_index < patch_string.length() && goal_string_index < goal_string.length()){
        
        if(patch_string[patch_string_index] == goal_string[goal_string_index]){
            compare_continue = pre_handle_arr[patch_string_index];
            patch_string_index++;
            goal_string_index++;
        }else{
            //如果没有匹配成功，并且这个时候compare_continue是-1，说明在已匹配子串中没有最大公共子序列
            //那么我们直接匹配目标字符串的下一位
            if(compare_continue == -1){
                goal_string_index++;
                patch_string_index = 0;
            }else{
                //如果在某一位匹配失败，并且有公共子序列，那么就利用公共子序列，将公共子序列的前半部分向前挪到后半部分的位置
                patch_string_index = compare_continue + 1;
                
                compare_continue = pre_handle_arr[compare_continue];
//                cout << patch_string_index << "," << compare_continue << endl;
            }
        }
        
//        cout << patch_string_index << "," << goal_string_index << endl;
    }

```

道理很简单，除了第一位，每一位的字符都要和tmp+1这个位置的字符比对一下。如果相等，那么就可以说明最大公共子字符串又扩充了一位。

在逻辑上比较繁琐的就是进行字符串比较的那个过程，有点绕：

```c++
//我们首先先进行预处理，需要delete这个堆区数组
    int *pre_handle_arr = pre_handle(patch_string);
    
    
    //然后进行比较
    int compare_continue = -1;
    
    int patch_string_index = 0;
    int goal_string_index = 0;
    
    //退出这个循环主要是两种情况，首先就是目标字符串走完了，还有就是要匹配别人的小字符串走完了，前者代表失败，后者代表成功
    while(patch_string_index < patch_string.length() && goal_string_index < goal_string.length()){
        
        if(patch_string[patch_string_index] == goal_string[goal_string_index]){
            compare_continue = pre_handle_arr[patch_string_index];
            patch_string_index++;
            goal_string_index++;
        }else{
            //如果没有匹配成功，并且这个时候compare_continue是-1，说明在已匹配子串中没有最大公共子序列
            //那么我们直接匹配目标字符串的下一位
            if(compare_continue == -1){
                goal_string_index++;
                patch_string_index = 1;
            }else{
                //如果在某一位匹配失败，并且有公共子序列，那么就利用公共子序列，将公共子序列的前半部分向前挪到后半部分的位置
                patch_string_index = compare_continue + 1;
                
                compare_continue = pre_handle_arr[compare_continue];
                //cout << patch_string_index << "," << compare_continue << endl;
            }
        }
        
//        cout << patch_string_index << "," << goal_string_index << endl;
    }

```

首先我们要注意循环的条件，必须两个string都没有遍历完才可以进行循环，两个之中有其中一个遍历完了就不可以循环了。

我们主要使用patch_string_index和goal_string_index两个索引分别遍历匹配小字符串和目标字符串。如果相等，当然是这两个索引都会自增，然后比较目标字符串和匹配小字符串的下一位。如果发现不匹配了，首先就要看看以匹配的子串里面有没有最大公共子字符串（使用compare_continue==-1）。如果没有，那么直接使用匹配字符串的第0位去匹配，目标字符串的下一位就好了（patch_string_index=0赋值，goal_string_index自增）。如果发现有最大公共子字符串那就让最大公共子字符串的后一位去匹配目标字符串的当前位置。所以对于比较的结果，一共是三类情况。



## 环状队列

因为队列只能从尾部加入，从顶部移出，所以我们使用传统数组的方式会有问题，因为随着头部内容的不断移出以及尾部的不断移进，整个队列会逐渐往线性表的后部靠拢，这样子在线性表的前半部分就会有很大的空间浪费。如果要把已经贴近后半部分的内容挪到靠近线性表头部的位置，这就需要大量的开销，所以我们就需要换装队列。

环状队列本质上还是线性表，通过取模的操作获得环状的效果。

环状队列比较什么时候满的时候我们，除了可以维护一个存储了环状队列当前容量的变量之外还可以预留一个空位置。为了统一我们的逻辑，我们必须设定一套在所有的时期都适用的判定环状队列空或者满的办法。我们设定头指针与尾指针重合代表空，尾索引取模如果比头索引取模之后小1，或者比头索引大maxsize-1那么就说明队列已经满了。rear永远指向没有值的下一个要插入的位置，头索引永远指向下一个要推出的值，除非队列是空的。

这次实现中使用了模板类，因为模板类不是类，所以模板类是不能拆的，应该放在一个头文件中，要不就会报错。此外我们就是要注意取模和边界条件。这样子就可以了。总体的实现还是比较简单的。

## 走迷宫算法

走迷宫算法是一个对栈结构的非常不错的利用，我们我们通过一个栈来获得我们已经走过的路径，如果栈顶的节点在所有方向上都走不通，那就进行弹栈操作。在倒数第二个节点上进行各个方向的尝试。任何曾经进过栈的节点都会被记录下来，防止走重复的路。

这里在编程里面碰到了一些问题，比如在C++11中，我们发现枚举和结构体实例化的时候我们不再需要在前面再加struct和enum这两个关键词。直接当做一个类使用就好了。

此外我们发现int a\[\]\[\]，实际上a变量这个时候并不是一个二维指针，而是一个数组对象，所以说我们没有办法把他当做一个二维指针使用。其实使用栈空间来申请二维数组，获取其二维指针的方式并不是没有，但是比较困难，并且语法比较容易混淆，所以我们使用new的方式产生线性数组，以及指针数组来产生二维数组。



