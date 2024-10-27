#ifndef QUEUE_H
#define QUEUE_H

#include <QString>
#include "person.h"
class Queue {
public:
    Queue(int capacity);
    ~Queue();

    void enqueue(const Person &person);
    Person dequeue();
    Person peek() const;

    bool isEmpty() const;
    int size() const;

    int position(const QString &name) const;
    int position(int ticket_number) const;

private:
    Person *array;
    int front, rear, count, capacity;
};

#endif // QUEUE_H
