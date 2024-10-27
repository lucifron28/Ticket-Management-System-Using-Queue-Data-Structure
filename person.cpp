#include "person.h"

Person::Person(const QString &name, int ticket_number)
    : name(name), ticket_number(ticket_number) {}

QString Person::getName() const {
    return name;
}

int Person::getTicketNumber() const {
    return ticket_number;
}

QString Person::getFormattedTicketNumber() const {
    return QString("%1").arg(ticket_number, 3, 10, QChar('0'));
}
