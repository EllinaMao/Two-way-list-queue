// classwork.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Задание 1
Реализовать шаблонный класс "Очередь" на основе двусвязного списка.

Задание 2
В существующий класс двусвязного списка добавить: операцию клонирования списка (функция должна возвращать адрес головы клонированного списка), перегрузить оператор + (оператор должен возвращать адрес головы нового списка, содержащего элементы обоих списков для которых вызывался оператор), перегрузить оператор * (оператор должен возвращать адрес головы нового списка, содержащего только общие элементы обоих списков для которых вызывался оператор).
*/

#include <iostream>
#include "Two way list.h"

using namespace std;

int main() {
    TwoWayList<int> queue;
    TwoWayList<int> queue2;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);


    queue2.enqueue(10);
    queue2.enqueue(25);
    queue2.enqueue(30);

    queue.output();

    cout << "Front: " << queue.front() << endl; 

    cout << "Dequeue: " << queue.dequeue() << endl; 
    cout << "Dequeue: " << queue.dequeue() << endl; 

    cout << "Is empty: " << endl;

    if (queue.isEmpty()) {
        cout << "Queue is empty." << endl;
    }
    else {
        cout << "Queue is not empty." << endl;
    }

    TwoWayList<int> sum = queue + queue2;
    sum.output();

    TwoWayList<int> intersection = queue * queue2;

    intersection.output();

    return 0;
}
