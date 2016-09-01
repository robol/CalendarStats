#include "icscalendar.h"
#include <libical/ical.h>
#include <QDebug>
#include <QFile>

ICSCalendar::ICSCalendar(QString path)
{
    mPath = path;
    mValid = parseContent();
}

bool
ICSCalendar::isValid()
{
    return mValid;
}

bool
ICSCalendar::parseContent()
{
    mEventDates.clear();

    QFile icsFile(mPath);
    if (! icsFile.exists()) {
        qDebug() << "Warning: Selected file does not exist!";
    }
    else {
        if (icsFile.open(QIODevice::ReadOnly)) {
            QByteArray content = icsFile.readAll();
            icalcomponent * c = icalparser_parse_string(content.data());

            if (!c) return false;

            // Iterate over all the events in the calendar
            icalcomponent * event = icalcomponent_get_first_component(c, ICAL_VEVENT_COMPONENT);
            do {
                icalproperty * p = icalcomponent_get_first_property(event, ICAL_DTSTART_PROPERTY);
                if (p) {
                    struct icaltimetype t = icalproperty_get_dtstart(p);
                    mEventDates.append(QDateTime(QDate(t.year, t.month, t.day), QTime(0, 0)));
                }
                icalproperty_free(p);
            } while ((event = icalcomponent_get_next_component(c, ICAL_VEVENT_COMPONENT)));

            icalcomponent_free(c);

            return true;
        }
    }

    return false;
}

int
ICSCalendar::countEvents(QDateTime start, QDateTime end)
{
    int total = 0;

    for (int i = 0; i < mEventDates.size(); i++) {
        const QDateTime& t = mEventDates.at(i);
        if (t >= start && t <= end) {
            total++;
        }
    }

    return total;
}
