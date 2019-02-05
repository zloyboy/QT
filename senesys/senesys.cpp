#include "senesys.h"

Senesys::Senesys(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("SENESYX");
    db.setUserName("root");
    db.setPassword("mysql");
    db.setConnectOptions("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3");
    db.open();
}

bool Senesys::checkAccess(ulong userId)
{
    QSqlQuery query;

    query.prepare("SELECT DateFrom, DateTo, TimeFrom, TimeTo, WeekDays FROM TimeZones WHERE UserID = ?");
    query.addBindValue(uint(userId));
    query.exec();

    if (query.first())
    {
        QDate dateFrom = query.value(0).toDate();
        QDate dateTo = query.value(1).toDate();
        QTime timeFrom = query.value(2).toTime();
        QTime timeTo = query.value(3).toTime();
        uint weekDays = query.value(4).toUInt();

        QDateTime now = QDateTime::currentDateTime();

        if ((weekDays & 0x01) && !(weekDays >> now.date().dayOfWeek() & 0x01))
            return false;

        if (now.date() < dateFrom || now.date() > dateTo)
            return false;

        if (now.time() < timeFrom || now.time() > timeTo)
            return false;

        return true;
    }

    return false;
}

bool Senesys::getUserId(ulong *userId, ulong cardId)
{
    QSqlQuery query;

    query.prepare("SELECT UserID FROM Cards WHERE CardID = ?");
    query.addBindValue(uint(cardId));
    query.exec();

    if (query.first())
    {
        *userId = query.value(0).toUInt();

        return true;
    }

    return false;
}

QString Senesys::getUserName(ulong userId)
{
    QSqlQuery query;

    query.prepare("SELECT FirstName, LastName FROM Users WHERE UserID = ?");
    query.addBindValue(uint(userId));
    query.exec();

    if (query.first())
    {
        QString firstName = query.value(0).toString();
        QString lastName = query.value(1).toString();

        return firstName + " " + lastName;
    }

    return QString();
}
