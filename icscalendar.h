#ifndef ICSCALENDAR_H
#define ICSCALENDAR_H

#include <QString>
#include <QDateTime>

class ICSCalendar
{
public:
    ICSCalendar(QString path);

    // Count the number of events falling in the specified interval.
    int countEvents(QDateTime start, QDateTime end);

    // Return true if the calendar has been parsed succesfully.
    bool isValid();

private:
    QString mPath;
    QList<QDateTime> mEventDates;
    bool mValid = false;

    // Parse the content of the file specified by the user
    bool parseContent();
};

#endif // ICSCALENDAR_H
