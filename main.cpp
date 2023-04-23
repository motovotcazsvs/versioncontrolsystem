#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "control.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Control control;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("control", &control); //и регистрируем его в качестве контекста в Qml слое

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    control.started();//
    return app.exec();
}
