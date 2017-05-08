//
// Created by 杜臻 on 2017/5/6.
//

#ifndef MYDATASTRUCTURE_BTREE_H
#define MYDATASTRUCTURE_BTREE_H

#include <iostream>

using namespace std;

//这里我们实现一个B树，首先声明B树，作为一个模板类
template<class T>
class BTree;

//然后我们声明B树的一个节点
template<class T>
class BTreeItem {
    friend class BTree<T>;

private:
    //首先设计数据成员
    //首先需要一个看是不是叶子节点的变量，B树种叶子节点的逻辑和飞叶节点的逻辑不太一样
    //比如在插入过程中，如果是叶节点我们就直接进行一次插入就可以了，如果不是叶节点我们就需要
    //再往下找，并且要预先分割查找路径。如果是叶子节点，那么我们实际上做的是一个插入操作，在节点中插入东西
    //而且叶子节点也有一些特点，那就是他没有字数，也就是说他一开始子节点指针数组是空的，当树根节点不断上升的时候这个指针数组才会
    //开始起作用。
    bool leaf;
    //其实在B树种根节点也很特殊，我们也需要特殊处理
    //然后是一个key数组，这个数组存的是我们真正需要的东西
    T *keyArr;
    //然后是一个指针数组，这个数组比key数组多一位
    BTreeItem<T> **childArr;
    //为了方便，我们记录一下父节点，虽然实际上在《算法导论》的设计中，节点并不需要什么父节点
    BTreeItem<T> *parent;
    //这里我们使用一个变量来key数组使用的有效位，我们使用m记录，同时对于非叶子节点，那么子节点数组的有效位就是m+1
    int valid;
public:
    //为了方便调试，我们加入一个节点的打印功能
    void printItem();

    //我们创建一个构造函数
    BTreeItem(bool isLeaf, int Treerank);
};


//下面就是B树的实现
template<class T>
class BTree {
    //我们首先设置一下树的私有数据成员
private:

    //为了方便进行调试，我们的处理就是将所有的节点指针放一份到一个数组里
    BTreeItem<T> **ItemPtrPool;
    //这个变量是上面那个索引的有效大小
    int ItemPtrPoolLastIndex;
    //我们使用一个变量存储这个数的阶，这个决定了我们申请节电中两个数组的大小
    int rank;
public:
    //指向根节点的指针
    BTreeItem<T> *root;

    //构造函数，我们创建一个新的节点，然后创建出一个指针池，并且创建阶数
    BTree(T newValue, int newrank);

    //这里我们使用一个函数来进行所有节点的打印，方便调试
    void printTree();

    //这里设置一个节点分裂的函数，形参我们要分裂的父节点的指针，以及这个子节点在
    //父节点数组中索引值
    void splitItem(BTreeItem<T> *parent, int childIndex);

    //这里设置一个key值插入的函数，这里的第一个形参我们需要插入一个要添加元素的子树的根
    //因为这个函数是一个递归函数
    void insertKey(T keyValue, BTreeItem<T> *root);

    //这里我们设定一个key查找函数，并返回其所在节点
    BTreeItem<T> *searchKey(T keyValue);

    //双节点合并的函数，形参分别是合并节点的父节点，然后就是两个节点在父节点中子树指针的索引
    void itemMerge(BTreeItem<T> *parent, int left, int right);

    //从左右要节点的函数，我们称为平衡函数，向左右要节点，使自己的值不要太少了
    //如果可以从左右要到节点，那就返回true，反之false
    bool balanceItem(BTreeItem<T> *parent, int child);

    //找前趋key所在的Item，
    BTreeItem<T> *getPre(BTreeItem<T> *now, int keyIndex);

    //找后继所在的Item
    BTreeItem<T> *getPost(BTreeItem<T> *now, int keyIndex);

    //删除函数
    void delItemKey(T key);

    //删除以root为子树跟的key
    void delItemKeyWithRoot(BTreeItem<T> *childRoot, T key);
};

template<class T>
void BTree<T>::printTree() {
    cout << endl << "准备打印所有节点" << endl;
    for (int i = 0; i <= ItemPtrPoolLastIndex; ++i) {
        //我们打印那个存储了所有节点指针的数组
        //vaild为-1说明这个节点什么都没有存，那就是废节点
        if (ItemPtrPool[i]->valid == -1) {
            cout << "跳过废节点" << endl;
        } else {
            ItemPtrPool[i]->printItem();
            cout << endl;
        }
    }
    cout << "打印完所有节点" << endl;
}

template<class T>
void BTree<T>::splitItem(BTreeItem<T> *parent, int childIndex) {
    //这里是节点分分裂操作
    //valid是最后一个指针的索引，如果这个索引值+1=数组中的元素个数=阶数-1，说明这个是满的节点
    //需要分裂的节点
    if (parent->childArr[childIndex]->valid == rank - 2) {
        //这里说明这个子节点要被拆了。
        //现在我们拆一下子节点，拆成相等的两份，中间节点上移，先找出中间节点
        int middleIndex = (rank - 2) / 2;
        //然后创建一个新的节点，将中间节点之后的值挪过去
        BTreeItem<T> *newItem = new BTreeItem<T>(parent->childArr[childIndex]->leaf, rank);
        //我们初始化父节点指针
        newItem->parent = parent;

        //我们把这个节点寄存在数组中
        ItemPtrPoolLastIndex++;
        ItemPtrPool[ItemPtrPoolLastIndex] = newItem;

        //然后我们将前面节点后半部分的key值放到新建的节点上就好了。
        for (int i = middleIndex + 1; i <= rank - 2; ++i) {
            //有效值从-1开始，每次为key数组插入新值之前加一
            newItem->valid++;
            newItem->keyArr[newItem->valid] = parent->childArr[childIndex]->keyArr[i];
        }


        //然后我们将后半部分的子节点指针拷过去，如果是叶节点就不用拷贝了
        if (!newItem->leaf) {
            //如果不是叶节点才要进行子指针的拷贝
            for (int i = middleIndex + 1; i <= rank - 1; ++i) {
                newItem->childArr[i - middleIndex - 1] = parent->childArr[childIndex]->childArr[i];
            }
        }

        //这里修改前面一个数组的有效位
        parent->childArr[childIndex]->valid = (rank - 2) / 2 - 1;


        //===================基于插入排序的key值插入================================

//        //然后将中间key插入在父节点中，并且将新节点的指针插入到key的右下方
//        //为什么我们说是右下方，这个和我们的分裂方式有关，我们是左边往右边分出去一个新的节点的
//        //这里我们进行key的插入，使用插入排序的思路
//        //我们假设父节点还没有满
//        //然后我们设定一个变量来存储插入的位置，从而可以判定子节点指针在父节点数组中的插入位置
//        int ptrInsert = 0;
//        //我们从父节点已有key值的最后一位插入
//        for (int j = parent->valid; j >= 0; j--) {
//            if (parent->childArr[childIndex]->keyArr[middleIndex] <= parent->keyArr[j]) {
//                parent->keyArr[j + 1] = parent->keyArr[j];
//            }
//
//            if (parent->childArr[childIndex]->keyArr[middleIndex] > parent->keyArr[j]) {
//                //这里说明已经遍历到了父节点的key值比要插入的值小的状况了，我们插入在遍历位置的后一位
//                //后一位是刚刚挪动过的
//                parent->keyArr[j + 1] = parent->childArr[childIndex]->keyArr[middleIndex];
//                ptrInsert = j + 1;
//            }
//
//            if (j == 0) {
//                //这里说明要插入的值是最小的，我们插入在0节点就好了
//                parent->keyArr[j] = parent->childArr[childIndex]->keyArr[middleIndex];
//                ptrInsert = 0;
//            }
//        }

        //===================基于插入排序的key值插入================================

        //我们可以看到，我们之前的处理不太好，因为上面的这个逻辑没有办法很好的处理key数组是空但是
        //子节点指针数组有值的情况，所以既然我们已经知道key值会插入在分裂节点在父节点中指针的右上方
        //那么我们为什么还需要这种基于插入排序的插入方法呢
        for (int j = parent->valid; j >= childIndex; j--) {
            //我们挪动key数组的值
            parent->keyArr[j + 1] = parent->keyArr[j];
        }

        //现在位置空出来了
        parent->keyArr[childIndex] = parent->childArr[childIndex]->keyArr[middleIndex];


        //下面来插入子节点指针，假设key插入的位置是a，那么我们要插入的是右下方，也就是a+1
        //我们要将包裹a+1之后的位置向后挪动，子节点指针的数组是
        for (int k = parent->valid + 1; k >= childIndex + 1; k--) {
            parent->childArr[k + 1] = parent->childArr[k];
        }

        //现在新插入key的右下方已经被空出来了，我们插入新的节点指针
        parent->childArr[childIndex + 1] = newItem;
        //然后我们调整父指针的key数组有效位
        parent->valid++;
        //然后将新的指针节点插入在新加入key的右下方，其实根据上面的插入，已有的指针已经就在新加入
        //这里整个分裂就已经完成了。

    } else {
        cout << "此节点不需要分裂" << endl;
    }
}

template<class T>
BTree<T>::BTree(T newValue, int newrank) {
    //我们使用一个值来进行初始化
    //创建一个新节点，阶数为6
    root = new BTreeItem<T>(true, 6);

    //然后我们在这个节点中插入一个值
    root->valid++;
    root->keyArr[root->valid] = newValue;


    //然后我们创建指针池数组
    ItemPtrPool = new BTreeItem<T> *[20];
    //初始化阶数
    rank = newrank;
    //我们初始化这个数组
    for (int i = 0; i < 20; ++i) {
        ItemPtrPool[i] = 0;
    }
    //初始化索引，指向有值的最后一位索引
    ItemPtrPoolLastIndex = -1;

    //我们把根节点放到数组中
    ItemPtrPoolLastIndex++;
    ItemPtrPool[ItemPtrPoolLastIndex] = root;

}

template<class T>
void BTree<T>::insertKey(T keyValue, BTreeItem<T> *childRoot) {
    cout << "准备插入" << endl;
    //在插入的过程中根节点是要进行特殊处理的
    //如果我们发现根节点要满了，那么我们要对根节点的分裂特殊处理
    if (childRoot == root && root->valid == (rank - 2)) {
        cout << "发现根节点已满" << endl;
        //那么就要进行根节点的节点分裂
        //我们先创造出来一个新的根节点
        BTreeItem<T> *newRoot = new BTreeItem<T>(false, rank);
        //将新节点的指针放在指针池中
        ItemPtrPoolLastIndex++;
        ItemPtrPool[ItemPtrPoolLastIndex] = newRoot;

        newRoot->childArr[0] = root;
        root = newRoot;
        splitItem(root, 0);


        //然后我们继续从根节点进行递归调用
        insertKey(keyValue, root);
        //这里就可以结束函数了
        return;
    }


    BTreeItem<T> *now = childRoot;

    //如果不是叶节点，那就要看方向然后继续递归
    if (!now->leaf) {
        cout << "当前节点是飞叶节点" << endl;
        for (int i = 0; i <= now->valid; ++i) {
            if (keyValue < now->keyArr[i]) {
                //我们找一个第一个比keyValue大的数，向这个树右边走，然后退出循环
                //我们首先看看左边的节点要不要分裂，如果不会分裂，下面的函数不会执行
                //看看要不要分裂
                if (now->childArr[i]->valid == rank - 2) {
                    //这里就是要分裂了
                    splitItem(now, i);
                    //分裂完之后再当前节点再进行一次递归
                    insertKey(keyValue, now);
                    return;
                } else {
                    //这里就是不要分裂，直接向下递归找插入位置
                    insertKey(keyValue, now->childArr[i]);
                    return;
                }
            }
            if ((keyValue > (now->keyArr[i])) && i == now->valid) {
                //如果要加入的key比key数组的最后一位还大，那我们就往这个key的右边走
                //还是要看看要不要分裂
                if (now->childArr[i + 1]->valid == rank - 2) {
                    //要分裂
                    splitItem(now, i + 1);
                    //分裂完之后原地递归
                    insertKey(keyValue, now);
                    return;
                } else {
                    //不分裂就向下递归
                    insertKey(keyValue, now->childArr[i + 1]);
                    return;
                }
            }

            if (keyValue == now->keyArr[i]) {
                cout << "不能插入重复键值" << endl;
            }
        }
    } else {
        cout << "当前节点是叶节点" << endl;
        //这里就是叶节点，我们直接插入就好，因为都已经提前分裂好了，我们不用担心分裂问题
        //设定插入位置，没进下面的循环就默认插在最后
        int insertIndex = now->valid + 1;

        for (int i = now->valid; i >= 0; i--) {
            //节点中的内容从小到大排序的，我们使用插入排序的方式
            if (keyValue == now->keyArr[i]) {
                cout << "不能插入重复键值" << endl;
                return;
            }
            //利用插入排序的思路
            if (keyValue < now->keyArr[i]) {
                now->keyArr[i + 1] = now->keyArr[i];
                insertIndex = i;
            }//=====下面这个方式没有办法处理插入头部的元素，传统的插入排序也是在循环之外插入的
//            else {
//                //到这里说明前面已经没有比新加入的key大的值了，那么，新的key就加在这个节点后面
//                now->keyArr[i + 1] = keyValue;
//                now->valid++;
//                return;
//            }
            else {
                //当发现当前遍历的key已经比要插入的key小了，那就直接结束循环吧
                break;
            }
        }
        now->valid++;
        now->keyArr[insertIndex] = keyValue;
    }


}

template<class T>
BTreeItem<T> *BTree<T>::searchKey(T keyValue) {
    BTreeItem<T> *now = root;
    //我们从根节点开始向下查找，使用迭代的方式
    while (!now->leaf) {
        //不断查找当前节点
        for (int i = 0; i <= now->valid; ++i) {
            if (keyValue == now->keyArr[i]) {
                cout << "在B树中找到了" << endl;
                return now;
            } else if (keyValue < now->keyArr[i]) {
                //除了最后一个，我们永远向左子树查找，我们从当前节点最小的开始扫描，然后找到一个比查找值打的key
                //从这个key的左下方继续查找
                now = now->childArr[i];
                break;
            }

            //这里处理最后一个节点，可能要往右下方走
            if (i == now->valid && keyValue > now->keyArr[i]) {
                now = now->childArr[i + 1];
                break;
            }
        }
    }

    //这里就是处理叶节点了，我们遍历叶节点
    for (int j = 0; j <= now->valid; ++j) {
        if (keyValue == now->keyArr[j]) {
            cout << "在B树种找到了" << endl;
            return now;
        }
    }

    //这里说明找不到
    cout << "找不到" << endl;

    return 0;

}

template<class T>
void BTree<T>::itemMerge(BTreeItem<T> *parent, int left, int right) {
    //我们可以进行合并，这个合并对于根节点是要特殊处理的
    //只有根节点子树的合并会造成树高度的变化，特别是当根节点只有一个节点的时候
    //我们在逻辑上保留的是left，将夹在left和right之间的节点合并下来，也把右边的节点合并进来

    //首先将父节点中的值拿下来
    parent->childArr[left]->valid++;
    parent->childArr[left]->keyArr[parent->childArr[left]->valid] = parent->keyArr[left];


    //后边节点的子树指针
    if (!parent->childArr[left]->leaf) {
        //非叶节点才合并
        for (int i = 0; i <= parent->childArr[right]->valid; ++i) {
            parent->childArr[left]->childArr[i + parent->childArr[left]->valid +
                                             1] = parent->childArr[right]->childArr[i];

        }
    }

    //然后把右边节点的key复制过来
    for (int i = 0; i <= parent->childArr[right]->valid; ++i) {
        parent->childArr[left]->valid++;
        parent->childArr[left]->keyArr[parent->childArr[left]->valid] = parent->childArr[right]->keyArr[i];
    }

    //把后面的节点去掉
    parent->childArr[right]->valid = -1;

    //把parent节点的对应key去掉，那个key的索引也是left
    for (int j = left; j <= parent->valid - 1; ++j) {
        parent->keyArr[j] = parent->keyArr[j + 1];
    }

    //然后处理掉right的指针
    for (int k = right; k < parent->valid; ++k) {
        parent->childArr[k] = parent->childArr[k + 1];
    }

    parent->valid--;

    //如果parent已经没有东西了，那么我们需要删除并且重定向根节点
    if (parent->valid == -1 && parent == root) {
        //这里说明根节点已经什么都没有了，我们重新定位根节点
        root = root->childArr[0];
    }

}

template<class T>
bool BTree<T>::balanceItem(BTreeItem<T> *parent, int child) {
    cout << "开始进行节点平衡" << endl;
    //rank/2是子树个数的最低限度，rank/2-1是子树指针的最低索引，valid+1是子树指针实际的最大索引
    if (child - 1 >= 0 && (parent->childArr[child - 1]->valid + 2) > (rank / 2)) {
        cout << "向左边要节点" << endl;
        //这里的说明可以向左边要一个节点
        //左边节点的右侧key和子节点指针都要移到child节点的最左侧
        //首先插入key
        for (int i = 0; i < parent->childArr[child]->valid; ++i) {
            parent->childArr[child]->keyArr[i + 1] = parent->childArr[child]->keyArr[i];
        }

        //这里插入，插入在child的首位，把父节点放到child上
        parent->childArr[child]->keyArr[0] = parent->keyArr[child - 1];

        //把child左边节点最大值放到父节点上
        parent->keyArr[child - 1] = parent->childArr[child - 1]->keyArr[parent->childArr[child - 1]->valid];

        //然后把child左边节点的最右指针挪过来
        for (int j = 0; j < parent->childArr[child]->valid + 1; ++j) {
            //挪出来一个位置
            parent->childArr[child]->childArr[j + 1] = parent->childArr[child]->childArr[j];
        }

        parent->childArr[child]->childArr[0] = parent->childArr[child - 1]->childArr[
                parent->childArr[child - 1]->valid + 1];

        //整理数组有效位
        parent->childArr[child]->valid++;
        parent->childArr[child - 1]->valid--;
        //这样子就全部完成了

        return true;
    } else if (child + 1 <= parent->valid + 1 && (parent->childArr[child + 1]->valid + 2) > (rank / 2)) {
        //我们这里要看child右边的索引是不是存在
        cout << "向右边节点要" << endl;

        //这里就说明要和右边的换
        //首先是将key从父节点换下来
        parent->childArr[child]->keyArr[parent->childArr[child]->valid + 1] = parent->keyArr[child];

        //然后将右边节点最左边key放到父节点上
        parent->keyArr[child] = parent->childArr[child + 1]->keyArr[0];
        for (int i = 0; i < parent->childArr[child + 1]->valid; ++i) {
            parent->childArr[child + 1]->keyArr[i] = parent->childArr[child + 1]->keyArr[i + 1];
        }

        //然后将右边节点的子树指针给child
        parent->childArr[child]->childArr[parent->childArr[child]->valid + 2] = parent->childArr[child +
                                                                                                 1]->childArr[0];

        //将右边节点的子树数组缩一下
        for (int j = 0; j < parent->childArr[child + 1]->valid + 1; ++j) {
            parent->childArr[child + 1]->childArr[j] = parent->childArr[child + 1]->childArr[j + 1];
        }

        //然后重新整理数组有效位
        parent->childArr[child]->valid++;
        parent->childArr[child + 1]->valid--;

        return true;
    }

    return false;

}

template<class T>
BTreeItem<T> *BTree<T>::getPre(BTreeItem<T> *now, int keyIndex) {
    //首先只有飞叶节点才有前趋和后继
    if (now->leaf) {
        //如果是叶节点就不用找了
        cout << "这个是叶节点，没有前趋节点" << endl;
        return 0;
    } else {
        //这里是非叶节点，前趋，向左下先走一步
        BTreeItem<T> *scan = now->childArr[keyIndex];
        //然后我们一路向右，这个右是整个节点的最右
        while (!scan->leaf) {
            //如果不是叶节点我们就一路向最右走
            scan = scan->childArr[scan->valid + 1];
        }
        //返回前趋所在的节点，我们看前趋节点的最后一个key就好了
        return scan;
    }
}

template<class T>
void BTree<T>::delItemKey(T key) {
    delItemKeyWithRoot(root, key);
}

template<class T>
void BTree<T>::delItemKeyWithRoot(BTreeItem<T> *childRoot, T key) {
    //我们首先从childRoot向下找
    //首先先遍历当前节点值
    for (int i = 0; i <= childRoot->valid; ++i) {
        if (key == childRoot->keyArr[i]) {
            //这里说明找到了，那么我们要看看是叶节点 还是飞叶节点
            if (childRoot->leaf) {
                //如果是叶节点，那么我们直接删除就好
                for (int j = i; j < childRoot->valid; ++j) {
                    childRoot->keyArr[j] = childRoot->keyArr[j + 1];
                }
                childRoot->valid--;
                return;
            } else {
                //如果不是叶节点那么我们就要看往哪个方向删除
                //首先看左节点的大小，看看够不够
                if (childRoot->childArr[i]->valid + 2 > rank / 2) {
                    //这里我们可以看到，左边是够的，那么我们就去找前趋
                    BTreeItem<T> *newKeyItem = getPre(childRoot, i);
                    T newKey = newKeyItem->keyArr[newKeyItem->valid];

                    //从当前节点递归删除前趋
                    delItemKeyWithRoot(childRoot, newKey);

                    //然后替换
                    childRoot->keyArr[i] = newKey;

                    return;
                } else if (childRoot->childArr[i + 1]->valid + 2 > rank / 2) {
                    //这里是右边够的，那就找后继
                    BTreeItem<T> *newKeyItem = getPost(childRoot, i);
                    T newKey = newKeyItem->keyArr[0];

                    //从当前节点递归删除后继
                    delItemKeyWithRoot(childRoot, newKey);

                    //替换
                    childRoot->keyArr[i] = newKey;

                    return;
                } else {
                    //之类说明两边都不行
                    //那么就进行一次合并
                    itemMerge(childRoot, i, i + 1);

                    //然后再从递归之后当前节点递归删除
                    delItemKeyWithRoot(childRoot, key);

                    return;
                }
            }
        }//这里说明我们要找的key和当前遍历的key不相同，从左边遍历，我们要找的第一个比key大的
        else if (key < childRoot->keyArr[i]) {
            //如果已经是叶子节点，没有办法继续了，所以我们必须保证是非也节点才能保证递归
            if (!childRoot->leaf) {
                //那么我们就从左下递归
                if (childRoot->childArr[i]->valid + 2 == rank / 2) {
                    //如果左右有节点可以给当前子树
                    if (balanceItem(childRoot, i)) {
                        //这里就是如果可以从两边要到节点并且
                        //那么我们就进行一次原地递归
                        delItemKeyWithRoot(childRoot, key);
                        return;
                    } else {
                        //这里说明要一次合并然后再递归
                        itemMerge(childRoot, i, i + 1);
                        delItemKeyWithRoot(childRoot, key);
                        return;
                    }
                } else {
                    //这里说明不少东西，直接向左走
                    delItemKeyWithRoot(childRoot->childArr[i], key);
                    return;
                }
            }

        }//如果我们要找的key比最后一个都大，那么我们就可以直接从最后元素的右边递归
        else if (i == childRoot->valid) {
            //如果是非叶节点我们才继续考虑，关于向下递归这里尤其要考虑叶节点的情况
            if (!childRoot->leaf) {
                //这里是key比最后一个值要大的情况
                //我们向右下递归
                if (childRoot->childArr[i + 1]->valid + 2 == rank / 2) {
                    //如果左右有节点可以给当前子树
                    if (balanceItem(childRoot, i)) {
                        //这里就是如果可以从两边要到节点并且
                        //那么我们就进行一次原地递归
                        delItemKeyWithRoot(childRoot, key);
                        return;
                    } else {
                        //这里说明要一次合并然后再递归
                        itemMerge(childRoot, i, i - 1);
                        delItemKeyWithRoot(childRoot, key);
                        return;
                    }
                } else {
                    //这里说明不少东西，直接向右走
                    delItemKeyWithRoot(childRoot->childArr[i + 1], key);
                    return;
                }
            }
        }
    }

    cout << "要删除的元素不在树中" << endl;
}

template<class T>
BTreeItem<T> *BTree<T>::getPost(BTreeItem<T> *now, int keyIndex) {

    if (now->leaf) {
        cout << "这是叶节点，没有后继" << endl;
        return 0;
    } else {
        //首先创建一个扫描指针，后继节点
        //我们优先向右下走一步，然后一路向最左走
        BTreeItem<T> *scan = now->childArr[keyIndex + 1];

        while (!scan->leaf) {
            scan = scan->childArr[0];
        }

        //走到这里就是后继所在的节点了
        return scan;
    }


    return 0;
}


template<class T>
void BTreeItem<T>::printItem() {
    //这里我们打印一下节点的内容，主要打印的是key数组的值
    cout << leaf << " " << valid << " [";
    for (int i = 0; i <= valid; ++i) {
        cout << keyArr[i] << ",";
    }
    cout << "]";
}

template<class T>
BTreeItem<T>::BTreeItem(bool isLeaf, int Treerank) {
    //这里我们创建一个构造函数
    leaf = isLeaf;
    //创建key数组，key的数量不能多于Treeranks-1个
    keyArr = new T[Treerank - 1];
    //创建子节点指针数组，这个数组比key数组多一位
    childArr = new BTreeItem<T> *[Treerank];
    //初始化数组的有效位的最后一个指针，这里指的是key
    valid = -1;
    //这里注意父指针没有初始化，我们需要在外面初始化一下
    parent = 0;
}

#endif //MYDATASTRUCTURE_BTREE_H
