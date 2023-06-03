#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QVector>
#include "tcpipastm.h"

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    Q_INVOKABLE bool commandOrRepository(QString);
    Q_INVOKABLE void setControlUp();
    Q_INVOKABLE void setControlDown();
    void started();


signals:
    changeShowString(QString str1, QString str2, QString str3, QString str4, QString str5, QString str6, QString str7);

public slots:
    void slotGetRepositories();
    void slotGetRepositoriesUP();
    void slotGetRepositoriesDOWN();

private:
    QStringList list_commands;
    QStringList list_repositories;
    int enter_element;
    int current_element_repositories;
    QVector<QString> vector_elements;
    tcpipastm *obj_tcpip;


private:
    void setPositionElements();
    int getPositionElement(int &, int);
    void setBufferElements(QStringList &, int);
    void requestGetRepositories(QString);
    void clearBeginningBuffer(int);
    void getRepositoriesUPDOWN(int, int);
};

#endif // CONTROL_H
