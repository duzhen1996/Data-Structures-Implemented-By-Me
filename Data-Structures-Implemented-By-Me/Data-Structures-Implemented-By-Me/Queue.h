//
//  Queue.hpp
//  MyDataStructure
//
//  Created by 杜臻 on 17/3/28.
//  Copyright © 2017年 杜臻. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include <iostream>

using namespace std;

template<class T>
class Queue {
public:
    Queue(int MaxQueueSize);

    bool IsFull();

    void add(const T &item);

    bool IsEmpty();

    T *Delete();

    void printQueue();

    ~Queue();

private:
    T *queue;
    int front;
    int rear;
    int MaxQueueSize;
};

template<class T>
Queue<T>::Queue(int MaxQueueSize) {
    //因为预留一个空位来进行队列或者空或者满的判断
    this->MaxQueueSize = MaxQueueSize + 1;
    this->queue = new T[this->MaxQueueSize];
    this->front = 0;
    this->rear = 0;
}

template<class T>
void Queue<T>::add(const T &item) {
    //判断是不是满了
    if (((rear + 1) % MaxQueueSize) == front) {
        cout << "已经满了，不能再加入" << endl;
        return;
    }

    //如果没有满，就进行值的插入操作
    queue[rear] = item;
    rear = (rear + 1) % MaxQueueSize;

//    cout << "(rear , front) = " << rear << " , " << front << endl;
}

template<class T>
T *Queue<T>::Delete() {
    //首先判断是不是空的
    if (rear == front) {
        cout << "is empty" << endl;
        return NULL;
    }

    //如果发现没有空，那就取出来这么一个东西
    T returnValue = queue[front];

    //移动头指针的位置
    front = (front + 1) % MaxQueueSize;
//    cout << "(rear , front) = " << rear << " , " << front << endl;
    return &returnValue;
}

template<class T>
bool Queue<T>::IsEmpty() {
    //判断现在这个队列是不是空的
    return (rear == front);
}

template<class T>
bool Queue<T>::IsFull() {
    //现在判断这个队列是不是满的
    return ((rear + 1) % MaxQueueSize) == front;
}

template<class T>
Queue<T>::~Queue() {
    delete queue;
}

template<class T>
void Queue<T>::printQueue() {
    cout << "开始打印:" << endl;
    for (int i = front; i != rear; i = (i + 1) % MaxQueueSize) {
        cout << queue[i] << ";";
    }
    cout << endl;
}


#endif /* Queue_hpp */
