#include "person.h"

Person::Person(const QString &name, int ticket_number)
    : name(name), ticket_number(ticket_number) {}

QString Person::getName() const {
    return name;
}

int Person::getTicketNumber() const {
    return ticket_number;
}
