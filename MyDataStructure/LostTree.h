//
// Created by 杜臻 on 2017/5/10.
//

#ifndef MYDATASTRUCTURE_LOSTTREE_H
#define MYDATASTRUCTURE_LOSTTREE_H

//为了实现方便，我们就不进行键值对的归并，我们就使用键来建树就好
class LostTree {
public:
    //这里我们先创造败者树的构造函数
    LostTree(int mergeSize);

    //这里我们进行树的构造，在缓冲区填满之后进行。
    void treeBuild();

    //获取当前树数组索引的key的缓冲区编号，也就是当前节点的所属于的归并数组序号
    int getBufferIndex(int treeIndex);

    //打印败者树
    void printLostTree();

    //这里我们进行析构函数的处理
    ~LostTree();

    //然后声明一个数组来存储叶节点缓存，这里本来是要存储键值对的，我们简化这个过程，存的是键数字
    int *buffer;

    //这里我们输出一个元素，并且加入新元素进行重构
    //返回的是一个归并数组序号，并且接受一个形参，向缓冲区加入一个新的key，去替代被弹出元素的位置
    //并且最后重构一个数组
    int popAndInsert(int newKey);

private:
    //合并的数组个数，也是下面两个数组的大小
    int mergeSize;

    //声明一个数组来存储完全树的非叶节点，存的是缓冲区索引，也就是归并数组的序号
    int *indexLeaf;

};


#endif //MYDATASTRUCTURE_LOSTTREE_H
