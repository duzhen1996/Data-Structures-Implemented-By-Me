//
// Created by 杜臻 on 2017/5/10.
//

#include "LostTree.h"
#include <iostream>

using namespace std;

LostTree::LostTree(int mergeSize) {
    //我们使用一个函数来进行构造，使用要归并的数组的数量来初始化，这决定了我们树叶节点数量非非叶节点数量
    buffer = new int[mergeSize];
    //按理来说完全树叶节点和非叶节点数组是一样的
    indexLeaf = new int[mergeSize];

    this->mergeSize = mergeSize;
}

LostTree::~LostTree() {
    delete[]buffer;
    delete[]indexLeaf;
}


void LostTree::treeBuild() {
    //我们首先构造胜者树
    //自下而上构造，我们从最后一位开始，构造到根节点，先不要管根节点的父节点
    for (int i = mergeSize - 1; i >= 1; i--) {
        //我们遍历所有的非叶节点，将这些节点的左右两个子节点的key比较的放到父节点中，我们进行从小到大的归并
        //首先我们找出左儿子所在的归并数组号
        int left = getBufferIndex(i * 2);
        int right = getBufferIndex(i * 2 + 1);

        //我们让左儿子和右儿子的值做一个比较，小的往父节点放
        if (buffer[left] >= buffer[right]) {
            //让右儿子的节点放到父节点上
            indexLeaf[i] = right;
        } else {
            indexLeaf[i] = left;
        }
    }

    //到这里胜者树构造完毕
    indexLeaf[0] = indexLeaf[1];

    //然后开始进行败者树改造，我们自上而下
    for (int j = 1; j <= mergeSize - 1; ++j) {
        //我们先找出左右节点
        int left = getBufferIndex(j * 2);
        int right = getBufferIndex(j * 2 + 1);

        //这个函数我们只要和buffer索引打交道就好了
        //这里这里就是看看值一不一样，把不一样的失败者换上来

        //如果和左节点一样，就换成右节点，和右节点一样就换成左节点
        if (indexLeaf[j] == left) {
            indexLeaf[j] = right;
        } else {
            indexLeaf[j] = left;
        }
    }
}

int LostTree::getBufferIndex(int treeIndex) {

    if (treeIndex <= mergeSize - 1) {
        return indexLeaf[treeIndex];
    } else {
        //这是叶节点，没有存在于非叶节点数组中，这里推算
        return treeIndex - mergeSize;
    }
}

void LostTree::printLostTree() {
    for (int i = 0; i < mergeSize; ++i) {
        cout << buffer[indexLeaf[i]] << " , ";
    }

    for (int j = 0; j < mergeSize; ++j) {
        cout << buffer[j] << " , ";
    }
    cout << endl;
}

int LostTree::popAndInsert(int newKey) {
    //首先拿出返回值的key
    int returnKey = buffer[indexLeaf[0]];

    //然后将新的值放到缓冲区已经弹出的key对应的索引处
    buffer[indexLeaf[0]] = newKey;

    //这个时候打印一下缓冲区
//    for (int i = 0; i < 8; ++i) {
//        cout << buffer[i] << endl;
//    }

    //然后我们进行树的重构工作，我们不断向上遍历，直到便利到树根，树根的父节点单独处理
    //设置当前索引，在新加入的节点处
    int nowBufferIndex = indexLeaf[0];
    int compareTreeIndex = (indexLeaf[0] + mergeSize) / 2;

    while (true) {

        //一直调整到根节点
        //获取当前节点的key
        int nowKey = buffer[nowBufferIndex];
        int compareKey = buffer[getBufferIndex(compareTreeIndex)];
        cout << "nowKey=" << nowKey << " , " << "compareKey=" << compareKey << endl;
        //如果当前key更小，就不断向上走，如果比父节点大，那就父节点代替他向上走
        //当前节点留在父节点的位置
        if (nowKey <= compareKey) {
            //如果没到根节点，继续向上比较
            if (compareTreeIndex != 1) {
                compareTreeIndex = compareTreeIndex / 2;
            } else {
                //如果已经到了根节点，那就直接把这个key的buffer索引，
                //也就是归并数组号放到0号节点上
                indexLeaf[0] = nowBufferIndex;
                break;
            }
        } else {

            if (compareTreeIndex != 1) {
                int tmpBufferIndex = indexLeaf[compareTreeIndex];
                indexLeaf[compareTreeIndex] = nowBufferIndex;
                nowBufferIndex = tmpBufferIndex;
                compareTreeIndex = compareTreeIndex / 2;
                cout << "来到这里1 nowBufferIndex = " << nowBufferIndex << " compareTreeIndex = " << compareTreeIndex
                     << endl;

            } else {
                cout << "来到这里2 nowBufferIndex = " << nowBufferIndex << " compareTreeIndex = " << compareTreeIndex
                     << endl;
                //这里说明now节点已经比到根节点的，如果比根节点大，那他就留在根节点，根节点根节点走到父节点的位置
                indexLeaf[0] = getBufferIndex(compareTreeIndex);
                indexLeaf[1] = nowBufferIndex;
                break;
            }
        }

        cout << endl;

        //先打印一次数组
        for (int i = 0; i < 8; ++i) {
            cout << buffer[indexLeaf[i]] << endl;
        }

        cout << endl;

    }

    return returnKey;
}


