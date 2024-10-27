#include "queue.h"
#include <stdexcept>

Queue::Queue(int capacity)
    : front(0), rear(-1), count(0), capacity(capacity) {
    array = new Person[capacity];
}

Queue::~Queue() {
    delete[] array;
}

void Queue::enqueue(const Person &person) {
    if (count == capacity) {
        throw std::overflow_error("Queue is full");
    }
    rear = (rear + 1) % capacity;
    array[rear] = person;
    count++;
}

Person Queue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    Person person = array[front];
    front = (front + 1) % capacity;
    count--;
    return person;
}

Person Queue::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    return array[front];
}

bool Queue::isEmpty() const {
    return count == 0;
}

int Queue::size() const {
    return count;
}

int Queue::position(const QString &name) const {
    for (int i = 0; i < count; ++i) {
        int index = (front + i) % capacity;
        if (array[index].getName() == name) {
            return i + 1;
        }
    }
    return -1; // Not found
}

int Queue::position(int ticket_number) const {
    for (int i = 0; i < count; ++i) {
        int index = (front + i) % capacity;
        if (array[index].getTicketNumber() == ticket_number) {
            return i + 1;
        }
    }
    return -1; // Not found
}
