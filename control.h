#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    Q_INVOKABLE void setControlUpDown(QString, QString, QString, QString, QString, QString, QString);

signals:
    changeShowString(QString str1, QString str2, QString str3, QString str4, QString str5, QString str6, QString str7);

public slots:

private:

};

#endif // CONTROL_H
