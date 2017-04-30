//
// Created by 杜臻 on 17/3/31.
//

#ifndef MYDATASTRUCTURE_LINKEDLIST_H
#define MYDATASTRUCTURE_LINKEDLIST_H

#include <iostream>
#include <cstdlib>
using namespace std;


template<class T>
class LinkedItem;


//这里我们实现一个链表
template<class T>
class LinkedList {
public:
    LinkedList(T content);

    void insert(int position, T item);

    T deleteItem(int position);

    void printLinkedList();

    ~LinkedList();


private:
    //指向链表的最后一个元素。
    LinkedItem<T> *last;
    int length;
};


template<class T>
LinkedList<T>::LinkedList(T content)
        : length(1) {
    //链表使用一个元素初始化
    //所有的链表节点都在堆区中
    LinkedItem<T> *newItem = new LinkedItem<T>();
    newItem->content = content;
    last = newItem;
    newItem->next = newItem;
    cout << "链表被初始化" << endl;
}

//position代表插入在哪个节点的后面
template<class T>
void LinkedList<T>::insert(int position, T item) {

    //如果现在什么都没有，那么我们就要直接建一个绩点，并且让这个节点指针指向自己，构成一个环装
    if (position >= length) {
        cout << "输入不合法" << endl;
        return;
    } else {
        //如果是插在第一个，first指针就要特殊处理
        if (position == -1){
            //所有的链表节点都在堆区中
            LinkedItem<T> *newItem = new LinkedItem<T>();
            newItem->content = item;
            newItem->next = last->next;
            last->next = newItem;

        } else{

            //创建一个指针来遍历链表，这个指针初始化指向链表头部
            LinkedItem<T> *nowItem = last->next;

            //这里首先到达position所到达的位置
            for (int i = 0; i < position; ++i) {
                nowItem = nowItem->next;
            }

            //然后这里创建一个节点
            LinkedItem<T> *newItem = new LinkedItem<T>();
            newItem->content = item;
            newItem->next = nowItem->next;
            nowItem->next = newItem;

            //如果是加在最后的，那么我们要注意修改last指针
            if (position == (length - 1)){
                last = newItem;
            }
        }
    }

    length++;

}

template<class T>
void LinkedList<T>::printLinkedList() {
    //设立一个指针遍历链表
    LinkedItem<T> *nowItem = last->next;

    //打印这个链表
    for (int i = 0; i < length; ++i) {
        cout << nowItem->content << " ; ";
        nowItem = nowItem->next;
    }

    cout << endl;
}

template <class T>
T LinkedList<T>::deleteItem(int position) {
    //还是要先进行输入合法性的验证
    LinkedItem<T>* delItem;

    if (position >= length) {
        cout << "输入不合法" << endl;
        exit(-1);
    } else{
        //这里是输入合法的状况
        //如果是删除头结点和尾节点都要单独处理
        if (position == -1){
            //删除头结点
            delItem = last->next;
            //重新定位头结点
            last->next = delItem->next;
//            //返回删除的值
//            return delItem->content;
        } else{
            //如果是删除最后一个元素，就要重新定位last
            if(position == (length - 1)){

                //首先定位到我们要删除的位置
                //创建一个指针来遍历链表，这个指针初始化指向链表头部
                LinkedItem<T> *nowItem = last->next;
                LinkedItem<T> *redirItem = 0;
                //这里首先到达position所到达的位置
                for (int i = 0; i < position; ++i) {
                    if(i = position-1){
                        //获取倒数第二个元素
                        redirItem = nowItem;
                    }
                    nowItem = nowItem->next;
                }

                //删除
                delItem = nowItem->next;
                nowItem -> next = delItem -> next;
                last = redirItem;
            } else{
                //首先定位到我们要删除的位置
                //创建一个指针来遍历链表，这个指针初始化指向链表头部
                LinkedItem<T> *nowItem = last->next;

                //这里首先到达position所到达的位置
                for (int i = 0; i < position; ++i) {
                    nowItem = nowItem->next;
                }

                //删除
                delItem = nowItem->next;
                nowItem -> next = delItem -> next;
            }

        }

    }

    //返回删除的值
    T returnValue = delItem->content;
    length--;
    delete delItem;
    return returnValue;
}

template <class T>
LinkedList<T>::~LinkedList() {
    //这里进行所有链表节点的析构操作
    //不断删除第一个元素就好
    for (int i = 0; i < length; ++i) {
        deleteItem(0);
    }
}


template<class T>
class LinkedItem {
//设定链表元素的友元，
    friend class LinkedList<T>;

private:
    T content;
    LinkedItem<T> *next;
};


#endif //MYDATASTRUCTURE_LINKEDLIST_H
