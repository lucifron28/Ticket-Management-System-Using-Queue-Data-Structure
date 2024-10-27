#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person {
public:
    Person(const QString &name = "", int ticket_number = 0);

    QString getName() const;
    int getTicketNumber() const;
    QString getFormattedTicketNumber() const; // Add this line

private:
    QString name;
    int ticket_number;
};

#endif // PERSON_H
