//
// Created by 杜臻 on 2017/4/25.
//

#ifndef MYDATASTRUCTURE_BINARYSEARCHTREE_H
#define MYDATASTRUCTURE_BINARYSEARCHTREE_H

#include <iostream>
#include "Queue.h"
#include "LinkedBTree.h"

template<class T>
class BinarySearchItem;

template<class T>
class BinarySearchTree {
public:
	BinarySearchTree(T rootvalue);

	//插入元素
	void insert(T insertValue);

	//查找查看某一个值的节点是不是存在，如果存在返回树节点节点，不存在返回空指针
	BinarySearchItem<T> *ifExist(T searchValue);

	//删除元素
	void delItem(T delValue);


	//使用广度优先搜索来进行析构
	~BinarySearchTree();

private:
	BinarySearchItem<T> *root;

	//寻找后继节点
	BinarySearchItem<T> *post_Item(BinarySearchItem<T> *now);
};

template<class T>
BinarySearchTree<T>::BinarySearchTree(T rootvalue) {
	//我们构建根节点
	root = new BinarySearchItem<T>(rootvalue);
}

template<class T>
void BinarySearchTree<T>::insert(T insertValue) {
	//我们插入一个节点从根节点开始比较
	//创建一个遍历树的指针
	BinarySearchItem<T> *now = root;
	BinarySearchItem<T> *pass = 0;
	//一直向下遍历，直到now已经变成空指针
	while (now != 0) {
		if (insertValue >= (now->element)) {
			//如果比当前节点大，那就往右子树方向走
			pass = now;
			now = now->right;
		}
		else {
			//如果比当前节点小，那就往左子树方向走
			pass = now;
			now = now->left;
		}
	}
	//到这里之后pass节点之后就是我们要插入节点的地方
	if (insertValue >= (pass->element)) {
		//如果比pass大，那就插在pass右边
		pass->right = new BinarySearchItem<T>(insertValue);

		pass->right->parent = pass;
	}
	else {
		//比pass小，插左边
		pass->left = new BinarySearchItem<T>(insertValue);

		pass->left->parent = pass;
	}
}

template<class T>
BinarySearchItem<T> *BinarySearchTree<T>::ifExist(T searchValue) {
	//使用一个指针来遍历数组
	BinarySearchItem<T> *now = root;
	//如果找到最后发现now是一个空指针，那么就说明并没有找到我们需要的元素。
	while (now != 0) {
		if (now->element == searchValue) {
			return now;
		}
		else if (searchValue > (now->element)) {
			//如果发现比子树根节点大，那就往右子树走
			now = now->right;
		}
		else {
			now = now->left;
		}
	}

	return 0;
}

template<class T>
void BinarySearchTree<T>::delItem(T delValue) {
	//首先我们在当前树中找到这个节点

	BinarySearchItem<T> *getItem = ifExist(delValue);

	//看看是不是找到了
	if (getItem == 0) {
		cout << "这个节点并不存在" << endl;
		return;
	}

	//我们进行删除，主要分为三种情况，在没有子节点的时候我们直接删除
	//首先是没有子节点的情况
	if (getItem->right == 0 && getItem->left == 0) {
		//直接删除，并且修改父节点的子树指针
		BinarySearchItem<T> *parentPtr = getItem->parent;

		//如果父节点指针是空的，我们不让删除。根节点最好还是不要删除为好
		if (parentPtr == 0) {
			cout << "this is the only root item" << endl;
		}


		//然后查看是左子树还是右子树
		if (parentPtr->left == getItem) {
			//左子树就析构左子树节点
			delete parentPtr->left;
			parentPtr->left = 0;
		}
		else if (parentPtr->right == getItem) {
			//是父节点的右子树就析构右子树节点
			delete parentPtr->right;
			parentPtr->right = 0;
		}
	}//这里是有一个子节点的情况，首先假设有左节点
	else if (getItem->right == 0 && getItem->left != 0) {
		//删除并连接，修改父节点的子树指针
		BinarySearchItem<T> *parentPtr = getItem->parent;
		BinarySearchItem<T> *leftPtr = getItem->left;
		leftPtr->parent = parentPtr;
		//这里我们进行一个判断，如果我们看看会不会出现父节点指针为0的情况。
		if (parentPtr == 0)
		{
			//我们看看这里这里会不会判断出是父节点
			cout << "find no parent item" << endl;
			//这里我们进行root指针的重构，走到这里说明root根节点已经被删除了

			//这里说明有一个左子节点，我们首先删除当前节点，然后把root节点给左子节点就好了
			BinarySearchItem<T> *tmp = root;
			root = root->left;
			root->parent = 0;
			delete tmp;

			return;


		}
		//然后查看是左子树还是右子树
		if (parentPtr->left == getItem) {
			//左子树就析构左子树节点，并且连接
			delete parentPtr->left;
			parentPtr->left = leftPtr;

		}
		else if (parentPtr->right == getItem) {
			//是父节点的右子树就析构右子树节点
			delete parentPtr->right;
			parentPtr->right = leftPtr;
		}
	}//这里还有只有一个子节点的情况，我们假设只有右节点
	else if (getItem->left == 0 && getItem->right != 0) {
		//删除并连接，修改父节点的子树指针
		BinarySearchItem<T> *parentPtr = getItem->parent;
		BinarySearchItem<T> *rightPtr = getItem->right;
		rightPtr->parent = parentPtr;

		//如果我们发现父节点是空，那么就是根节点
		if (parentPtr == 0) {
			//应该是右边有子节点
			//我们把根节点给右边的子节点
			BinarySearchItem<T>* tmp = root;
			root = root->right;
			root->parent = 0;
			delete tmp;

			return;
		}


		//然后查看是左子树还是右子树
		if (parentPtr->left == getItem) {
			//左子树就析构左子树节点，并且连接
			delete parentPtr->left;
			parentPtr->left = rightPtr;

		}
		else if (parentPtr->right == getItem) {
			//是父节点的右子树就析构右子树节点
			delete parentPtr->right;
			parentPtr->right = rightPtr;
		}
	}//这里我们假设既有左节点又有右节点
	else if (getItem->left != 0 && getItem->right != 0) {
		//当我们要删除的元素有两个子节点的时候我们就需要注意了，我们要做的是优先找到后继节点
		//并且这个后继节点一定在右子树中，不可能不存在
		BinarySearchItem<T> *postItem = post_Item(getItem);
		//然后我们首先需要将后继节点的值放到我们要删除的节点上来，然后我们真正删除的是后继节点
		getItem->element = postItem->element;
		//删除后继节点，这个后继节点没有左子树，要么有右子树，要么没有右子树，分开讨论
		//如果这个后继节点没有子节点，直接删除即可
		if (postItem->right == 0) {
			//找到后继节点的父节点
			BinarySearchItem<T> *parentItem = postItem->parent;
			if (parentItem->left == postItem) {
				delete parentItem->left;
				parentItem->left = 0;
			}
			else if (parentItem->right == postItem) {
				delete parentItem->right;
				parentItem->right = 0;
			}
		}//如果有右节点，那么我们就需要额外做一个连接操作
		else if (postItem->right != 0) {
			//找到后继节点的父节点，并且做一个连接操作
			BinarySearchItem<T> *parentItem = postItem->parent;
			//右节点
			BinarySearchItem<T> *rightItem = postItem->right;
			rightItem->parent = parentItem;

			if (parentItem->right == postItem) {
				delete parentItem->right;
				parentItem->right = rightItem;
			}
			else if (parentItem->left == postItem) {
				delete parentItem->left;
				parentItem->left = rightItem;
			}
		}

	}
}

template<class T>
BinarySearchItem<T> *BinarySearchTree<T>::post_Item(BinarySearchItem<T> *now) {
	//后继节点的如果有就返回后继节点，没有后继节点那就返回空指针
	//后继节点主要有两个，一个是右子树的最左节点，如果没有右子树，那就往回找祖先节点，找到第一个是左子树根节点的祖先节点的父节点
	//首先看看有没有右子树
	if (now->right != 0) {
		//如果有右子树，那就前往右子树的最左节点
		now = now->right;
		while (now->left != 0) {
			now = now->left;
		}
		//这里now就是右子树的最左节点
		return now;
	}
	else {
		//我们不断向父节点寻找，直到发现我们往父节点走的过程是往右上方走了一步
		//这个判断需要两个变量，一个是遍历到的最新父节点，一个是上一个历史父节点
		//我们要做的判断就是用最新父节点的的左子树和历史父节点做一个比较，如果发现两个相等
		//那么最新父节点就是后继节点
		BinarySearchItem<T> *pass = now;
		now = now->parent;
		while (now != 0 && pass != now->left) {
			//如果发现now还没有走到根节点，并且还没有找到第一个当前节点所在的左子树的父节点（细细体会这句话的含义）
			//向根节点遍历
			pass = now;
			now = now->parent;
		}
		//到这里说明now就是我们要找后继节点的节点所在最小父子树的父节点
		if (now != 0) {
			return now;
		}
	}

	return 0;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
	//利用广度优先搜索来进行析构操作，广度优先搜索的实现需要使用环状队列
	Queue<BinarySearchItem<T> *> *deleteQueue = new Queue<BinarySearchItem<T> *>(100);

	//    //进行广度优先遍历，将二叉树的要delete的节点放在队列中。
	//    BinarySearchItem<T> *now = root;

		//一开始先把节点放在头部
	deleteQueue->add(root);

	while (!deleteQueue->IsEmpty()) {
		//拿出要删除的元素
		BinarySearchItem<T> *delItem = *(deleteQueue->Delete());
		//将要删除元素的左右节点加入到队列中（如果不为空）
		if (delItem->left != 0) {
			deleteQueue->add(delItem->left);
		}
		if (delItem->right != 0) {
			deleteQueue->add(delItem->right);
		}
		cout << "delete " << delItem->element << endl;
		delete delItem;
	}


	//析构队列
	delete deleteQueue;
}


template<class T>
class BinarySearchItem {
	friend class BinarySearchTree<T>;

public:
	BinarySearchItem(T initValue) {
		element = initValue;
		parent = 0;
		left = 0;
		right = 0;
	}

private:
	//父指针
	BinarySearchItem<T> *parent;
	BinarySearchItem<T> *left;
	BinarySearchItem<T> *right;

	T element;
};

#endif //MYDATASTRUCTURE_BINARYSEARCHTREE_H
