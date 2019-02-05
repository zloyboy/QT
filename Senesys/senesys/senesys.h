#ifndef SENESYS_H
#define SENESYS_H

#include <QDateTime>
#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class Senesys : public QObject
{
    Q_OBJECT

public:
    explicit Senesys(QObject *parent = 0);
    bool checkAccess(ulong userId);
    bool getUserId(ulong *userId, ulong cardId);
    QString getUserName(ulong userId);

private:
    QSqlDatabase db;
};

#endif // SENESYS_H
